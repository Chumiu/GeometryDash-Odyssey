#pragma once
using namespace geode::prelude;

class ComicLayer : public CCLayer, public BoomScrollLayerDelegate, public DynamicScrollDelegate
{
protected:
    BoomScrollLayer *m_scrollLayer = nullptr;
    CCMenuItemSpriteExtra *m_rightBtn = nullptr;
    CCMenuItemSpriteExtra *m_leftBtn = nullptr;
    CCSprite *m_background = nullptr;

    int m_comicNumber = 1;
    int m_currentPage = 0;
    int m_totalPages = 1;

    virtual bool init(int comicNumber);
    virtual void keyBackClicked();
    void scrollLayerMoved(CCPoint);

    //  Para crear el comic
    void loadComic(CCArray *array);

    //  Functions
    void onCredits(CCObject *);
    void onHollow(CCObject *);
    void onPrev(CCObject *);
    void onNext(CCObject *);
    void onBack(CCObject *);

    //  Misc.
    void verifySecretAchievement();

public:
    bool m_redirectToMap = false;
    int m_mapIndex = -1;

    static ComicLayer *create(int comicNumber);
    CCScene *scene(int comicNumber);
};