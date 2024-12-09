#include "OdysseyPopup.hpp"

bool OdysseyPopup::setup(std::string const &title, std::string const &desc)
{
    auto contentSize = m_mainLayer->getContentSize();
    auto m_background = CCScale9Sprite::create("square02b_001.png", {0, 0, 80, 80});

    m_background->setPosition({contentSize.width / 2.f, contentSize.height / 2.f + 2.f});
    m_background->setContentSize({280, 120});
    m_background->setColor({133, 68, 41});
    m_mainLayer->addChild(m_background);

    auto m_textArea = TextArea::create(desc, "bigFont.fnt", 1.f, 1000.f, {0.5, 0.5}, 40.f, false);
    m_textArea->setPosition(contentSize / 2);
    m_textArea->setScale(0.5f);
    m_mainLayer->addChild(m_textArea);

    m_closeBtn->setNormalImage(ButtonSprite::create("OK", 0.75));
    m_closeBtn->setPosition({contentSize.width / 2, 23.f});

    this->setTitle(title);
    this->m_reverseKeyBack = true;
    this->m_noElasticity = true;
    return true;
};

void OdysseyPopup::setWarning(bool savefile, bool translation){
    m_translationWarning = translation;
    m_savefileWarning = savefile;
};

void OdysseyPopup::onClose(CCObject *){

    if(m_savefileWarning) GameManager::sharedState()->setUGV("201", true);
    if(m_translationWarning) GameManager::sharedState()->setUGV("202", true);
    removeFromParentAndCleanup(true);
};

OdysseyPopup *OdysseyPopup::create(std::string title, std::string desc)
{
    auto ret = new OdysseyPopup();

    if (ret->initAnchored(300.f, 200.f, title, desc))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
};