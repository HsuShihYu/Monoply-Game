#pragma once
#include "pch.h"
using namespace std;


class Map
{
	// �϶����c
	struct chunk
	{
		int chunkNumber; //�϶��s��
		string chunkName; //�϶��W��
		int chunkType; //�϶�����
		int chunkInitialPrice; //�϶���l����
		int chunkPassPrice0; //�϶��s���L���O
		int chunkPassPrice1; //�϶��@���L���O
		int chunkPassPrice2; //�϶��G���L���O
		int chunkPassPrice3; //�϶��T���L���O
		string chunkMemo; //�϶��Ƶ��A���Ѿ��|�R�B�z����
	};
public:
	static void renewMap();
	static vector<string> drawMap;

private:
	vector<chunk> chunkList; //�V���a�ϤW���Ҧ�Chunk
	string mapName;


	friend class Game;
	friend class Player;
};