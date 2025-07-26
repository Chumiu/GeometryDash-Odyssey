#pragma once
using namespace geode::prelude;

class ComicLayer : public cocos2d::CCLayer, public BoomScrollLayerDelegate, public DynamicScrollDelegate
{
public:
    BoomScrollLayer *m_scrollLayer = nullptr;
    CCMenuItemSpriteExtra *m_rightBtn = nullptr;
    CCMenuItemSpriteExtra *m_leftBtn = nullptr;
    CCSprite *m_background = nullptr;
    CCSprite *m_cornerBL = nullptr;
    CCSprite *m_cornerBR = nullptr;
    CCSize m_winSize;

    const char *m_backgroundMusic = "menuLoop.mp3";
    int m_comicNumber = 1;
    int m_currentPage = 0;
    int m_totalPages = 1;
    bool m_RedirectToMap;
    bool m_fromPopup = false;

    virtual bool init(int, bool);
    virtual void keyBackClicked();
    void scrollLayerMoved(CCPoint);

    //  Para crear el Scroll layer
    void createComic(CCArray *, int);
    CCNode *createComicPage(const char *, const char *);
    //  CCNode *createPage(int);

    void verifySecretAchievement();

    void onCredits(CCObject *);
    void onHollow(CCObject *);
    void onPrev(CCObject *);
    void onNext(CCObject *);
    void onBack(CCObject *);

public:
    static ComicLayer *create(int, bool);
    CCScene *scene(int, bool);
};
