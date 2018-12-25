#ifndef _People_
#define _People_
#include "LibraryPro.h"
#include "Animal.h"
#include "Vehicle.h"
#include "Object.h"
//Animal
class CPEOPLE :public CObject {
private:
	bool mState;//isDead
public:
	CPEOPLE() = default;
	CPEOPLE(int up, int down, int left, int right, int tmpfloor) :CObject(up, down, left, right, tmpfloor) {
		mState = false;
	}
	CPEOPLE(const CPEOPLE&tmp,int up, int down,int floor) :CObject(tmp,up, down,floor) {
		mState = false;
	}
	CPEOPLE(int left, int right,int LR) :CObject(right, left,LR)
	{
		mState = false;
	}
	bool GoUp() {
		return CObject::GoUp();
	}
	bool GoLeft() {
		return CObject::GoLeft();
	}
	bool GoRight() {
		return CObject::GoRight();
	}
	bool  GoDown() {
		return CObject::GoDown();
	}
	bool imPact(vector<CVEHICLE*> tmp)
	{
		//NumOfVE=15
		for (int i = 0; i < tmp.size(); i++)
		{
			if (tmp[i]->isCollide(*this))
				return true;
		}
		return false;
	}
	bool isImpact(vector<CANIMAL*> tmp)
	{
		//NumOfAni=15
		for (int i = 0; i < tmp.size(); i++)
		{
			if (tmp[i]->isCollide(*this))
				return true;
		}
		return false;
	}
	bool isFinish(int tmpfloor)//Go to next level
	{
		return CObject::checkFinish(tmpfloor);
	}
	bool isDead() { return mState; }
	void BlockCor(int &x,int &y)
	{
		CObject::BlockCor(x, y);
		x += 1;
		y += 1;
	}
	void gotoXY(int x, int y)
	{
		
	}
};
#endif

