#pragma once
using namespace geode::prelude;

class FanmadeGamesCell : public CCLayer
{
private:
    bool init(const char *, CCObject *, SEL_MenuHandler);

public:
    static FanmadeGamesCell *create(const char *, CCObject *, SEL_MenuHandler);
};