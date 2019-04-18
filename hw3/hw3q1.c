/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define N 25
#define BOARD_ELEMENT '#'
#define PERCENT 0
#define FIRST_PLAYER PERCENT
#define P_HEAD '%'
#define SHTRODEL 1
#define S_HEAD '@'
#define ILLEGAL_MOVE 0

#define LOWER_ARR_SIZE 4
#define LOWEST_TURNS_WITHOUT_FOOD 2

#define SNAKE_START_SIZE 3
#define P_BODY '*'
#define S_BODY '+'
#define FOOD_ELEMENT 'F'

#define DOWN 2
#define LEFT 4
#define RIGHT 6
#define UP 8
#define DECIMAL 10
#define ENTER1 '\r' // Enter on the server
#define ENTER2 '\n' //Enter on my local machine
/*-------------------------------------------------------------------------
*   Function declartion
*--------------------------------------------------------------------------*/

void print_introduction_msg();                        //print welcome message , and introduction message to the game
void print_board_size_msg();                          //print message to enter board size
void print_steps_without_food();                      //print message to enter maximum number of steps can snake do without food
void print_food_location_msg();                       //print message to insert place for next food
void help_print_board(int size);                      //printing static part of the board
void print_board(char board[N][N], int size);          //print the current board for the user
void print_player_message(int player);                //print message when we switch between users
void print_insert_direction();			              //print message asking the user to insert his move
void print_finsih_msg(int player,int finish_reason ); //get the player who lose and the reason of losing and print message state
void print_error_input();                             //print message - there is error in the input
void print_invalid_input();			                  //print message - re-insert valid input
void print_full_board();		                      //print message - full board - no winner

void init_mat(char matrix[][N], int len, int* snake_p, int* snake_s);			  //initialize matrix with spaces and
void init_snakes(int* snake_p, int* snake_s, int len); // initializes the snakes arrays
void update_snake_to_matrix(char matrix[][N], int len, int* snake,
                            char body, char head);

void play_turns(char matrix[][N],int len, int* snake_p, int* snake_s,
                int twf, int food);
int make_move(char matrix[][N], int len, int* snake_p, int* snake_s,
              int turn);
void init_mat_and_snakes(char matrix[][N], int len,int* snake_p,
                         int* snake_s);
void update_snake_to_matrix(char matrix[][N], int len, int* snake,
                            char body, char head);
int input_and_check(int lowest, int highest);
int input_check_direction();
int input_and_put_food(char matrix[][N], int len);
bool check_food_coordinations(char matrix[][N], int len, int i, int j);
int move_snake(char matrix[][N], int len, int* snake, int direction,
               int turn);
int get_pos_from_direction(char matrix[][N], int len, int* snake,
                           int direction, int turn);
int get_snake_len(int* snake);
int power(int base, int x);
int arr_to_int(int* arr, int len);
void board_full(char matrix[][N], int len);
void update_b(char matrix[][N], int len, int* snake_p, int* snake_s,
              int food);
int eat(char matrix[][N], int len, int* lives,int turn, int twf);
void board_full(char matrix[][N], int len);
void decrease_life(int* lives, int turn);
void update_b(char matrix[][N], int len, int* snake_p, int* snake_s,
              int food);

