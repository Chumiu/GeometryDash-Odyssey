#include "OdysseyComicLayer.hpp"
#include "OdysseySelectLayer.hpp"
#include "SecretVaultLayer.hpp"
#include "../utils/Utils.hpp"

const int HOLLOW_COIN_QUOTA = 12;
const int COMICS_AMOUNT = 12;

bool OdysseyComicLayer::init(int issueNumber, bool redirectToMap)
{
    if (!CCLayer::init())
        return false;

    m_background = CCSprite::create("GJ_gradientBG.png");
    m_winSize = CCDirector::sharedDirector()->getWinSize();
    m_comicNumber = issueNumber;
    m_RedirectToMap = redirectToMap;

    /*
    //  Cancion de musica para el cuarto
    m_backgroundMusic = fmt::format("comic_{:02}.mp3"_spr, issueNumber).c_str();
    log::debug("Comic MP3: {}", fmt::format("comic_{:02}.mp3"_spr, issueNumber).c_str());
    GameManager::sharedState()->fadeInMusic(m_backgroundMusic);
    */

    auto size = m_background->getContentSize();

    m_background->setScaleX((m_winSize.width) / size.width);
    m_background->setScaleY((m_winSize.height) / size.height);
    m_background->setAnchorPoint({0, 0});

    m_background->setColor({120, 120, 120});
    m_background->setID("background"_spr);
    addChild(m_background, -2);

    auto arr = CCArray::create();
    auto dotMenu = CCMenu::create();

    //  Calls the function to create the whole comic (by adding it to the Array for BoomScrollLayer)
    createComic(arr, issueNumber);

    m_scrollLayer = BoomScrollLayer::create(arr, 0, false, nullptr, static_cast<DynamicScrollDelegate *>(this));
    m_scrollLayer->m_extendedLayer->m_delegate = static_cast<BoomScrollLayerDelegate *>(this);
    m_scrollLayer->m_looped = false;

    m_scrollLayer->instantMoveToPage(m_currentPage);
    addChild(m_scrollLayer);

    static_cast<CCSpriteBatchNode *>(m_scrollLayer->getChildren()->objectAtIndex(1))->setPositionY(-45);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(OdysseyComicLayer::onBack));

    backBtn->setID("back-button"_spr);
    backBtn->setSizeMult(1.2f);

    auto menuBack = CCMenu::create();
    menuBack->addChild(backBtn);
    menuBack->setPosition({24, m_winSize.height - 24});
    menuBack->setID("back-menu"_spr);
    addChild(menuBack);

    if (issueNumber == 4)
    {
        auto hollowSprite = CCSprite::createWithSpriteFrameName("HollowSkull_001.png"_spr);
        hollowSprite->setColor({90, 90, 90});

        auto hollowBtn = CCMenuItemSpriteExtra::create(
            hollowSprite,
            this,
            menu_selector(OdysseyComicLayer::onHollow));

        hollowBtn->setPosition({m_winSize.width - 20, m_winSize.height - 20});
        hollowBtn->setTag(0);

        auto opacity = GameManager::sharedState()->getUGV("205") ? 150 : 0;
        hollowBtn->setID("hollow-button");
        hollowBtn->setOpacity(opacity);

        auto secretMenu = CCMenu::create();
        secretMenu->addChild(hollowBtn);
        secretMenu->setPosition({0, 0});
        addChild(secretMenu);
    };

    m_cornerBL = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    m_cornerBL->setPosition({-1, -1});
    m_cornerBL->setAnchorPoint({0, 0});
    m_cornerBL->setID("corner-bl"_spr);
    addChild(m_cornerBL, 2);

    m_cornerBR = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    m_cornerBR->setPosition({m_winSize.width + 1, -1});
    m_cornerBR->setAnchorPoint({1, 0});
    m_cornerBR->setFlipX(true);
    m_cornerBR->setID("corner-br"_spr);
    addChild(m_cornerBR, 2);

    //  Navigation menu
    CCMenu *navMenu = CCMenu::create();
    navMenu->setPosition({0, 0});

    auto leftArrow = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    auto rightArrow = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    leftArrow->setFlipX(true);

    m_leftBtn = CCMenuItemSpriteExtra::create(leftArrow, this, menu_selector(OdysseyComicLayer::onPrev));
    m_rightBtn = CCMenuItemSpriteExtra::create(rightArrow, this, menu_selector(OdysseyComicLayer::onNext));

    m_leftBtn->setPosition({20.f, m_winSize.height / 2});
    m_leftBtn->setVisible(false);
    m_rightBtn->setPosition({m_winSize.width - 20.f, m_winSize.height / 2});

    navMenu->addChild(m_leftBtn);
    navMenu->addChild(m_rightBtn);
    this->addChild(navMenu);

    //  Mod::get()->setSettingValue<bool>("watched-comic-0" + std::to_string(m_comicNumber), true);
    GameManager::sharedState()->setUGV(fmt::format("2{}", m_comicNumber + 10).c_str(), true);

    //  Para verificar el achievement de Comic Book fan
    auto AM = AchievementManager::sharedState();
    if (!AM->isAchievementEarned("geometry.ach.odyssey.secret19"))
    {
        this->runAction(CCSequence::create(
            CCDelayTime::create(1.f),
            CCCallFunc::create(this, callfunc_selector(OdysseyComicLayer::verifySecretAchievement)),
            0));
    }

    //  Llama a la funcion para el logro secreto
    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    return true;
};

