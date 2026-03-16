#include "ComicLayer.hpp"
#include "OdysseySelectLayer.hpp"
#include "EndCreditsLayer.hpp"
#include "SecretVaultLayer.hpp"
#include "../nodes/ComicNode.hpp"
#include "../utils/Utils.hpp"

const int HOLLOW_COIN_QUOTA = 12;
const int COMICS_AMOUNT = 12;

bool ComicLayer::init(int issueNumber)
{
    if (!CCLayer::init())
        return false;

    //  The number of the comic
    m_comicNumber = issueNumber;

    //  Background
    m_background = CCSprite::create("GJ_gradientBG.png");
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto bgSize = m_background->getContentSize();
    m_background->setScaleX((winSize.width) / bgSize.width);
    m_background->setScaleY((winSize.height) / bgSize.height);
    m_background->setAnchorPoint({0, 0});
    addChild(m_background, -2);

    auto arr = CCArray::create();
    auto dotMenu = CCMenu::create();

    //	Calls the function that creates the comic (by adding it to the BoomScrollLayer array)
    loadComic(arr);

    //  Scroll Layer for the comics
    m_scrollLayer = BoomScrollLayer::create(arr, 0, false, nullptr, static_cast<DynamicScrollDelegate *>(this));
    m_scrollLayer->m_extendedLayer->m_delegate = static_cast<BoomScrollLayerDelegate *>(this);
    m_scrollLayer->m_looped = false;
    m_scrollLayer->instantMoveToPage(m_currentPage);
    addChild(m_scrollLayer);

    static_cast<CCSpriteBatchNode *>(m_scrollLayer->getChildren()->objectAtIndex(1))->setPositionY(-45);

    //  Button Menu
    auto buttonMenu = CCMenu::create();
    buttonMenu->setID("button-menu");
    buttonMenu->setZOrder(5);
    addChildAtPosition(buttonMenu, Anchor::BottomLeft, ccp(0, 0), false);

    //  Back Button
    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(ComicLayer::onBack));

    backBtn->setID("back-button");
    backBtn->setSizeMult(1.2f);
    buttonMenu->addChildAtPosition(backBtn, Anchor::TopLeft, ccp(24, -24), false);

    //  Info Button
    auto infoText = Odyssey::createText(
        "The comics are now handled as <cg>Online Content</c> because they were too heavy to handle locally via the Mod. If you have issues on reading them, you can view them in the <cy>Showcase Video</c> uploaded on <cr>Switchstep's Youtube</c>.",
        "Los comics ahora son manejados como contenido <cg>Online</c> dado a que sus dimensiones eran muy pesadas para el mod. Si no puedes leerlos bien, puedes verlos en el <cy>Video Showcase</c> del mod subido en el <cr>Youtube de Switchstep</c>.");

    auto infoBtn = InfoAlertButton::create("Optimization", infoText, 1);
    infoBtn->setID("comic-info-button");
    buttonMenu->addChildAtPosition(infoBtn, Anchor::BottomRight, ccp(-24, 24), false);

    if (m_comicNumber == 4)
    {
        //  Adds a button to access the Hollow
        auto hollowSpr = CCSprite::createWithSpriteFrameName("HollowSkull_001.png"_spr);
        hollowSpr->setColor({90, 90, 90});

        auto hollowBtn = CCMenuItemSpriteExtra::create(
            hollowSpr,
            this,
            menu_selector(ComicLayer::onHollow));

        auto opacity = GameManager::sharedState()->getUGV("205") ? 150 : 0;
        hollowBtn->setID("hollow-button");
        hollowBtn->setOpacity(opacity);

        buttonMenu->addChildAtPosition(hollowBtn, Anchor::TopRight, ccp(-20, -20), false);
    };

    //  Corners of the Layer
    auto cornerBL = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    cornerBL->setAnchorPoint({0, 0});
    cornerBL->setZOrder(2);
    cornerBL->setID("corner-bl");

    auto cornerBR = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    cornerBR->setAnchorPoint({1, 0});
    cornerBR->setFlipX(true);
    cornerBR->setZOrder(2);
    cornerBR->setID("corner-br");

    this->addChildAtPosition(cornerBL, Anchor::BottomLeft, ccp(-1, -1), false);
    this->addChildAtPosition(cornerBR, Anchor::BottomRight, ccp(1, -1), false);

    //  Navigation Menu
    CCMenu *navMenu = CCMenu::create();
    this->addChildAtPosition(navMenu, Anchor::BottomLeft, ccp(0, 0), false);

    auto leftArrow = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    auto rightArrow = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    leftArrow->setFlipX(true);

    m_leftBtn = CCMenuItemSpriteExtra::create(
        leftArrow,
        this,
        menu_selector(ComicLayer::onPrev));
    m_leftBtn->setVisible(false);

    m_rightBtn = CCMenuItemSpriteExtra::create(
        rightArrow,
        this,
        menu_selector(ComicLayer::onNext));

    navMenu->addChildAtPosition(m_leftBtn, Anchor::Left, ccp(20, 0), false);
    navMenu->addChildAtPosition(m_rightBtn, Anchor::Right, ccp(-20, 0), false);

    //  Enables the flag that is required to verify if all the comics were read
    GameManager::sharedState()->setUGV(fmt::format("2{:02}", m_comicNumber + 10).c_str(), true);

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
    //  Adds keybind features for desktop-only users (PC or MacOS)
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

