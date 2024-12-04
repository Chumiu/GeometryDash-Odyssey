#include "Utils.hpp"

void Odyssey::addCorners(CCLayer *layer, const char *cornerSprite, float offset)
{
    //  Corners
    auto m_cornerBL = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerBL->setAnchorPoint({0, 0});
    m_cornerBL->setPosition({0 - offset, 0 - offset});
    m_cornerBL->setID("corner-bl"_spr);

    auto m_cornerBR = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerBR->setPosition({layer->getContentWidth() + offset, 0 - offset});
    m_cornerBR->setAnchorPoint({1, 0});
    m_cornerBR->setFlipX(true);
    m_cornerBR->setID("corner-br"_spr);

    auto m_cornerTL = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerTL->setAnchorPoint({0, 1});
    m_cornerTL->setPosition({0 - offset, layer->getContentHeight() + offset});
    m_cornerTL->setFlipY(true);
    m_cornerTL->setID("corner-tl"_spr);

    auto m_cornerTR = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerTR->setPosition({layer->getContentWidth() + offset, layer->getContentHeight() + offset});
    m_cornerTR->setAnchorPoint({1, 1});
    m_cornerTR->setFlipX(true);
    m_cornerTR->setFlipY(true);
    m_cornerTR->setID("corner-tr"_spr);

    layer->addChild(m_cornerBL);
    layer->addChild(m_cornerBR);
    layer->addChild(m_cornerTL);
    layer->addChild(m_cornerTR);
};

CCNode *Odyssey::createProgressBar(int percentage, bool isPractice)
{
    auto node = CCNode::create();

    int rgbValue = isPractice ? 255 : 0;
    ccColor3B color = {0, 255, (GLubyte)rgbValue};

    auto bgBar = CCSprite::create("GJ_progressBar_001.png");
    bgBar->setColor({0, 0, 0});
    bgBar->setOpacity(100);
    bgBar->setScale(0.9f);
    bgBar->setZOrder(1);

    node->addChild(bgBar);

    auto progressBar = CCSprite::create("GJ_progressBar_001.png");
    auto rectX = (progressBar->getContentWidth() * percentage) / 100;
    progressBar->setTextureRect({0, .5f, rectX, progressBar->getContentHeight()});
    progressBar->setScaleX(0.89f);
    progressBar->setScaleY(0.75f);
    progressBar->setColor(color);
    progressBar->setZOrder(2);

    progressBar->setAnchorPoint({0, 0.5});
    progressBar->setPositionX(-151.3f);

    node->addChild(progressBar);

    std::string progressNumber = std::to_string(percentage);
    auto progressLabel = CCLabelBMFont::create(fmt::format("{}%", progressNumber).c_str(), "bigFont.fnt");
    progressLabel->setPositionY(0.5f);
    progressLabel->setScale(0.325f);
    progressLabel->setZOrder(3);

    node->addChild(progressLabel);

    const char *mode = isPractice ? "Practice Mode" : "Normal Mode";
    auto label = CCLabelBMFont::create(mode, "bigFont.fnt");
    label->setPositionY(18.0f);
    label->setScale(0.45f);
    node->addChild(label);

    return node;
};

CCNode *Odyssey::createDifficultyNode(GJDifficulty diff, int stars)
{
    auto node = CCNode::create();
    node->setContentSize({20.f, 32.5f});

    std::string difficultyName = fmt::format("diffIcon_{:02}_btn_001.png", static_cast<int>(diff));
    auto diffSprite = CCSprite::createWithSpriteFrameName(difficultyName.c_str());
    diffSprite->setPosition({node->getContentWidth() / 2, node->getContentHeight()});
    diffSprite->setScale(1.25f);

    auto starLabel = CCLabelBMFont::create(std::to_string(stars).c_str(), "bigFont.fnt");
    starLabel->limitLabelWidth(10, 0.6f, 0.1f);
    starLabel->setPosition({0, 0});

    auto starSprite = CCSprite::createWithSpriteFrameName("GJ_bigStar_noShadow_001.png");
    starSprite->setPosition({node->getContentWidth(), 0});
    starSprite->setScale(0.5f);

    node->addChild(diffSprite);
    node->addChild(starSprite);
    node->addChild(starLabel);
    return node;
};

