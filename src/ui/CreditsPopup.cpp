#include "CreditsPopup.hpp"
#include "../nodes/CreditsNode.hpp"

bool CreditsPopup::init()
{
    if (!Popup::init(430.0f, 270.0f, "GJ_square07.png"))
        return false;

    //  Backgrounds
    m_background = CCScale9Sprite::create("GJ_square06.png", {0, 0, 80, 80});
    m_background->setContentSize(m_mainLayer->getContentSize());
    m_background->setZOrder(-1);
    m_mainLayer->addChildAtPosition(m_background, Anchor::Center, ccp(0, 0), false);

    m_middleground = CCScale9Sprite::create("square02c_001.png", {0, 0, 80, 80});
    m_middleground->setContentSize({375, 200});
    m_middleground->setOpacity(125);
    m_middleground->setZOrder(1);
    m_mainLayer->addChildAtPosition(m_middleground, Anchor::Center, ccp(0, -15), false);

    //  Upper Credits Label
    auto m_creditsLabel = CCLabelBMFont::create("Credits", "bigFont.fnt");
    m_creditsLabel->setZOrder(3);
    m_mainLayer->addChildAtPosition(m_creditsLabel, Anchor::Top, ccp(0, -25), false);

    auto m_lineDeco = CCSprite::createWithSpriteFrameName("floorLine_001.png");
    m_lineDeco->setColor({0, 0, 0});
    m_lineDeco->setScale(0.75f);
    m_lineDeco->setZOrder(3);
    m_lineDeco->setOpacity(60);
    m_mainLayer->addChildAtPosition(m_lineDeco, Anchor::Top, ccp(0, -45), false);

    //  Navigation Menu
    auto m_menuBtn = CCMenu::create();
    m_menuBtn->setContentSize(m_mainLayer->getContentSize());
    m_mainLayer->addChildAtPosition(m_menuBtn, Anchor::BottomLeft, ccp(0, 0), false);

    auto m_nextSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    m_nextSpr->setFlipX(true);

    m_nextBtn = CCMenuItemSpriteExtra::create(
        m_nextSpr,
        this,
        menu_selector(CreditsPopup::onPage));
    m_nextBtn->setTag(1);

    auto m_prevSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");

    m_prevBtn = CCMenuItemSpriteExtra::create(
        m_prevSpr,
        this,
        menu_selector(CreditsPopup::onPage));
    m_prevBtn->setTag(-1);

    m_menuBtn->addChildAtPosition(m_prevBtn, Anchor::Left, ccp(-30, 0), false);
    m_menuBtn->addChildAtPosition(m_nextBtn, Anchor::Right, ccp(30, 0), false);

    //  Setting Credits
    m_creditsManagersLayer = createCredits(0, "Management and Organization");
    m_creditsManagersLayer->setID("managers-layer");
    m_mainLayer->addChildAtPosition(m_creditsManagersLayer, Anchor::BottomLeft, ccp(0, 0), false);

    m_creditsModdersLayer = createCredits(1, "Mod Developers");
    m_creditsModdersLayer->setID("mod-developers-layer");
    m_mainLayer->addChildAtPosition(m_creditsModdersLayer, Anchor::BottomLeft, ccp(0, 0), false);

    m_creditsCreatorsLayerOne = createCredits(2, "Level Creators");
    m_creditsCreatorsLayerOne->setID("level-creators-layer");
    m_mainLayer->addChildAtPosition(m_creditsCreatorsLayerOne, Anchor::BottomLeft, ccp(0, 0), false);

    m_creditsCreatorsLayerTwo = createCredits(3, "Contest Winners");
    m_creditsCreatorsLayerTwo->setID("contest-winners-layer");
    m_mainLayer->addChildAtPosition(m_creditsCreatorsLayerTwo, Anchor::BottomLeft, ccp(0, 0), false);

    m_creditsArtistsLayer = createCredits(4, "Artists");
    m_creditsArtistsLayer->setID("artists-layer");
    m_mainLayer->addChildAtPosition(m_creditsArtistsLayer, Anchor::BottomLeft, ccp(0, 0), false);

    m_creditsTestersLayerOne = createCredits(5, "Playtesters (1/2)");
    m_creditsTestersLayerOne->setID("playtesters-one-layer");
    m_mainLayer->addChildAtPosition(m_creditsTestersLayerOne, Anchor::BottomLeft, ccp(0, 0), false);

    m_creditsTestersLayerTwo = createCredits(6, "Playtesters (2/2)");
    m_creditsTestersLayerTwo->setID("playtesters-two-layer");
    m_mainLayer->addChildAtPosition(m_creditsTestersLayerTwo, Anchor::BottomLeft, ccp(0, 0), false);

    m_creditsSpecialsLayer = createCredits(7, "Special Thanks");
    m_creditsSpecialsLayer->setID("special-thanks-layer");
    m_mainLayer->addChildAtPosition(m_creditsSpecialsLayer, Anchor::BottomLeft, ccp(0, 0), false);

    if (auto m_dankyUser = static_cast<CreditsNode *>(m_creditsCreatorsLayerOne->getChildByID("Danky99-icon")))
    {
        //  Wanted! Secret
        m_dankyUser->setIconVisible(false);
        auto menu = CCMenu::create();
        menu->setPosition({0, 0});
        menu->setZOrder(10);

        auto dankySpr = CreditsNode::create("Danky99", 14178231, 11, 9, 11, 3);
        dankySpr->setUserButtonVisible(false);
        dankySpr->setScale(0.85);

        auto button = CCMenuItemSpriteExtra::create(
            dankySpr,
            this,
            menu_selector(CreditsPopup::onKill));

        button->setContentSize({40, 40});
        button->m_scaleMultiplier = 1.0;

        dankySpr->setPosition({20, 20});
        button->setPosition(m_dankyUser->getPosition());

        menu->addChild(button);
        m_creditsCreatorsLayerOne->addChild(menu);
    }

    changeTab();
    return true;
}

