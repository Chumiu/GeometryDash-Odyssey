#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>
#include "../layers/OdysseySelectLayer.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyGameManager, GameManager)
{
    int countForType(IconType icon)
    {
        if (icon == IconType::Cube)
            return 502;
        if (icon == IconType::Ship)
            return 170;
        if (icon == IconType::Ball)
            return 121;
        if (icon == IconType::Ufo)
            return 151;
        if (icon == IconType::Wave)
            return 97;
        if (icon == IconType::Robot)
            return 68;
        if (icon == IconType::Spider)
            return 69;
        if (icon == IconType::Swing)
            return 44;

        return GameManager::countForType(icon);
    }

    bool isIconUnlocked(int id, IconType type)
    {
        //  if (Odyssey::isCustomIcon(id, type)) return GameManager::isIconUnlocked(id, type);
        return true;
    }

    bool isColorUnlocked(int id, UnlockType type)
    {
        return true;
    }

    void returnToLastScene(GJGameLevel *level)
    {
        if (level->m_levelType == GJLevelType::Local)
        {
            int page = Odyssey::islandPageForLevelID(level->m_levelID);

            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, OdysseySelectLayer::scene(page)));
            GameManager::sharedState()->fadeInMusic("TheMap.mp3"_spr);

            return;
        }

        GameManager::returnToLastScene(level);
    }
};