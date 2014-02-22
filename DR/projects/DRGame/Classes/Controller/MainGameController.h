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
    
    //生成grid cell
	bool generateGridCell(unsigned int rIndex,unsigned int vIndex);
    
    //get the grid cell property data struct
    GridElementProperty getGridElementProperty(unsigned int rIndex,unsigned int vIndex);
    
    //判断滑动过程中的元素是否可以相连
	bool judgeElementsCanConnected();
    
    //insert a cell into the connected array
	void insertCellIntoConnectedArray(unsigned int rIndex,unsigned int vIndex);

private:
    bool initWith();
	
	//更新grid cell：位置和索引
	void updateGridCell(unsigned int rIndex,unsigned int vIndex);
	
	//判断本关卡游戏是否结束
	bool judgeGameIsEnd();

	//判断相连的元素是否可以消除
	bool judgeConnectedElementsCanClear();
	
	
    
	//remove a cell from the connected array
	void removeCellFromConnectedArray(unsigned int pIndex);
    
	//insert a cell into the cell container
	void insertCellIntoGridContainer(unsigned int pIndex);
    
	//remove a cell from the cell container(clear a cell from the screen for connecting)
	void removeCellFromGridContainer(unsigned int pIndex);

	
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
	
    GridElementProperty     mGridPropertyContainer[GRID_ROW*GRID_VOLUME];
private:

};

#endif
