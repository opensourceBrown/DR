#ifndef _GENERAL_DATAMODEL_H_
#define _GENERAL_DATAMODEL_H_

#include "cocos2d.h"
#include "GameConstant.h"

USING_NS_CC;


//����ͨ������ģ��

//������Ϸ����Ԫ������
typedef enum{
    kElementType_Monster=0,					//��
    kElementType_Sword,						//��
    kElementType_Bow,						//��
    kElementType_Coin,						//���
    kElementType_Posion,					//Ѫƿ
}ElementType;

//���������
typedef enum{
    kBustyType_Common=0,              	   //��ͨ��
    kBustyType_Boss,                  	   //boss��
}BustyType;

//����boss�ֵ�����
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

//����ħ������
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
	
//����ħ���Ľṹ
typedef struct{
	MagicType				mMagicType;
	unsigned int			mID;
	unsigned int			mCDTime;
}MagicProperty;

//����ְҵ����
typedef enum{
    kOccupationType_Human=0,					//����
    kOccupationType_Bower,						//����
    kOccupationType_Hunter,						//����
    kOccupationType_Master,						//��ʦ
    kOccupationType_Barbarian,					//����
    kOccupationType_Assassin,					//��ɱ��
    kOccupationType_Soldier,					//սʿ
    kOccupationType_Paladin,					//ʥ��ʿ
    kOccupationType_Trader,						//����
}OccupationType;

//����װ���ṹ
typedef struct{
	char mName[GENERAL_CHAR_LENGTH];			//װ������
	unsigned char mLevel;						//����
	unsigned int mCoin;							//��װ������Ľ��
	unsigned int mPay;							//�������������װ������Ҫ��֧������
	unsigned int mCompositeExperience;			//�ϳɸ�װ��ʱ��Ҫ�ľ���ֵ
	unsigned int mUpdateExperience;				//������װ��ʱ��Ҫ�ľ���ֵ
	unsigned int mUpdatePreWeapon;				//����ǰһ��װ��
	unsigned int mMaxHealth;					//�������ֵ
	unsigned int mDefencePerShield;				//ÿ���ܵķ�����
	unsigned int mMaxShield;					//�����ж���
	unsigned char mHealthPerPotion;				//ÿ��ѩƿ�Ļָ�ֵ
	unsigned char mBasicDamage;					//����������
	unsigned char mWeaponDamage;				//����������
	float 	mLeech;								//��Ѫ��ͨ���������Իָ���Ѫ��
	float 	mCriticalDamageRate;				//��������
	float	mPierce;							//��͸��
}EquipmentProperty;

//����ְҵ�ṹ
typedef struct{
	char mName[GENERAL_CHAR_LENGTH];			//ְҵ����
	unsigned char mLevel;						//����
	unsigned int mCoin;							//��ְҵ����Ľ��
	unsigned int mPay;							//�������������ְҵ����Ҫ��֧������
	unsigned int mMaxHealth;					//�������ֵ
	unsigned int mDefencePerShield;				//ÿ���ܵķ�����
	unsigned int mMaxShield;					//�����ж���
	unsigned char mHealthPerPotion;				//ÿ��ѩƿ�Ļָ�ֵ
	unsigned char mBasicDamage;					//����������
	unsigned char mWeaponDamage;				//����������
	float 	mLeech;								//��Ѫ��ͨ���������Իָ���Ѫ��
	float 	mCriticalDamageRate;				//��������
	float	mPierce;							//��͸��
}OccupationProperty;

//������ҽṹ
typedef struct{
	unsigned int mMaxHealth;					//�������ֵ
	unsigned int mDefencePerShield;				//ÿ���ܵķ�����
	unsigned int mMaxShield;					//�����ж���
	unsigned char mHealthPerPotion;				//ÿ��ѩƿ�Ļָ�ֵ
	unsigned char mBasicDamage;					//����������
	unsigned char mWeaponDamage;				//����������
	float 	mLeech;								//��Ѫ��ͨ���������Իָ���Ѫ��
	float 	mCriticalDamageRate;				//��������
	float	mPierce;							//��͸��
	
}PlayerProperty;

//����ֽṹ
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

//����ؿ��ṹ
typedef struct{
    unsigned int            mID;
    
}GameStageProperty;

class GeneralDataModel : public CCObject
{
public:
    GeneralDataModel();
    ~GeneralDataModel();
};

#endif
