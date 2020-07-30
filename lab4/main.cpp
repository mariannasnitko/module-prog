#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#include "list.h"
#include "deque.h"

void List_print(List *self);
List readFloatsFromFile(const char *fileName);
void processList(List *list);

int main(void)
{
    srand(time(NULL));
    List list = readFloatsFromFile("data.txt");
    List_print(&list);
    int k = list.size();
    printf("List size %d\n", k);
    processList(&list);
    puts("");
    List_print(&list);
    puts("");
    Deque deque;
    Deque deque2;
    for (int i = 0; i < list.size(); i++)
    {
        if (i % 2 == 0)
        {
            deque2.pushFront(list[i]);
        }
        else
        {
            deque.pushBack(list[i]);
        }
    }
    puts("");
    deque.print();
    puts("");
    deque2.print();
    int n = deque.size();
    int m = deque2.size();
    printf("Deque size %d, %d\n", n, m);
    List list2;
    return 0;
}

void List_print(List *self)
{
    for (int i = 0; i < self->size(); i++)
    {
        printf("%d). %3.3lf\n", i, (*self)[i]);
    }
}

List readFloatsFromFile(const char *fileName)
{
    List list;
    char buf[100];
    int buf_i = 0;
    FILE *fin = fopen("data.txt", "r");
    char ch = fgetc(fin);
    while (1)
    {
        if (ch == ' ' || ch == EOF)
        {
            buf[buf_i] = '\0';
            buf_i = 0;
            float curr_num = atof(buf);
            if (buf[0] != '\0')
            {
                list.add(curr_num);
            }
        }
        else
        {
            buf[buf_i++] = ch;
        }
        if (ch == EOF)
        {
            break;
        }
        ch = fgetc(fin);
    }
    if (fin != NULL)
    {
        fclose(fin);
    }
    return list;
}

void processList(List * list)
{
    double num = 0;
    int firts_position = 0;
    int length = list->size();
    for (int i = 0; i < length; i++)
    {
        num = (*list)[i];
        if (num < 0)
        {
            list->removeAt(i);
            list->insert(firts_position, num);
        }
    }
}