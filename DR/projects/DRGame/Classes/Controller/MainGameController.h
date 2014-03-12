#ifndef _MAIN_GMAE_CONTROLLER_H_
#define _MAIN_GMAE_CONTROLLER_H_


#include "BaseController.h"
#include "cocos2d.h"
#include "GridElementProperty.h"


class MainGameController : public BaseController
{
public:
    MainGameController();
    ~MainGameController();
    
    static MainGameController *create();
    
    //����grid cell
	bool generateGridCell(unsigned int rIndex,unsigned int vIndex);
    
    //get the grid cell property data struct
    GridElementProperty *getGridElementProperty(unsigned int rIndex,unsigned int vIndex);
    
    //�жϻ��������е�Ԫ���Ƿ��������
    void processGridCellSelected(unsigned int rIndex,unsigned int vIndex);
    
    //insert a cell into the connected array
	void insertCellIntoConnectedArray(unsigned int rIndex,unsigned int vIndex);
    
    //�ж�������Ԫ���Ƿ��������
	bool judgeConnectedElementsCanClear();
    
    //reset mStageConnectedElements:remove all children
    void resetStageConnectedElements();
    
	//��������Ԫ��
	void clearConnectedElements();
    
    OccupationType getPlayerOccupation(){return mPlayerProperty.mType;}
    PlayerProperty getPlayerProperty(){return mPlayerProperty;}
    
    void updateStatusData();

private:
    bool initWith();
	
	//����grid cell��λ�ú�����
	//void updateGridCell(unsigned int rIndex,unsigned int vIndex);
	
	//�жϱ��ؿ���Ϸ�Ƿ����
	bool judgeGameStageIsEnd();
    
    //������ǰ��Ϸ�ؿ�
	void endCurrentStage();
    
	//remove a cell from the connected array
	void removeCellFromConnectedArray();
    
    //play sound effect
    void playSelctedSoundEffect(ElementType pType);             //when grid cell clicked or selected
    void playClearSoundEffect();                                //when the connected cells clearing
    
    //draw or clear connected line between two cells
    void addConnectedLine();
    void cleanConnectedLine();
    
    //judge whether the cell can be insert into the connected array
    bool judgeGridCellCanInserted(unsigned int rIndex,unsigned int vIndex);
    
    void readPlayerProperty();
    
    void selectMagic(MagicType pID=kMagicType_None);
    bool judgeIsTriggerMagic();
    void triggerMagic(MagicType pID);
    
    void triggerWeapon(unsigned int pID);
    
    void statisticsDataPerRound();

private:
	unsigned int			mCoins;						//ÿһ�ؿ�(stage���ۼƵĽ��
	unsigned int 			mScore;						//ÿһ�ؿ��ۼƵĻ���
	unsigned int 			mRound;						//ÿһ�ؿ��ۼƵĻغ���
	unsigned int			mKilledMonster;				//ɱ���Ĺ���
	unsigned int			mCurrentShield;				//��ǰ�Ķ���
	unsigned int			mCurrentPotion;				//��ǰ��Ѫ��
    
    unsigned int            mCurShield;
    unsigned int            mCurPortion;
	
    //current valid magic in current game stage
	CCArray					*mMagicInStage;				//��ǰ�ؿ��п���ʹ�õ�ħ��
    
    //connected elements array
	CCArray					*mStageConnectedElements;	//ÿһ�غ����Ѿ�������Ԫ�أ���˳��洢Ԫ�ص����ͺͶ�Ӧcell�ı�ʶ���ɼӿ�ɾ��
    
    //current stage property
    GameStageProperty       mStageProperty;
    PlayerProperty          mPlayerProperty;
    
    MagicProperty           mMagic;
    
    CCArray                 *mGridPropertyContainer;
private:

};

#endif
