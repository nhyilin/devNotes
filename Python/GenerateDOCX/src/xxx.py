import numpy as np


# 初始化棋盘
def init_board():
    board = np.zeros((15, 15), dtype=int)
    return board


# 打印棋盘
def print_board(board):
    print("   ", end="")
    for i in range(15):
        print("{0:2d}".format(i), end="")
    print()
    for i in range(15):
        print("{0:2d}".format(i), end="")
        for j in range(15):
            if board[i][j] == 1:
                print(" ●", end="")
            elif board[i][j] == 2:
                print(" ○", end="")
            else:
                print("  ", end="")
        print()


# 判断是否有五子连珠
def check_win(board, player):
    for i in range(15):
        for j in range(11):
            if board[i][j] == player and board[i][j + 1] == player and board[i][j + 2] == player and board[i][
                j + 3] == player and board[i][j + 4] == player:
                return True
        for j in range(15):
            if i < 11 and board[i][j] == player and board[i + 1][j] == player and board[i + 2][j] == player and \
                    board[i + 3][j] == player and board[i + 4][j] == player:
                return True
        for j in range(11):
            if i < 11 and board[j][i] == player and board[j + 1][i + 1] == player and board[j + 2][i + 2] == player and \
                    board[j + 3][i + 3] == player and board[j + 4][i + 4] == player:
                return True
            if i > 3 and board[j][i] == player and board[j + 1][i - 1] == player and board[j + 2][i - 2] == player and \
                    board[j + 3][i - 3] == player and board[j + 4][i - 4] == player:
                return True
    return False


# 下棋
def play(board, player):
    while True:
        x = int(input("请输入横坐标（0-14）："))
        y = int(input("请输入纵坐标（0-14）："))
        if x < 0 or x > 14 or y < 0 or y > 14 or board[x][y] != 0:
            print("输入无效，请重新输入！")
            continue
        board[x][y] = player
        break


# 主程序
def main():
    board = init_board()
    print_board(board)
    player = 1
    while True:
        play(board, player)
        print_board(board)
        if check_win(board, player):
            print("玩家 {0} 获胜！".format(player))
            break
        player = 3 - player


if __name__ == '__main__':
    main()
