#include "FangamePopup.hpp"

bool FangamePopup::setup(const char *fileName, const char *url)
{
    auto contentSize = m_mainLayer->getContentSize();
    m_link = url;

    m_linkButton = CCMenuItemSpriteExtra::create(
        ButtonSprite::create(m_buttonText, "goldFont.fnt", "GJ_button_02.png", 0.75f),
        this,
        menu_selector(FangamePopup::onLink));
    m_linkButton->setPosition({contentSize.width / 2, -10});
    m_linkButton->setScale(0.95f);

    auto menu = CCMenu::create();
    menu->setContentSize(contentSize);
    menu->setPosition({0, 0});
    menu->setZOrder(10);
    menu->addChild(m_linkButton);
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
    m_linkButton->setNormalImage(ButtonSprite::create(newText, "goldFont.fnt", "GJ_button_05.png", 0.75f));
}

FangamePopup *FangamePopup::create(const char *fileName, const char *url)
{
    auto ret = new FangamePopup();

    if (ret->initAnchored(386.f, 252.f, fileName, url))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
};