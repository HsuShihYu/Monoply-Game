#pragma once
#include "pch.h"
using namespace std;

//�֦��]��
struct property
{
	int moneyInPocket;
	int moneyInBank;
	int stock;
};

// �֦��϶��y�z���c
struct hasChunkStatus
{
	int playerNumber; //���a�s��
	string playerName; //���a�W��
	int playerPosition; //���a��m
	property hasMoney; //���a�֦�������
	vector<string> hasBuffNuff; //���a�֦������|�ΩR�B�ĪG
	int hasChunkStage; //�֦����϶����š]�L�H�֦��B��l�B�@���B�G���B�T���^
	vector<int> hasChunkNumber; //�֦����϶��s��
	vector<int> hasChunkStagePrice; //�֦����϶����š]��l�B�@���B�G���B�T���^
};

class Player
{
private:
	static int PlayerQuantity; //�������a�`��
	static vector<Player> PlayerList; //�������a�M��
	hasChunkStatus hasChunk; //���a�֦����϶��M��

public:
	// ��l�غc�l
	Player();
	// �a���a�W�٪��غc�l
	Player(string preferName);
	// �a���㪱�a��T���غc�l�A�Ω�Ū�ɲ��ͪ��a�ɨϥ�
	Player(hasChunkStatus preferHasChunk);
	// �W�[���a�`�ƶq
	static void addPlayerQuantity(Player* preferPlayerPointer);
	// ��s���a��T�� �a��
	static void renewPlayerState();
	// ��s���a��m�� �a��
	static void putPlayerOnMap();
	// ��s���a�a����m�ε��Ũ� �a��
	static void renewProperty();
	// �Ȧs�����a��T��
	static vector<string>drawPlayer;

	friend class Game;
	friend class Map;
};
