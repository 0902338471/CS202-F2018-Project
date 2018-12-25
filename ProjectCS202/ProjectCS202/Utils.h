#pragma once
#include <string>
#include <mmsystem.h>
using namespace std;

//common function for loading sounds: background music, sound effect,...
void loadSound(string fileName) {
	PlaySound(TEXT(fileName.c_str), NULL, SND_SYNC);
}	