// The program entry point
// Setts up the game properties such as matrix size and snakes starting points
// Calls play_turns function which handles the ingame  competition
int main()
{
    //initialization
    int size = 0, twf = 0, food = 0; // twf is turns without food
    char matrix[N][N];
    int snake_p[N * N], snake_s[N * N];//snake_p is the % player and snake_s is the @ player


    print_introduction_msg();

    print_board_size_msg();
    size = input_and_check(LOWER_ARR_SIZE, N);

    init_mat_and_snakes(matrix, size, snake_p, snake_s);

    print_steps_without_food();
    twf = input_and_check(LOWEST_TURNS_WITHOUT_FOOD, -1);


    food = input_and_put_food(matrix, size);

    //main turn start (perhaps use while loop in main, but preferable use the loop in the turn function)
    play_turns(matrix, size, snake_p, snake_s, twf, food);

    return 0;
}
// The turn handler function
// Input: board game matrix, the matrix length, two arrays for the snakes locations, amount of turns without food(twf), and food location
// The function handles the game with structure of turns
void play_turns(char matrix[][N],int len, int* snake_p, int* snake_s,
                int twf, int food)
{
    int turn = FIRST_PLAYER, eaten = 0, lives[2] = {twf, twf}; // lives[0] is life of % and life[1] is life of @
    while(true)
    {
        board_full(matrix, len);
        eaten = make_move(matrix, len, snake_p, snake_s , turn);
        update_b(matrix, len, snake_p, snake_s, food);
        //here we will check if eaten or not and will choose if to decrease life, and to remove
        if(eaten)
        {
           food = eat(matrix, len, lives, turn, twf);
        }
        else
        {
            decrease_life(lives, turn);
        }
        turn = !turn;
        update_b(matrix, len, snake_p, snake_s, food);
    }
}
// Input: array of lives of players, and the turn which represents the current player
// The function decreases the life the current player and if he runs out of turns since the-
// last time he ate, the function will end the game
void decrease_life(int* lives, int turn)
{
    lives[turn]--;
    if(lives[turn] <= 0)
    {
        //end game here
        print_finsih_msg(turn, !ILLEGAL_MOVE);
        exit(0);
    }
}
// Input: game board matrix, the matrix length
// The function will end the game if the board is full
void board_full(char matrix[][N], int len)
{
    for(int i = 0; i < len; i++)
    {
        for(int j =0; j < len; j++)
        {
            if(matrix[i][j] ==  ' ' || matrix[i][j] == FOOD_ELEMENT)
                return;
        }
    }
    print_board(matrix, len);
    print_full_board();
    exit(0);
}
// Input: game board matrix, matrix length, the array of players lives, and the turns allowed without food
// The function checks if the board is full and if so ends the game using the function board_full-
// otherwise, the function will refill the life of the current player to the turns without food amount set up in the start of the game.
// Then, the function will get the location for new food and will put it where it will be inputed
// Return Value: the function will return the location entered for the new food
int eat(char matrix[][N], int len, int* lives, int turn, int twf)
{
    int food = 0;
    board_full(matrix, len);
    lives[turn] = twf;
    food = input_and_put_food(matrix, len);
    matrix[food / N][food % N] = FOOD_ELEMENT;
    return food;
}
// Return Value: the function will recive a direction as an input and will check if it is a valid input-
// if not, it will ask again until a valid input is given. The function will end the program if an invalid type was entered-
// (charachter for instance)
int input_check_direction()
{
    int direct = 0;
    if(scanf("%d",&direct) != 1)
    {
        print_error_input();
        exit(-1);
    }
    while(direct != DOWN && direct != LEFT && direct != RIGHT &&
          direct != UP)
    {
        print_invalid_input();
        if(scanf("%d",&direct) != 1)
        {
            print_error_input();
            exit(-1);
        }
    }
    return direct;
}
// Input: game board matrix, the matrix length, two arrays of snakes locations and the current turn
// Return Value: the function will make the move of the snake and will return a value which represents if the snake moved has ate the food-
// -(by moving to the food coordinate on the board)
int make_move(char matrix[][N], int len, int* snake_p, int* snake_s,
              int turn)
{
    int direct = 0, eaten = 0;
    print_board(matrix, len);
    print_player_message(turn);
    print_insert_direction();
    direct = input_check_direction();
    eaten = move_snake(matrix, len, turn == PERCENT ? snake_p : snake_s,
                        direct, turn);
    return eaten;
}

