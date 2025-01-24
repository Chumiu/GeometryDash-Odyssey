#include "OdysseyLevelPopup.hpp"
#include "../layers/ComicLayer.hpp"
#include "../utils/Utils.hpp"

bool OdysseyLevelPopup::setup(std::string const &title)
{
    //  El Nivel
    m_level = GameLevelManager::get()->getMainLevel(m_levelID, true);
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto contentSize = m_mainLayer->getContentSize();

    //  Titulo
    setTitle(m_level->m_levelName);
    m_title->limitLabelWidth(200, .85f, .1f);
    m_title->setPositionY(m_title->getPositionY() - 5.0f);
    m_title->setID("level-name-label");

    //  Boton de Cerrar
    m_closeBtn->setPosition(m_closeBtn->getPositionX() + 5, m_closeBtn->getPositionY() - 5);

    //  Esquinas del Layer
    Odyssey::addCorners(m_mainLayer, "dailyLevelCorner_001.png", 0);

    //  La cara de Dificultad
    auto difficultyNode = Odyssey::createDifficultyNode(m_level->m_difficulty, m_level->m_stars, m_level->m_normalPercent == 100);
    difficultyNode->setPosition({contentSize.width / 5, contentSize.height / 2 + 35});
    difficultyNode->setAnchorPoint({0.5f, 0.5f});
    difficultyNode->setID("difficulty-node");
    m_mainLayer->addChild(difficultyNode);

    //  Barra de progreso en Normal
    auto normalProgress = Odyssey::createProgressBar(m_level->m_normalPercent, false);
    normalProgress->setPosition({contentSize.width / 2, contentSize.height / 2 - 45.0f});
    normalProgress->setID("normal-progress-node");
    m_mainLayer->addChild(normalProgress);

    //  Barra de progreso en Practica
    auto practiceProgress = Odyssey::createProgressBar(m_level->m_practicePercent, true);
    practiceProgress->setPosition({contentSize.width / 2, normalProgress->getPositionY() - 40.0f});
    practiceProgress->setID("practice-progress-node");
    m_mainLayer->addChild(practiceProgress);

    //  Menu de Botones
    auto buttonsMenu = CCMenu::create();
    buttonsMenu->setContentSize(m_mainLayer->getContentSize());
    buttonsMenu->setID("buttons-menu");
    buttonsMenu->setPosition({0, 0});
    m_mainLayer->addChild(buttonsMenu);

    //  Play Button
    auto playButton = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png"),
        this,
        menu_selector(OdysseyLevelPopup::onPlay));
    playButton->setPosition({buttonsMenu->getContentWidth() / 2, buttonsMenu->getContentHeight() / 2 + 40.f});
    playButton->setID("play-button"_spr);

    //  Level stats
    std::string levelName = static_cast<gd::string>(m_level->m_levelName);
    std::string levelInfo = "<cy>" + levelName + "</c>" + "\n<cg>Total Attempts</c>: " + std::to_string(m_level->m_attempts) + "\n<cl>Total Jumps</c>: " + std::to_string(m_level->m_jumps) + "\n<cp>Normal</c>: " + std::to_string(m_level->m_normalPercent) + "%" + "\n<co>Practice</c>: " + std::to_string(m_level->m_practicePercent) + "%";

    //  Info Button
    auto infoButton = InfoAlertButton::create("Level Stats", levelInfo, 1);
    infoButton->setPosition({buttonsMenu->getContentWidth() - 20.f, buttonsMenu->getContentHeight() - 20.f});

    //  Options Button
    auto isSongDownloaded = MusicDownloadManager::sharedState()->isSongDownloaded(Odyssey::getLevelSongID(m_levelID));
    auto baseColor_1 = isSongDownloaded ? CircleBaseColor::Green : CircleBaseColor::Cyan;

    auto optionsSprite = CircleButtonSprite::createWithSpriteFrameName("GDO_SettingsIcon_001.png"_spr, 1.2, baseColor_1, CircleBaseSize::Small);
    //  optionsSprite->setScale(.8f);

    auto optionsButton = CCMenuItemSpriteExtra::create(
        optionsSprite,
        this,
        menu_selector(OdysseyLevelPopup::onSettings));
    optionsButton->setPosition({8, 8});

    //  Hint para descargar la cancion
    if (!MusicDownloadManager::sharedState()->isSongDownloaded(Odyssey::getLevelSongID(m_levelID)))
    {
        auto hint = CCSprite::createWithSpriteFrameName("GDO_AudioHint_001.png"_spr);
        hint->setPosition({-40, 30});
        m_mainLayer->addChild(hint);

        optionsButton->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(
            CCEaseSineOut::create(CCScaleTo::create(0.5f, 1.5)),
            CCEaseSineIn::create(CCScaleTo::create(0.5f, 1)))));
    }

    //  Para indicar que el jugador revise el comic o no
    auto seenComic = GameManager::sharedState()->getUGV(fmt::format("2{}", m_levelID + 11 - 7000).c_str());
    auto baseColor_2 = seenComic ? CircleBaseColor::Green : CircleBaseColor::Cyan;

    //  Comics Button
    auto comicButton = CCMenuItemSpriteExtra::create(
        CircleButtonSprite::createWithSpriteFrameName("GDO_ComicIcon_001.png"_spr, 1, baseColor_2, CircleBaseSize::Small),
        this,
        menu_selector(OdysseyLevelPopup::onComic));
    comicButton->setPosition({buttonsMenu->getContentWidth() - 8, 8});

    //  Si el jugador no ha visto el comic, anima el boton
    if (!seenComic)
    {
        comicButton->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(
            CCEaseSineOut::create(CCScaleTo::create(0.5f, 1.5)),
            CCEaseSineIn::create(CCScaleTo::create(0.5f, 1)))));
    }

    //  Para niveles que no tienen comic, se crea un boton de "Lore"
    auto loreSprite = CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png");
    loreSprite->setScale(0.8f);

    auto loreButton = CCMenuItemSpriteExtra::create(
        loreSprite,
        this,
        menu_selector(OdysseyLevelPopup::onLore));
    loreButton->setPosition({buttonsMenu->getContentWidth() - 8, 8});
    loreButton->setVisible(false);

    //  Adding the buttons
    buttonsMenu->addChild(playButton);
    buttonsMenu->addChild(infoButton);
    buttonsMenu->addChild(optionsButton);
    buttonsMenu->addChild(comicButton);
    buttonsMenu->addChild(loreButton);

    if (m_levelID > 7500)
        comicButton->setVisible(false);

    if (m_levelID > 7500 && m_levelID < 7600)
        loreButton->setVisible(true);

    //  Array de los coins coleccionados del Nivel
    auto coinMenu = CCMenu::create();
    auto coinArray = CCArray::create();
    coinMenu->setContentSize({40.0f, 25.f});

    for (int i = 0; i < 3; i++)
    {
        bool isCollected = GameStatsManager::sharedState()->hasSecretCoin(fmt::format("{}_{}", m_level->m_levelID.value(), i + 1).c_str());
        auto node = CCSprite::createWithSpriteFrameName(isCollected ? "GJ_coinsIcon_001.png" : "GJ_coinsIcon_gray_001.png");
        node->setScale(0.8f);

        coinArray->addObject(node);
        coinMenu->addChild(node);
    };

    coinMenu->setPosition(m_mainLayer->getContentWidth() / 2, 20.f);
    GameToolbox::alignItemsHorisontally(coinArray, 12.f, {0, 0}, false);
    m_mainLayer->addChild(coinMenu);

    /*
    //  Para descargar los assets de Audio y SFX (Texto)
    auto label = CCLabelBMFont::create("Download Assets", "goldFont.fnt");
    label->setScale(0.8f);

    auto audioBtn = CCMenuItemSpriteExtra::create(
        label,
        this,
        menu_selector(OdysseyLevelPopup::onAudio));

    audioBtn->setPosition({contentSize.width / 2, -10});
    audioBtn->setID("download-audio-btn");
    buttonsMenu->addChild(audioBtn);

    //  Flecha para esconder el Widget
    auto arrowSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    arrowSprite->setRotation(90);
    arrowSprite->setScale(0.5f);

    auto arrowBtn = CCMenuItemSpriteExtra::create(
        arrowSprite,
        this,
        menu_selector(OdysseyLevelPopup::onHideAudio));

    arrowBtn->setPosition(contentSize.width / 2, 0);
    arrowBtn->setID("hide-song-button");
    arrowBtn->setVisible(false);
    arrowBtn->setOpacity(0);
    buttonsMenu->addChild(arrowBtn);

    //  Crea el CustomSongWidget
    auto songID = Odyssey::getLevelSongID(m_levelID);
    auto assets = Odyssey::getLevelAudioAssets(m_levelID);

    log::debug("LEVEL ID: {}", m_levelID);
    log::debug("SONG ID: {}", songID);

    auto songObject = SongInfoObject::create(songID);
    m_audioWidget = CustomSongWidget::create(songObject, 0, 0, 0, 1, 0, 0, 1, 0);
    m_audioWidget->updateWithMultiAssets(assets.first, assets.second, 0);
    m_audioWidget->setID("song-widget");

    //  Extiende el BG del widget por si acaso
    auto bg = m_audioWidget->getChildByID("bg");
    bg->setAnchorPoint({0.5, 1});
    bg->setContentHeight(100);
    bg->setPositionY(25.f);

    auto textLabel = m_audioWidget->getChildByID("id-and-size-label");
    textLabel->setPositionY(textLabel->getPositionY());

    auto downloadBtn = m_audioWidget->getChildByIDRecursive("download-button");
    downloadBtn->setPositionX(-170.f);

    auto cancelBtn = m_audioWidget->getChildByIDRecursive("cancel-button");
    cancelBtn->setPositionX(-170.f);

    auto songLabel = static_cast<CCLabelBMFont *>(m_audioWidget->getChildByID("song-name-label"));
    songLabel->setCString(LevelTools::getAudioTitle(m_level->m_audioTrack).c_str());

    m_audioWidget->getSongInfoIfUnloaded();

    m_audioWidget->setPosition(winSize.width / 2, -30);
    this->addChild(m_audioWidget);
    */

    return true;
};

