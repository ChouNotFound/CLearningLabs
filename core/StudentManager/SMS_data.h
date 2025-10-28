/******************************************************************************
 * @file    SMS_data.h
 * @author  zhouzhenyang
 * @date    2025-10-20
 ******************************************************************************
 * Description:
 *   学生数据管理模块的头文件，定义学生结构体和相关函数声明
 *
 * Contains:
 *   - Student 结构体定义
 *   - 相关常量定义
 *   - 函数声明
 ******************************************************************************
 * @version 1.0
 ******************************************************************************/

#ifndef SMS_DATA_H
#define SMS_DATA_H

/*=============================================================================
 *                          常量定义区
 *===========================================================================*/

#define MAX_STUDENTS 100
#define NAME_LENGTH 50

/*=============================================================================
 *                          类型定义区
 *===========================================================================*/

/* 学生结构体 */
typedef struct {
    int id;
    char name[NAME_LENGTH];
    int age;
    float score;
} Student;

/*=============================================================================
 *                         全局变量声明区
 *===========================================================================*/

extern Student students[MAX_STUDENTS];
extern int student_count;

/*=============================================================================
 *                        函数声明区
 *===========================================================================*/

void sms_data_init_students(void);
int sms_data_add_student(const Student* student);
int sms_data_delete_student(int id);
Student* sms_data_find_student(int id);
int sms_data_get_student_count(void);
Student* sms_data_get_all_students(void);

// 文件操作函数声明
int sms_data_save_to_file(void);
int sms_data_load_from_file(void);
void sms_data_clear_all_students(void);

#endif // SMS_DATA_H