//call each turn
//Input : recieves game board matrix and it's len, the two snakes arrays of snakes locations and food location
//Updates the game board of the locations of empty spaces, snakes and food
void update_b(char matrix[][N], int len, int* snake_p, int* snake_s,
               int food)
{
    for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++)
			matrix[i][j] = ' ';
	}
    //put food to matrix
    matrix[food / N][food % N] = FOOD_ELEMENT;
    //update the snakes into the matrix
    update_snake_to_matrix(matrix, get_snake_len(snake_p), snake_p,
                           P_BODY, P_HEAD);
    update_snake_to_matrix(matrix, get_snake_len(snake_s), snake_s,
                            S_BODY, S_HEAD);

}
// Input: game board matrix, the matrix length and the two snakes (by array of locations)
// The function will initialize the snake arrays and the matrix array
void init_mat_and_snakes(char matrix[][N], int len,int* snake_p,
                         int* snake_s)
{
    init_snakes(snake_p, snake_s, len);
    init_mat(matrix, len, snake_p, snake_s);
}




// Input: game matrix, matrix len and two snakes (by array of locations)
// The function initializes the matrix with spaces and puts the two snakes into the matrix
void init_mat(char matrix[][N], int len,int* snake_p,int* snake_s){
    //initialization of the matrix
    for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++)
			matrix[i][j] = ' ';
	}
    //update snakes to matrix
    update_snake_to_matrix(matrix, get_snake_len(snake_p), snake_p,
                            P_BODY, P_HEAD);

    update_snake_to_matrix(matrix, get_snake_len(snake_s), snake_s,
                            S_BODY, S_HEAD);

    //food update to matrix is in 'input and put food' function, so it is not required here
}
// Input: two int arrays, one for each snake and the len of the board
// The function initializes the array of the snakes with -1 which represents the end of the snake and then puts initial-
// values to the first three locations in the array
void init_snakes(int* snake_p, int* snake_s, int len){
	for(int i = 0; i < len; i++)
		for(int j = 0; j < len; j++){
			snake_p[i * len + j] = -1;
			snake_s[i * len + j] = -1;
		}
    for(int i = 0; i < SNAKE_START_SIZE; i++)
    {
        snake_p[i] = 0 * N + i;
        snake_s[i] = (len - 1) * N + i;
    }
}
// Input: game board matrix, the matrix length, an array of one of the snakes, the snake body charachter and the snake head charachter
// The function will put the snake to the matrix
void update_snake_to_matrix(char matrix[][N], int len, int* snake,
                             char body, char head)
{
    int index = 0;
     for(int i = 0; i < len; i++)
    {
        index = snake[i];
        matrix[index / N][index % N] = i ? body : head;
    }
}



//----------------------------------------FUNCTIONS BELOW DOES NOT HAVE SIGNATURE IN THE TOP OF THE FILE -------------
//this function gets input according to certain requirements and retruns a valid input
//input: lowest represents the lowest valid value, and highest is the highest valid value divider is by what we divide the input
//output: a valid input given
int input_and_check(int lowest, int highest)
{
    int input = 0;
    if(scanf("%d",&input) != 1)
    {
        print_error_input();
        exit(-1);
    }
    while(input < lowest || input > (highest >= 0 ? highest : input))
    {
        print_invalid_input();
        if(scanf("%d",&input) != 1)
        {
            print_error_input();
            exit(-1);
        }
    }
    return input;
}
//This fucntion gets food as input and checks it, and puts the valid input inside the matrix and returns it
int input_and_put_food(char matrix[][N], int len)
{
    print_food_location_msg();
    int i = 0, j = 0;
    if(scanf("%d %d", &i, &j) != 2)
    {
        print_error_input();
        exit(-1);
    }
    while(!check_food_coordinations(matrix, len, i, j))//could use input and check instead, but the new function is more clean
    {
        print_invalid_input();
        if(scanf("%d %d", &i, &j) != 2)
        {
            print_error_input();
            exit(-1);
        }
    }
    //puts the food into the valid coordinates in the matrix
    matrix[i][j] = FOOD_ELEMENT;
    return i * N + j;
}

// (used also for checking movement coordinates)
// Input: game board matrix, matrix length, i coordinate(row) and j coordinate(column)
// Return Value: will return wheather the location is an empty location on the game board
bool check_food_coordinations(char matrix[][N], int len, int i, int j)
{
    if(i < 0 || i >= len || j < 0 || j >= len)
        return false;
    else
        return matrix[i][j] == ' ' || matrix[i][j] == FOOD_ELEMENT;
}


