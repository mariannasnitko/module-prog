#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <getopt.h>
#include <assert.h>

#include <csv.h>
#include <list.h>
#include "strstrmap.h"
#include "bstree.h"

struct Inventor
{
    int id;
    char name[100];
    int year;
    char invention[100];
    int patents;
    float rId;
};
typedef struct Inventor Inventor;

void readFile(char *inputFileName, char string[], int len);
void outFile(char *outFileName, char *string);

StrStrMap *createInventorMap(int id, const char *name, int year, const char *invention, int patents, float rId);
void fillListOfMapsFromInventorsArray(List *listOfMaps, Inventor array[], int length);
void fillListOfMapsFromTable(List *table, List *listOfMaps);
void proccesListOfMaps(List *listOfMaps, int patents);
void fillTableFromListOfMaps(List *table, List *listOfMaps);
void printListOfMaps(List *listOfMaps);
char *String_allocCopy(const char *value);
char *String_allocFromInt(int value);
char *String_allocFromDouble(double value);

int main(int argc, char *argv[])
{
    char input[20] = "name";
    char output[20] = "name";
    int patents = 0;
    bool isInput = false;
    bool isOutput = false;
    bool processPatents = false;
    bool StrStrMapToBSTree = false;
    int opt;
    while ((opt = getopt(argc, argv, "b n:o:")) != -1)
    {
        switch (opt)
        {
        case 'n':
        {
            patents = atof(optarg);
            processPatents = true;
        }
        break;
        case 'o':
        {
            strcpy(output, optarg);
            isOutput = true;
        }
        break;
        case 'b':
        {
            StrStrMapToBSTree = true;
        }
        break;
        case ':':
        {
            printf("option needs a value\n");
        }
        break;
        case '?':
        {
            printf("unknown option: %c\n", optopt);
        }
        break;
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
        List listOfMaps;
        List_init(&listOfMaps);
        fillListOfMapsFromTable(&table, &listOfMaps);
        if (StrStrMapToBSTree == true)
        {
            BSTree *bSTreeOfInventors = BSTree_alloc();
            for (size_t i = 0; i < List_size(&listOfMaps); i++)
            {
                StrStrMap *map = List_get(&listOfMaps, i);
                BSTree_insert(bSTreeOfInventors, map);
            }
            printf("Binary Search Tree:\n");
            traverseInOrder(bSTreeOfInventors->root);
            printf("\n");
            //
            if (processPatents == true)
            {
                for (size_t i = 0; i < List_size(&listOfMaps); i++)
                {
                    StrStrMap *map = List_get(&listOfMaps, i);
                    if (atof(StrStrMap_get(map, "patents")) < patents)
                    {
                        int key = getKey(map);
                        if (BSTree_lookup(bSTreeOfInventors, key) == true)
                        {
                            BSTree_delete(bSTreeOfInventors, key);
                        }
                    }
                }
                printf("BSTree result:\n");
                traverseInOrder(bSTreeOfInventors->root);
                printf("\n");
            }
            BSTree_clear(bSTreeOfInventors);
            BSTree_free(bSTreeOfInventors);
        }
        if (processPatents == true)
        {
            proccesListOfMaps(&listOfMaps, patents);
        }
        if (isOutput == true)
        {
            List parsedTable;
            List_init(&parsedTable);
            fillTableFromListOfMaps(&parsedTable, &listOfMaps);
            char *p = Csv_createStringFromTable(&parsedTable);
            outFile(output, p);
            free(p);
            Csv_clearTable(&parsedTable);
            List_deinit(&parsedTable);
        }
        else
        {
            printListOfMaps(&listOfMaps);
        }
        Csv_clearTable(&table);
        List_deinit(&table);

        for (size_t i = 0; i < List_size(&listOfMaps); i++)
        {
            StrStrMap *map = List_get(&listOfMaps, i);
            StrStrMap_clear(map);
        }
        List_deinit(&listOfMaps);
    }
    else
    {
        Inventor testArray[] = {{4, "inventor1", 1675, "name 1", 100, 3.1},
                                {8, "inventor2", 1775, "name 2", 10, 33.2},
                                {15, "inventor3", 1875, "name 3", 20, 55.3},
                                {16, "inventor4", 1975, "name 4", 340, 4.4},
                                {23, "inventor5", 2075, "name 5", 15, 2.5}};
        int testArrLen = 5;
        List listOfMaps;
        List_init(&listOfMaps);

        fillListOfMapsFromInventorsArray(&listOfMaps, testArray, testArrLen);

        if (StrStrMapToBSTree == true)
        {
            BSTree *bSTreeOfInventors = BSTree_alloc();
            for (size_t i = 0; i < List_size(&listOfMaps); i++)
            {
                StrStrMap *map = List_get(&listOfMaps, i);
                BSTree_insert(bSTreeOfInventors, map);
            }
            printf("Binary Search Tree:\n");
            traverseInOrder(bSTreeOfInventors->root);
            printf("\n");
            if (processPatents == true)
            {
                for (size_t i = 0; i < List_size(&listOfMaps); i++)
                {
                    StrStrMap *map = List_get(&listOfMaps, i);
                    if (atof(StrStrMap_get(map, "patents")) < patents)
                    {
                        int key = getKey(map);
                        if (BSTree_lookup(bSTreeOfInventors, key) == true)
                        {
                            BSTree_delete(bSTreeOfInventors, key);
                        }
                    }
                }
                printf("Binary Search Tree after proccesing:\n");
                traverseInOrder(bSTreeOfInventors->root);
                printf("\n");
            }
            BSTree_clear(bSTreeOfInventors);
            BSTree_free(bSTreeOfInventors);
        }
        if (processPatents == true)
        {
            proccesListOfMaps(&listOfMaps, patents);
        }
        if (isOutput == true)
        {
            List parsedTable;
            List_init(&parsedTable);
            fillTableFromListOfMaps(&parsedTable, &listOfMaps);
            char *p = Csv_createStringFromTable(&parsedTable);
            outFile(output, p);
            free(p);
            Csv_clearTable(&parsedTable);
            List_deinit(&parsedTable);
        }
        else
        {
            printListOfMaps(&listOfMaps);
        }
        for (size_t i = 0; i < List_size(&listOfMaps); i++)
        {
            StrStrMap *map = List_get(&listOfMaps, i);
            StrStrMap_clear(map);
        }
        List_deinit(&listOfMaps);
    }
    return 0;
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
    FILE *fw = fopen(outFileName, "w");
    if (fw == NULL)
    {
        printf("Error opening file %s\n", outFileName);
        exit(EXIT_FAILURE);
    }
    fprintf(fw, "%s", string);
    fclose(fw);
}

char *String_allocCopy(const char *value)
{
    char *copy = malloc(strlen(value) + 1);
    strcpy(copy, value);
    return copy;
}

char *String_allocFromInt(int value)
{
    char buffer[100];
    buffer[0] = '\0';
    sprintf(buffer, "%i", value);
    char *str = malloc(strlen(buffer) + 1);
    strcpy(str, buffer);
    return str;
}

char *String_allocFromDouble(double value)
{
    char buffer[100];
    buffer[0] = '\0';
    sprintf(buffer, "%f", value);
    char *str = malloc(strlen(buffer) + 1);
    strcpy(str, buffer);
    return str;
}

StrStrMap *createInventorMap(int id, const char *name, int year, const char *invention, int patents, float rId)
{
    char *idValue = String_allocFromInt(id);
    char *nameValue = String_allocCopy(name);
    char *yearValue = String_allocFromInt(year);
    char *inventionValue = String_allocCopy(invention);
    char *patentsValue = String_allocFromInt(patents);
    char *rIdValue = String_allocFromDouble(rId);
    StrStrMap *map = StrStrMap_alloc();
    StrStrMap_add(map, "id", idValue);
    StrStrMap_add(map, "name", nameValue);
    StrStrMap_add(map, "year", yearValue);
    StrStrMap_add(map, "invention", inventionValue);
    StrStrMap_add(map, "patents", patentsValue);
    StrStrMap_add(map, "rId", rIdValue);
    return map;
}

void printListOfMaps(List *listOfMaps)
{
    printf("Id\t\t    Name\t\t  Year\t\t       Invention\t\t    Patents  RandId\n");
    for (size_t i = 0; i < List_size(listOfMaps); i++)
    {
        List valueList;
        List_init(&valueList);
        StrStrMap *item = List_get(listOfMaps, i);
        StrStrMap_values(item, &valueList);
        for (size_t j = 0; j < List_size(&valueList); j++)
        {
            printf("%s\t\t ", (char *)List_get(&valueList, j));
        }
        printf("\n");
        List_deinit(&valueList);
    }
}

void fillListOfMapsFromTable(List *table, List *listOfMaps)
{
    for (size_t i = 1; i < List_size(table); i++)
    {
        List *row = List_get(table, i);
        int id = Csv_int(row, 0);
        char nameBuff[100];
        nameBuff[0] = '\0';
        Csv_string(row, 1, nameBuff, 100);
        int year = Csv_int(row, 2);
        char inventionBuff[100];
        inventionBuff[0] = '\0';
        Csv_string(row, 3, inventionBuff, 100);
        int patents = Csv_int(row, 4);
        float rId = Csv_double(row, 5);
        List_add(listOfMaps, createInventorMap(id, nameBuff, year, inventionBuff, patents, rId));
    }
}

void fillListOfMapsFromInventorsArray(List *listOfMaps, Inventor array[], int length)
{
    for (size_t i = 0; i < length; i++)
    {
        List_add(listOfMaps, createInventorMap(array[i].id, array[i].name, array[i].year, array[i].invention, array[i].patents, array[i].rId));
    }
}

void proccesListOfMaps(List *listOfMaps, int patents)
{
    for (size_t i = 0; i < List_size(listOfMaps); i++)
    {
        StrStrMap *map = List_get(listOfMaps, i);
        if (atof(StrStrMap_get(map, "patents")) > patents)
        {
            StrStrMap_clear(map);
            List_removeAt(listOfMaps, i);
            i -= 1;
        }
    }
}

void fillTableFromListOfMaps(List *table, List *listOfMaps)
{
    List *row = List_alloc();
    Csv_addString(row, "Id");
    Csv_addString(row, "Name");
    Csv_addString(row, "Year");
    Csv_addString(row, "Invention");
    Csv_addString(row, "Patents");
    Csv_addString(row, "RandId");
    Csv_addRow(table, row);
    for (size_t i = 0; i < List_size(listOfMaps); i++)
    {
        List *row = List_alloc();
        List valueList;
        List_init(&valueList);
        StrStrMap *item = List_get(listOfMaps, i);
        StrStrMap_values(item, &valueList);
        for (size_t j = 0; j < List_size(&valueList); j++)
        {
            Csv_addString(row, (char *)List_get(&valueList, j));
        }
        Csv_addRow(table, row);
        List_deinit(&valueList);
    }
}