#include <Geode/Geode.hpp>
#include <Geode/modify/GameStatsManager.hpp>
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyGameStatsManager, GameStatsManager)
{
    void incrementStat(char const* p0, int p1){
        GameStatsManager::incrementStat(p0, p1);

        if(std::string_view(p0) == std::string_view("14")){
            log::debug("ORBES");

            Mod::get()->setSavedValue<int>("Orbs", GameStatsManager::getStat(p0) + p1);
        }
    };

    void checkCoinAchievement(GJGameLevel *level)
    {
        auto GM = GameManager::sharedState();
        int coinPercent = (getCollectedCoinsForLevel(level) / 3.f) * 100.f;

        auto achievementID = fmt::format("geometry.ach.level{:02}c", level->m_levelID.value() - 7000);
        log::info("coinPercent: {}, achID: {}", coinPercent, achievementID);

        if (level->m_levelType == GJLevelType::Local)
        {
            GM->reportAchievementWithID(achievementID.c_str(), coinPercent, false);
        }
    }

    int getBaseCurrencyForLevel(GJGameLevel *level)
    {
        if (level->m_levelID.value() == 7009)
            return 500;

        if (level->m_levelID.value() == 7502)
            return 500;

        return GameStatsManager::getBaseCurrencyForLevel(level);
    }

    bool isItemUnlocked(UnlockType type, int ID)
    {
        //  Practice Music Unlocker
        if (type == UnlockType::GJItem && ID == 17)
            return true;

        return GameStatsManager::isItemUnlocked(type, ID);
    }

    int getItemUnlockState(int p0, UnlockType p1)
    {
        //  El icono no es custom
        if (!Odyssey::isIconCustom(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))))
            return 4;

        //  No tiene achievement
        if (!AchievementManager::sharedState()->achievementForUnlock(p0, p1).empty())
            return 1;

        //  Icono aun no ha salido
        if (Odyssey::isIconUpcoming(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))))
            return 6;

        //  Icono de tienda
        return 5;
    }

    void createStoreItems()
    {
        auto newShop = static_cast<ShopType>(6);
        if (!m_allStoreItems)
        {
            m_allStoreItems = CCDictionary::create();
            m_allStoreItems->retain();

            m_storeItems = CCDictionary::create();
            m_storeItems->retain();

            m_storeItemArray = CCArray::create();
            m_storeItemArray->retain();

            //  REFERENCIA
            //  - Indice en la tienda
            //  - ID
            //  - UnlockType
            //  - Precio
            //  - Tienda

            addStoreItem(1, 500, 1, 100, newShop); // CUBO
            addStoreItem(2, 501, 1, 100, newShop); // CUBO
            addStoreItem(3, 502, 1, 100, newShop); // CUBO
            addStoreItem(4, 503, 1, 100, newShop); // CUBO

            addStoreItem(5, 1, 12, 500, newShop);  // LLAVE
            addStoreItem(6, 2, 12, 500, newShop);  // LLAVE
            addStoreItem(7, 46, 13, 100, newShop); // SWING
            addStoreItem(8, 47, 13, 100, newShop); // SWING

            addStoreItem(9, 504, 1, 100, newShop);  // CUBO
            addStoreItem(10, 505, 1, 100, newShop); // CUBO
            addStoreItem(11, 506, 1, 100, newShop); // CUBO
            addStoreItem(12, 507, 1, 100, newShop); // CUBO

            addStoreItem(13, 121, 5, 100, newShop); // BOLA
            addStoreItem(14, 122, 5, 100, newShop); // BOLA
            addStoreItem(15, 174, 4, 100, newShop); // NAVE
            addStoreItem(16, 175, 4, 100, newShop); // NAVE

            addStoreItem(17, 18, 12, 50, newShop); // ANIMACION
            addStoreItem(18, 19, 12, 50, newShop); // ANIMACION
            addStoreItem(19, 20, 12, 50, newShop); // ANIMACION
        }
    }
};