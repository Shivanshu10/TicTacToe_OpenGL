#include<iostream>
#include<GL/glut.h>
#include<GL/freeglut.h>
#include<math.h>

using namespace std;

class TicTacToeBoard {
    public:
    char board[3][3];
    int filled;
    int llx, lly, w, h;

    public:
    TicTacToeBoard(int llx, int lly, int w, int h) {
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                board[i][j]='_';
            }
        }
        filled=0;
        this->llx=llx;
        this->lly=lly;
        this->w=w;
        this->h=h;
    }

    int put(int x, int y, char c) {
        // outside board
        if (x<llx || y<lly || x>(llx+w) || y>(lly+h)) {
            return -1;
        }

        int i, j;
        if (x<=((w/3)+llx)) {
            j=0;
        } else if (x<=(2*w/3)+llx) {
            j=1;
        } else if (x<=w+llx) {
            j=2;
        }

        if (y<=((h/3)+lly)) {
            i=0;
        } else if (y<=((2*h/3)+lly)) {
            i=1;
        } else if (y<=(h+lly)) {
            i=2;
        }

        if (i>=3 || j>=3) {
            //cout << "ArrayIndexOutOfBound: put function" << endl;
            return -1;
        }
        if (board[i][j]!='_') {
            //cout << "Illegal Placement" << endl;
            return -1;
        }
        board[i][j]=c;
        filled++;
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

    void drawX(int mx, int my, int w, int h) {
        glColor3f(1, 0.18, 0.38);
        //glColor3f(0.93, 0.93, 0.93);
        glLineWidth(30);
        glBegin(GL_LINES);
        glVertex2f(mx-w/2, my-h/2);
        glVertex2f(mx+w/2, my+h/2);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(mx+w/2, my-h/2);
        glVertex2f(mx-w/2, my+h/2);
        glEnd();
    }

    void drawO(int ori_x, int ori_y, int radius) {
        glColor3f(0.3, 0.85, 0.83);
        //glColor3f(0.93, 0.93, 0.93);
        glBegin(GL_POINTS);
        for (int i = 0; i <= 300; i++) {
            double angle = 2 * 3.14 * i / 300;
            double x = cos(angle) * radius;
            double y = sin(angle) * radius;
            glVertex2d(ori_x + x, ori_y + y);
        }
        glEnd();
    }

    void draw() {
        // draw lines
        glColor3f(0.93, 0.93, 0.93);
        glBegin(GL_LINES);
        glVertex2f(llx+w/3, lly);
        glVertex2f(llx+w/3, lly+h);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(llx+(2*w)/3, lly);
        glVertex2f(llx+(2*w)/3, lly+h);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(llx, lly+h/3);
        glVertex2f(llx+w, lly+h/3);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(llx, lly+(2*h)/3);
        glVertex2f(llx+w, lly+(2*h)/3);
        glEnd();

        // draw X and O
        int x=w/6, y=2*h/3+h/6;
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                if (board[i][j]=='X') {
                    drawX(x+llx, y+lly, w/3-40, h/3-40);
                }
                else if (board[i][j]=='O') {
                    drawO(x+llx, y+lly, (w/3-40)/2);
                }
                x+=(w/3);
            }
            x=w/6;
            y-=(h/3);
        }
    }

    void reset() {
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                board[i][j]='_';
            }
        }
        filled=0;
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
    public:
    TicTacToeBoard board=TicTacToeBoard(250, 250, 500, 500);
    Player p1=Player('X');
    Player p2=Player('O');
    bool turn_p1=true, p1_won=false, p2_won=false;

    void drawString(void *font,const char s[], int x, int y) {
    	glRasterPos2i(x, y);
    	glutBitmapString(font, (unsigned char*)s);
    }

    bool checkWinner() {
	    int i, j;
	    // horizontal checkN_24, (unsigned char*
	    for(i=0;i<3;i++) {
		    for(j=1;j<3;j++) {
                if(board.board[i][0]!='_' && board.board[i][0]==board.board[i][j]) {
                    if(j==2) {
                        return true;
                    }
			    }
                else {
                    break;
                }
		    }
	    }
	    // vertical check
	    for(i=0;i<3;i++) {
		    for(j=1;j<3;j++) {
			    if(board.board[0][i]!='_' && board.board[0][i]==board.board[j][i]) {
				    if(j==2) {
                        return true;
                    }
			    }
			    else {
				    break;
                }
		    }
	    }
	    // Diagonal check
	    if((board.board[0][0]!='_' && board.board[0][0]==board.board[1][1] && board.board[0][0]==board.board[2][2]) || (board.board[2][0]!='_' && board.board[2][0]==board.board[1][1] && board.board[2][0]==board.board[0][2])) {
            return true;
        }
	    return false;
    }

    bool checkDraw() {
    	for (int i=0; i<3; i++) {
    		for (int j=0; j<3; j++) {
    			if (board.board[i][j]=='_') {
    				return false;
    			}
    		}
    	}
    	return true;
    }

    void clickEvent(int x, int y) {
        // check inside tic tac toe board
    	if (p1_won || p2_won) {
    		return;
    	}
        int fill=-1;
        if (turn_p1) {
            fill=p1.put(&board, x, y);
            if (fill==-1) {
                return;
            }
        } else {
            fill=p2.put(&board, x, y);
            if (fill==-1) {
                return;
            }
        }
        if (turn_p1) {
        	turn_p1=false;
        } else {
            turn_p1=true;
        }
        glutPostRedisplay();
        board.print();
    }

    void gameOver() {
       if (p1_won && p2_won) {
           //cout << "tie" << endl;
    	   glColor3f(0.93, 0.93, 0.93);
           drawString(GLUT_BITMAP_HELVETICA_18, "       DRAW :(", 425, 770);
       }
       else if (p1_won) {
           //cout << "p1 won" << endl;
           glColor3f(0.3, 0.85, 0.83);
           drawString(GLUT_BITMAP_HELVETICA_18, "PLAYER O WON!!", 425, 770);
       }
       else if(p2_won) {
           //cout << "p2 won" << endl;
           glColor3f(1, 0.18, 0.38);
           drawString(GLUT_BITMAP_HELVETICA_18, "PLAYER X WON!!", 425, 770);
       }
       glutPostRedisplay();
    }

    void draw() {
    	glColor3f(0.40, 0.40, 0.40);
        drawString(GLUT_BITMAP_HELVETICA_18, "Made in Thapar", 425, 30);
        if (p1_won || p2_won) {
        	gameOver();
        }
        else if (turn_p1) {
        	glColor3f(1, 0.18, 0.38);
        	drawString(GLUT_BITMAP_HELVETICA_18, "PLAYER X TURN", 425, 770);
        }
        else {
        	glColor3f(0.3, 0.85, 0.83);
        	drawString(GLUT_BITMAP_HELVETICA_18, "PLAYER O TURN", 425, 770);
        }
        board.draw();
    }
    
    void reset() {
    	turn_p1=true;
    	p1_won=false;
    	p2_won=false;
    	board.reset();
        draw();
    }
};

