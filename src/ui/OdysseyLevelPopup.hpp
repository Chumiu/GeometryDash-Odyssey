#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

class OdysseyLevelPopup : public Popup{
private:
    GJGameLevel *m_level;
    CustomSongWidget *m_audioWidget = nullptr;
    int m_levelID = 0;

protected:
    bool init();
    void onPlay(CCObject *);
    void onSettings(CCObject *);
    void onComic(CCObject *);
    void onLore(CCObject *);

public:
    static OdysseyLevelPopup *create(int);
};