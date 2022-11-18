#include "helper_functions.h"

int main()
{
    unsigned int inputNum;
    int rotate;
    printf("Please give your number: \n");
    scanf("%u", &inputNum);
    printf("Please give your rotation: \n");
    scanf("%d", &rotate);
    printf("\n");
    my_rottate(inputNum, rotate);
    return 0;
}