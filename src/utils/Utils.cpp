#include "Utils.hpp"

//  Adds corners to the "Level Popups"
void Odyssey::addCorners(CCLayer *layer, const char *cornerSprite, float offset)
{
    auto m_cornerBL = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerBL->setAnchorPoint({0, 0});
    m_cornerBL->setPosition({0 - offset, 0 - offset});
    m_cornerBL->setID("corner-bl"_spr);

    auto m_cornerBR = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerBR->setPosition({layer->getContentWidth() + offset, 0 - offset});
    m_cornerBR->setAnchorPoint({1, 0});
    m_cornerBR->setFlipX(true);
    m_cornerBR->setID("corner-br"_spr);

    auto m_cornerTL = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerTL->setAnchorPoint({0, 1});
    m_cornerTL->setPosition({0 - offset, layer->getContentHeight() + offset});
    m_cornerTL->setFlipY(true);
    m_cornerTL->setID("corner-tl"_spr);

    auto m_cornerTR = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerTR->setPosition({layer->getContentWidth() + offset, layer->getContentHeight() + offset});
    m_cornerTR->setAnchorPoint({1, 1});
    m_cornerTR->setFlipX(true);
    m_cornerTR->setFlipY(true);
    m_cornerTR->setID("corner-tr"_spr);

    layer->addChild(m_cornerBL);
    layer->addChild(m_cornerBR);
    layer->addChild(m_cornerTL);
    layer->addChild(m_cornerTR);
};

void Odyssey::setSpanish(bool value){
    GameManager::sharedState()->setGameVariable("0201", value);
}

bool Odyssey::isSpanish(){
    return GameManager::sharedState()->getGameVariable("0201");
}

//  Function that just returns the comic number the player is allowed to read
int Odyssey::getMaxComic(){
    auto GSM = GameStatsManager::sharedState();
    int maxValue = 2;

    for(auto ii = 1; ii <= 9; ii++){
        log::debug("* Has completed level {}? = {}", ii, GSM->hasCompletedMainLevel(7000 + ii));

        if(!GSM->hasCompletedMainLevel(7000 + ii)) break;

        maxValue++;

        if(ii == 4) maxValue = 7;
        if(ii == 9) maxValue = 12;
    }

    log::debug("* Returning value is: {}", maxValue);
    return maxValue;
};

//  Adds a node that's the progress bar of a Level
CCNode *Odyssey::createProgressBar(int percentage, bool isPractice)
{
    auto node = CCNode::create();

    int rgbValue = isPractice ? 255 : 0;
    ccColor3B color = {0, 255, (GLubyte)rgbValue};

    auto bgBar = CCSprite::create("GJ_progressBar_001.png");
    bgBar->setColor({0, 0, 0});
    bgBar->setOpacity(100);
    bgBar->setScale(0.9f);
    bgBar->setZOrder(1);

    node->addChild(bgBar);

    auto progressBar = CCSprite::create("GJ_progressBar_001.png");
    auto rectX = (progressBar->getContentWidth() * percentage) / 100;
    progressBar->setTextureRect({0, .5f, rectX, progressBar->getContentHeight()});
    progressBar->setScaleX(0.89f);
    progressBar->setScaleY(0.75f);
    progressBar->setColor(color);
    progressBar->setZOrder(2);

    progressBar->setAnchorPoint({0, 0.5});
    progressBar->setPositionX(-151.3f);

    node->addChild(progressBar);

    std::string progressNumber = std::to_string(percentage);
    auto progressLabel = CCLabelBMFont::create(fmt::format("{}%", progressNumber).c_str(), "bigFont.fnt");
    progressLabel->setPositionY(0.5f);
    progressLabel->setScale(0.325f);
    progressLabel->setZOrder(3);

    node->addChild(progressLabel);

    const char *mode = isPractice ? "Practice Mode" : "Normal Mode";
    auto label = CCLabelBMFont::create(mode, "bigFont.fnt");
    label->setPositionY(18.0f);
    label->setScale(0.45f);
    node->addChild(label);

    return node;
};

//  Adds a Node that's the difficulty of a level
CCNode *Odyssey::createDifficultyNode(GJDifficulty diff, int stars, bool isCompleted)
{
    auto node = CCNode::create();
    node->setContentSize({22.f, 32.5f});

    std::string difficultyName = fmt::format("diffIcon_{:02}_btn_001.png", static_cast<int>(diff));
    auto diffSprite = CCSprite::createWithSpriteFrameName(difficultyName.c_str());
    diffSprite->setPosition({node->getContentWidth() / 2, node->getContentHeight()});
    diffSprite->setScale(1.25f);

    auto starLabel = CCLabelBMFont::create(std::to_string(stars).c_str(), "bigFont.fnt");
    starLabel->limitLabelWidth(25, 0.6f, 0.1f);
    starLabel->setPosition({0, 0});

    if (isCompleted)
        starLabel->setColor({255, 255, 0});

    auto starSprite = CCSprite::createWithSpriteFrameName("GJ_bigStar_noShadow_001.png");
    starSprite->setPosition({node->getContentWidth(), 0});
    starSprite->setScale(0.5f);

    node->addChild(diffSprite);
    node->addChild(starSprite);
    node->addChild(starLabel);
    return node;
};

