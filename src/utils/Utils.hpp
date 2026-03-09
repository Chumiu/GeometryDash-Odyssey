#pragma once
using namespace geode::prelude;

namespace Odyssey
{
    inline static std::vector<Mod *> breakingModsList;

    //  Dialogos
    DialogLayer *createDialog(const char *event, int background = 1, bool sameName = true);
    DialogLayer *createDialogResponse(const char *event, int times);

    //  Nodos para el Level Popup
    CCNode *createDifficultyNode(GJDifficulty, int, bool);
    CCNode *createProgressBar(int, bool);

    //  Funciones
    void addCorners(CCLayer *, const char *, float);
    void insertAssetsToMap(bool, std::vector<int>);

    void verifyVaultHints();
    void hasAllVaultRewards();

    //  Enteros
    int getIslandForLevel(int levelID);

    //  Vectores
    std::vector<Mod *> getEarlyLoadBreakingMods();
    std::vector<Mod *> getBreakingMods();

    int getLevelSongID(int levelID);
    std::pair<gd::string, gd::string> getLevelAudioAssets(int levelID);

    void patch(int, geode::ByteVector const &);
    std::vector<unsigned char> intToBytes(int);
};