DialogLayer *Odyssey::createDialog(const char *event)
{
    CCArray *arr = CCArray::create();

    //  SOLAMENTE REEMPLAZA ESTA LINEA CUANDO YA TENGAMOS EL SETTING MEJORADO
    auto spanishText = Mod::get()->getSettingValue<bool>("spanish-language");

    if (event == "shopIntroduction")
    {
        if (!spanishText)
        {
            auto dialog_01 = DialogObject::create("????", "Uh, <d020>hello...", 25, 1, false, {255, 255, 255});
            auto dialog_02 = DialogObject::create("????", "Wait<d010>.<d010>.<d010>.", 24, 1, false, {255, 255, 255});
            auto dialog_03 = DialogObject::create("????", "<s250>WAIT!</s>", 20, 1, false, {255, 255, 255});
            auto dialog_04 = DialogObject::create("????", "A <cg>customer</c>! <d020>No way,<d020> a real <cg>customer</c>!<d020> I thought no one would ever come here!", 20, 1, false, {255, 255, 255});
            auto dialog_05 = DialogObject::create("????", "My name is <cp>Carp</c>,<d020> I am the shopkeeper of <cb>The Dangerous Zones</c>.", 21, 1, false, {255, 255, 255});
            auto dialog_06 = DialogObject::create("Carp", "Why do I live here?<d020> Well,<d020> let's just say I found out <cr>something I shouldn't have</c><d010>.<d010>.<d010>.", 22, 1, false, {255, 255, 255});
            auto dialog_07 = DialogObject::create("Carp", "Don't check <cy>RubRub's</c> computer search history...", 23, 1, false, {255, 255, 255});
            auto dialog_08 = DialogObject::create("Carp", "As a punishment,<d020> I was removed from the community shop and sent here.", 22, 1, false, {255, 255, 255});
            auto dialog_09 = DialogObject::create("Carp", "I have a lot of stuff to sell!<d020> So if you need anything you can get it here!", 20, 1, false, {255, 255, 255});
            auto dialog_10 = DialogObject::create("Carp", "Or not<d010>.<d010>.<d010>.", 19, 1, false, {255, 255, 255});

            arr->addObject(dialog_01);
            arr->addObject(dialog_02);
            arr->addObject(dialog_03);
            arr->addObject(dialog_04);
            arr->addObject(dialog_05);
            arr->addObject(dialog_06);
            arr->addObject(dialog_07);
            arr->addObject(dialog_08);
            arr->addObject(dialog_09);
            arr->addObject(dialog_10);
        }
        else
        {
            auto dialog_01 = DialogObject::create("????", "Uh, hola...", 25, 1, false, {255, 255, 255});
            auto dialog_02 = DialogObject::create("????", "Espera<d010>.<d010>.<d010>.", 24, 1, false, {255, 255, 255});
            auto dialog_03 = DialogObject::create("????", "<s250>ESPERA!</s>", 20, 1, false, {255, 255, 255});
            auto dialog_04 = DialogObject::create("????", "Un <cg>cliente!</c><d020> No puede ser, es un cliente!<d020> Crei que nadie llegaria aqui jamas.", 20, 1, false, {255, 255, 255});
            auto dialog_05 = DialogObject::create("????", "Me llamo <cp>Carp</c>, soy el shopkeeper de <cb>The Dangerous Zones</c>.", 21, 1, false, {255, 255, 255});
            auto dialog_06 = DialogObject::create("Carp", "Por que vivo aqui?<d020> Bien,<d020> digamos que me entere de <cr>algo que no debi</c><d010>.<d010>.<d010>.", 22, 1, false, {255, 255, 255});
            auto dialog_07 = DialogObject::create("Carp", "No revises el historial de busqueda de la computadora de <cy>RubRub</c>.", 23, 1, false, {255, 255, 255});
            auto dialog_08 = DialogObject::create("Carp", "Como castigo,<d020> me retiraron de la tienda comunitaria y me enviaron aqui.", 22, 1, false, {255, 255, 255});
            auto dialog_09 = DialogObject::create("Carp", "¡Tengo muchas cosas para vender!<d020> Asi que si necesitas algo puedes conseguirlo aqui!", 20, 1, false, {255, 255, 255});
            auto dialog_10 = DialogObject::create("Carp", "O no<d010>.<d010>.<d010>.", 19, 1, false, {255, 255, 255});

            arr->addObject(dialog_01);
            arr->addObject(dialog_02);
            arr->addObject(dialog_03);
            arr->addObject(dialog_04);
            arr->addObject(dialog_05);
            arr->addObject(dialog_06);
            arr->addObject(dialog_07);
            arr->addObject(dialog_08);
            arr->addObject(dialog_09);
            arr->addObject(dialog_10);
        }
    }

    if (event == "wizardIntroduction")
    {
        if (!spanishText)
        {
            auto dialog_01 = DialogObject::create("Dumbledalf", "Hello there!<d040> Before you begin, <d020>I want to let you know something.", 56, 1, false, {255, 255, 255});
            auto dialog_02 = DialogObject::create("Dumbledalf", "To get the <cy>full experience</c> of the game, <d020>I'd recommend to check out the <cg>comics</c>.", 56, 1, false, {255, 255, 255});
            auto dialog_03 = DialogObject::create("Dumbledalf", "These can be read from the Menu of each level, <d020>don't forget to look at them before playing!", 56, 1, false, {255, 255, 255});
            auto dialog_04 = DialogObject::create("Dumbledalf", "Alright, <d020>I'll stop breaking the fourth wall and go back to <co>the bunker</c><d010>.<d010>.<d010>.", 53, 1, false, {255, 255, 255});
            auto dialog_05 = DialogObject::create("Dumbledalf", "Oh, whoops... <d030>I might said too much<d010>.<d010>.<d010>.", 54, 1, false, {255, 255, 255});
            auto dialog_06 = DialogObject::create("Dumbledalf", "<s250><cy>Goodbye boy</c>!</s>", 55, 1, false, {255, 255, 255});

            arr->addObject(dialog_01);
            arr->addObject(dialog_02);
            arr->addObject(dialog_03);
            arr->addObject(dialog_04);
            arr->addObject(dialog_05);
            arr->addObject(dialog_06);
        }
        else
        {
            //  To do
        }
    }

    if (event == "wizardIslandComplete")
    {
        if (!spanishText)
        {

            auto dialog_01 = DialogObject::create("Dumbledalf", "<s250><co>WOW,<d020> such skill!</c></s>", 55, 1, false, {255, 255, 255});
            auto dialog_02 = DialogObject::create("Dumbledalf", "You have played these kinds of <cg>games</c> before, <d020>don't cha?", 56, 1, false, {255, 255, 255});
            auto dialog_03 = DialogObject::create("Dumbledalf", "Well, <d020>let's venture to the <cb>next island</c>, <d020>boy.", 56, 1, false, {255, 255, 255});
            auto dialog_04 = DialogObject::create("Dumbledalf", "<cg>The jungle of echoes</c> awaits us<d010>.<d010>.<d010>.", 53, 1, false, {255, 255, 255});

            arr->addObject(dialog_01);
            arr->addObject(dialog_02);
            arr->addObject(dialog_03);
            arr->addObject(dialog_04);
        }
        else
        {
            //  To do
        }
    }

    if (event == "wizardEnding")
    {
        if (!spanishText)
        {
            auto dialog_01 = DialogObject::create("Dumbledalf", "Hey <cy>Buddy</c>! You finished all the levels!", 56, 1, false, {255, 255, 255});
            auto dialog_02 = DialogObject::create("Dumbledalf", "Amazing work! <d020>we'll continue our adventure in the next <cg>update</c>.", 53, 1, false, {255, 255, 255});
            auto dialog_03 = DialogObject::create("Dumbledalf", "But while we wait, <d030>you can go and try getting all the <cy>secret coins</c><d010>.<d010>.<d010>.", 56, 1, false, {255, 255, 255});
            auto dialog_04 = DialogObject::create("Dumbledalf", "Maybe you can also discover some more <cr>secrets</c><d010>.<d010>.<d010>.", 56, 1, false, {255, 255, 255});
            auto dialog_05 = DialogObject::create("Dumbledalf", "Or challenge yourself with the <co>extra levels</c>!", 53, 1, false, {255, 255, 255});
            auto dialog_06 = DialogObject::create("Dumbledalf", "Up to you my buddy, <d020>we will meet again!", 56, 1, false, {255, 255, 255});
            auto dialog_07 = DialogObject::create("Dumbledalf", "<cg>Thank you for playing!</c>", 55, 1, false, {255, 255, 255});

            arr->addObject(dialog_01);
            arr->addObject(dialog_02);
            arr->addObject(dialog_03);
            arr->addObject(dialog_04);
            arr->addObject(dialog_05);
            arr->addObject(dialog_06);
            arr->addObject(dialog_07);
        }
        else
        {
            //  To do
        }
    }

    if (event == "blockedAccess")
    {
        if (!spanishText)
        {

            auto dialog_01 = DialogObject::create("Dumbledalf", "<s250>YOU SHALL NOT PASS</s>", 55, 1, false, {255, 255, 255});
            auto dialog_02 = DialogObject::create("Dumbledalf", "I'm sorry,<d010> <cy>Player...</c>", 56, 1, false, {255, 255, 255});
            auto dialog_03 = DialogObject::create("Dumbledalf", "You have to <cr>disable</c> the Mod to have access...", 56, 1, false, {255, 255, 255});
            auto dialog_04 = DialogObject::create("Dumbledalf", "Safety measures,<d020> ya know?", 53, 1, false, {255, 255, 255});

            arr->addObject(dialog_01);
            arr->addObject(dialog_02);
            arr->addObject(dialog_03);
            arr->addObject(dialog_04);
        }
        else
        {
            auto dialog_01 = DialogObject::create("Dumbledalf", "<s250>QUIETO AHI, CHAMACO.</s>", 55, 1, false, {255, 255, 255});
            auto dialog_02 = DialogObject::create("Dumbledalf", "Mis disculpas, <d020><cy>Jugador...</c>", 56, 1, false, {255, 255, 255});
            auto dialog_03 = DialogObject::create("Dumbledalf", "Tendras que <cr>deshabilitar</c> el mod para acceder al resto del juego.", 56, 1, false, {255, 255, 255});
            auto dialog_04 = DialogObject::create("Dumbledalf", "Medidas de seguridad, <d020>sabes?", 53, 1, false, {255, 255, 255});

            arr->addObject(dialog_01);
            arr->addObject(dialog_02);
            arr->addObject(dialog_03);
            arr->addObject(dialog_04);
        }
    }

    auto dialogLayer = DialogLayer::createDialogLayer(nullptr, arr, 2);
    dialogLayer->animateInRandomSide();
    dialogLayer->setZOrder(2);

    return dialogLayer;
};