void OdysseyComicLayer::createComic(CCArray *arr, int issueNumber)
{
    auto spanishText = GameManager::sharedState()->getGameVariable("0201");

    std::vector<ccColor3B> colors = {
        {33, 33, 33},
        {63, 6, 155},
        {0, 32, 59},
        {29, 24, 51},
        {173, 41, 66},
        {120, 0, 0},
        {0, 142, 17},
        {0, 69, 184},
        {0, 207, 228},
        {0, 207, 228},
        {4, 0, 171},
        {107, 0, 10},
    };

    std::vector<int> totalPages = {
        9, // 1st
        5, // 2nd
        4, // 3rd
        4, // 4th
        9, // 5th
        6, // 6th
        3, // 7th
        4, // 8th
        3, // 9th
        5, // 10th
        7, // 11th
        6  // 12th
    };

    m_background->setColor(colors[issueNumber - 1]);
    m_totalPages = totalPages[issueNumber - 1];

    for (int ii = 0; ii < m_totalPages; ii++)
    {
        //  auto pages = getPage(issueNumber, ii + 1);
        //  auto pageSprite = spanishText ? pages.second : pages.first;

        auto language = spanishText ? "SPA" : "ENG";
        auto spriteName = fmt::format("Comic_{}_{:02}_{:02}.png", language, issueNumber, ii + 1);

        log::debug("Page Sprite Name = {}", fmt::format("Comic_{}_{:02}_{:02}.png", language, issueNumber, ii + 1));
        arr->addObject(createComicPage(spriteName.c_str()));
    };
};

void OdysseyComicLayer::onHollow(CCObject *)
{
    auto GM = GameManager::sharedState();
    auto GSM = GameStatsManager::sharedState();

    if (!Mod::get()->getSettingValue<bool>("bypass-vaults"))
    {
        //  Conoce al Hollow por primera vez
        if (!GM->getUGV("205"))
        {
            if (auto hollowBtn = this->getChildByIDRecursive("hollow-button"))
            {
                hollowBtn->runAction(CCFadeTo::create(1, 150));
            };

            log::info("MEETING HOLLOW");
            auto dialog = Odyssey::createDialog("meetingHollow");
            this->addChild(dialog, 3);
            GM->setUGV("205", true);
            return;
        }

        //  No tiene las monedas
        if (GSM->getStat("8") < HOLLOW_COIN_QUOTA)
        {
            log::info("HOLLOW NOT ENOUGH");
            auto dialog = Odyssey::createDialog("belowHollowQuota");
            this->addChild(dialog, 3);
            return;
        }

        //  Suficientes monedas pero no vio el dialogo
        if (GSM->getStat("8") >= HOLLOW_COIN_QUOTA && !GM->getUGV("210"))
        {
            log::info("HOLLOW ENOUGH");
            auto dialog = Odyssey::createDialog("hollowQuotaReached");
            this->addChild(dialog, 3);
            GM->setUGV("210", true);
            return;
        }
    }

    auto scene = CCScene::create();
    scene->addChild(SecretVaultLayer::create());
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(1.f, scene));
};

