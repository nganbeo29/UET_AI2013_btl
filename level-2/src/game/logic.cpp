/**
 * Logic cpp implementation
 *
 */

#include "logic.h"

/* ---------- Importing ---------- */

#include <format>
#include <limits>
#include <sstream>

#include "../utils/logger.h"
using namespace std;

/* ---------- Definitions ---------- */

/**
 * Mô tả: Khởi tạo bàn cờ với ký tự mặc định.
 * Đầu vào: board, size
 * Đầu ra: Không có
 * Tác dụng phụ: Ghi dữ liệu vào board
 * TODO:
 */
void Logic::initBoard(char board[][BOARD_N_MAX], const int size) {
    // TODO: implement
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = '-';
        }
    }
}

/**
 * Mô tả: Kiểm tra nước đi có hợp lệ không.
 * Đầu vào: board, size, row, col
 * Đầu ra: true nếu hợp lệ
 * Tác dụng phụ: Không có
 * TODO:
 */
bool Logic::isValidMove(const char board[][BOARD_N_MAX], const int size, const int row, const int col) {
    // TODO: implement
    if (row < 0 || row >= size || col < 0 || col >= size || board[row][col] != '-') {
        return false;
    }
    return true;
}

/**
 * Mô tả: Thực hiện một nước đi.
 * Đầu vào: board, row, col, symbol
 * Đầu ra: Không có
 * Tác dụng phụ: Ghi vào board
 * TODO:
 */
void Logic::makeMove(char board[][BOARD_N_MAX], const int row, const int col, const char symbol) {
    // TODO: implement
    board[row][col] = symbol;
}

/**
 * Mô tả: Kiểm tra một ô có phải là đầu mở hay không.
 * Đầu vào: board, size, x, y, symbol
 * Đầu ra: true nếu là đầu mở
 * Tác dụng phụ: Không có
 * TODO:
 */
bool Logic::isEmptyHead(const char board[][BOARD_N_MAX], const int size, int x, int y, const char symbol) {
    // TODO: implement
    if (x == size || x == -1 || y == size || y == -1 || board[x][y] == '-' || board[x][y] == symbol) return true;
    return false;
}

/**
 * Mô tả: Kiểm tra điều kiện thắng.
 * Đầu vào: board, size, symbol, goal, rule
 * Đầu ra: true nếu thắng
 * Tác dụng phụ: Có thể log debug
 * TODO:
 */
bool Logic::checkWin(char board[][BOARD_N_MAX], const int size, const char symbol, const int goal, EndRule rule) {
    // TODO: implement
    int dr[] = {1, 0, 1, 1};
    int dc[] = {0, 1, 1, -1};
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] != symbol) continue;
            for (int k = 0; k < 4; k++) {
                int count = 1;
                int nr = i + dr[k];
                int nc = j + dc[k];
                while (nr >= 0 && nr < size && nc >= 0 && nc < size && board[nr][nc] == symbol) {
                    count++;
                    nr += dr[k];
                    nc += dc[k];
                }
                if (count != goal) continue;
                if (rule == EndRule::NONE) {
                    return true;
                } else if (rule == EndRule::OPEN_ONE) {
                    if (isEmptyHead(board, size, i - dr[k], j - dc[k], symbol) || 
                    isEmptyHead(board, size, nr, nc, symbol)) return true;
                } else {
                    if (isEmptyHead(board, size, i - dr[k], j - dc[k], symbol) && 
                    isEmptyHead(board, size, nr, nc, symbol)) return true;
                }
            }
        }
    }
    return false;
}

/**
 * Mô tả: Kiểm tra trạng thái hòa.
 * Đầu vào: board, size
 * Đầu ra: true nếu hòa
 * Tác dụng phụ: Không có
 * TODO:
 */
bool Logic::checkDraw(char board[][BOARD_N_MAX], const int size) {
    // TODO: implement
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == '-') return false;
        }
    }
    return true;
}

/**
 * Mô tả: Lấy đường thắng nếu tồn tại.
 * Đầu vào: board, size, symbol, goal, rule
 * Đầu ra: optional WinLine
 * Tác dụng phụ: Không có
 * TODO:
 */
std::optional<WinLine> Logic::getWinLine(
    const char board[][BOARD_N_MAX],
    const int size,
    const char symbol,
    const int goal,
    EndRule rule) {
    // TODO: implement
    int dr[] = {1, 0, 1, 1};
    int dc[] = {0, 1, 1, -1};
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] != symbol) continue;
            for (int k = 0; k < 4; k++) {
                vector<pair<int, int>> c;
                c.push_back({i, j});
                int count = 1;
                int nr = i + dr[k];
                int nc = j + dc[k];
                while (nr >= 0 && nr < size && nc >= 0 && nc < size && board[nr][nc] == symbol) {
                    c.push_back({nr, nc});
                    count++;
                    nr += dr[k];
                    nc += dc[k];
                }
                if (count != goal) continue;
                bool valid = false;
                if (rule == EndRule::NONE) {
                    valid =  true;
                } else if (rule == EndRule::OPEN_ONE) {
                    if (isEmptyHead(board, size, i - dr[k], j - dc[k], symbol) || 
                    isEmptyHead(board, size, nr, nc, symbol)) valid = true;
                } else {
                    if (isEmptyHead(board, size, i - dr[k], j - dc[k], symbol) && 
                    isEmptyHead(board, size, nr, nc, symbol)) valid = true;
                }
                if (valid) {
                    WinLine w;
                    w.cells = c;
                    return w;
                }
            }
        }
    }
    return std::nullopt;
}