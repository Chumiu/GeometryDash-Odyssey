#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include "../utils/Utils.hpp"

using namespace geode::prelude;

enum class Artist
{
    ML500 = 2102,
    Minox = 13284787,
    Danky = 14178231,
    Angelo = 18718615,
    Cyan = 21113321
};

class $modify(OdysseyLoadingLayer, LoadingLayer)
{
    bool init(bool reload)
    {
        if (!LoadingLayer::init(reload))
            return false;

        auto GM = GameManager::sharedState();

        auto SFC = CCSpriteFrameCache::get();
        auto searchPathRoot = dirs::getModRuntimeDir() / Mod::get()->getID() / "resources";
        CCFileUtils::sharedFileUtils()->addSearchPath(searchPathRoot.string().c_str());
        SFC->addSpriteFramesWithFile("GJO_GameSheet01.plist"_spr);

        auto mainTitle = static_cast<CCSprite *>(this->getChildByID("gd-logo"));
        if (mainTitle)
        {
            auto odysseyTitle = CCSprite::createWithSpriteFrameName("GDO_MainLogo_001.png"_spr);
            mainTitle->setDisplayFrame(odysseyTitle->displayFrame());
        }

        auto robtopLogo = static_cast<CCSprite *>(this->getChildByID("robtop-logo"));
        if (robtopLogo)
        {
            auto teamLogo = CCSprite::createWithSpriteFrameName("GDO_TeamLogo_001.png"_spr);
            robtopLogo->setDisplayFrame(teamLogo->displayFrame());
        };

        //  La bandera de "Aceptar los ToS" del juego
        if (!GM->getUGV("30"))
        {
            GM->setUGV("30", true);
        }

        OdysseyLoadingLayer::addOdysseyAudioAssets();
        OdysseyLoadingLayer::addCustomIconCredits();

        return true;
    }

    void addOdysseyAudioAssets()
    {
        MusicDownloadManager::sharedState()->m_resourceSfxUnorderedSet.clear();
        MusicDownloadManager::sharedState()->m_resourceSongUnorderedSet.clear();

        // TDS
        Odyssey::insertAssetsToMap(false, {288, 537, 757, 758, 759, 1005, 1373, 1374, 1375, 1376, 1548, 1992, 1993, 1994, 1995, 2037, 2038, 2039, 2040, 2779, 3081, 3383, 3384, 3556, 4273, 4274, 4293, 4294, 4395, 4397, 4404, 7501, 7874, 8180, 13536, 14554, 14563, 14575});
        Odyssey::insertAssetsToMap(true, {10005070, 10006468, 10009443});

        // GH
        Odyssey::insertAssetsToMap(false, {539, 554, 1076, 1740, 2389, 2390, 2392, 2590, 2591, 2844, 2847, 3082, 3084, 3084, 3085, 3114, 3120, 3533, 4395, 4397, 4404, 7274, 7501, 7791, 7795, 7799, 12087, 12089, 12121, 12132, 12174, 12175, 12178, 12184, 12188, 12198, 12920, 15950, 15955, 18929});
        Odyssey::insertAssetsToMap(true, {676349});

        // SU
        Odyssey::insertAssetsToMap(false, {491, 492, 493, 562, 755, 1025, 1049, 1567, 1571, 1572, 1586, 1587, 1619, 1740, 1751, 1897, 2393, 2711, 2716, 2717, 2718, 2847, 2910, 2913, 2914, 2915, 2916, 2974, 3016, 3210, 3383, 3384, 4260, 4261, 4262, 4273, 4289, 4290, 4397, 4404, 6242, 6310, 7231, 7646, 7647, 19796});
        Odyssey::insertAssetsToMap(true, {10000718, 10007255});

        // CF
        Odyssey::insertAssetsToMap(false, {328, 539, 1739, 3208, 4395, 4397, 4404, 4869, 6256, 7501, 12875, 13228, 13231, 14061, 176949, 17650, 17651, 17652});
        Odyssey::insertAssetsToMap(true, {10007201});

        // CJ
        Odyssey::insertAssetsToMap(false, {4395, 4397, 4404, 7501, 566});

        // BS
        Odyssey::insertAssetsToMap(false, {993, 1185, 1372, 1377, 1378, 1601, 1741, 1744, 1745, 2075, 2612, 2824, 2981, 2982, 4072, 4073, 4074, 7625, 7735, 7943, 8181, 8191, 9873, 15907, 18771, 1374, 1375, 1376, 1751, 2390, 2392, 2716, 2717, 2718, 3081, 4290, 6242});
        Odyssey::insertAssetsToMap(true, {10006666});
    }

    void addCustomIconCredits()
    {
        auto gs = GameStatsManager::sharedState();

        gs->m_usernameForAccountID.insert(std::make_pair(14178231, "Danky99"));
        gs->m_usernameForAccountID.insert(std::make_pair(18718615, "AngelozDD"));
        gs->m_usernameForAccountID.insert(std::make_pair(13284787, "MinoX28"));
        gs->m_usernameForAccountID.insert(std::make_pair(21113321, "cyanflower"));

        for (int i = 486; i < 502; i++)
        {
            Odyssey::addCreditsToIcon(std::make_pair(i, UnlockType::Cube), (int)Artist::Danky);
        }
        Odyssey::addCreditsToIcon(std::make_pair(502, UnlockType::Cube), (int)Artist::Minox);
        for (int i = 503; i < 507; i++)
        {
            Odyssey::addCreditsToIcon(std::make_pair(i, UnlockType::Cube), (int)Artist::Cyan);
        }
        Odyssey::addCreditsToIcon(std::make_pair(507, UnlockType::Cube), (int)Artist::ML500);
        Odyssey::addCreditsToIcon(std::make_pair(508, UnlockType::Cube), (int)Artist::ML500);
    
        Odyssey::addCreditsToIcon(std::make_pair(170, UnlockType::Ship), (int)Artist::Danky);
        Odyssey::addCreditsToIcon(std::make_pair(171, UnlockType::Ship), (int)Artist::ML500);
        Odyssey::addCreditsToIcon(std::make_pair(172, UnlockType::Ship), (int)Artist::ML500);

        Odyssey::addCreditsToIcon(std::make_pair(119, UnlockType::Ball), (int)Artist::Danky);
        Odyssey::addCreditsToIcon(std::make_pair(120, UnlockType::Ball), (int)Artist::ML500);
        Odyssey::addCreditsToIcon(std::make_pair(121, UnlockType::Ball), (int)Artist::ML500);
        Odyssey::addCreditsToIcon(std::make_pair(122, UnlockType::Ball), (int)Artist::Cyan);

        Odyssey::addCreditsToIcon(std::make_pair(150, UnlockType::Bird), (int)Artist::ML500);
        Odyssey::addCreditsToIcon(std::make_pair(151, UnlockType::Bird), (int)Artist::ML500);

        Odyssey::addCreditsToIcon(std::make_pair(97, UnlockType::Dart), (int)Artist::Danky);
        Odyssey::addCreditsToIcon(std::make_pair(98, UnlockType::Dart), (int)Artist::ML500);

        Odyssey::addCreditsToIcon(std::make_pair(44, UnlockType::Swing), (int)Artist::Danky);
    }
};