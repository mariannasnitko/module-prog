#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"

void Csv_addInt(List *row, int value)
{
    char buffer[100];
    sprintf(buffer, "%i", value);
    char *bufOnHeap = malloc(strlen(buffer) + 1);
    strcpy(bufOnHeap, buffer);
    List_add(row, bufOnHeap);
}

void Csv_addDouble(List *row, double value)
{
    char buffer[100];
    sprintf(buffer, "%lf", value);
    char *bufOnHeap = malloc(strlen(buffer) + 1);
    strcpy(bufOnHeap, buffer);
    List_add(row, bufOnHeap);
}

void Csv_addString(List *row, const char *value)
{
    char *bufOnHeap = malloc(strlen(value) + 1);
    strcpy(bufOnHeap, value);
    List_add(row, bufOnHeap);
}

int Csv_int(List *row, int index)
{
    if (index >= 0 && index < row->size)
    {
        int buff = atoi(row->items[index]);
        return buff;
    }
    else
    {
        printf("ERROR: invalid index\n");
        return -1;
    }
}

double Csv_double(List *row, int index)
{
    if (index >= 0 && index < row->size)
    {
        float buffer = atof(row->items[index]);
        return buffer;
    }
    else
    {
        printf("ERROR: invalid index\n");
        return -1;
    }
}

int Csv_string(List *row, int index, char *buf, int nBuf)
{
    if (strlen(List_get(row, index)) + 1 > nBuf)
    {
        return -1;
    }
    else
    {
        strcpy(buf, List_get(row, index));
        return 0;
    }
}

void Csv_addRow(List *table, List *row)
{
    List_add(table, row);
}

List *Csv_row(List *table, int index)
{
    return table->items[index];
}

void Csv_fillTableFromString(List *csvTable, const char *csvStr)
{
    List *row = NULL;
    char buf[10000];
    int bufX = 0;
    const char *p = csvStr;
    while (1)
    {
        if (*p == ',' || *p == '\n' || *p == '\0')
        {
            buf[bufX] = '\0';
            if (bufX == 0 && *p == '\0' && row == NULL)
            {
                break;
            }
            if (row == NULL)
            {
                row = List_alloc();
            }
            char *bufOnHeap = malloc(strlen(buf) + 1);
            strcpy(bufOnHeap, buf);
            List_add(row, bufOnHeap);
            if (*p == '\n' || *p == '\0')
            {
                List_add(csvTable, row);
                row = NULL;
            }
            bufX = 0;
        }
        else
        {
            buf[bufX] = *p;
            bufX += 1;
        }
        if (*p == '\0')
        {
            break;
        }
        p += 1;
    }
}

int Csv_fillStringFromTable(List *csvTable, char *buf, int nBuf)
{
    buf[0] = '\0';
    int buffLength = 0;
    for (size_t i = 0; i < List_size(csvTable); i++)
    {
        List *rowItem = List_get(csvTable, i);
        for (size_t j = 0; j < List_size(rowItem); j++)
        {
            char *value = List_get(rowItem, j);
            strcat(buf, value);
            if (j != List_size(rowItem) - 1)
            {
                strcat(buf, ",");
            }
            buffLength += strlen((char*)List_get(rowItem,j));
        }
        if (i != List_size(csvTable) - 1)
        {
            strcat(buf, "\n");
        }
    }
    if (buffLength > nBuf)
        return -1;
    return 0;
}

char *Csv_createStringFromTable(List *csvTable)
{
    char *newString = malloc(sizeof(char) * 10000);
    newString[0] = '\0';
    Csv_fillStringFromTable(csvTable, newString, 10000);
    return newString;
}

void Csv_clearTable(List *csvTable)
{
    for (size_t i = 0; i < List_size(csvTable); i++)
    {
        List *temp = List_get(csvTable, i);
        for (size_t j = 0; j < List_size(temp); j++)
        {
            free(List_get(temp, j));
        }
        List_free(List_get(csvTable, i));
    }
}