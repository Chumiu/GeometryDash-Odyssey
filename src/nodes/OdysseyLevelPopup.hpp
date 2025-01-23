#pragma once
using namespace geode::prelude;

class OdysseyLevelPopup : public geode::Popup<std::string const &>
{
private:
    GJGameLevel *m_level;
    CustomSongWidget *m_audioWidget = nullptr;
    int m_levelID = 0;

protected:
    bool setup(std::string const &) override;
    void onPlay(CCObject *);
    void onSettings(CCObject *);
    void onComic(CCObject *);
    void onLore(CCObject *);

    /*
    void onAudio(CCObject *);
    void onHideAudio(CCObject *);
    */

public:
    static OdysseyLevelPopup *create(int);
};