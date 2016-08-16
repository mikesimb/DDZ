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
//��ʼ����Ϸ����
bool CDDZ_Game::Initialize_Game()
{
	//���ȳ�ʼ��player
	for (int i = 0;i < 3;i++)
	{
		Player[i] = new CPLayer;
		Player[i]->setPlayerStatue(0);
		Player[i]->setPlayerIdentfy(pi_NONE);
		Player[i]->setPlayerHandCardCount(0);
// 		Player[i]->PlayerStatue = 0;
// 		Player[i]->Playeridentfy = pi_NONE;
// 		Player[i]->PlayrHandCardCount = 0;
	}
	for (int j = 0; j < 54 ;j++ )
	{
		Card[j] = j ;
	}
	
	return true;

}

void CDDZ_Game::StartGame()
{
	//����׼��
	for (int i = 0 ;i < 3 ;i++)
	{
		Player[i]->setPlayerStatue(1);
		int* cards = Player[i]->getPlayerHandCard();
		//Player[i]->PlayerStatue = 1;
		for (int j = 0; j < 21; j++)
			cards[j] = 0;
			Player[i]->setPlayerIdentfy(pi_NONE);
	}
	//����
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
	for (int index = 0; index < 54; index++) {
		//OutputCardinfo(index);
		
		int playnum = index % 3;
		int player_cardnum = index / 3;

		int* cards = Player[playnum]->getPlayerHandCard();
		cards[player_cardnum] = Card[index];
		int cardcount = Player[playnum]->getPlayerHandCardCount();
		Player[playnum]->setPlayerHandCardCount(++cardcount);
	}
	
	KeepBottomCards();
	return;
	

	int c = 0;
	OutputDebugString("���0��");
	for ( c = 0; c < 21; c++)
	{
		OutputCardinfo(Player[0]->getPlayerHandCard()[c]);
	}
	OutputDebugString("���0\n");
	OutputDebugString("���1��");
	for ( c = 0; c < 21; c++)
	{
		OutputCardinfo(Player[1]->getPlayerHandCard()[c]);
	}
	OutputDebugString("���1\n");
	OutputDebugString("���2��");
	for ( c = 0; c < 21; c++)
	{
		OutputCardinfo(Player[2]->getPlayerHandCard()[c]);
	}
	OutputDebugString("���2\n");
	OutputDebugString("��������\n");
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
	//ѯ�����0�Ƿ�Ҫ����
	int flag = 0; //�м������Ҫ����
	//��һ��ѯ������Ƿ�Ҫ����
	for (int i = 0; i < 3; i++)
	{
		srand((unsigned)time(0));
		if (rand() % 2 == 1)
		{
			Player[i]->setPlayerStatue(true);
			flag++;
		}
		else
			Player[i]->setPlayerStatue(false);
	}
	//���Ҫ��������Ҷ���1��
	if (flag > 1)
	{
		//���ڶ���ѯ�ʣ�ֻ����һ����
		bool alreadyhaslord = false;
		for (int i = 0; i < 3; i++)
		{
			if(alreadyhaslord)
			{
				Player[i]->setPlayerStatue(false);
			}
			else
			{
				if (Player[i]->getPlayerStatue())
				{
					srand((unsigned)time(0));
					if (rand() % 2 == 1)
					{
						Player[i]->setPlayerStatue(true);
						alreadyhaslord = true;
					}
					else
						Player[i]->setPlayerStatue(false);
				}
			}
		}
	}
}

void CDDZ_Game::FightforLandlordEnd()
{
	//ȷ�����
	for (int j = 0; j < 3; j++)
	{

		if (Player[j]->getPlayerStatue())
		{
			Player[j]->setPlayerIdentfy(pi_Landlord);
		}
		else
			Player[j]->setPlayerIdentfy(pi_Peasant);

	}
}

void CDDZ_Game::LandlordGetBottomCards(byte Playerindex)
{
	for (int i = 0 ;i<3 ;i++)
	{
		if (Player[i]->getPlayerIdentfy() == pi_Landlord)
		{
			Player[i]->getPlayerHandCard()[18] = BottomCard[0];
			Player[i]->getPlayerHandCard()[19] = BottomCard[1];
			Player[i]->getPlayerHandCard()[20] = BottomCard[2];
			int cardcount = Player[i]->getPlayerHandCardCount();
			 cardcount += 3;
			 Player[i]->setPlayerHandCardCount(cardcount);
			break;
		}
		
	}

}

void CDDZ_Game::StartGame_SendCard()
{
	//������Ҫ��ʼ������
	//�����ҵ���������
	//ѯ�ʵ�����ʲô��
	//�������ƽ���
	//�ҵ���һ�����Ƶ���
	//ѯ����һ�����Ƶ���
	//���ƽ���
}
