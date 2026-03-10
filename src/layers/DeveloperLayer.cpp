#include "DeveloperLayer.hpp"
#include "ComicLayer.hpp"
#include "../ui/OdysseyLevelPopup.hpp"
#include "../ui/AlertPopup.hpp"
#include "../utils/Utils.hpp"

bool DeveloperLayer::init()
{
    if (!CCLayer::init())
        return false;

    m_background = CCSprite::create("game_bg_08_001.png");
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto size = m_background->getContentSize();

    //  Background
    m_background->setScale(winSize.width / size.width);
    m_background->setAnchorPoint({0, 0});
    m_background->setPosition({0, -75});
    m_background->setColor({0, 0, 90});
    m_background->setID("background"_spr);
    addChild(m_background, -2);

    //  Back Button
    auto menuBack = CCMenu::create();
    menuBack->setID("back-menu"_spr);
    addChildAtPosition(menuBack, Anchor::TopLeft, ccp(24, -24), false);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(DeveloperLayer::onBack));
    backBtn->setID("back-button"_spr);
    backBtn->setSizeMult(1.2f);
    menuBack->addChild(backBtn);

    //  Talk Menu
    auto pageTalkMenu = CCMenu::create();
    pageTalkMenu->setLayout(RowLayout::create()
                                ->setGap(460.0f)
                                ->setGrowCrossAxis(true)
                                ->setCrossAxisOverflow(false));
    pageTalkMenu->setID("page-menu");
    addChildAtPosition(pageTalkMenu, Anchor::Center, ccp(0, 0), false);

    auto prevTalkBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png"),
        this,
        menu_selector(DeveloperLayer::onTalkNav));
    prevTalkBtn->setID("arrow-prev-talk");
    prevTalkBtn->setTag(-1);

    auto nextTalkSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
    nextTalkSpr->setFlipX(true);

    auto nextTalkBtn = CCMenuItemSpriteExtra::create(
        nextTalkSpr,
        this,
        menu_selector(DeveloperLayer::onTalkNav));
    nextTalkBtn->setID("arrow-next-talk");
    nextTalkBtn->setTag(1);

    //  Talk Main Menu
    m_talkMenu = CCMenu::create();
    m_talkMenu->setID("dialogs-menu"_spr);
    m_talkMenu->setContentSize({370.0f, 70.0f});
    m_talkMenu->setLayout(RowLayout::create()
                              ->setGap(8.0f)
                              ->setAutoScale(false)
                              ->setGrowCrossAxis(true)
                              ->setCrossAxisOverflow(false)
                              ->setCrossAxisLineAlignment(AxisAlignment::Even));
    addChildAtPosition(m_talkMenu, Anchor::Center, ccp(0, 100), false);

    pageTalkMenu->addChildAtPosition(prevTalkBtn, Anchor::Center, ccp(m_talkMenu->getContentWidth() / -2, 100), false);
    pageTalkMenu->addChildAtPosition(nextTalkBtn, Anchor::Center, ccp(m_talkMenu->getContentWidth() / 2, 100), false);

    auto talkLabel = CCLabelBMFont::create("Dialog Events:", "goldFont.fnt");
    talkLabel->setPosition({m_talkMenu->getPositionX(), m_talkMenu->getPositionY() + m_talkMenu->getContentHeight() / 2 + 10.0f});
    talkLabel->setScale(0.75f);
    addChild(talkLabel);

    //  Levels Page Menu
    auto pageLevelMenu = CCMenu::create();
    pageLevelMenu->setLayout(RowLayout::create()
                                 ->setGap(460.0f)
                                 ->setGrowCrossAxis(true)
                                 ->setCrossAxisOverflow(false));
    pageLevelMenu->setID("page-menu");
    addChildAtPosition(pageLevelMenu, Anchor::Center, ccp(0, 0), false);

    auto prevLvlBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png"),
        this,
        menu_selector(DeveloperLayer::onLevelNav));
    prevLvlBtn->setID("arrow-prev-talk");
    prevLvlBtn->setTag(-1);

    auto nextLvlSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
    nextLvlSpr->setFlipX(true);

    auto nextLvlBtn = CCMenuItemSpriteExtra::create(
        nextLvlSpr,
        this,
        menu_selector(DeveloperLayer::onLevelNav));
    nextLvlBtn->setID("arrow-next-talk");
    nextLvlBtn->setTag(1);

    //  Levels Main Menu
    m_levelsMenu = CCMenu::create();
    m_levelsMenu->setID("levels-menu"_spr);
    m_levelsMenu->setContentSize({370.0f, 70.0f});
    m_levelsMenu->setLayout(RowLayout::create()
                                ->setGap(8.0f)
                                ->setAutoScale(false)
                                ->setGrowCrossAxis(true)
                                ->setCrossAxisOverflow(false)
                                ->setCrossAxisLineAlignment(AxisAlignment::Even));
    addChildAtPosition(m_levelsMenu, Anchor::Center, ccp(0, 10), false);

    pageLevelMenu->addChildAtPosition(prevLvlBtn, Anchor::Center, ccp(m_levelsMenu->getContentWidth() / -2, 10), false);
    pageLevelMenu->addChildAtPosition(nextLvlBtn, Anchor::Center, ccp(m_levelsMenu->getContentWidth() / 2, 10), false);

    auto levelsLabel = CCLabelBMFont::create("Levels:", "goldFont.fnt");
    levelsLabel->setPosition({m_levelsMenu->getPositionX(), m_levelsMenu->getPositionY() + m_levelsMenu->getContentHeight() / 2 + 10.0f});
    levelsLabel->setScale(0.75f);
    addChild(levelsLabel);

    //  Comics Menu
    auto comicsMenu = CCMenu::create();
    comicsMenu->setID("comics-menu"_spr);
    comicsMenu->setContentSize({420.0f, 64.0f});
    comicsMenu->setLayout(RowLayout::create()
                              ->setGap(8.0f)
                              ->setAutoScale(false)
                              ->setGrowCrossAxis(true)
                              ->setCrossAxisOverflow(false)
                              ->setCrossAxisLineAlignment(AxisAlignment::Even));
    addChildAtPosition(comicsMenu, Anchor::Center, ccp(0, -70), false);

    auto comicsLabel = CCLabelBMFont::create("Comics", "goldFont.fnt");
    comicsLabel->setPosition({winSize.width / 2, comicsMenu->getPositionY() + comicsMenu->getContentHeight() / 2 + 10.0f});
    comicsLabel->setScale(0.75f);
    addChild(comicsLabel);

    for (auto ii = 0; ii < 12; ii++)
    {
        auto seen = GameManager::sharedState()->getUGV(fmt::format("2{}", ii + 11).c_str());
        auto texture = seen ? "GJ_button_01.png" : "GJ_button_04.png";

        auto comic = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(fmt::format("#{:02}", ii + 1).c_str(), 40, true, "goldFont.fnt", texture, 22.5f, 0.4f),
            this,
            menu_selector(DeveloperLayer::onComic));

        comic->setTag(ii + 1);
        comicsMenu->addChild(comic);
        comicsMenu->updateLayout();
    };

    //  Calls the functions to update each
    updateTalk();
    updateLevels();

    setKeypadEnabled(true);
    return true;
}

