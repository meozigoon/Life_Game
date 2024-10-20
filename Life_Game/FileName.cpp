#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

int r, c; // ������ ũ��

// Ŀ�� ����, ���� ����
void CursorView(BOOL b)
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
    cursorInfo.bVisible = b; //Ŀ�� Visible TRUE(����) FALSE(����)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// ���� ���� ���� ���� ������
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

// ����, ��� �� ����
void textcolor(int foreground, int background)
{
    int color = foreground + background * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

vector<vector<bool>> board; // ������

// ������ �ʱ�ȭ
void initializeBoard()
{
    srand((unsigned)time(NULL)); // rand �ʱ�ȭ
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            board[i][j] = (rand() % 10 < 3); // 30%�� Ȯ���� ����ִ� ���� �ʱ�ȭ
}

// ������ ���
void printBoard()
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (board[i][j])
            {
                textcolor(BLACK, WHITE); // �۾� black, ��� white
                cout << "  ";
            }
            else
            {
                textcolor(WHITE, BLACK); // �۾� white, ��� black
                cout << "  ";
            }
        }
        textcolor(WHITE, BLACK); // �۾� white, ��� black
        cout << '\n';
    }
}

// ���� ����
void calculateNextGeneration()
{
    vector<vector<bool>> newBoard(r, vector<bool>(c, false));
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int neighbors = 0;
            // �̿��ϴ� ���� ��
            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++)
                {
                    if (di == 0 && dj == 0)
                        continue; // ���� ���� ����
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < r && nj >= 0 && nj < c && board[ni][nj])
                        neighbors++;
                }
            // ����, ���� ��Ģ ����
            if (board[i][j])
                newBoard[i][j] = (neighbors == 2 || neighbors == 3);
            else
                newBoard[i][j] = (neighbors == 3);
        }
    }
    // ���ο� ���������� ������Ʈ
    board = newBoard;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int g;
    textcolor(WHITE, BLACK); // �۾� white, ��� black
    cout << "rows        : ";
    cin >> r;
    cout << "columns     : ";
    cin >> c;
    cout << "generations : ";
    cin >> g;
    board.resize(r, vector<bool>(c, false)); // r * c, false�� ������ �ʱ�ȭ
    Sleep(300);
    CursorView(FALSE); // Ŀ�� ����
    initializeBoard(); // �ʱ�ȭ
    int generation = 0;
    while (1)
    {
        textcolor(WHITE, BLACK); // �۾� white, ��� black
        system("cls"); // ȭ�� �����
        cout << generation << " / " << g << '\n';
        printBoard();
        calculateNextGeneration();
        if (g == generation)
        {
            char c;
            int generation_add;
            CursorView(TRUE); // Ŀ�� ����
            textcolor(WHITE, BLACK); // �۾� white, ��� black
            cout << "continue? (Y / N) : "; // �Էµ� ���밡 ������ �� �������
            cin >> c; // Y / N �Է�
            if (c == 'Y' || c == 'y' || c == '1') // ���
            {
                cout << "add generations : ";
                cin >> generation_add;
                g += generation_add;
                CursorView(FALSE); // Ŀ�� ����
            }
            else // �ߴ�
                break;
        }
        generation++;
        Sleep(300);
    }
    return 0;
}