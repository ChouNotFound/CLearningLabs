/******************************************************************************
 * @file    SMS_controller.c
 * @author  zhouzhenyang
 * @date    2025-10-20
 ******************************************************************************
 * Description:
 *   应用程序控制模块，包含学生管理系统的核心控制逻辑
 *
 * Functions:
 *   - sms_initialize_application() : 初始化应用程序
 *   - sms_handle_user_choice()     : 处理用户选择
 *   - sms_run()   : 运行应用程序主循环
 ******************************************************************************
 * @version 1.0
 ******************************************************************************/

/*=============================================================================
 *                           头文件包含区
 *===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "Tprint.h"
#include "SMS_controller.h"
#include "SMS_ui.h"
#include "SMS_data.h"
#include "SMS_service.h"

/*=============================================================================
 *                          函数实现区
 *===========================================================================*/

/* 初始化应用程序 */
void sms_initialize_application(void)
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

/* 处理用户选择 */
void sms_handle_user_choice(int choice)
{
    switch (choice)
    {
        case 1:
            sms_service_add_student();
            break;
        case 2:
            sms_service_display_all_students();
            break;
        case 3:
            sms_service_search_student();
            break;
        case 4:
            sms_service_delete_student();
            break;
        case 5:
            // 返回主菜单，不执行任何操作，循环会在sms_run中结束
            break;
        case 6:
            printf("感谢使用，再见！\n");
            exit(0);
            break;
        default:
            printf("无效选择，请重新输入！\n");
    }
}

/* 运行应用程序主循环 */
void sms_run(void)
{
    int choice = 0;

    while (6 != choice && 5 != choice)
    {
        sms_ui_show_menu();
        choice = sms_ui_get_user_choice();
        sms_handle_user_choice(choice);
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