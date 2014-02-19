//
//  DataConstant.h
//  DRGame
//
//  Created by magic on 14-2-18.
//
//

#ifndef DRGame_DataConstant_h
#define DRGame_DataConstant_h

//定义游戏消除元素类型
typedef enum{
    kElementType_Monster=0,					//怪
    kElementType_Sword,						//剑
    kElementType_Bow,						//弓
    kElementType_Coin,						//金币
    kElementType_Medicine,					//血瓶
}ElementType;

//ÂÆö‰πâÊÄ™Á±ªÂûã
typedef enum{
    kBustyType_Common=0,              	   //普通怪
    kBustyType_Boss,                  	   //boss怪
}BustyType;

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
    unsigned int             mID;					//πÿø®id
    
	float					mCommMosterRate;		//∆’Õ®π÷≥ˆœ÷µƒ∏≈¬
	float					mCoinRate;			//Ω±“≥ˆœ÷µƒ∏≈¬
	float					mPotionRate;			//—™∆ø≥ˆœ÷µƒ∏≈¬
	float					mBossMosterRate;		//bossπ÷≥ˆœ÷µƒ∏≈¬
	float					mShieldRate;			//∂‹≥ˆœ÷µƒ∏≈¬
	unsigned int				mPassCondID;			//πÿø®Õ®π˝Ãıº˛µƒid
}GameStageProperty;

#endif