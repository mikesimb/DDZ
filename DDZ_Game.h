#pragma once
enum PlayerIdentfy
{
	pi_NONE = 0,
	pi_Landlord,
	pi_Peasant
};

enum GameState
{
	gs_NONE,//��״̬
	gs_Ready,//׼���׶�
	gs_refreshcards,//ϴ��
	gs_SendCardToPlayer,//����
	gs_fightforLandlord,//�е���
	gs_Landlordgetcards,//�����õ���
	gs_PlayerSendCard,//����
	gs_End, //�����ƾ�
	gs_calc //������

};

typedef struct tgaPlayerData
{
	PlayerIdentfy Playeridentfy;  //���������������ƾ����
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
	//���Կ�ʼ��
	void  StartGame();

	void GetCardTypeandValue(int CardIndex,byte &CardType, byte &CardValue);

	void OutputCardinfo(int CardIndex);


	void refreshCards();//ϴ��

	void SendCardtoPlayer(byte Playerindex);

	void KeepBottomCards();//��������

	void Fightforlandlord();//������

	void FightforLandlordEnd();

	void LandlordGetBottomCards(byte Playerindex);//������ȡ����

	void StartGame_SendCard();//��ʼ����

	void JudgeCardsType();//�ж�����

	void NextPlayerSendCard();//��һλ����

	void JudgeValue();//�жϴ�С

	void OnPlayerIsEnd();//��һλ��ҳ�������

	void CalculationScroe();//������


//��Ϊ���������Ⱦ߱����ߵ�����
private:
	//pPlayerData  Player[3];
	CPLayer *  Player[3];
	int BottomCard[3];
//��һ����54��
	byte  Card[54];


};

