#ifndef _Vehicle_
#define _Vehicle_
#include "Object.h"
#include "Drawing.h"
class CVEHICLE :public CObject {
public:
	CVEHICLE(int up, int down, int left, int right, int tmpfloor) :CObject(up, down, left, right, tmpfloor) {

	}
	CVEHICLE() = default;
	~CVEHICLE()
	{

	};
	virtual bool GoRight()
	{
		return CObject::GoRight();
	}
	virtual bool GoLeft()
	{
		return CObject::GoLeft();
	}
	int getSize() {
		return Num;
	}
	void BlockCor(int &x, int &y)
	{
		CObject::BlockCor(x, y);
	}
	void ObStacleRight()//for ObStacles only
	{
		CObject::ObStacleRight();
	}
	void ObStacleLeft()
	{
		CObject::ObStacleLeft();
	}
private:
	int Num;//numberofvehicle
	//bool OutScreen;//True => drawing False =>Not Drawing
};
class CTRUCK :public CVEHICLE {
public:
	CTRUCK(int up, int down, int left, int right, int tmpfloor) :CVEHICLE(up, down, left, right, tmpfloor) {

	}
	CTRUCK() = default;
	~CTRUCK();
	bool GoRight()
	{
		return CVEHICLE::GoRight();
	}
	bool GoLeft()
	{
		return CVEHICLE::GoLeft();
	}
	void ObStacleRight(bool &check)//for ObStacles only
	{
		CObject::ObStacleRight();
	}
	void ObStacleLeft()
	{
		CObject::ObStacleLeft();
	}
private:
	void DTRUCK();//drawing truck
};
class CCAR :public CVEHICLE {
public:
	CCAR(int up, int down, int left, int right, int tmpfloor) :CVEHICLE(up, down, left, right, tmpfloor) {

	}
	CCAR() = default;
	~CCAR()
	{

	}
	bool GoRight()
	{
		return CObject::GoRight();
	}
	bool GoLeft()
	{
		return CObject::GoLeft();
	}
	void BlockCor(int &x, int &y)
	{
		CVEHICLE::BlockCor(x, y);
	}
	void ObStacleRight()//for ObStacles only
	{
		CVEHICLE::ObStacleRight();
	}
	void ObStacleLeft()
	{
		CVEHICLE::ObStacleLeft();
	}
private:
	void DCAR();//drawing car
};
class CAmbu 
{
public:
	CAmbu()
	{
		xcor = LeftEdge;
		ycor = 35;
	}
	bool checkDone()
	{
		xcor += 5;
		drawAmbuCar(xcor, ycor);
		move_ambucar_by5(xcor - 5, ycor);
		Sleep(100);
		if (xcor + 16 > RightEdge)
			return true;
		else return false;
		//play sound here
	}
	void updatePosAm()
	{
		xcor += 5;
	}
private:
	int xcor;
	int ycor;
};
#endif