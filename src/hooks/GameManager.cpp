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
            return 515;
        if (icon == IconType::Ship)
            return 175;
        if (icon == IconType::Ball)
            return 124;
        if (icon == IconType::Ufo)
            return 153;
        if (icon == IconType::Wave)
            return 100;
        if (icon == IconType::Robot)
            return 68;
        if (icon == IconType::Spider)
            return 69;
        if (icon == IconType::Swing)
            return 46;
        if (icon == IconType::Jetpack)
            return 9;

        return GameManager::countForType(icon);
    }

    bool isIconUnlocked(int id, IconType type)
    {
        if (Odyssey::isCustomIcon(id, type))
            return GameManager::isIconUnlocked(id, type);
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

    void reportPercentageForLevel(int levelID, int percent, bool isPractice)
    {
        GameManager::reportPercentageForLevel(levelID, percent, isPractice);
        log::info("Level: {}, {}, {}", levelID, percent, isPractice);

        if(levelID == 201){
            if(isPractice){
                GameManager::sharedState()->reportAchievementWithID("geometry.ach.level201a", percent, false);
            } else {
                GameManager::sharedState()->reportAchievementWithID("geometry.ach.level201b", percent, false);
            }
        };

        if(levelID == 202){
            if(isPractice){
                GameManager::sharedState()->reportAchievementWithID("geometry.ach.level202a", percent, false);
            } else {
                GameManager::sharedState()->reportAchievementWithID("geometry.ach.level202b", percent, false);
            }
        };
    };

    void reportAchievementWithId(const char *ach, int perc, bool flag)
    {
        GameManager::reportAchievementWithID(ach, perc, flag);

        log::debug("ACH: {}, Percent: {}, Flag: {}", ach, perc, flag);
    };
};