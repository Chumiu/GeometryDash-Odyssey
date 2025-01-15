#include "Utils.hpp"
#include "Dialogs.hpp"

void Odyssey::addCorners(CCLayer *layer, const char *cornerSprite, float offset)
{
    //  Corners
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

CCNode *Odyssey::createDifficultyNode(GJDifficulty diff, int stars)
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

    auto starSprite = CCSprite::createWithSpriteFrameName("GJ_bigStar_noShadow_001.png");
    starSprite->setPosition({node->getContentWidth(), 0});
    starSprite->setScale(0.5f);

    node->addChild(diffSprite);
    node->addChild(starSprite);
    node->addChild(starLabel);
    return node;
};

DialogLayer *Odyssey::createDialog(const char *event)
{
    CCArray *arr = CCArray::create();

    auto dialogColor = 2;
    std::vector<std::vector<gd::string>> dialogList;
    auto spanishText = GameManager::sharedState()->getGameVariable("0201");

    //  Puede que esto si o no sirva, pero a este punta ya vale
    if (std::string_view(event) == std::string_view("meetingShopkeeper"))
        dialogList = CarpIntroduction;

    if (std::string_view(event) == std::string_view("meetingWizard"))
        dialogList = WizardIntroduction;

    if (std::string_view(event) == std::string_view("firstIslandClear"))
        dialogList = FirstIslandClear;

    if (std::string_view(event) == std::string_view("end"))
        dialogList = Ending;

    if (std::string_view(event) == std::string_view("lockedOgre"))
        dialogList = LockedOgre;

    if (std::string_view(event) == std::string_view("meetingHollow"))
    {
        dialogList = HollowIntroduction;
        dialogColor = 5;
    }

    if (std::string_view(event) == std::string_view("belowHollowQuota"))
    {
        dialogList = HollowNotEnough;
        dialogColor = 5;
    }

    if (std::string_view(event) == std::string_view("hollowQuotaReached"))
    {
        dialogList = HollowEnough;
        dialogColor = 5;
    }

    //  Al tener ya una lista de dialogos asignado, se hace este ciclo
    //  Donde cada parte del dialogo es agregado al Array
    for (auto ii = dialogList.begin(); ii != dialogList.end(); ii++)
    {
        auto text = ii->at(2 + spanishText);
        auto dialog = DialogObject::create(ii->at(0), text, std::stoi(ii->at(1)), 1, false, {255, 255, 255});
        arr->addObject(dialog);
    }

    //  Al terminar, crea el Layer del dialogo y lo agrega al a escena
    auto dialogLayer = DialogLayer::createDialogLayer(nullptr, arr, dialogColor);
    dialogLayer->animateInRandomSide();
    dialogLayer->setZOrder(10);

    return dialogLayer;
};

DialogLayer *Odyssey::createDialogResponse(const char *event, int times)
{
    CCArray *arr = CCArray::create();

    auto dialogColor = 2;
    std::vector<std::vector<gd::string>> dialogList;
    auto spanishText = GameManager::sharedState()->getGameVariable("0201");
    auto knowsCarp = GameManager::sharedState()->getUGV("204");

    if (std::string_view(event) == std::string_view("onExtraLevel"))
    {
        dialogList = LockedExtraLevel;

        auto dialogData = dialogList.at(times);
        auto character = knowsCarp ? dialogData[0] : "????";
        auto text = dialogData[2 + spanishText];

        auto dialog = DialogObject::create(character, text, std::stoi(dialogData[1]), 1, false, {255, 255, 255});
        arr->addObject(dialog);
    }

    if (std::string_view(event) == std::string_view("onFinalComic"))
    {
        dialogList = LockedFinalComic;

        auto dialogData = dialogList.at(times);
        auto character = knowsCarp ? dialogData[0] : "????";
        auto text = dialogData[2 + spanishText];

        auto dialog = DialogObject::create(character, text, std::stoi(dialogData[1]), 1, false, {255, 255, 255});
        arr->addObject(dialog);
    }

    //  Al terminar, crea el Layer del dialogo y lo agrega al a escena
    auto dialogLayer = DialogLayer::createDialogLayer(nullptr, arr, dialogColor);
    dialogLayer->animateInRandomSide();
    dialogLayer->setZOrder(10);

    return dialogLayer;
}



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

int Odyssey::islandPageForLevelID(int levelID)
{
    if (levelID < 7005)
        return 0;

    if (levelID > 7500)
        return 2;

    return 1;
};

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

    for (auto ii = 10; ii <= 18; ii++)
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
    }
    else
    {
        GameManager::sharedState()->setUGV("231", false);
    }

    if (allHollow)
    {
        log::debug("Tiene todos los rewards del Hollow");

        if (!GameManager::sharedState()->getUGV("232"))
        {
            GameManager::sharedState()->setUGV("232", true);
            log::debug("Habilitado el Hint de Gargan (Ogro)");
        }
    }
    else
    {
        GameManager::sharedState()->setUGV("232", false);
    }
};

std::vector<Mod *> Odyssey::getEarlyLoadBreakingMods()
{
    std::vector<Mod *> breakingMods;
    std::vector<std::string> breakingModIDs = {
        "capeling.geometry-dash-lunar"};

    for (std::string id : breakingModIDs)
    {
        Mod *mod = Loader::get()->getInstalledMod(id);

        if (mod && Loader::get()->isModLoaded(id))
        {
            breakingMods.push_back(mod);
        }
    }

    return breakingMods;
};

std::vector<Mod *> Odyssey::getBreakingMods()
{
    std::vector<Mod *> breakingMods;
    std::vector<std::string> breakingModIDs = {
        "capeling.geometry-dash-lunar",
        "dankmeme.globed2",
        "gdutilsdevs.gdutils",
        "itzkiba.better_progression",
        "ninxout.redash"};

#ifdef GEODE_IS_ANDROID
    breakingModIDs.push_back("hiimjustin000.more_icons");
#endif
    for (std::string id : breakingModIDs)
    {
        Mod *mod = Loader::get()->getInstalledMod(id);

        if (mod && Loader::get()->isModLoaded(id))
        {
            breakingMods.push_back(mod);
        }
    }

    return breakingMods;
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