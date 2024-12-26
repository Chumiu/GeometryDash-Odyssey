#include <Geode/Geode.hpp>
#include <Geode/modify/LevelTools.hpp>

using namespace geode::prelude;

class $modify(OdysseyLevelTools, LevelTools)
{
	static bool verifyLevelIntegrity(std::string verifyString, int levelID)
	{
		return true;
	}

	$override static gd::string getAudioTitle(int levelID)
	{
		switch (levelID)
		{
		case 101:
			return "The Seven Seas";
		case 102:
			return "Ghost House";
		case 103:
			return "Super Ultra";
		case 104:
			return "Cryptofunk";
		case 105:
			return "Hellfire";
		case 106:
			return "Boss Rush";
		case 107:
			return "Absolute Zero";
		case 108:
			return "Comfort Food";
		case 109:
			return "Critical Hit";

		case 501:
			return "Conclusion";
		case 502:
			return "Burning Sands";
		case 503:
			return "Super Wubtendo";

		default:
			return LevelTools::getAudioTitle(levelID);
		}
	}

	$override static gd::string getAudioFileName(int levelID)
	{
		switch (levelID)
		{
		case 101:
			return "10009443.ogg"_spr;
		case 102:
			return "GhostHouse.mp3"_spr;
		case 103:
			return "10007255.ogg"_spr;
		case 104:
			return "10007201.ogg"_spr;
		case 105:
			return "10007222.mp3"_spr;
		case 106:
			return "10007196.ogg"_spr;
		case 107:
			return "10007188.ogg"_spr;
		case 108:
			return "10012389.ogg"_spr;
		case 109:
			return "10007200.ogg"_spr;

		case 501:
			return "ConclusiveJourney.mp3"_spr;
		case 502:
			return "BurningSands.mp3"_spr;
		case 503:
			return "SuperWubtendo.mp3"_spr;

		default:
			return LevelTools::getAudioFileName(levelID);
		}
	}

	$override static int artistForAudio(int p0)
	{
		switch (p0)
		{
		case 101:
			return 6;
		case 102:
			return 12;
		case 103:
			return 7;
		case 104:
			return 7;
		case 105:
			return 7;
		case 106:
			return 7;
		case 107:
			return 7;
		case 108:
			return 7;
		case 109:
			return 7;

		case 501:
			return 1;
		case 502:
			return 9;
		case 503:
			return 7;

		default:
			return LevelTools::artistForAudio(p0);
		}
	}

	$override static gd::string nameForArtist(int p0)
	{
		switch (p0)
		{
		case 12:
			return "Schtiffles";
		default:
			return LevelTools::nameForArtist(p0);
		}
	}

	$override static gd::string ngURLForArtist(int p0)
	{
		switch (p0)
		{
		case 12:
			return "https://schtiffles.newgrounds.com";
		default:
			return LevelTools::ngURLForArtist(p0);
		}
	}

