#ifndef _Game_
#define _Game_
#include "LibraryPro.h"
#include "Object.h"
#include "People.h"
#include "Drawing.h"
#include "CTRAFFICLIGHT.h"
#include <thread>
#include <future>
#include <chrono>
#include <mutex>

class CGAME {


	vector<CVEHICLE*> VE[10];
	vector<CANIMAL*> ANI[10];
	CLIGHT LIGHT[10];
	CPEOPLE PEOPLE;
	int Curlevel; //6 levels for a game
	int CurFloor;
	bool NextLevel = false;
public:
	CGAME()
	{
		Curlevel = 1;// Set Number Of Vehicle Here
		getPeopleByDefault();
		getVehicleByDefault();
		getAnimalByDefault();
		getLIGHT();
		//CurFloor = 1;
		bool impact = false;
		CPEOPLE tmp = PEOPLE;
		CPEOPLE tmp1;
		//drawHuman();
		//DrawingLanes(true);
		/*while(true)
		{
			//DrawingLanes(false);
			drawAni();
			drawVe();
			drawHuman();
			NotFlickeringPeople(tmp, tmp1);
			updatePosVehicle();
			updatePosAnimal();
			updatePosPeople('W');
			Sleep(1000);
			//Check collide
			/*if (CurFloor % 2 == 0)
				impact = PEOPLE.imPact(VE[CurFloor]);
			else
			if(CurFloor%2!=0)
				impact = PEOPLE.isImpact(ANI[CurFloor]);
			if (impact)
			{
				break;
			}
		}*/
		//system("pause>nil");
		/*drawHuman();
		while (true)
		{
			char c = _getch();
			if (c == 'W' || c == 'A' || c == 'D' || c == 'S'||c=='w'||c=='a'||c=='s'||c=='d')
			{
				if (updatePosPeople(c,NextLevel))
				{
					drawHuman();
					NotFlickeringPeople(tmp, tmp1);
				}
				if (Curlevel == 6)
					break;
			}
		}
		system("cls");
		FinishGames();
		system("pause>nil");*/
	}
	void saveAnimals(ofstream&fout)
	{
		for (int i = 0; i < 10; i++)
		{
			int size = ANI[i].size();
			fout.write((char*)&size, sizeof(int));
			for (int j = 0; j < size; j++)
			{
				saveToFile(fout, *ANI[i][j]);
			}
		}
	}
	void saveVehicles(ofstream&fout)
	{
		for (int i = 0; i < 10; i++)
		{
			int size = VE[i].size();
			fout.write((char*)&size, sizeof(int));
			for (int j = 0; j < size; j++)
			{
				saveToFile(fout, *VE[i][j]);
			}
		}
	}
	bool checkCollide()
	{
		if (CurFloor == 0)
			return false;
		if (CurFloor % 2 == 0)
			return  PEOPLE.imPact(VE[CurFloor]);
		else
			return PEOPLE.isImpact(ANI[CurFloor]);
	}
	bool checkNextLevel()
	{
		return NextLevel;
	}
	void turnOffNextLevel()
	{
		NextLevel = false;
	}

	void getLIGHT()// default light
	{
		LIGHT[2] = CLIGHT(Stop + 100);
		LIGHT[4] = CLIGHT(Stop);
		LIGHT[6] = CLIGHT(Stop + 200);
	}

