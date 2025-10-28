/******************************************************************************
 * @file    SMS_service.c
 * @author  zhouzhenyang
 * @date    2025-10-20
 ******************************************************************************
 * Description:
 *   学生信息管理服务模块，提供学生信息的增删改查服务接口
 *
 * Functions:
 *   - print_student_info(const Student* student)    : 打印单个学生信息
 *   - sms_service_add_student()                     : 添加学生服务
 *   - sms_service_display_all_students()            : 显示所有学生服务
 *   - sms_service_search_student()                  : 查找学生服务
 *   - sms_service_delete_student()                  : 删除学生服务
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
#include "SMS_service.h"
#include "SMS_data.h"
#include "SMS_ui.h"

/*=============================================================================
 *                          函数实现区
 *===========================================================================*/

/* 打印单个学生信息 */
void print_student_info(const Student* student)
{
    printf("学号: %d\n", student->id);
    printf("姓名: %s\n", student->name);
    printf("年龄: %d\n", student->age);
    printf("成绩: %.2f\n", student->score);
}

/* 添加学生服务 */
void sms_service_add_student(void)
{
    int continue_loop = 1;  // 循环控制变量，初始化为1以进入循环
    char continue_choice;
    
    while (continue_loop)
    {
        if (MAX_STUDENTS <= sms_data_get_student_count())
        {
            printf("学生数量已达上限！\n");
            break;  // 跳出循环
        }
        
        Student s;

        printf("\n--- 添加学生 ---\n");
        printf("请输入学号: ");
        scanf("%d", &s.id);
        
        // 检查是否已存在相同ID的学生
        Student* existing_student = sms_data_find_student(s.id);
        if (existing_student != NULL)
        {
            printf("已存在学号为 %d 的学生:\n", s.id);
            print_student_info(existing_student);
            
            char overwrite_choice;
            printf("是否覆盖该学生信息？(y/n): ");
            scanf(" %c", &overwrite_choice);
            
            if (overwrite_choice != 'y' && overwrite_choice != 'Y')
            {
                printf("取消添加学生。\n");
                printf("是否继续添加其他学生？(y/n): ");
                scanf(" %c", &continue_choice);
                
                if (continue_choice == 'y' || continue_choice == 'Y')
                {
                    continue;  // 继续外层循环
                }
                else
                {
                    break;  // 跳出循环
                }
            }
            else
            {
                // 用户选择覆盖，先删除原有的学生记录
                sms_data_delete_student(s.id);
            }
        }
        
        printf("请输入姓名: ");
        // 使用fgets替代scanf以更好地处理中文字符
        while (getchar() != '\n'); // 清空输入缓冲区
        fgets(s.name, sizeof(s.name), stdin);
        // 移除末尾的换行符
        s.name[strcspn(s.name, "\n")] = 0;
        
        printf("请输入年龄: ");
        scanf("%d", &s.age);
        printf("请输入成绩: ");
        scanf("%f", &s.score);
        
        if (0 != sms_data_add_student(&s))
        {
            printf("学生信息添加成功！\n");
            printf("添加的学生信息:\n");
            print_student_info(&s);
            
            // 保存数据到文件
            if (!sms_data_save_to_file())
            {
                printf("警告：数据保存到文件失败！\n");
            }
        }
        else
        {
            printf("学生信息添加失败！\n");
        }
        
        printf("是否继续添加学生？(y/n): ");
        scanf(" %c", &continue_choice);
        
        if (continue_choice == 'y' || continue_choice == 'Y')
        {
            continue_loop = 1;  // 继续循环
        }
        else
        {
            break;  // 跳出循环
        }
    }
}

/* 显示所有学生服务 */
void sms_service_display_all_students(void)
{
    int count = sms_data_get_student_count();
    
    if (0 == count)
    {
        printf("\n暂无学生信息！\n");
        return;
    }
    
    Student* all_students = sms_data_get_all_students();
    
    printf("\n--- 所有学生信息 ---\n");

    for (int i = 0; count > i; i++)
    {
        printf("第%d个学生:\n", i + 1);
        print_student_info(&all_students[i]);
    }
}

/* 查找学生服务 */
void sms_service_search_student(void)
{
    if (0 == sms_data_get_student_count())
    {
        printf("\n暂无学生信息！\n");
        return;
    }
    
    int id;
    char continue_choice = 'y';  // 初始化为'y'以进入循环

    while (continue_choice == 'y' || continue_choice == 'Y')
    {
        printf("\n--- 查找学生 ---\n");
        printf("请输入要查找的学生学号: ");
        scanf("%d", &id);
        
        Student* student = sms_data_find_student(id);

        if (NULL != student)
        {
            printf("\n找到学生信息:\n");
            print_student_info(student);
        }
        else
        {
            printf("未找到学号为 %d 的学生！\n", id);
        }
        
        printf("是否继续查找学生？(y/n): ");
        scanf(" %c", &continue_choice);
    }
}

/* 删除学生服务 */
void sms_service_delete_student(void)
{
    char continue_choice = 'y';  // 初始化为'y'以进入循环
    
    while (continue_choice == 'y' || continue_choice == 'Y')
    {
        if (0 == sms_data_get_student_count())
        {
            printf("\n暂无学生信息！\n");
            return;
        }
        
        char input[10];
        
        printf("\n--- 删除学生 ---\n");
        printf("请输入要删除的学生学号（输入ALL删除所有学生）: ");
        scanf("%s", input);
        
        // 检查是否输入ALL
        if (strcmp(input, "ALL") == 0 || strcmp(input, "all") == 0) 
        {
            // 确认删除所有学生
            char confirm_choice;
            printf("警告：此操作将永久删除所有学生数据且无法恢复！\n");
            printf("您确定要继续吗？(y/N): ");
            scanf(" %c", &confirm_choice);
            
            if (confirm_choice == 'y' || confirm_choice == 'Y')
            {
                int count = sms_data_get_student_count();
                sms_data_clear_all_students();
                
                // 保存数据到文件（现在是空的）
                if (sms_data_save_to_file())
                {
                    printf("所有 %d 条学生数据已清除！\n", count);
                }
                else
                {
                    printf("警告：数据保存到文件失败！\n");
                }
            }
            else
            {
                printf("操作已取消。\n");
            }
        }
        else 
        {
            // 删除单个学生
            int id = atoi(input);
            
            if (0 != sms_data_delete_student(id))
            {
                printf("学号为 %d 的学生信息已删除！\n", id);
                
                // 保存数据到文件
                if (!sms_data_save_to_file())
                {
                    printf("警告：数据保存到文件失败！\n");
                }
            }
            else
            {
                printf("未找到学号为 %d 的学生！\n", id);
            }
        }
        
        // 检查学生数量，如果为0则退出循环
        if (0 == sms_data_get_student_count())
        {
            break;
        }
        
        printf("是否继续删除学生？(y/n): ");
        scanf(" %c", &continue_choice);
    }
}
