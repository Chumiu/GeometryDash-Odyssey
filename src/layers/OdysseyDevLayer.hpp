#pragma once
using namespace geode::prelude;

class OdysseyDevLayer : public cocos2d::CCLayer {
    protected:
        CCSprite * m_background = nullptr;

        virtual bool init();
        virtual void keyBackClicked();
        void onBack(cocos2d::CCObject*);

        void onCarp01(CCObject *);
        void onCarp02(CCObject *);
        void onCarp03(CCObject *);
        void onCarp04(CCObject *);
        void onWizard01(CCObject *);
        void onWizard02(CCObject *);
        void onWizard03(CCObject *);
        void onWizard04(CCObject *);

        void onComic(CCObject *);
        void onLevel(CCObject *);
        void onOgre(CCObject *);
    public:
        static OdysseyDevLayer * create();
        CCScene * scene();
};