Game game=Game();

void display() {
    glClearColor(0.22, 0.24, 0.27, 1);
    //glClearColor(0.0, 0.0, 0.0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    game.draw();
    glFlush();

    if (game.checkWinner()==true) {
    	if (game.turn_p1==true) {
    		// p1 won
            game.p1_won=true;
        }
        else {
        	game.p2_won=true;
        }
        return;
    }
    if (game.checkDraw()==true) {
    	game.p1_won=true;
        game.p2_won=true;
    }
}

void init(int x, int y, int w, int h, int pt_size, int line_width) {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(x, y);
	glutCreateWindow("Tic Tac Toe Game");

    glClearColor(1, 1, 1, 1);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(pt_size);
    glLineWidth(line_width);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, w, 0.0, h);
	glClear(GL_COLOR_BUFFER_BIT);
}

void onMouseClick(int button,int state,int x,int y) {
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
        game.clickEvent(x, y);
    }
}

void onKeyPress(unsigned char key, int x, int y){
    switch(key){
		case 'y':
			if(game.p1_won || game.p2_won)
			{
				game.reset();
			}
			break;
		case 'n':
			if(game.p1_won || game.p2_won)
				exit(0);
			break;
		case 27:
			exit(0);
	}
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    init(0, 0, 1000, 1000, 5, 8);
	glutDisplayFunc(display);
    glutMouseFunc(onMouseClick);
	glutKeyboardFunc(onKeyPress);
    glutIdleFunc(display);
    //game.play();
	glutMainLoop();
	return 0;
}

