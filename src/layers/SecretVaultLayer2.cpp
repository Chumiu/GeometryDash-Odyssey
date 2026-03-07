#include "SecretVaultLayer2.hpp"
#include "../utils/Dialogs.hpp"
#include "../utils/Utils.hpp"
#include "OdysseySelectLayer.hpp"

bool SecretVaultLayer2::init()
{
    if (!CCLayer::init())
        return false;

    //  Flag that saves whenever the Vault should be in Spanish or not.
    m_spanish = GameManager::sharedState()->getGameVariable("0201");

    //  Title
    auto title = CCLabelBMFont::create("The Ogre", "goldFont.fnt");
    addChildAtPosition(title, Anchor::Top, ccp(0, -22), false);

    //  Background Details
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto background = CCSprite::create("GJ_gradientBG.png");

    background->setScaleX((winSize.width) / background->getTextureRect().size.width);
    background->setScaleY((winSize.height) / background->getTextureRect().size.height);
    background->setAnchorPoint({0, 0});
    background->setPosition({0, 0});
    background->setColor({0, 30, 0});
    background->setID("background"_spr);
    addChild(background, -5);

    auto bgDeco = CCSprite::createWithSpriteFrameName("OgreBG_2_001.png"_spr);
    bgDeco->setPosition({0, 0});
    bgDeco->setAnchorPoint({0, 0});
    bgDeco->setColor({0, 50, 0});
    bgDeco->setOpacity(180);
    bgDeco->setScaleX((winSize.width) / bgDeco->getTextureRect().size.width);
    bgDeco->setScaleY((winSize.height) / bgDeco->getTextureRect().size.height);
    bgDeco->setBlendFunc({GL_SRC_ALPHA, GL_ONE});

    auto bgDeco1A = CCSprite::createWithSpriteFrameName("OgreBG_3_001.png"_spr);
    bgDeco1A->setPosition({0, 0});
    bgDeco1A->setAnchorPoint({0, 0});
    bgDeco1A->setColor({0, 0, 0});
    bgDeco1A->setScaleY((winSize.height) / bgDeco1A->getTextureRect().size.height);
    //  bgDeco1A->setBlendFunc({GL_SRC_ALPHA, GL_ONE});

    auto bgDeco1B = CCSprite::createWithSpriteFrameName("OgreBG_3_001.png"_spr);
    bgDeco1B->setPosition({winSize.width, 0});
    bgDeco1B->setAnchorPoint({1, 0});
    bgDeco1B->setColor({0, 0, 0});
    bgDeco1B->setFlipX(true);
    bgDeco1B->setScaleY((winSize.height) / bgDeco1B->getTextureRect().size.height);
    //  bgDeco1B->setBlendFunc({GL_SRC_ALPHA, GL_ONE});

    addChild(bgDeco, -3);
    addChild(bgDeco1A, -1);
    addChild(bgDeco1B, -1);

    //  Fireflies particles
    auto bg_particle_01 = GameToolbox::particleFromString("30a-1a5a1a5a90a180a50a25a300a150a0a0a0a0a0a0a8a4a0a0a1a0a1a0a0a0a1a0a0a0a0a0a1a0a1a0a0a0a1a0a0.3a0.15a0.3a0.15a0a0a0a0a0a0a0a2a1a0a0a0a159a0a0a0a0a0a0a1a0a0a0a0a0a0a0", NULL, false);
    bg_particle_01->setPosition(winSize / 2);
    addChild(bg_particle_01, 10);

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
    addChildAtPosition(m_textInput, Anchor::Center, ccp(0, 60), false);

    //  Response message
    m_response = CCLabelBMFont::create("", "gjFont42.fnt");
    addChildAtPosition(m_response, Anchor::Center, ccp(0, 100), false);

    //  Initial Message
    auto introMessage = m_spanish ? "Bienvenido" : "Welcome";
    updateMessage(introMessage, MessageType::Basic);

    //  Creating the Vault keeper
    auto keeperMenu = CCMenu::create();
    keeperMenu->setPosition({0, 0});
    addChild(keeperMenu);

    auto keeperSprite = CCSprite::createWithSpriteFrameName("OgreKeeper_001.png"_spr);
    keeperSprite->setScale(1.15f);

    auto keeperButton = CCMenuItemSpriteExtra::create(
        keeperSprite,
        this,
        menu_selector(SecretVaultLayer2::onSubmit));

    keeperButton->setContentSize({72.f, 72.f});
    keeperButton->setPosition({winSize.width / 2, winSize.height / 2 - 20.f});
    keeperSprite->setAnchorPoint({0.5, 1});
    keeperSprite->setPositionY(72.f);

    keeperMenu->addChild(keeperButton);

    //  Re-verifies whenever the vault rewards have been all Claimed
    Odyssey::hasAllVaultRewards();

    //  Message if all the rewards were collected
    if (GameManager::sharedState()->getUGV("231"))
    {
        auto message = m_spanish ? "No hay nada mas que obtener de aqui..." : "Nothing more to get from here...";
        auto text = CCLabelBMFont::create(message, "gjFont41.fnt");
        text->setPosition({winSize.width / 2, 20});
        text->setColor({0, 150, 0});
        text->setOpacity(150);
        text->setScale(0.5f);
        addChild(text);
    }

    // puerta
    auto doorSpr = CCSprite::createWithSpriteFrameName("GDO_VaultDoor_001.png"_spr);
    // doorSpr->setColor({0, 255, 0});
    doorSpr->setAnchorPoint({.5f, .5f});
    doorSpr->setScale(.7f);

    auto doorBtn = CCMenuItemSpriteExtra::create(doorSpr, this, menu_selector(SecretVaultLayer2::onExtraLevels));

    auto doorParticle = GameToolbox::particleFromString("30a-1a1a0.3a16a90a7a0a0a34a35a0a-17a30a0a20a0a8a6a0a0a0.890196a0a1a0a0a0a1a0a1a1a0a0a0.0823529a0a0.72549a0a0a0a1a0a0.19a0a0.38a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
    doorParticle->setPosition(doorSpr->getScaledContentSize() / 2);

    doorBtn->addChild(doorParticle);

    auto doorMenu = CCMenu::create();
    doorMenu->setPosition({winSize.width - 45, 45});
    doorMenu->addChild(doorBtn);
    //  addChild(doorMenu);

    auto m_doorSpr = CCSprite::createWithSpriteFrameName("GDO_VaultDoor_001.png"_spr);
    m_doorSpr->setAnchorPoint({.5f, .5f});
    m_doorSpr->setScale(.7f);

    m_doorBtn = CCMenuItemSpriteExtra::create(
        doorSpr,
        this,
        menu_selector(SecretVaultLayer2::onExtraLevels));
    m_doorBtn->setID("ogre-path-door");
    m_doorBtn->m_scaleMultiplier = 1;
    m_doorBtn->m_colorEnabled = true;
    m_doorBtn->m_colorDip = 100.f;
    keeperMenu->addChildAtPosition(m_doorBtn, Anchor::BottomRight, ccp(-50, 50), false);

    auto m_doorParticles = GameToolbox::particleFromString("30a-1a1a0.3a16a90a7a0a0a34a35a0a-17a30a0a20a0a8a6a0a0a0.890196a0a1a0a0a0a1a0a1a1a0a0a0.0823529a0a0.72549a0a0a0a1a0a0.19a0a0.38a0a0a0a0a0a0a0a0a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
    m_doorParticles->setID("door-particles");
    m_doorBtn->addChildAtPosition(m_doorParticles, Anchor::Center, ccp(0, 0), false);

    auto GM = GameManager::sharedState();
    if ((!GM->getUGV("280") || !GM->getUGV("281")) && !Mod::get()->getSettingValue<bool>("bypass-vaults"))
    {
        m_doorParticles->setOpacity(0);
        m_doorBtn->setColor({0, 0, 0});
        m_doorBtn->setEnabled(false);
    }

    if (GM->getUGV("280") && !GM->getUGV("281"))
    {
        this->runAction(CCSequence::create(
            CCDelayTime::create(0.5f),
            CCCallFunc::create(this, callfunc_selector(SecretVaultLayer2::getOgreDialog)),
            CCDelayTime::create(3.0f),
            CCCallFunc::create(this, callfunc_selector(SecretVaultLayer2::enableGate)),
            0));
    }

    //  Menu sound
    GameManager::sharedState()->fadeInMusic("SecretLoop02.mp3"_spr);
    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    return true;
};

void SecretVaultLayer2::getOgreDialog()
{
    auto dialog = Odyssey::createDialogExt("ogre-beginning", 3);
    GameManager::sharedState()->setUGV("281", true);
    addChild(dialog, 3);
};

void SecretVaultLayer2::enableGate()
{
    if (m_doorBtn)
    {
        m_doorBtn->runAction(CCTintTo::create(2, 255, 255, 255));
        m_doorBtn->setEnabled(true);

        if (auto particles = this->getChildByIDRecursive("door-particles"))
        {
            particles->runAction(CCFadeTo::create(2, 255));
        }
    }
};

void SecretVaultLayer2::onExtraLevels(CCObject *)
{
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, OdysseySelectLayer::scene(3)));
}

