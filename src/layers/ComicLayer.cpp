#include "ComicLayer.hpp"
#include "OdysseySelectLayer.hpp"
#include "EndCreditsLayer.hpp"
#include "SecretVaultLayer.hpp"

#include "../nodes/ComicNode.hpp"
#include "../utils/Utils.hpp"

const int HOLLOW_COIN_QUOTA = 12;
const int COMICS_AMOUNT = 12;

bool ComicLayer::init(int issueNumber, bool redirectToMap)
{
    if (!CCLayer::init())
        return false;

    m_background = CCSprite::create("GJ_gradientBG.png");
    m_winSize = CCDirector::sharedDirector()->getWinSize();
    m_comicNumber = issueNumber;
    m_RedirectToMap = redirectToMap;

    auto spanishText = GameManager::sharedState()->getGameVariable("0201");
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
    loadComic(arr, issueNumber);

    m_scrollLayer = BoomScrollLayer::create(arr, 0, false, nullptr, static_cast<DynamicScrollDelegate *>(this));
    m_scrollLayer->m_extendedLayer->m_delegate = static_cast<BoomScrollLayerDelegate *>(this);
    m_scrollLayer->m_looped = false;

    m_scrollLayer->instantMoveToPage(m_currentPage);
    addChild(m_scrollLayer);

    static_cast<CCSpriteBatchNode *>(m_scrollLayer->getChildren()->objectAtIndex(1))->setPositionY(-45);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(ComicLayer::onBack));

    backBtn->setID("back-button");
    backBtn->setSizeMult(1.2f);
    backBtn->setPosition({24, m_winSize.height - 24});

    auto infoText = spanishText ? "La calidad de los comics tuvo que ser reducida, de lo contrario el mod tendria problemas. Si no puedes leerlos bien, puedes verlos en el <cy>Video Showcase</c> del mod subido en el <cr>Youtube de Switchstep</c>." : "The quality of the comics had to be reduced, else the mod would have issues. If you have issues on reading them, you can view them in the <cy>Showcase Video</c> uploaded on <cr>Switchstep's Youtube</c>";

    auto infoBtn = InfoAlertButton::create("Quality Issues", infoText, 1);
    infoBtn->setPosition({m_winSize.width - 24, 24});
    infoBtn->setID("comic-info-button");

    auto menuBack = CCMenu::create();
    menuBack->setPosition({0, 0});
    menuBack->setID("back-menu");
    menuBack->addChild(backBtn);
    menuBack->addChild(infoBtn);
    menuBack->setZOrder(5);
    addChild(menuBack);

    //  If the comic issue is 4 (Super Ultra's comic), adds the Hollow's button
    if (issueNumber == 4)
    {
        auto hollowSprite = CCSprite::createWithSpriteFrameName("HollowSkull_001.png"_spr);
        hollowSprite->setColor({90, 90, 90});

        auto hollowBtn = CCMenuItemSpriteExtra::create(
            hollowSprite,
            this,
            menu_selector(ComicLayer::onHollow));

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

    //  Navigation menu
    CCMenu *navMenu = CCMenu::create();
    navMenu->setPosition({0, 0});

    auto leftArrow = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    auto rightArrow = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    leftArrow->setFlipX(true);

    m_leftBtn = CCMenuItemSpriteExtra::create(leftArrow, this, menu_selector(ComicLayer::onPrev));
    m_rightBtn = CCMenuItemSpriteExtra::create(rightArrow, this, menu_selector(ComicLayer::onNext));

    m_leftBtn->setPosition({20.f, m_winSize.height / 2});
    m_leftBtn->setVisible(false);
    m_rightBtn->setPosition({m_winSize.width - 20.f, m_winSize.height / 2});

    navMenu->addChild(m_leftBtn);
    navMenu->addChild(m_rightBtn);
    this->addChild(navMenu);

    //  Mod::get()->setSettingValue<bool>("watched-comic-0" + std::to_string(m_comicNumber), true);
    GameManager::sharedState()->setUGV(fmt::format("2{}", m_comicNumber + 10).c_str(), true);

    //  To verify the secret achievement of reading all the Comics
    auto AM = AchievementManager::sharedState();
    if (!AM->isAchievementEarned("geometry.ach.odyssey.secret19"))
    {
        this->runAction(CCSequence::create(
            CCDelayTime::create(1.f),
            CCCallFunc::create(this, callfunc_selector(ComicLayer::verifySecretAchievement)),
            0));
    }

#ifdef GEODE_IS_DESKTOP
    this->addEventListener(
        KeybindSettingPressedEventV3(Mod::get(), "keybind-comic-next-page"),
        [this](Keybind const &, bool down, bool, double)
        {
            if (down)
            {
                ComicLayer::onNext(this);
            }
        });

    this->addEventListener(
        KeybindSettingPressedEventV3(Mod::get(), "keybind-comic-prev-page"),
        [this](Keybind const &, bool down, bool, double)
        {
            if (down)
            {
                ComicLayer::onPrev(this);
            }
        });
#endif

    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    return true;
};

