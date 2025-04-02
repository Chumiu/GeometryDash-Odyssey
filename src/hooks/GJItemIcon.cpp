#include <Geode/Geode.hpp>
#include <Geode/modify/GJItemIcon.hpp>
#include "../utils/Utils.hpp"
#include "../utils/IconUtils.hpp"

using namespace geode::prelude;

class $modify(GJItemIcon)
{
    static GJItemIcon* createBrowserItem(UnlockType unlockType, int itemID) 
    {
        GJItemIcon* ret = GJItemIcon::createBrowserItem(unlockType, itemID);

        int vehicleID = IconUtils::unlockTypeToInt(unlockType);

        ret->m_unlockType = unlockType;

        if (vehicleID >= 900)
        {
            ret->removeAllChildrenWithCleanup(true);

            auto icon = SimplePlayer::create(0);
            icon->updatePlayerFrame(itemID, IconUtils::intToIconType(vehicleID));
            icon->setColors(GameManager::get()->colorForIdx(17), {255, 255, 255});
            icon->setPosition(ret->getContentSize() / 2);
            ret->m_player = icon;
            ret->addChild(ret->m_player);
        }
        
        return ret;
    }

    static float scaleForType(UnlockType p0) 
    { 
        switch (IconUtils::unlockTypeToInt(p0))
        {
        case 900:
            return .6f;
        case 901:
        case 902:
            return .8f;
        case 903:
            return .7f;
        }
        
        return GJItemIcon::scaleForType(p0);
    }

    void changeToLockedState(float p0) 
    {
        
        GJItemIcon::changeToLockedState(p0);

        if (IconUtils::isCustomVehicle(m_unlockType))
        {   
            auto layer = static_cast<SimplePlayer*>(m_player)->m_firstLayer;
            layer->setOpacity(120);
            layer->setColor({0, 0, 0});
            layer->setVisible(true);
            
            for(auto child : CCArrayExt<CCSprite*>(layer->getChildren()))
            {
                child->setVisible(false);
            }
        }

    }

};