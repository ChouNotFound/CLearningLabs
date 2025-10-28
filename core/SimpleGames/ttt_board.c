/******************************************************************************
 * @file    board.c
 * @author  
 * @date    2025-10-28
 ******************************************************************************
 * Description:
 *   井字棋游戏棋盘模块实现文件
 *
 * Functions:
 *   - ttt_board_initialize() : 初始化棋盘
 *   - ttt_board_check_win() : 检查玩家是否获胜
 *   - ttt_board_is_full() : 检查棋盘是否已满
 ******************************************************************************
 * @version 1.0
 ******************************************************************************/

/*=============================================================================
 *                           头文件包含区
 *===========================================================================*/

#include "ttt_board.h"

/*=============================================================================
 *                          函数实现区
 *===========================================================================*/

/* 初始化棋盘 */
void ttt_board_initialize(ttt_board_t board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = ' ';
        }
    }
}

/* 检查玩家是否获胜 */
int ttt_board_check_win(ttt_board_t board, char player)
{
    // 检查行
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return 1;
        }
    }
    
    // 检查列
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
        {
            return 1;
        }
    }
    
    // 检查对角线
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    {
        return 1;
    }
    
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        return 1;
    }
    
    return 0;
}

/* 检查棋盘是否已满 */
int ttt_board_is_full(ttt_board_t board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0; // 棋盘未满
            }
        }
    }
    return 1; // 棋盘已满
}