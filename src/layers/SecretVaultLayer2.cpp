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
    m_response = CCLabelBMFont::create("", "gjFont42.fnt");
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
    if (lower == "odyssey" && !AM->isAchievementEarned("geometry.ach.odyssey.secret01"))
    {
        response = "So you know how to adventure...",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret01", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "invaders" && !AM->isAchievementEarned("geometry.ach.odyssey.secret02"))
    {
        response = "Not so unknown now...",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret02", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "astral" && !AM->isAchievementEarned("geometry.ach.odyssey.secret03"))
    {
        response = "It strikes fear into my heart...",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret03", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "dumbledalf" && !AM->isAchievementEarned("geometry.ach.odyssey.secret04"))
    {
        response = "What a humble man...",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret04", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "carp" && !AM->isAchievementEarned("geometry.ach.odyssey.secret05"))
    {
        response = "Useless piece of scrap metal...",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret05", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "uncertain")
    {
        response = "Good luck...",
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "colon" && !AM->isAchievementEarned("geometry.ach.odyssey.secret06"))
    {
        response = "Even the lord listens to his prayers...",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret06", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "rubrub" && !AM->isAchievementEarned("geometry.ach.odyssey.secret07"))
    {
        response = "My hatred grows with each breath he takes...",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret07", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "elemental" && !AM->isAchievementEarned("geometry.ach.odyssey.secret08"))
    {
        response = "All of them together... What will happen?...",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret08", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "demon gauntlet" && !AM->isAchievementEarned("geometry.ach.odyssey.secret09"))
    {
        response = "You see? I wasn't lying!",
        GM->reportAchievementWithID("geometry.ach.odyssey.secret09", 100, false);
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    //  Random easter eggs
    if (lower == "switch")
    {
        response = "The skeleton appears",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "master")
    {
        response = "Cubical genius",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "mathi")
    {
        response = "Mathi approved",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "cyanflower")
    {
        response = "what even is a slimeboy?",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "ghostpower")
    {
        response = "XD",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "nando")
    {
        response = "Donde he oido antes ese nombre?",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "monstercat")
    {
        response = "One day... surely",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "spooky")
    {
        response = "We don't talk about Spooky",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "sparky")
    {
        response = "No coins here, bud",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "glubfub")
    {
        response = "Never liked him",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "gatekeeper")
    {
        response = "We used to be together...",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "wraith")
    {
        response = "One-liners make me mad...",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "the hollow")
    {
        response = "no...",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "lunar")
    {
        response = "Who?",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "nukebound")
    {
        response = "Nukebound to what?",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "wanderer")
    {
        response = "I'm pretty sure he isn't dead",
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    //  Wrong answers
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

    //  auto GM = GameManager::sharedState();
    auto AM = AchievementManager::sharedState();

    //  Odyssey
    if (ID == 11 && !AM->isAchievementEarned("geometry.ach.odyssey.secret01"))
    {
        std::vector<std::string> messages = {
            "So...",
            "Look how far you've come",
            "Went through molten lands",
            "Explored floating worlds",
            "And endure subzero temperatures",
            "Now, you set for to an...",
            "Uh..."
            "What was the word again?"};

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    //  Invaders
    if (ID == 12 && !AM->isAchievementEarned("geometry.ach.odyssey.secret02"))
    {
        std::vector<std::string> messages = {
            "From the stars above they came forth",
            "From up there to below here",
            "From a far away place",
            "They possess many colors and forms",
            "One thing for sure...",
            "They are the space... uh...",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    //  Astral
    if (ID == 13 && !AM->isAchievementEarned("geometry.ach.odyssey.secret03"))
    {
        std::vector<std::string> messages = {
            "That wretched beast...",
            "The killer of cosmos...",
            "The galactic eradicator...",
            "It's hunger never satisfied",
            "For only one thing it trully desires",
            "The phoenix from castle of jello is against him",
            "I've forgotten that foul shellfish's name",
            "I wish I knew what it was again...",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    //  Dumbledalf
    if (ID == 14 && !AM->isAchievementEarned("geometry.ach.odyssey.secret04"))
    {
        std::vector<std::string> messages = {
            "It's been a long time...",
            "Since anyone visited me",
            "This place has been empty for long",
            "Feels like a prison",
            "Rubrub has forgotten us",
            "But sometimes, an old man comes around",
            "Funny clothes, white beard...",
            "And he always carries this colorful stone",
            "I wish I could remember his name...",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    //  Carp
    if (ID == 15 && !AM->isAchievementEarned("geometry.ach.odyssey.secret05"))
    {
        std::vector<std::string> messages = {
            "Oh, yeah... I remember",
            "The old man isn't the only one...",
            "That pink guy would come too",
            "Oh... I hate him!",
            "Always getting in the way!",
            "Selling his junk!",
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

    //  Uncertain
    if (ID == 16)
    {
        std::vector<std::string> messages = {
            "Have you ever been sure of something?",
            "Sometimes I think about strange things",
            "There's a hidden level here...",
            "It makes me think about that stuff",
            "It's name is uncertain...",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    //  Colon
    if (ID == 17 && !AM->isAchievementEarned("geometry.ach.odyssey.secret06"))
    {
        std::vector<std::string> messages = {
            "Riddle me this, riddle me that...",
            "I am a fox with many tails",
            "Afraid of arachnids with sharp turns",
            "They say I smell great",
            "You better be hiding your gold well",
            "Else I will be ashamed of its ease...",
            "Who am I?",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    //  Rubrub
    if (ID == 18 && !AM->isAchievementEarned("geometry.ach.odyssey.secret07"))
    {
        std::vector<std::string> messages = {
            "That evil, foolish ruler",
            "Taking eons to give to his land",
            "Locking us all here",
            "Betraying us for the sake of secrets",
            "And don't get me started",
            "How long it took him",
            "To give us the legendary creation tools",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    //  Elemental
    if (ID == 19 && !AM->isAchievementEarned("geometry.ach.odyssey.secret08"))
    {
        std::vector<std::string> messages = {
            "Without this, our world would be gone",
            "It's influence spreads around it",
            "It's the key to everything",
            "It even game it's name..."
            "To this whole odyssey",
            "Whatever that means, really",
            "I'm just reciting from this book I have",
        };

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    //  Elemental
    if (ID == 20 && !AM->isAchievementEarned("geometry.ach.odyssey.secret09"))
    {
        std::vector<std::string> messages = {
            "So, you know a lot about keys",
            "That reminds me...",
            "There was one time...",
            "Someone released the demon guardian",
            "What a doozy...",
            "It did bring forth something else...",
            "A large, monstrous cave",
            "They say demons lurk there",
            "If you were to challenge it",
            "Be ready to face hell"};

        if (m_messageIDX == messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[m_messageIDX];
    }

    //  Dialog with no purpose
    if (ID == 1)
    {
        std::vector<std::string> messages = {
            "You're still here?",
            "You've been more patient than many",
            "Perhaps you're worthy of my time",
            "Just give me a moment",
            "I need to go to sleep",
            "Zzz...",
            "...",
            "......",
            "Greh...",
            "...",
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
            "Grough...",
            "Who dares enter my lair?",
            "Oh... it's just a player",
            "What brings you here?",
            "Have you come forward to listen to my riddles?",
            "Do you seek to rebel against our leader too?",
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
            "It isn't the first time someone did that",
            "And it certainly won't be the last time",
            "If I could smash you with my mighty club",
            "It would be great",
            "But I've lost my hands years ago",
            "He took them away from me",
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
            "A long time ago",
            "Longer than you've been born for",
            "That's for sure",
            "All in the name of secrets...",
            "Every time someone comes here",
            "They just yell at me things",
            "They never listen to me or my riddles",
            "And then leave, mad...",
            "Is it something on my face?",
            "It is beyond me...",
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
        "Have you come forward to listen to my riddles?",
        "Do you seek to rebel against our leader too?",
        "...",
        "......",
        "You're here to bug me",
        "You futile little pest",
        "It isn't the first time someone did that",
        "If I could smash you with my mighty club",
        "You're still here?",
        "You've been more patient than many",
        "Perhaps you're worthy of my time",
        "Zzz...",
        "Greh...",
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
        m_response->setColor({102, 255, 102});
        break;

    case MessageType::WrongAnswer:
        m_response->setColor({255, 102, 102});
        m_messageID = 0;
        m_messageIDX = 0;
        break;

    case MessageType::CorrectAnswer:
        m_response->setColor({102, 255, 255});
        m_messageID = 0;
        m_messageIDX = 0;
        break;
    }
};

void SecretVaultLayer2::keyBackClicked()
{
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
    GameManager::sharedState()->fadeInMenuMusic();
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