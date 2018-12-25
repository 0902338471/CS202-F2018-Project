#ifndef _Drawing_
#define _Drawing_
#include <iostream>
#include <Windows.h>
using namespace std;
void gotoxy(int x, int y);
void FixConsoleWindow();
void drawcar(int x, int y, int color);
void drawdog(int x, int y);
void drawplayer(int x, int y);
void draw_reverse_dog(int x, int y,int color);
void move_reverse_dog(int x, int y);
void move_car(int x, int y);
void drawplayerSpace(int x, int y);
void drawcarSpace(int x, int y, int color);
void draw_reverse_dogSpace(int x, int y, int color);
void move_reverse_dog_by5(int x, int y);
void move_car_by5(int x, int y);
void drawGreenLight(int ycor);
void drawGreenLight(int ycor);
void drawRedLight(int ycor);
void drawAmbuCar(int x, int y);
void move_ambucar_by5(int x, int y);
void cls();
#endif









