#ifndef _MAIN_GMAE_CONTROLLER_H_
#define _MAIN_GMAE_CONTROLLER_H_


#include "BaseController.h"
//#include "cocos2dx.h"
#include "cocos2d.h"


class MainGameController : public BaseController
{
public:
    MainGameController();
    ~MainGameController();

private:

	//����grid cell
	void generateGridCell(unsigned int rIndex,unsigned int vIndex);
	
	//����grid cell��λ�ú�����
	void updateGridCell(unsigned int rIndex,unsigned int vIndex);
	
	//�жϱ��ؿ���Ϸ�Ƿ����
	bool judgeGameIsEnd();

	//�ж�������Ԫ���Ƿ��������
	bool judgeConnectedElementsCanClear();
	
	//�жϻ��������е�Ԫ���Ƿ��������
	bool judgeElementsCanConnected();



	
private:
	unsigned int			mCoins;						//ÿһ�ؿ�(stage���ۼƵĽ��
	unsigned int 			mScore;						//ÿһ�ؿ��ۼƵĻ���
	unsigned int 			mRound;						//ÿһ�ؿ��ۼƵĻغ���
	unsigned int			mKilledMonster;				//ɱ���Ĺ���
	unsigned int			mCurrentShield;				//��ǰ�Ķ���
	unsigned int			mCurrentPotion;				//��ǰ��Ѫ��
	
	CCArray					*mMagicInStage;				//��ǰ�ؿ��п���ʹ�õ�ħ��
	CCArray					*mStageConnectedElements;	//ÿһ�غ����Ѿ�������Ԫ�أ���˳��洢Ԫ�ص����ͺͶ�Ӧcell�ı�ʶ���ɼӿ�ɾ��
	CCArray					*mGridCellContainer;
	

private:

};

#endif
