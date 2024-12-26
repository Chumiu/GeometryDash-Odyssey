#pragma once
using namespace geode::prelude;

class OdysseyEndCreditsLayer : public cocos2d::CCLayer
{
protected:
    CCSprite *m_background;
    CCSize m_winSize;
    CCLayer *endCreditsLayer;

    CCArray *row1CreditArray;
    CCArray *row2CreditArray;
    CCArray *row3CreditArray;
    CCArray *row4CreditArray;
    CCArray *row5CreditArray;
    CCArray *row6CreditArray;
    CCArray *row7CreditArray;
    CCArray *row8CreditArray;
    CCArray *row9CreditArray;
    CCArray *row10CreditArray;
    CCArray *row11CreditArray;
    int speed = 0;
    virtual bool init();
    virtual void keyBackClicked();
    virtual void createEndCredits();
    void onBack(cocos2d::CCObject *);
public:
    void backMenuLayer();
    
public:
    static OdysseyEndCreditsLayer *create();
    static CCScene *scene();
};