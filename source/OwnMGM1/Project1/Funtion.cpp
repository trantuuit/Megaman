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

int gameTime = 6;
double gravity = -0.003;
double jumpVolume = 1;