/**
 * Ternimal Renderer cpp implementation
 *
 */

#include "renderer.h"

/* ---------- Importing ---------- */

#include <format>
#include <iostream>

#include "../game/setup.h"
#include "../utils/config.h"
using namespace std;

/* ---------- Definitions ---------- */

/**
 * Mô tả:
 *   Constructor của TerminalRenderer.
 *
 * TODO:
 *   - Khởi tạo trạng thái ban đầu nếu cần
 */
TerminalRenderer::TerminalRenderer() : I_Renderer() {
    // TODO: init state
}

/**
 * Mô tả:
 *   Destructor của TerminalRenderer.
 *
 * TODO:
 *   - Giải phóng tài nguyên nếu có
 */
TerminalRenderer::~TerminalRenderer() {
    // TODO: cleanup nếu cần
}

/**
 * Mô tả:
 *   Khởi tạo renderer với config.
 *
 * TODO:
 *   - Đọc config
 *   - Thiết lập môi trường hiển thị
 */
void TerminalRenderer::init(const RunConfig& config) {
    // TODO: init renderer theo config
    (void) config;
}

/**
 * Mô tả:
 *   Xóa màn hình terminal.
 *
 * TODO:
 *   - Sử dụng ANSI escape sequence để clear screen
 */
void TerminalRenderer::clearScreen() {
    // TODO: clear screen
    std::cout << "\n"
              << "\x1B[2J\x1B[H"
              << "\n";
    return;
}

/**
 * Mô tả:
 *   Hiển thị menu lựa chọn.
 *
 * TODO:
 *   - Bước 1: kiểm tra selectType
 *   - Bước 2: in menu tương ứng
 *   - Trường hợp biên: selectType không hợp lệ
 */
void TerminalRenderer::showSelectMenu(SelectType selectType, int context) {
    // TODO: render menu theo loại
    switch (selectType) {
        case SelectType::TITLE_UI:
            std::cout << std::format(">----- TIC-TAC-TOE [Console v{}] -----<\n\n", VERSION);
            break;

        case SelectType::SIZE_UI:
            // TODO: display board size selection
            // Example: "Size Input (NxN, 3 <= N <= BOARD_N_MAX)"
            cout << "Please choose board size" << endl << format("(NXN, 3 <= N <= {})", BOARD_N_MAX) << endl;
            break;

        case SelectType::GOAL_UI:
            // TODO: display goal selection
            // Example: "Goal Input (3 - 5, goal <= size)"
            cout << "Please choose winning goal" << endl << "(3 <= goal <= size)" << endl;
            break;

        case SelectType::GAME_MODE_UI:
            // TODO: display game mode selection
            // Example: "(1) PvP | (2) PvE | (3) EvE"
            cout << "Please choose game mode: " << endl;
            cout << "(1) PVP || (2) PVE || (3) EVE" << endl;
            break;

        case SelectType::BOT_LEVEL_UI:
            // TODO: display bot level selection
            // Example: "(1) EASY | (2) MEDIUM | (3) HARD"
            cout << "Please choose bot level: " << endl;
            cout << "(1) EASY || (2) MEDIUM || (3) HARD" << endl;
            break;

        case SelectType::PLAYER_UI:
            // TODO: display player move prompt
            // Example input format: "(row, col)"
            cout << "Enter your move:" << endl << "(row col, 0-based)" << endl;
            break;

        case SelectType::MUL_BOT_LEVEL_UI:
            // TODO: display multiple bot level selection
            // Example input format: "(bot1_level, bot2_level)"
            cout << "Please choose levels for both bots: " << endl;
            cout << "Example input format: bot1 bot 2" << endl;
            cout << "(1) EASY || (2) MEDIUM || (3) HARD" << endl;
            break;

        default:
            break;
    }
}

/**
 * Mô tả:
 *   Hiển thị thông báo lựa chọn không hợp lệ.
 *
 * TODO:
 *   - Bước 1: xác định loại lỗi
 *   - Bước 2: in thông báo tương ứng
 */
void TerminalRenderer::showInvalidSelect(SelectType selectType, int context) {
    // TODO: render invalid message
    (void) context;
    switch (selectType) {
        case SelectType::SIZE_UI:
            // TODO: display board size selection
            // Example: "Size Input (NxN, 3 <= N <= BOARD_N_MAX)"
            cout << format("Invalid size, please choose again. Must be {} to {}.\n", BOARD_N_MIN, BOARD_N_MAX);
            break;

        case SelectType::GOAL_UI:
            // TODO: display goal selection
            // Example: "Goal Input (3 - 5, goal <= size)"
            cout << "Invalid goals, please choose again. Must be 3 to size.\n";
            break;

        case SelectType::GAME_MODE_UI:
            // TODO: display game mode selection
            // Example: "(1) PvP | (2) PvE | (3) EvE"
            cout << "Invalid mode, please choose again. Must be 1, 2 or 3.\n";
            break;

        case SelectType::BOT_LEVEL_UI:
        case SelectType::MUL_BOT_LEVEL_UI:
            // TODO: display bot level selection
            // Example: "(1) EASY | (2) MEDIUM | (3) HARD"
            cout << "Invalid bot level, please choose again. Must be 1, 2 or 3.\n";
            break;

        default:
            break;
    }
}

