#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyPlayerObject, PlayerObject)
{
    bool init(int p0, int p1, GJBaseGameLayer* p2, cocos2d::CCLayer* p3, bool p4)
    {
        if (!PlayerObject::init(p0, p1, p2, p3, p4)) return false;

        Odyssey::updateIcon(this, p0, IconType::Cube, true);
        Odyssey::updateIcon(this, GameManager::sharedState()->m_playerShip.value(), IconType::Ship, true);
    
        return true;
    }
    void updatePlayerFrame(int id)
    {
        PlayerObject::updatePlayerFrame(id);

        Odyssey::updateIcon(this, GameManager::sharedState()->m_playerFrame.value(), IconType::Cube, true);
    }

    void updatePlayerRollFrame(int id)
    {
        PlayerObject::updatePlayerRollFrame(id);

        Odyssey::updateIcon(this, id, IconType::Ball, true);
    }

    void updatePlayerSwingFrame(int id)
    {
        PlayerObject::updatePlayerSwingFrame(id);

        Odyssey::updateIcon(this, id, IconType::Swing, true);
    }

    void updatePlayerShipFrame(int id)
    {
        PlayerObject::updatePlayerShipFrame(id);

        Odyssey::updateIcon(this, GameManager::sharedState()->m_playerFrame.value(), IconType::Cube, true);
        Odyssey::updateIcon(this, id, IconType::Ship, true);
    }

    void updatePlayerDartFrame(int id)
    {
        PlayerObject::updatePlayerDartFrame(id);
        
        Odyssey::updateIcon(this, id, IconType::Wave, true);
    }

    void resetPlayerIcon()
    {
        PlayerObject::resetPlayerIcon();

        Odyssey::updateIcon(this, GameManager::sharedState()->m_playerFrame.value(), IconType::Cube, true);
        Odyssey::updateIcon(this, GameManager::sharedState()->m_playerShip.value(), IconType::Ship, true);

    }
};