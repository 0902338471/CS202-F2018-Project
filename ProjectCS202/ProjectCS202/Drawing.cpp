#include "Drawing.h"
#include "LibraryPro.h"
void cls()
{
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void move_reverse_dog_by5(int x, int y)
{
	//x=50;y=20;
	gotoxy(x, y); cout << " ";
	for (int i = x - 1; i > x - 5; --i)
	{
		gotoxy(i, y);
		cout << " ";
	}
	for (int i = x - 1; i > x - 6; --i)
	{
		gotoxy(i, y + 1);
		cout << " ";
	}
	gotoxy(x - 1, y + 2); cout << " ";
	gotoxy(x - 2, y + 2); cout << " ";
	gotoxy(x - 8, y + 2); cout << " ";
	for (int i = x - 6; i > x - 10; --i)
	{
		gotoxy(i, y - 1);
		cout << " ";
	}
}
void drawGreenLight(int ycor)
{
	char a = 219;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	if (ycor == 0) ycor++;
	gotoxy(RightEdge, ycor);
	cout << a << a;
}
void drawRedLight(int ycor)
{
	char a = 219;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 28);
	if (ycor == 0) ycor++;
	gotoxy(RightEdge, ycor);
	cout << a << a;
}
void move_car_by5(int x, int y)
{
	//x=50, y=20
	for (int i = x; i < x + 5; ++i)
	{
		gotoxy(i, y);
		cout << " ";
	}
	for (int i = x + 3; i < x + 8; ++i)
	{
		gotoxy(i, y - 1);
		cout << " ";
	}
	for (int i = x; i < x + 5; ++i)
	{
		gotoxy(i, y + 1);
		cout << " ";
	}
	gotoxy(x + 3, y + 2); cout << " ";
	gotoxy(x + 4, y + 2); cout << " ";
	gotoxy(x + 5, y + 2); cout << " ";
	for (int i = x + 14; i < x + 17; ++i)
	{
		gotoxy(i, y + 2);
		cout << " ";
	}
}
void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void move_reverse_dog(int x, int y)
{
	gotoxy(x, y); cout << " ";
	gotoxy(x - 1, y + 1); cout << " ";
	gotoxy(x - 1, y + 2); cout << " ";
	gotoxy(x - 6, y - 1); cout << " ";
	gotoxy(x - 7, y + 2); cout << " ";
}
void move_car(int x, int y)
{
	gotoxy(x, y); cout << " ";
	gotoxy(x, y + 1); cout << " ";
	gotoxy(x + 3, y - 1); cout << " ";
	gotoxy(x + 3, y + 2); cout << " ";
	gotoxy(x + 14, y + 2); cout << " ";
}
void drawcar(int x, int y, int color)
{
	//int color = rand() % 2 + 12;
	char a = 219, b = 220, c = 223;
	gotoxy(x, y + 1);
	// dai 20, cao 4
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << a;
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	cout << b;
	gotoxy(x + 1, y); cout << a;
	gotoxy(x + 1, y + 1); cout << a;
	gotoxy(x + 2, y); cout << a;
	gotoxy(x + 2, y + 1); cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	for (int i = x + 3; i < x + 6; ++i)
	{
		gotoxy(i, y + 1); cout << a;
		gotoxy(i, y + 2); cout << c;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = x + 3; i < x + 8; ++i)
	{
		gotoxy(i, y); cout << a;
	}
	for (int i = x + 3; i < x + 6; ++i)
	{
		gotoxy(i, y - 1); cout << b;
	}
	gotoxy(x + 6, y - 1); cout << a;
	gotoxy(x + 7, y - 1); cout << a;
	gotoxy(x + 6, y + 1); cout << a;
	gotoxy(x + 7, y + 1); cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	for (int i = x + 8; i < x + 13; ++i)
	{
		gotoxy(i, y); cout << a;
		for (int j = x + 8; j < x + 11; ++j)
		{
			gotoxy(j, y - 1); cout << a;
		}
	}
	gotoxy(x + 11, y - 1); cout << b;
	gotoxy(x + 13, y); cout << b;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = x + 8; i < x + 14; ++i)
	{
		gotoxy(i, y + 1); cout << a;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	for (int i = x + 14; i < x + 17; ++i)
	{
		gotoxy(i, y + 1); cout << a;
		gotoxy(i, y + 2); cout << c;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = x + 14; i < x + 18; ++i)
	{
		gotoxy(i, y);
		cout << b;
	}
	gotoxy(x + 17, y + 1); cout << a;
	gotoxy(x + 18, y + 1); cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoxy(x + 19, y + 1); cout << b;

}
void drawAmbuCar(int x, int y)
{
	char a = 219, b = 220, c = 223;
	gotoxy(x, y + 1);
	// dai 16, cao 4
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int i = 0; i < 12; ++i) {
		for (int j = -1; j < 4; ++j) {
			if (j == -1) {
				gotoxy(i + x, j + y); cout << b;
			}
			else {
				gotoxy(i + x, j + y); cout << a;
			}
		}
	}
	for (int i = 0; i < 12; ++i) {
		gotoxy(i + x, y + 3); cout << c;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	gotoxy(x + 5, y); cout << a;
	gotoxy(x + 6, y); cout << a;
	for (int i = 3; i <= 8; ++i) {
		gotoxy(x + i, y + 1); cout << a;
	}
	gotoxy(x + 5, y + 2); cout << a;
	gotoxy(x + 6, y + 2); cout << a;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(x + 1, y + 3); cout << a;
	gotoxy(x + 2, y + 3); cout << a;

	gotoxy(x + 9, y + 3); cout << a;
	gotoxy(x + 10, y + 3); cout << a;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(x + 12, y + 1); cout << a;
	gotoxy(x + 12, y + 2); cout << a;
	gotoxy(x + 13, y + 1); cout << a;
	gotoxy(x + 13, y + 2); cout << a;
	gotoxy(x + 12, y + 3); cout << a;
	gotoxy(x + 13, y + 3); cout << a;
	gotoxy(x + 12, y + 3); cout << c;
	gotoxy(x + 13, y + 3); cout << c;
}
void drawcarSpace(int x, int y, int color)
{
	//int color = rand() % 2 + 12;
	char a=' ', b = ' ', c = ' ';
	gotoxy(x, y + 1);
	// dai 20, cao 4
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << a;
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	cout << b;
	gotoxy(x + 1, y); cout << a;
	gotoxy(x + 1, y + 1); cout << a;
	gotoxy(x + 2, y); cout << a;
	gotoxy(x + 2, y + 1); cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	for (int i = x + 3; i < x + 6; ++i)
	{
		gotoxy(i, y + 1); cout << a;
		gotoxy(i, y + 2); cout << c;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = x + 3; i < x + 8; ++i)
	{
		gotoxy(i, y); cout << a;
	}
	for (int i = x + 3; i < x + 6; ++i)
	{
		gotoxy(i, y - 1); cout << b;
	}
	gotoxy(x + 6, y - 1); cout << a;
	gotoxy(x + 7, y - 1); cout << a;
	gotoxy(x + 6, y + 1); cout << a;
	gotoxy(x + 7, y + 1); cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	for (int i = x + 8; i < x + 13; ++i)
	{
		gotoxy(i, y); cout << a;
		for (int j = x + 8; j < x + 11; ++j)
		{
			gotoxy(j, y - 1); cout << a;
		}
	}
	gotoxy(x + 11, y - 1); cout << b;
	gotoxy(x + 13, y); cout << b;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = x + 8; i < x + 14; ++i)
	{
		gotoxy(i, y + 1); cout << a;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	for (int i = x + 14; i < x + 17; ++i)
	{
		gotoxy(i, y + 1); cout << a;
		gotoxy(i, y + 2); cout << c;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = x + 14; i < x + 18; ++i)
	{
		gotoxy(i, y);
		cout << b;
	}
	gotoxy(x + 17, y + 1); cout << a;
	gotoxy(x + 18, y + 1); cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoxy(x + 19, y + 1); cout << b;

}
void drawdog(int x, int y)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(x, y);// x=50, y=20
				 // do dai cua con cho la 9, do cao la 4
	char a = 219, b = 220, c = 223;
	cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	for (int i = y; i < y + 3; ++i)
	{
		gotoxy(x + 1, i);
		cout << a;
	}
	gotoxy(x + 2, y);
	cout << b;
	gotoxy(x + 2, y + 1);
	cout << a;
	gotoxy(x + 2, y + 2);
	cout << c;
	gotoxy(x + 3, y); cout << b;
	gotoxy(x + 3, y + 1); cout << a;
	gotoxy(x + 4, y); cout << b;
	gotoxy(x + 4, y + 1); cout << a;
	gotoxy(x + 5, y); cout << a;
	gotoxy(x + 5, y + 1); cout << a;
	gotoxy(x + 6, y); cout << a;
	gotoxy(x + 6, y + 1); cout << a;
	gotoxy(x + 6, y - 1); cout << b;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	gotoxy(x + 7, y - 1); cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	for (int i = y; i < y + 2; ++i)
	{
		gotoxy(x + 7, i); cout << a;
	}
	gotoxy(x + 7, y + 2); cout << c;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoxy(x + 8, y - 1); cout << a;
	gotoxy(x + 8, y); cout << b;
	gotoxy(x + 8, y + 1); cout << a;
	gotoxy(x + 8, y + 2); cout << a;
	gotoxy(x + 9, y - 1); cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	gotoxy(x + 9, y); cout << a;
}
void drawplayer(int x, int y)
{
	char a = 219, b = 220, c = 223, d = 221, e = 222;
	gotoxy(x, y);//x=50,y=20
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << a << a;
	gotoxy(x - 1, y + 1);
	cout << d;
	gotoxy(x + 2, y + 1);
	cout << e;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	gotoxy(x, y + 1);
	cout << a << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	gotoxy(x, y + 2);
	cout << d;
	gotoxy(x + 1, y + 2); cout << e;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	gotoxy(x, y - 1); cout << b << b;
}
void drawplayerSpace(int x, int y)
{
	gotoxy(x, y);//x=50,y=20
	char a = ' ', b = ' ', c = ' ', d = ' ', e = ' ';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << a << a;
	gotoxy(x - 1, y + 1);
	cout << d;
	gotoxy(x + 2, y + 1);
	cout << e;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	gotoxy(x, y + 1);
	cout << a << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	gotoxy(x, y + 2);
	cout << d;
	gotoxy(x + 1, y + 2); cout << e;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	gotoxy(x, y - 1); cout << b << b;
}
void draw_reverse_dog(int x, int y, int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(x, y);// x=50, y=20
				 // do dai cua con cho la 9, do cao la 4
	char a = 219, b = 220, c = 223;
	cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = y; i < y + 3; ++i)
	{
		gotoxy(x - 1, i);
		cout << a;
	}
	gotoxy(x - 2, y);
	cout << b;
	gotoxy(x - 2, y + 1);
	cout << a;
	gotoxy(x - 2, y + 2);
	cout << c;
	gotoxy(x - 3, y); cout << b;
	gotoxy(x - 3, y + 1); cout << a;
	gotoxy(x - 4, y); cout << b;
	gotoxy(x - 4, y + 1); cout << a;
	gotoxy(x - 5, y); cout << a;
	gotoxy(x - 5, y + 1); cout << a;
	gotoxy(x - 6, y); cout << a;
	gotoxy(x - 6, y + 1); cout << a;
	gotoxy(x - 6, y - 1); cout << b;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	gotoxy(x - 7, y - 1); cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = y; i < y + 2; ++i)
	{
		gotoxy(x - 7, i); cout << a;
	}
	gotoxy(x - 7, y + 2); cout << c;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	gotoxy(x - 8, y - 1); cout << a;
	gotoxy(x - 8, y); cout << b;
	gotoxy(x - 8, y + 1); cout << a;
	gotoxy(x - 8, y + 2); cout << a;
	gotoxy(x - 9, y - 1); cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	gotoxy(x - 9, y); cout << a;

}
void draw_reverse_dogSpace(int x, int y, int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(x, y);// x=50, y=20
				 // do dai cua con cho la 9, do cao la 4
	char a =' ', b = ' ', c = ' ';
	cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = y; i < y + 3; ++i)
	{
		gotoxy(x - 1, i);
		cout << a;
	}
	gotoxy(x - 2, y);
	cout << b;
	gotoxy(x - 2, y + 1);
	cout << a;
	gotoxy(x - 2, y + 2);
	cout << c;
	gotoxy(x - 3, y); cout << b;
	gotoxy(x - 3, y + 1); cout << a;
	gotoxy(x - 4, y); cout << b;
	gotoxy(x - 4, y + 1); cout << a;
	gotoxy(x - 5, y); cout << a;
	gotoxy(x - 5, y + 1); cout << a;
	gotoxy(x - 6, y); cout << a;
	gotoxy(x - 6, y + 1); cout << a;
	gotoxy(x - 6, y - 1); cout << b;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	gotoxy(x - 7, y - 1); cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = y; i < y + 2; ++i)
	{
		gotoxy(x - 7, i); cout << a;
	}
	gotoxy(x - 7, y + 2); cout << c;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	gotoxy(x - 8, y - 1); cout << a;
	gotoxy(x - 8, y); cout << b;
	gotoxy(x - 8, y + 1); cout << a;
	gotoxy(x - 8, y + 2); cout << a;
	gotoxy(x - 9, y - 1); cout << a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	gotoxy(x - 9, y); cout << a;

}
void drawAmbuCarSpace(int x, int y, int color)
{
	//int color = rand() % 2 + 12;
	char a = ' ', b = ' ', c = ' ';
	gotoxy(x, y + 1);
	// dai 16, cao 4
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = 0; i < 12; ++i) {
		for (int j = -1; j < 4; ++j) {
			if (j == -1) {
				gotoxy(i + x, j + y); cout << b;
			}
			else {
				gotoxy(i + x, j + y); cout << a;
			}
		}
	}
	for (int i = 0; i < 12; ++i) {
		gotoxy(i + x, y + 3); cout << c;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	gotoxy(x + 5, y); cout << a;
	gotoxy(x + 6, y); cout << a;
	for (int i = 3; i <= 8; ++i) {
		gotoxy(x + i, y + 1); cout << a;
	}
	gotoxy(x + 5, y + 2); cout << a;
	gotoxy(x + 6, y + 2); cout << a;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	gotoxy(x + 1, y + 3); cout << a;
	gotoxy(x + 2, y + 3); cout << a;

	gotoxy(x + 9, y + 3); cout << a;
	gotoxy(x + 10, y + 3); cout << a;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	gotoxy(x + 12, y + 1); cout << a;
	gotoxy(x + 12, y + 2); cout << a;
	gotoxy(x + 13, y + 1); cout << a;
	gotoxy(x + 13, y + 2); cout << a;
	gotoxy(x + 12, y + 3); cout << a;
	gotoxy(x + 13, y + 3); cout << a;
	gotoxy(x + 12, y + 3); cout << c;
	gotoxy(x + 13, y + 3); cout << c;
}
void move_ambucar_by5(int x, int y)
{
	for (int i = x; i < x + 5; ++i)
	{
		for (int j = y - 1; j < y + 4; ++j)
		{
			gotoxy(i, j);
			cout << " ";
		}
	}
}