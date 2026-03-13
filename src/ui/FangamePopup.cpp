#include "FangamePopup.hpp"

bool FangamePopup::init(const char *fileName, const char *url)
{
    if (!Popup::init(386.f, 252.f))
        return false;

    auto contentSize = m_mainLayer->getContentSize();
    m_spriteName = fileName;
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

    // auto sprite = CCSprite::create(fileName);
    // sprite->setPosition({contentSize.width / 2, contentSize.height / 2});
    // sprite->setScale(1.8f);
    // m_mainLayer->addChild(sprite);

    FangamePopup::loadImage();

    this->setTitle("");
    return true;
}

void FangamePopup::loadImage()
{
    m_circle = LoadingCircle::create();
    m_circle->setParentLayer(this);
    m_circle->setZOrder(25);
    m_circle->show();

    // Load the image
    std::string URL = fmt::format("https://raw.githubusercontent.com/Chumiu/GeometryDash-Odyssey/refs/heads/main/resources/Promos/{}", m_spriteName);

    auto req = web::WebRequest();
    req.onProgress([](web::WebProgress const &p) {});

    req.timeout(std::chrono::seconds(5));

    m_listener.spawn(
        req.get(URL),
        [this](web::WebResponse res)
        {
            if (!res.ok())
            {
                log::error("REQUEST FAILED");
                onImageFail();
            }
            else
            {
                auto data = res.data();

                m_sprite = LazySprite::create({217.5f, 144.f}, false);
                m_sprite->loadFromData(const_cast<uint8_t *>(data.data()), data.size(), LazySprite::Format::kFmtPng);

                onImageSuccess();
            }
        });
};

void FangamePopup::onImageSuccess()
{
    fadeLoadingCircle();
    m_sprite->setScale(1.8f);

    //  Resizes the sprite based on the Texture Quality
    if (CCDirector::sharedDirector()->getLoadedTextureQuality() == TextureQuality::kTextureQualityMedium)
        m_sprite->setScale(0.9f);

    if (CCDirector::sharedDirector()->getLoadedTextureQuality() == TextureQuality::kTextureQualityLow)
        m_sprite->setScale(0.45f);

    m_mainLayer->addChildAtPosition(m_sprite, Anchor::Center, ccp(0, 0), false);
};

void FangamePopup::onImageFail()
{
    fadeLoadingCircle();

    auto size = this->getContentSize();
    auto label = CCLabelBMFont::create("Error while loading :(", "bigFont.fnt", 0.0f, kCCTextAlignmentCenter);
    label->setScale(0.75f);

    m_mainLayer->addChildAtPosition(label, Anchor::Center, ccp(0, 0), false);
};

void FangamePopup::fadeLoadingCircle()
{
    if (m_circle == nullptr)
        return;

    m_circle->fadeAndRemove();
};

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