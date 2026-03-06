#pragma once
using namespace geode::prelude;

class DeveloperLayer : public cocos2d::CCLayer
{
protected:
    CCSprite *m_background = nullptr;

    virtual bool init();
    virtual void keyBackClicked();
    void onBack(cocos2d::CCObject *);

    void onCarp02(CCObject *);
    void onCarp03(CCObject *);
    void onCarp04(CCObject *);
    void onStoryDialogNew(CCObject *);
    void onPopup(CCObject *);

    void onComic(CCObject *);
    void onLevel(CCObject *);
    void onOgre(CCObject *);

public:
    static DeveloperLayer *create();
    CCScene *scene();
};