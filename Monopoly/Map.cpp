#include "Map.h"
#include"Player.h"
#include "Game.h"

using namespace std;

// 讀 mainMap 裡的 chunkName 到 地圖上
string trans(string x)
{
	string temp;
	if (x.length() == 4)
	{
		temp = "|  " + x + "  ";
	}
	else if (x.length() == 6)
	{
		temp = "| " + x + " ";
	}
	else if (x.length() == 8)
	{
		temp = "|" + x + "";
	}
	return temp;
}

void Map::renewMap()
{
	vector<string>transMap;
	transMap = initialmap(transMap);

	// 填入地圖上第一排
	//////////////////////////////////////////////
	string temp;
	string row1 = "";
	temp = trans(Game::mainMap.chunkList[0].chunkName);
	row1.append(temp);
	for (int i = 27; i >= 21; i--)
	{
		temp = trans(Game::mainMap.chunkList[i].chunkName);
		row1.append(temp);
	}
	row1 = row1 + "|";

	// 填入地圖上第二排~第七排
	/////////////////////////////////////////////////
	vector<string>row2_7;
	for (int i = 1; i <= 6; i++)
	{
		string newRow = "";
		temp = trans(Game::mainMap.chunkList[i].chunkName);
		newRow.append(temp);
		newRow.append("|                                                     ");
		temp = trans(Game::mainMap.chunkList[21 - i].chunkName);
		newRow.append(temp);
		newRow = newRow + "|";
		row2_7.push_back(newRow);
	}

	// 填入地圖上第八排
	////////////////////////////////////////////////
	string row8 = "";
	for (int i = 7; i <= 14; i++)
	{
		temp = trans(Game::mainMap.chunkList[i].chunkName);
		row8.append(temp);
	}
	row8 = row8 + "|";

	// 填入主要Map
	//////////////////////////////////////////////////
	transMap[1] = row1;
	for (int i = 0; i <= 5; i++)
	{
		transMap[4 * i + 5] = row2_7[i];
	}
	transMap[29] = row8;
	drawMap = transMap;

	// 印出背景
	for (int i = 0; i < drawMap.size(); i++)
	{
		cout << drawMap[i] << endl;
	}
}

vector<string> Map::drawMap = {};











