#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_welcome_message1(){
	printf("Starting the AES Algorithm, please pick amount of iterations:\n");
}

void print_invalid_amount(){
	printf("Invalid amount of iterations!\n");
	printf("Please try again:\n");
}

void print_welcome_message2(){
	printf("Please pick a matrix size:\n");
}

void print_enter_matrix(){
	printf("Please enter the matrix:\n");
}

void print_encrypted_message(){
	printf("The encrypted message is:\n");
}

void print_matrix(int n, int aes[n][n]){
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", aes[i][j]);
		}
		printf("\n");
	}
}

int sbox[256] = { 99, 124, 119, 123, 242, 107, 111, 197, 48, 1, 103, 43, 254,
		215, 171, 118, 202, 130, 201, 125, 250, 89, 71, 240, 173, 212, 162, 175,
		156, 164, 114, 192, 183, 253, 147, 38, 54, 63, 247, 204, 52, 165, 229,
		241, 113, 216, 49, 21, 4, 199, 35, 195, 24, 150, 5, 154, 7, 18, 128,
		226, 235, 39, 178, 117, 9, 131, 44, 26, 27, 110, 90, 160, 82, 59, 214,
		179, 41, 227, 47, 132, 83, 209, 0, 237, 32, 252, 177, 91, 106, 203, 190,
		57, 74, 76, 88, 207, 208, 239, 170, 251, 67, 77, 51, 133, 69, 249, 2,
		127, 80, 60, 159, 168, 81, 163, 64, 143, 146, 157, 56, 245, 188, 182,
		218, 33, 16, 255, 243, 210, 205, 12, 19, 236, 95, 151, 68, 23, 196, 167,
		126, 61, 100, 93, 25, 115, 96, 129, 79, 220, 34, 42, 144, 136, 70, 238,
		184, 20, 222, 94, 11, 219, 224, 50, 58, 10, 73, 6, 36, 92, 194, 211,
		172, 98, 145, 149, 228, 121, 231, 200, 55, 109, 141, 213, 78, 169, 108,
		86, 244, 234, 101, 122, 174, 8, 186, 120, 37, 46, 28, 166, 180, 198,
		232, 221, 116, 31, 75, 189, 139, 138, 112, 62, 181, 102, 72, 3, 246, 14,
		97, 53, 87, 185, 134, 193, 29, 158, 225, 248, 152, 17, 105, 217, 142,
		148, 155, 30, 135, 233, 206, 85, 40, 223, 140, 161, 137, 13, 191, 230,
		66, 104, 65, 153, 45, 15, 176, 84, 187, 22 };

void bytes_substitution(int len, int arr[][len])
{
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            //substitute element i,j on matrix with element [Matrix]i,j on Sbox
            arr[i][j] = sbox[arr[i][j]];
        }
    }
}

void rows_shift(int len, int arr[][len])
{
    int temp[len], index;
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            //get the index of the element in the new array
            index = j - i + len*(j - i < 0);
            //sets the new array
            temp[index] = arr[i][j];
        }
        //copies the temporary array to the matrix
        for(int j =0; j < len; j++)
            arr[i][j] = temp[j];
    }
}

void handle_matrix(int len, int arr[][len], int iterations)
{
    for(int i = 0; i < iterations; i++)
    {
        bytes_substitution(len, arr);
        rows_shift(len,arr);
    }

    print_encrypted_message();
    print_matrix(len, arr);
}

void input_matrix(int size, int arr[][size])
{
    print_enter_matrix();
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
}

int main()
{
    int matrix[16][16];
    int iterations = 0, size = 0 ;
    print_welcome_message1();
    while(scanf("%d",&iterations), iterations < 0)
        print_invalid_amount();
    print_welcome_message2();
    scanf("%d", &size);
    //matrix = (int*)malloc(sizeof(int) * size * size);
    input_matrix(size, matrix);

    handle_matrix(size, (int(*)[size])matrix, iterations);
	return 0;
}
