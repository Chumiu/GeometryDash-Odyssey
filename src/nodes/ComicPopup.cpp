#include "ComicPopup.hpp"
#include "../layers/ComicLayer.hpp"

bool ComicPopup::setup()
{
    auto contentSize = m_mainLayer->getContentSize();

    //  Fondo del Popup
    auto m_background = CCScale9Sprite::create("square02b_001.png", {0, 0, 80, 80});
    m_background->setPosition({contentSize.width / 2, contentSize.height / 2});
    m_background->setContentSize({380, 120});
    m_background->setColor({133, 68, 41});
    m_mainLayer->addChild(m_background);

    //  Menu de Botones
    auto buttonMenu = CCMenu::create();
    buttonMenu->setID("button-menu");
    buttonMenu->setContentSize({360.f, 120.f});
    buttonMenu->setPosition({contentSize.width / 2, contentSize.height / 2});
    buttonMenu->setLayout(RowLayout::create()
                              ->setGap(12.0f)
                              ->setAutoScale(false)
                              ->setGrowCrossAxis(true)
                              ->setCrossAxisOverflow(false)
                              ->setCrossAxisLineAlignment(AxisAlignment::Even));

    //  Botones de los comics
    for (auto ii = 0; ii < 12; ii++)
    {
        auto seen = GameManager::sharedState()->getUGV(fmt::format("2{}", ii + 11).c_str());
        auto texture = seen ? "GJ_button_01.png" : "GJ_button_04.png";

        auto comicButton = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(fmt::format("#{:02}", ii + 1).c_str(), 50, true, "goldFont.fnt", texture, 25.f, 0.6f),
            this,
            menu_selector(ComicPopup::onComic));

        buttonMenu->addChild(comicButton);
        comicButton->setTag(ii + 1);
    };
    buttonMenu->updateLayout();
    m_mainLayer->addChild(buttonMenu);

    //  Texto de los creditos
    auto creditsText = CCLabelBMFont::create("Comics made by ReyBenGDYT and 3LIPNG.", "chatFont.fnt");
    creditsText->setPosition({contentSize.width / 2, 22});
    creditsText->setColor({80, 40, 0});
    creditsText->setScale(0.8f);
    m_mainLayer->addChild(creditsText);

    this->setID("comic-popup"_spr);
    this->setTitle("Comics");
    m_title->setScale(1.0f);
    return true;
};

void ComicPopup::onComic(CCObject * sender){
    auto comic = ComicLayer::create(sender->getTag(), false);
    comic->m_fromPopup = true;

    auto button = static_cast<CCMenuItemSpriteExtra *>(sender);
    button->setSprite(ButtonSprite::create(fmt::format("#{:02}", sender->getTag()).c_str(), 50, true, "goldFont.fnt", "GJ_button_01.png", 25.f, 0.6f));

    auto scene = CCScene::create();
    scene->addChild(comic);

    GameManager::sharedState()->fadeInMusic(fmt::format("comic_{:02}.mp3"_spr, sender->getTag()).c_str());
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
};

ComicPopup *ComicPopup::create()
{
    auto ret = new ComicPopup();

    if (ret && ret->initAnchored(400.f, 200.f))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
};