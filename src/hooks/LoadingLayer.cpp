#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include "../utils/Utils.hpp"
#include <filesystem>
#include <iostream>

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

        auto version = CCLabelBMFont::create(fmt::format("{}", Mod::get()->getVersion().toVString(true)).c_str(), "goldFont.fnt");
        version->setPosition({5, 5});
        version->setAnchorPoint({0, 0});
        version->setScale(0.5f);
        this->addChild(version);

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

        OdysseyLoadingLayer::addCustomIconCredits();
        OdysseyLoadingLayer::addOdysseyAudioAssets();
        OdysseyLoadingLayer::addOdysseyComicAssets();

        //  La bandera de "Aceptar los ToS" del juego
        if (!GM->getUGV("30"))
            GM->setUGV("30", true);

        //  La bandera de primer dialogo del Shopkeeper (500 Orbes)
        if (!GM->getUGV("17"))
            GM->setUGV("17", true);

        GameManager::sharedState()->setIntGameVariable("1001", 0);

        return true;
    }

    const char *getLoadingString()
    {
        if (m_fromRefresh)
            return LoadingLayer::getLoadingString();

        std::vector<std::string> messages =
            {
                "Remember to play\nNukebound first!",
                "Increasing the amount\nof mod incompatibilities...",
                "Are you recording this\nright now?",
                "Explorers, the failed promise...",
                "Adding more wanted posters\non the shop",
                "Why the vaults talk about\nthis random gal?",
                "If something breaks,\nblame it on Chumiu",
                "Mathi Approved"};

        return messages.at(rand() % messages.size()).c_str();
    };

    void addOdysseyAudioAssets()
    {
        MusicDownloadManager::sharedState()->m_resourceSfxUnorderedSet.clear();
        MusicDownloadManager::sharedState()->m_resourceSongUnorderedSet.clear();

        // The Dangerous Seas
        Odyssey::insertAssetsToMap(false, {288, 537, 757, 758, 759, 1005, 1373, 1374, 1375, 1376, 1548, 1992, 1993, 1994, 1995, 2037, 2038, 2039, 2040, 2779, 3081, 3383, 3384, 3556, 4273, 4274, 4293, 4294, 4395, 4397, 4404, 7501, 7874, 8180, 13536, 14554, 14563, 14575, 22875});
        Odyssey::insertAssetsToMap(true, {10009443});

        // Ghost House
        Odyssey::insertAssetsToMap(false, {539, 554, 1076, 1740, 2389, 2390, 2392, 2590, 2591, 2844, 2847, 3082, 3084, 3084, 3085, 3114, 3120, 3533, 4395, 4397, 4404, 7274, 7501, 7791, 7795, 7799, 12087, 12089, 12121, 12132, 12174, 12175, 12178, 12184, 12188, 12198, 12920, 15950, 15955, 18929});
        //Odyssey::insertAssetsToMap(true, {676349}); - no es necesario

        // Super Ultra
        Odyssey::insertAssetsToMap(false, {491, 492, 493, 562, 755, 1025, 1049, 1567, 1571, 1572, 1586, 1587, 1619, 1740, 1751, 1897, 2393, 2711, 2716, 2717, 2718, 2847, 2910, 2913, 2914, 2915, 2916, 2974, 3016, 3210, 3383, 3384, 4260, 4261, 4262, 4273, 4289, 4290, 4397, 4404, 6242, 6310, 7231, 7646, 7647, 19796});
        Odyssey::insertAssetsToMap(true, {10000718, 10007255});

        // Cryptofunk
        Odyssey::insertAssetsToMap(false, {328, 583, 539, 1739, 2297, 3208, 4395, 4397, 4404, 4869, 6256, 7501, 12875, 13228, 13231, 14061, 176949, 17650, 17651, 17652});
        Odyssey::insertAssetsToMap(true, {10007201});

        // Hellfire
        Odyssey::insertAssetsToMap(false, {1368, 3001, 3002, 3003, 6243, 6244, 6245, 7224, 7225, 7243, 7245, 7246, 7260, 7262, 7271, 7643, 7652, 7945, 10104, 13237, 13238, 13239, 17604, 17619, 17621, 18164, 19729});
        Odyssey::insertAssetsToMap(true, {10007222});

        // Bossrush
        Odyssey::insertAssetsToMap(false, {998, 1014, 1024, 1950, 3083, 6808, 6833, 6838, 6840, 6863, 6870, 6897, 6900, 7667, 13057});
        Odyssey::insertAssetsToMap(true, {10007196});

        //Absolute Zero
        Odyssey::insertAssetsToMap(true, {10007188, 10011788});

        //Comfort Food
        Odyssey::insertAssetsToMap(true, {10012389});

        //Critical Hit
        Odyssey::insertAssetsToMap(false, {476, 709, 717, 2031, 2032, 2074, 2856, 3112, 3548, 4563, 4566, 4841, 4883, 5222, 6881, 6882, 6883, 7653, 7659, 7687, 13980, 22879});
        Odyssey::insertAssetsToMap(true, {10007200, 10000721});

        // Conclusive Journey
        Odyssey::insertAssetsToMap(false, {4395, 4397, 4404, 7501, 566});

        // Burning Sands
        Odyssey::insertAssetsToMap(false, {993, 1185, 1372, 1377, 1378, 1601, 1741, 1744, 1745, 2075, 2612, 2824, 2981, 2982, 4072, 4073, 4074, 7625, 7735, 7943, 8181, 8191, 9873, 15907, 18771, 1374, 1375, 1376, 1751, 2390, 2392, 2716, 2717, 2718, 3081, 4290, 6242});
        Odyssey::insertAssetsToMap(true, {10006666});
    }

    void addOdysseyComicAssets()
    {
        std::string zipPath;
        std::string unzipDir;

        log::debug("Loading comic assets...");

#ifdef GEODE_IS_WINDOWS
        zipPath = geode::Mod::get()->getResourcesDir().string() + "\\" + "ComicAssets.zip";
        unzipDir = geode::Mod::get()->getResourcesDir().string() + "\\" + "ComicAssets";
#endif
#ifdef GEODE_IS_ANDROID
        zipPath = geode::Mod::get()->getResourcesDir().string() + "/" + "ComicAssets.zip";
        unzipDir = geode::Mod::get()->getResourcesDir().string() + "/" + "ComicAssets";
#endif

        auto result = geode::utils::file::Unzip::intoDir(zipPath, unzipDir);

        CCFileUtils::get()->addTexturePack(CCTexturePack{
            .m_id = this->getID(),
            .m_paths = {unzipDir}});

        auto *textureCache = CCTextureCache::sharedTextureCache();
        auto *spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();

        //  Proceso para meter todas las paginas
        for (auto ii = 0; ii < 6; ii++)
        {
            auto max = (ii == 0)   ? 9
                       : (ii == 1) ? 5
                       : (ii == 2) ? 4
                       : (ii == 3) ? 4
                       : (ii == 4) ? 9
                                   : 6;

            //  Agrega todas las paginas del comic al cache
            for (auto jj = 0; jj < max; jj++)
            {
                log::debug("    Loading Comic: {} - Page: {}", ii, jj);

                auto pageENG = fmt::format("Comic_ENG_0{}_0{:02}.png"_spr, ii + 1, jj + 1);
                auto pageSPA = fmt::format("Comic_SPA_0{}_0{:02}.png"_spr, ii + 1, jj + 1);

                textureCache->addImage(pageENG.c_str(), false);
                textureCache->addImage(pageSPA.c_str(), false);
            }
        }

        textureCache->addImage("Comic_Error.png"_spr, false);
        log::debug("Comic files succesfully loaded");
    }

    void
    addCustomIconCredits()
    {
        auto gs = GameStatsManager::sharedState();
        gs->m_usernameForAccountID.insert(std::make_pair(14178231, "Danky99"));
        gs->m_usernameForAccountID.insert(std::make_pair(18718615, "AngelozDD"));
        gs->m_usernameForAccountID.insert(std::make_pair(13284787, "MinoX28"));

        //  Cubes
        for (int i = 486; i < 493; i++)
            Odyssey::addCreditsToIcon(std::make_pair(i, UnlockType::Cube), (int)Artist::Danky);
        Odyssey::addCreditsToIcon(std::make_pair(493, UnlockType::Cube), (int)Artist::Minox);  // MinoX
        Odyssey::addCreditsToIcon(std::make_pair(494, UnlockType::Cube), (int)Artist::ML500);  // ML5
        Odyssey::addCreditsToIcon(std::make_pair(495, UnlockType::Cube), (int)Artist::Cyan);   // Cyan
        Odyssey::addCreditsToIcon(std::make_pair(496, UnlockType::Cube), (int)Artist::Angelo); // Angelo
        Odyssey::addCreditsToIcon(std::make_pair(497, UnlockType::Cube), (int)Artist::Angelo); // Angelo
        for (int i = 498; i < 503; i++)
            Odyssey::addCreditsToIcon(std::make_pair(i, UnlockType::Cube), (int)Artist::Danky);
        Odyssey::addCreditsToIcon(std::make_pair(503, UnlockType::Cube), (int)Artist::Minox);  // MinoX
        Odyssey::addCreditsToIcon(std::make_pair(504, UnlockType::Cube), (int)Artist::Danky);  // Danky
        Odyssey::addCreditsToIcon(std::make_pair(505, UnlockType::Cube), (int)Artist::Danky);  // Danky
        Odyssey::addCreditsToIcon(std::make_pair(506, UnlockType::Cube), (int)Artist::Danky);  // Danky
        Odyssey::addCreditsToIcon(std::make_pair(507, UnlockType::Cube), (int)Artist::Danky);  // Danky
        Odyssey::addCreditsToIcon(std::make_pair(508, UnlockType::Cube), (int)Artist::Cyan);   // Cyan
        Odyssey::addCreditsToIcon(std::make_pair(509, UnlockType::Cube), (int)Artist::Cyan);   // Cyan
        Odyssey::addCreditsToIcon(std::make_pair(510, UnlockType::Cube), (int)Artist::Cyan);   // Cyan
        Odyssey::addCreditsToIcon(std::make_pair(511, UnlockType::Cube), (int)Artist::Angelo); // Angelo
        Odyssey::addCreditsToIcon(std::make_pair(512, UnlockType::Cube), (int)Artist::Cyan);   // Cyan
        Odyssey::addCreditsToIcon(std::make_pair(513, UnlockType::Cube), (int)Artist::ML500);  // ML5
        Odyssey::addCreditsToIcon(std::make_pair(514, UnlockType::Cube), (int)Artist::Danky);  // Danky

        //  Ships
        Odyssey::addCreditsToIcon(std::make_pair(170, UnlockType::Ship), (int)Artist::Danky);  // Danky
        Odyssey::addCreditsToIcon(std::make_pair(171, UnlockType::Ship), (int)Artist::Angelo); // Angelo
        Odyssey::addCreditsToIcon(std::make_pair(172, UnlockType::Ship), (int)Artist::Angelo); // Angelo
        Odyssey::addCreditsToIcon(std::make_pair(173, UnlockType::Ship), (int)Artist::Danky);  // Danky
        Odyssey::addCreditsToIcon(std::make_pair(174, UnlockType::Ship), (int)Artist::ML500);  // ML5
        Odyssey::addCreditsToIcon(std::make_pair(175, UnlockType::Ship), (int)Artist::Angelo); // Angelo
        Odyssey::addCreditsToIcon(std::make_pair(176, UnlockType::Ship), (int)Artist::ML500);  // ML5
        Odyssey::addCreditsToIcon(std::make_pair(177, UnlockType::Ship), (int)Artist::ML500);  // ML5

        //  Balls
        Odyssey::addCreditsToIcon(std::make_pair(119, UnlockType::Ball), (int)Artist::Danky); // Danky
        Odyssey::addCreditsToIcon(std::make_pair(120, UnlockType::Ball), (int)Artist::ML500); // ML5
        Odyssey::addCreditsToIcon(std::make_pair(121, UnlockType::Ball), (int)Artist::Danky); // Danky
        Odyssey::addCreditsToIcon(std::make_pair(122, UnlockType::Ball), (int)Artist::Minox);  // MinoX
        Odyssey::addCreditsToIcon(std::make_pair(123, UnlockType::Ball), (int)Artist::Angelo); // Angelo
        Odyssey::addCreditsToIcon(std::make_pair(124, UnlockType::Ball), (int)Artist::ML500);  // ML5
        Odyssey::addCreditsToIcon(std::make_pair(125, UnlockType::Ball), (int)Artist::ML500);  // ML5
        Odyssey::addCreditsToIcon(std::make_pair(126, UnlockType::Ball), (int)Artist::Cyan);   // Angelo

        //  UFOs
        Odyssey::addCreditsToIcon(std::make_pair(150, UnlockType::Bird), (int)Artist::Angelo); // Angelo
        Odyssey::addCreditsToIcon(std::make_pair(151, UnlockType::Bird), (int)Artist::ML500);  // ML5
        Odyssey::addCreditsToIcon(std::make_pair(152, UnlockType::Bird), (int)Artist::ML500);  // ML5
        Odyssey::addCreditsToIcon(std::make_pair(153, UnlockType::Bird), (int)Artist::Angelo); // Angelo
        Odyssey::addCreditsToIcon(std::make_pair(154, UnlockType::Bird), (int)Artist::Danky);  // Danky

        //  Waves
        Odyssey::addCreditsToIcon(std::make_pair(97, UnlockType::Dart), (int)Artist::Angelo); // Angelo
        Odyssey::addCreditsToIcon(std::make_pair(98, UnlockType::Dart), (int)Artist::Danky);  // Danky
        Odyssey::addCreditsToIcon(std::make_pair(99, UnlockType::Dart), (int)Artist::ML500);  // ML5
        Odyssey::addCreditsToIcon(std::make_pair(100, UnlockType::Dart), (int)Artist::ML500); // ML5

        //  Swings
        Odyssey::addCreditsToIcon(std::make_pair(44, UnlockType::Swing), (int)Artist::Danky); // Danky
        Odyssey::addCreditsToIcon(std::make_pair(45, UnlockType::Swing), (int)Artist::Danky); // Danky
        Odyssey::addCreditsToIcon(std::make_pair(46, UnlockType::Swing), (int)Artist::Danky); // Danky
        Odyssey::addCreditsToIcon(std::make_pair(46, UnlockType::Swing), (int)Artist::ML500); // ML5
        Odyssey::addCreditsToIcon(std::make_pair(47, UnlockType::Swing), (int)Artist::ML500); // ML5

        //  Jetpack
        Odyssey::addCreditsToIcon(std::make_pair(9, UnlockType::Jetpack), (int)Artist::Minox); // MinoX
    }
};