#include <Geode/Geode.hpp>
#include <Geode/modify/DialogLayer.hpp>
#include "../layers/ComicLayer.hpp"

using namespace geode::prelude;

class $modify(OdysseyDialogLayer, DialogLayer)
{
    void onClose()
    {
        //  Evento 1: Al interactuar con el viejo por primera vez
        if(GameManager::sharedState()->getUGV("203") && !GameManager::sharedState()->getUGV("211"))
        {
            auto layer = ComicLayer::create(1);
            layer->m_redirectToMap = true;

            auto scene = CCScene::create();
            scene->addChild(layer);

            GameManager::sharedState()->fadeInMusic("comic_01.mp3"_spr);
            CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, scene));
        };

        DialogLayer::onClose();
    };
};