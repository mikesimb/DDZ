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
	pPlayerData  Player[3];
	int BottomCard[3];
//��һ����54��
	byte  Card[54];


};