void OdysseyLevelPopup::onPlay(CCObject *sender)
{
    auto button = static_cast<CCMenuItemSpriteExtra *>(sender);
    auto spanish = GameManager::sharedState()->getGameVariable("0201");

    if (!MusicDownloadManager::sharedState()->isSongDownloaded(Odyssey::getLevelSongID(m_levelID)))
    {
        auto popup = createQuickPopup(
            "No Audio",
            spanish ? "El nivel tiene <cj>Assets de audio</c> que no ha sido <cg>descargado</c> aun. Descargalos primero antes de jugar. <cy>Se encuentran en las opciones del nivel</c> (Abajo a la Izquierda)." : "The level has <cj>Audio Assets</c> that has not been <cg>downloaded</c> yet. Please download them first before playing. <cy>They're located on the level options</c> (Bottom Left).",
            spanish ? "Volver" : "Go Back",
            nullptr, [](auto, auto) {});

        /*
            [button, this](auto, bool btn2)
            {
            if (btn2)
            {
                FMODAudioEngine::sharedEngine()->playEffect("playSound_01.ogg");
                button->setEnabled(false);

                auto level = GameLevelManager::get()->getMainLevel(m_levelID, true);
                level->m_levelString = LocalLevelManager::get()->getMainLevelString(m_levelID);
                log::info("ID: {}", level->m_songID);

                CCDirector::get()->replaceScene(CCTransitionFade::create(0.5f, PlayLayer::scene(level, false, false)));
            }
            });
        */
    }
    else
    {
        FMODAudioEngine::sharedEngine()->playEffect("playSound_01.ogg");

        auto level = GameLevelManager::get()->getMainLevel(m_levelID, true);
        level->m_levelString = LocalLevelManager::get()->getMainLevelString(m_levelID);
        log::info("ID: {}", level->m_songID);

        CCDirector::get()->replaceScene(CCTransitionFade::create(0.5f, PlayLayer::scene(level, false, false)));
    }
};

