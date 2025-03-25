#include "InstantMenuItemSprite.hpp"

bool InstantMenuItemSprite::init(CCNode* sprite, CCObject* target, SEL_MenuHandler callback)
{
    if (!CCMenuItemSpriteExtra::init(sprite, sprite, target, callback)) return false;

    return true;
}

void InstantMenuItemSprite::selected()
{
    CCMenuItemSpriteExtra::activate();
    CCMenuItemSpriteExtra::unselected();
}

void InstantMenuItemSprite::activate()
{
    //hacer que no ejecute otra vez la funcion de activar
}

InstantMenuItemSprite* InstantMenuItemSprite::create(CCNode* sprite, CCObject* target, SEL_MenuHandler callback)
{
    auto ret = new InstantMenuItemSprite();

    if (ret->init(sprite, target, callback))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
};