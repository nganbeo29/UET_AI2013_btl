/**
 * Bot LV2 cpp implementation
 *
 */

#include "bot_lv2.h"

/* ---------- Importing ---------- */

#include <sstream>

#include "../../utils/logger.h"
#include "../logic.h"

/* ---------- Definitions ---------- */

/**
 * Mô tả:
 *   Constructor của BotLevel2.
 */
BotLevel2::BotLevel2(const BotLevel& _level, const char& _symbol)
    : BotLevel1(_level, _symbol) {
}

/**
 * Mô tả:
 *   Destructor của BotLevel2.
 */
BotLevel2::~BotLevel2() {
}

/**
 * Mô tả:
 *   Trả về nước đi của bot MEDIUM.
 *
 * TODO:
 *   - Gọi heuristic để chọn nước đi
 */
pII BotLevel2::getMove(char board[][BOARD_N_MAX], const int size, const int goal) {
    // TODO: gọi simple_heuristic với symbol và op_symbol
    char opponent = (symbol == 'X') ? 'O' : 'X';
    return simple_heuristic(board, size, goal, symbol, opponent);
}

/**
 * Mô tả:
 *   Heuristic đơn giản:
 *   - Ưu tiên thắng
 *   - Chặn đối thủ
 *   - Fallback random
 *
 * TODO:
 *   - Bước 1: kiểm tra nước thắng
 *   - Bước 2: kiểm tra nước chặn
 *   - Bước 3: chọn random nếu không có
 */
pII BotLevel2::simple_heuristic(char board[][BOARD_N_MAX], const int size, const int goal, const char botSymbol, const char playerSymbol) {
    // TODO: implement heuristic
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (board[r][c] == '-') {
                board[r][c] = botSymbol;
                bool win = Logic::checkWin(board, size, botSymbol, goal, EndRule::OPEN_TWO);
                board[r][c] = '-';
                if (win) {
                    return {r, c};
                }
            }
        }
    }
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (board[r][c] == '-') {
                board[r][c] = playerSymbol;
                bool lose = Logic::checkWin(board, size, playerSymbol, goal, EndRule::OPEN_TWO);
                board[r][c] = '-';
                if (lose) {
                    return {r, c};
                }
            }
        }
    }
    int ddr[] = {-1, 0, 1, 1};
    int ddc[] = {1, 1, 1, 0};
    int maxc = 1;
    pII l = {-1, -1};
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (board[r][c] == '-') {
                board[r][c] = botSymbol;
                for (int k = 0; k < 4; k++) {
                    int co = 1;
                    for (int d = 1; d < size; d++) {
                        int nr = r + ddr[k] * d;
                        int nc = c + ddc[k] * d;
                        if (nc < 0 || nc >= size || nr < 0 || nr >= size || board[nr][nc] != botSymbol) break;
                        co++;
                    } 
                    for (int d = 1; d < size; d++) {
                        int nr = r - ddr[k] * d;
                        int nc = c - ddc[k] * d;
                        if (nc < 0 || nc >= size || nr < 0 || nr >= size || board[nr][nc] != botSymbol) break;
                        co++;
                    }
                    if (co > maxc) {
                        maxc = co;
                        l = {r, c};
                    }
                }
                board[r][c] = '-';
                }
        }
    }
    if (l.first != -1) return l;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (board[r][c] == '-') {
                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        int nr = r + dr;
                        int nc = c + dc;
                        if (nr >= 0 && nr < size && nc >= 0 && nc < size && board[nr][nc] != '-') return {r, c};
                    }
                }
            }
        }
    }
    int mid = size / 2;
    if (board[mid][mid] == '-') return {mid, mid};
    // fallback
    return random_pick(board, size);
}