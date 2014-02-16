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

	//生成grid cell
	void generateGridCell(unsigned int rIndex,unsigned int vIndex);
	
	//更新grid cell：位置和索引
	void updateGridCell(unsigned int rIndex,unsigned int vIndex);
	
	//判断本关卡游戏是否结束
	bool judgeGameIsEnd();

	//判断相连的元素是否可以消除
	bool judgeConnectedElementsCanClear();
	
	//判断滑动过程中的元素是否可以相连
	bool judgeElementsCanConnected();



	
private:
	unsigned int			mCoins;						//每一关卡(stage）累计的金币
	unsigned int 			mScore;						//每一关卡累计的积分
	unsigned int 			mRound;						//每一关卡累计的回合数
	unsigned int			mKilledMonster;				//杀死的怪数
	unsigned int			mCurrentShield;				//当前的盾数
	unsigned int			mCurrentPotion;				//当前的血量
	
	CCArray					*mMagicInStage;				//当前关卡中可以使用的魔法
	CCArray					*mStageConnectedElements;	//每一回合中已经相连的元素（按顺序存储元素的类型和对应cell的标识，可加可删）
	CCArray					*mGridCellContainer;
	

private:

};

#endif
