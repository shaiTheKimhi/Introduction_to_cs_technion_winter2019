#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



int print_welcome_message(){
    return printf("La Inspectora Murillo, Please enter El Professor name:\n");
}

int printW(){
    return printf("\nEl Professor sent Walter White into the robbery!\n");
}

int printDa(){
    return printf("\nEl Professor sent Daenerys Targaryen into the robbery!\n");
}

int printDo(){
    return printf("\nEl Professor sent Doron Kabilio into the robbery!\n");
}

int printNo(){
    return printf("\nNO player has been sent into the robbery!\n");
}

int call_print(int daen, int doron, int walter, int sum, int amount)
{
    //makes doron true if
    doron = doron * ((int)(amount < 6) * (!daen));
    walter = ((int)(amount > 4) + (int)((sum/amount)%5)) * ((!daen) * (!doron)) ;
    amount = daen && printDa();
    amount = doron && printDo();
    amount = walter && printW();
    return (!doron && !walter & !daen) && printNo();
}

int main()
{
    int daen=1, doron = 1, walter = 0, amount = 1, sum = 0;
    char input, prevchar;//can use as integers and use the line above
    print_welcome_message();
    //gets the first character as input
    scanf("%c", &prevchar);
    //inputs characters until '!'
    while(scanf("%c",&input) == 1 && input != '!')
    {
        //conditions are made with * for 'all' statements over characters
        daen *= (int)(((int)input - prevchar) > 0);
        doron *= (int)(prevchar != 'r' && input != 'r');
        sum+=(int)prevchar;//does not sums the last character
        amount++;
        prevchar = input;
    }

    sum+=input;
    //walter has another condition with 'and' (*) and has daen to be false in order to be true
    call_print(daen, doron, walter, sum, amount);
	return 0;
}