void DeveloperLayer::onLevelNav(CCObject *sender)
{
    if (m_levelPage + sender->getTag() < 0 || m_levelPage + sender->getTag() > 3)
        return;

    m_levelPage = m_levelPage + sender->getTag();
    updateLevels();
}

void DeveloperLayer::onTalkNav(CCObject *sender)
{
    if (m_talkPage + sender->getTag() < 0 || m_talkPage + sender->getTag() > 4)
        return;

    m_talkPage = m_talkPage + sender->getTag();
    updateTalk();
}

//  Updates the button of the Events
void DeveloperLayer::updateTalk()
{
    m_talkMenu->removeAllChildren();

    std::vector<gd::string> events = {
        "Carp (Meet)",
        "Wizard (Meet)",
        "Wizard (Level Locked)",
        "Wizard (Island Clear)",
        "Wizard (Main Ending)",
        "Wizard (Extra Locked)",
        "Hollow (Meet)",
        "Hollow (Quota Fail)",
        "Hollow (Quota Success)",
        "Ogre (Locked)",
        "Ogre (Meet)",
        "Ogre (Quest Intro)",
        "Ogre (Quest Start)",
        "Ogre (1st Clear)",
        "Ogre (2nd Clear)",
        "Ogre (3rd Clear)",
        "Ogre (4th Clear)",
        "Ogre (Quest End)",
        "Ogre (Level Locked)",
        "Wizard (Full Completion)",
    };

    auto offset = m_talkPage * 4;

    for (auto ii = 0; ii < 4; ii++)
    {
        auto eventBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(events[ii + offset].c_str(), 140, true, "goldFont.fnt", "GJ_button_01.png", 22.5f, 0.4f),
            this,
            menu_selector(DeveloperLayer::onTalk));

        eventBtn->setTag(ii + offset);
        m_talkMenu->addChild(eventBtn);
    }

    m_talkMenu->updateLayout();
}

