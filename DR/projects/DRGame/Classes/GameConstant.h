#ifndef _GAME_CONSTANT_H_
#define _GAME_CONSTANT_H_


//定义游戏常量
#define GENERAL_CHAR_LENGTH			128						//通用字符数组长度

//定义触摸事件响应优先级
#define TOUCH_EVENT_PRIORITY_DEFAULT	128
#define TOUCH_EVENT_PRIORITY_MID		256
#define TOUCH_EVENT_PRIORITY_TOP		512

//定义游戏界面网格的行数和列数
#define GRID_ROW_COUNT					6						//游戏界面网格的行数
#define GRID_VOLUME_COUNT				6						//游戏界面网格的列数

#define WIN_SIZE			CCDirector::sharedDirector()->getWinSize()

//定义网格cell的索引类型
enum GRIDINDEX_TYPE{
	kGRIDINDEX_TYPE_DEFAULT=0,									//自身
	kGRIDINDEX_TYPE_NEXT,										//下一个
	kGRIDINDEX_TYPE_PRE,										//下一个
};

//定义网格的行数和列数
#define GRID_ROW			6
#define GRID_VOLUME         6


#endif
