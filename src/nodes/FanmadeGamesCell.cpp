#include "FanmadeGamesCell.hpp"

bool FanmadeGamesCell::init(const char *spriteName, cocos2d::CCObject *target, cocos2d::SEL_MenuHandler callback)
{
    if (!CCLayer::init())
    {
        return false;
    }

    this->setContentSize({358.0f, 118.0f});

    auto menu = CCMenu::create();
    menu->setContentSize(this->getContentSize());
    menu->setPosition({0, 0});

    auto sprite = CCSprite::create(spriteName);
    sprite->setScale(0.95f);

    auto btn = CCMenuItemSpriteExtra::create(
        sprite,
        target,
        callback);

    btn->setPosition(menu->getContentSize() / 2);
    btn->m_scaleMultiplier = 1.f;
    btn->m_colorEnabled = true;
    btn->m_colorDip = 100.0f;

    menu->addChild(btn);
    this->addChild(menu);

    return true;
};

FanmadeGamesCell *FanmadeGamesCell::create(const char *p0, cocos2d::CCObject *p1, cocos2d::SEL_MenuHandler p2)
{
    auto ret = new FanmadeGamesCell();

    if (ret->init(p0, p1, p2))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};