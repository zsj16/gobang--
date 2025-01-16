//work of Zhu sijia-五子棋人人对战和人机对战图形化界面的实现，包括了悔棋复盘和三三禁手
#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#define NUM 15
#define WIN_NUM 5
int pieceArr[NUM][NUM] = { 0 }; // Records the state of each board position: 0=empty, 1=black, 2=white
struct Move {
    int x, y;  // Position on the board
    int color; // Color of the piece (1 for black, 2 for white)
};
Move history[500];
int historyIndex = 0; // Current move count
// Function to display game options
void option() {
    settextcolor(WHITE);
    settextstyle(100, 0, _T("Consolas"));
    outtextxy(125, 200, _T("人人对战")); // Display "Player vs Player"
    outtextxy(125, 400, _T("人机对战")); // Display "Player vs AI"
}
// Function to display game functions
void function() {
    settextcolor(WHITE);
    settextstyle(40, 0, _T("Consolas"));
    outtextxy(200, 600, _T("悔棋")); // Display "Undo Move"
    outtextxy(300, 600, _T("复盘")); // Display "Replay"
}
// Function to draw the board lines
void Draw_line() {
    setlinecolor(BLACK);
    for (int x = 20; x < 600; x += 40) line(x, 20, x, 580); // Vertical lines
    for (int y = 20; y < 600; y += 40) line(20, y, 580, y); // Horizontal lines
}
// Function to draw the special points on the board
void Draw_point() {
    setfillcolor(BLACK);
    fillcircle(140, 140, 5);
    fillcircle(140, 460, 5);
    fillcircle(460, 140, 5);
    fillcircle(460, 460, 5);
    fillcircle(300, 300, 5);
}
// Function to draw a piece on the board
void Draw_piece(int color, int i, int j) {
    if (i >= 0 && i < NUM && j >= 0 && j < NUM) {
        setfillcolor(color == 1 ? BLACK : WHITE);
        pieceArr[i][j] = color;
        fillcircle(20 + i * 40, 20 + j * 40, 15); // Draw a circle for the piece
    }
}
// Function to replay the game
void replay() {
    ExMessage m;
    while (1) {
        m = getmessage(EX_MOUSE);
        if (m.message == WM_LBUTTONDOWN && m.x >= 300 && m.x <= 380 && m.y >= 600 && m.y <= 640) {
            clearcliprgn();
            loadimage(NULL, _T("2.png"));
            Draw_line();
            Draw_point();
            function();
            for (int i = 0; i < historyIndex; i++) {
                Draw_piece(history[i].color, history[i].x, history[i].y);
                Sleep(1000);
            }
            break;
        }
    }
}
// Function to check if the game is over
int GameOver(int x, int y) {
    x = x / 40;
    y = y / 40;
    int n = pieceArr[x][y];
    if (n == 1) {
        if (x == 0 || x == 14 || y == 0 || y == 14) {
        }
        else {
            int count1 = 0, count2 = 0, count3 = 0, count4 = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0;
            int i, j;
            // Check horizontally
            count1 = 0;
            c1 = 0;
            for (i = x; i - 1 >= 0 && pieceArr[i][y] == n && pieceArr[i - 1][y] != 2; i--) count1++;
            for (i = x + 1; i + 1 < NUM && pieceArr[i][y] == n && pieceArr[i + 1][y] != 2; i++) count1++;
            for (i = x; i >= 0 && pieceArr[i][y] == n; i--) c1++;
            for (i = x + 1; i < NUM && pieceArr[i][y] == n; i++) c1++;
            if (count1 == 3 && c1 == 3) count1 = 1;
            else count1 = 0;

            // Check vertically
            count2 = 0;
            c2 = 0;
            for (j = y; j - 1 >= 0 && pieceArr[x][j] == n && pieceArr[x][j - 1] != 2; j--) count2++;
            for (j = y + 1; j + 1 < NUM && pieceArr[x][j] == n && pieceArr[x][j + 1] != 2; j++) count2++;
            for (j = y; j >= 0 && pieceArr[x][j] == n; j--) c2++;
            for (j = y + 1; j < NUM && pieceArr[x][j] == n; j++) c2++;
            if (count2 == 3 && c2 == 3) count2 = 1;
            else count2 = 0;

            // Check diagonal (top-right to bottom-left)
            count3 = 0;
            c3 = 0;
            for (i = x, j = y; i + 1 < NUM && j - 1 >= 0 && pieceArr[i][j] == n && pieceArr[i + 1][j - 1] != 2; i++, j--) count3++;
            for (i = x - 1, j = y + 1; i - 1 >= 0 && j + 1 < NUM && pieceArr[i][j] == n && pieceArr[i - 1][j + 1] != 2; i--, j++) count3++;
            for (i = x, j = y; i < NUM && j - 1 >= 0 && pieceArr[i][j] == n; i++, j--) c3++;
            for (i = x - 1, j = y + 1; i >= 0 && j + 1 < NUM && pieceArr[i][j] == n; i--, j++) c3++;
            if (count3 == 3 && c3 == 3) count3 = 1;
            else count3 = 0;

            // Check diagonal (top-left to bottom-right)
            count4 = 0;
            c4 = 0;
            for (i = x, j = y; i - 1 >= 0 && j - 1 >= 0 && pieceArr[i][j] == n && pieceArr[i - 1][j - 1] != 2; i--, j--) count4++;
            for (i = x + 1, j = y + 1; i + 1 < NUM && j + 1 < NUM && pieceArr[i][j] == n && pieceArr[i + 1][j + 1] != 2; i++, j++) count4++;
            for (i = x, j = y; i >= 0 && j >= 0 && pieceArr[i][j] == n; i--, j--) c4++;
            for (i = x + 1, j = y + 1; i < NUM && j < NUM && pieceArr[i][j] == n; i++, j++) c4++;
            if (count4 == 3 && c4 == 3) count4 = 1;
            else count4 = 0;
            int count = count1 + count2 + count3 + count4;
            if (count >= 2) return 2;
        }
    }
    if (n == 0) return 0;
    int count = 0;
    int i, j;

    // Check for win condition in all directions
    int directions[8][2] = { {-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {1,1}, {-1,1}, {1,-1} };
    for (int d = 0; d < 8; d += 2) {
        count = 1;
        for (int i = 1; i < WIN_NUM; i++) {
            int nx = x + i * directions[d][0], ny = y + i * directions[d][1];
            if (nx >= 0 && nx < NUM && ny >= 0 && ny < NUM && pieceArr[nx][ny] == n) count++;
            else break;
        }
        for (int i = 1; i < WIN_NUM; i++) {
            int nx = x + i * directions[d + 1][0], ny = y + i * directions[d + 1][1];
            if (nx >= 0 && nx < NUM && ny >= 0 && ny < NUM && pieceArr[nx][ny] == n) count++;
            else break;
        }
        if (count >= WIN_NUM) return n;
    }
    return 0;
}
// Function to record and draw a move
void Draw_piece_record_history(bool black, int x, int y) {
    if (x < 600 && y < 600) {
        int i = x / 40;
        int j = y / 40;
        int color = black ? 1 : 2;

        Draw_piece(color, i, j);

        history[historyIndex].x = i;
        history[historyIndex].y = j;
        history[historyIndex].color = color;
        historyIndex++; // Increment history index
    }
}
// Check if the move is valid
bool NicePos(int x, int y) {
    if (x >= 600 || y >= 600) return false;
    int i = x / 40, j = y / 40;
    return pieceArr[i][j] == 0;
}
// Function to undo the last move
void Undo_move() {
    if (historyIndex > 0) {
        historyIndex--; // Decrement history index
        int lastX = history[historyIndex].x;
        int lastY = history[historyIndex].y;
        pieceArr[lastX][lastY] = 0;
    }
}
// AI function for black player
void BLACK_AI_DRAW() {
    int score[NUM][NUM] = { 1 };
    for (int x = 0; x < NUM; x++) {
        for (int y = 0; y < NUM; y++) {
            int h1 = 0, h2 = 0, h3 = 0, h4 = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0, p1 = 0, p2 = 0, p3 = 0, p4 = 0, o1 = 0, o2 = 0, o3 = 0, o4 = 0;
            int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
            int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
            int i = 0, j = 0;
            if (pieceArr[x][y] == 1) score[x][y] = 0;
            else if (pieceArr[x][y] == 2) {
                // Defense logic
                score[x][y] = 0;
                for (i = x; i >= 0 && pieceArr[i][y] == 2 && pieceArr[i - 1][y] != 1; i--) h1++;
                for (i = x; i < NUM && pieceArr[i][y] == 2 && pieceArr[i + 1][y] != 1; i++) h2++;
                for (i = x; i >= 0 && pieceArr[i][y] == 2; i--) h3++;
                for (i = x; i < NUM && pieceArr[i][y] == 2; i++) h4++;
                if (h1 == 3 && h3 == 4 && pieceArr[x + 1][y] == 0) score[x + 1][y] += 4000000;
                if (h2 == 3 && h4 == 4 && pieceArr[x - 1][y] == 0) score[x - 1][y] += 4000000;
                if (h1 == 3 && h3 == 3 && pieceArr[x + 1][y] == 0) score[x + 1][y] += 40000;
                if (h2 == 3 && h4 == 3 && pieceArr[x - 1][y] == 0) score[x - 1][y] += 40000;
                if (h1 == 2 && pieceArr[x + 1][y] == 0) score[x + 1][y] += 4000;
                if (h2 == 2 && pieceArr[x - 1][y] == 0) score[x - 1][y] += 4000;
                if (h1 == 1 && pieceArr[x + 1][y] == 0) score[x + 1][y] += 1000;
                if (h2 == 1 && pieceArr[x - 1][y] == 0) score[x - 1][y] += 1000;
                for (j = y; j >= 0 && pieceArr[x][j] == 2 && pieceArr[x][j - 1] != 1; j--) s1++;
                for (j = y; j < NUM && pieceArr[x][j] == 2 && pieceArr[x][j + 1] != 1; j++) s2++;
                for (j = y; j >= 0 && pieceArr[x][j] == 2; j--) s3++;
                for (j = y; j < NUM && pieceArr[x][j] == 2; j++) s4++;
                if (s1 == 3 && s3 == 4 && pieceArr[x][y + 1] == 0) score[x][y + 1] += 4000000;
                if (s2 == 3 && s4 == 4 && pieceArr[x][y - 1] == 0) score[x][y - 1] += 4000000;
                if (s1 == 3 && s3 == 3 && pieceArr[x][y + 1] == 0) score[x][y + 1] += 40000;
                if (s2 == 3 && s4 == 3 && pieceArr[x][y - 1] == 0) score[x][y - 1] += 40000;
                if (s1 == 2 && pieceArr[x][y + 1] == 0) score[x][y + 1] += 4000;
                if (s2 == 2 && pieceArr[x][y - 1] == 0) score[x][y - 1] += 4000;
                if (s1 == 1 && pieceArr[x][y + 1] == 0) score[x][y + 1] += 1000;
                if (s2 == 1 && pieceArr[x][y - 1] == 0) score[x][y - 1] += 1000;
                for (i = x, j = y; i < NUM && j >= 0 && pieceArr[i][j] == 2 && pieceArr[i + 1][j - 1] != 1; i++, j--) p1++;
                for (i = x, j = y; i >= 0 && j < NUM && pieceArr[i][j] == 2 && pieceArr[i - 1][j + 1] != 1; i--, j++) p2++;
                for (i = x, j = y; i < NUM && j >= 0 && pieceArr[i][j] == 2; i++, j--) p3++;
                for (i = x, j = y; i >= 0 && j < NUM && pieceArr[i][j] == 2; i--, j++) p4++;
                if (p1 == 3 && p3 == 4 && pieceArr[x - 1][y + 1] == 0) score[x - 1][y + 1] += 4000000;
                if (p2 == 3 && p4 == 4 && pieceArr[x + 1][y - 1] == 0) score[x + 1][y - 1] += 4000000;
                if (p1 == 3 && p3 == 3 && pieceArr[x - 1][y + 1] == 0) score[x - 1][y + 1] += 40000;
                if (p2 == 3 && p4 == 3 && pieceArr[x + 1][y - 1] == 0) score[x + 1][y - 1] += 40000;
                if (p1 == 2 && pieceArr[x - 1][y + 1] == 0) score[x - 1][y + 1] += 4000;
                if (p2 == 2 && pieceArr[x + 1][y - 1] == 0) score[x + 1][y - 1] += 4000;
                if (p1 == 1 && pieceArr[x - 1][y + 1] == 0) score[x - 1][y + 1] += 1000;
                if (p2 == 1 && pieceArr[x + 1][y - 1] == 0) score[x + 1][y - 1] += 1000;
                for (i = x, j = y; i >= 0 && j >= 0 && pieceArr[i][j] == 2 && pieceArr[i - 1][j - 1] != 1; i--, j--) o1++;
                for (i = x, j = y; i < NUM && j < NUM && pieceArr[i][j] == 2 && pieceArr[i + 1][j + 1] != 1; i++, j++) o2++;
                for (i = x, j = y; i >= 0 && j >= 0 && pieceArr[i][j] == 2; i--, j--) o3++;
                for (i = x, j = y; i < NUM && j < NUM && pieceArr[i][j] == 2; i++, j++) o4++;
                if (o1 == 3 && o3 == 4 && pieceArr[x + 1][y + 1] == 0) score[x + 1][y + 1] += 4000000;
                if (o2 == 3 && o4 == 4 && pieceArr[x - 1][y - 1] == 0) score[x - 1][y - 1] += 4000000;
                if (o1 == 3 && o3 == 3 && pieceArr[x + 1][y + 1] == 0) score[x + 1][y + 1] += 40000;
                if (o2 == 3 && o4 == 3 && pieceArr[x - 1][y - 1] == 0) score[x - 1][y - 1] += 40000;
                if (o1 == 2 && pieceArr[x + 1][y + 1] == 0) score[x + 1][y + 1] += 4000;
                if (o2 == 2 && pieceArr[x - 1][y - 1] == 0) score[x - 1][y - 1] += 4000;
                if (o1 == 1 && pieceArr[x + 1][y + 1] == 0) score[x + 1][y + 1] += 1000;
                if (o2 == 1 && pieceArr[x - 1][y - 1] == 0) score[x - 1][y - 1] += 1000;
            }
            else if (pieceArr[x][y] == 0) {
                // Attack logic
                pieceArr[x][y] = 1;
                for (i = x; i >= 0 && pieceArr[i][y] == 1; i--) count1++;
                for (i = x + 1; i < NUM && pieceArr[i][y] == 1; i++) count1++;
                for (i = x; i - 1 >= 0 && pieceArr[i][y] == 1 && pieceArr[i - 1][y] != 2; i--) c1++;
                for (i = x + 1; i + 1 < NUM && pieceArr[i][y] == 1 && pieceArr[i + 1][y] != 2; i++) c1++;
                if (count1 <= 4 && c1 <= 2) score[x][y] += 100 * count1;
                if (count1 == 3 && c1 == 3) score[x][y] += 1000;
                if (count1 == 4 && c1 >= 3) score[x][y] += 10000;
                if (count1 == 5) score[x][y] += 10000000;
                count1 = 0; c1 = 0;
                for (j = y; j >= 0 && pieceArr[x][j] == 1; j--) count2++;
                for (j = y + 1; j < NUM && pieceArr[x][j] == 1; j++) count2++;
                for (j = y; j - 1 >= 0 && pieceArr[x][j] == 1 && pieceArr[x][j - 1] != 2; j--) c2++;
                for (j = y + 1; j + 1 < NUM && pieceArr[x][j] == 1 && pieceArr[x][j + 1] != 2; j++) c2++;
                if (count2 <= 4 && c2 <= 2) score[x][y] += 100 * count2;
                if (count2 == 3 && c2 == 3) score[x][y] += 1000;
                if (count2 == 4 && c2 >= 3) score[x][y] += 10000;
                if (count2 == 5) score[x][y] += 10000000;
                count2 = 0; c2 = 0;
                for (i = x, j = y; i < NUM && j >= 0 && pieceArr[i][j] == 1; i++, j--) count3++;
                for (i = x - 1, j = y + 1; i >= 0 && j < NUM && pieceArr[i][j] == 1; i--, j++) count3++;
                for (i = x, j = y; i + 1 < NUM && j - 1 >= 0 && pieceArr[i][j] == 1 && pieceArr[i + 1][j - 1] != 2; i++, j--) c3++;
                for (i = x - 1, j = y + 1; i - 1 >= 0 && j + 1 < NUM && pieceArr[i][j] == 1 && pieceArr[i - 1][j + 1] != 2; i--, j++) c3++;
                if (count3 <= 4 && c3 <= 2) score[x][y] += 100 * count3;
                if (count3 == 3 && c3 == 3) score[x][y] += 1000;
                if (count3 == 4 && c3 >= 3) score[x][y] += 10000;
                if (count3 == 5) score[x][y] += 10000000;
                count3 = 0; c3 = 0;
                for (i = x, j = y; i >= 0 && j >= 0 && pieceArr[i][j] == 1; i--, j--) count4++;
                for (i = x + 1, j = y + 1; i < NUM && j < NUM && pieceArr[i][j] == 1; i++, j++) count4++;
                for (i = x, j = y; i - 1 >= 0 && j - 1 >= 0 && pieceArr[i][j] == 1 && pieceArr[i - 1][j - 1] != 2; i--, j--) c4++;
                for (i = x + 1, j = y + 1; i + 1 < NUM && j + 1 < NUM && pieceArr[i][j] == 1 && pieceArr[i + 1][j + 1] != 2; i++, j++) c4++;
                if (count4 <= 4 && c4 <= 2) score[x][y] += 100 * count4;
                if (count4 == 3 && c4 == 3) score[x][y] += 1000;
                if (count4 == 4 && c4 >= 3) score[x][y] += 10000;
                if (count4 == 5) score[x][y] += 10000000;
                pieceArr[x][y] = 0;
            }
        }
    }

    // Find the best move based on score
    int maxVal = score[0][0];
    int maxX = 0, maxY = 0;
    for (int i = 0; i < NUM; i++) {
        for (int j = 0; j < NUM; j++) {
            if (score[i][j] > maxVal) {
                maxVal = score[i][j];
                maxX = i;
                maxY = j;
            }
        }
    }
    Draw_piece(1, maxX, maxY);
    history[historyIndex].x = maxX;
    history[historyIndex].y = maxY;
    history[historyIndex].color = 1;
    historyIndex++;

    int n = GameOver(40 * maxX, 40 * maxY);
    if (n == 1) {
        settextcolor(BROWN);
        settextstyle(36, 0, _T("Consolas"));
        outtextxy(250, 0, _T("黑棋赢了"));
        replay();
    }
    else if (n == 2) {
        settextcolor(BROWN);
        settextstyle(36, 0, _T("Consolas"));
        outtextxy(250, 0, _T("白棋赢了"));
        replay();
    }
}
// AI function for white player
void WHITE_AI_DRAW() {
    int score[NUM][NUM] = { 1 };
    for (int x = 0; x < NUM; x++) {
        for (int y = 0; y < NUM; y++) {
            int h1 = 0, h2 = 0, h3 = 0, h4 = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0, p1 = 0, p2 = 0, p3 = 0, p4 = 0, o1 = 0, o2 = 0, o3 = 0, o4 = 0;
            int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
            int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
            int i = 0, j = 0;
            if (pieceArr[x][y] == 2) score[x][y] = 0;
            else if (pieceArr[x][y] == 1) {
                // Defense logic
                score[x][y] = 0;
                for (i = x; i >= 0 && pieceArr[i][y] == 1 && pieceArr[i - 1][y] != 2; i--) h1++;
                for (i = x; i < NUM && pieceArr[i][y] == 1 && pieceArr[i + 1][y] != 2; i++) h2++;
                for (i = x; i >= 0 && pieceArr[i][y] == 1; i--) h3++;
                for (i = x; i < NUM && pieceArr[i][y] == 1; i++) h4++;
                if (h1 == 3 && h3 == 4 && pieceArr[x + 1][y] == 0) score[x + 1][y] += 4000000;
                if (h2 == 3 && h4 == 4 && pieceArr[x - 1][y] == 0) score[x - 1][y] += 4000000;
                if (h1 == 3 && h3 == 3 && pieceArr[x + 1][y] == 0) score[x + 1][y] += 40000;
                if (h2 == 3 && h4 == 3 && pieceArr[x - 1][y] == 0) score[x - 1][y] += 40000;
                if (h1 == 2 && pieceArr[x + 1][y] == 0) score[x + 1][y] += 4000;
                if (h2 == 2 && pieceArr[x - 1][y] == 0) score[x - 1][y] += 4000;
                if (h1 == 1 && pieceArr[x + 1][y] == 0) score[x + 1][y] += 1000;
                if (h2 == 1 && pieceArr[x - 1][y] == 0) score[x - 1][y] += 1000;
                for (j = y; j >= 0 && pieceArr[x][j] == 1 && pieceArr[x][j - 1] != 2; j--) s1++;
                for (j = y; j < NUM && pieceArr[x][j] == 1 && pieceArr[x][j + 1] != 2; j++) s2++;
                for (j = y; j >= 0 && pieceArr[x][j] == 1; j--) s3++;
                for (j = y; j < NUM && pieceArr[x][j] == 1; j++) s4++;
                if (s1 == 3 && s3 == 4 && pieceArr[x][y + 1] == 0) score[x][y + 1] += 4000000;
                if (s2 == 3 && s4 == 4 && pieceArr[x][y - 1] == 0) score[x][y - 1] += 4000000;
                if (s1 == 3 && s3 == 3 && pieceArr[x][y + 1] == 0) score[x][y + 1] += 40000;
                if (s2 == 3 && s4 == 3 && pieceArr[x][y - 1] == 0) score[x][y - 1] += 40000;
                if (s1 == 2 && pieceArr[x][y + 1] == 0) score[x][y + 1] += 4000;
                if (s2 == 2 && pieceArr[x][y - 1] == 0) score[x][y - 1] += 4000;
                if (s1 == 1 && pieceArr[x][y + 1] == 0) score[x][y + 1] += 1000;
                if (s2 == 1 && pieceArr[x][y - 1] == 0) score[x][y - 1] += 1000;
                for (i = x, j = y; i < NUM && j >= 0 && pieceArr[i][j] == 1 && pieceArr[i + 1][j - 1] != 2; i++, j--) p1++;
                for (i = x, j = y; i >= 0 && j < NUM && pieceArr[i][j] == 1 && pieceArr[i - 1][j + 1] != 2; i--, j++) p2++;
                for (i = x, j = y; i < NUM && j >= 0 && pieceArr[i][j] == 1; i++, j--) p3++;
                for (i = x, j = y; i >= 0 && j < NUM && pieceArr[i][j] == 1; i--, j++) p4++;
                if (p1 == 3 && p3 == 4 && pieceArr[x - 1][y + 1] == 0) score[x - 1][y + 1] += 4000000;
                if (p2 == 3 && p4 == 4 && pieceArr[x + 1][y - 1] == 0) score[x + 1][y - 1] += 4000000;
                if (p1 == 3 && p3 == 3 && pieceArr[x - 1][y + 1] == 0) score[x - 1][y + 1] += 40000;
                if (p2 == 3 && p4 == 3 && pieceArr[x + 1][y - 1] == 0) score[x + 1][y - 1] += 40000;
                if (p1 == 2 && pieceArr[x - 1][y + 1] == 0) score[x - 1][y + 1] += 4000;
                if (p2 == 2 && pieceArr[x + 1][y - 1] == 0) score[x + 1][y - 1] += 4000;
                if (p1 == 1 && pieceArr[x - 1][y + 1] == 0) score[x - 1][y + 1] += 1000;
                if (p2 == 1 && pieceArr[x + 1][y - 1] == 0) score[x + 1][y - 1] += 1000;
                for (i = x, j = y; i >= 0 && j >= 0 && pieceArr[i][j] == 1 && pieceArr[i - 1][j - 1] != 2; i--, j--) o1++;
                for (i = x, j = y; i < NUM && j < NUM && pieceArr[i][j] == 1 && pieceArr[i + 1][j + 1] != 2; i++, j++) o2++;
                for (i = x, j = y; i >= 0 && j >= 0 && pieceArr[i][j] == 1; i--, j--) o3++;
                for (i = x, j = y; i < NUM && j < NUM && pieceArr[i][j] == 1; i++, j++) o4++;
                if (o1 == 3 && o3 == 4 && pieceArr[x + 1][y + 1] == 0) score[x + 1][y + 1] += 4000000;
                if (o2 == 3 && o4 == 4 && pieceArr[x - 1][y - 1] == 0) score[x - 1][y - 1] += 4000000;
                if (o1 == 3 && o3 == 3 && pieceArr[x + 1][y + 1] == 0) score[x + 1][y + 1] += 40000;
                if (o2 == 3 && o4 == 3 && pieceArr[x - 1][y - 1] == 0) score[x - 1][y - 1] += 40000;
                if (o1 == 2 && pieceArr[x + 1][y + 1] == 0) score[x + 1][y + 1] += 4000;
                if (o2 == 2 && pieceArr[x - 1][y - 1] == 0) score[x - 1][y - 1] += 4000;
                if (o1 == 1 && pieceArr[x + 1][y + 1] == 0) score[x + 1][y + 1] += 1000;
                if (o2 == 1 && pieceArr[x - 1][y - 1] == 0) score[x - 1][y - 1] += 1000;
            }
            else if (pieceArr[x][y] == 0) {
                // Attack logic
                pieceArr[x][y] = 2;
                for (i = x; i >= 0 && pieceArr[i][y] == 2; i--) count1++;
                for (i = x + 1; i < NUM && pieceArr[i][y] == 2; i++) count1++;
                for (i = x; i - 1 >= 0 && pieceArr[i][y] == 2 && pieceArr[i - 1][y] != 1; i--) c1++;
                for (i = x + 1; i + 1 < NUM && pieceArr[i][y] == 2 && pieceArr[i + 1][y] != 1; i++) c1++;
                if (count1 <= 4 && c1 <= 2) score[x][y] += 100 * count1;
                if (count1 == 3 && c1 == 3) score[x][y] += 1000;
                if (count1 == 4 && c1 >= 3) score[x][y] += 10000;
                if (count1 == 5) score[x][y] += 10000000;
                count1 = 0; c1 = 0;
                for (j = y; j >= 0 && pieceArr[x][j] == 2; j--) count2++;
                for (j = y + 1; j < NUM && pieceArr[x][j] == 2; j++) count2++;
                for (j = y; j - 1 >= 0 && pieceArr[x][j] == 2 && pieceArr[x][j - 1] != 1; j--) c2++;
                for (j = y + 1; j + 1 < NUM && pieceArr[x][j] == 2 && pieceArr[x][j + 1] != 1; j++) c2++;
                if (count2 <= 4 && c2 <= 2) score[x][y] += 100 * count2;
                if (count2 == 3 && c2 == 3) score[x][y] += 1000;
                if (count2 == 4 && c2 >= 3) score[x][y] += 10000;
                if (count2 == 5) score[x][y] += 10000000;
                count2 = 0; c2 = 0;
                for (i = x, j = y; i < NUM && j >= 0 && pieceArr[i][j] == 2; i++, j--) count3++;
                for (i = x - 1, j = y + 1; i >= 0 && j < NUM && pieceArr[i][j] == 2; i--, j++) count3++;
                for (i = x, j = y; i + 1 < NUM && j - 1 >= 0 && pieceArr[i][j] == 2 && pieceArr[i + 1][j - 1] != 1; i++, j--) c3++;
                for (i = x - 1, j = y + 1; i - 1 >= 0 && j + 1 < NUM && pieceArr[i][j] == 2 && pieceArr[i - 1][j + 1] != 1; i--, j++) c3++;
                if (count3 <= 4 && c3 <= 2) score[x][y] += 100 * count3;
                if (count3 == 3 && c3 == 3) score[x][y] += 1000;
                if (count3 == 4 && c3 >= 3) score[x][y] += 10000;
                if (count3 == 5) score[x][y] += 10000000;
                count3 = 0; c3 = 0;
                for (i = x, j = y; i >= 0 && j >= 0 && pieceArr[i][j] == 2; i--, j--) count4++;
                for (i = x + 1, j = y + 1; i < NUM && j < NUM && pieceArr[i][j] == 2; i++, j++) count4++;
                for (i = x, j = y; i - 1 >= 0 && j - 1 >= 0 && pieceArr[i][j] == 2 && pieceArr[i - 1][j - 1] != 1; i--, j--) c4++;
                for (i = x + 1, j = y + 1; i + 1 < NUM && j + 1 < NUM && pieceArr[i][j] == 2 && pieceArr[i + 1][j + 1] != 1; i++, j++) c4++;
                if (count4 <= 4 && c4 <= 2) score[x][y] += 100 * count4;
                if (count4 == 3 && c4 == 3) score[x][y] += 1000;
                if (count4 == 4 && c4 >= 3) score[x][y] += 10000;
                if (count4 == 5) score[x][y] += 10000000;
                pieceArr[x][y] = 0;
            }
        }
    }

    // Find the best move based on score
    int maxVal = score[0][0];
    int maxX = 0, maxY = 0;
    for (int i = 0; i < NUM; i++) {
        for (int j = 0; j < NUM; j++) {
            if (score[i][j] > maxVal) {
                maxVal = score[i][j];
                maxX = i;
                maxY = j;
            }
        }
    }
    Draw_piece(2, maxX, maxY);
    history[historyIndex].x = maxX;
    history[historyIndex].y = maxY;
    history[historyIndex].color = 2;
    historyIndex++;

    int n = GameOver(40 * maxX, 40 * maxY);
    if (n == 1) {
        settextcolor(BROWN);
        settextstyle(36, 0, _T("Consolas"));
        outtextxy(250, 0, _T("黑棋赢了"));
        replay();
    }
    else if (n == 2) {
        settextcolor(BROWN);
        settextstyle(36, 0, _T("Consolas"));
        outtextxy(250, 0, _T("白棋赢了"));
        replay();
    }
}
// Main game loop
int main() {
    initgraph(650, 650);  // Create graphics window
    ExMessage m;

    option();
    int color = 1;  // Black plays first (1 for black, 2 for white)
    bool gameStarted = false, AI_BLACKgameStarted = false, AI_WHITEgameStarted = false;

    while (1) {
        m = getmessage(EX_MOUSE);
        if (m.message == WM_LBUTTONDOWN) {
            if (m.x >= 140 && m.x <= 540 && m.y >= 200 && m.y <= 300) {
                gameStarted = true;
                loadimage(NULL, _T("2.png"));
                Draw_line();
                Draw_point();
                function();
                break;
            }
            else if (m.x >= 140 && m.x <= 540 && m.y >= 400 && m.y <= 500) {
                settextcolor(WHITE);
                settextstyle(100, 0, _T("Consolas"));
                outtextxy(125, 200, _T("我走先手"));
                outtextxy(125, 400, _T("我走后手"));
                while (1) {
                    m = getmessage(EX_MOUSE);
                    if (m.message == WM_LBUTTONDOWN) {
                        if (m.x >= 140 && m.x <= 540 && m.y >= 200 && m.y <= 300) {
                            AI_WHITEgameStarted = true;
                            loadimage(NULL, _T("2.png"));
                            Draw_line();
                            Draw_point();
                            function();
                            break;
                        }
                        else if (m.x >= 140 && m.x <= 540 && m.y >= 400 && m.y <= 500) {
                            AI_BLACKgameStarted = true;
                            loadimage(NULL, _T("2.png"));
                            Draw_line();
                            Draw_point();
                            function();
                            Draw_piece_record_history(true, 40 * 7, 40 * 7); // AI starts with black at center
                            color = 2;  // Human plays white next
                            break;
                        }
                    }
                }
                break;
            }
        }
    }

    while (gameStarted || AI_BLACKgameStarted || AI_WHITEgameStarted) {
        m = getmessage(EX_MOUSE);
        if (m.message == WM_LBUTTONDOWN) {
            if (NicePos(m.x, m.y)) {
                // Record and draw human move
                Draw_piece_record_history(color == 1, m.x, m.y);

                int n = GameOver(m.x, m.y);
                if (n != 0) {
                    settextcolor(BROWN);
                    settextstyle(36, 0, _T("Consolas"));
                    outtextxy(250, 0, n == 1 ? _T("黑棋赢了") : _T("白棋赢了"));
                    replay();
                    break;
                }

                // Switch to the next color
                color = (color == 1) ? 2 : 1;

                if (AI_BLACKgameStarted) {
                    if (color == 1) {  // AI's turn to play black
                        Sleep(300);
                        BLACK_AI_DRAW();
                        n = GameOver(40 * history[historyIndex - 1].x, 40 * history[historyIndex - 1].y);
                        if (n != 0) {
                            settextcolor(BROWN);
                            settextstyle(36, 0, _T("Consolas"));
                            outtextxy(250, 0, n == 1 ? _T("黑棋赢了") : _T("白棋赢了"));
                            replay();
                            break;
                        }
                        color = 2;  // Switch back to human's turn (white)
                    }
                }
                else if (AI_WHITEgameStarted) {
                    if (color == 2) {  // AI's turn to play white
                        Sleep(300);
                        WHITE_AI_DRAW();
                        n = GameOver(40 * history[historyIndex - 1].x, 40 * history[historyIndex - 1].y);
                        if (n != 0) {
                            settextcolor(BROWN);
                            settextstyle(36, 0, _T("Consolas"));
                            outtextxy(250, 0, n == 1 ? _T("黑棋赢了") : _T("白棋赢了"));
                            replay();
                            break;
                        }
                        color = 1;  // Switch back to human's turn (black)
                    }
                }
            }
            else if (m.x >= 200 && m.x <= 280 && m.y >= 600 && m.y <= 640) {
                Undo_move();
                // Determine the correct color after undo
                color = (historyIndex > 0) ? (history[historyIndex].color == 1 ? 2 : 1) : 1;  // If we've undone all moves, start with black
                clearcliprgn();
                loadimage(NULL, _T("2.png"));
                Draw_line();
                Draw_point();
                function();
                for (int i = 0; i < historyIndex; i++) {
                    Draw_piece(history[i].color, history[i].x, history[i].y);
                }
                continue;
            }
        }
    }

    return 0;
}