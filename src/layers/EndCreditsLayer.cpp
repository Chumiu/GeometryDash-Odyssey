#include "EndCreditsLayer.hpp"
#include "../nodes/EndCreditsNode.hpp"
using namespace geode::prelude;

bool EndCreditsLayer::init()
{
    if (!CCLayer::init())
        return false;

    FMODAudioEngine::sharedEngine()->playMusic("StayInsideMe.mp3", true, 1.f, 0);

    m_background = CCSprite::create("game_bg_32_001.png");
    m_winSize = CCDirector::sharedDirector()->getWinSize();
    auto size = m_background->getContentSize();

    //  Tint Background
    auto tintDur = 1.5f;
    auto bgSequence = CCRepeatForever::create(CCSequence::create(
        CCTintTo::create(tintDur, 40, 100, 255),
        CCTintTo::create(tintDur, 40, 255, 133),
        CCTintTo::create(tintDur, 120, 255, 40),
        CCTintTo::create(tintDur, 255, 208, 40),
        CCTintTo::create(tintDur, 255, 47, 40),
        CCTintTo::create(tintDur, 255, 40, 241),
        CCTintTo::create(tintDur, 65, 40, 255),
        CCTintTo::create(tintDur, 40, 126, 255),
        nullptr));

    //  Background
    m_background->setScale(m_winSize.width / size.width);
    m_background->setColor({40, 100, 255});
    m_background->setAnchorPoint({0.5, 0});
    m_background->setID("background"_spr);
    m_background->setOpacity(0);
    m_background->setZOrder(-2);

    this->m_background->runAction(CCSequence::create(
        CCDelayTime::create(5.f),
        CCFadeIn::create(1.5f),
        nullptr));
    this->m_background->runAction(bgSequence);

    this->addChildAtPosition(m_background, Anchor::Bottom, ccp(0, 0), false);
    createEndCredits();

    //  Back Menu
    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(EndCreditsLayer::onBack));

    backBtn->setID("back-button"_spr);
    backBtn->setSizeMult(1.2f);

    auto menuBack = CCMenu::create();
    menuBack->addChild(backBtn);
    menuBack->setPosition({24, m_winSize.height - 24});
    menuBack->setID("back-menu"_spr);
    addChild(menuBack);

    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    this->scheduleUpdate();
    return true;
};

