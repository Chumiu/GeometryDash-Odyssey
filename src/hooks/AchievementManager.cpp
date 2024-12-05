#include <Geode/Geode.hpp>
#include <Geode/modify/AchievementManager.hpp>

class $modify(OdysseyAchievementManager, AchievementManager)
{
    void addManualAchievements()
    {
        AchievementManager::addAchievement(
            "geometry.ach.level01a",
            "All hands on deck!",
            "Completed \"The Dangerous Seas\" in practice mode",
            "Complete \"The Dangerous Seas\" in practice mode",
            "icon_486",
            1);

        AchievementManager::addAchievement(
            "geometry.ach.level01b",
            "The Dangerous Seas!",
            "Completed \"The Dangerous Seas\" in normal mode",
            "Complete \"The Dangerous Seas\" in normal mode",
            "icon_487",
            1);

        AchievementManager::addAchievement(
            "geometry.ach.level02a",
            "Spooky butts...",
            "Completed \"Ghost House\" in practice mode",
            "Complete \"Ghost House\" in practice mode",
            "icon_488",
            1);

        AchievementManager::addAchievement(
            "geometry.ach.level02b",
            "Ghost house!",
            "Completed \"Ghost House\" in normal mode",
            "Complete \"Ghost House\" in normal mode",
            "icon_489",
            1);

        AchievementManager::addAchievement(
            "geometry.ach.level03a",
            "Under Powered",
            "Completed \"Super Ultra\" in practice mode",
            "Complete \"Super Ultra\" in practice mode",
            "icon_490",
            1);

        AchievementManager::addAchievement(
            "geometry.ach.level03b",
            "Super Ultra!",
            "Completed \"Super Ultra\" in normal mode",
            "Complete \"Super Ultra\" in normal mode",
            "ball_119",
            1);

        AchievementManager::addAchievement(
            "geometry.ach.level04a",
            "Digital Disco",
            "Completed \"Criptofunk\" in practice mode",
            "Complete \"Criptofunk\" in practice mode",
            "icon_491",
            1);

        AchievementManager::addAchievement(
            "geometry.ach.level04b",
            "Criptofunk!",
            "Completed \"Criptofunk\" in normal mode",
            "Complete \"Criptofunk\" in normal mode",
            "icon_492",
            1);

        // Aun sin testear
        AchievementManager::addAchievement(
            "geometry.ach.level201a",
            "Neferkitty's curse",
            "Completed \"Burning Sands\" in practice mode",
            "Complete \"Burning Sands\" in practice mode",
            "dart_97",
            1);

        AchievementManager::addAchievement(
            "geometry.ach.level201b",
            "Burning Sands!",
            "Completed \"Burning Sands\" in normal mode",
            "Complete \"Burning Sands\" in normal mode",
            "ship_170",
            1);

        AchievementManager::addAchievement(
            "geometry.ach.level202a",
            "End of the road",
            "Completed \"Conclusive Journey\" in practice mode",
            "Complete \"Conclusive Journey\" in practice mode",
            "icon_493",
            1);

        /*
        AchievementManager::addAchievement(
            "geometry.ach.level202b",
            "Conclusive Journey!",
            "Completed \"Conclusive Journey\" in normal mode",
            "Complete \"Conclusive Journey\" in normal mode",
            "robot_69",
            1);
        */

        AchievementManager::addAchievement(
            "geometry.ach.demoncoin01",
            "Ultimate Burning Sands",
            "Completed \"Burning Sands\" with all 3 coins",
            "Complete \"Burning Sands\" with all 3 coins",
            "icon_494",
            1);

        //  AchievementManager::addAchievement("geometry.ach.odyssey.secret01", "Odyssey, ya see!", "Found the secret!", "It's a secret...", "", 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret02", "Threat from the stars", "Found the secret!", "It's a secret...", "bird_150", 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret03", "Finish him!", "Found the secret!", "It's a secret...", "icon_503", 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret04", "Funny old man!", "Found the secret!", "It's a secret...", "icon_504", 1);
        //  AchievementManager::addAchievement("geometry.ach.odyssey.secret05", "Annoying robot", "Found the secret!", "It's a secret...", "", 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret06", "Sightless Kitsune", "Found the secret!", "It's a secret...", "icon_505", 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret07", "Seven years...", "Found the secret!", "It's a secret...", "bird_151", 1);
        //  AchievementManager::addAchievement("geometry.ach.odyssey.secret08", "Global energy", "Found the secret!", "It's a secret...", , 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret09", "Devil's lair", "Found the secret!", "It's a secret...", "ball_120", 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret10", "Rainbow power!", "Found the secret!", "It's a secret...", "ball_121", 1);
        //  AchievementManager::addAchievement("geometry.ach.odyssey.secret11", "Coming soon", "Found the secret!", "It's a secret...", "", 1);
        //  AchievementManager::addAchievement("geometry.ach.odyssey.secret12", "Mortal", "Found the secret!", "It's a secret...", "", 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret13", "About her", "Found the secret!", "It's a secret...", "icon_506", 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret14", "Knockout!", "Found the secret!", "It's a secret...", "ship_171", 1);
        //  AchievementManager::addAchievement("geometry.ach.odyssey.secret15", "Coincidence!", "Found the secret!", "It's a secret...", "", 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret16", "Pirate manners", "Found the secret!", "It's a secret...", "ball_122", 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret17", "Don't make no sense", "Found the secret!", "It's a secret...", "icon_507", 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret18", "Salvation", "Found the secret!", "It's a secret...", "ship_172", 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret19", "Programmer's secret", "Found the secret!", "It's a secret...", "icon_508", 1);
        AchievementManager::addAchievement("geometry.ach.odyssey.secret20", "Comic book fan!", "Found the secret!", "It's a secret...", "dart_98", 1);
    }
};