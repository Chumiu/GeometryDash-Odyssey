#pragma once
using namespace geode::prelude;

class ComicLayer : public cocos2d::CCLayer, public BoomScrollLayerDelegate, public DynamicScrollDelegate
{
protected:
    BoomScrollLayer *m_scrollLayer = nullptr;
    CCMenuItemSpriteExtra *m_rightBtn = nullptr;
    CCMenuItemSpriteExtra *m_leftBtn = nullptr;
    CCSprite *m_background = nullptr;
    CCSize m_winSize;

    const char *m_backgroundMusic = "menuLoop.mp3";
    int m_comicNumber = 1;
    int m_currentPage = 0;
    int m_totalPages = 1;
    bool m_RedirectToMap;

    virtual bool init(int, bool);
    virtual void keyBackClicked();
    void scrollLayerMoved(CCPoint);

    //  Para crear el comic
    void loadComic(CCArray *array, int comicNumber);

    //  Functions
    void onCredits(CCObject *);
    void onHollow(CCObject *);
    void onPrev(CCObject *);
    void onNext(CCObject *);
    void onBack(CCObject *);

    //  Misc.
    void verifySecretAchievement();

public:
    bool m_fromPopup = false;

    static ComicLayer *create(int comicNumber, bool redirect);
    CCScene *scene(int comicNumber, bool redirect);
};