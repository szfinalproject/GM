#pragma once
#include <iostream>

using namespace std;

class Score
{
	int scr;
	int sOrD = 0;
public:
	
	int* getScore();
	int* getSD() { return &sOrD; };
	Score() { scr = 0; };
	
};