void OdysseyLevelPopup::onSettings(CCObject *sender)
{
    auto layer = GameLevelOptionsLayer::create(m_level);
    layer->show();
};

void OdysseyLevelPopup::onComic(CCObject *sender)
{
    auto scene = CCScene::create();
    scene->addChild(ComicLayer::create(m_levelID + 1 + Odyssey::islandPageForLevelID(m_levelID) - 7000, false));

    auto button = static_cast<CCMenuItemSpriteExtra *>(sender);
    button->setSprite(CircleButtonSprite::createWithSpriteFrameName("GDO_ComicIcon_001.png"_spr, 1, CircleBaseColor::Green, CircleBaseSize::Small));

    GameManager::sharedState()->fadeInMusic(fmt::format("comic_{:02}.mp3"_spr, m_levelID + 1 + Odyssey::islandPageForLevelID(m_levelID) - 7000).c_str());
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
};

void OdysseyLevelPopup::onLore(CCObject *sender)
{
    auto spanish = GameManager::sharedState()->getGameVariable("0201");

    if (m_levelID == 7501)
    {
        auto lore = spanish ? "<cg>\"Conclusive Journey\"</c> cuenta la historia de un Antiguo Camino que conduce al desolado desierto. Antes de que ocurran los eventos de <cy>GD: Odyssey</c>, el equipo de aventureros deambula por aqui en busca de mas pistas que ayuden a comprender lo que esta ocurriendo en Geometry City." : "<cg>\"Conclusive Journey\"</c> tells the tale of an Ancient Road leading to the desolate desert. Before the events of <cy>GD: Odyssey</c>, the team of adventurers wander here in search for more clues to help understand what's happening in Geometry City.";

        auto credits = FLAlertLayer::create("Info", lore, "ok");
        credits->show();
    }

    if (m_levelID == 7502)
    {
        auto lore = spanish ? "<cg>\"Burning Sands\"</c> cuenta la historia de Nefferkitty, un antiguo dios egipcio y protector de la Piedra de los elementos. Antes de los eventos de <cy>GD: Odyssey</c>, el equipo de aventureros visito el desierto durante la invasion del <cr>Wanderer</c>. Los acontecimientos de este juego ocurren despues de completar este nivel." : "<cg>\"Burning Sands\"</c> tells the story of Nefferkitty, an ancient Egyptian god and protector of the Stone of elements. Before the events of <cy>GD: Odyssey</c>, the team of adventurers visited the desert during the <cr>Wanderer's</c> invasion. The events of this game take place after completing this level.";

        //  auto credits = FLAlertLayer::create("Info", lore, "ok");
        auto credits = Popup::create("Info", lore, "Ok");
        credits->show();
    }
}

