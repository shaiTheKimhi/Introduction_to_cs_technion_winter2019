/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int shift=0;
    char input;
    printf("Please enter shift number:\n");
    scanf("%d",&shift);
    printf("Please enter text to encrypt:\n");
    while(scanf("%c",&input) == 1)
    {
        if(input >= 'a' && input <= 'z')
            printf("%c",(char)((input - 'a' + shift)%26 + 'a'));
        else if(input >= 'A' && input <= 'Z')
            printf("%c",(char)((input - 'A' + shift)%26 + 'A'));
        else
            printf("%c",input);
    }
    return 0;
}
