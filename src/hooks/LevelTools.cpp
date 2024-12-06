#include <Geode/Geode.hpp>
#include <Geode/modify/LevelTools.hpp>

using namespace geode::prelude;

class $modify(OdysseyLevelTools, LevelTools)
{
	static gd::string getAudioTitle(int levelID)
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
		case 201:
			return "Burning Sands";
		case 202:
			return "Conclusion";
		default:
			return LevelTools::getAudioTitle(levelID);
		}
	}

	static gd::string getAudioFileName(int levelID)
	{
		switch (levelID)
		{
			case 100:
				return "TheDangerousSeas.mp3"_spr;
			case 101:
				return "GhostHouse.mp3"_spr;
			case 102:
				return "SuperUltra.mp3"_spr;
			case 103:
				return "CryptoFunk.mp3"_spr;
			case 104:
				return "Hellfire.mp3"_spr;
			case 201:
				return "BurningSands.mp3"_spr;
			case 202:
				return "ConclusiveJourney.mp3"_spr;
				
			default:
				return LevelTools::getAudioFileName(levelID);
		}
	}

	static GJGameLevel *getLevel(int levelID, bool loaded)
	{
		GJGameLevel *level = GJGameLevel::create();
		switch (levelID)
		{
		case 1:
			setLevelInfo(level, 6, GJDifficulty::Harder, 0, 0); // The Dangerous Seas
			level->m_levelName = "The Dangerous Seas";
			level->m_audioTrack = 100;
			level->m_coins = 3;
			break;
		case 2:
			setLevelInfo(level, 7, GJDifficulty::Harder, 0, 0); // Ghost House
			level->m_levelName = getAudioTitle(102);
			level->m_audioTrack = 101;
			level->m_coins = 3;
			break;
		case 3:
			setLevelInfo(level, 8, GJDifficulty::Insane, 0, 0); // Super Ultra
			level->m_levelName = getAudioTitle(103);
			level->m_audioTrack = 102;
			level->m_coins = 3;
			break;
		case 4:
			setLevelInfo(level, 9, GJDifficulty::Insane, 0, 0); // Cryptofunk
			level->m_levelName = getAudioTitle(104);
			level->m_audioTrack = 103;
			level->m_coins = 3;
			break;
		case 5:
			setLevelInfo(level, 6, GJDifficulty::Harder, 0, 0); // Hellfire
			level->m_levelName = getAudioTitle(105);
			level->m_audioTrack = 104;
			level->m_coins = 3;
			break;
		case 6:
			setLevelInfo(level, 7, GJDifficulty::Harder, 0, 0); // Boss Rush
			level->m_levelName = getAudioTitle(106);
			level->m_audioTrack = 105;
			level->m_coins = 3;
			break;
		case 7:
			setLevelInfo(level, 8, GJDifficulty::Insane, 0, 0); // Frostbite
			level->m_levelName = getAudioTitle(107);
			level->m_audioTrack = 106;
			level->m_coins = 3;
			break;
		case 8:
			setLevelInfo(level, 9, GJDifficulty::Insane, 0, 0); // Super Wubtendo
			level->m_levelName = getAudioTitle(108);
			level->m_audioTrack = 107;
			level->m_coins = 3;
			break;
		case 201:
			setLevelInfo(level, 10, GJDifficulty::Demon, 0, 0); // Burning Sands
			level->m_levelName = getAudioTitle(201);
			level->m_audioTrack = 201;
			level->m_demon = 1;
			level->m_coins = 3;
			break;
		case 202:
			setLevelInfo(level, 8, GJDifficulty::Insane, 0, 0); // Conclusive Journey
			level->m_levelName = "Conclusive Journey";
			level->m_audioTrack = 202;
			level->m_coins = 3;
			break;
		}

		if (!loaded)
		{
			level->m_levelString = LocalLevelManager::sharedState()->getMainLevelString(levelID);
		}
		level->m_levelID = levelID;
		level->m_levelType = GJLevelType::Local;

		return level;
	};

	static void setLevelInfo(GJGameLevel *level, int stars, GJDifficulty difficulty, int coinsRequired, int frameTime)
	{
		level->m_stars = stars;
		level->m_difficulty = difficulty;
		level->m_requiredCoins = coinsRequired;
		level->m_timestamp = frameTime;
	};

	static bool verifyLevelIntegrity(std::string verifyString, int levelID)
	{
		return true;
	}

	static gd::string getAudioString(int levelID)
	{
		return LevelTools::getAudioString(99 + levelID);
	}
};