/*
void OdysseyLevelPopup::onAudio(CCObject *sender)
{
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto button = static_cast<CCMenuItemSpriteExtra *>(sender);
    button->runAction(CCFadeTo::create(0.5, 0));

    if (m_audioWidget)
    {
        m_audioWidget->runAction(CCEaseSineOut::create(CCMoveTo::create(0.5, {winSize.width / 2, 30})));

        if (auto arrowButton = this->getChildByIDRecursive("hide-song-button"))
        {
            arrowButton->setVisible(true);
            arrowButton->runAction(CCFadeTo::create(0.5, 255));
            arrowButton->runAction(CCEaseSineOut::create(CCMoveTo::create(0.5, {arrowButton->getPositionX(), 40})));
        }
    }
};

void OdysseyLevelPopup::onHideAudio(CCObject *sender)
{
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto button = static_cast<CCMenuItemSpriteExtra *>(sender);
    button->setPosition(button->getPositionX(), 0);
    button->setVisible(false);
    button->setOpacity(0);

    if (m_audioWidget)
    {
        m_audioWidget->runAction(CCEaseSineIn::create(CCMoveTo::create(0.5, {winSize.width / 2, -30})));

        if (auto downloadAudioBtn = this->getChildByIDRecursive("download-audio-btn"))
        {
            downloadAudioBtn->runAction(CCFadeTo::create(0.5, 255));
        }
    }
};
*/

OdysseyLevelPopup *OdysseyLevelPopup::create(int levelID)
{
    auto ret = new OdysseyLevelPopup();
    ret->m_levelID = levelID;

    if (ret && ret->initAnchored(380.f, 260.f, ""))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
};