void EndCreditsLayer::createEndCredits()
{
    m_mainCreditsLayer = CCLayer::create();

    //  First Page
    auto m_textArea = TextArea::create("A <co>TCM Team</c> Production", "bigFont.fnt", 1.f, 1000.f, {0.5, 0.5}, 40.f, false);
    m_textArea->setScale(0.75f);
    m_textArea->setOpacity(0);

    auto m_sprite = CCSprite::createWithSpriteFrameName("MainLogo_001.png"_spr);
    m_sprite->setPosition(ccp(m_textArea->getPositionX(), m_textArea->getPositionY()));
    m_sprite->setOpacity(0);

    m_textArea->runAction(CCSequence::create(
        CCDelayTime::create(1.5f),
        CCFadeTo::create(1.5f, 255),
        CCDelayTime::create(1.f),
        CCFadeTo::create(1.5f, 0),
        nullptr));

    m_sprite->runAction(CCSequence::create(
        CCDelayTime::create(5.5f),
        CCFadeIn::create(1.5f),
        nullptr));

    auto creditsPage01 = CCLayer::create();
    creditsPage01->addChildAtPosition(m_sprite, Anchor::Center, ccp(0, 0), false);
    creditsPage01->addChildAtPosition(m_textArea, Anchor::Center, ccp(0, 0), false);
    creditsPage01->setID("credits-intro-layer");

    //  Other Pages
    auto creditsPage02 = createCredits(0, "Management and Organization");
    creditsPage02->setID("managers-layer");

    auto creditsPage03 = createCredits(1, "Mod Developers");
    creditsPage03->setID("mod-developers-layer");

    auto creditsPage04 = createCredits(2, "Level Creators");
    creditsPage04->setID("level-creators-layer");

    auto creditsPage05 = createCredits(3, "Contest Winners");
    creditsPage05->setID("contest-winners-layer");

    auto creditsPage06 = createCredits(4, "Artists");
    creditsPage06->setID("artists-layer");

    auto creditsPage07 = createCredits(5, "Playtesters");
    creditsPage07->setID("playtesters-layer");

    auto creditsPage08 = createCredits(7, "Special Thanks");
    creditsPage08->setID("special-thanks-layer");

    //  Last Page
    auto m_finalText = CCLabelBMFont::create("Thanks for playing :D", "goldFont.fnt");
    m_finalText->setScale(0.8f);
    m_finalText->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);

    auto creditsPage09 = CCLayer::create();
    creditsPage09->addChildAtPosition(m_finalText, Anchor::Center, ccp(0, 0), false);
    creditsPage09->setID("credits-outro-layer");

    //  Adding the layers
    m_mainCreditsLayer->addChildAtPosition(creditsPage01, Anchor::BottomLeft, ccp(0, 0), false);
    m_mainCreditsLayer->addChildAtPosition(creditsPage02, Anchor::BottomLeft, ccp(0, creditsPage01->getContentHeight() * -0.8), false);
    m_mainCreditsLayer->addChildAtPosition(creditsPage03, Anchor::BottomLeft, ccp(0, creditsPage02->getPositionY() - creditsPage03->getContentHeight()), false);
    m_mainCreditsLayer->addChildAtPosition(creditsPage04, Anchor::BottomLeft, ccp(0, creditsPage03->getPositionY() - creditsPage04->getContentHeight()), false);
    m_mainCreditsLayer->addChildAtPosition(creditsPage05, Anchor::BottomLeft, ccp(0, creditsPage04->getPositionY() - creditsPage05->getContentHeight()), false);
    m_mainCreditsLayer->addChildAtPosition(creditsPage06, Anchor::BottomLeft, ccp(0, creditsPage05->getPositionY() - creditsPage06->getContentHeight()), false);
    m_mainCreditsLayer->addChildAtPosition(creditsPage07, Anchor::BottomLeft, ccp(0, creditsPage06->getPositionY() - creditsPage07->getContentHeight()), false);
    m_mainCreditsLayer->addChildAtPosition(creditsPage08, Anchor::BottomLeft, ccp(0, creditsPage07->getPositionY() - creditsPage08->getContentHeight()), false);
    m_mainCreditsLayer->addChildAtPosition(creditsPage09, Anchor::BottomLeft, ccp(0, creditsPage08->getPositionY() - creditsPage09->getContentHeight()), false);

    //  The Animation
    this->m_mainCreditsLayer->runAction(CCSequence::create(
        CCDelayTime::create(8.5f),
        CCMoveBy::create(45.f, {m_mainCreditsLayer->getPositionX(), m_mainCreditsLayer->getPositionY() - creditsPage09->getPositionY()}),
        CCDelayTime::create(1.5f),
        CCCallFunc::create(this, callfunc_selector(EndCreditsLayer::backMenuLayer)),
        nullptr));

    this->addChild(m_mainCreditsLayer);
};

