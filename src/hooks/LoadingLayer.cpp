#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <filesystem>
#include <iostream>
#include "../utils/Utils.hpp"
#include "../utils/IconUtils.hpp"

using namespace geode::prelude;

enum class Artist
{
    ML500 = 2102,
    Minox = 13284787,
    Danky = 14178231,
    Angelo = 18718615,
    Cyan = 21113321,
    Retro = 617383
};

class $modify(OdysseyLoadingLayer, LoadingLayer)
{
    bool init(bool reload)
    {
        if (!LoadingLayer::init(reload))
            return false;

//  Solo para el mod en Modo desarrollador
#ifndef DEVELOPER_MODE
        Mod::get()->setSavedValue<bool>("developer-version", false);
		Mod::get()->setSavedSetting<bool>("dev-mode", false);
#endif

#ifdef DEVELOPER_MODE
        Mod::get()->setSavedValue<bool>("developer-version", true);
#endif

        auto SFC = CCSpriteFrameCache::get();
        auto searchPathRoot = dirs::getModRuntimeDir() / Mod::get()->getID() / "resources";
        CCFileUtils::sharedFileUtils()->addSearchPath(searchPathRoot.string().c_str());
        SFC->addSpriteFramesWithFile("GDO_GameSheet01.plist"_spr);

        //  Loads the assets
        OdysseyLoadingLayer::addCustomIconCredits();
        OdysseyLoadingLayer::addOdysseyAssets();
        OdysseyLoadingLayer::loadStats();

        //  Adds the version of the fangame at the bottom left
        auto version = CCLabelBMFont::create(fmt::format("{}", Mod::get()->getVersion().toVString(true)).c_str(), "goldFont.fnt");
        version->setPosition({5, 5});
        version->setAnchorPoint({0, 0});
        version->setScale(0.75f);
        this->addChild(version);

        //  Modifies the sprites
        auto mainTitle = static_cast<CCSprite *>(this->getChildByID("gd-logo"));
        if (mainTitle)
        {
            auto odysseyTitle = CCSprite::createWithSpriteFrameName("MainLogo_001.png"_spr);
            mainTitle->setDisplayFrame(odysseyTitle->displayFrame());
        }

        auto robtopLogo = static_cast<CCSprite *>(this->getChildByID("robtop-logo"));
        if (robtopLogo)
        {
            auto teamLogo = CCSprite::createWithSpriteFrameName("TeamLogo_Big_001.png"_spr);
            robtopLogo->setDisplayFrame(teamLogo->displayFrame());
        };

        return true;
    }

    const char *getLoadingString()
    {
        if (m_fromRefresh)
            return LoadingLayer::getLoadingString();

        std::vector<const char *> messages =
            {
                "Remember to play\nNukebound first!",
                "Increasing the amount\nof mod incompatibilities...",
                "Are you recording this\nright now?",
                "Explorers, the failed promise...",
                "Adding more wanted posters\non the shop",
                "Why the vaults talk about\nthis random gal?",
                "I wonder what game theory\nthinks about this",
                "Pray for the programmers...",
                "If something breaks,\nblame it on Chumiu",
                "This mod is dedicated to MDK :)",
                "Some vault codes are based on\nMDK's lore in his website",
                "Mathi Approved",
            };

        int rand = (std::rand() % messages.size());
        return messages[rand];
    };

