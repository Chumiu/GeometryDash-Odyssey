#pragma once
using namespace geode::prelude;

class LanguagePopup : public Popup
{
protected:
    CCMenuItemSpriteExtra *m_englishBtn = nullptr;
    CCMenuItemSpriteExtra *m_spanishBtn = nullptr;
    InfoAlertButton *m_infoButton = nullptr;

    bool m_toggled = false;

    bool init();
    void onUpdate(CCObject *);

    void onEnglish(CCObject *);
    void onSpanish(CCObject *);
    void onClose(CCObject *);

    void toggle();

public:
    static LanguagePopup *create();
};