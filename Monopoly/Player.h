#pragma once
#include "pch.h"
using namespace std;

//擁有財產
struct property
{
	int moneyInPocket;
	int moneyInBank;
	int stock;
};

// 擁有區塊描述結構
struct hasChunkStatus
{
	int playerNumber; //玩家編號
	string playerName; //玩家名稱
	int playerPosition; //玩家位置
	property hasMoney; //玩家擁有的金錢
	vector<string> hasBuffNuff; //玩家擁有的機會或命運效果
	int hasChunkStage; //擁有的區塊等級（無人擁有、初始、一階、二階、三階）
	vector<int> hasChunkNumber; //擁有的區塊編號
	vector<int> hasChunkStagePrice; //擁有的區塊等級（初始、一階、二階、三階）
};

class Player
{
private:
	static int PlayerQuantity; //紀錄玩家總數
	static vector<Player> PlayerList; //紀錄玩家清單
	hasChunkStatus hasChunk; //玩家擁有的區塊清單

public:
	// 初始建構子
	Player();
	// 帶玩家名稱的建構子
	Player(string preferName);
	// 帶完整玩家資訊的建構子，用於讀檔產生玩家時使用
	Player(hasChunkStatus preferHasChunk);
	// 增加玩家總數量
	static void addPlayerQuantity(Player* preferPlayerPointer);
	// 更新玩家資訊到 地圖
	static void renewPlayerState();
	// 更新玩家位置到 地圖
	static void putPlayerOnMap();
	// 更新玩家地產位置及等級到 地圖
	static void renewProperty();
	// 暫存的玩家資訊表
	static vector<string>drawPlayer;

	friend class Game;
	friend class Map;
};
