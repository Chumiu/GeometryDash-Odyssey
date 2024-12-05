#include "SecretVaultLayer.hpp"
#include "../utils/Utils.hpp"

bool SecretVaultLayer::init()
{
    if (!CCLayer::init())
        return false;

    //  Title
    auto title = CCLabelBMFont::create("The Hollow", "goldFont.fnt");
    addChildAtPosition(title, Anchor::Top, ccp(0, -22), false);

    //  Background
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto background = CCSprite::createWithSpriteFrameName("HollowBG_001.png"_spr);

    background->setScaleX((winSize.width) / background->getTextureRect().size.width);
    background->setScaleY((winSize.height) / background->getTextureRect().size.height);
    background->setAnchorPoint({0, 0});
    background->setPosition({0, 0});
    background->setColor({120, 0, 0});
    background->setID("background"_spr);
    addChild(background, -2);

    //  Back Button
    auto menuBack = CCMenu::create();
    menuBack->setPosition({24, winSize.height - 24});
    menuBack->setID("back-menu"_spr);
    addChild(menuBack);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(SecretVaultLayer::onBack));

    backBtn->setID("back-button"_spr);
    backBtn->setSizeMult(1.2f);
    menuBack->addChild(backBtn);

    //  Text Input
    m_textInput = TextInput::create(180, "...");
    m_textInput->setFilter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ");
    m_textInput->setMaxCharCount(20);
    addChildAtPosition(m_textInput, Anchor::Center, ccp(0, 65), false);

    //  Response message
    m_response = CCLabelBMFont::create("", "gjFont41.fnt");
    addChildAtPosition(m_response, Anchor::Center, ccp(0, 100), false);
    updateMessage("Welcome...", MessageType::Basic);

    //  Creating the Vault keeper
    auto keeperMenu = CCMenu::create();
    keeperMenu->setPosition({0, 0});
    addChild(keeperMenu);

    auto keeperSprite = CCSprite::createWithSpriteFrameName("HollowKeeper_001.png"_spr);
    keeperSprite->setScale(1.15f);

    auto keeperButton = CCMenuItemSpriteExtra::create(
        keeperSprite,
        this,
        menu_selector(SecretVaultLayer::onSubmit));

    keeperButton->setPosition({winSize.width / 2, winSize.height / 2 - 20.f});
    keeperMenu->addChild(keeperButton);

    // auto * test = new GameToolBox();

    auto particles_01 = GameToolbox::particleFromString("50a-1a2a0.5a15a90a0a50a25a400a0a0a0a0a0a0a0a15a7a0a0a0a0a0a0a0a0a1a0a0a0a0a0a0a0a0a0a0a0a1a0a0.5a0.2a0.5a0.2a0a0a0a0a0a0a0a2a0a0a0a0a25a0a0a0a0a0a0a1a0a0a0a0a0a0a0", NULL, false);
    particles_01->setPositionX(winSize.width / 2);
    addChild(particles_01);

    auto particles_02 = GameToolbox::particleFromString("10a-1a4a2a1a90a0a15a10a400a100a0a0a0a0a0a0a100a50a0a0a0a0a0a0a0a0a0.5a0.25a0a0a0a0a0a0a0a0a0a0a0.5a0.25a1a0a1a0a0a0a0a0a0a0a0a2a0a0a0a0a40a0a0a0a0a0a0a1a0a0a0a0a0a0a0", NULL, false);
    particles_02->setPosition(winSize / 2);
    addChild(particles_02);

    GameManager::sharedState()->fadeInMusic("SecretLoop01.mp3"_spr);
    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    return true;
};