CCLayer *EndCreditsLayer::createCredits(int listIDX, const char *reason)
{
    //  Creates the layer
    auto layer = CCLayer::create();
    layer->setZOrder(3);

    //  For the User Data list
    std::vector<std::vector<gd::string>> userList;
    bool specialLayer = false;
    auto userScale = 1.0f;

    //  Based on the index, its assigned what List to fetch data
    switch (listIDX)
    {
    case 0:
        userList = creditsManagers;
        layer->setContentHeight(m_winSize.height * 0.6);
        userScale = 1.1f;
        break;

    case 1:
        userList = creditsModders;
        layer->setContentHeight(m_winSize.height * 0.6);
        userScale = 1.1f;
        break;

    case 2:
        userList = creditsCreatorsOne;
        // layer->setContentHeight(m_winSize.height * 0.8);
        break;

    case 3:
        userList = creditsCreatorsTwo;
        layer->setContentHeight(m_winSize.height * 0.8);
        break;

    case 4:
        userList = creditsArtists;
        layer->setContentHeight(m_winSize.height * 0.8);
        break;

    case 5:
        userList = creditsTesters;
        layer->setContentHeight(m_winSize.height * 1.2);
        break;

    default:
        userList = creditsSpecials;
        // layer->setContentHeight(m_winSize.height * 0.8);
        specialLayer = true;
    }

    //  Sub-credits label
    auto creditsLabel = CCLabelBMFont::create(reason, "goldFont.fnt");
    creditsLabel->setScale(1.5f);
    creditsLabel->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    creditsLabel->setAnchorPoint({0.5f, 0.5f});
    creditsLabel->limitLabelWidth(240.0f, 0.6f, 0.4f);
    layer->addChildAtPosition(creditsLabel, Anchor::Top, ccp(0, -10), false);

    //  Creates the array (for later aligning)
    CCArray *firstRowArray = CCArray::create();
    CCArray *secondRowArray = CCArray::create();
    CCArray *thirdRowArray = CCArray::create();
    CCArray *fourthRowArray = CCArray::create();

    //  Adds the Users
    for (auto ii = 0; ii < userList.size(); ii++)
    {
        auto userData = userList[ii];

        //  Gets the Data
        auto userName = userData[0].c_str();
        auto userID = std::atoi(userData[1].c_str());
        auto userIcon = std::atoi(userData[2].c_str());
        auto userColor1 = std::atoi(userData[3].c_str());
        auto userColor2 = std::atoi(userData[4].c_str());
        auto userGlow = std::atoi(userData[5].c_str());

        //  Creates the Node
        auto user = EndCreditsNode::create(userName, userID, userIcon, userColor1, userColor2, userGlow);
        user->setID(fmt::format("{}-icon", userName));
        user->setScale(userScale);

        if (specialLayer)
        {
            //  First Row
            if (ii < 3)
                firstRowArray->addObject(user);

            //  Second Row
            else if (ii >= 3 && ii < 7)
                secondRowArray->addObject(user);

            //  Third Row
            else
                thirdRowArray->addObject(user);
        }
        else
        {
            //  First Row
            if (ii < 5)
                firstRowArray->addObject(user);

            //  Second Row
            else if (ii >= 5 && ii < 10)
                secondRowArray->addObject(user);

            //  Third Row
            else if (ii >= 10 && ii < 15)
                thirdRowArray->addObject(user);

            //  Fourth Row
            else
                fourthRowArray->addObject(user);
        }

        //  Adds the User
        layer->addChild(user, 4);
    }

    //  Aligns the users Horizontally
    auto contentSize = layer->getContentSize();
    auto offset = 0;

    if (!secondRowArray->count())
    {
        GameToolbox::alignItemsHorisontally(firstRowArray, 100.f, ccp(contentSize.width / 2, contentSize.height / 2 + offset), false);
    }
    else if (!thirdRowArray->count())
    {
        GameToolbox::alignItemsHorisontally(firstRowArray, 90.f, ccp(contentSize.width / 2, contentSize.height / 2 + 35 + offset), false);
        GameToolbox::alignItemsHorisontally(secondRowArray, 90.f, ccp(contentSize.width / 2, contentSize.height / 2 - 35 + offset), false);
    }
    else if (!fourthRowArray->count())
    {
        GameToolbox::alignItemsHorisontally(firstRowArray, 90.f, ccp(contentSize.width / 2, contentSize.height / 2 + 70 + offset), false);
        GameToolbox::alignItemsHorisontally(secondRowArray, 90.f, ccp(contentSize.width / 2, contentSize.height / 2 + offset), false);
        GameToolbox::alignItemsHorisontally(thirdRowArray, 90.f, ccp(contentSize.width / 2, contentSize.height / 2 - 70 + offset), false);
    }
    else
    {
        GameToolbox::alignItemsHorisontally(firstRowArray, 90.f, ccp(contentSize.width / 2, contentSize.height / 2 + 105 + offset), false);
        GameToolbox::alignItemsHorisontally(secondRowArray, 90.f, ccp(contentSize.width / 2, contentSize.height / 2 + 35 + offset), false);
        GameToolbox::alignItemsHorisontally(thirdRowArray, 90.f, ccp(contentSize.width / 2, contentSize.height / 2 - 35 + offset), false);
        GameToolbox::alignItemsHorisontally(fourthRowArray, 90.f, ccp(contentSize.width / 2, contentSize.height / 2 - 105 + offset), false);
    }

    //  Returns the layer
    return layer;
}

void EndCreditsLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(1.f, MenuLayer::scene(false)));
    GameManager::sharedState()->fadeInMenuMusic();
};

void EndCreditsLayer::backMenuLayer()
{
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(1.f, MenuLayer::scene(false)));
    GameManager::sharedState()->fadeInMenuMusic();
};

void EndCreditsLayer::onBack(CCObject *)
{
    keyBackClicked();
};

EndCreditsLayer *EndCreditsLayer::create()
{
    EndCreditsLayer *pRet = new EndCreditsLayer();

    if (pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }

    delete pRet;
    return nullptr;
}

CCScene *EndCreditsLayer::scene()
{
    auto layer = EndCreditsLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
}