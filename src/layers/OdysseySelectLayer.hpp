#pragma once
#include <Geode/ui/GeodeUI.hpp>
using namespace geode::prelude;

class OdysseySelectLayer : public CCLayer, GJDropDownLayerDelegate
{
public:
    BoomScrollLayer *m_scrollLayer;
    CCSprite *m_background;
    CCNode *m_islandNode;
    CCMenu *m_levelMenu;
    CCSize m_winSize;
    CCNode *m_dotNode;
    CCMenuItemSpriteExtra *m_shopButton;
    CCSprite *m_islandTexture;

    int m_pageAmount = 4;
    int m_currentPage = 0;
    int m_levelAmount = 0;
    int m_extraTimes = 0;
    int m_ogreDialog = 0;

    bool m_animating = false;
    bool m_ogreWillTalk = false;

    virtual bool init(int);
    virtual void keyBackClicked();

    std::vector<CCPoint> getPositionForButtons();
    std::vector<CCPoint> getPositionForDots();

    void addLevelButtons();
    void addIslandDots();

    bool isLevelComplete(int);
    void setLevelComplete(int);

    void enableButtonTouch();

    void animateLevelCompletation();
    void animateShopUnlock();
    void enableLevelAnimation(CCObject *);

    void switchToPage(int);
    void onNextPage(CCObject *);
    void onBackPage(CCObject *);

    void onBack(CCObject *);
    void onLevel(CCObject *);
    void onExtraLevel(CCObject *);
    void onRope(CCObject *);
    
    void onShop(CCObject *);
    void onOgre(CCObject *);
    void onSongs(CCObject *);
    void onComics(CCObject *);
    void onSettings(CCObject *);
    void onLanguage(CCObject *);

    void getWizardDialog01();
    void getWizardDialog02();
    void getWizardDialog03();
    void getComic01();
    void getComic06();
    void getComic12();
    void getOgreDialog();
    void unlockOgreChest();
	void getFullCompletion();

public:
	bool m_notify = false;

    static OdysseySelectLayer *create(int);
    static CCScene *scene(int);
};
