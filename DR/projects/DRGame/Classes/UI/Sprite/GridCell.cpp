#include "GridCell.h"

GridCell::GridCell():
    m_status(false),
    m_property(NULL),
    m_elementGridImg(NULL)
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

bool GridCell::initWith(const char *pszFileName)
{
    bool tRet=false;
    
    do {
        CC_BREAK_IF(!pszFileName);
        m_elementGridImg=CCSprite::createWithSpriteFrameName(pszFileName);
        CC_BREAK_IF(!m_elementGridImg);
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
    
    constructMonsterCellEX();
}

void GridCell::constructMonsterCellEX()
{
    do{
        CC_BREAK_IF(!m_property);
        CC_BREAK_IF(!m_property->mType==kElementType_Monster);
        
        CCString *attachValue=CCString::createWithFormat("%d",(int)m_property->mMonsterProperty.mDamage);
        CCLabelTTF *tAttackValueTTF = CCLabelTTF::create(attachValue->getCString(),"Marker Felt",14);
        CC_BREAK_IF(!tAttackValueTTF);
        tAttackValueTTF->setAnchorPoint(ccp(0.5,0.5));
        tAttackValueTTF->setContentSize(CCSizeMake(20, 15));
        tAttackValueTTF->setColor(ccc3(0,255,0));
        tAttackValueTTF->setPosition(ccp(m_elementGridImg->getPosition().x+m_elementGridImg->getContentSize().width,m_elementGridImg->getPosition().y+m_elementGridImg->getContentSize().height-tAttackValueTTF->getContentSize().height));
        this->addChild(tAttackValueTTF);
        
        CCString *defenceValue=CCString::createWithFormat("%d",(int)m_property->mMonsterProperty.mDamage);
        CCLabelTTF *tDefenceValueTTF = CCLabelTTF::create(defenceValue->getCString(),"Marker Felt",14);
        CC_BREAK_IF(!tDefenceValueTTF);
        tDefenceValueTTF->setAnchorPoint(ccp(0.5,0.5));
        tDefenceValueTTF->setContentSize(CCSizeMake(20, 15));
        tDefenceValueTTF->setColor(ccc3(0,255,0));
        tDefenceValueTTF->setPosition(ccp(m_elementGridImg->getPosition().x+m_elementGridImg->getContentSize().width,m_elementGridImg->getPosition().y+m_elementGridImg->getContentSize().height-2*tAttackValueTTF->getContentSize().height));
        this->addChild(tDefenceValueTTF);
        
        CCString *lifeValue=CCString::createWithFormat("%d",(int)m_property->mMonsterProperty.mDamage);
        CCLabelTTF *tLifeValueTTF = CCLabelTTF::create(lifeValue->getCString(),"Marker Felt",14);
        CC_BREAK_IF(!tLifeValueTTF);
        tLifeValueTTF->setAnchorPoint(ccp(0.5,0.5));
        tLifeValueTTF->setContentSize(CCSizeMake(20, 15));
        tLifeValueTTF->setColor(ccc3(255,0,0));
        tLifeValueTTF->setPosition(ccp(m_elementGridImg->getPosition().x+m_elementGridImg->getContentSize().width,m_elementGridImg->getPosition().y+m_elementGridImg->getContentSize().height-3*tAttackValueTTF->getContentSize().height));
        this->addChild(tLifeValueTTF);
    }while(0);
}

