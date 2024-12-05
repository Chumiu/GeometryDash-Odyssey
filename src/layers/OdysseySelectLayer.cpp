#include "OdysseySelectLayer.hpp"
#include "OdysseyLevelPopup.hpp"
#include "OdysseyComicLayer.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

bool OdysseySelectLayer::init(int page)
{
    if (!CCLayer::init())
        return false;

    m_currentPage = page;

    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    m_winSize = CCDirector::sharedDirector()->getWinSize();

    // canción
    std::string song = "TheMap.mp3"_spr;

    // fondo
    int bgID = 1;
    ccColor3B bgColor = {26, 12, 43};

    // islas
    const char *islandTexture = "odyssey_island01.png"_spr;
    CCPoint islandPosition = {m_winSize.width / 2, m_winSize.height / 2 - 20};
    ccColor3B islandColor = {255, 255, 255};
    float islandScale = 1.8f;

    switch (page)
    {
    case 0:
        bgID = 52;
        bgColor = {32, 39, 46};
        m_levelAmount = 4;
        break;
    case 2:
        bgID = 15;
        bgColor = {53, 7, 0};
        islandTexture = "island_extra.png"_spr;
        islandPosition = CCPoint{m_winSize.width / 2 - 100, islandPosition.y};
        islandScale = .5f;
        break;
    default:
        islandColor = {0, 0, 0};
        break;
    }

    FMODAudioEngine::sharedEngine()->playMusic(song, true, .25f, 0);

    m_background = CCSprite::create(GameManager::sharedState()->getBGTexture(bgID));

    m_background->setColor(bgColor);
    m_background->setAnchorPoint({0, 0});
    m_background->setPositionY(-100);

    m_background->setScale(m_winSize.width / m_background->getContentWidth());

    addChild(m_background, -1);

    auto backMenu = CCMenu::create();
    backMenu->setPosition(24, m_winSize.height - 24);

    auto backSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    auto backButton = CCMenuItemSpriteExtra::create(backSpr, this, menu_selector(OdysseySelectLayer::onBack));

    backMenu->addChild(backButton);

    addChild(backMenu);

    m_islandNode = CCNode::create();

    if (page == 1)
    {
        auto comingSoonLabel = CCLabelBMFont::create("Coming Soon! :)", "bigFont.fnt");

        comingSoonLabel->setScale(.7f);
        comingSoonLabel->setPosition(m_winSize / 2);

        m_islandNode->addChild(comingSoonLabel, 999);
    }

    if (page == 2)
    {
        auto extra01_unlocked = Mod::get()->getSettingValue<bool>("level-extra-01-unlocked");
        auto extra02_unlocked = Mod::get()->getSettingValue<bool>("level-extra-02-unlocked");

        auto menu = CCMenu::create();
        menu->setPosition({0, 0});

        auto firstSprite = CCSprite::createWithSpriteFrameName(islandTexture);
        firstSprite->setScale(islandScale);

        auto firstIsland = CCMenuItemSpriteExtra::create(
            firstSprite,
            this,
            menu_selector(OdysseySelectLayer::onExtraLevel));

        firstIsland->setColor(islandColor);
        firstIsland->setPosition(islandPosition);
        firstIsland->setTag(201);

        auto secondSprite = CCSprite::createWithSpriteFrameName("island_extra2.png"_spr);
        secondSprite->setScale(islandScale);

        auto secondIsland = CCMenuItemSpriteExtra::create(
            secondSprite,
            this,
            menu_selector(OdysseySelectLayer::onExtraLevel));

        secondIsland->setTag(202);
        secondIsland->setPosition({m_winSize.width / 2 + 100, m_winSize.height / 2});

        if (!extra01_unlocked)
        {
            auto lock = CCSprite::createWithSpriteFrameName("GJLargeLock_001.png");
            firstSprite->setColor({25, 25, 25});
            firstIsland->addChild(lock, 10);

            lock->setPosition(firstIsland->getContentSize() / 2);
        }

        if (!extra02_unlocked)
        {
            auto lock = CCSprite::createWithSpriteFrameName("GJLargeLock_001.png");
            secondSprite->setColor({25, 25, 25});
            secondIsland->addChild(lock, 10);

            lock->setPosition(secondIsland->getContentSize() / 2);
        }

        menu->addChild(firstIsland);
        menu->addChild(secondIsland);

        m_islandNode->addChild(menu);
    }

    auto island = CCSprite::createWithSpriteFrameName(islandTexture);
    island->setScale(islandScale);
    island->setColor(islandColor);

    island->setAnchorPoint({.5f, .5f});
    island->setPosition(islandPosition);

    if (page == 2)
        island->setVisible(false);

    m_islandNode->addChild(island);
    addChild(m_islandNode);

    addLevelButtons();
    auto moveUp = CCEaseInOut::create(CCMoveTo::create(2.0f, {0, 5}), 1.8f);
    auto moveDown = CCEaseInOut::create(CCMoveTo::create(2.0f, {0, 0}), 1.8f);

    m_islandNode->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(moveUp, moveDown)));
    auto islandTitle = CCSprite::createWithSpriteFrameName(fmt::format("island_title{:02}.png"_spr, page + 1).c_str());

    islandTitle->setScale(.85f);
    islandTitle->setPosition({m_winSize.width / 2, m_winSize.height - 30});

    addChild(islandTitle);

    auto switchMenu = CCMenu::create();

    if (page > 0)
    {
        auto navSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
        navSprite->setFlipX(true);

        auto leftButton = CCMenuItemSpriteExtra::create(navSprite, this, menu_selector(OdysseySelectLayer::onBackPage));
        leftButton->setPositionX(-m_winSize.width / 2 + 45);

        switchMenu->addChild(leftButton);
    }

    if (page < m_pageAmount - 1)
    {
        auto navSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");

        auto rightButton = CCMenuItemSpriteExtra::create(navSprite, this, menu_selector(OdysseySelectLayer::onNextPage));
        rightButton->setPositionX(m_winSize.width / 2 - 45);

        switchMenu->addChild(rightButton);
    }

    addChild(switchMenu);

    auto m_cornerBL = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    m_cornerBL->setPosition({-1, -1});
    m_cornerBL->setAnchorPoint({0, 0});
    m_cornerBL->setID("corner-bl"_spr);
    addChild(m_cornerBL, 2);

    auto m_cornerBR = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    m_cornerBR->setPosition({m_winSize.width + 1, -1});
    m_cornerBR->setAnchorPoint({1, 0});
    m_cornerBR->setFlipX(true);
    m_cornerBR->setID("corner-br"_spr);
    addChild(m_cornerBR, 2);

    //  Se reemplazara esto con el Game Manager, pero lo tengo para Desarrollo
    //  auto GM = GameManager::sharedState();
    //  auto watchedComic01 = GM->getUGV("52");
    auto meetWizard = Mod::get()->getSettingValue<bool>("meet-wizard");
    log::debug("FIRST COMIC {}", meetWizard);

    if (!meetWizard)
    {
        this->runAction(CCSequence::create(
            CCDelayTime::create(0.5f),
            CCCallFunc::create(this, callfunc_selector(OdysseySelectLayer::getWizardDialog01)),
            0));
    };

    return true;
};

