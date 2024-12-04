#include "SecretVaultLayer2.hpp"
#include "../utils/Utils.hpp"

bool SecretVaultLayer2::init()
{
    if (!CCLayer::init())
        return false;

    //  Title
    auto title = CCLabelBMFont::create("The Ogre", "goldFont.fnt");
    addChildAtPosition(title, Anchor::Top, ccp(0, -22), false);

    //  Background
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto background = CCSprite::create("GJ_gradientBG.png");

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
        menu_selector(SecretVaultLayer2::onBack));

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

    auto keeperSprite = CCSprite::createWithSpriteFrameName("GJ_secretLock_001.png");
    keeperSprite->setScale(1.15f);

    auto keeperButton = CCMenuItemSpriteExtra::create(
        keeperSprite,
        this,
        menu_selector(SecretVaultLayer2::onSubmit));

    keeperButton->setPosition({winSize.width / 2, winSize.height / 2 - 20.f});
    keeperMenu->addChild(keeperButton);

    GameManager::sharedState()->fadeInMusic("SecretLoop02.mp3"_spr);
    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    return true;
};

void SecretVaultLayer2::onSubmit(CCObject *)
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

    if (lower == "demon gauntlet")
    {
        response = "You see? I wasn't lying!",
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower != "")
    {
        std::vector<std::string> messages = {
            "Argh...",
            "You're just like the other people",
            "Yelling nonsense at me will do nothing",
            "False...",
            "Missed one, try another!",
            "Incorrect guess!",
            "This room isn't silent",
            "Let me finish...",
            "Raaagh...",
            "Growl...",
            "Reaaah...",
            "Foolish mortal!",
            "Enough is enough",
            "Its time to stop",
            "Betsy... get him",
            "What is this...",
            "Don't you have better things to do?",
            "You're wasting my time",
            "Will you ever leave?",
            "...",
            "Everytime you fail, I get madder",
            "No",
            "Nuh uh!",
            "Close enough",
            "I will smash you to bits...",
            "Get out of my vault"};

        int rand = (std::rand() % messages.size());
        response = messages[rand];

        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    //  Gets the type color
    MessageType type = (m_messageID > 10) ? MessageType::Special : MessageType::Basic;
    updateMessage(response, type);
};

std::string SecretVaultLayer2::getMessage()
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

std::string SecretVaultLayer2::getThreadMessage(int ID, int index)
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
            "I need to go to sleep",
            "Zzz...",
            "...",
            "......",
            "Greh...",
            "Snore Mimimimi..."
            "...",
            "Huh...?",
            "You're still here?",
        };

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
            "Somebody once told me",
            "I remind them of someone else",
            "Mean and green...",
            "Surely I'm not that guy",
            "But I like their attitude",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 3)
    {
        std::vector<std::string> messages = {
            "Being locked for years",
            "Sure takes a toll on your head",
            "But at least I don't have to see",
            "People arguing about flaming faces",
            "Heheh... that's some good stuff",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 4)
    {
        std::vector<std::string> messages = {
            "My mighty club...",
            "Her name is Betsy",
            "She swings far and hits hard",
            "That's what she also says about me",
            "At least, I think I heard her say it once",
            "Is my club possessed by a ghost?",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 5)
    {
        std::vector<std::string> messages = {
            "I would normally tell you",
            "To leave me be",
            "But you seem chill",
            "I would also give you a cup of leaf water",
            "But I have no hands anymore",
            "So ask Betsy",
            "If she even can",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 6)
    {
        std::vector<std::string> messages = {
            "Sometimes I look at the ceiling",
            "It tends to say gullible",
            "Don't believe me? Look up",
            "It worked on one guy at least",
            "I laughed so high when it happened",
            "And then he locked me in here",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    if (ID == 7)
    {
        std::vector<std::string> messages = {
            "What is a sleep schedule?",
            "A miserable little pile of times",
            "But enough talk",
            "Its time for me to rest",
            "Please...",
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

std::string SecretVaultLayer2::getBasicMessage()
{
    std::vector<std::string> messages = {
        "Grough...",
        "Who dares enter my lair?",
        "Oh... it's just a player",
        "What brings you here?",
        "Have you come again to listen to my riddles?",
        "Do you seek to rebel against our leader too?",
        "...",
        "You're just here to bug me",
        "You futile little pest",
        "You're not the first not the last that will annoy me",
        "You've been more patient than many",
        "Perhaps you're worthy of my time",
        "Just give me a moment",
    };

    int rand = (std::rand() % messages.size());
    return (messages[rand]);
};

void SecretVaultLayer2::updateMessage(std::string message, MessageType type)
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
        m_messageID = 0;
        m_messageIDX = 0;
        break;

    case MessageType::CorrectAnswer:
        m_response->setColor({102, 255, 102});
        m_messageID = 0;
        m_messageIDX = 0;
        break;
    }
};

void SecretVaultLayer2::keyBackClicked()
{
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
};

void SecretVaultLayer2::onBack(CCObject *)
{
    keyBackClicked();
};

SecretVaultLayer2 *SecretVaultLayer2::create()
{
    auto ret = new SecretVaultLayer2();

    if (ret->init())
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

CCScene *SecretVaultLayer2::scene()
{
    auto layer = SecretVaultLayer2::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
};