DialogLayer *Odyssey::createDialogResponse(const char *event, int times)
{
    auto spanishText = Mod::get()->getSettingValue<bool>("spanish-language");
    CCArray *arr = CCArray::create();
    if (event == "playerIsPoor")
    {
        if (!spanishText)
        {
            auto dialog01 = DialogObject::create("Carp", "Here's your purcha-<d020> wait a second.", 20, 1, false, {255, 255, 255});
            auto dialog02 = DialogObject::create("Carp", "Sorry,<d030> you don't have enough <cy>coins</c>.", 21, 1, false, {255, 255, 255});
            auto dialog03 = DialogObject::create("Carp", "Are you trying to scam me?", 22, 1, false, {255, 255, 255});
            auto dialog04 = DialogObject::create("Carp", "I might be blind,<d030> but I'm sure you don't have <cy>enough</c> to <cg>buy</c> this.", 25, 1, false, {255, 255, 255});

            switch (times)
            {
            case 0:
                arr->addObject(dialog01);
                arr->addObject(dialog02);
                break;

            case 1:
                arr->addObject(dialog03);
                break;

            case 2:
                arr->addObject(dialog04);
                break;
            }
        }
        else
        {
            // To Do
        }
    }

    if (event == "extraIslandLocked")
    {
        if (!spanishText)
        {
            auto dialog01 = DialogObject::create("Carp", "You can buy the key to unlock that in my <cy>Shop</c>.", 25, 1, false, {255, 255, 255});
            auto dialog02 = DialogObject::create("Carp", "Yep,<d030> you still need to <cg>buy</c> it.", 20, 1, false, {255, 255, 255});
            auto dialog03 = DialogObject::create("Carp", "Go grind some stuff to <cg>buy</c> this!", 23, 1, false, {255, 255, 255});

            switch (times)
            {
            case 0:
                arr->addObject(dialog01);
                break;

            case 1:
                arr->addObject(dialog02);
                break;

            case 2:
                arr->addObject(dialog03);
                break;
            }
        }
        else
        {
            // To Do
        }
    }

    if (event == "finalComicLocked")
    {
        if (!spanishText)
        {
            auto dialog01 = DialogObject::create("Carp", "You must <cg>complete</c> the story mode before showing you that.", 19, 1, false, {255, 255, 255});
            auto dialog02 = DialogObject::create("Carp", "Try to <cg>complete</c> the game first.", 21, 1, false, {255, 255, 255});
            auto dialog03 = DialogObject::create("Carp", "Someone's impatient<d010>.<d010>.<d010>.", 22, 1, false, {255, 255, 255});
            auto dialog04 = DialogObject::create("Carp", "Alright man,<d020> you want to <cr>spoil</c> you the story?", 25, 1, false, {255, 255, 255});
            auto dialog05 = DialogObject::create("Carp", "You are getting on my nerves,<d020> <cg>complete the game</c>!", 21, 1, false, {255, 255, 255});
            auto dialog06 = DialogObject::create("Carp", "<s500><cg>COMPLETE THE GAME.</c></s>", 26, 1, false, {255, 255, 255});

            switch (times)
            {
            case 0:
                arr->addObject(dialog01);
                break;

            case 1:
                arr->addObject(dialog02);
                break;

            case 2:
                arr->addObject(dialog03);
                break;

            case 3:
                arr->addObject(dialog04);
                break;

            case 4:
                arr->addObject(dialog05);
                break;

            case 5:
                arr->addObject(dialog06);
                break;
            }
        }
        else
        {
            // To Do
        }
    }

    auto dialogLayer = DialogLayer::createDialogLayer(nullptr, arr, 2);
    dialogLayer->animateInRandomSide();
    dialogLayer->setZOrder(2);
    return dialogLayer;
}

