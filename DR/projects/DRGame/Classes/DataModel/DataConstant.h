//
//  DataConstant.h
//  DRGame
//
//  Created by magic on 14-2-18.
//
//

#ifndef DRGame_DataConstant_h
#define DRGame_DataConstant_h

#include "GameConstant.h"

//定义游戏消除元素类型
typedef enum{
    kElementType_Monster=0,					//怪
    kElementType_Sword,						//剑
    kElementType_Bow,						//弓
    kElementType_Coin,						//金币
    kElementType_Potion,					//血瓶
    kElementType_Shield,					//盾
}ElementType;

//定义怪物的类型
typedef enum{
    kBustyType_Common=0,              	   //普通怪
    kBustyType_Boss,                  	   //boss怪
}BustyType;

//注：magic，与游戏界面cell对应的结构体暂时由我来定义吧，我下面添加了，暂时现不用你定义的这个结构体，因为后续这块可能要修改
//比如怪，虽然分普通怪和boss怪，但是他们的配置是放在一个文件中的，通过id区分就可以了，所以下面的GameLayerElement和BlockData结构暂时我现不用了
//暂时我先用自己定义的,稍后我们可以过一下这块
//定义界面元素结构体
typedef struct{
	int     attack;        //剑攻击力
    int     monsterAttack; //怪物总攻击力
    int     defence;       //当前防御力
    int     maxdefence;    //最大防御力
    int     life;          //生命值
    int     maxLife;       //最大生命值
    
    int     roundNumber;   //回合数
    int     score;         //得分
} GameLayerElement;

//消除元素对应的结构体
typedef struct {
    ElementType elementType;    //游戏消除元素类型
    int         attackPower;    //怪物攻击力
    int         defencePower;   //怪物防御力
    BustyType   bustyType;      //怪物类型(boss or 普通怪)
} BlockData;

static inline GameLayerElement GameLayerElementMake(
                                                    int attack,
                                                    int monsterAttack,
                                                    int defence,
                                                    int maxdefence,
                                                    int life,
                                                    int maxlife,
                                                    int roundNumber,
                                                    int score
                                                    ) {
    GameLayerElement gameLayerElement;
    gameLayerElement.attack = attack;
    gameLayerElement.monsterAttack = monsterAttack;
    gameLayerElement.defence = defence;
    gameLayerElement.maxdefence = maxdefence;
    gameLayerElement.life = life;
    gameLayerElement.maxLife = maxlife;
    gameLayerElement.roundNumber = roundNumber;
    gameLayerElement.score = score;
    return gameLayerElement;
}

static inline BlockData BlockDataMake(
                                      ElementType elementType,
                                      int   attackPower,
                                      int   defencePower,
                                      BustyType bustyType
                                      ) {
    BlockData   blockData;
    blockData.elementType = elementType;
    blockData.attackPower = attackPower;
    blockData.defencePower = defencePower;
    blockData.bustyType = bustyType;
    return blockData;
}

//定义boss怪的类型
typedef enum{
    kBossBustyType_Chaotic=0,
    kBossBustyType_Poisonous,
    kBossBustyType_Healer,
    kBossBustyType_Spiky,
    kBossBustyType_Acidic,
    kBossBustyType_Vampire,
    kBossBustyType_Golden,
    kBossBustyType_Freezing,
    kBossBustyType_Mage,
    kBossBustyType_Corrosive,
    kBossBustyType_Overseer,
    kBossBustyType_Flaming,
    kBossBustyType_Trampling,
    kBossBustyType_Kamikaze,
}BossBustyType;

//定义魔法类型
typedef enum{
    kMagicType_Steal=0,
    kMagicType_Fireball,
    kMagicType_CounterAttack,
    kMagicType_GoldenTouch,
    kMagicType_BoostHealth,
    kMagicType_BigGameHunter,
    kMagicType_Shatter,
    kMagicType_BoostGold,
    kMagicType_Teleport,
    kMagicType_Heal,
}MagicType;

//定义魔法的结构
typedef struct{
	MagicType				mMagicType;
	unsigned int			mID;
	unsigned int			mCDTime;
}MagicProperty;

//定义职业类型
typedef enum{
    kOccupationType_Human=0,					//人类
    kOccupationType_Bower,						//弓手
    kOccupationType_Hunter,						//猎人
    kOccupationType_Master,						//法师
    kOccupationType_Barbarian,					//蛮族
    kOccupationType_Assassin,					//暗杀者
    kOccupationType_Soldier,					//战士
    kOccupationType_Paladin,					//圣骑士
    kOccupationType_Trader,						//商人
}OccupationType;