	$override static GJGameLevel *getLevel(int levelID, bool loaded)
	{
		GJGameLevel *level = GJGameLevel::create();
		switch (levelID)
		{
		case 7001: // The Dangerous Seas
			level->m_levelName = "The Dangerous Seas";
			level->m_audioTrack = 101;
			level->m_stars = 6;
			level->m_difficulty = GJDifficulty::Hard;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;

		case 7002: // Ghost House
			level->m_levelName = getAudioTitle(102);
			level->m_audioTrack = 102;
			level->m_stars = 8;
			level->m_difficulty = GJDifficulty::Harder;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;

		case 7003: // Super Ultra
			level->m_levelName = getAudioTitle(103);
			level->m_audioTrack = 103;
			level->m_stars = 10;
			level->m_difficulty = GJDifficulty::Insane;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;

		case 7004: // Cryptofunk
			level->m_levelName = getAudioTitle(104);
			level->m_audioTrack = 104;
			level->m_stars = 12;
			level->m_difficulty = GJDifficulty::Insane;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;

		case 7005: // Hellfire
			level->m_levelName = getAudioTitle(105);
			level->m_audioTrack = 105;
			level->m_stars = 10;
			level->m_difficulty = GJDifficulty::Harder;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;

		case 7006: // Boss Rush
			level->m_levelName = getAudioTitle(106);
			level->m_audioTrack = 106;
			level->m_stars = 8;
			level->m_difficulty = GJDifficulty::Harder;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;

		case 7007: // Absolute Zero
			level->m_levelName = getAudioTitle(107);
			level->m_audioTrack = 107;
			level->m_stars = 10;
			level->m_difficulty = GJDifficulty::Harder;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;

		case 7008: // Comfort Food
			level->m_levelName = getAudioTitle(108);
			level->m_audioTrack = 108;
			level->m_stars = 12;
			level->m_difficulty = GJDifficulty::Insane;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;

		case 7009: // Critical Hit
			level->m_levelName = getAudioTitle(109);
			level->m_audioTrack = 109;
			level->m_stars = 15;
			level->m_difficulty = GJDifficulty::Demon;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_demon = 1;
			level->m_coins = 3;
			break;

		case 7501: // Conclusive Journey
			level->m_levelName = "Conclusive Journey";
			level->m_audioTrack = 501;
			level->m_stars = 10;
			level->m_difficulty = GJDifficulty::Harder;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;

		case 7502: // Burning Sands
			level->m_levelName = getAudioTitle(502);
			level->m_audioTrack = 502;
			level->m_stars = 15;
			level->m_difficulty = GJDifficulty::Demon;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_demon = 1;
			level->m_coins = 3;
			break;

		case 7503: // Super Wubtendo
			level->m_levelName = getAudioTitle(503);
			level->m_audioTrack = 503;
			level->m_stars = 12;
			level->m_difficulty = GJDifficulty::Insane;
			level->m_requiredCoins = 0;
			level->m_timestamp = 0;
			level->m_coins = 3;
			break;
		}

		if (!loaded)
			level->m_levelString = LocalLevelManager::sharedState()->getMainLevelString(levelID);

		level->m_levelID = levelID;
		level->m_levelType = GJLevelType::Local;

		return level;
	};

	$override static gd::string getAudioString(int levelID)
	{
		if (levelID > 7500)
			return LevelTools::getAudioString(levelID);

		return LevelTools::getAudioString(99 + levelID);
	}

	$override static gd::string urlForAudio(int songID)
	{
		switch (songID)
		{
		case 101:
			return "https://youtu.be/izovSb5Z7lw?si=2ybicOLa5N8m5leC"; // The Dangerous Seas
		case 102:
			return "https://youtu.be/F5C6GIZkm64?si=fNWOMGENJ3A-pFIo"; // Ghost House
		case 103:
			return "https://youtu.be/PLEQGywWbV0?si=R46Lun6Sc_Csiiey"; // Super Ultra
		case 104:
			return "https://youtu.be/l3UnRInJuMY?si=k0Zn66wZf9ZgTvP-"; // CryptoFunk
		case 105:
			return "https://youtu.be/wLOMwg0FPLA?si=TjTTz2g-XJvHWdON"; // Hellfire
		case 106:
			return "https://youtu.be/CxPFyu5AGng?si=2ZSWgul-Du_hI47u"; // Boss Rush
		case 107:
			return "https://youtu.be/5jt10MW1mFU?si=IHQcPTaB9KSimznE"; // Absolute Zero
		case 108:
			return "https://youtu.be/qmhv7hQmID4?si=kH9YP1Yijb-u5qIK"; // Comfort Food
		case 109:
			return "https://youtu.be/rQZinpJoiYQ?si=w3xg-WNM5J9Q2-se"; // Critical Hit
		case 110:
			return "https://www.newgrounds.com/audio/listen/678590"; // Harmony Of The Heart

		case 501:
			return "https://youtu.be/BcoURwJr9PI?si=Mb3Zi1azTN2bbrYE"; // Conclusive
		case 502:
			return "https://youtu.be/gyxh9R59oj4?si=IhxSU7XQvwJX32z3"; // Burning Sands
		case 503:
			return "https://youtu.be/EnmAuu92RKo?si=Ywq4DfaiC0f2jr2d"; // Super Wubtendo

		default:
			return LevelTools::urlForAudio(songID);
		}
	}
};