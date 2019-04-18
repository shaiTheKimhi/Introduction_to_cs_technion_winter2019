#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define N (100)
#define MAX_LEN (255)
#define MAX_SENTENCE_LEN ((MAX_LEN + 1) * N - 1)
#define WORD_SEPERATOR ('_')
#define SUCCESS (0)
#define ERROR (1)
#define TWO 2
#define FIRST_LETTER_CAPITAL 'A'
#define LAST_LETTER_CAPITAL 'Z'
#define FIRST_LETTER_NON_CAPITAL 'a'
#define UNDERSCORE '_'
#define END_STRING '\0'

//initializes char array to ""
void init_string(char* c_arr, int len)
{
    for(int i = 0; i < len; i++)
        c_arr[i] = '\0';
}
//This function will convert all charachters to certain value, while
//converting Capital letters to the same value given by the according non
//capital letters
int get_char_value(char c)
{
    if(c >= FIRST_LETTER_CAPITAL && c <= LAST_LETTER_CAPITAL)
        return c - FIRST_LETTER_CAPITAL;
    else
        return c - FIRST_LETTER_NON_CAPITAL;
}
//This function will compare strings non case-sensively
int compare_strings(char* str1, char* str2)
{
    int len1 = strlen(str1), len2 = strlen(str2), len = 0, val1, val2;
    len = len1 > len2 ? len2 : len1;
    for(int i = 0; i < len; i++)
    {
        val1 = get_char_value(str1[i]);
        val2 = get_char_value(str2[i]);
        if(val2 > val1)
            return val2 - val1;
        if(val1 > val2)
            return val2 - val1;
    }
    return len1-len2;
}

bool read_number_of_strings(int * n) {
    if (scanf("%d", n) != 1) {
        return false;
    }

    return ((*n >= 1) && (*n <= N));
}
//The function will free the dynamically allocated array of strings
void free_strings(char * strings[], int n) {
    for(int i = 0; i < n; i++)
    {
        free(strings[i]);
    }
}
//This function reads the strings for the array of censored words,
//Will return whether the function succeeded
bool read_strings(char * strings[], int n) {
    char str[MAX_LEN];
    int len = 0, valid = 1;
    for(int i = 0; i < n; i++)
    {
        valid = valid && scanf("%s", str);
        len = strlen(str) + 1;
        strings[i] = (char*)malloc(sizeof(char) * len);
        valid = valid && strings[i];
        for(int j = 0; j < len; j++)
        {
            strings[i][j] = str[j];
        }
    }
    return valid ;
}
//This function checks if the array is sorted or not
bool are_sorted(char * strings[], int n) {
    for(int i = 0; i < n - 1; i++)
    {
        if(compare_strings(strings[i], strings[i+1]) < 0)
        {
            return false;
        }
    }
    return true;
}
// This function checks the array a binary search in order to know if a
//certain word is in there
bool search_in_array(char* strings[], int n, char* string)
{
    int start = 0, end = n - 1 , mid = (start + end)/TWO, cmp = 0;
    while(end!=start)
    {
        cmp = compare_strings(strings[mid], string);
        if(cmp < 0)
        {
            end = mid;
            mid = (start + end)/TWO;
        }
        else if(cmp > 0)
        {
            start = mid;
            mid = (start + end + 1)/TWO;
        }
        else
        {
            return true;
        }

    }
    return false;
}
// This function checks whether the given word is in the array of censored
//words
bool is_string_in_array(char * strings[], int n, char * string) {
    return search_in_array(strings, n, string);
}
// Input: sentence, word and the sentence start index
// The function adds the word to the sentence starting from the starting
//index given
void put_word_to_sentence(char* sentence, char* word, int start_index)
{
    int len = strlen(word);
    for(int i = 0; i < len; i++)
    {
        sentence[start_index + i] = word[i];
    }
    //sentence[len] = '_';
}
// Input: words array , it's length, sentence, starting index, string
//and current charachter index in the sentence
// This function checks if the word is not in the given censored word array
//and if it is not there, it will call the put_word_to_sentence function
//and will put the word to the sentence
void handle_check_word(char* words[], int n, char* sentence, int* index,
                        char* str, int i)
{
    if(!is_string_in_array(words, n, str))
    {
        *(index) += strlen(str);
        put_word_to_sentence(sentence, str, *(index) - strlen(str));
        if((unsigned)i != strlen(sentence)){
            sentence[*(index)] = sentence[i];
            *(index) += 1;
        }
    }
    init_string(str, MAX_LEN);
}
//removes the last character if it is underscore and keeps it otherwise
void remove_last_underscore(char* sentence)
{
    if(sentence[strlen(sentence) - 1] == '_' &&
    sentence[strlen(sentence) - 2] != '_')
        sentence[strlen(sentence) - 1] = '\0';
}
void delete_words(char * words[], int n, char * sentence) {
    int len = strlen(sentence), iteration = 0, index = 0;
    char str[MAX_LEN];///, *new_str = (char*)malloc(1*strlen(sentence));
    init_string(str, MAX_LEN);
    for(int i = 0; i < len; i++)
    {
        if(sentence[i] == '_')
        {
            handle_check_word(words, n, sentence, &index, str, i);

            iteration = 0;
        }
        else
        {
            str[iteration++] = sentence[i];
        }
    }
    handle_check_word(words, n, sentence, &index, str, len);
    sentence[index] = '\0';
    remove_last_underscore(sentence);
    ///free(sentence);
    ///sentence = new_str;
    //WRITE THE CODE HERE
}

int main() {
    int n;
    printf("Enter number of banned words: ");
    if (!read_number_of_strings(&n)) {
        printf("Invalid number!\n");
        return ERROR;
    }

    char * banned_words[N];
    printf("Enter banned words: ");
    if (!read_strings(banned_words, n)) {
        printf("Can't read words!\n");
        return ERROR;
    }

    if (!are_sorted(banned_words, n)) {
        printf("Words are not sorted correctly!\n");
        free_strings(banned_words, n);
        return ERROR;
    }

    char sentence[MAX_SENTENCE_LEN + 1];
    printf("Enter a sentence:\n");
    if (scanf("%s", sentence) != 1) {
        printf("Invalid sentence!\n");
        free_strings(banned_words, n);
        return ERROR;
    }

    delete_words(banned_words, n, sentence);
    printf("Censored sentence:\n%s\n", sentence);

    free_strings(banned_words, n);
    return SUCCESS;
}
