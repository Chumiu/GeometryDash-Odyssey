#pragma once
using namespace geode::prelude;

class PromoPopup : public geode::Popup<>
{
protected:
    int m_countdown = 0;
    int m_randomValue = 0;
    bool m_isRewardAvailable = false;

    TextArea * m_textArea = nullptr;
    CCSprite * m_masterSprite = nullptr;
    CCMenuItemSpriteExtra * m_button = nullptr;

    bool setup() override;

    void onCountdown();
    void onClick(CCObject *);

public:
    static PromoPopup *create();
};