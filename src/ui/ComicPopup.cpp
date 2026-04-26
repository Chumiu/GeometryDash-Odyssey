#include "ComicPopup.hpp"
#include "../layers/ComicLayer.hpp"
#include "../utils/Utils.hpp"
#include "Geode/loader/Log.hpp"
#include <Geode/binding/GameManager.hpp>

bool ComicPopup::init(int mapIndex)
{
    if (!Popup::init(400.f, 200.f))
        return false;

    auto contentSize = m_mainLayer->getContentSize();

    m_mapIndex = mapIndex;
    log::debug("Initialized Popup with MapIndex = {}", mapIndex);

    Odyssey::getMaxComic();

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

    //  Comic Buttons
    auto maxComic = Odyssey::getMaxComic();

    for (auto ii = 1; ii <= 12; ii++)
    {
        //  If the index is higher than the max comic (Story-progression)
        if (ii > maxComic)
        {
            auto lockedButton = CCMenuItemSpriteExtra::create(
                ButtonSprite::create("???", 50, true, "goldFont.fnt", "GJ_button_05.png", 25.f, 0.6f),
                this,
                nullptr);
            lockedButton->setID(fmt::format("locked-comic-{:02}", ii));
            buttonMenu->addChild(lockedButton);
            continue;
        }

        //  If the comic is unlocked, just displays a detail if the player has seen it
        auto seen = GameManager::get()->getUGV(fmt::format("2{}", ii + 10).c_str());
        log::info("Check seen: 2{} {}",  ii + 10, seen);
        auto texture = seen ? "GJ_button_02.png" : "GJ_button_01.png";

        auto comicButton = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(fmt::format("#{:02}", ii).c_str(), 50, true, "goldFont.fnt", texture, 25.f, 0.6f),
            this,
            menu_selector(ComicPopup::onComic));

        comicButton->setID(fmt::format("comic-{:02}", ii));
        comicButton->setTag(ii);
        buttonMenu->addChild(comicButton);
    };
    buttonMenu->updateLayout();
    m_mainLayer->addChild(buttonMenu);

    //  Texto de los creditos
    auto creditsText = CCLabelBMFont::create("Comics made by ReyBenGDYT and 3LIPNG.", "chatFont.fnt");
    creditsText->setPosition({contentSize.width / 2, 22});
    creditsText->setColor({80, 40, 0});
    creditsText->setScale(0.8f);
    m_mainLayer->addChild(creditsText);

    this->setTitle("Comics");
    m_title->setScale(1.0f);

    this->setID("comic-popup"_spr);
    return true;
};

void ComicPopup::onComic(CCObject *sender)
{
    auto comic = ComicLayer::create(sender->getTag());
    comic->m_mapIndex = m_mapIndex;

    auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
    button->setSprite(ButtonSprite::create(fmt::format("#{:02}", sender->getTag()).c_str(), 50, true, "goldFont.fnt", "GJ_button_01.png", 25.f, 0.6f));

    auto scene = CCScene::create();
    scene->addChild(comic);

    GameManager::get()->setUGV(fmt::format("2{}", sender->getTag() + 10).c_str(), false);

    GameManager::sharedState()->fadeInMusic(fmt::format("comic_{:02}.mp3"_spr, sender->getTag()).c_str());
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
};

ComicPopup *ComicPopup::create(int mapIndex)
{
    auto ret = new ComicPopup();

    if (ret->init(mapIndex))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};