	int Handle(bool& finishDrawingHuman, condition_variable& cv, mutex& m)
	{
		CPEOPLE OldPos = PEOPLE;//Old Position of PEOPLE
		CPEOPLE CurrentPos;//Current Postition of PEOPLE
		char c = _getch();
		finishDrawingHuman = false;
		cv.notify_one();
		if (c == 'W' || c == 'A' || c == 'D' || c == 'S' || c == 'w' || c == 'a' || c == 's' || c == 'd')
		{
			if (updatePosPeople(c, NextLevel))
			{
				lock_guard<mutex> lock(m);
				drawHuman();
				NotFlickeringPeople(OldPos, CurrentPos);//Set People to that OldPos, Drawing Space People at that postion and then update OldPos to CurrentPos
			}
			finishDrawingHuman = true;
			if (NextLevel)
				return NextLevelStatus;
			return NormalStatus;
		}
		else if (c == 'O' || c == 'o')
		{
			pauseGame();
			finishDrawingHuman = false;
			cv.notify_one();
		}
		else if (c == 'L' || c == 'l')
		{
			//savegame
			finishDrawingHuman = false;
			cv.notify_one();
			ofstream fout("Gameload.bin", ios::binary | ios::trunc);
			saveGame(fout);
			fout.close();
			cls();
			gotoxy(75, 25);
			cout << "Saving game...";
			Sleep(1000);
			cls();
			gotoxy(65, 25);
			cout << "Continued?(1/0)";
			char ch = _getch();
			while (ch != '1' &&ch != '0')
			{
				cls();
				gotoxy(75, 25);
				cout << "Continued?(1/0)";
				ch = _getch();
			}
			if (ch == '0')
			{
				//finishDrawingHuman = false;
				//cv.notify_one();
				return NewGameStatus;
			}
			cls();
			drawHuman();
			return NormalStatus;
		}
		else if (c == 'T' || c == 't')
		{
			//finishDrawingHuman = false;
			//cv.notify_one();
			return NewGameStatus;
		}
		finishDrawingHuman = true;
		return NormalStatus;
	}
	void GameOver()
	{
		system("cls");
		cout << "Game Over";
		Sleep(10000000);
		system("pause");
	}
	void NotFlickeringPeople(CPEOPLE &OldPos, CPEOPLE&CurrentPos)
	{
		CurrentPos = PEOPLE;
		PEOPLE = OldPos;
		drawHumanSpace();//clearing Old Pos
		//Sleep(100);
		PEOPLE = CurrentPos;//Return to current Pos
		OldPos = CurrentPos;// Updating OldPos to Current Pos
	}
	void DrawingLanes(bool check)
	{
		char a = 1;
		int k = 6;
		for (int i = 6; i <= 39; i += k)
		{
			for (int j = 0; j <= RightEdge + 1; j++)
			{
				gotoxy(j, i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 56);
				cout << a;
				if (check == true)
					Sleep(1);
			}
			if (i == 6)
				k = 7;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}

	void NextLevelScreen()
	{
		gotoxy(53, 18);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 53);
		for (int i = 65; i < 87; i++)
		{
			gotoxy(i, 20);
			cout << " ";
			Sleep(20);
		}
		for (int i = 19; i > 15; i--)
		{
			gotoxy(86, i);
			cout << " ";
			Sleep(20);
		}
		for (int i = 86; i > 64; i--)
		{
			gotoxy(i, 16);
			cout << " ";
			Sleep(20);
		}
		for (int i = 16; i < 21; i++)
		{
			gotoxy(65, i);
			cout << " ";
			Sleep(20);
		}
		gotoxy(72, 18);
		cout << "Level " << Curlevel;
		Sleep(100);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
		system("cls");
	}
	void drawAni()//OK
	{
		int xcor = 0, ycor = 0;
		bool check;
		for (int i = 1; i <= maxfloorsForAni; i += 2)
		{
			for (int j = 0; j < ANI[i].size(); j++)
			{
				ANI[i][j]->BlockCor(xcor, ycor);
				if ((xcor - LengthAni) >= 0)
				{
					draw_reverse_dog(xcor, ycor, 14);
					move_reverse_dog_by5(xcor + 5, ycor);
					//draw_reverse_dog(xcor, ycor, 14);
				}
				else
					draw_reverse_dogSpace(xcor + 10, ycor, 14);
			}
		}
	}
	void drawVe()//OK
	{
		int VeCor = 28;
		int xcor = 0, ycor = 0;
		for (int i = 2; i <= maxfloorsForVe; i += 2)
		{
			if (LIGHT[i].OnGreen())
			{
				for (int j = 0; j < VE[i].size(); j++)
				{
					VE[i][j]->BlockCor(xcor, ycor);
					if (xcor + LengthVe <= RightEdge)
					{
						drawcar(xcor + 5, ycor, 15);
						move_car_by5(xcor, ycor);
						//drawcar(xcor + 5, ycor, 15);
					}
					else
						drawcarSpace(xcor, ycor, 15);
				}
				drawGreenLight(VeCor - (i / 2 - 1)*LengthBetweenRows);
			}
			else
				drawRedLight(VeCor - (i / 2 - 1)*LengthBetweenRows);
		}
	}
	void drawHuman()//OK
	{
		int xcor = 0, ycor = 0;
		PEOPLE.BlockCor(xcor, ycor);
		drawplayer(xcor, ycor);
	}
	void drawHumanSpace()//Clear Position
	{
		int xcor = 0, ycor = 0;
		PEOPLE.BlockCor(xcor, ycor);
		drawplayerSpace(xcor, ycor);
	}
	/*void drawGame()//Just for testing
	{
		int height = 35;
		drawplayer(50, 41);
		int count = 0;
		for (int start = height; start >= 5; start -= 6, count += 1)
		{
			if (count % 2 == 0)
				draw_reverse_dog(165, start);
			else
				drawcar(0, start);
		}
		system("pause>nil");
	}*/
	~CGAME() {};
	void getPeopleFile(ifstream& fin)
	{
		int Left,Up,Right,Down;
		fin.read((char*)&Left, sizeof(int));
		fin.read((char*)&Up, sizeof(int));
		fin.read((char*)&Right, sizeof(int));
		fin.read((char*)&Down, sizeof(int));
		PEOPLE = CPEOPLE(Up,Down,Left,Right,CurFloor);
	}
	void getAnimalFile(ifstream& fin)//load game
	{
		int Left, Up, Right, Down;
		for (int i = 0; i < 10; i++)
		{
			int size;
			fin.read((char*)&size, sizeof(int));
			for (int j = 0; j < size; j++)
			{
				fin.read((char*)&Left, sizeof(int));
				fin.read((char*)&Up, sizeof(int));
				fin.read((char*)&Right, sizeof(int));
				fin.read((char*)&Down, sizeof(int));
				ANI[i][j] = new CANIMAL(Up, Down, Left, Right, CurFloor);
			}
		}
	}
	void getVehicleFile(ifstream&fin)//load game
	{
		int Left, Up, Right, Down;
		for (int i = 0; i < 10; i++)
		{
			int size;
			fin.read((char*)&size, sizeof(int));
			for (int j = 0; j < size; j++)
			{
				fin.read((char*)&Left, sizeof(int));
				fin.read((char*)&Up, sizeof(int));
				fin.read((char*)&Right, sizeof(int));
				fin.read((char*)&Down, sizeof(int));
				VE[i][j] = new CVEHICLE(Up, Down, Left, Right, CurFloor);
			}
		}
	}
	void getPeopleByDefault()//New game(OK)
	{
		PEOPLE = CPEOPLE(YCorOfHuman - 1, YCorOfHuman + 2, XCorOfHuman - 1, XCorOfHuman + 2, 0);//please change the coordinate of people
	}
	void getVehicleByDefault()//New game(OK)
	{
		int Distance = (RightEdge - LeftEdge - Curlevel * LengthVe) / Curlevel;
		if (Curlevel != 1)
			Distance = (RightEdge - LeftEdge - Curlevel * LengthVe) / (Curlevel - 1);
		int startHeight = YCorOfVe;
		for (int i = 2; i <= maxfloorsForVe; i += 2)
		{
			int startPos = LeftEdge;
			VE[i].clear();
			for (int j = 0; j < Curlevel; j++)
			{
				CVEHICLE *tmp = new CCAR(startHeight - 1, startHeight + 2, startPos, startPos + LengthVe, i);
				VE[i].push_back(tmp);
				//delete tmp;
				startPos = startPos + LengthVe + Distance;//startpos+=distance
				if (startPos >= RightEdge)
					break;
			}
			startHeight -= LengthBetweenRows;
		}
	}
	//Logic game
	//Level 1:1 VE 1 ANI
	//Level 2 :2 VE 2 ANI
	//Level 3:3 VE 2 ANI
	//Level 4:4 VE 3 ANI
	//Level 5:5 VE 3 Ani
	void getAnimalByDefault()//New game(OK)
	{
		int tmp = Curlevel;
		if (Curlevel == 3)
			Curlevel--;
		if (Curlevel == 4 || Curlevel == 5)
			Curlevel = 3;
		int Distance = (RightEdge - LeftEdge - Curlevel * LengthAni) / Curlevel;
		if (Curlevel != 1)
			Distance = (RightEdge - LeftEdge - Curlevel * LengthAni) / (Curlevel - 1);
		int startHeight = YCorOfAni;
		for (int i = 1; i <= maxfloorsForAni; i += 2)
		{
			int startPos = RightEdge;
			ANI[i].clear();
			for (int j = 0; j < Curlevel; j++)
			{
				CANIMAL *tmp = new CBIRD(startHeight - 1, startHeight + 2, startPos - LengthAni, startPos, i);
				ANI[i].push_back(tmp);
				//delete tmp;
				startPos = startPos - LengthAni - Distance;//startpos+=distance
				if (startPos <= LeftEdge)
					break;
			}
			startHeight -= LengthBetweenRows;
		}
		Curlevel = tmp;
	}
	void newGame()
	{
		//delete all and set default again
		Curlevel = 1;
		CurFloor = 0;
		getAnimalByDefault();
		getPeopleByDefault();
		getVehicleByDefault();
		DrawingLanes(true);
		drawHuman();
	}
	void exitGame(HANDLE);
	void startGame()
	{
		//Check Button
		//Preparing database for game
		getPeopleByDefault();
		getAnimalByDefault();
		getVehicleByDefault();
		//drawing game
	}
	void loadGame(ifstream&fin)
	{
		fin.read((char*)&Curlevel, sizeof(Curlevel));
		fin.read((char*)&CurFloor, sizeof(CurFloor));
		getPeopleByDefault();
		getPeopleFile(fin);
		getAnimalByDefault();
		getAnimalFile(fin);
		getVehicleByDefault();
		getVehicleFile(fin);
	}
	void saveGame(ofstream&fout)
	{
		fout.write((char*)&Curlevel, sizeof(Curlevel));
		fout.write((char*)&CurFloor, sizeof(CurFloor));
		saveToFile(fout, PEOPLE);
		saveAnimals(fout);
		saveVehicles(fout);
	}
	void pauseGame()
	{
		resumeGame();
		//After pressing p go on printing out the console
	}
	void resumeGame()
	{
		char c = _getch();
		while (c != 'O' &&c != 'o')
		{
			c = _getch();
		}
		//After pressing p go on printing out the console
	}
	void FinishGames()
	{
		system("cls");
		gotoxy(60, 20);
		cout << "CONGRATULATION!";
		cout << "Do you want to play again";
		while (true)
		{
			char m = _getch();
			if (m == 'Y' || m == 'y')
			{
				system("cls");
				//playagain
			}
		}
	}


