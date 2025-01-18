#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "../layers/CreditsLayer.hpp"
#include "../layers/OdysseySelectLayer.hpp"
#include "../layers/DeveloperLayer.hpp"
#include "../layers/FanmadeGamesLayer.hpp"
#include "../nodes/CreditsNode.hpp"
#include "../nodes/ComicPopup.hpp"
#include "../nodes/OdysseyPopup.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

bool shownAlert = false;

class $modify(OdysseyMenuLayer, MenuLayer)
{
    bool init()
    {
        if (!MenuLayer::init())
            return false;

        if (Mod::get()->getSettingValue<bool>("restart-mod"))
            OdysseyMenuLayer::Restart();

        //  Incompatibilities fixed in 4.2.0
        /*
        auto breakingMods = Odyssey::getBreakingMods();
        if (!breakingMods.empty())
        {
            if (!shownAlert)
            {
                std::string description = "Disable the following Mods to use <cy>Geometry Dash: Odyssey</c>:";

                for (Mod *mod : breakingMods)
                {
                    log::debug("{}", mod->getName());
                    description += "\n- <cr>" + mod->getName() + "</c>";
                }

                auto popup = FLAlertLayer::create(
                    "Incompatible Mods",
                    description,
                    "OK");

                shownAlert = true;
                popup->m_scene = this;
                popup->show();
            }

            if (!Odyssey::getEarlyLoadBreakingMods().empty() || Loader::get()->isModLoaded("ninxout.redash"))
                return true;
        }
        */

        if (!GameManager::sharedState()->getUGV("201"))
        {
            auto popup = OdysseyPopup::create("Savefile Notice", "<cr>Odyssey</c> stores the data in\na separate <cy>savefile</c>. Your data\nwill be <cg>restored</c> when you\n<cb>turn off</c> the Mod.");
            popup->setWarning(true, false);
            popup->m_scene = this;
            popup->show();
        };

        if (!GameManager::sharedState()->getUGV("202") && GameManager::sharedState()->getGameVariable("0201"))
        {
            auto popup = OdysseyPopup::create("Language Notice", "Dado a limitaciones de\ncaracteres en el juego, habran\n<cr>errores ortograficos</c>\n(como la falta de acentos)");
            popup->setWarning(false, true);
            popup->setZOrder(104);
            popup->m_scene = this;
            popup->show();
        };

        //  Reemplaza el titulo
        auto gameTitle = static_cast<CCSprite *>(this->getChildByID("main-title"));
        if (gameTitle)
        {
            auto odysseyTitle = CCSprite::createWithSpriteFrameName("GDO_MainLogo_001.png"_spr);
            gameTitle->setDisplayFrame(odysseyTitle->displayFrame());
            gameTitle->setPositionY(gameTitle->getPositionY() - 15);
        }

        //  Reemplazar el boton para acceder al Menu Online
        auto mainMenu = static_cast<CCMenu *>(this->getChildByID("main-menu"));
        auto creatorButton = static_cast<CCMenuItemSpriteExtra *>(mainMenu->getChildByID("editor-button"));
        if (creatorButton)
        {
            auto mgSprite = CCSprite::createWithSpriteFrameName("GJ_moreGamesBtn_001.png");

            //  Esto cambiara mas tarde
            creatorButton->setNormalImage(mgSprite);
        }

        //  Boton para acceder a los comics mas facil
        auto bottomMenu = static_cast<CCMenu *>(this->getChildByID("bottom-menu"));

        //  Remplaza el boton de Newgrounds por el boton de MDK
        if (auto newgroundsButton = static_cast<CCMenuItemSpriteExtra *>(bottomMenu->getChildByID("newgrounds-button")))
        {
            newgroundsButton->removeFromParentAndCleanup(true);

            auto MDKButton = CCMenuItemSpriteExtra::create(
                CircleButtonSprite::createWithSpriteFrameName("GDO_MDKLogo_001.png"_spr, 1.5, CircleBaseColor::Green, CircleBaseSize::MediumAlt),
                this,
                menu_selector(OdysseyMenuLayer::onMDK));

            bottomMenu->addChild(MDKButton);
            bottomMenu->updateLayout();
        }

        if (GameManager::sharedState()->getUGV("208") || GameManager::sharedState()->getUGV("222"))
        {
            auto comicButton = CCMenuItemSpriteExtra::create(
                CircleButtonSprite::createWithSpriteFrameName("GDO_ComicIcon_001.png"_spr, 1, CircleBaseColor::Green, CircleBaseSize::MediumAlt),
                this,
                menu_selector(OdysseyMenuLayer::onComics));

            bottomMenu->addChild(comicButton);
            bottomMenu->updateLayout();
        }

        if (Mod::get()->getSettingValue<bool>("dev-mode"))
        {
            auto devButton = CCMenuItemSpriteExtra::create(
                CircleButtonSprite::createWithSpriteFrameName("geode.loader/settings.png", 1, CircleBaseColor::Gray, CircleBaseSize::MediumAlt),
                this,
                menu_selector(OdysseyMenuLayer::onDev));

            bottomMenu->addChild(devButton);
            bottomMenu->updateLayout();
        }

        //  Boton de more games es reemplazado por Creditos
        auto moreGamesMenu = static_cast<CCMenu *>(this->getChildByID("more-games-menu"));
        auto moreGamesButton = static_cast<CCMenuItemSpriteExtra *>(moreGamesMenu->getChildByID("more-games-button"));
        if (moreGamesButton)
        {
            auto creditsSprite = CrossButtonSprite::createWithSpriteFrameName("GDO_CreditsIcon_001.png"_spr, 1.5f);
            creditsSprite->setScale(0.9f);
            moreGamesButton->setTag(1);

            //  Esto cambiara mas tarde
            moreGamesButton->setNormalImage(creditsSprite);
        }

        if (auto levelEditorHint = static_cast<CCSprite *>(this->getChildByID("level-editor-hint")))
            levelEditorHint->setVisible(false);

        auto rightMenu = static_cast<CCMenu *>(this->getChildByID("right-side-menu"));

        auto dailyCButton = static_cast<CCMenuItemSpriteExtra *>(rightMenu->getChildByID("daily-chest-button"));
        if (dailyCButton)
            dailyCButton->setVisible(false);

        return true;
    }

