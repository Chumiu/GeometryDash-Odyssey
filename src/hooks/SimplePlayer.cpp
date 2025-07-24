#include <Geode/Geode.hpp>
#include <Geode/modify/SimplePlayer.hpp>
#include "../utils/IconUtils.hpp"

using namespace geode::prelude;

class $modify(CustomSimplePlayer, SimplePlayer)
{
    void updatePlayerFrame(int iconID, IconType type)
    {
        SimplePlayer::updatePlayerFrame(iconID, type);

        IconUtils::updateIcon(this, iconID, type, false);
    }
};