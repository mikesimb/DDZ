#pragma once
class CDDZ_Game
{
public:
	CDDZ_Game();
	~CDDZ_Game();
	bool Initialize_Game();
	//���Կ�ʼ��
	void  StartGame();

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
	DWORD Player[3];
	byte  PlayerStatue[3];//�����˶��Ѿ�׼������
//��һ����54��
	byte  Card[54];


};

