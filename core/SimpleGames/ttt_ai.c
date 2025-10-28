/******************************************************************************
 * @file    ai.c
 * @author  
 * @date    2025-10-28
 ******************************************************************************
 * Description:
 *   井字棋游戏AI模块实现文件
 *
 * Functions:
 *   - ttt_ai_make_move() : AI执行移动
 ******************************************************************************
 * @version 1.0
 ******************************************************************************/

/*=============================================================================
 *                           头文件包含区
 *===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "ttt_ai.h"
#include "ttt_board.h"

/*=============================================================================
 *                          函数实现区
 *===========================================================================*/

/* AI执行移动 */
void ttt_ai_make_move(ttt_board_t board, char player)
{
    // 初始化随机数种子
    static int first_run = 1;
    if (first_run) {
        srand((unsigned int)time(NULL));
        first_run = 0;
    }
    // 简单AI策略：
    // 1. 检查是否能赢，如果能赢则直接赢
    // 2. 检查是否需要阻止对手赢
    // 3. 如果中心位置空着，优先占据中心
    // 4. 如果角落位置空着，占据角落
    // 5. 否则随机选择一个空位
    
    printf("AI (%c) 正在思考...\n", player);
    
    // 添加一点延迟让AI显得更真实
#ifdef _WIN32
    Sleep(1000);
#else
    sleep(1);
#endif
    
    // 1. 检查是否能赢
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = player;
                if (ttt_board_check_win(board, player)) {
                    printf("AI (%c) 在位置 %d %d 落子\n", player, i+1, j+1);
                    return;
                }
                board[i][j] = ' '; // 撤销尝试
            }
        }
    }
    
    // 2. 检查是否需要阻止对手赢 (假设对手是X如果玩家是O，反之亦然)
    char opponent = (player == 'X') ? 'O' : 'X';
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = opponent;
                if (ttt_board_check_win(board, opponent)) {
                    board[i][j] = player; // 阻止对手
                    printf("AI (%c) 在位置 %d %d 落子\n", player, i+1, j+1);
                    return;
                }
                board[i][j] = ' '; // 撤销尝试
            }
        }
    }
    
    // 3. 优先占据中心位置
    if (board[1][1] == ' ') {
        board[1][1] = player;
        printf("AI (%c) 在位置 %d %d 落子\n", player, 2, 2);
        return;
    }
    
    // 4. 占据角落位置
    int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (int i = 0; i < 4; i++) {
        int row = corners[i][0];
        int col = corners[i][1];
        if (board[row][col] == ' ') {
            board[row][col] = player;
            printf("AI (%c) 在位置 %d %d 落子\n", player, row+1, col+1);
            return;
        }
    }
    
    // 5. 随机选择一个空位
    int empty_positions[BOARD_SIZE * BOARD_SIZE][2];
    int count = 0;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                empty_positions[count][0] = i;
                empty_positions[count][1] = j;
                count++;
            }
        }
    }
    
    if (count > 0) {
        int random_index = rand() % count;
        int row = empty_positions[random_index][0];
        int col = empty_positions[random_index][1];
        board[row][col] = player;
        printf("AI (%c) 在位置 %d %d 落子\n", player, row+1, col+1);
    }
}