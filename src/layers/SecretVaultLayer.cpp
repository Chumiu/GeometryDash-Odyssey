#include "SecretVaultLayer.hpp"
#include "../utils/Utils.hpp"

bool SecretVaultLayer::init()
{
    if (!CCLayer::init())
        return false;

    //  Title
    m_title = CCLabelBMFont::create("The Hollow", "goldFont.fnt");
    addChildAtPosition(m_title, Anchor::Top, ccp(0, -22), false);
    m_title->setColor({180, 0, 0});
    m_title->setZOrder(30);

    //  Data
    m_achievementName = "";
    m_spanish = GameManager::sharedState()->getGameVariable("0201");

    //  Background
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    m_background = CCSprite::createWithSpriteFrameName("HollowBG_001.png"_spr);
    m_bg_2 = CCSprite::createWithSpriteFrameName("HollowBG_2_001.png"_spr);
    m_bg_3 = CCSprite::createWithSpriteFrameName("HollowBG_3_001.png"_spr);

    m_background->setScaleX((winSize.width) / m_background->getTextureRect().size.width);
    m_background->setScaleY((winSize.height) / m_background->getTextureRect().size.height);
    m_background->setAnchorPoint({0, 0});
    m_background->setPosition({0, 0});
    m_background->setColor({120, 0, 0});
    m_background->setID("background"_spr);
    addChild(m_background, -4);

    m_bg_2->setScaleX((winSize.width) / m_bg_2->getTextureRect().size.width);
    m_bg_2->setScaleY((winSize.height) / m_bg_2->getTextureRect().size.height);
    m_bg_2->setID("background-layer-2"_spr);
    m_bg_2->setAnchorPoint({0, 0});
    m_bg_2->setPosition({0, 0});
    m_bg_2->setColor({0, 0, 0});
    m_bg_2->setOpacity(90);
    addChild(m_bg_2, -3);

    m_bg_3->setScaleX((winSize.width) / m_bg_3->getTextureRect().size.width);
    m_bg_3->setScaleY((winSize.height) / m_bg_3->getTextureRect().size.height);
    m_bg_3->setID("background-layer-3"_spr);
    m_bg_3->setAnchorPoint({0, 0});
    m_bg_3->setPosition({0, 0});
    m_bg_3->setColor({0, 0, 0});
    addChild(m_bg_3, -2);

    //  Back Button
    auto menuBack = CCMenu::create();
    menuBack->setPosition({24, winSize.height - 24});
    menuBack->setID("back-menu"_spr);
    addChild(menuBack);

    m_backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("HollowArrow_001.png"_spr),
        this,
        menu_selector(SecretVaultLayer::onBack));

    m_backBtn->setID("back-button"_spr);
    m_backBtn->setSizeMult(1.2f);
    menuBack->addChild(m_backBtn);

    //  Boton para el nivel secreto "Uncertain"
    m_levelNode = CCNode::create();
    m_levelNode->setContentSize({0, 30});
    m_levelNode->setAnchorPoint({0.5, 0.5});
    m_levelNode->setPosition({winSize.width - 60.f, winSize.height / 2});
    addChild(m_levelNode);

    //  Text Input
    m_textInput = TextInput::create(180, "...");
    m_textInput->setFilter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ");
    m_textInput->setMaxCharCount(20);
    m_textInput->setZOrder(10);
    addChildAtPosition(m_textInput, Anchor::Center, ccp(0, 65), false);

    if (GameManager::sharedState()->getUGV("236"))
    {
        auto m_levelMenu = CCMenu::create();
        m_levelMenu->setContentSize(m_levelNode->getContentSize());
        m_levelMenu->setPosition({0, 0});

        auto m_levelBtnSprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
        m_levelBtnSprite->setScale(0.45f);

        m_levelBtn = CCMenuItemSpriteExtra::create(
            m_levelBtnSprite,
            this,
            nullptr);
        m_levelMenu->addChildAtPosition(m_levelBtn, Anchor::Center);

        m_levelTitle = CCLabelBMFont::create("Fracture", "bigFont.fnt");
        m_levelTitle->setScale(0.5f);

        m_levelNode->addChildAtPosition(m_levelTitle, Anchor::Top);
        m_levelNode->addChild(m_levelMenu);
    };

    if (GameManager::sharedState()->getUGV("234"))
    {
        if (!AchievementManager::sharedState()->isAchievementEarned("geometry.ach.odyssey.secret21"))
        {
            auto menu = CCMenu::create();
            menu->setZOrder(10);

            auto sprite = CCSprite::createWithSpriteFrameName("chest_02_02_001.png");
            sprite->setScale(0.5);

            auto button = CCMenuItemSpriteExtra::create(
                sprite,
                this,
                menu_selector(SecretVaultLayer::onSecret));

            button->m_selectSound = "chestClick.ogg";
            button->m_scaleMultiplier = 1;
            button->m_colorEnabled = true;
            button->m_colorDip = 100.f;
            button->setPositionY(-55);

            menu->addChild(button);
            this->addChild(menu);
        };

        FMODAudioEngine::sharedEngine()->stopAllMusic(true);

        m_background->setColor({60, 60, 60});
        m_title->setColor({255, 255, 255});
        m_textInput->setEnabled(false);
        m_textInput->setString("...");
        m_bg_2->setVisible(false);
        m_bg_3->setVisible(false);

        setKeyboardEnabled(true);
        setKeypadEnabled(true);
        return true;
    }

    //  Creating the Vault keeper
    auto keeperMenu = CCMenu::create();
    keeperMenu->setPosition({0, 0});
    addChild(keeperMenu, 3);

    m_keeper = CCSprite::create();
    m_keeper->setContentSize({60, 60});

    keeper_body = CCSprite::createWithSpriteFrameName("HollowKeeper_Head_001.png"_spr);
    keeper_body->setScale(1.15f);

    keeper_eyes = CCSprite::createWithSpriteFrameName("HollowKeeper_Eyes01_001.png"_spr);
    keeper_eyes->setScale(1.15f);

    keeper_eyesGlow = CCSprite::createWithSpriteFrameName("HollowKeeper_Eyes02_001.png"_spr);
    keeper_eyesGlow->setScale(1.15f);
    keeper_eyesGlow->setOpacity(0);

    keeper_lock = CCSprite::createWithSpriteFrameName("HollowKeeper_Lock_001.png"_spr);
    keeper_lock->setScale(1.15f);

    m_keeper->addChildAtPosition(keeper_body, Anchor::Center);
    m_keeper->addChildAtPosition(keeper_eyes, Anchor::Center);
    m_keeper->addChildAtPosition(keeper_eyesGlow, Anchor::Center);
    m_keeper->addChildAtPosition(keeper_lock, Anchor::Center, {0, -10});

    keeper_lock->setZOrder(1);
    keeper_body->setZOrder(2);
    keeper_eyes->setZOrder(3);
    keeper_eyesGlow->setZOrder(4);

    //  Makes the Keeper as a button for interaction
    m_keeperBtn = CCMenuItemSpriteExtra::create(
        m_keeper,
        this,
        menu_selector(SecretVaultLayer::onSubmit));

    m_keeperBtn->setPosition({winSize.width / 2, winSize.height / 2 - 20.f});
    m_keeperBtn->m_colorEnabled = false;
    m_keeperBtn->m_colorDip = 100.0f;
    keeperMenu->addChild(m_keeperBtn);

    //  Response message
    m_response = CCLabelBMFont::create("", "gjFont41.fnt");
    m_response->setZOrder(20);
    addChildAtPosition(m_response, Anchor::Center, ccp(0, 100), false);

    //  Mensaje inicial
    auto introMessage = m_spanish ? "Bienvenido..." : "Welcome...";
    updateMessage(introMessage, MessageType::Basic);

    bg_particle_01 = GameToolbox::particleFromString("50a-1a2a0.5a15a90a0a50a25a400a0a0a0a0a0a0a0a15a7a0a0a0a0a0a0a0a0a1a0a0a0a0a0a0a0a0a0a0a0a1a0a0.5a0.2a0.5a0.2a0a0a0a0a0a0a0a2a0a0a0a0a25a0a0a0a0a0a0a1a0a0a0a0a0a0a0", NULL, false);
    bg_particle_01->setPositionX(winSize.width / 2);
    addChild(bg_particle_01);

    bg_particle_02 = GameToolbox::particleFromString("10a-1a4a2a1a90a0a15a10a400a100a0a0a0a0a0a0a100a50a0a0a0a0a0a0a0a0a0.5a0.25a0a0a0a0a0a0a0a0a0a0a0.5a0.25a1a0a1a0a0a0a0a0a0a0a0a2a0a0a0a0a40a0a0a0a0a0a0a1a0a0a0a0a0a0a0", NULL, false);
    bg_particle_02->setPosition(winSize / 2);
    addChild(bg_particle_02);

    keeper_auraParticles = GameToolbox::particleFromString("20a-1a2a1a6a90a180a29a0a11a0a0a0a0a0a0a0a6a4a0a0a0a0a0a0a0a0a1a0a0a0a0a0a0a0a0a0a0a0a1a0a0.5a0a0.5a0a25a20a30a15a0a0a1a2a0a0a0a0a2a0a0a0a0a0a0a1a1a0a0a0a0a0a0", NULL, false);
    keeper_auraParticles->setPosition(m_keeperBtn->getPosition());
    addChild(keeper_auraParticles, 1);

    GameManager::sharedState()->fadeInMusic("SecretLoop01.mp3"_spr);
    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    if (GameManager::sharedState()->getUGV("232") && !GameManager::sharedState()->getUGV("233"))
    {
        auto message = m_spanish ? "Nada que hacer aqui... A menos que... Visites a su hermano..." : "Nothing to do here... Unless... You visit his brother...";
        auto text = CCLabelBMFont::create(message, "gjFont41.fnt");
        text->setPosition({winSize.width / 2, 20});
        text->setColor({150, 0, 0});
        text->setOpacity(150);
        text->setScale(0.5f);
        addChild(text);
    }

    Odyssey::hasAllVaultRewards();

    return true;
};