CCLayer *CreditsPopup::createCredits(int listIDX, const char *reason)
{
    //  Creates the layer
    auto layer = CCLayer::create();
    layer->setContentSize(m_mainLayer->getContentSize());
    layer->setZOrder(3);

    //  Sub-credits label
    auto creditsLabel = CCLabelBMFont::create(reason, "goldFont.fnt");
    creditsLabel->setScale(0.75f);
    creditsLabel->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    creditsLabel->setAnchorPoint({0.5f, 1.0f});
    creditsLabel->limitLabelWidth(240.0f, 0.6f, 0.4f);
    layer->addChildAtPosition(creditsLabel, Anchor::Center, ccp(0, 82.5), false);

    //  For the User Data list
    std::vector<std::vector<gd::string>> userList;
    bool specialLayer = false;
    auto userScale = 1.0f;

    //  Based on the index, its assigned what List to fetch data
    switch (listIDX)
    {
    case 0:
        userList = creditsManagers;
        break;

    case 1:
        userList = creditsModders;
        break;

    case 2:
        userList = creditsCreatorsOne;
        userScale = 0.85f;
        break;

    case 3:
        userList = creditsCreatorsTwo;
        userScale = 0.85f;
        break;

    case 4:
        userList = creditsArtists;
        userScale = 0.85f;
        break;

    case 5:
        userList = creditsTestersOne;
        userScale = 0.85f;
        break;

    case 6:
        userList = creditsTestersTwo;
        userScale = 0.85f;
        break;

    default:
        userList = creditsSpecials;
        specialLayer = true;
        userScale = 0.85f;
    }

    //  Creates the array (for later aligning)
    CCArray *firstRowArray = CCArray::create();
    CCArray *secondRowArray = CCArray::create();
    CCArray *thirdRowArray = CCArray::create();

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
        auto user = CreditsNode::create(userName, userID, userIcon, userColor1, userColor2, userGlow);
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
            else
                thirdRowArray->addObject(user);
        }

        //  Adds the User
        layer->addChild(user, 4);
    }

    //  Aligns the users Horizontally
    auto contentSize = m_mainLayer->getContentSize();
    auto offset = -15;

    if (!secondRowArray->count())
    {
        //  If there's only one row
        GameToolbox::alignItemsHorisontally(firstRowArray, 80.f, ccp(contentSize.width / 2, contentSize.height / 2 + offset), false);
    }
    else if (!thirdRowArray->count())
    {
        //  If there's two rows
        GameToolbox::alignItemsHorisontally(firstRowArray, 74.f, ccp(contentSize.width / 2, contentSize.height / 2 + 30 + offset), false);
        GameToolbox::alignItemsHorisontally(secondRowArray, 74.f, ccp(contentSize.width / 2, contentSize.height / 2 - 30 + offset), false);
    }
    else
    {
        //  If it's all three rows
        GameToolbox::alignItemsHorisontally(firstRowArray, 74.f, ccp(contentSize.width / 2, contentSize.height / 2 + 60 + offset), false);
        GameToolbox::alignItemsHorisontally(secondRowArray, 74.f, ccp(contentSize.width / 2, contentSize.height / 2 + offset), false);
        GameToolbox::alignItemsHorisontally(thirdRowArray, 74.f, ccp(contentSize.width / 2, contentSize.height / 2 - 60 + offset), false);
    }

    //  Returns the layer
    return layer;
}