    void onDev(CCObject *)
    {
        auto scene = CCScene::create();
        scene->addChild(DeveloperLayer::create());

        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
    }

    void onMDK(CCObject *)
    {
        auto popup = createQuickPopup(
            "MDK Music",
            "Wanna visit <cy>MDK</c>'s website for awesome music and know more about the <cg>World of Wubstep</c>?",
            "Cancel",
            "Open",
            [](auto, bool btn2)
            {
                if (btn2)
                {
                    CCApplication::sharedApplication()->openURL("https://morgandavidking.com/");
                }
            });
    };

    void onPlay(CCObject *)
    {
        auto breakingMods = Odyssey::getBreakingMods();

        if (!breakingMods.empty())
        {
            std::string description = "Disable the following Mods to use <cy>Geometry Dash: Odyssey</c>:";

            for (Mod *mod : breakingMods)
            {
                log::debug("{}", mod->getName());
                description += "\n- <cr>" + mod->getName() + "</c>";
            }

            auto popup = FLAlertLayer::create(
                "Incompatible Mods",
                description,
                "OK");

            popup->show();
            return;
        }

        auto levelscene = OdysseySelectLayer::scene(0);
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, levelscene));
    }

    void onCreator(CCObject *sender)
    {
        auto developerMode = Mod::get()->getSettingValue<bool>("dev-mode");

        if (developerMode)
        {
            MenuLayer::onCreator(sender);
            return;
        }

        auto *layer = FanmadeGamesLayer::create();
        addChild(layer, 100);

        layer->showLayer(false);
        return;
    }

    void onMoreGames(CCObject *)
    {
        auto credits = CreditsLayer::create();
        credits->show();
    }

    void onComics(CCObject *)
    {
        auto comicPopup = ComicPopup::create();
        comicPopup->show();
    }

    void Restart()
    {
        Mod::get()->setSettingValue<bool>("restart-mod", false);

        for (auto ii = 1; ii <= 40; ii++)
        {
            auto variable = (ii < 10) ? fmt::format("20{}", ii) : fmt::format("2{}", ii);
            GameManager::sharedState()->setUGV(variable.c_str(), false);
            log::debug("Restarting UGV = {}", variable);
        };

        log::debug("Variables succesfully restarted");
    }
};