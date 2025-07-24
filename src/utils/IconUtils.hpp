#pragma once
using namespace geode::prelude;

namespace IconUtils
{
    std::vector<std::string> getPlayerFrames(int, IconType);
    gd::string getSheetName(int, IconType);
    std::string getItemKey(int, int);

    void updateIcon(CCNode *, int, IconType, bool);
    void updateRobotSprite(GJRobotSprite *, int, IconType);
    void unlockObject(int, int);
    void addCredits(std::pair<int, UnlockType>, int);
    void setVehicleSaveId(int, int);

    bool isIconCustom(int, IconType);
    bool isIconSecret(int, IconType);
    bool isCustomVehicle(UnlockType);
    bool isCustomVehicle(IconType);

    int currentVehicleID();
    int unlockTypeToInt(UnlockType);
    int iconTypeToInt(IconType);
    int currentIdForVehicle(int);

    UnlockType intToUnlockType(int);
    IconType intToIconType(int);
};