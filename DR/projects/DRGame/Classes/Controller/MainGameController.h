#ifndef _MAIN_GMAE_CONTROLLER_H_
#define _MAIN_GMAE_CONTROLLER_H_


#include "BaseController.h"
#include "cocos2d.h"


class MainGameController : public BaseController
{
public:
    MainGameController();
    ~MainGameController();
    
    static MainGameController *create();
    
    //����grid cell
	bool generateGridCell(unsigned int rIndex,unsigned int vIndex);
    
    //get the grid cell property data struct
    GridElementProperty getGridElementProperty(unsigned int rIndex,unsigned int vIndex);
    
    //�жϻ��������е�Ԫ���Ƿ��������
	bool judgeElementsCanConnected();
    
    //insert a cell into the connected array
	void insertCellIntoConnectedArray(unsigned int rIndex,unsigned int vIndex);

private:
    bool initWith();
	
	//����grid cell��λ�ú�����
	void updateGridCell(unsigned int rIndex,unsigned int vIndex);
	
	//�жϱ��ؿ���Ϸ�Ƿ����
	bool judgeGameIsEnd();

	//�ж�������Ԫ���Ƿ��������
	bool judgeConnectedElementsCanClear();
	
	
    
	//remove a cell from the connected array
	void removeCellFromConnectedArray(unsigned int pIndex);
    
	//insert a cell into the cell container
	void insertCellIntoGridContainer(unsigned int pIndex);
    
	//remove a cell from the cell container(clear a cell from the screen for connecting)
	void removeCellFromGridContainer(unsigned int pIndex);

	
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
	
    GridElementProperty     mGridPropertyContainer[GRID_ROW*GRID_VOLUME];
private:

};

#endif
