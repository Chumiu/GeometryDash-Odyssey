#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/GeodeUI.hpp>
using namespace geode::prelude;

class CreditsPopup : public Popup
{
protected:
    CCMenuItemSpriteExtra *m_fowardTabBtn = nullptr;
    CCMenuItemSpriteExtra *m_backTabBtn = nullptr;

    cocos2d::CCMenu *m_fowardTabMenu = nullptr;
    cocos2d::CCMenu *m_backTabMenu = nullptr;

    cocos2d::CCLayer *m_creditsmoddevLayer = nullptr;
    cocos2d::CCLayer *m_creditsrobLayer = nullptr;
    cocos2d::CCLayer *m_creditsOrgLayer = nullptr;
    cocos2d::CCLayer *m_creditsCreatorsLayer = nullptr;
    cocos2d::CCLayer *m_creditsArtLayer = nullptr;
    cocos2d::CCLayer *m_creditsPlayTestLayer = nullptr;
    cocos2d::CCLayer *m_creditsContestLevelsLayer = nullptr;

    cocos2d::extension::CCScale9Sprite *m_bgSprite02 = nullptr;
    cocos2d::extension::CCScale9Sprite *bgLayer = nullptr;
    CCLabelBMFont *creditsLabel = nullptr;

    int m_tab = 0;
    int m_lastTab = 6;

    bool init();
    void setupCreditsOrgTab();
    void setupCreditsCreatorsTab();
    void setupCreditsArtistsTab();
    void setupCreditsTestersTab();
    void setupCreditsModDeveloperTab();
    void setupCreditsSpecialThanksTab();
    void setupCreditsContestLevelsTab();
    void onDanky(CCObject *);
    void onNext(CCObject *);
    void onPrev(CCObject *);
    void changeTab();

public:
    static CreditsPopup *create();
};
