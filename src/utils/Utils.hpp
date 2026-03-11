#pragma once
using namespace geode::prelude;

namespace Odyssey
{
    //  Dialogos
    DialogLayer *createDialog(const char *event, int background = 1, bool sameName = true);
    gd::string createText(const char *english, const char *spanish = "");

    //  Nodos para el Level Popup
    CCNode *createDifficultyNode(GJDifficulty, int, bool);
    CCNode *createProgressBar(int, bool);

    //  Funciones
    void addCorners(CCLayer *, const char *, float);
    void insertAssetsToMap(bool, std::vector<int>);

    void verifyVaultHints();
    void hasAllVaultRewards();

    void setSpanish(bool value);
    bool isSpanish();

    //  Enteros
    int getIslandForLevel(int levelID);

    int getLevelSongID(int levelID);
    std::pair<gd::string, gd::string> getLevelAudioAssets(int levelID);

    void patch(int, geode::ByteVector const &);
    std::vector<unsigned char> intToBytes(int);
};