#pragma once
#include "pch.h"
#include "Map.h"
#include "Player.h"
#include "Draw.h"

using namespace std;



class Game
{
private:
	int totalPlayer; //���a�`��
	static int currentCount; //�Ѿl�C������
	static int currentPlayer; //�ثe���쪺���a
	static Map mainMap;
	static int currentStockPrice;
	static string currentStockPriceMsg;
	static vector<int> BlockList;

public:
	// �غc�l�A��JŪ���ɮת��ɮצW��
	Game(string preferFile);
	// ���J�C��
	void LoadGame(string preferFile);
	// �x�s�C��
	void SaveGame(string preferFile);
	// ���s�}�l
	void NewGame();	
	//�Y��l
	void RollingDice(Player &preferPlayer, int preferStep, bool global);
	// ���a���ʴX��
	void PlayerMove(int preferAddVector, Player &preferPlayer);
	//���a�i����ʧ@
	int selectAction();
	//���
	bool gameMenu();
	friend class Map;
	friend class Player;
	friend class Draw;
};