//  Updated function to get the dialogs of the game
DialogLayer *Odyssey::createDialog(const char *eventName, int background, bool sameName)
{
    //  Based on language, the file name is assignated.
    auto spanish = Odyssey::isSpanish();
    auto fileName = spanish ? "Spanish.json" : "English.json";

    //  Obtains the info from the selected Language File
    std::ifstream file(Mod::get()->getResourcesDir() / fileName);
    Result<matjson::Value, matjson::ParseError> rawData = matjson::parse(file);
    CCArray *array = CCArray::create();

    if (rawData.isOk())
    {
        matjson::Value data = rawData.unwrap();

        if (data.isObject() && data.contains(eventName))
        {
            auto &dataObject = data[eventName];

            //  If the event exists, enters here
            if (dataObject.isObject())
            {
                auto name = dataObject["name"].asString().unwrapOr("");
                auto sprites = dataObject["sprites"].asArray().unwrap();
                auto dialogs = dataObject["dialogs"].asArray().unwrap();

                //  If the dialog has more than one name
                std::vector<matjson::Value> names;
                if (!sameName && dataObject.contains("names"))
                    names = dataObject["names"].asArray().unwrap();

                //  Fills the array with the dialog objects from the data
                for (auto ii = 0; ii < dialogs.size(); ii++)
                {
                    auto auxName = sameName ? name : names.at(ii).asString().unwrap();

                    std::string auxText = dialogs.at(ii).asString().unwrap();
                    auxText = utils::string::replace(auxText, "<username>", GameManager::get()->m_playerName);

                    auto dialogObj = DialogObject::create(auxName, auxText, sprites.at(ii).asInt().unwrap(), 1, false, {255, 255, 255});
                    array->addObject(dialogObj);
                }
            }
        }
    }

    //  If there was an error during the process, just stores this error message.
    if (array->count() == 0)
    {
        auto dialogObj = DialogObject::create("ERROR 404", "[There was an error while loading the data]", 28, 1, false, {255, 255, 255});
        array->addObject(dialogObj);
    }

    //  Creates the layer to return it
    auto dialogLayer = DialogLayer::createDialogLayer(nullptr, array, background);
    dialogLayer->animateInRandomSide();
    dialogLayer->setZOrder(10);
    return dialogLayer;
};

//  Creates text that can be translated by the "Language" settings
gd::string Odyssey::createText(const char *english, const char *spanish)
{
    return (Odyssey::isSpanish()) ? spanish : english;
}

//  Adds the audio assets to the Music Download Manager
void Odyssey::insertAssetsToMap(bool isSong, std::vector<int> IDs)
{
    auto map = MusicDownloadManager::sharedState()->m_resourceSfxUnorderedSet;

    for (int assetID : IDs)
    {
        if (isSong)
            MusicDownloadManager::sharedState()->m_resourceSongUnorderedSet.insert(assetID);
        else
            MusicDownloadManager::sharedState()->m_resourceSfxUnorderedSet.insert(assetID);
    }
}

//  Returns what's the island page of the current level
int Odyssey::getIslandForLevel(int levelID)
{
    if (levelID <= 7004)
        return 0;

    if (levelID > 7004 && levelID <= 7009)
        return 1;

    if (levelID > 7500 && levelID <= 7505)
        return 2;

    if (levelID > 7600 && levelID <= 7605)
        return 3;

    return 0;
};

//  Verifies the hints you have collected from the Vaults.
void Odyssey::verifyVaultHints()
{
    auto AM = AchievementManager::sharedState();

    //  This only is called upon game loading, to disable the Vault Riddles if they already have the achievement:
    //  * Comic Book Fan can be collected without the vault hint
    //  * The other three secret rewards need the hint to be enabled

    for (auto ii = 1; ii <= 24; ii++)
    {
        auto achievementName = fmt::format("geometry.ach.odyssey.secret{:02}", ii);
        auto savedValueName = fmt::format("3{:02}", ii);

        //  Mod::get()->setSavedValue<bool>(savedValueName, AM->isAchievementEarned(achievementName.c_str()));
        GameManager::sharedState()->setUGV(savedValueName.c_str(), AM->isAchievementEarned(achievementName.c_str()));
    }
};

