#pragma once
enum PlayerIdentfy
{
	pi_NONE = 0,
	pi_Landlord,
	pi_Peasant
};

typedef struct tgaPlayerData
{
	PlayerIdentfy Playeridentfy;  //这个代表了玩家在牌局里的
	int PlayerHandCard[21];
	int PlayrHandCardCount;
	byte PlayerStatue;

}PlayerData,*pPlayerData;


class CDDZ_Game
{
public:
	CDDZ_Game();
	~CDDZ_Game();
	bool Initialize_Game();
	//可以开始了
	void  StartGame();

	void GetCardTypeandValue(int CardIndex,byte &CardType, byte &CardValue);

	void OutputCardinfo(int CardIndex);


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
	pPlayerData  Player[3];
	int BottomCard[3];
//有一副牌54张
	byte  Card[54];


};

