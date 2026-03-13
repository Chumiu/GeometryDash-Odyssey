#pragma once
using namespace geode::prelude;

class DeveloperLayer : public CCLayer
{
protected:
    CCSprite *m_background = nullptr;

    CCMenu * m_talkMenu = nullptr;
    CCMenu * m_levelsMenu = nullptr;

    virtual bool init();
    virtual void keyBackClicked();
    void onBack(CCObject *);

    void onTalk(CCObject *);
    void onLevel(CCObject *);
    void onPopup(CCObject *);
    void onComic(CCObject *);

    void onTalkNav(CCObject *);
    void onLevelNav(CCObject *);

    void updateTalk();
    void updateLevels();

public:
    unsigned int m_talkPage = 0;
    unsigned int m_levelPage = 0;

    static DeveloperLayer *create();
    CCScene *scene();
};