	void clearScreenAndCreateNewLevel() {
		Curlevel++;
		if (Curlevel == 6)
			Curlevel = 1;
		CurFloor = 0;
		getPeopleByDefault();//new
		//CPEOPLE tmp(PEOPLE, YCorOfHuman - 1, YCorOfHuman + 2,CurFloor); old
		getVehicleByDefault();
		getAnimalByDefault();
		getLIGHT();
		system("cls");
		NextLevelScreen();
		DrawingLanes(true);
		drawHuman();
		//PEOPLE = tmp; old
	}


	bool updatePosPeople(char c, bool &NextLevel)//OK
	{
		if (c == 'W' || c == 'w')
		{
			if (Curlevel == 6)
			{
				//
			}
			else
			{
				if (PEOPLE.GoUp() == false)//Standing on the maximum floor ,checking by using Coordinates
				{
					//Go to next level
					NextLevel = true;
				}
				else
					CurFloor++;
				return true;
			}
		}
		else if (c == 'A' || c == 'a')
		{
			return PEOPLE.GoLeft();//creating bool variables just for checking for later problem . People will go to the left 
		}
		else if (c == 'S' || c == 's')
		{
			if (CurFloor != 0)
				CurFloor--;
			return PEOPLE.GoDown();
		}
		else if (c == 'D' || c == 'd')
		{
			return PEOPLE.GoRight();
		}
	}
	void updatePosVehicle()//OK
	{
		int startHeight = YCorOfAni;
		for (int i = 2; i <= maxfloorsForVe; i += 2)
		{
			if (LIGHT[i].OnGreen())
			{
				for (int j = 0; j < VE[i].size(); j++)
				{
					/*if (VE[i][j]->GoRight()==false)//Vehicle goes right
					{
						CCAR tmp(startHeight - 1, startHeight + 2, 0, 0 + LengthVe, i + 1);
					}*/
					VE[i][j]->ObStacleRight();
				}
				startHeight -= LengthBetweenRows;
			}
		}
	}
	void updatePosAnimal()//OK
	{
		for (int i = 1; i <= maxfloorsForAni; i += 2)
		{
			for (int j = 0; j < ANI[i].size(); j++)
			{
				ANI[i][j]->ObStacleLeft();//Animal goes left
			}
		}
	}
};
#endif

