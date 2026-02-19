#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/GeodeUI.hpp>
using namespace geode::prelude;

class FangamePopup : public Popup{
    protected:
        const char *m_link;
        const char *m_buttonText = "Test";
        CCMenuItemSpriteExtra * m_linkBtn = nullptr;

        bool init(const char *, const char *);
        void onLink(CCObject *);

    public:
        static FangamePopup * create(const char *, const char *);
        void setButtonText(const char *);
};