void SecretVaultLayer::onSubmit(CCObject *)
{
    std::string response = getMessage();
    std::string lower;

    auto GM = GameManager::sharedState();
    auto AM = AchievementManager::sharedState();

    for (auto elem : m_textInput->getString())
        lower += std::tolower(elem);

    m_textInput->setString("");

    //  List of codes
    if (lower == "color" && !AM->isAchievementEarned("geometry.ach.odyssey.secret10"))
    {
        response = "This is monochromatic, is it?",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret10", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "fracture")
    {
        response = "Embrace the chaos",
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "explorers" && !AM->isAchievementEarned("geometry.ach.odyssey.secret11"))
    {
        response = "Maybe in the next update...",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret11", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "player" && !AM->isAchievementEarned("geometry.ach.odyssey.secret12"))
    {
        response = "...Was it you?",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret12", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "mono" && !AM->isAchievementEarned("geometry.ach.odyssey.secret13"))
    {
        response = "Something about her feels off...",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret13", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "nock em" && !AM->isAchievementEarned("geometry.ach.odyssey.secret14"))
    {
        response = "Enemy defeated... not",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret14", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "machina" && !AM->isAchievementEarned("geometry.ach.odyssey.secret15"))
    {
        response = "How sudden...",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret15", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "the seven seas" && !AM->isAchievementEarned("geometry.ach.odyssey.secret16"))
    {
        response = "Guide us, captain...",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret16", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "smooth jazz" && !AM->isAchievementEarned("geometry.ach.odyssey.secret17"))
    {
        response = "Blergh",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret17", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "angel" && !AM->isAchievementEarned("geometry.ach.odyssey.secret18"))
    {
        response = "The holy...",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret18", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "gargan")
    {
        response = "What do you mean?...",
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower != "")
    {
        std::vector<std::string> messages = {
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
            "..."};

        int rand = (std::rand() % messages.size());
        response = messages[rand];

        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

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

        if (message == "")
            message = getBasicMessage();
        m_messageIDX++;

        return message;
    }
    else
    {
        auto ret = getThreadMessage(m_messageID, m_messageIDX++);
        if (ret == "")
            ret = getBasicMessage();
        return ret;
    }
};

std::string SecretVaultLayer::getThreadMessage(int ID, int index)
{
    log::debug("ID: {} - IDX: {}", ID, index);

    //  auto GM = GameManager::sharedState();
    auto AM = AchievementManager::sharedState();

    //  Color
    if (ID == 11 && !AM->isAchievementEarned("geometry.ach.odyssey.secret10"))
    {
        std::vector<std::string> messages = {
            "I am the language of light",
            "I give life to all you see",
            "Without me, the world would be gray...",
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Fracture
    if (ID == 12)
    {
        std::vector<std::string> messages = {
            "Sometimes, breaking isn't the end, but the start...",
            "Dive into the glitchy abyss I have for you",
            "It's called fracture",
            "Hold on tight",
            "The beats here might just split reality",
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Explorers
    if (ID == 13 && !AM->isAchievementEarned("geometry.ach.odyssey.secret11"))
    {
        std::vector<std::string> messages = {
            "That failed promise",
            "That guardian of the forest temple",
            "Delayed until the end of time...",
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Player
    if (ID == 14 && !AM->isAchievementEarned("geometry.ach.odyssey.secret12"))
    {
        std::vector<std::string> messages = {
            "They have doomed this world...",
            "They who let the Darkness out...",
            "Who could it be? Perhaps, is it in front of me?",
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Mono
    if (ID == 15 && !AM->isAchievementEarned("geometry.ach.odyssey.secret13"))
    {
        std::vector<std::string> messages = {
            "Her cross-shaped ribbon and blank eyes...",
            "A traveler with pale, greyscale skin...",
            "Her pure black hair flows like a waterfall...",
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Nock em
    if (ID == 16 && !AM->isAchievementEarned("geometry.ach.odyssey.secret14"))
    {
        std::vector<std::string> messages = {
            "A bossfight approaches...",
            "Predator or prey...",
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Machina
    if (ID == 17 && !AM->isAchievementEarned("geometry.ach.odyssey.secret15"))
    {
        std::vector<std::string> messages = {
            "Silhouette harmony...",
            "Deus ex...",
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  The seven seas
    if (ID == 18 && !AM->isAchievementEarned("geometry.ach.odyssey.secret16"))
    {
        std::vector<std::string> messages = {
            "Sail forth if you dare...",
            "They used to be seven...",
            "And now they are dangerous...",
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Smooth Jazz
    if (ID == 19 && !AM->isAchievementEarned("geometry.ach.odyssey.secret17"))
    {
        std::vector<std::string> messages = {
            "The warrior of Wubstep's worst enemy...",
            "I am tired of hearing that saxophone...",
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Angel
    if (ID == 20 && !AM->isAchievementEarned("geometry.ach.odyssey.secret18"))
    {
        std::vector<std::string> messages = {
            "Those against the demons...",
            "Their voice echoes across heaven...",
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

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
        "How long you'll stay here?...",
        "This will be fun...",
        "Join me... become one with the darkness",
        "Amuse me... mortal",
        "He locked me in here...",
        "It's been a while I seen someone here...",
        "..."};

    int rand = (std::rand() % messages.size());
    return (messages[rand]);
};

void SecretVaultLayer::updateMessage(std::string message, MessageType type)
{
    m_response->setString(message.c_str());
    m_response->limitLabelWidth(320, 0.6f, 0.6f);
    log::debug("TYPE {}", (int)type);

    switch (type)
    {
    case MessageType::Basic:
        m_response->setColor({255, 255, 255});
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
};

void SecretVaultLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
    GameManager::sharedState()->fadeInMenuMusic();
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