// Input: game board matix, the matrix length, an array of one of the snake locations, direction to move to and the turn of the current player
// Return Value: the fucntion will move the snake to the direction given, and will return wheather the snake has eaten
int move_snake(char matrix[][N], int len, int* snake, int direction,
                int turn)
{
	int len_s = get_snake_len(snake), new_pos = 0, eaten = 0;
    new_pos = get_pos_from_direction(matrix, len, snake, direction, turn);

    eaten = matrix[new_pos / N][new_pos % N] == FOOD_ELEMENT;
	for(int i = eaten ? len_s : len_s - 1; i > 0; i--){
		snake[i] = snake[i-1];
	}
	snake[0] = new_pos;
    return eaten;
}
// Input: game board matix, the matrix length, an array of one of the snake locations, direction to move to and the turn of the current player
// Return Value: the function will calculate the coordinates of the snake after it's move(to the given direction) and will check wheather the-
// move is a valid move. the function will return the coordiantes of the snake after it moved
int get_pos_from_direction(char matrix[][N], int len, int* snake,
                            int direction, int turn)
{
    int i = snake[0] / 25, j = snake[0] % 25;
    i += direction == UP ? -1 : direction == DOWN ? 1 : 0;
    j += direction == LEFT ? -1 : direction == RIGHT ? 1 : 0;
    if(!check_food_coordinations(matrix, len, i, j))
    {
        print_finsih_msg(turn, ILLEGAL_MOVE);
        exit(-1);
    }
    return i * N + j ;
}


// Input: a snake represented by array of it's locations
// Return Value: the function will return the length of the snake (by reading it until the first -1 value)
int get_snake_len(int* snake)
{
	int len = 0;
	while(snake[len] != -1)
		len++;
	return len;

}



//----------------------------START OF THE GIVEN FUNCTIONS (NOT FOR ME TO CODE HERE)---------------------------------------
void print_introduction_msg()
{
    printf("Welcome to multi-snake  game, The game have 2 player Percent and Shtrodel.\n"
    "The game starts with PERCENT player.\n");
    printf("You have to choose 4 moves :Up,Down,Right and Left "
    "The Percent player is the snake that starts in (0,0)\n\n");
}

void print_board_size_msg(){
    printf("Insert board size between 4 and 25:\n");
}

void print_steps_without_food(){
    printf("Insert the maximum number of steps the snake can do without food:\n");
}

void print_food_location_msg(){
    printf("in order to continue the game please Insert a row then column numbers to place the next food: \n");
}

void help_print_board(int size)
{
    int i=0;
    printf("%c",BOARD_ELEMENT);
    for(i=0;i<size;i++)
    {
        printf("%c",BOARD_ELEMENT);
    }
    printf("%c\n",BOARD_ELEMENT);
}

void print_board(char board[N][N], int size)
{
    int i=0,j=0;
    help_print_board(size);
    for(i=0;i<size;i++)
    {
        printf("%c",BOARD_ELEMENT);
        for(j=0;j<size;j++)
        {
            printf("%c",board[i][j]);
        }
        printf("%c\n",BOARD_ELEMENT);
    }
    help_print_board(size);
    printf("\n\n");
}

void print_player_message(int player )
{
    printf("******* Turn of %c ***********\n",player==PERCENT?P_HEAD:S_HEAD);
}

void print_insert_direction(){
    printf("Enter the direction to move your snake: (2-down,4-left,6-right,8-up):\n");
}

void print_finsih_msg(int player ,int finish_reason)
{
    printf("\nThe game finish and the winner is:\n");
    printf("*** %s player ****.\n",player==PERCENT?"SHTRODEL":"PERCENT");
    printf("The reason is %s of the ",finish_reason==ILLEGAL_MOVE? "Illegal move" : "Snake die");
    printf("%s player.\n\n",player==PERCENT?"PERCENT":"SHTRODEL");
}

void print_invalid_input(){
    printf("Please re-Inset valid input:\n");
}

void print_full_board(){
    printf("Full Board. The game over with no Winner.\n");
}
void print_error_input(){
    printf("Error with the input.\n");
}
