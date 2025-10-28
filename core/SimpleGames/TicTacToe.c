/******************************************************************************
 * @file    TicTacToe.c
 * @author  
 * @date    2025-10-28
 ******************************************************************************
 * Description:
 *   井字棋游戏实现文件
 *
 * Functions:
 *   - ttt_run() : 运行井字棋游戏
 ******************************************************************************
 * @version 1.0
 ******************************************************************************/

/*=============================================================================
 *                           头文件包含区
 *===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "Tprint.h"
#include "ttt_board.h"
#include "ttt_display.h"
#include "ttt_input.h"
#include "ttt_ai.h"

/*=============================================================================
 *                          函数实现区
 *===========================================================================*/

/* 运行井字棋游戏 */
void ttt_run(void)
{
    ttt_board_t board;
    char currentPlayer = 'X';
    int gameEnded = 0;
    int gameMode = 0; // 1: 人人对战, 2: 人机对战
    
    // 初始化棋盘
    ttt_board_initialize(board);
    
    printf("\n========== 井字棋游戏 ==========\n");
    printf("请选择游戏模式:\n");
    printf("1. 双人对战\n");
    printf("2. 人机对战\n");
    printf("请输入选项 (1 或 2): ");
    scanf("%d", &gameMode);
    
    if (gameMode == 2) {
        printf("你将与AI对战，你执 X，AI执 O\n");
    }
    
    printf("输入行列坐标进行落子，例如: 1 2 表示第1行第2列\n");
    printf("============================\n");
    
    while (!gameEnded)
    {
        // 显示棋盘
        ttt_display_board(board);
        
        // 根据游戏模式和当前玩家决定移动方式
        if (gameMode == 1 || currentPlayer == 'X') {
            // 玩家移动
            ttt_input_player_move(board, currentPlayer);
        } else {
            // AI移动
            ttt_ai_make_move(board, currentPlayer);
        }
        
        // 检查是否获胜
        if (ttt_board_check_win(board, currentPlayer))
        {
            ttt_display_board(board);
            if (gameMode == 2 && currentPlayer == 'O') {
                printf("AI 获胜！\n");
            } else {
                printf("玩家 %c 获胜！\n", currentPlayer);
            }
            gameEnded = 1;
        }
        // 检查棋盘是否已满
        else if (ttt_board_is_full(board))
        {
            ttt_display_board(board);
            printf("平局！\n");
            gameEnded = 1;
        }
        // 切换玩家
        else
        {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
    
    printf("游戏结束！\n");
}
