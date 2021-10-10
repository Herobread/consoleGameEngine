#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

int delay = 12;
int width = 70;
int height = 40;
wchar_t* screen = new wchar_t[width * height]; // Массив для записи в буфер
HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // Буфер экрана

string button = "";
float x = 10, y = 9;

void cleanBuffer()
{
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            screen[i * width + j] = ' ';
        }
    }
}

void render()
{
    DWORD dwBytesWritten = 0; // Для дебага

    //screen[width * height - 1] = '\0'; // end

    WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten); // Запись в буфер

    cleanBuffer(); // empty
}

string getKey()
{
    string c;
    char b;
    int a;
    a = _getch();
    if (a == 224)
    {
        a = _getch();
        if (a == 75)
        {
            return "leftArrow";
        }
        if (a == 72)
        {
            return "upArrow";
        }
        if (a == 80)
        {
            return "downArrow";
        }
        if (a == 77)
        {
            return "rightArrow";
        }
        if (a == 82)
        {
            return "insert";
        }
    }
    else if (a == 32)
    {
        return "space";
    }
    if (a == 8)
    {
        return "backspace";
    }
    if (a == 9)
    {
        return "tab";
    }
    if (a == 13)
    {
        return "enter";
    }
    if (a == 27)
    {
        return "esc";
    }
    b = a;
    c = b;
    return c;
}

void text(int X, int Y, string text)
{
    for (int i = 0; i < text.size(); i += 1)
    {
        screen[Y * width + X + i] = text[i];
    }
}

void drawSymbol(int X, int Y, char text)
{
    screen[Y * width + X] = text;
}

int main()
{
    //Сначала задаем минимальные значения
    SMALL_RECT zeroWindow = { 0, 0, 10, 10 };
    COORD zBuffer = { 10, 10 };
    SetConsoleWindowInfo(hConsole, TRUE, &zeroWindow);
    SetConsoleScreenBufferSize(hConsole, zBuffer);

    //А уже потом изменяем значения на нужные нам
    COORD bufferSize = { width, height };
    SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
    SetConsoleScreenBufferSize(hConsole, bufferSize);
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    SetConsoleActiveScreenBuffer(hConsole); // Настройка консоли
    cleanBuffer();

    //game vars
    int k = 0;

	while (true)
	{
        button = "";

        if (_kbhit()) // uncomment "if" to each few ms render, comment "if" to logic only after pressing button
            button = getKey();

        // input
        if (GetAsyncKeyState((unsigned short)'W') && y > 0 )
        {
            y -= 0.3;
        }
        if (GetAsyncKeyState((unsigned short)'S') && y < height - 1) // btw u gona subtract 1 because windows bad
        {
            y += 0.3;
        }
        if (GetAsyncKeyState((unsigned short)'A') && x > 0)
        {
            x -= 0.3;
        }
        if (GetAsyncKeyState((unsigned short)'D') && x < width - 1)
        {
            x += 0.3;
        }

        //logic
        if (k < width - 1)
            k += 1;
        else
            k = 0;

        //drawing
        drawSymbol((int)x, (int)y, '@');
        drawSymbol(k, 5, '-');
        text(1, 1, "this is demo game");
        text(1, 2, "use wasd to move");
        text(1, 3, "also it allows to run in pretty big fps, now:" + to_string(1000 / delay));
        text(1, 4, "example:");

        Sleep(delay);
        render();
	}
}