int Odyssey::currentVehicleID()
{
    auto gm = GameManager::get();
    switch (gm->m_playerIconType)
    {
    case IconType::Ship:
        return gm->getPlayerShip();
    case IconType::Ball:
        return gm->getPlayerBall();
    case IconType::Ufo:
        return gm->getPlayerBird();
    case IconType::Wave:
        return gm->getPlayerDart();
    case IconType::Robot:
        return gm->getPlayerRobot();
    case IconType::Spider:
        return gm->getPlayerSpider();
    case IconType::Swing:
        return gm->getPlayerSwing();
    case IconType::Jetpack:
        return gm->getPlayerJetpack();
    default:
        return gm->getPlayerFrame();
    }
}

void Odyssey::insertAssetsToMap(bool isSong, std::vector<int> IDs)
{
    auto map = MusicDownloadManager::sharedState()->m_resourceSfxUnorderedSet;

    for (int assetID : IDs)
    {
        if (isSong)
            MusicDownloadManager::sharedState()->m_resourceSongUnorderedSet.insert(assetID);
        else
            MusicDownloadManager::sharedState()->m_resourceSfxUnorderedSet.insert(assetID);
    }
}

bool Odyssey::isCustomIcon(int id, IconType type)
{
    if (id > 485 && type == IconType::Cube)
        return true;
    if (id > 169 && type == IconType::Ship)
        return true;
    if (id > 118 && type == IconType::Ball)
        return true;
    if (id > 96 && type == IconType::Wave)
        return true;
    if (id > 43 && type == IconType::Swing)
        return true;
     if (static_cast<int>(type) >= 900)
        return true;

    return false;
}