//  If all the vault rewards were collected, activates the special event
void Odyssey::hasAllVaultRewards()
{
    auto AM = AchievementManager::sharedState();
    auto allHollow = true;
    auto allOgre = true;

    for (auto ii = 1; ii <= 9; ii++)
    {
        auto achievementName = fmt::format("geometry.ach.odyssey.secret{:02}", ii);

        log::debug("Achievement: {}, Value: {}", achievementName, AM->isAchievementEarned(achievementName.c_str()));

        if (!AM->isAchievementEarned(achievementName.c_str()))
            allOgre = false;
        //  if(AM->isAchievementEarned(fmt::format("geometry.ach.odyssey.secret{:02}")))
    }

    for (auto ii = 10; ii <= 12; ii++)
    {
        auto achievementName = fmt::format("geometry.ach.odyssey.secret{:02}", ii);

        log::debug("Achievement: {}, Value: {}", achievementName, AM->isAchievementEarned(achievementName.c_str()));

        if (!AM->isAchievementEarned(achievementName.c_str()))
            allHollow = false;

        //  if(AM->isAchievementEarned(fmt::format("geometry.ach.odyssey.secret{:02}")))
    }

    if (!AM->isAchievementEarned("geometry.ach.odyssey.secret19"))
        allOgre = false;

    if (!AM->isAchievementEarned("geometry.ach.odyssey.secret20"))
        allOgre = false;

    if (!AM->isAchievementEarned("geometry.ach.odyssey.secret22"))
        allOgre = false;

    if (!AM->isAchievementEarned("geometry.ach.odyssey.secret23"))
        allOgre = false;

    if (!AM->isAchievementEarned("geometry.ach.odyssey.secret24"))
        allOgre = false;

    if (!GameManager::sharedState()->getUGV("234"))
        allOgre = false;

    /*
    if (!GameManager::sharedState()->getUGV("235"))
        allOgre = false;

    if (!GameManager::sharedState()->getUGV("236"))
        allHollow = false;
    */

    if (allOgre)
    {
        log::debug("Tiene todos los rewards del Ogro");

        if (!GameManager::sharedState()->getUGV("231"))
            GameManager::sharedState()->setUGV("231", true);

        //  log::debug("El jugador ya tiene todos los rewards del Ogro")
    }
    else
    {
        GameManager::sharedState()->setUGV("231", false);
    }

    if (allHollow)
    {
        log::debug("Tiene todos los rewards del Hollow");

        if (!GameManager::sharedState()->getUGV("232"))
            GameManager::sharedState()->setUGV("232", true);

        //  log::debug("Habilitado el Hint de Gargan (Ogro)");
    }
    else
    {
        GameManager::sharedState()->setUGV("232", false);
    }
};

void Odyssey::patch(int address, geode::ByteVector const &data)
{
    geode::Mod::get()->patch(reinterpret_cast<void *>(geode::base::get() + address), data).unwrap();
}

std::vector<unsigned char> Odyssey::intToBytes(int value)
{
    std::vector<unsigned char> result;
    result.push_back(value & 0x000000ff);
    result.push_back((value & 0x0000ff00) >> 8);
    result.push_back((value & 0x00ff0000) >> 16);
    result.push_back((value & 0xff000000) >> 24);
    return result;
}

int Odyssey::getLevelSongID(int levelID)
{
    switch (levelID)
    {
    case 7001: // The Dangerous Seas
        return 10009443;
    case 7002: // Ghost House
        return 676349;
    case 7003: // Super Ultra
        return 10007255;
    case 7004: // Cryptofunk
        return 10007201;
    case 7005: // Hellfire
        return 10007222;
    case 7006: // Boss Rush
        return 10007196;
    case 7007: // Absolute Zero
        return 10007188;
    case 7008: // Comfort Food
        return 10012389;
    case 7009: // Critical Hit
        return 10007200;

    case 7501: // Conclusive Journey
        return 500335;
    case 7502: // Burning Sands
        return 880262;

    case 7601: // Eclipse
        return 10007207;
    case 7602: // Jelly Castle
        return 10007227;
    case 7603: // Phone Me First
        return 1139782;
    case 7604: // Wubsplosion
        return 10007269;
    case 7605: // Granite
        return 10007320;

    default:
        return -1;
    }
}

