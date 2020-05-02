#pragma once
#include"pch.h"
#include"Game.h"
#include"Map.h"
#include"Player.h"

using namespace std;


class Draw
{
public:
	static void renewOutput();
	static void renewOutput(string msg, string hint);
	static void renewOutput(string msg);
	
private:
	friend class Map;
	friend class Player;
	friend class Game;
};
