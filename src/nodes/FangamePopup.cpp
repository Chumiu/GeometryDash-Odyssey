#include "FangamePopup.hpp"

bool FangamePopup::init(const char *fileName, const char *url)
{
    if (!Popup::init(386.f, 252.f))
        return false;

    auto contentSize = m_mainLayer->getContentSize();
    m_link = url;

    m_linkBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create(m_buttonText, "goldFont.fnt", "GJ_button_02.png", 0.75f),
        this,
        menu_selector(FangamePopup::onLink));

    m_linkBtn->setPosition({contentSize.width / 2, -10});
    m_linkBtn->setScale(0.95f);

    auto menu = CCMenu::create();
    menu->setContentSize(contentSize);
    menu->setPosition({0, 0});
    menu->setZOrder(10);
    menu->addChild(m_linkBtn);
    m_mainLayer->addChild(menu);

    auto sprite = CCSprite::create(fileName);
    sprite->setPosition({contentSize.width / 2, contentSize.height / 2});
    sprite->setScale(1.8f);
    m_mainLayer->addChild(sprite);

    this->setTitle("");
    return true;
}

void FangamePopup::onLink(CCObject *)
{
    CCApplication::sharedApplication()->openURL(m_link);
}

void FangamePopup::setButtonText(const char *newText)
{
    m_linkBtn->setNormalImage(ButtonSprite::create(newText, "goldFont.fnt", "GJ_button_05.png", 0.75f));
}

FangamePopup *FangamePopup::create(const char *fileName, const char *url)
{
    auto ret = new FangamePopup();

    if (ret->init(fileName, url))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};