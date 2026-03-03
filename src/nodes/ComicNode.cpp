#include "ComicNode.hpp"

bool ComicNode::init(const char *comicPage)
{
    if (!CCLayer::init())
        return false;

    m_spriteName = comicPage;

    ComicNode::loadImage();

    return true;
};

void ComicNode::loadImage()
{
    m_circle = LoadingCircle::create();
    m_circle->setParentLayer(this);
    m_circle->setZOrder(25);
    m_circle->show();

    // Load the image
    std::string URL = fmt::format("https://raw.githubusercontent.com/Chumiu/GeometryDash-Odyssey/refs/heads/main/resources/Comics/{}", m_spriteName);

    auto req = web::WebRequest();
    req.onProgress([](web::WebProgress const &p) {});

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

                m_sprite = LazySprite::create({480, 270});
                m_sprite->loadFromData(const_cast<uint8_t *>(data.data()), data.size(), LazySprite::Format::kFmtPng);

                onImageSuccess();
            }
        });
}

void ComicNode::onImageSuccess()
{
    fadeLoadingCircle();

    //  Resizes the sprite based on the Texture Quality
    if (CCDirector::sharedDirector()->getLoadedTextureQuality() == TextureQuality::kTextureQualityMedium)
        m_sprite->setScale(0.5f);

    if (CCDirector::sharedDirector()->getLoadedTextureQuality() == TextureQuality::kTextureQualityLow)
        m_sprite->setScale(0.25f);

    this->addChildAtPosition(m_sprite, Anchor::Center, ccp(0, 0), false);
}

void ComicNode::onImageFail()
{
    fadeLoadingCircle();

    auto size = this->getContentSize();
    auto label = CCLabelBMFont::create("Error while loading Comic page", "bigFont.fnt", 0.0f, kCCTextAlignmentCenter);
    label->setPosition({size.width / 2, size.height / 2});
    label->setScale(0.75f);

    this->addChild(label);
}

void ComicNode::fadeLoadingCircle()
{
    if (m_circle == nullptr)
        return;

    m_circle->fadeAndRemove();
};

ComicNode *ComicNode::create(const char *comicPage)
{
    auto ret = new ComicNode();

    if (ret->init(comicPage))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};