void SecretVaultLayer2::onSubmit(CCObject *)
{
    std::string response = getMessage();
    std::vector<gd::string> messages;
    std::vector<gd::string> reply;

    auto GM = GameManager::sharedState();
    auto AM = AchievementManager::sharedState();

    std::string lower = m_textInput->getString();
    std::transform(
        lower.begin(), lower.end(), lower.begin(), [](unsigned char c)
        { return std::tolower(c); });

    m_textInput->setString("");

    //  List of codes
    if (std::string_view(lower) == std::string_view("odyssey") && !AM->isAchievementEarned("geometry.ach.odyssey.secret01") && GM->getUGV("301"))
    {
        reply = {
            "So you know how to adventure...",
            "Entonces sabes como Adventurar...",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret01", 100, false);
        return;
    };

    if (std::string_view(lower) == std::string_view("invaders") && !AM->isAchievementEarned("geometry.ach.odyssey.secret02") && GM->getUGV("302"))
    {
        reply = {
            "Not so unknown now...",
            "Ahora no son tan desconocidos",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret02", 100, false);
        return;
    };

    if (std::string_view(lower) == std::string_view("astral") && !AM->isAchievementEarned("geometry.ach.odyssey.secret03") && GM->getUGV("303"))
    {
        reply = {
            "It strikes fear into my heart...",
            "Solo con oirlo me da escalofrios...",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret03", 100, false);
        return;
    };

    if (std::string_view(lower) == std::string_view("dumbledalf") && !AM->isAchievementEarned("geometry.ach.odyssey.secret04") && GM->getUGV("304"))
    {
        reply = {
            "What a humble man",
            "Que hombre tan humilde!",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret04", 100, false);
        return;
    };

    if (std::string_view(lower) == std::string_view("carp") && !AM->isAchievementEarned("geometry.ach.odyssey.secret05") && GM->getUGV("305"))
    {
        reply = {
            "Useless piece of scrap metal",
            "Inutil pedazo de metal",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret05", 100, false);
        return;
    };

    if (std::string_view(lower) == std::string_view("colon") && !AM->isAchievementEarned("geometry.ach.odyssey.secret06") && GM->getUGV("306"))
    {
        reply = {
            "Even the lord listens to his guidance...",
            "Hasta el lord escucha sus plegarias...",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret06", 100, false);
        return;
    };

    if (std::string_view(lower) == std::string_view("rubrub") && !AM->isAchievementEarned("geometry.ach.odyssey.secret07") && GM->getUGV("307"))
    {
        reply = {
            "My hatred towards him grows every day...",
            "Mi odio hacia el crece cada dia...",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret07", 100, false);
        return;
    };

    if (std::string_view(lower) == std::string_view("elemental") && !AM->isAchievementEarned("geometry.ach.odyssey.secret08") && GM->getUGV("308"))
    {
        reply = {
            "All of them together... what will happen?",
            "Todos juntos... que pasara?",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret08", 100, false);
        return;
    };

    if (std::string_view(lower) == std::string_view("demon gauntlet") && !AM->isAchievementEarned("geometry.ach.odyssey.secret09") && GM->getUGV("309"))
    {
        reply = {
            "SEE? I wasn't lying!",
            "Ves? No te estaba mintiendo!",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret09", 100, false);
        return;
    };

    if (std::string_view(lower) == std::string_view("sigma") && !AM->isAchievementEarned("geometry.ach.odyssey.secret22") && GM->getUGV("322"))
    {
        reply = {
            "What? I thought it was Delta",
            "Huh? Crei que era Delta",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret22", 100, false);
        return;
    };

    if (std::string_view(lower) == std::string_view("editor") && !AM->isAchievementEarned("geometry.ach.odyssey.secret23") && GM->getUGV("323"))
    {
        reply = {
            "Have you made a level yet?",
            "Ya hicistes un nivel?",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret23", 100, false);
        return;
    };

    //  Random easter eggs
    if (std::string_view(lower) == std::string_view("switch"))
    {
        reply = {
            "The skeleton appears",
            "El esqueleto aparece!",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("master"))
    {
        reply = {
            "Cubical genius",
            "Genio cubico",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("mathi"))
    {
        response = "Mathi approved";
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("cyanflower"))
    {
        reply = {
            "What's a slimeboy?",
            "Que es un slimeboy?",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("monstercat"))
    {
        reply = {
            "One day, surely...",
            "Un dia, seguramente...",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("spooky"))
    {
        reply = {
            "We don't talk about spooky",
            "Aqui no se habla de spooky",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("sparky"))
    {
        reply = {
            "No coins here, bud",
            "Aqui no vas a encontrar una moneda",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("glubfub"))
    {
        reply = {
            "Never liked him",
            "Nunca me agrado",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("gatekeeper"))
    {
        reply = {
            "We used to be togeher... but then I got locked here",
            "Estabamos juntos. Pero me encerraron aqui",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("wraith"))
    {
        reply = {
            "Always being a one-liner. Makes me mad",
            "Solo escuchar su nombre me enfurece",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("the hollow"))
    {
        response = "No...";
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("lunar"))
    {
        reply = {
            "Who?",
            "Quien?",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("nukebound"))
    {
        reply = {
            "Nukebound to what?",
            "Que es eso? Se puede comer?",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("wanderer"))
    {
        reply = {
            "I'm pretty sure he isn't dead",
            "Te aseguro que ese no esta muerto",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("mono"))
    {
        reply = {
            "Maybe say her name to my brother...",
            "Tal vez deberias decir su nombre a mi hermano",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    if (std::string_view(lower) == std::string_view("scarlet") || std::string_view(lower) == std::string_view("melissa") || std::string_view(lower) == std::string_view("sasha"))
    {
        reply = {
            "That name sounds familiar...",
            "Ese nombre suena familiar...",
        };
        updateMessage(reply.at(m_spanish), MessageType::WrongAnswer);
        return;
    };

    //  Wrong answers
    if (lower != "")
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

        if (m_spanish)
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
    int rand = std::rand() % 40 + 1;

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
    auto GM = GameManager::sharedState();
    auto AM = AchievementManager::sharedState();
    //  log::debug("ID: {} - IDX: {}", ID, index);
    std::vector<std::string> messages;

    //  Odyssey
    if (ID == 11 && !AM->isAchievementEarned("geometry.ach.odyssey.secret01"))
    {
        messages = {
            "So...",
            "Look how far you've come",
            "You've went through molten lands",
            "Explored floating worlds",
            "And endured subzero temperatures",
            "Now, you've set forth on an...",
            "Uh..."
            "What was the word again?"};

        if (m_spanish)
            messages = {
                "Asi que...",
                "Haz llegado muy lejos",
                "Haz viajado por las tierras ardientes",
                "Exploraste el mundo con tus amigos",
                "Y tuviste el valor de pasar temperaturas bajo zero",
                "Ahora, parece que estas listo para una...",
                "uh...",
                "Cual era el titulo?",
            };

        if (!GM->getUGV("301"))
        {
            log::info("Hint for Secret 01 enabled");
            GM->setUGV("301", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Invaders
    if (ID == 12 && !AM->isAchievementEarned("geometry.ach.odyssey.secret02"))
    {
        messages = {
            "From the stars above they came forth",
            "From up there to below here",
            "From a far away place",
            "They possess many colors and forms",
            "One thing for sure...",
            "They are the space... uh...",
        };

        if (m_spanish)
            messages = {
                "Ellos vienen desde las estrellas",
                "Desde alla arriba hasta aqui abajo",
                "Desde un lugar muy lejano",
                "Cuentan con muchos colores y formas",
                "Pero solo una cosa es segura...",
                "Ellos son los Inva... hmm..",
                "Como se dice en ingles?",
            };

        if (!GM->getUGV("302"))
        {
            log::info("Hint for Secret 02 enabled");
            GM->setUGV("302", true);
        };

        if (index >= messages.size())
        {

            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Astral
    if (ID == 13 && !AM->isAchievementEarned("geometry.ach.odyssey.secret03"))
    {
        messages = {
            "That wretched beast...",
            "The killer of cosmos...",
            "The galactic eradicator...",
            "It's hunger never satisfied",
            "For only one thing it truthfully desires",
            "The phoenix from castle of jello",
            "Its greatest foe and sole threat",
            "I've forgotten that foul shellfish's name",
            "I wish I knew what it was again...",
        };

        if (m_spanish)
            messages = {
                "Esa abominable bestia...",
                "El asesino del cosmos...",
                "El erradicador galactico...",
                "Su hambre nunca se satisface",
                "Pues solo una cosa desea con sinceridad.",
                "El fenix del gran castillo esta en su contra.",
                "He olvidado el nombre de ese repugnante crustaceo...",
                "Ojala pudiera recordarlo...",
            };

        if (!GM->getUGV("303"))
        {
            log::info("Hint for Secret 03 enabled");
            GM->setUGV("303", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Dumbledalf
    if (ID == 14 && !AM->isAchievementEarned("geometry.ach.odyssey.secret04"))
    {
        messages = {
            "It's been a long time...",
            "Since anyone visited me",
            "This place has been empty for long",
            "Feels like a prison",
            "RubRub has forgotten us",
            "But sometimes, an old man comes around",
            "Funny clothes, white beard...",
            "And he always carries this colorful stone",
            "I wish I could remember his name...",
        };

        if (m_spanish)
            messages = {
                "Hace mucho tiempo...",
                "que nadie me visitaba.",
                "Este lugar ha estado vacio por mucho tiempo.",
                "Pareciera una prision.",
                "RubRub nos tiene olvidados.",
                "Pero a veces, un anciano venia.",
                "Ropa graciosa, barba blanca...",
                "y siempre estaba con su piedra de colores.",
                "Ojala pudiera recordar su nombre...",
            };

        if (!GM->getUGV("304"))
        {
            log::info("Hint for Secret 04 enabled");
            GM->setUGV("304", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Carp
    if (ID == 15 && !AM->isAchievementEarned("geometry.ach.odyssey.secret05"))
    {
        messages = {
            "Oh, yeah... I remember",
            "The old man isn't the only one...",
            "This pink guy would come too",
            "Oh... I hate him!",
            "Always getting in the way!",
            "Selling his junk!",
            "Thankfully, I forgot his name.",
        };

        if (m_spanish)
            messages = {
                "Ah si... ya recuerdo",
                "Ese viejo no era el único que venia aqui.",
                "Tambien venia aquel sujeto rosado.",
                "Como lo odio!",
                "Siempre estorbando!",
                "Vendiendo sus porquerias!",
                "Afortunadamente, Olvide su nombre.",
            };

        if (!GM->getUGV("305"))
        {
            log::info("Hint for Secret 05 enabled");
            GM->setUGV("305", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    /*
    //  Uncertain
    if (ID == 16 && !GameManager::sharedState()->getUGV("235"))
    {
        messages = {
            "Have you ever been sure of something?",
            "Sometimes I think about strange things",
            "There's a hidden level here...",
            "It makes me think about that stuff",
            "Its name, uncertain...",
        };

        if (m_spanish)
            messages = {
                "Alguna vez has estado seguro de algo?",
                "A veces pienso en cosas extranas",
                "Hay un nivel oculto aqui...",
                "me hace pensar en esas cosas",
                "Su nombre, uncertain...",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }
    */

    //  Colon
    if (ID == 17 && !AM->isAchievementEarned("geometry.ach.odyssey.secret06"))
    {
        messages = {
            "Riddle me this, riddle me that...",
            "I am a fox with many tails",
            "Afraid of arachnids and their many sharp turns",
            "They say I smell great, they love me even",
            "You better be hiding your gold well",
            "Else I will be ashamed of its ease...",
            "Who am I?",
        };

        if (m_spanish)
            messages = {
                "Adivina esto, adivina aquello...",
                "Soy un zorro con muchas colas",
                "Temeroso de los aracnidos y sus vueltas sin sentido",
                "Dicen que huelo genial, incluso me aman",
                "Sera mejor que escondas bien las 3 doradas",
                "De lo contrario, me avergonzare de lo facil de hallarlas",
            };

        if (!GM->getUGV("306"))
        {
            log::info("Hint for Secret 06 enabled");
            GM->setUGV("306", true);
        };
        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Rubrub
    if (ID == 18 && !AM->isAchievementEarned("geometry.ach.odyssey.secret07"))
    {
        messages = {
            "That evil, foolish ruler",
            "Taking eons to give to his land",
            "Locking us all here",
            "Betraying us for the sake of secrets",
            "And don't get me started",
            "How long it took him",
            "To give us... the legendary creation tools",
        };

        if (m_spanish)
            messages = {
                "Este malvado y necio gobernante",
                "Que toma eones para dar algo a su tierra",
                "Nos mantiene a todos encerrados aqui",
                "Traicionandonos por el bien de los secretos",
                "Y ni me hagas empezar",
                "Con lo mucho que se ha tardado",
                "En entregarnos las legendarias herramientas de creacion...",
            };

        if (!GM->getUGV("307"))
        {
            log::info("Hint for Secret 07 enabled");
            GM->setUGV("307", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Elemental
    if (ID == 19 && !AM->isAchievementEarned("geometry.ach.odyssey.secret08"))
    {
        messages = {
            "Without this, our world would be gone",
            "It's influence spreads around it",
            "It's the key to everything",
            "It even gave its name..."
            "To this whole odyssey",
            "Whatever that means, really",
            "I'm just reciting from this book I have",
        };

        if (m_spanish)
            messages = {
                "Sin esto, nuestro mundo desapareceria",
                "Su influencia se extiende a su alrededor",
                "Es la clave de todo",
                "Incluso le dio su nombre a toda esta odisea...",
                "Lo que sea que eso signifique, en realidad",
                "Solo estoy recitando de este libro que tengo",
            };

        if (!GM->getUGV("308"))
        {
            log::info("Hint for Secret 08 enabled");
            GM->setUGV("308", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Demon Gauntlet
    if (ID == 20 && !AM->isAchievementEarned("geometry.ach.odyssey.secret09"))
    {
        messages = {
            "So, you know a lot about keys",
            "That reminds me...",
            "There was one time...",
            "Someone released the demon guardian",
            "What a doozy...",
            "It did bring forth something else...",
            "A large, monstrous cave",
            "They say demons lurk there",
            "If you were to challenge it",
            "Be ready... to face hell"};

        if (m_spanish)
            messages = {
                "Asi que sabes mucho sobre llaves",
                "Eso me recuerda...",
                "Recuerdas aquella vez...",
                "Que alguien libero al Demon Guardian?",
                "Que ingenuo...",
                "Aunque trajo consigo algo mas...",
                "Una cueva grande y monstruosa.",
                "Dicen que los demonios acechan ahi,",
                "Esperando a que llegue un retador.",
                "Si tu fueras a desafiarlos",
                "Preparate para un Infierno",
            };

        if (!GM->getUGV("309"))
        {
            log::info("Hint for Secret 09 enabled");
            GM->setUGV("309", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Mono
    if (ID == 21 && !AM->isAchievementEarned("geometry.ach.odyssey.secret13"))
    {
        messages = {
            "My brother doesn't stop talking...",
            "About this gal...",
            "Weirdly shaped ribbon, black hair",
            "Other details I don't care",
            "Kept murmuring her name...",
            "Mono...?",
            "What kind of name even is Mono...?",
        };

        if (m_spanish)
            messages = {
                "Mi hermano no para de hablar...",
                "Sobre una mujer... Pelo oscuro...",
                "Cinta de pelo con forma rara...",
                "Otros detalles que no me importa",
                "No dejaba de susurrar su nombre",
                "Mono...?",
                "Quien rayos se hace llamar Mono?",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Comic fan
    if (ID == 22 && !AM->isAchievementEarned("geometry.ach.odyssey.secret19"))
    {
        messages = {
            "Wanna know something?",
            "I hid a secret reward in this game",
            "Here's a hint to get it...",
            "Stay up to date with the story",
            "The artists will appreciate it",
        };

        if (m_spanish)
            messages = {
                "Quieres saber algo?",
                "Escondi un logro secreto en el juego",
                "Te dare una pista como conseguirlo",
                "Estas al dia con la historia?",
                "Los artistas lo apreciarian mucho",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Programmer's secret
    if (ID == 23 && !AM->isAchievementEarned("geometry.ach.odyssey.secret20"))
    {
        messages = {
            "Alright, fine",
            "I hid another secret as well...",
            "Forgot where I put it, though",
            "Don't blame me, blame the programmer!",
            "One of the three..."};

        if (m_spanish)
            messages = {
                "Ok... Ok...",
                "Hay otro logro secreto.",
                "Se me olvido en donde esta",
                "No me culpes, culpa a los programadores!",
                "Uno de los tres...",
            };

        if (!GameManager::sharedState()->getUGV("209"))
            GameManager::sharedState()->setUGV("209", true);

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Gargan
    if (ID == 24 && GameManager::sharedState()->getUGV("232") && !AM->isAchievementEarned("geometry.ach.odyssey.secret21"))
    {
        messages = {
            "I miss my brother...",
            "He has some anger issues...",
            "Definitely when you mention his real name",
            "Last time it happened, the room was painted red",
            "Maybe you don't know who I'm talking about",
            "But he is a grumpy one",
            "Gargan",
            "What will become of you?"};

        if (m_spanish)
            messages = {
                "Echo de menos a mi hermano...",
                "Tiene algunos problemas de ira...",
                "Sin duda cuando mencionas su nombre real",
                "La ultima vez que paso, su cuarto se pinto de rojo",
                "Tal vez no sabes de quien estoy hablando",
                "Pero el es un malhumorado",
                "Gargan",
                "Que sera de ti?"};

        if (!GM->getUGV("323"))
        {
            log::info("Hint for Secret 23 enabled");
            GM->setUGV("323", true);
        };

        if (index >= messages.size())
        {
            if (!GameManager::sharedState()->getUGV("233"))
                GameManager::sharedState()->setUGV("233", true);

            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Sigma
    if (ID == 25 && !AM->isAchievementEarned("geometry.ach.odyssey.secret22"))
    {
        messages = {
            "I keep hearing these words...",
            "From the cubes that come by",
            "Rizz... Edge... Aura...",
            "What is as Ski Bee Dee?",
            "They also use Greek letters",
            "Alpha, Beta, Gamma...",
            "There's a specific one",
            "Said by a cube with X eyes...",
            "Perhaps you might know?"};

        if (m_spanish)
            messages = {
                "He escuchado estas palabras...",
                "De los cubos que visitan por aca",
                "Peak... Curi... Momos...",
                "Que es una papeada?",
                "Tambien usan letras Griegas",
                "Alfa, Beta, Gamma...",
                "Hay una en especifico",
                "Lo dice un cubo con ojos equis...",
                "Tal vez tu sabes cual es?"};

        if (!GM->getUGV("322"))
        {
            log::info("Hint for Secret 22 enabled");
            GM->setUGV("322", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Editor
    if (ID == 26 && !AM->isAchievementEarned("geometry.ach.odyssey.secret23"))
    {
        messages = {
            "From the simplest of looks...",
            "To full blown games",
            "Hundreds of tools and styles",
            "Thousands of ways...",
            "To plaster your ideas in this canvas...",
            "Make sure you read it's guide first"};

        if (m_spanish)
            messages = {
                "Desde aspectos muy sencillos...",
                "Hasta juegos completos",
                "Cientos de instrumentos y estilos",
                "Miles de maneras...",
                "Para plasmar tus ideas en este lienzo...",
                "Asegurate de leer la guia primero"};

        if (!GM->getUGV("323"))
        {
            log::info("Hint for Secret 23 enabled");
            GM->setUGV("323", true);
        };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Wanted!
    if (ID == 27 && !AM->isAchievementEarned("geometry.ach.odyssey.secret24"))
    {
        messages = {
            "I sadly remember another thing",
            "The pink guy boasts about...",
            "The decoration he puts in his shop",
            "Changing it every time when a client comes",
            "Waste of time",
            "Also something about...",
            "The good reward",
            "If you catch a cube of a peculiar shape"};

        if (m_spanish)
            messages = {
                "Por desgracia recuerdo otra cosa",
                "De la que presume el tipo rosa...",
                "La decoracion que pone en su tienda",
                "La cambia cada vez que viene un cliente",
                "Una perdida de tiempo",
                "Tambien algo sobre...",
                "Una buena recompensa",
                "Si atrapas un cubo de forma familiar"};

        if (!GM->getUGV("324"))
        {
            log::info("Hint for Secret 24 enabled");
            GM->setUGV("324", true);
        };

        if (index >= messages.size())
        {
            if (!GameManager::sharedState()->getUGV("239"))
                GameManager::sharedState()->setUGV("239", true);

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
        "Who am I kidding",
        "You're here to bug me",
        "You futile little pest",
        "It isn't the first time someone did that",
        "And it certainly won't be the last time",
        "If I could smash you with my mighty club",
        "It would be great",
        "But I've lost my hands years ago",
        "He took them away from me",
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
        "...",
        "......",
        "You're still here?",
        "You've been more patient than many",
        "Perhaps you're worthy of my time",
        "Just give me a moment",
        "I need to go to sleep",
        "Zzz...",
        "...",
        "......",
    };

    if (m_spanish)
        messages = {
            "Grough... ",
            "Quien se atreve a entrar en mi guarida? ",
            "Oh... solo eres un jugador.",
            "Que te trae aqui?",
            "Has venido a escuchar mis acertijos?",
            "Buscas rebelarte contra nuestro lider tambien?",
            "...",
            "......",
            "A quien voy a tomar el pelo",
            "Estas aqui para molestarme, verdad?",
            "Diminuta plaga inutil.",
            "No es la primera vez que alguien hace eso,",
            "y ciertamente no sera la ultima.",
            "Si pudiera aplastarte con mi poderoso garrote, seria grandioso",
            "Pero perdi mis manos...",
            "EL me las quito hace mucho tiempo,",
            "mas de lo que llevas vivo.",
            "Eso es seguro.",
            "Todo en nombre de los secretos...",
            "Cada vez que alguien viene aqui,",
            "solo me gritan cosas.",
            "Nunca me escuchan a mi ni a mis acertijos,",
            "y luego se van, enojados...",
            "Es algo en mi cara?",
            "No lo entiendo...",
            "...",
            "......",
            "Todavia estas aqui?",
            "Eres mas paciente que muchos.",
            "Tal vez mereces mi tiempo.",
            "Dame un momento,",
            "Necesito dormir.",
            "Zzz...",
            "...",
            "......",
        };

    log::debug("Index: {}", m_randomMessageIDX);
    if (m_randomMessageIDX < messages.size() - 1)
        m_randomMessageIDX++;
    else
        m_randomMessageIDX = 0;

    return (messages[m_randomMessageIDX]);
};

void SecretVaultLayer2::updateMessage(std::string message, MessageType type)
{
    m_response->setString(message.c_str());
    m_response->limitLabelWidth(320, 0.6f, 0.6f);
    //  log::debug("TYPE {}", (int)type);

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
        m_messageID = 99;
        m_messageIDX = 0;
        break;

    case MessageType::CorrectAnswer:
        m_response->setColor({102, 255, 255});
        m_messageID = 99;
        m_messageIDX = 0;
        break;
    }
};

void SecretVaultLayer2::keyBackClicked()
{
    GameManager::sharedState()->fadeInMusic("IslandLoop02.mp3"_spr);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, OdysseySelectLayer::scene(1)));
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
