#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

class PromoPopup : public Popup
{
protected:
    int m_random = 0;
    int m_countdown = 0;
    bool m_isRewardAvailable = false;

    TextArea *m_textArea = nullptr;
    CCSprite *m_masterSpr = nullptr;
    CCMenuItemSpriteExtra *m_button = nullptr;

    bool init();
    void onCountdown();
    void onClick(CCObject *);

public:
    static PromoPopup *create();
};