    void addOdysseyAssets()
    {
        auto zipFilePath = Mod::get()->getResourcesDir() / "Assets.zip";
        auto unzipDir = Mod::get()->getResourcesDir();
        auto result = utils::file::Unzip::intoDir(zipFilePath, unzipDir, true);

        //  Loads the sheets as a texture pack
        CCFileUtils::get()->addTexturePack(CCTexturePack{
            .m_id = Mod::get()->getID(),
            .m_paths = {string::pathToString(Mod::get()->getResourcesDir())}});
        log::info("Odyssey Textures loaded");

        log::debug("Loading Assets...");
        auto SFC = CCSpriteFrameCache::get();

        //  Icons
        for (int ii = 486; ii <= 520; ii++)
            SFC->addSpriteFramesWithFile(fmt::format("player_{}.plist", ii).c_str());

        for (int ii = 170; ii <= 179; ii++)
            SFC->addSpriteFramesWithFile(fmt::format("ship_{}.plist", ii).c_str());

        for (int ii = 119; ii <= 130; ii++)
            SFC->addSpriteFramesWithFile(fmt::format("player_ball_{}.plist", ii).c_str());

        for (int ii = 150; ii <= 159; ii++)
            SFC->addSpriteFramesWithFile(fmt::format("bird_{}.plist", ii).c_str());

        for (int ii = 97; ii <= 102; ii++)
            SFC->addSpriteFramesWithFile(fmt::format("dart_{}.plist", ii).c_str());

        for (int ii = 44; ii <= 48; ii++)
            SFC->addSpriteFramesWithFile(fmt::format("swing_{}.plist", ii).c_str());

        SFC->addSpriteFramesWithFile("jetpack_09.plist");

        //  Custom Modes
        SFC->addSpriteFramesWithFile("boat_01.plist");
        SFC->addSpriteFramesWithFile("drone_01.plist");
        SFC->addSpriteFramesWithFile("slider_01.plist");
        SFC->addSpriteFramesWithFile("minecart_01.plist");

        log::info("Odyssey Icons Loaded");
    }

