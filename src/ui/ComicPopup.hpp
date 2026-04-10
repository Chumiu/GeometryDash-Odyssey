#pragma once
using namespace geode::prelude;

class ComicPopup : public Popup
{
private:
    int m_mapIndex = -1;

protected:
    bool init(int mapIndex);
    void onComic(CCObject *);

public:
    static ComicPopup *create(int mapIndex = -1);
};