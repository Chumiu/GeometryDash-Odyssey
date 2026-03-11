#include <Geode/Geode.hpp>
#include <Geode/modify/GameLevelOptionsLayer.hpp>
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(GDO_GameLevelOptionsLayer, GameLevelOptionsLayer)
{
    static GameLevelOptionsLayer *create(GJGameLevel *p0)
    {
        if (p0->m_levelType == GJLevelType::Main)
        {
            auto layer = GameLevelOptionsLayer::create(p0);
            auto winSize = CCDirector::sharedDirector()->getWinSize();
            auto contentSize = layer->m_mainLayer->getContentSize();

            //  Titulo
            auto label = CCLabelBMFont::create("Level Options", "bigFont.fnt");
            label->setScale(0.7f);
            label->setPosition({contentSize.width / 2, contentSize.height / 2 + 120});
            layer->m_mainLayer->addChild(label);

            auto label_2 = CCLabelBMFont::create("Audio Assets", "bigFont.fnt");
            label_2->setScale(0.7f);
            label_2->setPosition({contentSize.width / 2, contentSize.height / 2 - 20});
            layer->m_mainLayer->addChild(label_2);

            //  Crea el CustomSongWidget
            auto songID = Odyssey::getLevelSongID(p0->m_levelID);
            auto assets = Odyssey::getLevelAudioAssets(p0->m_levelID);

            auto songObject = SongInfoObject::create(songID);
            auto audioWidget = CustomSongWidget::create(songObject, 0, 0, 0, 1, 0, 0, 0, 0);
            audioWidget->setPosition({winSize.width / 2, winSize.height / 2 - 85.f});
            audioWidget->setID("song-widget");

            audioWidget->updateSongInfo();
            audioWidget->updateWithMultiAssets(assets.first, assets.second, 0);
            audioWidget->getSongInfoIfUnloaded();

            auto title = Odyssey::createText("Why the change?", "Porque este cambio?");
            auto desc = Odyssey::createText(
                "The mod previously had <cr>optimization issues</c>, this helps drastically decrease the mod's size by making you download the <cj>Audio Assets</c> like an <cy>Online level</c>.",
                "El mod anteriormente tuvo <cr>problemas de optimizacion</c>, esto ayuda a reducir el peso del mod haciendo que descargues el <cj>Audio</c> como si fuera un <cy>Nivel Online</c>.");

            //  Info Button
            auto infoButton = InfoAlertButton::create(title, desc, 0.5);
            infoButton->setPosition({90, -15});

            layer->m_buttonMenu->addChild(infoButton);
            layer->m_mainLayer->addChild(audioWidget);
            return layer;
        }

        return GameLevelOptionsLayer::create(p0);
    }
};