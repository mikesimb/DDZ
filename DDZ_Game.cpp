#include "stdafx.h"
#include "DDZ_Game.h"


CDDZ_Game::CDDZ_Game()
{
}


CDDZ_Game::~CDDZ_Game()
{
	for (int i = 0; i < 3; i++)
	{
		delete Player[i];
	}
}
//初始化游戏内容
bool CDDZ_Game::Initialize_Game()
{
	//首先初始化player
	for (int i = 0;i < 3;i++)
	{
		Player[i] = new PlayerData;
		Player[i]->PlayerStatue = 0;
		Player[i]->Playeridentfy = pi_NONE;
		Player[i]->PlayrHandCardCount = 0;
	}
	for (int j = 0; j < 54 ;j++ )
	{
		Card[j] = j ;
	}
	
	return true;

}

void CDDZ_Game::StartGame()
{
	//三人准备
	for (int i = 0 ;i < 3 ;i++)
	{
		Player[i]->PlayerStatue = 1;
		for (int j = 0; j < 21; j++)
			Player[i]->PlayerHandCard[j] = 0;
		Player[i]->Playeridentfy = pi_NONE;
	}
	//发牌
	refreshCards();
}

void CDDZ_Game::GetCardTypeandValue(int CardIndex, byte &CardType, byte &CardValue)
{
	CardType = Card[CardIndex] / 13;
	CardValue = Card[CardIndex] % 13;
	if ((CardType == 4) && (CardValue == 0))
	{
		CardType = 4;
		CardValue = 0;
	}
	if ((CardType == 4) && (CardValue == 1))
	{
		CardType =5;
		CardValue = 0;
	}
}

void CDDZ_Game::OutputCardinfo(int CardIndex)
{
	if ((CardIndex < 0) || (CardIndex > 54)) return;
	byte CardType, CardValue;
	char c_CardType[10] = "";
	GetCardTypeandValue(CardIndex, CardType, CardValue);
	CardValue = CardValue + 1;
	switch (CardType)
	{
	case 0:
		sprintf_s(c_CardType, 10, "%s*", "黑桃");
		break;
	case 1:
		sprintf_s(c_CardType, 10, "%s*", "草花");
		break;
	case 2:
		sprintf_s(c_CardType, 10, "%s*", "红桃");
		break;
	case 3:
		sprintf_s(c_CardType, 10, "%s*", "方块");
		break;
	case 4:
		sprintf_s(c_CardType, 10, "%s*", "小王");
		break;
	case 5:
		sprintf_s(c_CardType, 10, "%s*", "大王");
		break;

	default:
		break;
	}
	char A[255];

	sprintf_s(A, 255, "%s%d##", c_CardType, CardValue);
	OutputDebugString(A);
}

void CDDZ_Game::refreshCards()
{
	int index;
	int value;
	int median;
	/* 每次发牌的时候任意分配待交换的数据 */
	for (index = 0; index < 54; index++) {
	    value = rand() % 54;
	    median = Card[index];
		Card[index] = Card[value];
		Card[value] = median;
		
	}
	for (int i = 0; i < 54; i++)
	{
		OutputCardinfo(Card[i]);
	}
	

}

void CDDZ_Game::SendCardtoPlayer(byte Playerindex)
{
	OutputDebugString("开始发牌\n");
	for (int index = 0; index < 54; index++) {
		//OutputCardinfo(index);
		
		int playnum = index % 3;
		int player_cardnum = index / 3;
		Player[playnum]->PlayerHandCard[player_cardnum] = Card[index];
		Player[playnum]->PlayrHandCardCount++;
	}
	
	KeepBottomCards();
	return;
	

	int c = 0;
	OutputDebugString("玩家0：");
	for ( c = 0; c < 21; c++)
	{
		OutputCardinfo(Player[0]->PlayerHandCard[c]);
	}
	OutputDebugString("玩家0\n");
	OutputDebugString("玩家1：");
	for ( c = 0; c < 21; c++)
	{
		OutputCardinfo(Player[1]->PlayerHandCard[c]);
	}
	OutputDebugString("玩家1\n");
	OutputDebugString("玩家2：");
	for ( c = 0; c < 21; c++)
	{
		OutputCardinfo(Player[2]->PlayerHandCard[c]);
	}
	OutputDebugString("玩家2\n");
	OutputDebugString("结束发牌\n");
}

void CDDZ_Game::KeepBottomCards()
{
	BottomCard[0] = Card[51];
	BottomCard[1] = Card[52];
	BottomCard[2] = Card[53];
}

void CDDZ_Game::Fightforlandlord()
{
	srand((unsigned)time(0));
	//询问玩家0是否要地主
	int flag = 0; //有几个玩家要地主
	//第一轮询问玩家是否要地主
	for (int i = 0; i < 3; i++)
	{
		srand((unsigned)time(0));
		if (rand() % 2 == 1)
		{
			Player[i]->PlayerStatue = true;
			flag++;
		}
		else
			Player[i]->PlayerStatue = false;
	}
	//如果要地主的玩家多于1个
	if (flag > 1)
	{
		//做第二轮询问，只到第一个人
		bool alreadyhaslord = false;
		for (int i = 0; i < 3; i++)
		{
			if(alreadyhaslord)
			{
				Player[i]->PlayerStatue = false;
			}
			else
			{
				if (Player[i]->PlayerStatue)
				{
					srand((unsigned)time(0));
					if (rand() % 2 == 1)
					{
						Player[i]->PlayerStatue = true;
						alreadyhaslord = true;
					}
					else
						Player[i]->PlayerStatue = false;
				}
			}
		}
	}
}

void CDDZ_Game::FightforLandlordEnd()
{
	//确定身份
	for (int j = 0; j < 3; j++)
	{

		if (Player[j]->PlayerStatue)
		{
			Player[j]->Playeridentfy = pi_Landlord;
		}
		else
			Player[j]->Playeridentfy = pi_Peasant;

	}
}

void CDDZ_Game::LandlordGetBottomCards(byte Playerindex)
{
	for (int i = 0 ;i<3 ;i++)
	{
		if (Player[i]->Playeridentfy == pi_Landlord)
		{
			Player[i]->PlayerHandCard[18] = BottomCard[0];
			Player[i]->PlayerHandCard[19] = BottomCard[1];
			Player[i]->PlayerHandCard[20] = BottomCard[2];
			Player[i]->PlayrHandCardCount += 3;
			break;
		}
		
	}

}

void CDDZ_Game::StartGame_SendCard()
{
	//这里需要开始出牌了
	//首先找到地主出牌
	//询问地主出什么牌
	//地主出牌结束
	//找到下一个出牌的人
	//询问下一个出牌的人
	//出牌结束
}
