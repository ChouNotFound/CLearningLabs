/******************************************************************************
 * @file    StudentManager.c
 * @author  zhouzhenyang
 * @date    2025-10-28
 ******************************************************************************
 * Description:
 *   学生管理系统模块，包含学生管理系统的核心逻辑
 *
 * Functions:
 *   - sm_initialize() : 初始化学生管理系统
 *   - sm_run()        : 运行学生管理系统主循环
 ******************************************************************************
 * @version 1.0
 ******************************************************************************/

/*=============================================================================
 *                           头文件包含区
 *===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tprint.h"
#include "StudentManager.h"
#include "SMS_data.h"

/*=============================================================================
 *                          函数实现区
 *===========================================================================*/

// UI函数声明
static void sm_show_menu(void);
static int sm_get_user_choice(void);

// Service函数声明
static void sm_add_student(void);
static void sm_display_all_students(void);
static void sm_search_student(void);
static void sm_delete_student(void);

/* 初始化学生管理系统 */
void sm_initialize(void)
{
    sms_data_init_students();
    
    // 在初始化时加载学生数据
    if (sms_data_load_from_file())
    {
        printf("成功加载学生数据。\n");
    }
    else
    {
        printf("未找到学生数据文件，将创建新的数据文件。\n");
    }
}

/* 运行学生管理系统主循环 */
void sm_run(void)
{
    int choice = 0;

    while (6 != choice && 5 != choice)
    {
        sm_show_menu();
        choice = sm_get_user_choice();
        
        switch (choice)
        {
            case 1:
                sm_add_student();
                break;
            case 2:
                sm_display_all_students();
                break;
            case 3:
                sm_search_student();
                break;
            case 4:
                sm_delete_student();
                break;
            case 5:
                // 返回主菜单，不执行任何操作，循环会在sm_run中结束
                break;
            case 6:
                printf("感谢使用，再见！\n");
                exit(0);
                break;
            default:
                printf("无效选择，请重新输入！\n");
        }
    }
    
    // 退出前保存数据到文件
    if (sms_data_save_to_file())
    {
        printf("学生数据已保存。\n");
    }
    else
    {
        printf("保存学生数据失败！\n");
    }
}

/* 显示菜单 */
static void sm_show_menu(void)
{
    printf("\n========== 学生信息管理系统 ==========\n");
    printf("1. 添加学生信息\n");
    printf("2. 显示所有学生信息\n");
    printf("3. 查找学生信息\n");
    printf("4. 删除学生信息\n");
    printf("5. 返回主菜单\n");
    printf("6. 退出系统\n");
    printf("=====================================\n");
    printf("请选择功能（1-6）: ");
}

/* 获取用户选择 */
static int sm_get_user_choice(void)
{
    int choice = 0;
    scanf("%d", &choice);
    return choice;
}

/* 添加学生 */
static void sm_add_student(void)
{
    if (student_count >= MAX_STUDENTS) 
    {
        printf("学生数量已达上限！\n");
        return;
    }

    Student newStudent;
    printf("请输入学生学号: ");
    scanf("%d", &newStudent.id);
    
    // 检查学号是否已存在
    if (sms_data_find_student(newStudent.id) != NULL)
    {
        printf("学号 %d 已存在！\n", newStudent.id);
        return;
    }

    printf("请输入学生姓名: ");
    scanf("%s", newStudent.name);
    printf("请输入学生年龄: ");
    scanf("%d", &newStudent.age);
    printf("请输入学生成绩: ");
    scanf("%f", &newStudent.score);

    if (sms_data_add_student(&newStudent))
    {
        printf("添加学生成功！\n");
    }
    else
    {
        printf("添加学生失败！\n");
    }
}

/* 显示所有学生 */
static void sm_display_all_students(void)
{
    Student* allStudents = sms_data_get_all_students();
    int count = sms_data_get_student_count();

    if (count == 0)
    {
        printf("暂无学生信息！\n");
        return;
    }

    printf("\n========== 所有学生信息 ==========\n");
    printf("%-10s %-15s %-10s %-10s\n", "学号", "姓名", "年龄", "成绩");
    for (int i = 0; i < count; i++)
    {
        printf("%-10d %-15s %-10d %-10.2f\n", 
               allStudents[i].id, 
               allStudents[i].name, 
               allStudents[i].age, 
               allStudents[i].score);
    }
    printf("==================================\n");
    printf("总计: %d 名学生\n", count);
}

/* 查找学生 */
static void sm_search_student(void)
{
    int id;
    printf("请输入要查找的学生学号: ");
    scanf("%d", &id);

    Student* student = sms_data_find_student(id);
    if (student != NULL)
    {
        printf("\n========== 学生信息 ==========\n");
        printf("学号: %d\n", student->id);
        printf("姓名: %s\n", student->name);
        printf("年龄: %d\n", student->age);
        printf("成绩: %.2f\n", student->score);
        printf("==============================\n");
    }
    else
    {
        printf("未找到学号为 %d 的学生！\n", id);
    }
}

/* 删除学生 */
static void sm_delete_student(void)
{
    int id;
    printf("请输入要删除的学生学号: ");
    scanf("%d", &id);

    if (sms_data_delete_student(id))
    {
        printf("删除成功！\n");
    }
    else
    {
        printf("未找到学号为 %d 的学生，删除失败！\n", id);
    }
}