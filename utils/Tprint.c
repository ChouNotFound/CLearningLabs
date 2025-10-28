/******************************************************************************
 * @file    TPrint.c
 * @author  zhouzhenyang
 * @date    2025-10-20
 ******************************************************************************
 * Description:
 *   打印工具模块，包含打字机效果输出的相关函数实现
 *
 * Functions:
 *   - typeWriterEffect()  : 打字机效果输出字符串
 *   - typeWriterPrintf()  : 格式化打字机效果输出
 ******************************************************************************
 * @version 1.0
 ******************************************************************************/

/*=============================================================================
 *                           头文件包含区
 *===========================================================================*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <windows.h>
#include "Tprint.h"

/*=============================================================================
 *                          函数实现区
 *===========================================================================*/

#define OUTPUT_DELAY_MS 5

/* 打字机效果输出字符串 */
void typeWriterEffect(const char* str) 
{
    while (*str) 
    {
        putchar(*str++);
        fflush(stdout);
        Sleep(OUTPUT_DELAY_MS);
    }
}

/* 格式化打字机效果输出 */
void typeWriterPrintf(const char* format, ...) 
{
    va_list args;
    va_start(args, format);
    
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);
    
    typeWriterEffect(buffer);
}