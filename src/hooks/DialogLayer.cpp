#include <Geode/Geode.hpp>
#include <Geode/modify/DialogLayer.hpp>
#include "../layers/OdysseyComicLayer.hpp"

using namespace geode::prelude;

class $modify(OdysseyDialogLayer, DialogLayer)
{
    void onClose()
    {
        //  Se reemplazara esto con el Game Manager, pero lo tengo para Desarrollo
        //  auto GM = GameManager::sharedState();
        //  auto watchedComic01 = GM->getUGV("52");

        auto seenComic = Mod::get()->getSettingValue<bool>("watched-comic-01");
        //  log::debug("FIRST COMIC {}", seenComic);

        if(!seenComic)
        {
            auto layer = OdysseyComicLayer::create(1);
            auto scene = CCScene::create();
            scene->addChild(layer);

            CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, scene));

            Mod::get()->setSettingValue("watched-comic-01", true);
            //  GM->setUGV("52", true);
        };

        DialogLayer::onClose();
    };
};