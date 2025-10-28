/******************************************************************************
 * @file    main.c
 * @author  zhouzhenyang
 * @date    2025-10-20
 ******************************************************************************
 * Description:
 *   程序入口文件，包含main函数
 *
 * Functions:
 *   - main() : 主函数
 ******************************************************************************
 * @version 1.0
 ******************************************************************************/

/*=============================================================================
 *                           头文件包含区
 *===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "app_config.h"
#include "Tprint.h"
#include "SMS_controller.h"

/*=============================================================================
 *                          函数声明区
 *===========================================================================*/

void main_init_app(void);
void main_show_main_menu(void);

/*=============================================================================
 *                          函数实现区
 *===========================================================================*/

/* 主函数 */
/* @return 退出程序 */
int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int choice = 0;
    
    main_init_app();
    
    while (1)
    {
        main_show_main_menu();
        scanf("%d", &choice);
        
        switch (choice)
        {
            case 1:
                printf("\n学生信息管理系统");
                sms_run();
                break;
            case 2:
                printf("功能未实现\n");
                break;
            case 3:
                printf("功能未实现\n");
                break;
            case 4:
                printf("功能未实现\n");
                break;
            case 5:
                printf("感谢使用，再见！\n");
                return 0;
            default:
                printf("无效的选择！\n");
                break;
        }
        
        printf("按任意键继续...");
        getchar(); // 读取换行符
        getchar(); // 等待用户按键
    }
    
    return 0;
}

void main_init_app(void)
{
    printf("正在初始化系统...\n");
    sms_initialize_application();
    printf("系统初始化完成。\n");
}

void main_show_main_menu(void)
{
    printf("\n========== 主菜单 ==========\n");
    printf("1. 学生信息管理系统\n");
    printf("2. (未实现)\n");
    printf("3. (未实现)\n");
    printf("4. (未实现)\n");
    printf("5. 退出系统\n");
    printf("============================\n");
    printf("请选择功能（1-5）: ");
}