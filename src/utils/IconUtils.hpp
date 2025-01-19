#pragma once
using namespace geode::prelude;

namespace IconUtils
{
    std::vector<std::string> getPlayerFrames(int, IconType);
    gd::string getSheetName(int, IconType);

    void updateIcon(CCNode *, int, IconType, bool);
    void updateRobotSprite(GJRobotSprite *, int, IconType);
    void unlockObject(int, int);
    void addCredits(std::pair<int, UnlockType>, int);

    bool isIconCustom(int, IconType);
    bool isIconSecret(int, IconType);

    int currentVehicleID();
};