std::pair<gd::string, gd::string> Odyssey::getLevelAudioAssets(int levelID)
{
    switch (levelID)
    {
    case 7001: // The Dangerous Seas
        return {"10005070, 10006468, 10009443", "288, 537, 757, 758, 759, 1005, 1373, 1374, 1375, 1376, 1548, 1992, 1993, 1994, 1995, 2037, 2038, 2039, 2040, 2779, 3081, 3383, 3384, 3556, 4273, 4274, 4293, 4294, 4395, 4397, 4404, 7501, 7874, 8180, 13536, 14554, 14563, 14575, 22875"};
        break;
    case 7002: // Ghost House
        return {"676349", "539, 554, 1076, 1740, 2389, 2390, 2392, 2590, 2591, 2844, 2847, 3082, 3083, 3084, 3085, 3114, 3120, 3533, 4395, 4397, 4404, 7274, 7501, 7791, 7795, 7799, 12087, 12089, 12121, 12132, 12174, 12175, 12178, 12184, 12188, 12198, 12920, 15950, 15955, 18929, 22875"};
        break;
    case 7003: // Super Ultra
        return {"10000718, 10007255", "491, 492, 493, 562, 755, 1025, 1049, 1567, 1571, 1572, 1586, 1587, 1619, 1740, 1751, 1897, 2393, 2711, 2716, 2717, 2718, 2847, 2910, 2913, 2914, 2915, 2916, 2974, 3016, 3210, 3383, 3384, 4260, 4261, 4262, 4273, 4289, 4290, 4397, 4404, 6242, 6310, 7231, 7646, 7647, 19796, 22875"};
        break;
    case 7004: // Cryptofunk
        return {"10007201", "328, 493, 583, 538, 539, 1739, 2297, 3082, 3208, 4395, 4397, 4404, 4869, 6256, 7501, 7791, 12875, 13228, 13231, 17649, 17650, 17651, 17652, 22875"};
        break;
    case 7005: // Hellfire
        return {"10007222", "537, 1368, 1372, 1374, 1375, 1376, 1740, 1741, 2612, 3001, 3002, 3003, 4274, 4395, 4397, 4404, 6242, 6243, 6244, 6245, 7224, 7225, 7231,  7243, 7245, 7246, 7260, 7262, 7271, 7274, 7501, 7643, 7646, 7652, 7945, 10104, 12184, 13237, 13238, 13239, 17604, 17619, 17621, 18164, 19729, 22875"};
        break;
    case 7006: // Boss Rush
        return {"10007196", "554, 998, 1014, 1024, 1740, 1745, 1950, 1993, 1994, 1995, 3082, 3083, 3383, 3384, 3556, 4395, 4397, 4404, 6245, 6808, 6833, 6838, 6840, 6863, 6870, 6897, 6900, 7245, 7501, 7667, 13057, 22875"};
        break;
    case 7007: // Absolute Zero
        return {"10007188, 10011788", "4395, 4397, 4404, 7501, 7659, 7943, 22875"};
        break;
    case 7008: // Comfort Food
        return {"10012389", "4395, 4397, 4404, 7501, 7687, 22875"};
        break;
    case 7009: // Critical Hit
        return {"10000721, 10007200, 10004463", "473, 476, 709, 717, 1950, 1993, 1994, 1995, 2032, 2074, 2856, 3112, 3548, 4395, 4563, 4566, 4841, 4883, 5222, 6256, 6881, 6882, 7501, 7653, 7659, 7687, 7799, 7945, 13237, 13980, 17604, 18267, 22879"};
        break;

    case 7501: // Conclusive Journey
        return {"500335, 880262", "566, 4395, 4397, 4404, 7501, 21458"};
        break;
    case 7502: // Burning Sands
        return {"880262, 10006666", "993, 1185, 1372, 1374, 1375, 1376, 1377, 1378, 1601, 1741, 1744, 1745, 1751, 2075, 2390, 2392, 2612, 2716, 2717, 2718, 2824, 2981, 2982, 3081, 4072, 4073, 4074, 4290, 6242, 7625, 7735, 7943, 8181, 8191, 9873, 15907, 18771"};
        break;

    case 7601: // Eclipse
        return {"10007207, 10004233, 10007208", "566, 3114, 4395, 4397, 4404, 4470, 4846, 4847, 6620, 6621, 7501, 22875"};
        break;
    case 7602: // Jelly Castle
        return {"10007227", "2390, 4060, 4395, 4397, 4404, 7501, 7625, 22875"};
        break;
    case 7603: // Phone Me First
        return {"1139782", "1313, 1315, 1330, 1554, 2136, 2981, 4074, 4273, 4274, 4395, 4397, 4404, 6269, 7501, 13171, 20698, 22875"};
        break;
    case 7604: // Wubsplosion
        return {"10007269", "4395, 4397, 4404, 7501"};
        break;
    case 7605: // Granite
        return {"10007320", "709, 2032, 2075, 2076, 2500, 2979, 4397, 7491, 10731, 14901"};
        break;
    }

    return {"", ""};
};