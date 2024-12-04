#include <Geode/Geode.hpp>
#include <Geode/modify/SimplePlayer.hpp>
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(CustomSimplePlayer, SimplePlayer)
{
    void updatePlayerFrame(int iconID, IconType type)
    {
        SimplePlayer::updatePlayerFrame(iconID, type);

        if(type == IconType::Ufo){
            Odyssey::updateBird(this, iconID, type, false);
        }else{
            Odyssey::updateIcon(this, iconID, type, false);
        }
    }
};