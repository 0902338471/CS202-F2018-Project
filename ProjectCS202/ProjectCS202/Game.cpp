#include "Game.h"
#include "Drawing.h"
#include <thread>
#include <future>
#include <chrono>
#include <mutex>
#include <string>
#include <Windows.h>
#include <mmsystem.h>



mutex m;
condition_variable cv;
bool finishDrawingHuman = true;
promise<void> endSignal;
future<void> futureObj;
thread drawing;
//bool AMBULANCE = false;
CGAME mygame;
bool stop = false;
void callAmBulance()
{
	endSignal.set_value();
	drawing.detach();
	system("cls");
	CAmbu myAmbu;
	while (myAmbu.checkDone() == false)
	{
		//
	}
	gotoxy(75, 25);
	cout << "Game Over" << endl;
	stop = true;
	Sleep(3000);
	std::terminate();
}
void drawAndUpdate(future<void> futureObj) {
	while (futureObj.wait_for(chrono::milliseconds(1)) == future_status::timeout) {
		unique_lock<mutex> lock(m);
		cv.wait(lock, [] {return finishDrawingHuman; });
		mygame.drawVe();
		mygame.drawAni();
		if (mygame.checkCollide())
		{
			//openSound("D:\ProjectCS\Project\ProjectCS202\ProjectCS202\crash.wav", "Crash");
			Sleep(1000);
			//AMBULANCE = true;
			callAmBulance();
			
		}
		mygame.updatePosAnimal();
		mygame.updatePosVehicle();
		//this_thread::sleep_for(chrono::milliseconds(1));
		// Add function to clear animal and vehicles here
	}
}
int main()
{
	FixConsoleWindow();
	HWND console = GetConsoleWindow();
	HDC mydc = GetDC(console);
	COLORREF color = RGB(255, 255, 255);
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	//openSound("D:\ProjectCS\Project\ProjectCS202\ProjectCS202\crash.wav", "Crash");

	MoveWindow(console, r.left, r.top, 1920, 1080, TRUE);
	//menu();
	//new game only
	string menu[4] = { "New game", "Load game", "Settings","Exit" };
	int pointer = 0;
	while (true)
	{
		cls();
		gotoxy(45, 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout << "  ######  ########   #######   ######   ######  ##    ##    ########   #######     ###    ########" << endl;
		gotoxy(45, 3);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << " ##    ## ##     ## ##     ## ##    ## ##    ##  ##  ##     ##     ## ##     ##   ## ##   ##     ##" << endl;
		gotoxy(45, 4);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << " ##       ##     ## ##     ## ##       ##         ####      ##     ## ##     ##  ##   ##  ##     ##" << endl;
		gotoxy(45, 5);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << " ##       ########  ##     ##  ######   ######     ##       ########  ##     ## ##     ## ##     ##" << endl;
		gotoxy(45, 6);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		cout << " ##       ##   ##   ##     ##       ##       ##    ##       ##   ##   ##     ## ######### ##     ##" << endl;
		gotoxy(45, 7);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << " ##    ## ##    ##  ##     ## ##    ## ##    ##    ##       ##    ##  ##     ## ##     ## ##     ##" << endl;
		gotoxy(45, 8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "  ######  ##     ##  #######   ######   ######     ##       ##     ##  #######  ##     ## ########" << endl;
		gotoxy(80, 20);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int i = 0; i < 4; ++i)
		{
			gotoxy(80, 20 + i);
			if (i == pointer)
			{

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				cout << menu[i] << endl;
			}
			else
			{
				//gotoxy(100, 21);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << menu[i] << endl;
			}
		}
		bool NewMenu = false;

		while (true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
					pointer = 3;
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 4)
					pointer = 0;
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{
				case 0:
				{
					//mygame = CGAME();
					cls();
					mygame.newGame();
					//drawing.join();
					endSignal = promise<void>();
					futureObj = endSignal.get_future();
					drawing = thread(&drawAndUpdate, move(futureObj));
					while (true) {
						int tmp = mygame.Handle(finishDrawingHuman, cv, m);
						//if (!finishDrawingHuman) cout << "DONE" << endl;
						if (tmp == NextLevelStatus) {
							endSignal.set_value();
							drawing.detach();
							system("CLS");
							Sleep(1000);
							mygame.clearScreenAndCreateNewLevel();
							mygame.turnOffNextLevel();
							endSignal = promise<void>();
							futureObj = endSignal.get_future();
							drawing = thread(&drawAndUpdate, move(futureObj));
						}
						//Sleep(100);
						else if (tmp == NewGameStatus)
						{
							
							NewMenu = true;
							break;
						}
					}
					//finishDrawingHuman = true;
					endSignal.set_value();
					drawing.detach();
					//Sleep(100);
				}break;
				case 1:
				{
					cls();
					ifstream fin("Gameload.bin", ios::binary);
					mygame.loadGame(fin);
					//cls();
					//drawing.join();
					mygame.DrawingLanes(true);
					mygame.drawHuman();
					finishDrawingHuman = true;
					endSignal = promise<void>();
					futureObj = endSignal.get_future();
					drawing = thread(&drawAndUpdate, move(futureObj));
					while (true) {
						int tmp = mygame.Handle(finishDrawingHuman, cv, m);
						//if (!finishDrawingHuman) cout << "DONE" << endl;
						if (tmp == NextLevelStatus) {
							endSignal.set_value();
							drawing.detach();
							system("CLS");
							Sleep(1000);
							mygame.clearScreenAndCreateNewLevel();
							mygame.turnOffNextLevel();
							endSignal = promise<void>();
							futureObj = endSignal.get_future();
							drawing = thread(&drawAndUpdate, move(futureObj));
						}
						//Sleep(100);
						else if (tmp == NewGameStatus)
						{
							NewMenu = true;
							break;
						}
					}
					//finishDrawingHuman = true;
					endSignal.set_value();
					drawing.detach();
					//Sleep(100);
				}break;
				case 2:
				{
					int key;
					do
					{
						cls();
						cout << "1.Turn on Sounds" << endl;
						cout << "2.Turn off Sounds" << endl;
						cin >> key;
					} while (key != 1 && key != 2);
					if (key == 1)
						//Turn on
					{

					}
					else  
						//Turn off
					Sleep(1000);
				}
				case 3:
				{
					return 0;
				}break;
				}
				break;
			}
			Sleep(500);
		}

		if (NewMenu)
			continue;

	}
	endSignal.set_value();
	drawing.detach();
	/*endSignal = promise<void>();
	futureObj = endSignal.get_future();
	drawing = thread(&drawAndUpdate, move(futureObj));



	while (true) {
		bool tmp = mygame.Handle(finishDrawingHuman, cv, m);
		//if (!finishDrawingHuman) cout << "DONE" << endl;
		if (tmp) {
		endSignal.set_value();
		drawing.join();
		system("CLS");
		Sleep(1000);
		mygame.clearScreenAndCreateNewLevel();
		mygame.turnOffNextLevel();
		endSignal = promise<void>();
		futureObj = endSignal.get_future();
		drawing = thread(&drawAndUpdate, move(futureObj));
		}
		//Sleep(100);
	}*/


	//mygame.drawGame();
}