void SecretVaultLayer::executeJumpscare()
{
    m_keeper->setVisible(false);
    m_textInput->setVisible(false);
    m_title->setVisible(false);

    m_title->runAction(CCSequence::create(
        CCDelayTime::create(1),
        CCCallFunc::create(this, callfunc_selector(SecretVaultLayer::scareText01)),
        CCDelayTime::create(0.4),
        CCCallFunc::create(this, callfunc_selector(SecretVaultLayer::scareText02)),
        CCDelayTime::create(0.4),
        CCCallFunc::create(this, callfunc_selector(SecretVaultLayer::scareText03)),
        CCDelayTime::create(0.4),
        CCCallFunc::create(this, callfunc_selector(SecretVaultLayer::scareText04)),
        CCDelayTime::create(0.4),
        CCCallFunc::create(this, callfunc_selector(SecretVaultLayer::scareText05)),
        CCDelayTime::create(2),
        CCCallFunc::create(this, callfunc_selector(SecretVaultLayer::scareEnding)),
        CCDelayTime::create(1),
        CCCallFunc::create(this, callfunc_selector(SecretVaultLayer::scareKick)),
        nullptr));
};

void SecretVaultLayer::scareText01()
{
    //  FMODAudioEngine::sharedEngine()->playEffect("secretSound.ogg"_spr);
    auto jumpscare = CCSprite::createWithSpriteFrameName("HollowJumpscare_001.png"_spr);
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    jumpscare->setPosition({winSize.width / 2, winSize.height / 2 - 20.f});
    jumpscare->setID("spookyCube");
    jumpscare->setZOrder(20);
    addChild(jumpscare);

    m_title->setVisible(true);
    m_title->setString("You.");
    m_title->setPosition({winSize.width / 2 - 2, winSize.height / 2 + 40.f});
    m_title->setScale(0.75f);

    m_title->runAction(CCRepeatForever::create(
        CCSequence::createWithTwoActions(
            CCMoveBy::create(0.01f, {4, 0}),
            CCMoveBy::create(0.01f, {-4, 0}))));
};

