/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



int main()
{
    int height = 0;
    int bSum = 0, bAmount = 0, gSum = 0, gAmount = 0;
    printf("Students, please enter heights!\n");
    while(scanf("%d",&height)== 1)
    {
        if(height==0)
        {
            printf("Error! Invalid height 0!\n");
            return -1;
        }
        else if(height > 0)
        {
            gAmount++;
            gSum += height;
        }
        else if(height < 0)
        {
            bAmount++;
            bSum += height;
        }
    }
    if(gAmount)
        printf("Average girls height is: %.2f\n",(float)gSum/gAmount);
    else
        printf("No girls in class! :(");
    if(bAmount)
        printf("Average boys height is: %.2f\n",(float)-bSum/bAmount);
    else
        printf("No boys in class! :(\n");
    return 0;
}
