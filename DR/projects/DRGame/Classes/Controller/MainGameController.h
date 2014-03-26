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
    
    //…˙≥…grid cell
	bool generateGridCell(unsigned int rIndex,unsigned int vIndex);
    
    //get the grid cell property data struct
    GridElementProperty *getGridElementProperty(unsigned int rIndex,unsigned int vIndex);
    
    //≈–∂œª¨∂Øπ˝≥Ã÷–µƒ‘™Àÿ «∑Òø…“‘œ‡¡¨
    void processGridCellSelected(unsigned int rIndex,unsigned int vIndex);
    
    //insert a cell into the connected array
	void insertCellIntoConnectedArray(unsigned int rIndex,unsigned int vIndex);
    
    //≈–∂œœ‡¡¨µƒ‘™Àÿ «∑Òø…“‘œ˚≥˝
	bool judgeConnectedElementsCanClear();
    
    //reset mStageConnectedElements:remove all children
    void resetStageConnectedElements();
    
	//œ˚≥˝œ‡¡¨‘™Àÿ
	bool clearConnectedElements();      //if there is any monster who is undead, return YES
    
    OccupationType getPlayerOccupation(){ return mPlayerProperty.mType; }
    PlayerProperty getPlayerProperty(){
        mPlayerProperty.init();
        return mPlayerProperty;
    }
    
    void updateStatusData();
    
    void selectMagic(MagicType pID=kMagicType_None);
    
    void equipWeapon(unsigned int pID);
    void disableWeapon(unsigned int pID);
    
    void triggerBossSkill();
    
    void refreshWeapon();

private:
    bool initWith();
	
	//∏¸–¬grid cell£∫Œª÷√∫ÕÀ˜“˝
	//void updateGridCell(unsigned int rIndex,unsigned int vIndex);
	
	//≈–∂œ±æπÿø®”Œœ∑ «∑ÒΩ· ¯
	bool judgeGameStageIsEnd();
    
    //Ω· ¯µ±«∞”Œœ∑πÿø®
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
    
    bool judgeIsTriggerMagic(CCArray *pArray);
    void triggerMagic(MagicType pID,CCArray *pArray);
    
    void triggerWeapon(unsigned int pID);
    
    void recoverMonsterLifeFull();
    
    void statisticsDataPerRound();
    int  computeTotalDamageOfRound();
    void resetStageStatusData();

private:
	unsigned int			mCoins;						//√ø“ªπÿø®(stage£©¿€º∆µƒΩ±“
	unsigned int 			mScore;						//√ø“ªπÿø®¿€º∆µƒª˝∑÷
	unsigned int 			mRound;						//√ø“ªπÿø®¿€º∆µƒªÿ∫œ ˝
	unsigned int			mKilledMonster;				//…±À¿µƒπ÷ ˝
	unsigned int			mCurrentShield;				//µ±«∞µƒ∂‹ ˝
	unsigned int			mCurrentPotion;				//µ±«∞µƒ—™¡ø
    
    int                     mCurShield;
    int                     mCurPortion;
    int                     mCurStageKillMonster;
    int                     mCurStageCoin;
    int                     mCurStageScore;
    int                     mCurStageRound;
	
    int                     mTotalDamagePerRound;       //damage of current Round
    bool                    mSpiky;                     //判断当前状态是否反弹伤害
    int                     mCurrentSpikyCount;         //反弹boss的数量
    bool                    mMageEnable;                //场上存在Mage Boss时，此值为true，禁止释放魔法
    
    //current valid magic in current game stage
	CCArray					*mMagicInStage;				//µ±«∞πÿø®÷–ø…“‘ π”√µƒƒß∑®
    
    //connected elements array
	CCArray					*mStageConnectedElements;	//√ø“ªªÿ∫œ÷–“—æ≠œ‡¡¨µƒ‘™Àÿ£®∞¥À≥–Ú¥Ê¥¢‘™Àÿµƒ¿‡–Õ∫Õ∂‘”¶cellµƒ±Í ∂£¨ø…º”ø……æ£©
    
    //current stage property
    GameStageProperty       mStageProperty;
    PlayerProperty          mPlayerProperty;
    
    MagicProperty           mMagic;
    
    CCArray                 *mGridPropertyContainer;
private:

};

#endif
