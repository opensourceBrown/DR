#ifndef _GAME_CONSTANT_H_
#define _GAME_CONSTANT_H_


//������Ϸ����
#define GENERAL_CHAR_LENGTH			128						//ͨ���ַ����鳤��

//���崥���¼���Ӧ���ȼ�
#define TOUCH_EVENT_PRIORITY_DEFAULT	128
#define TOUCH_EVENT_PRIORITY_MID		256
#define TOUCH_EVENT_PRIORITY_TOP		512

//������Ϸ�������������������
#define GRID_ROW_COUNT					6						//��Ϸ�������������
#define GRID_VOLUME_COUNT				6						//��Ϸ�������������

#define WIN_SIZE			CCDirector::sharedDirector()->getWinSize()

//��������cell����������
enum GRIDINDEX_TYPE{
	kGRIDINDEX_TYPE_DEFAULT=0,									//����
	kGRIDINDEX_TYPE_NEXT,										//��һ��
	kGRIDINDEX_TYPE_PRE,										//��һ��
};


#endif
