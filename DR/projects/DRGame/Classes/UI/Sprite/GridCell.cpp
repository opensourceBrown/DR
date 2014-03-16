#include "GridCell.h"

GridCell::GridCell():
    m_status(false),
    m_property(NULL),
    m_elementGridImg(NULL),
    m_AttackValueTTF(NULL),
    m_DefenceValueTTF(NULL),
    m_LifeValueTTF(NULL)
{
    m_property = new GridElementProperty();
}

GridCell::~GridCell()
{
    if (m_property != NULL) {
        delete m_property;
    }
//    CC_SAFE_RELEASE_NULL(m_property);
}

GridCell* GridCell::createWithFrameName(const char *pszFileName)
{
    GridCell *cell = new GridCell();
    if (cell && cell->initWith(pszFileName))
    {
        cell->autorelease();
        
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}

void GridCell::refreshMonsterPropertyLabel()
{
    if (m_AttackValueTTF != NULL) {
        CCString *attachValue=CCString::createWithFormat("%d",(int)m_property->mMonsterProperty.mDamage);
        m_AttackValueTTF->setString(attachValue->getCString());
        
        m_AttackValueTTF->setAnchorPoint(ccp(0.5,0.5));
        m_AttackValueTTF->setContentSize(CCSizeMake(20, 15));
    }
    
    if (m_DefenceValueTTF != NULL) {
        CCString *defenceValue=CCString::createWithFormat("%d",(int)m_property->mMonsterProperty.mDefence);
        m_DefenceValueTTF->setString(defenceValue->getCString());
        
        m_DefenceValueTTF->setAnchorPoint(ccp(0.5,0.5));
        m_DefenceValueTTF->setContentSize(CCSizeMake(20, 15));
    }
    
    if (m_LifeValueTTF != NULL) {
        CCString *lifeValue=CCString::createWithFormat("%d",(int)m_property->mMonsterProperty.mLife);
        m_LifeValueTTF->setString(lifeValue->getCString());
        
        m_LifeValueTTF->setAnchorPoint(ccp(0.5,0.5));
        m_LifeValueTTF->setContentSize(CCSizeMake(20, 15));
    }
}

bool GridCell::initWith(const char *pszFileName)
{
    bool tRet=false;
    
    do {
        CC_BREAK_IF(!pszFileName);
        m_elementGridImg=CCSprite::createWithSpriteFrameName(pszFileName);
        CC_BREAK_IF(!m_elementGridImg);
        this->setContentSize(m_elementGridImg->getContentSize());
        addChild(m_elementGridImg);
        
        tRet=true;
    } while (0);
    
    return tRet;
}

void GridCell::setCellProperty(GridElementProperty *pElement)
{
    m_property->mID=pElement->mID;
    m_property->mIndex.rIndex=pElement->mIndex.rIndex;
    m_property->mIndex.vIndex=pElement->mIndex.vIndex;
    m_property->mType=pElement->mType;
    
    m_property->mMonsterProperty.mType = pElement->mMonsterProperty.mType;
    m_property->mMonsterProperty.mSkillType = pElement->mMonsterProperty.mSkillType;
    m_property->mMonsterProperty.mID = pElement->mMonsterProperty.mID;
    m_property->mMonsterProperty.mName = pElement->mMonsterProperty.mName;
    m_property->mMonsterProperty.mDescription = pElement->mMonsterProperty.mDescription;
    m_property->mMonsterProperty.mDefence = pElement->mMonsterProperty.mDefence;
    m_property->mMonsterProperty.mLife = pElement->mMonsterProperty.mLife;
    m_property->mMonsterProperty.mMaxLife = pElement->mMonsterProperty.mMaxLife;
    m_property->mMonsterProperty.mDamage = pElement->mMonsterProperty.mDamage;
    
    m_property->setStatus(pElement->getStatus());
    do {

    } while (0);
    
    if (m_property->mType == kElementType_Monster) {
        constructMonsterCellEX();
    }
}

void GridCell::constructMonsterCellEX()
{
    do{
        CC_BREAK_IF(!m_property);
        CC_BREAK_IF(!m_property->mType==kElementType_Monster);
//        CCLog("damage:%f",m_property->mMonsterProperty.mDamage);
        CCString *attachValue=CCString::createWithFormat("%d",(int)m_property->mMonsterProperty.mDamage);
        if (m_AttackValueTTF == NULL) {
            m_AttackValueTTF = CCLabelTTF::create(attachValue->getCString(),"Marker Felt",14);
        } else {
            m_AttackValueTTF->setString(attachValue->getCString());
        }
        CC_BREAK_IF(!m_AttackValueTTF);
        m_AttackValueTTF->setAnchorPoint(ccp(0.5,0.5));
        m_AttackValueTTF->setContentSize(CCSizeMake(20, 15));
        m_AttackValueTTF->setColor(ccc3(0,255,0));
        m_AttackValueTTF->setPosition(ccp(m_elementGridImg->getPosition().x+m_elementGridImg->getContentSize().width,m_elementGridImg->getPosition().y+m_elementGridImg->getContentSize().height-m_AttackValueTTF->getContentSize().height));
        this->addChild(m_AttackValueTTF);
//        CCLog("defence:%f",m_property->mMonsterProperty.mDefence);
        CCString *defenceValue=CCString::createWithFormat("%d",(int)m_property->mMonsterProperty.mDefence);
        if (m_DefenceValueTTF == NULL) {
            m_DefenceValueTTF = CCLabelTTF::create(defenceValue->getCString(),"Marker Felt",14);
        } else {
            m_DefenceValueTTF->setString(defenceValue->getCString());
        }
        CC_BREAK_IF(!m_DefenceValueTTF);
        m_DefenceValueTTF->setAnchorPoint(ccp(0.5,0.5));
        m_DefenceValueTTF->setContentSize(CCSizeMake(20, 15));
        m_DefenceValueTTF->setColor(ccc3(0,255,0));
        m_DefenceValueTTF->setPosition(ccp(m_elementGridImg->getPosition().x+m_elementGridImg->getContentSize().width,m_elementGridImg->getPosition().y+m_elementGridImg->getContentSize().height-2*m_AttackValueTTF->getContentSize().height));
        this->addChild(m_DefenceValueTTF);
//        CCLog("life:%f",m_property->mMonsterProperty.mLife);
        CCString *lifeValue=CCString::createWithFormat("%d",(int)m_property->mMonsterProperty.mLife);
        if (m_LifeValueTTF == NULL) {
            m_LifeValueTTF = CCLabelTTF::create(lifeValue->getCString(),"Marker Felt",14);
        } else {
            m_LifeValueTTF->setString(lifeValue->getCString());
        }
        CC_BREAK_IF(!m_LifeValueTTF);
        m_LifeValueTTF->setAnchorPoint(ccp(0.5,0.5));
        m_LifeValueTTF->setContentSize(CCSizeMake(20, 15));
        m_LifeValueTTF->setColor(ccc3(255,0,0));
        m_LifeValueTTF->setPosition(ccp(m_elementGridImg->getPosition().x+m_elementGridImg->getContentSize().width,m_elementGridImg->getPosition().y+m_elementGridImg->getContentSize().height-3*m_AttackValueTTF->getContentSize().height));
        this->addChild(m_LifeValueTTF);
    }while(0);
}