void OdysseySelectLayer::getWizardDialog01()
{
    auto dialog = Odyssey::createDialog("wizardIntroduction");
    Mod::get()->setSettingValue("meet-wizard", true);
    //  GM->setUGV("52", true);
    this->addChild(dialog, 3);
};

void OdysseySelectLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, MenuLayer::scene(false)));
    FMODAudioEngine::sharedEngine()->playMusic(GameManager::sharedState()->getMenuMusicFile(), true, .25f, 0);
};

void OdysseySelectLayer::onBack(CCObject *)
{
    keyBackClicked();
};

std::vector<CCPoint> OdysseySelectLayer::getPositionForButtons()
{
    std::vector<CCPoint> arr;

    switch (m_currentPage)
    {
    case 0:
        return {
            {-70, 60},
            {130, 70},
            {40, 10},
            {-80, -55}};
    }

    return arr;
}

void OdysseySelectLayer::addLevelButtons()
{
    m_levelMenu = CCMenu::create();

    m_levelMenu->setPosition(m_winSize / 2);

    if (m_levelAmount > 0)
    {
        for (int i = 0; i < m_levelAmount; i++)
        {
            auto levelSprite = CCSprite::createWithSpriteFrameName("worldLevelBtn_001.png"_spr);
            auto levelButton = CCMenuItemSpriteExtra::create(levelSprite, this, menu_selector(OdysseySelectLayer::onLevel));
            levelButton->setTag(i + 1);

            levelButton->setPosition(getPositionForButtons()[i]);

            m_levelMenu->addChild(levelButton);
        }
    }

    m_islandNode->addChild(m_levelMenu);
};

void OdysseySelectLayer::switchToPage(int page)
{
    auto scene = OdysseySelectLayer::scene(page);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(0.5f, scene));
}

void OdysseySelectLayer::onNextPage(CCObject *)
{
    switchToPage(m_currentPage + 1);
}

void OdysseySelectLayer::onBackPage(CCObject *)
{
    switchToPage(m_currentPage - 1);
}

void OdysseySelectLayer::onLevel(CCObject *sender)
{
    auto popup = OdysseyLevelPopup::create(sender->getTag());
    popup->show();
}

void OdysseySelectLayer::onExtraLevel(CCObject *sender)
{
    auto extra01_unlocked = Mod::get()->getSettingValue<bool>("level-extra-01-unlocked");
    auto extra02_unlocked = Mod::get()->getSettingValue<bool>("level-extra-02-unlocked");

    if ((extra01_unlocked && sender->getTag() == 201) || (extra02_unlocked && sender->getTag() == 202))
    {
        auto popup = OdysseyLevelPopup::create(sender->getTag());
        popup->show();
    }
    else
    {
        auto dialog = Odyssey::createDialogResponse("extraIslandLocked", m_extraTimes);
        //  GM->setUGV("52", true);
        this->addChild(dialog, 3);

        int tag = (m_extraTimes == 0)   ? 1
                  : (m_extraTimes == 1) ? 2
                                        : 0;
        m_extraTimes = tag;
    }
}

OdysseySelectLayer *OdysseySelectLayer::create(int page)
{
    OdysseySelectLayer *pRet = new OdysseySelectLayer();
    if (pRet->init(page))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

CCScene *OdysseySelectLayer::scene(int page)
{
    auto scene = CCScene::create();
    scene->addChild(OdysseySelectLayer::create(page));
    return scene;
}