    void addCustomIconCredits()
    {
        auto gs = GameStatsManager::sharedState();
        gs->m_usernameForAccountID.insert(std::make_pair(14178231, "Danky99"));
        gs->m_usernameForAccountID.insert(std::make_pair(18718615, "AngelozDD"));
        gs->m_usernameForAccountID.insert(std::make_pair(13284787, "MinoX28"));

        //  Cubes
        for (int i = 486; i < 493; i++)
            IconUtils::addCredits(std::make_pair(i, UnlockType::Cube), (int)Artist::Danky);
        IconUtils::addCredits(std::make_pair(493, UnlockType::Cube), (int)Artist::Minox);  // MinoX
        IconUtils::addCredits(std::make_pair(494, UnlockType::Cube), (int)Artist::ML500);  // ML5
        IconUtils::addCredits(std::make_pair(495, UnlockType::Cube), (int)Artist::Cyan);   // Cyan
        IconUtils::addCredits(std::make_pair(496, UnlockType::Cube), (int)Artist::Angelo); // Angelo
        IconUtils::addCredits(std::make_pair(497, UnlockType::Cube), (int)Artist::Angelo); // Angelo

        for (int i = 498; i < 503; i++)
            IconUtils::addCredits(std::make_pair(i, UnlockType::Cube), (int)Artist::Danky);

        IconUtils::addCredits(std::make_pair(503, UnlockType::Cube), (int)Artist::Minox);  // MinoX
        IconUtils::addCredits(std::make_pair(504, UnlockType::Cube), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(505, UnlockType::Cube), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(506, UnlockType::Cube), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(507, UnlockType::Cube), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(508, UnlockType::Cube), (int)Artist::Cyan);   // Cyan
        IconUtils::addCredits(std::make_pair(509, UnlockType::Cube), (int)Artist::Cyan);   // Cyan
        IconUtils::addCredits(std::make_pair(510, UnlockType::Cube), (int)Artist::Cyan);   // Cyan
        IconUtils::addCredits(std::make_pair(511, UnlockType::Cube), (int)Artist::Angelo); // Angelo
        IconUtils::addCredits(std::make_pair(512, UnlockType::Cube), (int)Artist::Cyan);   // Cyan
        IconUtils::addCredits(std::make_pair(513, UnlockType::Cube), (int)Artist::ML500);  // ML5
        IconUtils::addCredits(std::make_pair(514, UnlockType::Cube), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(515, UnlockType::Cube), (int)Artist::Retro);  // Retro
        IconUtils::addCredits(std::make_pair(516, UnlockType::Cube), (int)Artist::Cyan);   // Cyan
        IconUtils::addCredits(std::make_pair(517, UnlockType::Cube), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(518, UnlockType::Cube), (int)Artist::Cyan);   // Cyan
        IconUtils::addCredits(std::make_pair(519, UnlockType::Cube), (int)Artist::Cyan);   // Cyan

        //  Ships
        IconUtils::addCredits(std::make_pair(170, UnlockType::Ship), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(171, UnlockType::Ship), (int)Artist::Angelo); // Angelo
        IconUtils::addCredits(std::make_pair(172, UnlockType::Ship), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(173, UnlockType::Ship), (int)Artist::ML500);  // ML5
        IconUtils::addCredits(std::make_pair(174, UnlockType::Ship), (int)Artist::Angelo); // Angelo
        IconUtils::addCredits(std::make_pair(175, UnlockType::Ship), (int)Artist::ML500);  // ML5
        IconUtils::addCredits(std::make_pair(176, UnlockType::Ship), (int)Artist::Angelo); // Angelo
        IconUtils::addCredits(std::make_pair(177, UnlockType::Ship), (int)Artist::ML500);  // ML5
        IconUtils::addCredits(std::make_pair(178, UnlockType::Ship), (int)Artist::ML500);  // ML5
        IconUtils::addCredits(std::make_pair(179, UnlockType::Ship), (int)Artist::Cyan);   // Cyan

        //  Balls
        IconUtils::addCredits(std::make_pair(119, UnlockType::Ball), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(120, UnlockType::Ball), (int)Artist::ML500);  // ML5
        IconUtils::addCredits(std::make_pair(121, UnlockType::Ball), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(122, UnlockType::Ball), (int)Artist::Minox);  // MinoX
        IconUtils::addCredits(std::make_pair(123, UnlockType::Ball), (int)Artist::Angelo); // Angelo
        IconUtils::addCredits(std::make_pair(124, UnlockType::Ball), (int)Artist::ML500);  // ML5
        IconUtils::addCredits(std::make_pair(125, UnlockType::Ball), (int)Artist::ML500);  // ML5
        IconUtils::addCredits(std::make_pair(126, UnlockType::Ball), (int)Artist::Cyan);   // Angelo
        IconUtils::addCredits(std::make_pair(127, UnlockType::Ball), (int)Artist::ML500);  // ML5
        IconUtils::addCredits(std::make_pair(128, UnlockType::Ball), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(129, UnlockType::Ball), (int)Artist::Retro);  // Retro
        IconUtils::addCredits(std::make_pair(130, UnlockType::Ball), (int)Artist::Angelo); // Angelo

        //  UFOs
        IconUtils::addCredits(std::make_pair(150, UnlockType::Bird), (int)Artist::Angelo); // Angelo
        IconUtils::addCredits(std::make_pair(151, UnlockType::Bird), (int)Artist::ML500);  // ML5
        IconUtils::addCredits(std::make_pair(152, UnlockType::Bird), (int)Artist::ML500);  // ML5
        IconUtils::addCredits(std::make_pair(153, UnlockType::Bird), (int)Artist::Angelo); // Angelo
        IconUtils::addCredits(std::make_pair(154, UnlockType::Bird), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(155, UnlockType::Bird), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(156, UnlockType::Bird), (int)Artist::Angelo); // Angelo
        IconUtils::addCredits(std::make_pair(157, UnlockType::Bird), (int)Artist::Cyan);   // Cyan
        IconUtils::addCredits(std::make_pair(158, UnlockType::Bird), (int)Artist::Angelo); // Angelo
        IconUtils::addCredits(std::make_pair(159, UnlockType::Bird), (int)Artist::ML500);  // ML5

        //  Waves
        IconUtils::addCredits(std::make_pair(97, UnlockType::Dart), (int)Artist::Angelo); // Angelo
        IconUtils::addCredits(std::make_pair(98, UnlockType::Dart), (int)Artist::Danky);  // Danky
        IconUtils::addCredits(std::make_pair(99, UnlockType::Dart), (int)Artist::ML500);  // ML5
        IconUtils::addCredits(std::make_pair(100, UnlockType::Dart), (int)Artist::ML500); // ML5
        IconUtils::addCredits(std::make_pair(101, UnlockType::Dart), (int)Artist::ML500); // ML5
        IconUtils::addCredits(std::make_pair(102, UnlockType::Dart), (int)Artist::ML500); // ML5

        //  Swings
        IconUtils::addCredits(std::make_pair(44, UnlockType::Swing), (int)Artist::Danky); // Danky
        IconUtils::addCredits(std::make_pair(45, UnlockType::Swing), (int)Artist::Danky); // Danky
        IconUtils::addCredits(std::make_pair(46, UnlockType::Swing), (int)Artist::Danky); // Danky
        IconUtils::addCredits(std::make_pair(46, UnlockType::Swing), (int)Artist::ML500); // ML5
        IconUtils::addCredits(std::make_pair(47, UnlockType::Swing), (int)Artist::ML500); // ML5
        IconUtils::addCredits(std::make_pair(48, UnlockType::Swing), (int)Artist::Danky); // Danky

        //  Jetpack
        IconUtils::addCredits(std::make_pair(9, UnlockType::Jetpack), (int)Artist::Minox); // MinoX
    }

