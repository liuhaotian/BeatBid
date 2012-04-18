#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define SAFESCAN(f,...) if (f == 0) { printf(__VA_ARGS__); exit(1);}
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )

#define MAXBUFF 300

typedef struct act_t
{
    char Name[20];
    long long int Labor;
    long long int Material;
    long long int Subcontractor;
    long long int Days;

    long long int finishDay;
    long long int activCost;
} act_t;

typedef struct method_t
{
    act_t Activities[9];
} method_t;

void PrintMethod(method_t* method, int numMethod){
    int i, j;
    method_t* tempmethod;
    for (i = 0; i < numMethod; ++i)
    {
        printf("\nMethod #%d\n", i + 1);
        tempmethod = method + i;
        for (j = 0; j < 9; ++j)
        {
            printf("%s\t", (method + i)->Activities[j].Name);
            printf("%lld\t", (method + i)->Activities[j].Labor);
            printf("%lld\t", (method + i)->Activities[j].Material);
            printf("%lld\t", (method + i)->Activities[j].Subcontractor);
            printf("%lld\n", (method + i)->Activities[j].Days);
        }
    }
}

long long int RoundUp(float in){
    
}

long long int DirectCost(method_t* method){
    long long int ret = 0;
    int days, i = 0;;
    int rely[9][2], ratio[9][2];
    //memset(rely, 0, 18);
    rely[0][0] = 0;
    rely[1][0] = 0;
    rely[2][0] = 1;
    rely[3][0] = 1;
    rely[4][0] = 3;
    rely[5][0] = 3;
    rely[6][0] = 4;
    rely[7][0] = 6;
    rely[8][0] = 0;
    rely[0][1] = 0;
    rely[1][1] = 0;
    rely[2][1] = 1;
    rely[3][1] = 1;
    rely[4][1] = 3;
    rely[5][1] = 3;
    rely[6][1] = 4;
    rely[7][1] = 6;
    rely[8][1] = 4;

    ratio[0][0] = 0;
    ratio[0][1] = 0;
    ratio[1][0] = 0.7;
    ratio[1][1] = 0;
    ratio[2][0] = 0.5;
    ratio[2][1] = 0.7;
    ratio[3][0] = 0.3;
    ratio[3][1] = 0.4;
    ratio[4][0] = 0.5;
    ratio[4][1] = 0.3;
    ratio[5][0] = 0.4;
    ratio[5][1] = 0.5;
    ratio[6][0] = 0.4;
    ratio[6][1] = 0.6;
    ratio[7][0] = 0.3;
    ratio[7][1] = 0.6;
    ratio[8][0] = 0.7;
    ratio[8][1] = 0.4;
    /*
    1 0 0
    2 0.7 0
    3 0.5 0.7
    4 0.3 0.4
    5 0.5 0.3
    6 0.4 0.5
    7 0.4 0.6
    8 0.3 0.6
    9 0.7 0.4



    */

    //Excavation 0
    days = method->Activities[0].Days;
    method->Activities[i].finishDay = days;printf("%lld\n", method->Activities[i].finishDay);
    i++;

    //Foundation 1
    days = RoundUp(0.7 * method->Activities[rely[i][0]].Days + method->Activities[i].Days);
    method->Activities[i].finishDay = days;printf("%lld\n", method->Activities[i].finishDay);
    i++;

    //Basement 2
    days = RoundUp(max( days - (1 - ratio[i][0]) * method->Activities[rely[i][0]].Days + method->Activities[i].Days, 
                            (1 - ratio[i][1]) * method->Activities[i].Days + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;printf("%lld\n", method->Activities[i].finishDay);
    i++;

    //Framing 3
    days = RoundUp(max( days - (1 - ratio[i][0]) * method->Activities[rely[i][0]].Days + method->Activities[i].Days, 
                            (1 - ratio[i][1]) * method->Activities[i].Days + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;printf("%lld\n", method->Activities[i].finishDay);
    i++;

    //Closure 4
    days = RoundUp(max( days - (1 - ratio[i][0]) * method->Activities[rely[i][0]].Days + method->Activities[i].Days, 
                            (1 - ratio[i][1]) * method->Activities[i].Days + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;printf("%lld\n", method->Activities[i].finishDay);
    i++;

    //Roof 5
    days = RoundUp(max( days - (1 - ratio[i][0]) * method->Activities[rely[i][0]].Days + method->Activities[i].Days, 
                            (1 - ratio[i][1]) * method->Activities[i].Days + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;printf("%lld\n", method->Activities[i].finishDay);
    i++;

    //Siding 6
    days = RoundUp(max( days - (1 - ratio[i][0]) * method->Activities[rely[i][0]].Days + method->Activities[i].Days, 
                            (1 - ratio[i][1]) * method->Activities[i].Days + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;printf("%lld\n", method->Activities[i].finishDay);
    i++;

    //Finishing 7
    days = RoundUp(max( days - (1 - ratio[i][0]) * method->Activities[rely[i][0]].Days + method->Activities[i].Days, 
                            (1 - ratio[i][1]) * method->Activities[i].Days + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;printf("%lld\n", method->Activities[i].finishDay);
    i++;

    //Mechanical &Elctrical 8
    days = RoundUp(max( days - (1 - ratio[i][0]) * method->Activities[rely[i][0]].Days + method->Activities[i].Days, 
                            (1 - ratio[i][1]) * method->Activities[i].Days + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;printf("%lld\n", method->Activities[i].finishDay);
    i++;

    days = max(method->Activities[8].finishDay, method->Activities[7].finishDay);

    for (i = 0; i < 9; ++i)
    {
        ret += method->Activities[7].Labor;
        ret += method->Activities[7].Material;
        ret += method->Activities[7].Subcontractor;
    }

    return ret;
}

int main(int argc, char const *argv[])
{
    FILE * fin = fopen("orginaldata", "r");
    FILE * fout = fopen("output.out", "w");

    int i, j;

    int penalty;
    SAFESCAN(fscanf(fin, "Penalty: $%d\n", &penalty), "Penalty Format Error\n")

    int numMethod;
    SAFESCAN(fscanf(fin, "NumMethod: %d\n", &numMethod), "NumMethod Format Error\n")

    method_t* Method;
    Method = calloc(numMethod, sizeof(method_t));
    char name[20];

    for (i = 0; i < 9; ++i)
    {
        SAFESCAN(fscanf(fin, "%s", name), "Activities Name Error\n")
        for (j = 0; j < numMethod; ++j)
        {
            strcpy((Method + j)->Activities[i].Name, name);
            SAFESCAN(fscanf(fin, "\t%lld", &(Method + j)->Activities[i].Labor),         "Activities.Labor Format Error\n")
            SAFESCAN(fscanf(fin, "\t%lld", &(Method + j)->Activities[i].Material),      "Activities.Labor Format Error\n")
            SAFESCAN(fscanf(fin, "\t%lld", &(Method + j)->Activities[i].Subcontractor), "Activities.Labor Format Error\n")
            SAFESCAN(fscanf(fin, "\t%lld", &(Method + j)->Activities[i].Days),          "Activities.Labor Format Error\n")
        }
    }

    PrintMethod(Method, numMethod);
    printf("%lld\n", DirectCost(Method + 4));
    printf("%lld\n", RoundUp(1.1));

    free(Method);
    fclose(fin);
    fclose(fout);


    return 0;
}