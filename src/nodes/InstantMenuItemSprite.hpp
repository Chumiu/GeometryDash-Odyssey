#pragma once
using namespace geode::prelude;

class InstantMenuItemSprite : public CCMenuItemSpriteExtra
{
public:
    static InstantMenuItemSprite* create(CCNode* sprite, CCObject* target, SEL_MenuHandler callback);

    virtual bool init(CCNode* sprite, CCObject* target, SEL_MenuHandler callback);

    virtual void selected();
    virtual void activate();
};