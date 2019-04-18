#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_historiogram(int* arr, int len, char signal);
int get_max(int* arr, int len);
void print_winners(int max);
void print_w1(int winner);
void print_w2(int winner);
void print_w3(int winner);
void print_numbers();
int get_to_print(int* arr, int len, char signal);
void downgrade_array(int* arr, int len);

void print_welcome_message(){
	printf("Please enter a character:\n");
}

void print_welcome_message2(){
	printf("Please enter votes:\n");
}

void print_introduce_histogram(){
	printf("Histogram:\n");
}

void print_historiogram(int* arr, int len, char signal)
{
    int a, max = get_max(arr,len);;
    a = get_to_print(arr, len,signal);
    while(a){
        a = get_to_print(arr,len,signal);
    }

    print_numbers();
    print_winners(max);
}
int get_max(int* arr, int len){
    int max = 0, maxi = 0;
    for(int i=0;i<len;i++)
    {
        if(arr[i] > max){
            max = arr[i];
            maxi = i;
        }
    }
    return maxi + 1;
}
void print_winners(int max)
{
    print_w1(max);
    print_w2(max);
    print_w3(max);
}
void print_w1(int winner)
{
    switch(winner)
    {
    case 1:
        printf("Adi was elected!\n");
        break;
    case 2:
        printf("Alon was elected!\n");
        break;
    case 3:
        printf("Asaf was elected!\n");
        break;
    case 4:
        printf("Daniella was elected!\n");
        break;
    case 5:
        printf("Danielle was elected!\n");
        break;
    }
}
void print_w2(int winner)
{
    switch(winner)
    {
    case 6:
        printf("Dimitri was elected!\n");
        break;
    case 7:
        printf("Gasob was elected!\n");
        break;
     case 8:
        printf("Ido was elected!\n");
        break;
    case 9:
        printf("Najib was elected!\n");
        break;
    }
}
void print_w3(int winner)
{
     switch(winner)
    {
    case 10:
        printf("Nir was elected!\n");
        break;
    case 11:
        printf("Omer was elected!\n");
        break;
     case 12:
        printf("Yair was elected!\n");
        break;
    case 13:
        printf("Yaara was elected!\n");
        break;
    }
}
void print_numbers()
{
    for(int i = 0; i < 13 ; i++)
    {
        printf("%d ",i+1);
    }
    printf("\n");
}
void zero_arr(int* arr,int* a,int len)
{
    for(int i=0;i<len;i++)
    {
        if(a[i])
            arr[i]++;
        a[i] = 0;
    }
}
void print_spec(int len, int* a, char signal)
{
    for(int i = 0; i < len; i++)
        {
                if(a[i])
                    printf("%c ",signal);
                else
                    printf("  ");
                if(i >= 9)
                        printf(" ");
        }
        printf("\n");
}
int get_to_print(int* arr, int len, char signal)
{
    int a[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    int max = 0, flag = 0;
    for(int i = 0; i < len; i++)
    {
        if(arr[i] >= max){
            if(arr[i] > max){
                max = arr[i];
                zero_arr(arr,a,len);
            }
            a[i]=1;
            flag = arr[i] > 1;
            //here I have a problem with some
            arr[i]--;
        }
    }
    print_spec(len,a,signal);


    return flag;
}
void downgrade_array(int* arr, int len)
{
    for(int i=0;i<len;i++)
    {
        arr[i] -= arr[i] ? 1 : 0;
    }
}
int main()
{
    int arr[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0}, vote;
    char signal;
    print_welcome_message();
    scanf("%c",&signal);

    print_welcome_message2();
    while(scanf("%d",&vote)==1 && vote != -1)
    {
        arr[vote-1]++;
    }
    print_introduce_histogram();
    print_historiogram(arr,13,signal);
	return 0;
}






