#pragma once
using namespace geode::prelude;

class OdysseySelectLayer : public CCLayer
{
public:
    BoomScrollLayer* m_scrollLayer;
    CCSprite* m_background;
    CCNode* m_islandNode;
    CCMenu* m_levelMenu;
    CCSize m_winSize;

    int m_pageAmount = 3;
    int m_currentPage = 0;
    int m_levelAmount = 0;
    int m_extraTimes = 0;

    virtual bool init(int);
    virtual void keyBackClicked();

    std::vector<CCPoint> getPositionForButtons();

    void addLevelButtons();

    void switchToPage(int);
    void onNextPage(CCObject*);
    void onBackPage(CCObject*);

    void onBack(CCObject*);
    void onLevel(CCObject*);
    void onExtraLevel(CCObject *);

    void getWizardDialog01();

public:
    static OdysseySelectLayer* create(int);
    static CCScene* scene(int);
};