void SecretVaultLayer::scareText02()
{
    FMODAudioEngine::sharedEngine()->fadeOutMusic(1.f, 1);
    m_title->setString("You shouldn't.");
};

void SecretVaultLayer::scareText03()
{
    m_title->setString("You shouldn't have.");
};

void SecretVaultLayer::scareText04()
{
    m_title->setString("You shouldn't have done.");
};

void SecretVaultLayer::scareText05()
{
    m_title->setString("You shouldn't have done that.");
};

void SecretVaultLayer::scareEnding()
{
    if (auto cube = this->getChildByIDRecursive("spookyCube"))
        cube->removeFromParentAndCleanup(true);
    m_title->setVisible(false);

    FMODAudioEngine::sharedEngine()->playEffect("door001.ogg");
};

void SecretVaultLayer::scareKick()
{
    CCDirector::sharedDirector()->popSceneWithTransition(1.f, PopTransition::kPopTransitionFade);
    GameManager::sharedState()->setUGV("234", true);
}

void SecretVaultLayer::onSubmit(CCObject *)
{
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    std::string language = m_spanish ? "SPA" : "ENG";
    std::vector<gd::string> messages;
    std::vector<gd::string> voiceFiles;
    std::string response;

    auto GM = GameManager::sharedState();
    auto AM = AchievementManager::sharedState();

    std::string lower = m_textInput->getString();
    std::transform(
        lower.begin(), lower.end(), lower.begin(), [](unsigned char c)
        { return std::tolower(c); });

    m_textInput->setString("");
    m_achievementName = "";

    log::debug("Gargan: {}", m_garganIDX);

    if (std::string_view(lower) == std::string_view("gargan") && GM->getUGV("232") && GM->getUGV("233"))
    {
        messages = {
            "What do you mean?",
            "I don't know what you're talking about.",
            "What do you want?",
            "I swear, I don't know what do you mean!",
            "STOP SAYING THAT.",
            ". . . . . . . . ."};

        voiceFiles = {
            "hollow_ENG_038.mp3"_spr,
            "hollow_ENG_039.mp3"_spr,
            "hollow_ENG_040.mp3"_spr,
            "hollow_ENG_041.mp3"_spr,
            "hollow_ENG_042.mp3"_spr};

        if (m_spanish)
        {
            messages = {
                "Que estas diciendo?",
                "No se de que estas hablando.",
                "Que es lo que quieres?",
                "Te juro, que no se lo que quieres decir.",
                "DEJA DE DECIR ESO.",
                ". . . . . . . . ."};

            voiceFiles = {
                "hollow_SPA_038.mp3"_spr,
                "hollow_SPA_040.mp3"_spr,
                "hollow_SPA_039.mp3"_spr,
                "hollow_SPA_041.mp3"_spr,
                "hollow_SPA_042.mp3"_spr};
        }

        if (m_garganIDX < voiceFiles.size())
            FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[m_garganIDX]);

        if (m_garganIDX < messages.size())
            updateMessage(messages[m_garganIDX], MessageType::WrongAnswer);

        switch (m_garganIDX)
        {
        case 3:
            m_background->runAction(CCSequence::create(
                CCTintTo::create(1.f, 120, 0, 0),
                nullptr));
            break;

        case 4:
            keeper_angerParticles_01 = GameToolbox::particleFromString("50a-1a2a0a25a90a30a29a0a20a20a0a100a0a0a0a0a30a20a0a0a0a0a0a0a0a0a1a0a20a10a0a0a0a0a0a0a0a0a1a0a0.1a0a0.25a0a0a0a0a0a0a0a0a2a0a0a0a0a2a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
            keeper_angerParticles_01->setPosition(m_keeperBtn->getPosition());
            addChild(keeper_angerParticles_01, 1);

            keeper_angerParticles_02 = GameToolbox::particleFromString("30a-1a1a0.3a23a90a5a83a20a0a0a0a0a0a0a0a0a20a0a0a0a1a0a0a0a0a0a1a0a5a5a0a0a1a0a0a0a0a0a1a0a0a0a0.2a0.1a0a0a0a0a0a0a0a2a0a0a0a0a2a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
            //  keeper_angerParticles_02->setPosition({});
            keeper_angerParticles_02->setPosition({keeper_body->getContentWidth() / 2 - 11, 49});
            keeper_angerParticles_02->setScale(0.5);
            keeper_body->addChild(keeper_angerParticles_02, 4);

            keeper_angerParticles_03 = GameToolbox::particleFromString("30a-1a1a0.3a23a90a5a83a20a0a0a0a0a0a0a0a0a20a0a0a0a1a0a0a0a0a0a1a0a5a5a0a0a1a0a0a0a0a0a1a0a0a0a0.2a0.1a0a0a0a0a0a0a0a2a0a0a0a0a2a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
            //  keeper_angerParticles_03->setPosition(m_keeperBtn->getPosition());
            keeper_angerParticles_03->setPosition({keeper_body->getContentWidth() / 2 + 11, 49});
            keeper_angerParticles_03->setScale(0.5);
            keeper_body->addChild(keeper_angerParticles_03, 4);

            m_background->runAction(CCSequence::create(
                CCTintTo::create(1.f, 60, 0, 0),
                nullptr));
            break;

        case 5:
            keeper_angerParticles_02->runAction(CCFadeTo::create(1.f, 0));
            keeper_angerParticles_03->runAction(CCFadeTo::create(1.f, 0));
            keeper_lock->runAction(CCFadeTo::create(1.f, 0));
            keeper_body->runAction(CCTintTo::create(3.f, 30, 0, 0));

            m_background->runAction(CCTintTo::create(3.f, 0, 0, 0));
            m_levelNode->runAction(CCEaseIn::create(CCMoveBy::create(1, {120, 0}), 1.f));
            m_backBtn->runAction(CCEaseIn::create(CCMoveBy::create(1, {-90, 0}), 1.f));

            GameManager::sharedState()->fadeInMusic("SecretLoop03.mp3"_spr);
            setKeyboardEnabled(false);
            setKeypadEnabled(false);
            break;

        case 6:
            keeper_angerParticles_01->setVisible(false);
            executeJumpscare();
            break;
        }

        m_garganIDX++;
        return;
    }

    if (std::string_view(lower) != std::string_view("gargan") && m_garganIDX > 0)
        m_garganIDX = -1;

    //  List of codes
    if (std::string_view(lower) == std::string_view("color") && !AM->isAchievementEarned("geometry.ach.odyssey.secret10") && GM->getUGV("310"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_004.mp3"_spr, language));
        response = m_spanish ? "Esto es monocromatico, cierto?" : "This is monochromatic, is it?";

        updateMessage(response, MessageType::CorrectAnswer);
        m_achievementName = "geometry.ach.odyssey.secret10";
        return;
    };

    /*
    if (std::string_view(lower) == std::string_view("fracture") && !GameManager::sharedState()->getUGV("236"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_010.mp3"_spr, language));
        response = m_spanish ? "Abraza el caos" : "Embrace the chaos";
        GameManager::sharedState()->setUGV("236", true);

        addLevelAnimation();
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };
    */

    if (std::string_view(lower) == std::string_view("explorers") && !AM->isAchievementEarned("geometry.ach.odyssey.secret11") && GM->getUGV("311"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_014.mp3"_spr, language));
        response = m_spanish ? "Tal vez en la proxima actualizacion" : "Maybe in the next update...";

        m_achievementName = "geometry.ach.odyssey.secret11";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("player") && !AM->isAchievementEarned("geometry.ach.odyssey.secret12") && GM->getUGV("312"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_018.mp3"_spr, language));
        response = m_spanish ? "Fuistes tu?" : "...was it you?",

        m_achievementName = "geometry.ach.odyssey.secret12";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("mono") && !AM->isAchievementEarned("geometry.ach.odyssey.secret13") && GM->getUGV("313"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_022.mp3"_spr, language));
        response = m_spanish ? "Hay algo en ella se siente extrano..." : "Something about her feels off...",

        m_achievementName = "geometry.ach.odyssey.secret13";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("nock em") && !AM->isAchievementEarned("geometry.ach.odyssey.secret14") && GM->getUGV("314"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_025.mp3"_spr, language));
        response = m_spanish ? "Knock em out" : "Knock em out";

        m_achievementName = "geometry.ach.odyssey.secret14";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("machina") && !AM->isAchievementEarned("geometry.ach.odyssey.secret15") && GM->getUGV("315"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_028.mp3"_spr, language));
        response = m_spanish ? "Que casualidad..." : "How sudden...";

        m_achievementName = "geometry.ach.odyssey.secret15";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("the seven seas") && !AM->isAchievementEarned("geometry.ach.odyssey.secret16") && GM->getUGV("316"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_031.mp3"_spr, language));
        response = m_spanish ? "Guianos, capitan." : "Guide us, captain.";

        m_achievementName = "geometry.ach.odyssey.secret16";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("smooth jazz") && !AM->isAchievementEarned("geometry.ach.odyssey.secret17") && GM->getUGV("317"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_034.mp3"_spr, language));
        response = "Blergh";

        m_achievementName = "geometry.ach.odyssey.secret17";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("angel") && !AM->isAchievementEarned("geometry.ach.odyssey.secret18") && GM->getUGV("318"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_037.mp3"_spr, language));
        response = m_spanish ? "Los sagrados..." : "The holy...";

        m_achievementName = "geometry.ach.odyssey.secret18";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    //  Wrong Answers
    if (std::string_view(lower) != std::string_view("") || m_garganIDX != 0)
    {
        messages = {
            "Well then...",
            "You really are a fool...",
            "Enough is enough",
            "Come back when you're a little... smarter",
            "Arrgh... you pest...",
            "Cough, cough cough...",
            "Don't waste my time",
            "Your requests mean nothing",
            "Feel ashamed of yourself...",
            "A lasting impression...",
        };

        voiceFiles = {
            "hollow_ENG_043.mp3"_spr,
            "hollow_ENG_044.mp3"_spr,
            "hollow_ENG_045.mp3"_spr,
            "hollow_ENG_046.mp3"_spr,
            "hollow_ENG_047.mp3"_spr,
            "hollow_ENG_048.mp3"_spr,
            "hollow_ENG_049.mp3"_spr,
            "hollow_ENG_050.mp3"_spr,
            "hollow_ENG_051.mp3"_spr,
            "hollow_ENG_052.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Muy bien...",
                "Eres realmente un tonto...",
                "Ya es suficiente",
                "Vuelve cuando seas un poco... mas inteligente",
                "Arrgh... eres una molestia...",
                "Cough, cough cough...",
                "No me hagas perder el tiempo",
                "Tus peticiones no significan nada",
                "Siente vergüenza de ti mismo...",
                "Una impresión duradera...",
            };

            voiceFiles = {
                "hollow_SPA_043.mp3"_spr,
                "hollow_SPA_044.mp3"_spr,
                "hollow_SPA_045.mp3"_spr,
                "hollow_SPA_046.mp3"_spr,
                "hollow_SPA_047.mp3"_spr,
                "hollow_SPA_048.mp3"_spr,
                "hollow_SPA_049.mp3"_spr,
                "hollow_SPA_050.mp3"_spr,
                "hollow_SPA_051.mp3"_spr,
                "hollow_SPA_052.mp3"_spr,
            };
        }

        if (m_garganIDX != 0)
        {
            if (keeper_angerParticles_01 != nullptr)
                removeChild(keeper_angerParticles_01, true);

            if (keeper_angerParticles_02 != nullptr)
                keeper_body->removeChild(keeper_angerParticles_02, true);

            if (keeper_angerParticles_03 != nullptr)
                keeper_body->removeChild(keeper_angerParticles_03, true);

            GameManager::sharedState()->fadeInMusic("SecretLoop01.mp3"_spr);
            m_backBtn->runAction(CCEaseOut::create(CCMoveTo::create(1, {0, 0}), 1.f));
            m_levelNode->runAction(CCEaseIn::create(CCMoveTo::create(1, {winSize.width - 60.f, winSize.height / 2}), 1.f));
            m_background->runAction(CCTintTo::create(1.f, 180, 0, 0));
            setKeyboardEnabled(true);
            setKeypadEnabled(true);
        }

        m_garganIDX = 0;

        int rand = (std::rand() % messages.size());
        response = messages[rand];

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[rand]);
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    response = getMessage();

    //  Gets the type color
    MessageType type = (m_messageID > 10) ? MessageType::Special : MessageType::Basic;
    updateMessage(response, type);
};

std::string SecretVaultLayer::getMessage()
{
    int rand = std::rand() % 30 + 1;

    if (m_messageID == 0)
    {
        m_messageID = rand;
        m_messageIDX = 0;

        std::string message = getThreadMessage(m_messageID, m_messageIDX);

        if (message == std::string_view(""))
            message = getBasicMessage();
        m_messageIDX++;

        return message;
    }
    else
    {
        auto ret = getThreadMessage(m_messageID, m_messageIDX++);
        if (ret == std::string_view(""))
            ret = getBasicMessage();
        return ret;
    }
};

std::string SecretVaultLayer::getThreadMessage(int ID, int index)
{
    //  log::debug("ID: {} - IDX: {}", ID, index);
    std::vector<std::string> messages;
    std::vector<gd::string> voiceFiles;

    //  auto GM = GameManager::sharedState();
    auto AM = AchievementManager::sharedState();
    auto GM = GameManager::sharedState();

    //  Color
    if (ID == 11 && (!AM->isAchievementEarned("geometry.ach.odyssey.secret10")))
    {
        messages = {
            "I am the language of light",
            "I give life to all you see",
            "Without me, the world would be gray...",
        };

        voiceFiles = {
            "hollow_ENG_001.mp3"_spr,
            "hollow_ENG_002.mp3"_spr,
            "hollow_ENG_003.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Soy el lenguaje de la luz,",
                "Doy vida a todo lo que ves.",
                "Sin mi, el mundo seria gris...",
            };

            voiceFiles = {
                "hollow_SPA_001.mp3"_spr,
                "hollow_SPA_002.mp3"_spr,
                "hollow_SPA_003.mp3"_spr,
            };
        }

        if (!GM->getUGV("310"))
        {
            log::info("Hint for Secret 10 enabled");
            GM->setUGV("310", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    /*
    //  Fracture
    if (ID == 12 && !GameManager::sharedState()->getUGV("236"))
    {
        messages = {
            "Sometimes, breaking isn't the end, but the start...",
            "Dive into the glitchy abyss I have for you",
            "It's called Fracture",
            "Hold on tight",
            "The beats here might just split reality",
        };

        voiceFiles = {
            "hollow_ENG_005.mp3"_spr,
            "hollow_ENG_006.mp3"_spr,
            "hollow_ENG_007.mp3"_spr,
            "hollow_ENG_008.mp3"_spr,
            "hollow_ENG_009.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "A veces, romper no es el final, sino el comienzo...",
                "Sumérgete en esta prueba que tengo para ti",
                "Se llama Fracture",
                "Aguanta fuerte",
                "Los ritmos aqui podrian partir la realidad",
            };

            voiceFiles = {
                "hollow_SPA_005.mp3"_spr,
                "hollow_SPA_006.mp3"_spr,
                "hollow_SPA_007.mp3"_spr,
                "hollow_SPA_008.mp3"_spr,
                "hollow_SPA_009.mp3"_spr,
            };
        }

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }
    */

    //  Explorers
    if (ID == 13 && !AM->isAchievementEarned("geometry.ach.odyssey.secret11"))
    {
        messages = {
            "That failed promise...",
            "That guardian of the forest temple...",
            "Delayed until the end of time...",
        };

        voiceFiles = {
            "hollow_ENG_011.mp3"_spr,
            "hollow_ENG_012.mp3"_spr,
            "hollow_ENG_013.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "La promesa fallida",
                "Aquel guardian del templo del bosque",
                "Retrasado hasta el fin de los tiempos...",
            };

            voiceFiles = {
                "hollow_SPA_011.mp3"_spr,
                "hollow_SPA_012.mp3"_spr,
                "hollow_SPA_013.mp3"_spr,
            };
        }

        if (!GM->getUGV("311"))
        {
            log::info("Hint for Secret 11 enabled");
            GM->setUGV("311", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Player
    if (ID == 14 && !AM->isAchievementEarned("geometry.ach.odyssey.secret12"))
    {
        messages = {
            "They have doomed this world...",
            "They who let the Darkness out...",
            "Who could it be? Perhaps, is it in front of me?",
        };

        voiceFiles = {
            "hollow_ENG_015.mp3"_spr,
            "hollow_ENG_016.mp3"_spr,
            "hollow_ENG_017.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Han condenado a este mundo...",
                "Aquellos que liberaron a The Darkness...",
                "Quien pudo ser? Acaso, esta frente a mi?",
            };

            voiceFiles = {
                "hollow_SPA_015.mp3"_spr,
                "hollow_SPA_016.mp3"_spr,
                "hollow_SPA_017.mp3"_spr,
            };
        }

        if (!GM->getUGV("312"))
        {
            log::info("Hint for Secret 12 enabled");
            GM->setUGV("312", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Mono
    if (ID == 15 && !AM->isAchievementEarned("geometry.ach.odyssey.secret13"))
    {
        messages = {
            "Her cross-shaped ribbon and blank eyes...",
            "A traveller with pale, greyscale skin...",
            "Her pure black hair flows like a waterfall...",
        };

        voiceFiles = {
            "hollow_ENG_019.mp3"_spr,
            "hollow_ENG_020.mp3"_spr,
            "hollow_ENG_021.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Su cinta en forma de cruz",
                "Una viajera con piel palida y en escala de grises",
                "Su cabello negro fluye como cascada",
            };

            voiceFiles = {
                "hollow_SPA_019.mp3"_spr,
                "hollow_SPA_020.mp3"_spr,
                "hollow_SPA_021.mp3"_spr,
            };
        }

        if (!GM->getUGV("313"))
        {
            log::info("Hint for Secret 13 enabled");
            GM->setUGV("313", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Nock em
    if (ID == 16 && !AM->isAchievementEarned("geometry.ach.odyssey.secret14"))
    {
        messages = {
            "A bossfight approaches...",
            "Predator or prey...",
        };

        voiceFiles = {
            "hollow_ENG_023.mp3"_spr,
            "hollow_ENG_024.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Pagina numero dos...",
                "Bajo Zero...",
            };

            voiceFiles = {
                "hollow_SPA_023.mp3"_spr,
                "hollow_SPA_024.mp3"_spr,
            };
        }

        if (!GM->getUGV("314"))
        {
            log::info("Hint for Secret 14 enabled");
            GM->setUGV("314", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Machina
    if (ID == 17 && !AM->isAchievementEarned("geometry.ach.odyssey.secret15"))
    {
        messages = {
            "Silhouette harmony...",
            "Deus ex...",
        };

        voiceFiles = {
            "hollow_ENG_026.mp3"_spr,
            "hollow_ENG_027.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Casualidades, existen varias",
                "Mi favorita es el Deus Ex...",
            };

            voiceFiles = {
                "hollow_SPA_026.mp3"_spr,
                "hollow_SPA_027.mp3"_spr,
            };
        }

        if (!GM->getUGV("315"))
        {
            log::info("Hint for Secret 15 enabled");
            GM->setUGV("315", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  The seven seas
    if (ID == 18 && !AM->isAchievementEarned("geometry.ach.odyssey.secret16"))
    {
        messages = {
            "Sail forth if you dare...",
            "There used to be seven, and now they are dangerous...",
        };

        voiceFiles = {
            "hollow_ENG_029.mp3"_spr,
            "hollow_ENG_030.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Navega si te atreves...",
                "Antes eran siete, y ahora son peligrosos...",
            };

            voiceFiles = {
                "hollow_SPA_029.mp3"_spr,
                "hollow_SPA_030.mp3"_spr,
            };
        }

        if (!GM->getUGV("316"))
        {
            log::info("Hint for Secret 16 enabled");
            GM->setUGV("316", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Smooth Jazz
    if (ID == 19 && !AM->isAchievementEarned("geometry.ach.odyssey.secret17"))
    {
        messages = {
            "The Warrior of Wubstep's worst enemy...",
            "I am tired of hearing that saxophone...",
        };

        voiceFiles = {
            "hollow_ENG_032.mp3"_spr,
            "hollow_ENG_033.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "El peor enemigo del Guerrero del Wubstep...",
                "Estoy cansado de oir ese saxofon...",
            };

            voiceFiles = {
                "hollow_SPA_032.mp3"_spr,
                "hollow_SPA_033.mp3"_spr,
            };
        }

        if (!GM->getUGV("317"))
        {
            log::info("Hint for Secret 17 enabled");
            GM->setUGV("317", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Angel
    if (ID == 20 && !AM->isAchievementEarned("geometry.ach.odyssey.secret18"))
    {
        messages = {
            "Those against the demons...",
            "Their voice echoes across heaven...",
        };

        voiceFiles = {
            "hollow_ENG_035.mp3"_spr,
            "hollow_ENG_036.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Aquellos contra los demonios...",
                "Su voz resuena en el cielo...",
            };

            voiceFiles = {
                "hollow_SPA_035.mp3"_spr,
                "hollow_SPA_036.mp3"_spr,
            };
        }

        if (!GM->getUGV("318"))
        {
            log::info("Hint for Secret 18 enabled");
            GM->setUGV("318", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    m_messageID = 0;
    m_messageIDX = 0;
    return "";
};

std::string SecretVaultLayer::getBasicMessage()
{
    std::vector<std::string> messages = {
        "What brings you here?",
        "I've been rotting for years...",
        "Do I look sane to you?",
        "Welcome to the shadow realm",
        "The shadow government fears me",
        "Greheheheheh...",
        "How long you'll stay here...",
        "This will be fun...",
        "Join me... become one with the darkness",
        "Amuse me... mortal",
        "He locked me in here...",
        "It's been a while since I've seen someone here...",
    };

    int rand = (std::rand() % messages.size());
    return (messages[rand]);
};

void SecretVaultLayer::updateMessage(std::string message, MessageType type)
{
    auto flag_2 = false;
    m_response->setString(message.c_str());
    m_response->limitLabelWidth(320, 0.6f, 0.6f);
    //  log::debug("TYPE {}", (int)type);

    switch (type)
    {
    case MessageType::Basic:
        m_response->setColor({255, 255, 255});
        flag_2 = true;
        break;

    case MessageType::Special:
        m_response->setColor({255, 102, 102});
        break;

    case MessageType::WrongAnswer:
        m_response->setColor({102, 102, 102});
        m_messageID = 99;
        m_messageIDX = 0;
        break;

    case MessageType::CorrectAnswer:
        m_response->setColor({150, 102, 255});
        m_messageID = 99;
        m_messageIDX = 0;
        break;
    }

    auto flag = (std::string_view(message) == std::string_view("Welcome...") || std::string_view(message) == std::string_view("Bienvenido..."));
    //  log::debug("Test: {}", flag);
    fadeInLabel(flag, flag_2);
};

void SecretVaultLayer::fadeInLabel(bool firstTime, bool skipAnimation)
{
    if (skipAnimation && !firstTime)
    {
        for (int ii = 0; ii < strlen(m_response->getString()); ii++)
        {
            auto child = static_cast<CCSprite *>(m_response->getChildren()->objectAtIndex(ii));
            child->setOpacity(0);
        }
        return;
    }

    for (int ii = 0; ii < strlen(m_response->getString()); ii++)
    {
        auto child = static_cast<CCSprite *>(m_response->getChildren()->objectAtIndex(ii));
        child->setOpacity(0);

        if (ii == 0)
        {
            keeper_lock->setOpacity(255);

            m_textInput->runAction(CCSequence::create(
                CCCallFunc::create(this, callfunc_selector(SecretVaultLayer::disableKeeper)),
                CCDelayTime::create((strlen(m_response->getString()) * .175f) + 0.5),
                CCCallFunc::create(this, callfunc_selector(SecretVaultLayer::enableKeeper)),
                nullptr));

            if (!firstTime && m_garganIDX < 5)
            {
                keeper_body->runAction(CCSequence::create(
                    CCTintTo::create(1.f, 80, 0, 0),
                    CCDelayTime::create((strlen(m_response->getString()) * .175f) - 1),
                    CCTintTo::create(1.f, 255, 255, 255),
                    nullptr));

                keeper_eyesGlow->runAction(CCSequence::create(
                    CCFadeTo::create(1.f, 255),
                    CCDelayTime::create((strlen(m_response->getString()) * .175f) - 1),
                    CCFadeTo::create(1.f, 0),
                    nullptr));

                keeper_lock->runAction(CCSequence::create(
                    CCEaseSineOut::create(CCRotateBy::create(0.6, -15)),
                    CCEaseSineInOut::create(CCRotateBy::create(1.2, 30)),
                    CCEaseSineInOut::create(CCRotateBy::create(1.2, -30)),
                    CCEaseSineInOut::create(CCRotateBy::create(0.8, 15)),
                    nullptr));
            }
        }

        auto fadeInDelay = CCDelayTime::create(.05f * ii);
        auto fadeIn = CCFadeTo::create(.2f, 255);
        auto fadeOutDelay = CCDelayTime::create(.1f * strlen(m_response->getString()));
        auto fadeOut = CCFadeTo::create(.2f, 0);

        child->runAction(CCSequence::create(fadeInDelay, fadeIn, fadeOutDelay, fadeOut, nullptr));
    }
};

void SecretVaultLayer::enableKeeper()
{
    log::debug("Keeper enabled");

    if (m_achievementName != "")
    {
        auto GM = GameManager::sharedState();
        GM->reportAchievementWithID(m_achievementName.c_str(), 100, false);
    };

    m_textInput->setEnabled(true);
    m_keeperBtn->setEnabled(true);
};

void SecretVaultLayer::disableKeeper()
{
    log::debug("Keeper Disabled");
    m_textInput->setEnabled(false);
    m_keeperBtn->setEnabled(false);
};

void SecretVaultLayer::addLevelAnimation()
{
    auto m_levelMenu = CCMenu::create();
    m_levelMenu->setContentSize(m_levelNode->getContentSize());
    m_levelMenu->setPosition({0, 0});

    auto m_levelBtnSprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    m_levelBtnSprite->setScale(0.45f);

    m_levelBtn = CCMenuItemSpriteExtra::create(
        m_levelBtnSprite,
        this,
        nullptr);
    m_levelMenu->addChildAtPosition(m_levelBtn, Anchor::Center);
    m_levelBtn->setPositionX(100);

    m_levelTitle = CCLabelBMFont::create("Fracture", "bigFont.fnt");
    m_levelTitle->setScale(0.5f);
    m_levelTitle->setOpacity(0);

    m_levelNode->addChildAtPosition(m_levelTitle, Anchor::Top);
    m_levelNode->addChild(m_levelMenu);

    m_levelTitle->runAction(CCFadeTo::create(0.5f, 255));
    m_levelBtn->runAction(CCEaseSineOut::create(CCMoveTo::create(0.5, {0, 15})));
};

void SecretVaultLayer::onSecret(CCObject *sender)
{
    auto GM = GameManager::sharedState();
    auto GSM = GameStatsManager::sharedState();

    //  Da el achievement y incrementa la cantidad de orbes para el Jugador
    GM->reportAchievementWithID("geometry.ach.odyssey.secret21", 100, false);
    GameStatsManager::get()->incrementStat("13", 250);
    GameStatsManager::get()->incrementStat("14", 500);

    //  Crea el cofre que da los stats
    GJRewardObject *orbs = GJRewardObject::create(SpecialRewardItem::Orbs, 500, 0);
    GJRewardObject *diamonds = GJRewardObject::create(SpecialRewardItem::Diamonds, 250, 0);
    CCArray *rewards = CCArray::create();
    rewards->addObject(diamonds);
    rewards->addObject(orbs);

    //  Crea el layer que da el award
    GJRewardItem *item = GJRewardItem::createWithObjects(GJRewardType::Large, rewards);
    RewardUnlockLayer *layer = RewardUnlockLayer::create(2, nullptr);
    layer->m_chestType = 2;
    layer->setZOrder(200);

    //  Pone la escena
    cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(layer);
    layer->showCollectReward(item);

    //  Al abrirse el cofre, se reemplaza su textura y se deshabilita el boton
    auto chestTop = CCSprite::createWithSpriteFrameName("chest_02_04_001.png");
    auto chestBottom = CCSprite::createWithSpriteFrameName("chest_02_04_back_001.png");
    chestTop->setOpacity(100);
    chestBottom->setOpacity(100);

    auto sprite = CCSprite::create();
    sprite->addChild(chestTop);
    sprite->addChild(chestBottom, -1);
    sprite->setScale(0.5);

    auto btn = static_cast<CCMenuItemSpriteExtra *>(sender);
    btn->setEnabled(false);
    btn->setSprite(sprite);
};

void SecretVaultLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
    GameManager::sharedState()->fadeInMusic("comic_04.mp3"_spr);
    FMODAudioEngine::sharedEngine()->stopAllEffects();
};

void SecretVaultLayer::onBack(CCObject *)
{
    keyBackClicked();
};

SecretVaultLayer *SecretVaultLayer::create()
{
    auto ret = new SecretVaultLayer();

    if (ret->init())
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

CCScene *SecretVaultLayer::scene()
{
    auto layer = SecretVaultLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
};
