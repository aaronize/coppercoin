/**
 * 指针嵌套
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define false 0
#define true 1

#define NAME_MAX 40

typedef struct Teacher
{
    int id;
    char *name;
    int stu_num;
    char **stu_name;
} Teacher;

// int createTeacher(Teacher **p, int n1, int n2)
// {
//     int len = 0;
//     int i, j, k;
//     *p = (Teacher*)malloc(sizeof(Teacher)*3);

//     for (i = 0; i < n1; i++)
//     {
//         (*p)[i].tName = (char *)malloc(sizeof(char) * 20);
//         if ((*p)[i].tName == NULL)
//         {
//             return false;
//         }
//     }

//     for (j = 0; j < n2; j++)
//     {
//         (*p)[j].stu = (char **)malloc(sizeof(char) * 3);
//         if ((*p)[j].stu == NULL)
//         {
//             return false;
//         }

//         for (k = 0; k < 3; k++)
//         {
//             (*p)[j].stu[k] = (char *)malloc(sizeof(char) * 20);
//             if ((*p)[j].stu[k] == NULL)
//                 return false;
//         }
//     }
//     return true;
// }

/*
    *teacher: 指向老师数组的指针
    num: 开辟老师内存的个数
*/
int callocTeacher(Teacher **teacher, int num)
{
    if (teacher == NULL || num <= 0)
    {
        return -1;
    }

    Teacher *teacher_in = NULL;
    teacher_in = calloc(num, sizeof(Teacher));
    for (int i = 0; i < num; i++)
    {
        (teacher_in + i)->name = malloc(sizeof(char) * NAME_MAX);
        memset((teacher_in + i)->name, 0, sizeof(char) * NAME_MAX);
    }

    *teacher = teacher_in;

    return 0;
}
