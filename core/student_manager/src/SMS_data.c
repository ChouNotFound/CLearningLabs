/******************************************************************************
 * @file    SMS_data.c
 * @author  zhouzhenyang
 * @date    2025-10-20
 ******************************************************************************
 * Description:
 *   学生数据管理模块，包含学生数据的增删改查等基本操作
 *
 * Functions:
 *   - sms_data_init_students()          : 初始化学生数据
 *   - sms_data_add_student()            : 添加学生数据
 *   - sms_data_delete_student()         : 删除学生数据
 *   - sms_data_find_student()           : 查找学生数据
 *   - sms_data_get_student_count()      : 获取学生数量
 *   - sms_data_get_all_students()       : 获取所有学生数据
 ******************************************************************************
 * @version 1.0
 ******************************************************************************/

/*=============================================================================
 *                           头文件包含区
 *===========================================================================*/

#include <stdio.h>
#include <string.h>
#include "Tprint.h"
#include "SMS_data.h"

/*=============================================================================
 *                          全局变量定义区
 *===========================================================================*/

Student students[MAX_STUDENTS];
int student_count = 0;

/*=============================================================================
 *                          函数实现区
 *===========================================================================*/

/* 初始化学生数据 */
void sms_data_init_students(void)
{
    student_count = 0;
}

/* 添加学生数据 */
/* @param student 指向学生结构体的指针 */
/* @return 1表示成功，0表示失败 */
int sms_data_add_student(const Student* student)
{
    if (student_count >= MAX_STUDENTS)
    {
        return 0; // 学生数量已达上限
    }
    
    students[student_count] = *student;
    student_count++;
    return 1;
}

/* 根据学号删除学生数据 */
/* @param id 学号 */
/* @return 1表示成功，0表示未找到 */
int sms_data_delete_student(int id)
{
    for (int i = 0; i < student_count; i++)
    {
        if (students[i].id == id)
        {
            // 将后面的学生信息前移
            for (int j = i; j < student_count - 1; j++)
            {
                students[j] = students[j + 1];
            }
            student_count--;
            return 1;
        }
    }
    return 0; // 未找到学生
}

/* 根据学号查找学生数据 */
/* @param id 学号 */
/* @return 指向学生结构体的指针，未找到返回NULL */
Student* sms_data_find_student(int id)
{
    for (int i = 0; i < student_count; i++)
    {
        if (students[i].id == id) {
            return &students[i];
        }
    }
    return NULL; // 未找到学生
}

/* 获取学生数量 */
/* @return 当前学生数量 */
int sms_data_get_student_count(void)
{
    return student_count;
}

/* 获取所有学生数据 */
/* @return 指向学生数组的指针 */
Student* sms_data_get_all_students(void)
{
    return students;
}

/* 保存学生数据到文件 */
/* @return 1表示成功，0表示失败 */
int sms_data_save_to_file(void)
{
    FILE* fp = fopen("students.dat", "wb");
    if (fp == NULL)
    {
        return 0; // 文件打开失败
    }
    
    // 写入学生数量
    fwrite(&student_count, sizeof(int), 1, fp);
    
    // 写入所有学生数据
    fwrite(students, sizeof(Student), student_count, fp);
    
    fclose(fp);
    return 1;
}

/* 从文件加载学生数据 */
/* @return 1表示成功，0表示失败 */
int sms_data_load_from_file(void)
{
    FILE* fp = fopen("students.dat", "rb");
    if (fp == NULL)
    {
        return 0; // 文件不存在或打开失败
    }
    
    // 读取学生数量
    fread(&student_count, sizeof(int), 1, fp);
    
    // 读取所有学生数据
    fread(students, sizeof(Student), student_count, fp);
    
    fclose(fp);
    return 1;
}

/* 清除所有学生数据 */
void sms_data_clear_all_students(void)
{
    student_count = 0;
}
