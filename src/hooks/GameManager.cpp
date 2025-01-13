#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>
#include "../layers/OdysseySelectLayer.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyGameManager, GameManager)
{
    void firstLoad()
    {
        GameManager::firstLoad();
        Mod::get()->setSavedValue<int>("Orbs", 0);
    };

    int countForType(IconType icon)
    {
        //  auto hide = GameManager::sharedState()->getGameVariable("0202");
        switch (icon)
        {
        case IconType::Cube:
            return 514;
        case IconType::Ship:
            return 177;
        case IconType::Ball:
            return 126;
        case IconType::Ufo:
            return 154;
        case IconType::Wave:
            return 100;
        case IconType::Robot:
            return 68;
        case IconType::Spider:
            return 69;
        case IconType::Swing:
            return 47;
        case IconType::Jetpack:
            return 9;
        case IconType::Special:
            return 7;
        case IconType::DeathEffect:
            return 20;
        case IconType::ShipFire:
            return 6;
        case IconType::Item:
            return 21;
        default:
            //  Yes, this solution is terrible, but I don't know how to patch bytes.
            return GameManager::countForType(icon);
        }
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
            GameManager::sharedState()->fadeInMusic(fmt::format("IslandLoop{:02}.mp3"_spr, page + 1));
            // CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
            return;
        }

        GameManager::returnToLastScene(level);
    }

    void reportPercentageForLevel(int levelID, int percent, bool isPractice)
    {
        GameManager::reportPercentageForLevel(levelID, percent, isPractice);
        log::info("Level: {}, {}, {}", levelID, percent, isPractice);

        std::string achievementID = fmt::format("geometry.ach.level{:02}{}", levelID - 7000, isPractice ? "a" : "b");

        GameManager::sharedState()->reportAchievementWithID(achievementID.c_str(), percent, false);
    };

    void reportAchievementWithId(const char *ach, int perc, bool flag)
    {
        GameManager::reportAchievementWithID(ach, perc, flag);

        log::debug("ACH: {}, Percent: {}, Flag: {}", ach, perc, flag);
    };

    void dataLoaded(DS_Dictionary *dict)
    {
        GameManager::dataLoaded(dict);
    }
};
