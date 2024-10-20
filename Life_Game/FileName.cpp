#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

int r, c; // 게임판 크기

// 커서 숨김, 보임 조절
void CursorView(BOOL b)
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = b; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 글자 배경색 설정 위한 열거형
enum Color
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

// 글자, 배경 색 조정
void textcolor(int foreground, int background)
{
    int color = foreground + background * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

vector<vector<bool>> board; // 게임판

// 게임판 초기화
void initializeBoard()
{
    srand((unsigned)time(NULL)); // rand 초기화
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            board[i][j] = (rand() % 10 < 3); // 30%의 확률로 살아있는 셀로 초기화
}

// 게임판 출력
void printBoard()
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (board[i][j])
            {
                textcolor(BLACK, WHITE); // 글씨 black, 배경 white
                cout << "  ";
            }
            else
            {
                textcolor(WHITE, BLACK); // 글씨 white, 배경 black
                cout << "  ";
            }
        }
        textcolor(WHITE, BLACK); // 글씨 white, 배경 black
        cout << '\n';
    }
}

// 다음 세대
void calculateNextGeneration()
{
    vector<vector<bool>> newBoard(r, vector<bool>(c, false));
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int neighbors = 0;
            // 이웃하는 셀의 수
            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++)
                {
                    if (di == 0 && dj == 0)
                        continue; // 현재 셀은 제외
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < r && nj >= 0 && nj < c && board[ni][nj])
                        neighbors++;
                }
            // 생존, 번식 규칙 적용
            if (board[i][j])
                newBoard[i][j] = (neighbors == 2 || neighbors == 3);
            else
                newBoard[i][j] = (neighbors == 3);
        }
    }
    // 새로운 게임판으로 업데이트
    board = newBoard;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int g;
    textcolor(WHITE, BLACK); // 글씨 white, 배경 black
    cout << "rows        : ";
    cin >> r;
    cout << "columns     : ";
    cin >> c;
    cout << "generations : ";
    cin >> g;
    board.resize(r, vector<bool>(c, false)); // r * c, false로 게임판 초기화
    Sleep(300);
    CursorView(FALSE); // 커서 숨김
    initializeBoard(); // 초기화
    int generation = 0;
    while (1)
    {
        textcolor(WHITE, BLACK); // 글씨 white, 배경 black
        system("cls"); // 화면 지우기
        cout << generation << " / " << g << '\n';
        printBoard();
        calculateNextGeneration();
        if (g == generation)
        {
            char c;
            int generation_add;
            CursorView(TRUE); // 커서 보임
            textcolor(WHITE, BLACK); // 글씨 white, 배경 black
            cout << "continue? (Y / N) : "; // 입력된 세대가 끝났을 때 계속할지
            cin >> c; // Y / N 입력
            if (c == 'Y' || c == 'y' || c == '1') // 계속
            {
                cout << "add generations : ";
                cin >> generation_add;
                g += generation_add;
                CursorView(FALSE); // 커서 숨김
            }
            else // 중단
                break;
        }
        generation++;
        Sleep(300);
    }
    return 0;
}