/**
 * Mô tả:
 *   Hiển thị thông báo lựa chọn hợp lệ.
 *
 * TODO:
 *   - Bước 1: xác định loại select
 *   - Bước 2: in thông báo xác nhận
 */
void TerminalRenderer::showValidSelect(SelectType selectType, int context) {
    // TODO: render success message
    switch (selectType) {
        case SelectType::SIZE_UI:
            // TODO: display board size selection
            // Example: "Size Input (NxN, 3 <= N <= BOARD_N_MAX)"
            cout << format("Valid size: {}",  context) << endl;
            break;

        case SelectType::GOAL_UI:
            // TODO: display goal selection
            // Example: "Goal Input (3 - 5, goal <= size)"
            cout << format("Valid goals: {}",  context) << endl;
            break;

        case SelectType::GAME_MODE_UI:
            // TODO: display game mode selection
            // Example: "(1) PvP | (2) PvE | (3) EvE"
            cout << format("Valid game mode: {}",  context) << endl;
            break;

        case SelectType::BOT_LEVEL_UI:
        case SelectType::MUL_BOT_LEVEL_UI:
            // TODO: display bot level selection
            // Example: "(1) EASY | (2) MEDIUM | (3) HARD"
            cout << format("Valid bot level: {}",  context) << endl;
            break;
        default:
            break;
    }
}

/**
 * Mô tả:
 *   Hiển thị bàn cờ.
 *
 * TODO:
 *   - Bước 1: in header
 *   - Bước 2: in trục tọa độ
 *   - Bước 3: duyệt board và in từng ô
 */
void TerminalRenderer::displayBoard(const char board[][BOARD_N_MAX], const int size) {
    // TODO: render board
    cout << "    ";
    for (int i = 0; i < size; i++) {
        cout << "  " << i << " ";
    }
    cout << endl;
    cout << "    ";
    for (int i = 0; i < size; i++) {
        cout << " ---";
    }
    cout << endl;
    for (int j = 0; j < size; j++) {
        cout << "  " << j << " ";
        for (int i = 0; i < size; i++) {
            cout << "| " << board[j][i] << " ";
        }
        cout << "|" << endl;
        cout << "    ";
        for (int l = 0; l < size; l++) {
            cout << " ---";
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * Mô tả:
 *   Hiển thị thông tin player hiện tại.
 *
 * TODO:
 *   - In player index
 *   - Nếu là bot thì thêm label "(Bot)"
 */
void TerminalRenderer::showPlayer(int player, bool is_bot) {
    // TODO: render player info
    if (is_bot) {
        cout << format("Bot (Player {}) is thinking...", player + 1);
    } else {
        cout << format("Player {}'s turn", player + 1);
    }
    cout << endl;
}

/**
 * Mô tả:
 *   Hiển thị nước đi vừa thực hiện.
 *
 * TODO:
 *   - In ra tọa độ (row, col)
 */
void TerminalRenderer::showMove(const int row, const int col) {
    // TODO: render move
    cout << "Move placed at (" << row << ", " << col << ")" << endl;
}

/**
 * Mô tả:
 *   Hiển thị thông báo nước đi không hợp lệ.
 *
 * TODO:
 *   - In message lỗi
 */
void TerminalRenderer::showInvalidMove() {
    // TODO: render invalid move message
    cout << "Invalid move. Please choose again" << endl;
}

/**
 * Mô tả:
 *   Hiển thị kết quả game.
 *
 * TODO:
 *   - Bước 1: kiểm tra draw hoặc winner
 *   - Bước 2: in kết quả
 *   - Trường hợp biên: winner = -1
 */
void TerminalRenderer::showResult(const int winner, const bool is_bot, const WinLine* winLine) {
    // TODO: render result

    if (winner == DRAW_RESULT) {
        cout << "It's a draw!";
    } else if (is_bot) {
        cout << format("Bot (Player {}) wins!", winner + 1);
    } else {
        cout << format("Player {} wins!", winner + 1);
    }
}

/**
 * Mô tả:
 *   In kết quả đơn giản (judge mode).
 *
 * TODO:
 *   - In winner và số lượt
 */
void TerminalRenderer::printResult(const GameResult& gameResult) {
    // TODO: print result đơn giản
    cout << gameResult.winner << " " << gameResult.turns << endl;
}

/**
 * Mô tả:
 *   Đóng renderer.
 *
 * TODO:
 *   - Giải phóng tài nguyên nếu có
 */
void TerminalRenderer::close() {
    // TODO: cleanup renderer
}