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
    kElementType_UnDefined,
    kElementType_Monster=1,					//怪
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
    int     monsterAttack;
    int     defence;
    int     life;
    int     maxLife;
    
    BustyType   bustyType;      //monster type(boss or common)
} MonsterProperty;

//定义boss怪的类型
typedef enum{
    kBossBustyType_None=0,
    kBossBustyType_Chaotic  = 1,         //每一回合随机移动自己的地方
    kBossBustyType_Poisonous= 2,       //每次攻击会使Player的状态变成毒。毒的效果是让Player每一回合受到最大生命之的１０％的伤害。无法被盾抵抗。效果持续５回合。
    kBossBustyType_Healer   = 3,          //让所有受到伤害的怪兽回复生命值到最大值。
    kBossBustyType_Spiky    = 4,           //每次受到伤害会把同等伤害反弹给Player
    kBossBustyType_Acidic   = 5,          //每一回合把一个血瓶变成酸。删除酸的时候Player会受到跟这个Ｂｏｓｓ的攻击力同等的伤害。
    kBossBustyType_Vampire  = 6,         //每次对Player攻击时，自己会回复同等生命值。(Completed)
    kBossBustyType_Golden   = 7,          //每一回合Boss的头上的数字会减少，到0时，Boss会逃跑。
    kBossBustyType_Freezing = 8,        //随机把自己周围的２个block冰冻。被冰冻的block无法被消除。每一回合被冰冻的block都会重新判断。
    kBossBustyType_Mage     = 9,            //此Ｂｏｓｓ出现时无法使用魔法
    kBossBustyType_Corrosive= 10,       //此Ｂｏｓｓ出现时无法回复盾
    kBossBustyType_Overseer = 11,        //每一回合把一个剑变成怪兽
    kBossBustyType_Flaming  = 12,         //使自己周围block燃烧，如果删掉燃烧的block，Player会受到跟此Boss同等的伤害。
    kBossBustyType_Trampling= 13,       //每一回合随机破坏一个剑或者盾，删除被坏的block没有任何效果会发生。(Magic is Coding)
    kBossBustyType_Kamikaze = 14,        //每一回合Boss的头上的数字会减少，到0时，Player的血量会变成一半。之后Count Down再次开始。
}BossBustyType;

//定义魔法类型
typedef enum{
    kMagicType_None=0,
    kMagicType_Steal,
    kMagicType_Fireball,
    kMagicType_CounterAttack,
    kMagicType_GoldenTouch,
    kMagicType_BoostHealth,
    kMagicType_BigGameHunter,
    kMagicType_Shatter,
    kMagicType_BoostGold,
    kMagicType_Teleport,
    kMagicType_Heal,
    kMagicType_TreasureChamber,
    kMagicType_ManaPotion,
    kMagicType_Earthquake,
    kMagicType_Scavenge,
}MagicType;

//定义魔法的结构
typedef struct{
	MagicType				mMagicType;
	unsigned int			mID;
    bool                    mActive;        //魔法是否被激活
	int			mCDTime;
    
    void init(){
        mMagicType=kMagicType_None;
        mID=0;
        mActive = false;
        mCDTime=0;
    }
}MagicProperty;

//定义职业类型
typedef enum{
    kOccupationType_Human=0,					//人类
    kOccupationType_Bower,						//弓手
    kOccupationType_Pastor,                     //牧师
    kOccupationType_Hunter,						//猎人
    kOccupationType_Master,						//法师
    kOccupationType_Barbarian,					//蛮族
    kOccupationType_Assassin,					//暗杀者
    kOccupationType_Soldier,					//战士
    kOccupationType_Paladin,					//圣骑士
    kOccupationType_Trader,						//商人
}OccupationType;

//玩家状态
typedef enum {
    kPlayerStatus_Normal=0,                     //正常状态
    kPlayerStatus_Poisonous,                    //中毒
}PlayerStatus;

//定义装备结构
typedef struct{
	char mName[GENERAL_CHAR_LENGTH];			//装备名称
    unsigned int  mID;                          //id
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
    OccupationType mType;                       //类型
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
    
    void init(){
        mType=kOccupationType_Human;
        mLevel=0;
        mCoin=0;
        mPay=0;
        mMaxHealth=0;
        mDefencePerShield=0;
        mMaxShield=0;
        mHealthPerPotion=0;
        mBasicDamage=0;
        mWeaponDamage=0;
        mLeech=0;
        mCriticalDamageRate=0;
        mPierce=0;
    }
}OccupationProperty;



//定义玩家结构
typedef struct{
    OccupationType mType;
    unsigned int mWeaponID;                     //武器id
	unsigned int mMaxHealth;					//最大生命值
	unsigned int mDefencePerShield;				//每个盾的防御力
	unsigned int mMaxShield;					//最多持有盾数
	unsigned char mHealthPerPotion;				//每个雪瓶的恢复值
	unsigned char mBasicDamage;					//基本攻击力
	unsigned char mWeaponDamage;				//武器攻击力
	float 	mLeech;								//吸血，通过攻击可以恢复的血量
	float 	mCriticalDamageRate;				//暴击概率
	float	mPierce;							//穿透率
    PlayerStatus mStatus;                       //玩家状态
    unsigned int mValidRound;                   //对于特殊的boss技能使用，一般不用
	
    void init(){
        mType=kOccupationType_Human;
        mWeaponID=0;
        mMaxHealth=50;
        mDefencePerShield=3;
        mMaxShield=3;
        mHealthPerPotion=1;
        mBasicDamage=2;
        mWeaponDamage=3;
        mLeech=0;
        mCriticalDamageRate=0;
        mPierce=0;
        mStatus=kPlayerStatus_Normal;
        mValidRound=0;
    }
}PlayerProperty;

//定义怪结构
typedef struct{
	BustyType               mType;                  //boss or normal
	BossBustyType			mSkillType;
	unsigned int			mID;
	const char*				mName;
	const char*				mDescription;
    float                   mDefence;
    float                   mLife;
    float                   mMaxLife;
    float                   mDamage;
    unsigned int            mValidRound;            //有效回合数
}BustyProperty;

//定义关卡结构
typedef struct{
    unsigned int             mID;					//barrier id
    
	float					mCommMosterRate;		//appear rate of normal monster
	float					mCoinRate;              //appear rate of coins
	float					mPotionRate;			//appear rate of potion
	float					mBossMosterRate;		//appear rate of boss
	float					mShieldRate;			//appear rate of shield
    float                   mSwordRate;             //appear rate of sword
    float                   mBowRate;               //appear rate of bow
	unsigned int				mPassCondID;		//condition of pass barrier
}GameStageProperty;

//grid cell index struct
typedef struct{
	unsigned int            rIndex;			//––À˜“˝£∫∆ º÷µŒ™1             //行索引
	unsigned int            vIndex;			//¡–À˜“˝£∫∆ º÷µŒ™1             //列索引
}GIRDCELL_INDEX;

#endif