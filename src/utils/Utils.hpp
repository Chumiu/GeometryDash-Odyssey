#pragma once

using namespace geode::prelude;

namespace Odyssey {
    DialogLayer * createDialog(const char* event);
    DialogLayer * createDialogResponse(const char * event, int times);

    void addCorners(CCLayer *, const char * , float);

    CCNode * createDifficultyNode(GJDifficulty, int);
    CCNode * createProgressBar(int, bool);

    void insertAssetsToMap(bool, std::vector<int>);

    int currentVehicleID();
    bool isCustomIcon(int, IconType);
    std::vector<std::string> getPlayerFrames(int, IconType);
    void updateIcon(CCNode*, int, IconType, bool);

    void addCreditsToIcon(std::pair<int, UnlockType>, int);

    int islandPageForLevelID(int);
};