CCNode *OdysseyComicLayer::createComicPage(const char *spriteName)
{
    auto node = CCNode::create();
    auto comicSprite = CCSprite::createWithSpriteFrameName(spriteName);
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    comicSprite->setPosition(winSize / 2);
    comicSprite->setScale(1.9f);
    node->addChild(comicSprite);
    return node;
};

void OdysseyComicLayer::verifySecretAchievement()
{
    int comicProgress = 0;
    for (auto ii = 1; ii <= COMICS_AMOUNT; ii++)
    {
        comicProgress += GameManager::sharedState()->getUGV(fmt::format("2{}", ii + 10).c_str());
        log::debug("Comic {}, UGV {}, Value {}", ii, fmt::format("2{}", ii + 10).c_str(), GameManager::sharedState()->getUGV(fmt::format("2{}", ii + 10).c_str()));
    };
    log::debug("Comic progress: {}", comicProgress);

    auto percent = (comicProgress * 100) / COMICS_AMOUNT;
    log::info("Secret Comic Achievement progress: {}", percent);
    GameManager::sharedState()->reportAchievementWithID("geometry.ach.odyssey.secret19", percent, false);
};

void OdysseyComicLayer::scrollLayerMoved(CCPoint point)
{
    float transitionPoint = -point.x / CCDirector::sharedDirector()->getWinSize().width;
    int offset = std::floor(transitionPoint);

    if (transitionPoint == offset)
        m_currentPage = offset % m_totalPages;

    if (m_rightBtn)
        m_rightBtn->setVisible(m_currentPage < m_totalPages - 1);

    if (m_leftBtn)
        m_leftBtn->setVisible(m_currentPage > 0);
};

void OdysseyComicLayer::keyBackClicked()
{
    if (m_RedirectToMap)
    {
        auto layer = OdysseySelectLayer::create(0);
        auto scene = CCScene::create();
        scene->addChild(layer);

        CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, scene));
        return;
    }

    auto musicLoop = m_comicNumber < 6 ? "IslandLoop01.mp3"_spr : "IslandLoop02.mp3"_spr;
    GameManager::sharedState()->fadeInMusic(musicLoop);
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
};

void OdysseyComicLayer::onNext(CCObject *)
{
    m_scrollLayer->quickUpdate();
    m_scrollLayer->moveToPage(m_currentPage + 1);

    if (m_rightBtn)
        m_rightBtn->setVisible(m_currentPage + 1 < m_totalPages - 1);

    if (m_leftBtn)
        m_leftBtn->setVisible(m_currentPage > 0);
}

void OdysseyComicLayer::onPrev(CCObject *)
{
    m_scrollLayer->quickUpdate();
    m_scrollLayer->moveToPage(m_currentPage - 1);

    if (m_rightBtn)
        m_rightBtn->setVisible(m_currentPage < m_totalPages - 1);

    if (m_leftBtn)
        m_leftBtn->setVisible(m_currentPage - 1 > 0);
}

void OdysseyComicLayer::onBack(CCObject *)
{
    keyBackClicked();
};

OdysseyComicLayer *OdysseyComicLayer::create(int issueNumber, bool redirectToMap)
{
    auto ret = new OdysseyComicLayer();

    if (ret->init(issueNumber, redirectToMap))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

CCScene *OdysseyComicLayer::scene(int issueNumber, bool redirectToMap)
{
    auto layer = OdysseyComicLayer::create(issueNumber, redirectToMap);
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
};