//  Updates the buttons of the levels
void DeveloperLayer::updateLevels()
{
    m_levelsMenu->removeAllChildren();

    std::vector<int> levels = {
        7001,
        7002,
        7003,
        7004,
        7005,
        7006,
        7007,
        7008,
        7009,
        7501,
        7502,
        7601,
        7602,
        7603,
        7604,
        7605};

    auto offset = m_levelPage * 4;

    for (auto ii = 0; ii < 4; ii++)
    {
        auto level = LevelTools::getLevel(levels[ii + offset], false);

        auto levelBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(level->m_levelName.c_str(), 140, true, "goldFont.fnt", "GJ_button_01.png", 22.5f, 0.4f),
            this,
            menu_selector(DeveloperLayer::onLevel));

        levelBtn->setTag(levels[ii + offset]);
        m_levelsMenu->addChild(levelBtn);
    }

    m_levelsMenu->updateLayout();
};

//  On Level
void DeveloperLayer::onLevel(CCObject *sender)
{
    auto scene = CCScene::create();
    auto tag = sender->getTag();
    auto popup = OdysseyLevelPopup::create(sender->getTag());
    popup->show();
};

//  Opens the specified Comic
void DeveloperLayer::onComic(CCObject *sender)
{
    auto comic = ComicLayer::create(sender->getTag(), false);
    comic->m_fromPopup = true;

    auto button = static_cast<CCMenuItemSpriteExtra *>(sender);
    button->setSprite(ButtonSprite::create(fmt::format("#{:02}", sender->getTag()).c_str(), 40, true, "goldFont.fnt", "GJ_button_01.png", 22.5f, 0.4f));

    auto scene = CCScene::create();
    scene->addChild(comic);

    GameManager::sharedState()->fadeInMusic(fmt::format("comic_{:02}.mp3"_spr, sender->getTag()).c_str());
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
};

void DeveloperLayer::onTalk(CCObject *sender)
{
    std::vector<const char *> events = {
        "carp-introduction",
        "wizard-introduction",
        "main-level-locked",
        "first-island-clear",
        "main-ending",
        "extra-level-locked",
        "hollow-introduction",
        "hollow-quota-fail",
        "hollow-quota-success",
        "ogre-locked",
        "ogre-meeting",
        "ogre-quest-intro",
        "ogre-quest-start",
        "ogre-level-locked",
        "ogre-first-clear",
        "ogre-second-clear",
        "ogre-third-clear",
        "ogre-fourth-clear",
        "ogre-quest-ending",
        "full-completion",
    };

    std::vector<int> backgrounds = {
        2,
        4,
        4,
        4,
        4,
        4,
        5,
        5,
        5,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        4};

    std::vector<bool> sameNames = {
        false,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        false,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true,
        true};

    auto dialog = Odyssey::createDialog(events[sender->getTag()], backgrounds[sender->getTag()], sameNames[sender->getTag()]);
    this->addChild(dialog, 10);
};

void DeveloperLayer::onPopup(CCObject *sender)
{
    auto tag = sender->getTag();

    if (tag == 1)
    {
        auto popup = AlertPopup::create("Savefile Notice", "<cr>Odyssey</c> stores the data in\na separate <cy>savefile</c>. Your data\nwill be <cg>restored</c> when you\n<cb>turn off</c> the Mod.");
        popup->setWarning(true, false);
        popup->m_scene = this;
        popup->show();
    }

    if (tag == 2)
    {
        auto popup = AlertPopup::create("Language Notice", "Dado a limitaciones de\ncaracteres en el juego, habran\n<cr>errores ortograficos</c>\n(como la falta de acentos)");
        popup->setWarning(false, true);
        popup->m_scene = this;
        popup->setZOrder(104);
        popup->show();
    }

    if (tag == 3)
    {
        CCArray *rewardsArray = CCArray::create();

        rewardsArray->addObject(GJRewardObject::createItemUnlock(UnlockType::Cube, 520));
        rewardsArray->addObject(GJRewardObject::createItemUnlock(UnlockType::GJItem, 4));
        rewardsArray->addObject(GJRewardObject::create(SpecialRewardItem::Orbs, 2500, 14));

        GJRewardItem *rewardItems = GJRewardItem::createWithObjects(GJRewardType::Key100Treasure, rewardsArray);
        RewardUnlockLayer *layer = RewardUnlockLayer::create(7, nullptr);
        layer->m_chestType = 8;

        cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(layer);
        layer->showCollectReward(rewardItems);
        layer->setZOrder(500);
    }
};

void DeveloperLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
};

void DeveloperLayer::onBack(CCObject *)
{
    keyBackClicked();
};

DeveloperLayer *DeveloperLayer::create()
{
    auto ret = new DeveloperLayer();

    if (ret->init())
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

CCScene *DeveloperLayer::scene()
{
    auto layer = DeveloperLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
};