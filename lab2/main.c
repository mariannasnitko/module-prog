#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <getopt.h>

#include "list.h"
#include "csv.h"

struct Inventor
{
    char name[100];
    int year;
    char invention[100];
    int patents;
    float id;
};
typedef struct Inventor Inventor;

void readFile(char *inputFileName, char string[], int len);
void outFile(char *outFileName, char *string);

void processListOfStructs(List *inventors, int patents);
void printInventorsList(List *inventors);
void fillTableFromListOfStructs(List *table, List *inventors);
void fillInventorsListFromTable(List *table, List *inventors);
void fillListFromArray(List *inventors, Inventor array[], int length);

int main(int argc, char *argv[])
{
    char input[20] = "name";
    char output[20] = "name";
    int patents = 0;
    bool isInput = false;
    bool isOutput = false;
    bool processPatents = false;
    int opt;
    while ((opt = getopt(argc, argv, "n:o:")) != -1)
    {
        switch (opt)
        {
            case 'n':
            {
                patents = atoi(optarg);
                processPatents = true;
                break;
            }
            case 'o':
            {
                strcpy(output, optarg);
                isOutput = true;
                break;
            }
            case ':':
            {
                printf("option needs a value\n");
                break;
            }
            case '?':
            {
                printf("unknown option: %c\n", optopt);
                break;
            }
        }
    }
    for (; optind < argc; optind++)
    {
        strcpy(input, argv[optind]);
        isInput = true;
    }
    if (isInput == true)
    {
        int strLength = 1000;
        char csvStr[strLength];
        readFile(input, csvStr, strLength);
        List table;
        List_init(&table);
        Csv_fillTableFromString(&table, csvStr);
        List listOfInventors;
        List_init(&listOfInventors);
        fillInventorsListFromTable(&table, &listOfInventors);
        if (processPatents == true)
        {
            processListOfStructs(&listOfInventors, patents);
        }
        if (isOutput == true)
        {
            List parsedTable;
            List_init(&parsedTable);
            fillTableFromListOfStructs(&parsedTable, &listOfInventors);
            char *p = Csv_createStringFromTable(&parsedTable);
            outFile(output, p);
            free(p);
            Csv_clearTable(&parsedTable);
            List_deinit(&parsedTable);
        }
        else
        {
            printInventorsList(&listOfInventors);
        }
        Csv_clearTable(&table);
        List_deinit(&table);
        for (size_t i = 0; i < List_size(&listOfInventors); i++)
        {
            free(List_get(&listOfInventors, i));
        }
        List_deinit(&listOfInventors);
    }
    else
    {
        Inventor testArr[] = {{"inventor1", 1675, "name 1", 100, 3.1},
                              {"inventor2", 1775, "name 2", 10, 33.2},
                              {"inventor3", 1875, "name 3", 20, 55.3},
                              {"inventor4", 1975, "name 4", 340, 4.4},
                              {"inventor5", 2075, "name 5", 15, 2.5}};
        int testArrLen = 5;
        List listOfInventors;
        List_init(&listOfInventors);
        fillListFromArray(&listOfInventors, testArr, testArrLen);
        if (processPatents == true)
        {
            processListOfStructs(&listOfInventors, patents);
        }
        if (isOutput == true)
        {
            List parsedTable;
            List_init(&parsedTable);
            fillTableFromListOfStructs(&parsedTable, &listOfInventors);
            char *p = Csv_createStringFromTable(&parsedTable);
            outFile(output, p);
            free(p);
            Csv_clearTable(&parsedTable);
            List_deinit(&parsedTable);
        }
        else
        {
            printInventorsList(&listOfInventors);
        }
        for (size_t i = 0; i < List_size(&listOfInventors); i++)
        {
            free(List_get(&listOfInventors, i));
        }
        List_deinit(&listOfInventors);
    }
    return 0;
}

void fillListFromArray(List *inventors, Inventor array[], int length)
{
    for (size_t i = 0; i < length; i++)
    {
        Inventor *item = malloc(sizeof(Inventor));
        strcpy(item->name, array[i].name);
        item->year = array[i].year;
        strcpy(item->invention, array[i].invention);
        item->patents = array[i].patents;
        item->id = array[i].id;
        List_add(inventors, item);
    }
}

void processListOfStructs(List *inventors, int patents)
{
    for (size_t i = 0; i < List_size(inventors); i++)
    {
        Inventor *item = List_get(inventors, i);
        if (item->patents > patents)
        {
            List_removeAt(inventors, i);
            i -= 1;
        }
    }
}

void readFile(char *inputFileName, char string[], int len)
{
    FILE *fp = fopen(inputFileName, "r");
    if (fp == NULL)
    {
        printf("ERROR: file with such name does not exist.\n");
        exit(EXIT_FAILURE);
    }
    char ch = 0;
    int i = 0;
    while (ch != EOF)
    {
        ch = fgetc(fp);
        string[i] = ch;
        i++;
        if (i >= len)
        {
            abort();
        }
    }
    string[i - 1] = '\0';
    fclose(fp);
}

void outFile(char *outFileName, char *string)
{
    FILE *fw = NULL;
    fw = fopen(outFileName, "w");
    if (fw == NULL)
    {
        printf("Error opening file %s\n", outFileName);
        exit(EXIT_FAILURE);
    }
    printf("%s", string);
    fclose(fw);
}

void fillInventorsListFromTable(List *table, List *inventors)
{
    for (size_t i = 1; i < List_size(table); i++)
    {
        Inventor *item = malloc(sizeof(Inventor));
        List *row = List_get(table, i);
        Csv_string(row, 0, item->name, 100);
        item->year = Csv_int(row, 1);
        Csv_string(row, 2, item->invention, 100);
        item->patents = Csv_int(row, 3);
        item->id = Csv_double(row, 4);
        List_add(inventors, item);
    }
}

void fillTableFromListOfStructs(List *table, List *inventors)
{
    List *row = List_alloc();
    Csv_addString(row, "Inventor");
    Csv_addString(row, "Year");
    Csv_addString(row, "Popular invention");
    Csv_addString(row, "Number of patents");
    Csv_addString(row, "Random id");
    Csv_addRow(table, row);
    for (size_t i = 0; i < List_size(inventors); i++)
    {
        List *row = List_alloc();
        Inventor *item = List_get(inventors, i);
        Csv_addString(row, item->name);
        Csv_addInt(row, item->year);
        Csv_addString(row, item->invention);
        Csv_addInt(row, item->patents);
        Csv_addDouble(row, item->id);
        Csv_addRow(table, row);
    }
}

void printInventorsList(List *inventors)
{
    printf("Name\t\t\t Year\t\t Popular invention\t Number of patents\t Random id\n");
    for (size_t i = 0; i < List_size(inventors); i++)
    {
        Inventor *item = List_get(inventors, i);
        printf("%s\t\t ", item->name);
        printf("%i\t\t ", item->year);
        printf("%s\t\t ", item->invention);
        printf("%i\t\t ", item->patents);
        printf("%.2f\t\t ", item->id);
        printf("\n");
    }
}