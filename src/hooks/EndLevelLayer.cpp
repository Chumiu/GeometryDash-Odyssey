#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
#include "../layers/OdysseyComicLayer.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(GDO_EndLevelLayer, EndLevelLayer)
{
    void onMenu(CCObject *sender)
    {
        auto level = PlayLayer::get()->m_level->m_levelID;
        int page = Odyssey::islandPageForLevelID(level);

        log::debug("ON MENU, LEVEL: {}", (int)level);
    
        if(level == 7004 && AchievementManager::sharedState()->isAchievementEarned("geometry.ach.level04b") && !GameManager::sharedState()->getUGV("216")){
            auto layer = OdysseyComicLayer::create(6, true);
            auto scene = CCScene::create();
            scene->addChild(layer);

            CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, scene));
            EndLevelLayer::onMenu(sender);
            GameManager::sharedState()->fadeInMusic("comic_06.mp3"_spr);
            return;
        }

        if(level == 7009 && AchievementManager::sharedState()->isAchievementEarned("geometry.ach.level09b") && !GameManager::sharedState()->getUGV("222")){
            auto layer = OdysseyComicLayer::create(12, true);
            auto scene = CCScene::create();
            scene->addChild(layer);

            CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, scene));
            EndLevelLayer::onMenu(sender);
            GameManager::sharedState()->fadeInMusic("comic_12.mp3"_spr);
            return;
        }

        EndLevelLayer::onMenu(sender);
        GameManager::sharedState()->fadeInMusic(fmt::format("IslandLoop{:02}.mp3"_spr, page + 1));
    };
};