    void loadStats()
    {
        auto GM = GameManager::sharedState();
        auto GSM = GameStatsManager::sharedState();

        //  If there's account data found, disables the rest of this function.
        if (GJAccountManager::sharedState()->m_accountID != 0)
        {
            log::error("Account of data found, disabling the loading stats of the fangame to risk modified savefiles");
            Mod::get()->setSavedValue<bool>("disable-fangame", true);
            return;
        }

        //  Just as a safeguard.
        Mod::get()->setSavedValue<bool>("disable-fangame", false);

        //  The flag of the "Accepting TOS" of the game.
        if (!GM->getUGV("30"))
            GM->setUGV("30", true);

        //  The flag of the first shopkeeper dialog (Collecting 500 orbs).
        if (!GM->getUGV("17"))
            GM->setUGV("17", true);

        GameManager::sharedState()->setIntGameVariable("1001", 0);

        //  Verifies if the extra levels has any progress.
        auto extraLevel1 = GameLevelManager::sharedState()->getMainLevel(7501, false);
        auto extraLevel2 = GameLevelManager::sharedState()->getMainLevel(7502, false);

        if ((extraLevel1->m_normalPercent > 0 || extraLevel1->m_practicePercent > 0) && !GameManager::sharedState()->getUGV("237"))
            GameManager::sharedState()->setUGV("237", true);

        if ((extraLevel2->m_normalPercent > 0 || extraLevel2->m_practicePercent > 0) && !GameManager::sharedState()->getUGV("238"))
            GameManager::sharedState()->setUGV("238", true);

        //  Hands the orbs.
        if (auto orbs = Mod::get()->getSavedValue<int>("Orbs"))
            GSM->setStat("14", orbs);

        //  To ensure that the shop items are shown as bought.
        for (auto ii = 1; ii <= 21; ii++)
        {
            if (Mod::get()->getSavedValue<int>(fmt::format("store-item-{:02}", ii)) > 0)
            {
                auto var = CCString::createWithFormat("%i", Mod::get()->getSavedValue<int>(fmt::format("store-item-{:02}", ii)));
                GSM->m_purchasedItems->setObject(var, fmt::format("{}", ii));
            }
        }

        Odyssey::verifyVaultHints();
    }
};