#pragma once
using namespace geode::prelude;

namespace Odyssey
{
    inline static std::vector<Mod *> breakingModsList;

    //  Dialogos
    DialogLayer *createDialog(const char *event);
    DialogLayer *createDialogResponse(const char *event, int times);

    //  Nodos para el Level Popup
    CCNode *createDifficultyNode(GJDifficulty, int);
    CCNode *createProgressBar(int, bool);

    //  Funciones
    void addCorners(CCLayer *, const char *, float);
    void insertAssetsToMap(bool, std::vector<int>);
    //void updateIcon(CCNode *, int, IconType, bool);
    //void updateRobotSprite(GJRobotSprite *, int, IconType);
    //void addCreditsToIcon(std::pair<int, UnlockType>, int);
    void hasAllVaultRewards();

    //  Banderas
    //bool isIconCustom(int, IconType);
    //bool isIconSecret(int, IconType);
    //bool isIconShop(int, IconType);
    //bool isIconUpcoming(int, IconType);

    //  Enteros
    //int currentVehicleID();
    int islandPageForLevelID(int);

    //  Vectores
    //std::vector<std::string> getPlayerFrames(int, IconType);
    std::vector<Mod *> getEarlyLoadBreakingMods();
    std::vector<Mod *> getBreakingMods();

    //void unlockObject(int, int);

    void patch(int, geode::ByteVector const&);
    std::vector<unsigned char> intToBytes(int);
};