std::vector<std::string> Odyssey::getPlayerFrames(int iconID, IconType type)
{
    std::string iconName;
    switch (type)
    {
    case IconType::Ship:
        iconName = "ship";
        break;
    case IconType::Ball: 
        iconName = "player_ball"; 
        break;
    case IconType::Wave:
        iconName = "dart";
        break;
    case IconType::Swing:
        iconName = "swing";
        break;
    default:
        iconName = "player";
        break;
    }

    int typeNumber = static_cast<int>(type);

    switch (typeNumber)
    {
    case 900:
        iconName = "boat";    
        break;
    case 901:
        iconName = "drone";    
        break;
    case 902:
        iconName = "slider";    
        break;
    case 903:
        iconName = "minecart";    
        break;
    }

    if (typeNumber >= 900) iconID = 1;

    std::string frame1 = fmt::format("{}_{:02}_001.png"_spr, iconName, iconID);
    std::string frame2 = fmt::format("{}_{:02}_2_001.png"_spr, iconName, iconID);
    std::string frameExtra = fmt::format("{}_{:02}_extra_001.png"_spr, iconName, iconID);
    std::string frameGlow = fmt::format("{}_{:02}_glow_001.png"_spr, iconName, iconID);

    return {frame1, frame2, frameExtra, frameGlow};
}

