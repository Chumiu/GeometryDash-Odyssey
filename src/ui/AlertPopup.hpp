#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/GeodeUI.hpp>
using namespace geode::prelude;

class AlertPopup : public Popup{
protected:
    bool init(gd::string, gd::string);
    bool m_translationWarning = false;
    bool m_savefileWarning = false;

public:
    static AlertPopup *create(gd::string, gd::string);
    void onClose(CCObject *) override;
    void setWarning(bool, bool);
};