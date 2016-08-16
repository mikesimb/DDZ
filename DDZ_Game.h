#pragma once
enum PlayerIdentfy
{
	pi_NONE = 0,
	pi_Landlord,
	pi_Peasant
};

enum GameState
{
	gs_NONE,//无状态
	gs_Ready,//准备阶段
	gs_refreshcards,//洗牌
	gs_SendCardToPlayer,//发牌
	gs_fightforLandlord,//叫地主
	gs_Landlordgetcards,//地主拿底牌
	gs_PlayerSendCard,//出牌
	gs_End, //结束牌局
	gs_calc //计算结果

};

typedef struct tgaPlayerData
{
	PlayerIdentfy Playeridentfy;  //这个代表了玩家在牌局里的
	int PlayerHandCard[21];
	int PlayrHandCardCount;
	bool PlayerStatue;

}PlayerData,*pPlayerData;


class CPLayer
{
public:
	CPLayer() {};
	~CPLayer() {};

	PlayerIdentfy getPlayerIdentfy() { return m_Playeridentfy; };
	void setPlayerIdentfy(PlayerIdentfy pi) { m_Playeridentfy = pi; };

	void setPlayerHandCardCount(int count) { m_PlayerHandCardCount = count; };
	int getPlayerHandCardCount() { return m_PlayerHandCardCount; };

	void setPlayerStatue(bool ps) { m_PlayerStatue = ps; };
	bool getPlayerStatue() { return m_PlayerStatue; }

	int* getPlayerHandCard() { return &m_PlayerHandCard[0]; };

private:
	PlayerIdentfy m_Playeridentfy;
	int           m_PlayerHandCard[21];
	int           m_PlayerHandCardCount;
	bool          m_PlayerStatue;
};



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
	//pPlayerData  Player[3];
	CPLayer *  Player[3];
	int BottomCard[3];
//有一副牌54张
	byte  Card[54];


};