//  Loads the comic (hence the name)
void ComicLayer::loadComic(CCArray *array)
{
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

    //  Sets the color of the background
    m_background->setColor(colors[m_comicNumber - 1]);
    m_totalPages = totalPages[m_comicNumber - 1];

    //  Calls the function that gives the node of the comic page (which is handled online)
    for (int ii = 0; ii < m_totalPages; ii++)
    {
        auto languageRef = Odyssey::isSpanish() ? "SPA" : "ENG";
        auto spriteName = fmt::format("Comic_{}_{:02}_{:02}.png", languageRef, m_comicNumber, ii + 1);
        auto node = ComicNode::create(spriteName.c_str());
        array->addObject(node);
    };

    //  If it's the last comic, adds the button for the ending credits
    if (m_comicNumber == 12)
    {
        m_totalPages++;

        auto node = CCNode::create();
        auto menu = CCMenu::create();

        auto sprite = CrossButtonSprite::createWithSpriteFrameName("CreditsLabel_001.png"_spr, 1.5f);
        sprite->setScale(1.5f);

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(ComicLayer::onCredits));

        node->addChild(menu);
        menu->addChild(button);
        array->addObject(node);
    }
};

//  When the credits button is pressed
void ComicLayer::onCredits(CCObject *)
{
    auto scene = CCScene::create();
    scene->addChild(EndCreditsLayer::create());
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(1.f, scene));
};

//  When the Hollow's button is pressed.
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

            auto dialog = Odyssey::createDialog("hollow-introduction", 5);
            this->addChild(dialog, 3);
            GM->setUGV("205", true);
            return;
        }

        //  Not enough secret coins
        if (GSM->getStat("8") < HOLLOW_COIN_QUOTA)
        {
            auto dialog = Odyssey::createDialog("hollow-quota-fail", 5);
            this->addChild(dialog, 3);
            return;
        }

        //  Enough coins, gets special dialog (executed for the first time)
        if (GSM->getStat("8") >= HOLLOW_COIN_QUOTA && !GM->getUGV("210"))
        {
            auto dialog = Odyssey::createDialog("hollow-quota-success", 5, false);
            this->addChild(dialog, 3);
            GM->setUGV("210", true);
            return;
        }
    }

    auto scene = CCScene::create();
    scene->addChild(SecretVaultLayer::create());
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(1.f, scene));
};

//  Counts if all the comics were read, giving the extra achievement.
void ComicLayer::verifySecretAchievement()
{
    int comicProgress = 0;
    for (auto ii = 1; ii <= COMICS_AMOUNT; ii++)
    {
        comicProgress += GameManager::sharedState()->getUGV(fmt::format("2{}", ii + 10).c_str());
        //  log::debug("Comic {}, UGV {}, Value {}", ii, fmt::format("2{}", ii + 10).c_str(), GameManager::sharedState()->getUGV(fmt::format("2{}", ii + 10).c_str()));
    };

    auto percent = (comicProgress * 100) / COMICS_AMOUNT;
    log::debug("Comics achievement progress: {}", percent);
    GameManager::sharedState()->reportAchievementWithID("geometry.ach.odyssey.secret19", percent, false);
};

//  When the scroll layer... moved
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
    //  If it's a redirect, just moves to the select layer
    if (m_redirectToMap)
    {
        auto layer = OdysseySelectLayer::create(0);
        auto scene = CCScene::create();
        scene->addChild(layer);

        CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, scene));
        return;
    }

    //  If it's not a redirect, just pops the scene
    if (m_mapIndex != -1)
    {
        std::string song = (m_mapIndex == 3) ? "SecretLoop02.mp3"_spr : fmt::format("IslandLoop{:02}.mp3"_spr, m_mapIndex + 1);
        GameManager::sharedState()->fadeInMusic(song);
    } else {
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

ComicLayer *ComicLayer::create(int issueNumber)
{
    auto ret = new ComicLayer();

    if (ret->init(issueNumber))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

CCScene *ComicLayer::scene(int issueNumber)
{
    auto layer = ComicLayer::create(issueNumber);
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
};