void Odyssey::updateIcon(CCNode* player, int iconID, IconType type, bool isPlayerObject)
{
    


    if (!isCustomIcon(iconID, type)) return;

    auto frameCache = CCSpriteFrameCache::get();

    auto frames = getPlayerFrames(iconID, type);
    auto frame1Texture = frames[0];
    auto frame2Texture = frames[1];
    auto extraTexture = frames[2];
    auto glowTexture = frames[3];

    CCSprite* firstLayer;
    CCSprite* secondLayer;
    CCSprite* extraLayer;
    CCSprite* glowLayer;

    if (isPlayerObject)
    {
        auto obj = static_cast<PlayerObject*>(player);

        firstLayer = obj->m_iconSprite;
        secondLayer = obj->m_iconSpriteSecondary;
        extraLayer = obj->m_iconSpriteWhitener;
        glowLayer =  obj->m_iconGlow;

        if (type == IconType::Ship)
        {
            firstLayer = obj->m_vehicleSprite;
            secondLayer = obj->m_vehicleSpriteSecondary;
            extraLayer = obj->m_vehicleSpriteWhitener;
            glowLayer = obj->m_vehicleGlow;
        }
    }
    else
    {
        auto obj = static_cast<SimplePlayer*>(player);
        
        firstLayer = obj->m_firstLayer;
        secondLayer = obj->m_secondLayer;
        extraLayer = obj->m_detailSprite;
        glowLayer = obj->m_outlineSprite;


    }

    if (auto frame1 = frameCache->spriteFrameByName(frame1Texture.c_str()))
    {
        firstLayer->setDisplayFrame(frame1);
    }

    if (auto frame2 = frameCache->spriteFrameByName(frame2Texture.c_str()))
    {
        secondLayer->setDisplayFrame(frame2);
        secondLayer->setPosition(firstLayer->getContentSize() / 2);
    }

    if (auto extraFrame = frameCache->spriteFrameByName(extraTexture.c_str()))
    {
        extraLayer->setVisible(true);
        extraLayer->setDisplayFrame(extraFrame);
        extraLayer->setPosition(firstLayer->getContentSize() / 2);
    }

    if (auto glowFrame = frameCache->spriteFrameByName(glowTexture.c_str()))
    {
        glowLayer->setDisplayFrame(glowFrame);
        if (!isPlayerObject) glowLayer->setPosition(firstLayer->getContentSize() / 2);
    }
}

void Odyssey::addCreditsToIcon(std::pair<int, UnlockType> pair, int accountID)
{
    GameStatsManager::sharedState()->m_accountIDForIcon.insert(std::make_pair(pair, accountID));
}

int Odyssey::islandPageForLevelID(int levelID)
{
    if (levelID < 5) return 0;

    if (levelID > 200) return 2;

    return 1;
}