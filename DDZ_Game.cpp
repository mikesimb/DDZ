#include "stdafx.h"
#include "DDZ_Game.h"


CDDZ_Game::CDDZ_Game()
{
}


CDDZ_Game::~CDDZ_Game()
{
}
//��ʼ����Ϸ����
bool CDDZ_Game::Initialize_Game()
{
	//���ȳ�ʼ��player
	for (int i = 0;i < 3;i++)
	{
		Player[i] = new PlayerData;
		Player[i]->PlayerStatue = 0;
		Player[i]->Playeridentfy = pi_NONE;
	}
	for (int j = 0; j < 54 ;j++ )
	{
		Card[j] = j + 1;
	}
	
	return true;

}

void CDDZ_Game::StartGame()
{
	//����׼��
	for (int i = 0 ;i < 3 ;i++)
	{
		Player[i]->PlayerStatue = 1;
		for (int j = 0; j < 21; j++)
			Player[i]->PlayerHandCard[j] = 0;
		Player[i]->Playeridentfy = pi_NONE;
	}
	//����
	refreshCards();
}

void CDDZ_Game::GetCardTypeandValue(int CardIndex, byte &CardType, byte &CardValue)
{
	CardType = CardIndex / 13;
	CardValue = CardIndex % 13;
	if ((CardType == 4) && (CardValue == 1))
	{
		CardType = 4;
		CardValue = 0;
	}
	if ((CardType == 4) && (CardValue == 2))
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
	GetCardTypeandValue(Card[CardIndex], CardType, CardValue);
	switch (CardType)
	{
	case 0:
		sprintf_s(c_CardType, 10, "%s*", "����");
		break;
	case 1:
		sprintf_s(c_CardType, 10, "%s*", "�ݻ�");
		break;
	case 2:
		sprintf_s(c_CardType, 10, "%s*", "����");
		break;
	case 3:
		sprintf_s(c_CardType, 10, "%s*", "����");
		break;
	case 4:
		sprintf_s(c_CardType, 10, "%s*", "С��");
		break;
	case 5:
		sprintf_s(c_CardType, 10, "%s*", "����");
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
	/* ÿ�η��Ƶ�ʱ�������������������� */
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
	OutputDebugString("��ʼ����\n");
	for (int index = 0; index < 51; index++) {
		int playnum = index % 3;
		int player_cardnum = index / 3;
		Player[playnum]->PlayerHandCard[player_cardnum] = Card[index];
	}
	BottomCard[0] = Card[51];
	BottomCard[1] = Card[52];
	BottomCard[2] = Card[53];
	int c = 0;
	OutputDebugString("���0��");
	for ( c = 0; c < 21; c++)
	{
		OutputCardinfo(Player[0]->PlayerHandCard[c]);
	}
	OutputDebugString("���0\n");
	OutputDebugString("���1��");
	for ( c = 0; c < 21; c++)
	{
		OutputCardinfo(Player[1]->PlayerHandCard[c]);
	}
	OutputDebugString("���1\n");
	OutputDebugString("���2��");
	for ( c = 0; c < 21; c++)
	{
		OutputCardinfo(Player[2]->PlayerHandCard[c]);
	}
	OutputDebugString("���2\n");
	OutputDebugString("��������\n");
}
