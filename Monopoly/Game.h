#pragma once
#include "pch.h"
#include "Map.h"
#include "Player.h"
#include "Draw.h"

using namespace std;



class Game
{
private:
	int totalPlayer; //玩家總數
	static int currentCount; //剩餘遊戲局數
	static int currentPlayer; //目前輪到的玩家
	static Map mainMap;
	static int currentStockPrice;
	static string currentStockPriceMsg;
	static vector<int> BlockList;

public:
	// 建構子，輸入讀取檔案的檔案名稱
	Game(string preferFile);
	// 載入遊戲
	void LoadGame(string preferFile);
	// 儲存遊戲
	void SaveGame(string preferFile);
	// 重新開始
	void NewGame();	
	//擲骰子
	void RollingDice(Player &preferPlayer, int preferStep, bool global);
	// 玩家移動幾格
	void PlayerMove(int preferAddVector, Player &preferPlayer);
	//玩家可執行動作
	int selectAction();
	//選單
	bool gameMenu();
	friend class Map;
	friend class Player;
	friend class Draw;
};
