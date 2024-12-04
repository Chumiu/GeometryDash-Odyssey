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
    m_response = CCLabelBMFont::create("", "bigFont.fnt");
    addChildAtPosition(m_response, Anchor::Center, ccp(0, 105), false);
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
    if (lower == "odyssey")
    {
        response = "So you're part of the Explorers...",
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "invaders")
    {
        response = "Not so unknown now...",
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "astral")
    {
        response = "It strikes fear into my heart...",
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "dumbledalf")
    {
        response = "What a humble man...",
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "carp")
    {
        response = "Useless piece of scrap metal...",
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "comfort food")
    {
        response = "Good luck...",
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "colon")
    {
        response = "Even the lord listens to his prayers...",
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "rubrub")
    {
        response = "My hatred grows with each breath he takes...",
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "elemental")
    {
        response = "All of them together... What will happen?...",
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower != "")
    {
        std::vector<std::string> messages = {
            "Well then...",
            "You really are a fool...",
            "Enough is enough",
            "Come back when you're a little... smarter...",
            "Arrgh... you pest...",
            "Cough, cough, cough...",
            "Don't waste my time",
            "Your request means nothing",
            "Feel ashamed of yourself...",
            "A lasting impression...",
            "Is that all...?",
            "I have no idea what you're talking about...",
            "Next time say something coherent...",
            "What...?",
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
    int rand = std::rand() % 25 + 1;

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

    if (ID == 11)
    {
        std::vector<std::string> messages = {
            "So...",
            "Look how far you've come...",
            "Went through molten lands...",
            "Explored the floating worlds...",
            "Powered through the coldest of blizzards...",
            "Now you set forth to an... uh...",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 12)
    {
        std::vector<std::string> messages = {
            "From the stars above they came forth",
            "From up there to below here",
            "From a far away place",
            "They possess many colors and forms",
            "But one thing is for sure...",
            "They are the Space... hmm...",
            "What was that word again?"};

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 13)
    {
        std::vector<std::string> messages = {
            "That wretched beast...",
            "The killer of the cosmos...",
            "The galactic eradicator...",
            "Its hunger never satisfied",
            "For only one thing it truthfully desires",
            "The phoenix from the castle of jello",
            "I've forgotten that foul shellfish's name",
            "Wish I knew what it was again..."};

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 14)
    {
        std::vector<std::string> messages = {
            "It's been a long time...",
            "since anyone visited me...",
            "This place has been empty for quite long...",
            "Feels like a prison",
            "He has forgotten us",
            "But sometimes, an old man comes around...",
            "White beard, funny clothes...",
            "Has a colorful stone...",
            "I forgot his name..."};

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 15)
    {
        std::vector<std::string> messages = {
            "Oh, the old man...?",
            "He wasn't the only one that comes here",
            "There's a pink guy that comes too",
            "Oh, I despise him",
            "Getting in the middle of things",
            "Wanting to sell his garbage",
            "Thankfully, I forgot his name.",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 16)
    {
        std::vector<std::string> messages = {
            "Ever feel hungry?",
            "Check out this level I have here...",
            "It's called Comfort Food",
            "Just make sure to be careful...",
            "Wubstep is extremely addictive",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 17)
    {
        std::vector<std::string> messages = {
            "Riddle me this, riddle me that…",
            "I am a fox with many tails",
            "Afraid of arachnids and their many turns",
            "They say I smell great, they love me even",
            "You better be hiding your stash well",
            "Else I will be ashamed of its ease",
            "Who am I?..."};

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 18)
    {
        std::vector<std::string> messages = {
            "This evil, foolish ruler",
            "Taking eons to give to his land",
            "Locking us all here",
            "Betraying us for the sake of secrets",
            "And don't get me started",
            "How long it's been taking for him",
            "To give us the legendary monstrous feline..."};

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 19)
    {
        std::vector<std::string> messages = {
            "Without this, our world would be gone",
            "It's influence spreads around it",
            "It is the key to everything",
            "It even gave it's name to this whole odyssey...",
            "Whatever that means, really",
            "I'm just reciting from this book I have..."};

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 1)
    {
        std::vector<std::string> messages = {
            "You might wonder...",
            "Where I got the skull from",
            "It's a long story...",
            "I found it from a corpse laying around...",
            "Ok, maybe that wasn't long..."};

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 2)
    {
        std::vector<std::string> messages = {
            "It has been so long...",
            "Since I've last seen the light...",
            "And yet he lets me live...",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
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
        m_response->setColor({102, 255, 255});
        break;

    case MessageType::WrongAnswer:
        m_response->setColor({255, 102, 102});
        break;

    case MessageType::CorrectAnswer:
        m_response->setColor({102, 255, 102});
        break;
    }
};

void SecretVaultLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
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