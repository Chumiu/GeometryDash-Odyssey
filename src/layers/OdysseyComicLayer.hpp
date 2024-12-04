#pragma once
using namespace geode::prelude;

class OdysseyComicLayer : public cocos2d::CCLayer, public BoomScrollLayerDelegate, public DynamicScrollDelegate
{
public:
    BoomScrollLayer *m_scrollLayer = nullptr;
    CCSprite *m_background = nullptr;
    CCSprite *m_cornerBL = nullptr;
    CCSprite *m_cornerBR = nullptr;
    CCSize m_winSize;

    const char * m_backgroundMusic = "menuLoop.mp3";
    int m_comicNumber = 1;
    int m_currentPage = 0;
    int m_totalPages = 1;

    virtual bool init(int);
    virtual void keyBackClicked();

    CCNode *createPage(int);

    //  Para crear el Scroll layer
    void createComic(CCArray * , int);
    CCNode * createComicPage(const char *);
    std::pair<const char *, const char *>getPage(int, int);

    void scrollLayerMoved(CCPoint);
    void onSecret(CCObject *);
    void onBack(CCObject *);
    void onComic(CCObject *);
    void onHollow(CCObject *);

public:
    static OdysseyComicLayer *create(int);
    CCScene *scene(int);
};