void CreditsPopup::onPage(CCObject *sender)
{
    m_tab += sender->getTag();
    changeTab();
};

void CreditsPopup::changeTab()
{
    if (m_tab > m_lastTab)
        m_tab = m_lastTab;

    if (m_tab < 0)
        m_tab = 0;

    //  Sets the layers visible based on what the current tab page is.
    m_creditsManagersLayer->setVisible(m_tab == 0);
    m_creditsModdersLayer->setVisible(m_tab == 1);
    m_creditsCreatorsLayerOne->setVisible(m_tab == 2);
    m_creditsCreatorsLayerTwo->setVisible(m_tab == 3);
    m_creditsArtistsLayer->setVisible(m_tab == 4);
    m_creditsTestersLayerOne->setVisible(m_tab == 5);
    m_creditsTestersLayerTwo->setVisible(m_tab == 6);
    m_creditsSpecialsLayer->setVisible(m_tab == 7);

    //  Sets the buttons visible based if it's the edge pages
    m_prevBtn->setVisible(m_tab > 0);
    m_nextBtn->setVisible(m_tab < m_lastTab);

    std::vector<ccColor3B> backgroundColors = {
        {255, 0, 0},
        {255, 125, 0},
        {255, 255, 0},
        {0, 255, 0},
        {0, 255, 255},
        {0, 0, 255},
        {125, 0, 255},
        {255, 0, 255},
    };

    std::vector<ccColor3B> middlegroundColors = {
        {255, 100, 100},
        {255, 125, 100},
        {255, 255, 100},
        {100, 255, 100},
        {100, 255, 255},
        {100, 100, 255},
        {125, 100, 255},
        {255, 100, 255},
    };

    //  Changes the color of the background for aesthetic purposes
    m_background->setColor(backgroundColors[m_tab]);
    m_middleground->setColor(middlegroundColors[m_tab]);
}

void CreditsPopup::onKill(CCObject *sender)
{
    GameManager::sharedState()->reportAchievementWithID("geometry.ach.odyssey.secret24", 100, false);
    auto btn = static_cast<CCMenuItemSpriteExtra *>(sender);
    btn->setVisible(false);

    FMODAudioEngine::sharedEngine()->playEffect("explode_11.ogg");
    auto particle1 = GameToolbox::particleFromString("1a0a0.5a0a-1a0a0a29a0a11a0a0a0a0a0a0a0a30a1a0a0a1a0a1a0a0a0a1a0a100a1a0a0a1a0a1a0a0a0a1a0a0a0a0.5a0a0a0a0a0a0a0a1a2a1a0a0a0a2a0a0a0a0a0a0a1a0a0a0a0a0a0a0", NULL, false);
    auto particle2 = GameToolbox::particleFromString("50a0a0.5a0.25a-1a0a180a29a0a11a0a0a0a0a0a0a0a7a5a0a0a1a0a1a0a0a0a1a0a0a3a0a0a1a0a1a0a0a0a1a0a0a0a0.5a0.25a0a0a150a50a0a0a1a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);

    particle1->setPosition(btn->getPosition());
    particle1->setZOrder(100);

    particle2->setPosition(btn->getPosition());
    particle2->setZOrder(100);

    m_creditsCreatorsLayerOne->addChild(particle1);
    m_creditsCreatorsLayerOne->addChild(particle2);
}

CreditsPopup *CreditsPopup::create()
{
    auto ret = new CreditsPopup();

    if (ret->init())
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}