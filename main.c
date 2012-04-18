#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SAFESCAN(f,...) if (f == 0) { printf(__VA_ARGS__); exit(1);}
#define MAXBUFF 300

typedef struct act_t
{
    char Name[20];
    long long int Labor;
    long long int Material;
    long long int Subcontractor;
    long long int Days;
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
            SAFESCAN(fscanf(fin, "\t%lld", &(Method + j)->Activities[i].Labor),         "Excavation.Labor Format Error\n")
            SAFESCAN(fscanf(fin, "\t%lld", &(Method + j)->Activities[i].Material),      "Excavation.Labor Format Error\n")
            SAFESCAN(fscanf(fin, "\t%lld", &(Method + j)->Activities[i].Subcontractor), "Excavation.Labor Format Error\n")
            SAFESCAN(fscanf(fin, "\t%lld", &(Method + j)->Activities[i].Days),          "Excavation.Labor Format Error\n")
        }
    }

    PrintMethod(Method, numMethod);


    free(Method);
    fclose(fin);
    fclose(fout);


    return 0;
}