//定义装备结构
typedef struct{
	char mName[GENERAL_CHAR_LENGTH];			//装备名称
	unsigned char mLevel;						//级别
	unsigned int mCoin;							//该装备所需的金币
	unsigned int mPay;							//购买或升级到该装备所需要的支付费用
	unsigned int mCompositeExperience;			//合成该装备时需要的经验值
	unsigned int mUpdateExperience;				//升级该装备时需要的经验值
	unsigned int mUpdatePreWeapon;				//升级前一个装备
	unsigned int mMaxHealth;					//最大生命值
	unsigned int mDefencePerShield;				//每个盾的防御力
	unsigned int mMaxShield;					//最多持有盾数
	unsigned char mHealthPerPotion;				//每个雪瓶的恢复值
	unsigned char mBasicDamage;					//基本攻击力
	unsigned char mWeaponDamage;				//武器攻击力
	float 	mLeech;								//吸血，通过攻击可以恢复的血量
	float 	mCriticalDamageRate;				//暴击概率
	float	mPierce;							//穿透率
}EquipmentProperty;

//定义职业结构
typedef struct{
	char mName[GENERAL_CHAR_LENGTH];			//职业名称
	unsigned char mLevel;						//级别
	unsigned int mCoin;							//该职业所需的金币
	unsigned int mPay;							//购买或升级到该职业所需要的支付费用
	unsigned int mMaxHealth;					//最大生命值
	unsigned int mDefencePerShield;				//每个盾的防御力
	unsigned int mMaxShield;					//最多持有盾数
	unsigned char mHealthPerPotion;				//每个雪瓶的恢复值
	unsigned char mBasicDamage;					//基本攻击力
	unsigned char mWeaponDamage;				//武器攻击力
	float 	mLeech;								//吸血，通过攻击可以恢复的血量
	float 	mCriticalDamageRate;				//暴击概率
	float	mPierce;							//穿透率
}OccupationProperty;

//定义玩家结构
typedef struct{
	unsigned int mMaxHealth;					//最大生命值
	unsigned int mDefencePerShield;				//每个盾的防御力
	unsigned int mMaxShield;					//最多持有盾数
	unsigned char mHealthPerPotion;				//每个雪瓶的恢复值
	unsigned char mBasicDamage;					//基本攻击力
	unsigned char mWeaponDamage;				//武器攻击力
	float 	mLeech;								//吸血，通过攻击可以恢复的血量
	float 	mCriticalDamageRate;				//暴击概率
	float	mPierce;							//穿透率
	
}PlayerProperty;

//定义怪结构
typedef struct{
	BustyType               mType;              
	BossBustyType			mSkillType;
	unsigned int			mID;
	char					mName[GENERAL_CHAR_LENGTH];
	char					mDescription[GENERAL_CHAR_LENGTH];
	unsigned int			mDefence;
	unsigned int			mDamage;
	unsigned int			mPotion;
}BustyProperty;

//定义关卡结构
typedef struct{
    unsigned int             mID;					//πÿø®id                //关卡id
    
	float					mCommMosterRate;		//∆’Õ®π÷≥ˆœ÷µƒ∏≈¬       //普通怪出现的概率
	float					mCoinRate;			//Ω±“≥ˆœ÷µƒ∏≈¬             //金币出现的概率
	float					mPotionRate;			//—™∆ø≥ˆœ÷µƒ∏≈¬         //血瓶出现的概率
	float					mBossMosterRate;		//bossπ÷≥ˆœ÷µƒ∏≈¬       //boss怪出现的概率
	float					mShieldRate;			//∂‹≥ˆœ÷µƒ∏≈¬           //盾出现的概率
    float                   mSwordRate;                                     //剑出现的概率
    float                   mBowRate;                                       //弓出现的概率
	unsigned int				mPassCondID;			//πÿø®Õ®π˝Ãıº˛µƒid  //闯关通过的条件id
}GameStageProperty;

//grid cell index struct
typedef struct{
	unsigned int            rIndex;			//––À˜“˝£∫∆ º÷µŒ™1             //行索引
	unsigned int            vIndex;			//¡–À˜“˝£∫∆ º÷µŒ™1             //列索引
}GIRDCELL_INDEX;

//grid cell data struct
typedef struct{
	GIRDCELL_INDEX          mIndex;             //索引
	ElementType             mType;              //cell对应的类型：怪、盾、、、、、
	unsigned int            mID;                //怪id
    
    void init(){
        mIndex.rIndex=0;
        mIndex.vIndex=0;
        mType=kElementType_Coin;
        mID=0;
    }
}GridElementProperty;

#endif