void ComicLayer::loadComic(CCArray *array, int comicNumber)
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
        5, // 1st
        5, // 2nd
        4, // 3rd
        4, // 4th
        9, // 5th
        6, // 6th
        3, // 7th
        4, // 8th
        3, // 9th
        5, // 10th
        6, // 11th
        6  // 12th
    };

    m_background->setColor(colors[comicNumber - 1]);
    m_totalPages = totalPages[comicNumber - 1];

    for (int ii = 0; ii < m_totalPages; ii++)
    {
        auto languageRef = spanishText ? "SPA" : "ENG";
        auto spriteName = fmt::format("Comic_{}_{:02}_{:02}.png", languageRef, comicNumber, ii + 1);
        auto node = ComicNode::create(spriteName.c_str());
        array->addObject(node);
    };

    if (comicNumber == 12)
    {
        m_totalPages++;

        auto node = CCNode::create();
        auto menu = CCMenu::create();

        auto sprite = CrossButtonSprite::createWithSpriteFrameName("GDO_CreditsIcon_001.png"_spr, 1.5f);
        sprite->setScale(1.5f);

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(ComicLayer::onCredits));

        menu->addChild(button);
        node->addChild(menu);
        array->addObject(node);
    }
};

void ComicLayer::onCredits(CCObject *)
{
    auto scene = CCScene::create();
    scene->addChild(EndCreditsLayer::create());
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(1.f, scene));
};

void ComicLayer::onHollow(CCObject *)
{
    auto GM = GameManager::sharedState();
    auto GSM = GameStatsManager::sharedState();

    if (!Mod::get()->getSettingValue<bool>("bypass-vaults"))
    {
        //  Meets the hollow for the first time
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

        //  Not enough secret coins
        if (GSM->getStat("8") < HOLLOW_COIN_QUOTA)
        {
            log::info("HOLLOW NOT ENOUGH");
            auto dialog = Odyssey::createDialog("belowHollowQuota");
            this->addChild(dialog, 3);
            return;
        }

        //  Enough coins, gets special dialog (executed for the first time)
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

void ComicLayer::verifySecretAchievement()
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

void ComicLayer::scrollLayerMoved(CCPoint point)
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

void ComicLayer::keyBackClicked()
{
    if (m_RedirectToMap)
    {
        auto layer = OdysseySelectLayer::create(0);
        auto scene = CCScene::create();
        scene->addChild(layer);

        CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, scene));
        return;
    }

    if (!m_fromPopup)
    {
        auto musicLoop = m_comicNumber < 6 ? "IslandLoop01.mp3"_spr : "IslandLoop02.mp3"_spr;
        GameManager::sharedState()->fadeInMusic(musicLoop);
    }
    else
    {
        GameManager::sharedState()->fadeInMenuMusic();
    }

    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
};

void ComicLayer::onNext(CCObject *)
{
    m_scrollLayer->quickUpdate();
    m_scrollLayer->moveToPage(m_currentPage + 1);

    if (m_rightBtn)
        m_rightBtn->setVisible(m_currentPage + 1 < m_totalPages - 1);

    if (m_leftBtn)
        m_leftBtn->setVisible(m_currentPage > 0);
}

void ComicLayer::onPrev(CCObject *)
{
    m_scrollLayer->quickUpdate();
    m_scrollLayer->moveToPage(m_currentPage - 1);

    if (m_rightBtn)
        m_rightBtn->setVisible(m_currentPage < m_totalPages - 1);

    if (m_leftBtn)
        m_leftBtn->setVisible(m_currentPage - 1 > 0);
}

void ComicLayer::onBack(CCObject *)
{
    keyBackClicked();
};

ComicLayer *ComicLayer::create(int issueNumber, bool redirectToMap)
{
    auto ret = new ComicLayer();

    if (ret->init(issueNumber, redirectToMap))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

CCScene *ComicLayer::scene(int issueNumber, bool redirectToMap)
{
    auto layer = ComicLayer::create(issueNumber, redirectToMap);
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
};