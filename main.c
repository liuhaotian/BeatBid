#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

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

    int penalty;
    int requireDay;
    int targetMinDay, targetMaxDay;
    int numMethod;
    method_t* Method;
    FILE * fin;
    FILE * fout;
    int rely[9][2];
    float ratio[9][2];

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

            printf("%lld\n", (method + i)->Activities[j].finishDay);
        }
    }
}

long long int RoundUp(double in){
    return (long long int)ceil(in);
}

long long int DirectCost(method_t* method){
    long long int ret = 0;
    long long int days, i = 0;
    //int rely[9][2];
    //float ratio[9][2];
    method->Activities[0].finishDay = method->Activities[0].Days;
    //memset(rely, 0, 18);
    /*
    rely[0][0] = 0;
    rely[1][0] = 0;
    rely[2][0] = 1;
    rely[3][0] = 1;
    rely[4][0] = 3;
    rely[5][0] = 4;
    rely[6][0] = 4;
    rely[7][0] = 6;
    rely[8][0] = 0;
    rely[0][1] = 0;
    rely[1][1] = 1;
    rely[2][1] = 1;
    rely[3][1] = 1;
    rely[4][1] = 3;
    rely[5][1] = 4;
    rely[6][1] = 4;
    rely[7][1] = 6;
    rely[8][1] = 4;

    ratio[0][0] = 0;
    ratio[0][1] = 1;
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
    */
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

    //for the beginning:
    //Work may not start on Excavation until work on itself is 0% complete.
    //Work on Excavation may not proceed past 100% until work on itself is 100% complete.

    // if the last network lacks the second constrain, we set the second rely to the same, ratio to 1
    // so it looks like:
    //Work may not start on Mechanical & Electrical until work on Excavation is 70% complete.
    //Work on Mechanical & Electrical may not proceed past 1000000% until work on Siding is 100% complete.
    // a kind of work around
    // the same as any network constrain, for example in this project, for Foundation
    // it lacks the second constrain
    // with the help of workaround, it may look like this:
    //Work on Foundation may not proceed past 1000000% until work on Excavation is 100% complete.

    // so, the max() looks like max(var, foo), which foo is a negative value, so that it will always return
    // the first var

    */




    
    //Excavation 0
    days = RoundUp(max( method->Activities[rely[i][0]].finishDay + RoundUp((-1 + ratio[i][0]) * method->Activities[rely[i][0]].Days) + method->Activities[i].Days, 
                            RoundUp((1 - ratio[i][1]) * method->Activities[i].Days) + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;
    i++;

    //Foundation 1
    days = RoundUp(max( method->Activities[rely[i][0]].finishDay + RoundUp((-1 + ratio[i][0]) * method->Activities[rely[i][0]].Days) + method->Activities[i].Days, 
                            RoundUp((1 - ratio[i][1]) * method->Activities[i].Days) + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;
    i++;

    //Basement 2
    days = RoundUp(max( method->Activities[rely[i][0]].finishDay + RoundUp((-1 + ratio[i][0]) * method->Activities[rely[i][0]].Days) + method->Activities[i].Days, 
                            RoundUp((1 - ratio[i][1]) * method->Activities[i].Days) + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;
    i++;

    //Framing 3
    days = RoundUp(max( method->Activities[rely[i][0]].finishDay + RoundUp((-1 + ratio[i][0]) * method->Activities[rely[i][0]].Days) + method->Activities[i].Days, 
                            RoundUp((1 - ratio[i][1]) * method->Activities[i].Days) + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;
    i++;

    //Closure 4
    days = RoundUp(max( method->Activities[rely[i][0]].finishDay + RoundUp((-1 + ratio[i][0]) * method->Activities[rely[i][0]].Days) + method->Activities[i].Days, 
                            RoundUp((1 - ratio[i][1]) * method->Activities[i].Days) + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;
    i++;

    //Roof 5
    days = RoundUp(max( method->Activities[rely[i][0]].finishDay + RoundUp((-1 + ratio[i][0]) * method->Activities[rely[i][0]].Days) + method->Activities[i].Days, 
                            RoundUp((1 - ratio[i][1]) * method->Activities[i].Days) + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;
    i++;

    //Siding 6
    days = RoundUp(max( method->Activities[rely[i][0]].finishDay + RoundUp((-1 + ratio[i][0]) * method->Activities[rely[i][0]].Days) + method->Activities[i].Days, 
                            RoundUp((1 - ratio[i][1]) * method->Activities[i].Days) + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;
    i++;

    //Finishing 7
    days = RoundUp(max( method->Activities[rely[i][0]].finishDay + RoundUp((-1 + ratio[i][0]) * method->Activities[rely[i][0]].Days) + method->Activities[i].Days, 
                            RoundUp((1 - ratio[i][1]) * method->Activities[i].Days) + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;
    i++;

    //Mechanical &Elctrical 8
    days = RoundUp(max( method->Activities[rely[i][0]].finishDay + RoundUp((-1 + ratio[i][0]) * method->Activities[rely[i][0]].Days) + method->Activities[i].Days, 
                            RoundUp((1 - ratio[i][1]) * method->Activities[i].Days) + method->Activities[rely[i][1]].finishDay));
    method->Activities[i].finishDay = days;
    i++;

    days = max(method->Activities[8].finishDay, method->Activities[7].finishDay);
    
    for (i = 0; i < 9; ++i)
    {
        ret += method->Activities[i].Labor;
        ret += method->Activities[i].Material;
        ret += method->Activities[i].Subcontractor;
    }

    return ret;
}

long long int FinishDay(method_t* method){
    long long int ret = 0;
    int i;
    for (i = 0; i < 9; ++i)
    {
        ret = max(method->Activities[i].finishDay, ret);
    }
    return ret;
}

void* bidding(void* threadid){
    long tid = (long)threadid;
    int i, j, k, l, m, n, o, p, q;
    method_t tempmethod;
    long long int minCost = 1e12, tempCost = 0;
    int minArray[9];
    memset(minArray, 0, 9);
    long long int targetDay = 0, tempDay;
    for (targetDay = targetMinDay + tid; targetDay < targetMaxDay; targetDay += 8)
    {
        for (i = 0; i < 5; ++i)
        {
            for (j = 0; j < 5; ++j)
            {
                for (k = 0; k < 5; ++k)
                {
                    for (l = 0; l < 5; ++l)
                    {
                        for (m = 0; m < 5; ++m)
                        {
                            for (n = 0; n < 5; ++n)
                            {
                                for (o = 0; o < 5; ++o)
                                {
                                    for (p = 0; p < 5; ++p)
                                    {
                                        for (q = 0; q < 5; ++q)
                                        {
                                            tempmethod.Activities[0].Labor = (Method + i)->Activities[0].Labor;
                                            tempmethod.Activities[0].Material = (Method + i)->Activities[0].Material;
                                            tempmethod.Activities[0].Subcontractor = (Method + i)->Activities[0].Subcontractor;
                                            tempmethod.Activities[0].Days = (Method + i)->Activities[0].Days;
                                            tempmethod.Activities[0].finishDay = 0;

                                            tempmethod.Activities[1].Labor = (Method + j)->Activities[1].Labor;
                                            tempmethod.Activities[1].Material = (Method + j)->Activities[1].Material;
                                            tempmethod.Activities[1].Subcontractor = (Method + j)->Activities[1].Subcontractor;
                                            tempmethod.Activities[1].Days = (Method + j)->Activities[1].Days;
                                            tempmethod.Activities[1].finishDay = 0;

                                            tempmethod.Activities[2].Labor = (Method + k)->Activities[2].Labor;
                                            tempmethod.Activities[2].Material = (Method + k)->Activities[2].Material;
                                            tempmethod.Activities[2].Subcontractor = (Method + k)->Activities[2].Subcontractor;
                                            tempmethod.Activities[2].Days = (Method + k)->Activities[2].Days;
                                            tempmethod.Activities[2].finishDay = 0;

                                            tempmethod.Activities[3].Labor = (Method + l)->Activities[3].Labor;
                                            tempmethod.Activities[3].Material = (Method + l)->Activities[3].Material;
                                            tempmethod.Activities[3].Subcontractor = (Method + l)->Activities[3].Subcontractor;
                                            tempmethod.Activities[3].Days = (Method + l)->Activities[3].Days;
                                            tempmethod.Activities[3].finishDay = 0;

                                            tempmethod.Activities[4].Labor = (Method + m)->Activities[4].Labor;
                                            tempmethod.Activities[4].Material = (Method + m)->Activities[4].Material;
                                            tempmethod.Activities[4].Subcontractor = (Method + m)->Activities[4].Subcontractor;
                                            tempmethod.Activities[4].Days = (Method + m)->Activities[4].Days;
                                            tempmethod.Activities[4].finishDay = 0;

                                            tempmethod.Activities[5].Labor = (Method + n)->Activities[5].Labor;
                                            tempmethod.Activities[5].Material = (Method + n)->Activities[5].Material;
                                            tempmethod.Activities[5].Subcontractor = (Method + n)->Activities[5].Subcontractor;
                                            tempmethod.Activities[5].Days = (Method + n)->Activities[5].Days;
                                            tempmethod.Activities[5].finishDay = 0;

                                            tempmethod.Activities[6].Labor = (Method + o)->Activities[6].Labor;
                                            tempmethod.Activities[6].Material = (Method + o)->Activities[6].Material;
                                            tempmethod.Activities[6].Subcontractor = (Method + o)->Activities[6].Subcontractor;
                                            tempmethod.Activities[6].Days = (Method + o)->Activities[6].Days;
                                            tempmethod.Activities[6].finishDay = 0;

                                            tempmethod.Activities[7].Labor = (Method + p)->Activities[7].Labor;
                                            tempmethod.Activities[7].Material = (Method + p)->Activities[7].Material;
                                            tempmethod.Activities[7].Subcontractor = (Method + p)->Activities[7].Subcontractor;
                                            tempmethod.Activities[7].Days = (Method + p)->Activities[7].Days;
                                            tempmethod.Activities[7].finishDay = 0;

                                            tempmethod.Activities[8].Labor = (Method + q)->Activities[8].Labor;
                                            tempmethod.Activities[8].Material = (Method + q)->Activities[8].Material;
                                            tempmethod.Activities[8].Subcontractor = (Method + q)->Activities[8].Subcontractor;
                                            tempmethod.Activities[8].Days = (Method + q)->Activities[8].Days;
                                            tempmethod.Activities[8].finishDay = 0;

                                            //minCost = min(DirectCost(&tempmethod), minCost);
                                            tempCost = DirectCost(&tempmethod);
                                            tempDay = FinishDay(&tempmethod);

                                            if (tempDay <= targetDay)
                                            {
                                                if (tempDay > requireDay)
                                                {
                                                    tempCost += (tempDay - requireDay) * penalty;
                                                }
                                                minCost = min(tempCost, minCost);
                                                if (minCost == tempCost)
                                                {
                                                    minArray[0] = i;
                                                    minArray[1] = j;
                                                    minArray[2] = k;
                                                    minArray[3] = l;
                                                    minArray[4] = m;
                                                    minArray[5] = n;
                                                    minArray[6] = o;
                                                    minArray[7] = p;
                                                    minArray[8] = q;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        //DirectCost(&tempmethod);
        //PrintMethod(&tempmethod, 1);
        //printf("%lld\n", tempmethod.Activities[2].finishDay);
        fprintf (fout, "%lld\t%lld\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
                        targetDay, minCost,
                            minArray[0] + 1, minArray[1] + 1, minArray[2] + 1, minArray[3] + 1, 
                                minArray[4] + 1, minArray[5] + 1, minArray[6] + 1, minArray[7] + 1, minArray[8] + 1);
    }
}

int main(int argc, char const *argv[])
{
    fin = fopen("orginaldata", "r");
    fout = fopen("output.out", "w");

    int i, j, k, l, m, n, o, p, q;

    SAFESCAN(fscanf(fin, "Penalty: $%d\n", &penalty), "Penalty Format Error\n")

    SAFESCAN(fscanf(fin, "Required days: %d\n", &requireDay), "Required days Format Error\n")

    SAFESCAN(fscanf(fin, "Target day: %d %d\n", &targetMinDay, &targetMaxDay), "Target day Format Error\n")

    for (i = 0; i < 9; ++i)
    {
        SAFESCAN(fscanf(fin, "%d\t%d\t%d\t%f%%\t%f%%\n", &j, &rely[i][0], &rely[i][1], &ratio[i][0], &ratio[i][1]), 
                                "Ratio and rely Format Error\n")
        rely[i][0]--;
        rely[i][1]--;

        ratio[i][0] /= 100;
        ratio[i][1] /= 100;
    }

    //SAFESCAN(fscanf(fin, "Target day: %d %d\n", &targetMinDay, &targetMaxDay), "Target day Format Error\n")

    SAFESCAN(fscanf(fin, "NumMethod: %d\n", &numMethod), "NumMethod Format Error\n")

    Method = calloc(numMethod, sizeof(method_t));
    char name[20];

    for (i = 0; i < 9; ++i)
    {
        SAFESCAN(fscanf(fin, "%s", name), "Activities Name Error\n")
        for (j = 0; j < numMethod; ++j)
        {
            strcpy((Method + j)->Activities[i].Name, name);
            SAFESCAN(fscanf(fin, "\t%lld", &(Method + j)->Activities[i].Labor),         "Activities.Labor Format Error\n")
            SAFESCAN(fscanf(fin, "\t%lld", &(Method + j)->Activities[i].Material),      "Activities.Material Format Error\n")
            SAFESCAN(fscanf(fin, "\t%lld", &(Method + j)->Activities[i].Subcontractor), "Activities.Subcontractor Format Error\n")
            SAFESCAN(fscanf(fin, "\t%lld", &(Method + j)->Activities[i].Days),          "Activities.Days Format Error\n")
        }
    }

    //PrintMethod(Method, numMethod);
    //DirectCost(Method + 4);
    //PrintMethod(Method + 4, 1);
    /*
    printf("%lld\n", DirectCost(Method + 4));
    for (i = 0; i < 9; ++i)
    {
        printf("%lld\n", (Method + 4)->Activities[i].finishDay);
    }
    */
    pthread_t threads[8];
    int rc;
    long iterator;
    for (iterator = 0; iterator < 8; ++iterator)
    {
        rc = pthread_create(&threads[i], NULL, bidding, (void*)iterator);
    }
    pthread_exit(NULL);
    /*
    method_t tempmethod;
    long long int minCost = 1e12, tempCost;
    int minArray[9];
    memset(minArray, 0, 9);
    int targetDay = 0, tempDay;
    for (targetDay = targetMinDay; targetDay < targetMaxDay; ++targetDay)
    {
        for (i = 0; i < 5; ++i)
        {
            for (j = 0; j < 5; ++j)
            {
                for (k = 0; k < 5; ++k)
                {
                    for (l = 0; l < 5; ++l)
                    {
                        for (m = 0; m < 5; ++m)
                        {
                            for (n = 0; n < 5; ++n)
                            {
                                for (o = 0; o < 5; ++o)
                                {
                                    for (p = 0; p < 5; ++p)
                                    {
                                        for (q = 0; q < 5; ++q)
                                        {
                                            tempmethod.Activities[0].Labor = (Method + i)->Activities[0].Labor;
                                            tempmethod.Activities[0].Material = (Method + i)->Activities[0].Material;
                                            tempmethod.Activities[0].Subcontractor = (Method + i)->Activities[0].Subcontractor;
                                            tempmethod.Activities[0].Days = (Method + i)->Activities[0].Days;

                                            tempmethod.Activities[1].Labor = (Method + j)->Activities[1].Labor;
                                            tempmethod.Activities[1].Material = (Method + j)->Activities[1].Material;
                                            tempmethod.Activities[1].Subcontractor = (Method + j)->Activities[1].Subcontractor;
                                            tempmethod.Activities[1].Days = (Method + j)->Activities[1].Days;

                                            tempmethod.Activities[2].Labor = (Method + k)->Activities[2].Labor;
                                            tempmethod.Activities[2].Material = (Method + k)->Activities[2].Material;
                                            tempmethod.Activities[2].Subcontractor = (Method + k)->Activities[2].Subcontractor;
                                            tempmethod.Activities[2].Days = (Method + k)->Activities[2].Days;

                                            tempmethod.Activities[3].Labor = (Method + l)->Activities[3].Labor;
                                            tempmethod.Activities[3].Material = (Method + l)->Activities[3].Material;
                                            tempmethod.Activities[3].Subcontractor = (Method + l)->Activities[3].Subcontractor;
                                            tempmethod.Activities[3].Days = (Method + l)->Activities[3].Days;

                                            tempmethod.Activities[4].Labor = (Method + m)->Activities[4].Labor;
                                            tempmethod.Activities[4].Material = (Method + m)->Activities[4].Material;
                                            tempmethod.Activities[4].Subcontractor = (Method + m)->Activities[4].Subcontractor;
                                            tempmethod.Activities[4].Days = (Method + m)->Activities[4].Days;

                                            tempmethod.Activities[5].Labor = (Method + n)->Activities[5].Labor;
                                            tempmethod.Activities[5].Material = (Method + n)->Activities[5].Material;
                                            tempmethod.Activities[5].Subcontractor = (Method + n)->Activities[5].Subcontractor;
                                            tempmethod.Activities[5].Days = (Method + n)->Activities[5].Days;

                                            tempmethod.Activities[6].Labor = (Method + o)->Activities[6].Labor;
                                            tempmethod.Activities[6].Material = (Method + o)->Activities[6].Material;
                                            tempmethod.Activities[6].Subcontractor = (Method + o)->Activities[6].Subcontractor;
                                            tempmethod.Activities[6].Days = (Method + o)->Activities[6].Days;

                                            tempmethod.Activities[7].Labor = (Method + p)->Activities[7].Labor;
                                            tempmethod.Activities[7].Material = (Method + p)->Activities[7].Material;
                                            tempmethod.Activities[7].Subcontractor = (Method + p)->Activities[7].Subcontractor;
                                            tempmethod.Activities[7].Days = (Method + p)->Activities[7].Days;

                                            tempmethod.Activities[8].Labor = (Method + q)->Activities[8].Labor;
                                            tempmethod.Activities[8].Material = (Method + q)->Activities[8].Material;
                                            tempmethod.Activities[8].Subcontractor = (Method + q)->Activities[8].Subcontractor;
                                            tempmethod.Activities[8].Days = (Method + q)->Activities[8].Days;

                                            //minCost = min(DirectCost(&tempmethod), minCost);
                                            tempCost = DirectCost(&tempmethod);
                                            tempDay = FinishDay(&tempmethod);

                                            if (tempDay <= targetDay)
                                            {
                                                if (tempDay > requireDay)
                                                {
                                                    tempCost += (tempDay - requireDay) * penalty;
                                                }
                                                minCost = min(tempCost, minCost);
                                                if (minCost == tempCost)
                                                {
                                                    minArray[0] = i;
                                                    minArray[1] = j;
                                                    minArray[2] = k;
                                                    minArray[3] = l;
                                                    minArray[4] = m;
                                                    minArray[5] = n;
                                                    minArray[6] = o;
                                                    minArray[7] = p;
                                                    minArray[8] = q;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        fprintf (fout, "%d\t%lld\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
                        targetDay, minCost,
                            minArray[0] + 1, minArray[1] + 1, minArray[2] + 1, minArray[3] + 1, 
                                minArray[4] + 1, minArray[5] + 1, minArray[6] + 1, minArray[7] + 1, minArray[8] + 1);
    }
    */
    //printf("%lld\n", minCost);

    free(Method);
    fclose(fin);
    fclose(fout);


    return 0;
}