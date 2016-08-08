#pragma once
class CDDZ_Game
{
public:
	CDDZ_Game();
	~CDDZ_Game();
	bool Initialize_Game();
	//可以开始了
	void  StartGame();

	void refreshCards();//洗牌

	void SendCardtoPlayer(byte Playerindex);

	void KeepBottomCards();//留出底牌

	void Fightforlandlord();//抢地主

	void FightforLandlordEnd();

	void LandlordGetBottomCards(byte Playerindex);//地主获取底牌

	void StartGame_SendCard();//开始出牌

	void JudgeCardsType();//判断牌型

	void NextPlayerSendCard();//下一位出牌

	void JudgeValue();//判断大小

	void OnPlayerIsEnd();//有一位玩家出完牌了

	void CalculationScroe();//计算结果


//作为斗地主首先具备开具的条件
private:
	DWORD Player[3];
	byte  PlayerStatue[3];//三个人都已经准备好了
//有一副牌54张
	byte  Card[54];


};

