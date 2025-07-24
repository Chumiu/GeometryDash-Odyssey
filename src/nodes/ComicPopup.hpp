#pragma once
using namespace geode::prelude;

class ComicPopup : public geode::Popup<>
{
protected:
    bool setup() override;
    void onComic(CCObject *);

public:
    static ComicPopup *create();
};