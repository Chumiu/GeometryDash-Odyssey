#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "../layers/OdysseySelectLayer.hpp"
#include "../layers/OdysseyDevLayer.hpp"
#include "../layers/FanmadeGamesLayer.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyMenuLayer, MenuLayer)
{
    bool init()
    {
        if (!MenuLayer::init())
            return false;

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
        auto seenComic = Mod::get()->getSettingValue<bool>("watched-comic-01");

        if (seenComic)
        {   
            auto geodeButton = bottomMenu->getChildByID("geode.loader/geode-button");
            geodeButton->removeFromParentAndCleanup(true);

            auto comicButton = CCMenuItemSpriteExtra::create(
                CircleButtonSprite::createWithSpriteFrameName("GDO_comicBtn.png"_spr, 1, CircleBaseColor::Green, CircleBaseSize::MediumAlt),
                this,
                nullptr
            );

            bottomMenu->addChild(comicButton);
            bottomMenu->addChild(geodeButton);
            bottomMenu->updateLayout();
        }

        auto moreGamesMenu = static_cast<CCMenu *>(this->getChildByID("more-games-menu"));
        auto moreGamesButton = static_cast<CCMenuItemSpriteExtra *>(moreGamesMenu->getChildByID("more-games-button"));
        if (moreGamesButton)
        {
            auto creditsSprite = CCSprite::createWithSpriteFrameName("GDO_CreditsBtn_001.png"_spr);
            creditsSprite->setScale(0.9f);
            moreGamesButton->setTag(1);

            //  Esto cambiara mas tarde
            moreGamesButton->setNormalImage(creditsSprite);
        }

        /*
        for (int i = 0; i < GameManager::sharedState()->countForType(IconType::Cube); i++)
        {
            log::info("Unlock: {}, ID: {}", GameStatsManager::sharedState()->getItemUnlockState(i + 1, UnlockType::Cube), i + 1);
        }*/

        return true;
    }

    void onPlay(CCObject *)
    {
        auto levelscene = OdysseySelectLayer::scene(0);
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, levelscene));
    }

    void onCreator(CCObject *sender)
    {
        MenuLayer::onCreator(sender);

        // https://cdn.discordapp.com/attachments/1196219414090088492/1312260912178004028/652ded519286d.png?ex=674bd9b6&is=674a8836&hm=97941665f4143f33aaf60ef1b09f325d6d99e96121bd7f8b4729c1250d17b43b&
    }

    void onRobTop(CCObject *)
    {
        auto scene = CCScene::create();
        scene->addChild(OdysseyDevLayer::create());

        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
    };

    void onMoreGames(CCObject *)
    {
        auto credits = FLAlertLayer::create("Si", "Si", "ok");
        credits->show();
    }
};