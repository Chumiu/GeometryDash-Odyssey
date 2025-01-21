#include <Geode/Geode.hpp>
#include <Geode/modify/AchievementManager.hpp>

class $modify(OdysseyAchievementManager, AchievementManager)
{
	void addManualAchievements()
	{
		//	First Island
		AchievementManager::addAchievement("geometry.ach.level01a", "All hands on deck!", "Completed \"The Dangerous Seas\" in practice mode", "Complete \"The Dangerous Seas\" in practice mode", "icon_486", 1);
		AchievementManager::addAchievement("geometry.ach.level01b", "The Dangerous Seas!", "Completed \"The Dangerous Seas\" in normal mode", "Complete \"The Dangerous Seas\" in normal mode", "icon_487", 1);

		AchievementManager::addAchievement("geometry.ach.level02a", "Spooky butts...", "Completed \"Ghost House\" in practice mode", "Complete \"Ghost House\" in practice mode", "icon_488", 1);
		AchievementManager::addAchievement("geometry.ach.level02b", "Ghost House!", "Completed \"Ghost House\" in normal mode", "Complete \"Ghost House\" in normal mode", "icon_489", 1);

		AchievementManager::addAchievement("geometry.ach.level03a", "Underpowered", "Completed \"Super Ultra\" in practice mode", "Complete \"Super Ultra\" in practice mode", "icon_490", 1);
		AchievementManager::addAchievement("geometry.ach.level03b", "Super Ultra!", "Completed \"Super Ultra\" in normal mode", "Complete \"Super Ultra\" in normal mode", "ball_119", 1);

		AchievementManager::addAchievement("geometry.ach.level04a", "Digital Disco", "Completed \"Cryptofunk\" in practice mode", "Complete \"Cryptofunk\" in practice mode", "icon_491", 1);
		AchievementManager::addAchievement("geometry.ach.level04b", "Cryptofunk!", "Completed \"Cryptofunk\" in normal mode", "Complete \"Cryptofunk\" in normal mode", "icon_492", 1);

		//	Second island
		AchievementManager::addAchievement("geometry.ach.level05a", "Jungle Japes", "Completed \"Hellfire\" in practice mode", "Complete \"Hellfire\" in practice mode", "icon_493", 1);
		AchievementManager::addAchievement("geometry.ach.level05b", "Hellfire!", "Completed \"Hellfire\" in normal mode", "Complete \"Hellfire\" in normal mode", "ship_170", 1);

		AchievementManager::addAchievement("geometry.ach.level06a", "All Bosses (No Damage)", "Completed \"Boss Rush\" in practice mode", "Complete \"Boss Rush\" in practice mode", "icon_494", 1);
		AchievementManager::addAchievement("geometry.ach.level06b", "Boss Rush!", "Completed \"Boss Rush\" in normal mode", "Complete \"Boss Rush\" in normal mode", "ship_171", 1);

		AchievementManager::addAchievement("geometry.ach.level07a", "I'm freezing here...", "Completed \"Absolute Zero\" in practice mode", "Complete \"Absolute Zero\" in practice mode", "icon_495", 1);
		AchievementManager::addAchievement("geometry.ach.level07b", "Absolute Zero!", "Completed \"Absolute Zero\" in normal mode", "Complete \"Absolute Zero\" in normal mode", "ball_120", 1);

		AchievementManager::addAchievement("geometry.ach.level08a", "Yummers", "Completed \"Comfort Food\" in practice mode", "Complete \"Comfort Food\" in practice mode", "icon_496", 1);
		AchievementManager::addAchievement("geometry.ach.level08b", "Comfort Food!", "Completed \"Comfort Food\" in normal mode", "Complete \"Comfort Food\" in normal mode", "swing_44", 1);

		AchievementManager::addAchievement("geometry.ach.level09a", "Bonus Round", "Completed \"Critical Hit\" in practice mode", "Complete \"Critical Hit\" in practice mode", "dart_97", 1);
		AchievementManager::addAchievement("geometry.ach.level09b", "Critical Hit!", "Completed \"Critical Hit\" in normal mode", "Complete \"Critical Hit\" in normal mode", "icon_497", 1);
		AchievementManager::addAchievement("geometry.ach.level09c", "Ultimate Critical Hit!", "Completed \"Critical Hit\" with all coins", "Complete \"Critical Hit\" with all coins", "ship_172", 1);

		//	Extra Levels
		AchievementManager::addAchievement("geometry.ach.level501a", "End of the Road", "Completed \"Conclusive Journey\" in practice mode", "Complete \"Conclusive Journey\" in practice mode", "icon_498", 1);
		AchievementManager::addAchievement("geometry.ach.level501b", "Conclusive Journey!", "Completed \"Conclusive Journey\" in normal mode", "Complete \"Conclusive Journey\" in normal mode", "swing_45", 1);

		AchievementManager::addAchievement("geometry.ach.level502a", "Neferkitty's curse", "Completed \"Burning Sands\" in practice mode", "Complete \"Burning Sands\" in practice mode", "dart_98", 1);
		AchievementManager::addAchievement("geometry.ach.level502b", "Burning Sands!", "Completed \"Burning Sands\" in normal mode", "Complete \"Burning Sands\" in normal mode", "ship_173", 1);
		AchievementManager::addAchievement("geometry.ach.level502c", "Ultimate Burning Sands", "Completed \"Burning Sands\" with all coins", "Complete \"Burning Sands\" with all coins", "icon_499", 1);

		//  Contest Islands
		AchievementManager::addAchievement("geometry.ach.level601b", "Eclipse!", "Completed \"Eclipse\" in normal mode", "Complete \"Eclipse\" in normal mode", "ball_128", 1);
		AchievementManager::addAchievement("geometry.ach.level602b", "Jelly Castle!", "Completed \"Jelly Castle\" in normal mode", "Complete \"Jelly Castle\" in normal mode", "", 1);
		AchievementManager::addAchievement("geometry.ach.level603b", "Phone me First!", "Completed \"Phone me First\" in normal mode", "Complete \"Phone me First\" in normal mode", "swing_48", 1);
		AchievementManager::addAchievement("geometry.ach.level604b", "Wubsplosion!", "Completed \"Wubsplosion\" in normal mode", "Complete \"Wubsplosion\" in normal mode", "icon_516", 1);

		//  Secret Coins
		AchievementManager::addAchievement("geometry.ach.coins01", "Oh, these again!", "Collected 5 Secret Coins", "Collect 5 Secret Coins", "icon_517", 1);
		AchievementManager::addAchievement("geometry.ach.coins02", "Did I miss a key?", "Collected 10 Secret Coins", "Collect 10 Secret Coins", "ball_129", 1);
		AchievementManager::addAchievement("geometry.ach.coins03", "Hollow's Payday", "Collected 15 Secret Coins", "Collect 15 Secret Coins", "ship_178", 1);
		AchievementManager::addAchievement("geometry.ach.coins04", "Will Colon review these?", "Collected 20 Secret Coins", "Collect 20 Secret Coins", "bird_155", 1);
		AchievementManager::addAchievement("geometry.ach.coins05", "That one drone coin...", "Collected 25 Secret Coins", "Collect 25 Secret Coins", "", 1);
		AchievementManager::addAchievement("geometry.ach.coins06", "Pocket Change", "Collected 30 Secret Coins", "Collect 30 Secret Coins", "", 1);
		AchievementManager::addAchievement("geometry.ach.coins07", "Piggy Bank", "Collected 35 Secret Coins", "Collect 35 Secret Coins", "", 1);
		AchievementManager::addAchievement("geometry.ach.coins08", "Rent's Due", "Collected 40 Secret Coins", "Collect 40 Secret Coins", "", 1);

		//  Ogre
		AchievementManager::addAchievement("geometry.ach.odyssey.secret01", "Odyssey, ya see!", "Found the secret!", "It's a secret...", "bird_150", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret02", "Threat from the stars", "Found the secret!", "It's a secret...", "bird_151", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret03", "Finish him!", "Found the secret!", "It's a secret...", "icon_508", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret04", "Funny old man!", "Found the secret!", "It's a secret...", "icon_509", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret05", "Annoying robot", "Found the secret!", "It's a secret...", "ball_123", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret06", "Sightless Kitsune", "Found the secret!", "It's a secret...", "icon_510", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret07", "Seven years...", "Found the secret!", "It's a secret...", "bird_152", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret08", "Global energy", "Found the secret!", "It's a secret...", "bird_153", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret09", "Devil's lair", "Found the secret!", "It's a secret...", "ball_124", 1);

		//  Hollow
		AchievementManager::addAchievement("geometry.ach.odyssey.secret10", "Rainbow power!", "Found the secret!", "It's a secret...", "ball_125", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret11", "Coming soon", "Found the secret!", "It's a secret...", "jetpack_09", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret12", "Mortal", "Found the secret!", "It's a secret...", "icon_511", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret13", "About her", "Found the secret!", "It's a secret...", "icon_512", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret14", "Knockout!", "Found the secret!", "It's a secret...", "ship_176", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret15", "Coincidence!", "Found the secret!", "It's a secret...", "bird_154", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret16", "Pirate Manners", "Found the secret!", "It's a secret...", "ball_126", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret17", "Don't make no sense", "Found the secret!", "It's a secret...", "icon_513", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret18", "Salvation", "Found the secret!", "It's a secret...", "ship_177", 1);

		//  Special
		AchievementManager::addAchievement("geometry.ach.odyssey.secret19", "Comic book fan!", "Found the secret!", "It's a secret...", "dart_99", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret20", "Programmer's secret", "Found the secret!", "It's a secret...", "dart_100", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret21", "Must not be named", "Found the secret!", "It's a secret...", "icon_514", 1);

		//  Update 1.1.0
		AchievementManager::addAchievement("geometry.ach.odyssey.secret22", "Greek Grindset", "Found the secret!", "It's a secret...", "icon_515", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret23", "Geometry Canvas", "Found the secret!", "It's a secret...", "ball_127", 1);
		AchievementManager::addAchievement("geometry.ach.odyssey.secret24", "Wanted!", "Found the secret!", "It's a secret...", "", 1);
	}
};
