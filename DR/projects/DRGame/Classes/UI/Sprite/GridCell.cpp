#include "GridCell.h"

GridCell::GridCell():
    m_status(false),
    m_property(NULL)
{
//    m_property = new GridElementProperty();
}

GridCell::~GridCell()
{
//    if (m_property != NULL) {
//        delete m_property;
//    }
    CC_SAFE_RELEASE_NULL(m_property);
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
        CCSprite *gridImg=CCSprite::createWithSpriteFrameName(pszFileName);
        CC_BREAK_IF(!gridImg);
        addChild(gridImg);
        
        tRet=true;
    } while (0);
    
    return tRet;
}

void GridCell::setCellProperty(GridElementProperty *pElement)
{
//    m_property->mID=pElement->mID;
//    m_property->mIndex.rIndex=pElement->mIndex.rIndex;
//    m_property->mIndex.vIndex=pElement->mIndex.vIndex;
//    m_property->mType=pElement->mType;
    do {
        CC_BREAK_IF(!pElement);
        m_property=pElement;
        m_property->retain();
    } while (0);
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
        tAttackValueTTF->setColor(ccc3(0,0,255));
//        tAttackValueTTF->setPosition(ccp(tMonster->getPosition().x,tMonster->getPosition().y-tMonster->getContentSize().height));
//        this->addChild(tAttackValueTTF);
        
        CCString *defenceValue=CCString::createWithFormat("%d",(int)m_property->mMonsterProperty.mDamage);
        CCLabelTTF *tDefenceValueTTF = CCLabelTTF::create(defenceValue->getCString(),"Marker Felt",14);
        CC_BREAK_IF(!tDefenceValueTTF);
        tDefenceValueTTF->setAnchorPoint(ccp(0.5,0.5));
        tDefenceValueTTF->setColor(ccc3(0,0,255));
//        tDefenceValueTTF->setPosition(ccp(tMonster->getPosition().x,tMonster->getPosition().y-tMonster->getContentSize().height));
//        this->addChild(tDefenceValueTTF);
        
        CCString *lifeValue=CCString::createWithFormat("%d",(int)m_property->mMonsterProperty.mDamage);
        CCLabelTTF *tLifeValueTTF = CCLabelTTF::create(lifeValue->getCString(),"Marker Felt",14);
        CC_BREAK_IF(!tLifeValueTTF);
        tLifeValueTTF->setAnchorPoint(ccp(0.5,0.5));
        tLifeValueTTF->setColor(ccc3(0,0,255));
//        tLifeValueTTF->setPosition(ccp(tMonster->getPosition().x,tMonster->getPosition().y-tMonster->getContentSize().height));
//        this->addChild(tLifeValueTTF);
    }while(0);
}

