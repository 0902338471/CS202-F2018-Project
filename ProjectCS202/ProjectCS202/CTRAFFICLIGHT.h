#ifndef _CTRAFFICLIGHT_
#define _CTRAFFICLIGHT_
#include "Object.h"
class CLIGHT
{
public:
	CLIGHT(int TGs)
	{
		TG = TGs;
		red = false;
		green = true;
		Counttime = 0;
	}
	bool OnGreen()
	{
		Counttime++;
		if (Counttime == TG)
		{
			if (green == true)
			{
				green = false;
				red = true;
			}
			else
			{
				green = true;
				red = false;
			}
			Counttime=0;
		}
		return green;
	}
	CLIGHT()
	{
		red = false;
		green = true;
	}
private:
	bool red;
	bool green;
	int TG;//Time settings for green duration
	int Counttime;
};
#endif