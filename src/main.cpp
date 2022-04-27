#include<iostream>

using namespace std;

class TicTacToeBoard {
    private:
    char board[3][3];
    int filled;

    public:
    TicTacToeBoard() {
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                board[i][j]='_';
            }
        }
        filled=0;
    }

    int put(int x, int y, char c) {
        if (x>=3 || y>=3) {
            cout << "ArrayIndexOutOfBound: put function" << endl;
            return -1;
        }
        if (board[x][y]!='_') {
            cout << "Illegal Placement" << endl;
            return -1;
        }
        board[x][y]=c;
        filled++;
        cout << "Placed" << endl;
        return filled;
    }
    
    void print() {
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

class Player {
    private:
    char sign;
    
    public:
    Player(char s) {
        sign=s;
    }

    int put(TicTacToeBoard *board, int x, int y) {
        return board->put(x, y, sign);
    }
};

class Game {
    private:
    TicTacToeBoard board=TicTacToeBoard();
    Player p1=Player('X');
    Player p2=Player('O');

    public:
    int isPlayer1Won() {
        return 1;
    }
    
    int play() {
        bool turn_p1=true;
        int fill=0;
        int x, y;
        while(fill!=9) {
            fill=-1;
            cout << "Plese provide move: ";
            if (turn_p1) {
                while(fill==-1) {
                    cin >> x >> y;
                    fill=p1.put(&board, x, y);
                }
            } else {
                while (fill==-1) {
                    cin >> x >> y;
                    fill=p2.put(&board, x, y);
                }
            }
            board.print();
            turn_p1=!(turn_p1);
        }
        return isPlayer1Won();
    }
};

int main() {
    Game game=Game();
    game.play();
}