#include<fstream>
#include<string>
#include"Config.h"
using namespace std;

void ignoreLineIfstream(ifstream& fs, int lineCount)
{
	string s;
	for (int i = 0; i < lineCount; i++)
	{
		std::getline(fs, s);
	}
}

int GAMETIME = 6;
double GRAVITY = -0.003;
double MEGAMAN_VY_JUMP = 1;
double MEGAMAN_VX_GO = 0.3;