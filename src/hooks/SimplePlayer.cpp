#include <Geode/Enums.hpp>
#include <Geode/Geode.hpp>
#include <Geode/modify/SimplePlayer.hpp>
#include "../utils/IconUtils.hpp"
#include "Geode/loader/Log.hpp"

using namespace geode::prelude;

class $modify(CustomSimplePlayer, SimplePlayer)
{
    static void onModify(auto& self) 
    {
        if (!self.setHookPriorityPost("SimplePlayer::updatePlayerFrame", Priority::Last)) 
        {
            geode::log::warn("Failed to set hook priority to SimplePlayer::updatePlayerFrame");
        }
    }
    void updatePlayerFrame(int iconID, IconType type)
    {
        SimplePlayer::updatePlayerFrame(iconID, type);

        IconUtils::updateIcon(this, iconID, type, false);
    }
};