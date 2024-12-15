#pragma once
using namespace geode::prelude;

class OdysseySelectLayer : public CCLayer
{
public:
    BoomScrollLayer *m_scrollLayer;
    CCSprite *m_background;
    CCNode *m_islandNode;
    CCMenu *m_levelMenu;
    CCSize m_winSize;
    CCNode *m_dotNode;
    CCMenuItemSpriteExtra *m_shopButton;

    int m_pageAmount = 3;
    int m_currentPage = 0;
    int m_levelAmount = 0;
    int m_extraTimes = 0;

    bool m_animating = false;

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
    void onSongs(CCObject *);
    void onShop(CCObject *);

    void getWizardDialog01();

public:
    static OdysseySelectLayer *create(int);
    static CCScene *scene(int);
};
