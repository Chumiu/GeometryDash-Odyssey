#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>
#include "../layers/OdysseySelectLayer.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyGameManager, GameManager)
{
    int countForType(IconType icon)
    {
        //  auto hide = GameManager::sharedState()->getGameVariable("0202");

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
        if (Odyssey::isIconCustom(id, type))
            return GameManager::isIconUnlocked(id, type);

        if (type == IconType::Item)
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
            //CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
            //GameManager::sharedState()->fadeInMusic(fmt::format("IslandLoop{:02}.mp3"_spr, page));
            return;
        }

        GameManager::returnToLastScene(level);
    }

    void reportPercentageForLevel(int levelID, int percent, bool isPractice)
    {
        GameManager::reportPercentageForLevel(levelID, percent, isPractice);
        log::info("Level: {}, {}, {}", levelID, percent, isPractice);

        if (levelID == 501)
        {
            if (isPractice)
            {
                GameManager::sharedState()->reportAchievementWithID("geometry.ach.level501a", percent, false);
            }
            else
            {
                GameManager::sharedState()->reportAchievementWithID("geometry.ach.level501b", percent, false);
            }
        };

        if (levelID == 502)
        {
            if (isPractice)
            {
                GameManager::sharedState()->reportAchievementWithID("geometry.ach.level502a", percent, false);
            }
            else
            {
                GameManager::sharedState()->reportAchievementWithID("geometry.ach.level502b", percent, false);
            }
        };
    };

    void reportAchievementWithId(const char *ach, int perc, bool flag)
    {
        GameManager::reportAchievementWithID(ach, perc, flag);

        log::debug("ACH: {}, Percent: {}, Flag: {}", ach, perc, flag);
    };
};