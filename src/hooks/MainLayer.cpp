#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "../layers/OdysseySelectLayer.hpp"
#include "../layers/DeveloperLayer.hpp"
#include "../layers/FanmadeGamesLayer.hpp"
#include "../ui/LanguagePopup.hpp"
#include "../ui/CreditsPopup.hpp"
#include "../ui/AlertPopup.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

bool shownAlert = false;

class $modify(OdysseyMenuLayer, MenuLayer)
{
    bool init()
    {
        if (!MenuLayer::init())
            return false;

        //  Shows the language setting at the start
        if (!Mod::get()->setSavedValue("show-language-setting", true))
        {
            auto popup = LanguagePopup::create();
            popup->m_scene = this;
            popup->setZOrder(104);
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

        //  Agregua el boton de MDK
        auto MDKButton = CCMenuItemSpriteExtra::create(
            CircleButtonSprite::createWithSpriteFrameName("GDO_MDKLogo_001.png"_spr, 1.5, CircleBaseColor::Green, CircleBaseSize::MediumAlt),
            this,
            menu_selector(OdysseyMenuLayer::onMDK));

        bottomMenu->addChild(MDKButton);
        bottomMenu->updateLayout();

        if (Mod::get()->getSettingValue<bool>("dev-mode"))
        {
            auto devButton = CCMenuItemSpriteExtra::create(
                CircleButtonSprite::createWithSpriteFrameName("GDO_SettingsIcon_001.png"_spr, 1, CircleBaseColor::DarkPurple, CircleBaseSize::MediumAlt),
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
        auto credits = CreditsPopup::create();
        credits->show();
    }
};