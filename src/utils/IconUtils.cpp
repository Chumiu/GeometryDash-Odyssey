#include "IconUtils.hpp"

std::vector<std::string> IconUtils::getPlayerFrames(int iconID, IconType type)
{
    std::string iconName;
    switch (type)
    {
    case IconType::Ship:
        iconName = "ship";
        break;
    case IconType::Ball:
        iconName = "player_ball";
        break;
    case IconType::Ufo:
        iconName = "bird";
        break;
    case IconType::Wave:
        iconName = "dart";
        break;
    case IconType::Robot:
        iconName = "robot";
        break;
    case IconType::Spider:
        iconName = "spider";
        break;
    case IconType::Swing:
        iconName = "swing";
        break;
    case IconType::Jetpack:
        iconName = "jetpack";
        break;
    default:
        iconName = "player";
        break;
    }

    int typeNumber = static_cast<int>(type);

    switch (typeNumber)
    {
    case 900:
        iconName = "boat";
        break;
    case 901:
        iconName = "drone";
        break;
    case 902:
        iconName = "slider";
        break;
    case 903:
        iconName = "minecart";
        break;
    }

    if (typeNumber >= 900)
        iconID = 1;

    std::string frame1 = fmt::format("{}_{:02}_001.png"_spr, iconName, iconID);
    std::string frame2 = fmt::format("{}_{:02}_2_001.png"_spr, iconName, iconID);
    std::string frameExtra = fmt::format("{}_{:02}_extra_001.png"_spr, iconName, iconID);
    std::string frameGlow = fmt::format("{}_{:02}_glow_001.png"_spr, iconName, iconID);
    std::string frameDome = fmt::format("{}_{:02}_3_001.png"_spr, iconName, iconID);

    return {frame1, frame2, frameExtra, frameGlow, frameDome};
}

void IconUtils::updateIcon(CCNode *player, int iconID, IconType type, bool isPlayerObject)
{
    if (!isIconCustom(iconID, type))
        return;

    if (type == IconType::Robot || type == IconType::Spider)
        return;

    auto frameCache = CCSpriteFrameCache::get();
    auto frameDict = frameCache->m_pSpriteFrames;

    auto frames = getPlayerFrames(iconID, type);
    auto frame1Texture = frames[0];
    auto frame2Texture = frames[1];
    auto extraTexture = frames[2];
    auto glowTexture = frames[3];
    gd::string domeTexture = frames[4];

    CCSprite *firstLayer;
    CCSprite *secondLayer;
    CCSprite *extraLayer;
    CCSprite *glowLayer;
    GJRobotSprite *robotSprite;
    CCSprite *ufoDome;

    if (isPlayerObject)
    {
        auto obj = static_cast<PlayerObject *>(player);

        firstLayer = obj->m_iconSprite;
        secondLayer = obj->m_iconSpriteSecondary;
        extraLayer = obj->m_iconSpriteWhitener;
        glowLayer = obj->m_iconGlow;
        robotSprite = obj->m_robotSprite;

        if (type == IconType::Ship || type == IconType::Jetpack || type == IconType::Ufo)
        {
            firstLayer = obj->m_vehicleSprite;
            secondLayer = obj->m_vehicleSpriteSecondary;
            extraLayer = obj->m_vehicleSpriteWhitener;
            glowLayer = obj->m_vehicleGlow;
        }

        if (type == IconType::Ufo)
            ufoDome = obj->m_birdVehicle;
    }
    else
    {
        auto obj = static_cast<SimplePlayer *>(player);

        firstLayer = obj->m_firstLayer;
        secondLayer = obj->m_secondLayer;
        extraLayer = obj->m_detailSprite;
        glowLayer = obj->m_outlineSprite;
        robotSprite = obj->m_robotSprite;

        if (type == IconType::Ufo)
            ufoDome = obj->m_birdDome;
    }

    /*
    if (type == IconType::Robot || type == IconType::Spider)
    {
        updateRobotSprite(robotSprite, iconID, type);
        return;
    }
    */

    if (frameDict->objectForKey(frame1Texture))
    {
        firstLayer->setDisplayFrame(frameCache->spriteFrameByName(frame1Texture.c_str()));
    }

    if (frameDict->objectForKey(frame2Texture))
    {
        secondLayer->setDisplayFrame(frameCache->spriteFrameByName(frame2Texture.c_str()));
        secondLayer->setPosition(firstLayer->getContentSize() / 2);
    }

    if (frameDict->objectForKey(extraTexture))
    {
        extraLayer->setVisible(true);
        extraLayer->setDisplayFrame(frameCache->spriteFrameByName(extraTexture.c_str()));
        extraLayer->setPosition(firstLayer->getContentSize() / 2);
    }
    else
        extraLayer->setVisible(false);

    if (frameDict->objectForKey(glowTexture))
    {
        glowLayer->setDisplayFrame(frameCache->spriteFrameByName(glowTexture.c_str()));
        if (!isPlayerObject)
            glowLayer->setPosition(firstLayer->getContentSize() / 2);
    }

    if (type == IconType::Ufo)
    {
        if (frameDict->objectForKey(domeTexture))
        {
            ufoDome->setDisplayFrame(frameCache->spriteFrameByName(domeTexture.c_str()));
            ufoDome->setPosition(firstLayer->getContentSize() / 2);
        }
    }
}

void IconUtils::updateRobotSprite(GJRobotSprite *sprite, int iconID, IconType type)
{
    if (!sprite)
        return;

    sprite->setBatchNode(nullptr);
    sprite->m_paSprite->setBatchNode(nullptr);

    auto spriteParts = sprite->m_paSprite->m_spriteParts;

    auto frameCache = CCSpriteFrameCache::get();

    const char *iconName = "robot";
    if (type == IconType::Spider)
        iconName = "spider";

    for (int i = 0; i < spriteParts->count(); i++)
    {
        auto spritePart = static_cast<CCSpritePart *>(spriteParts->objectAtIndex(i));
        auto tag = spritePart->getTag();

        std::string frame1Texture = fmt::format("{}_{:02}_{:02}_001.png"_spr, iconName, iconID, tag);
        std::string frame2Texture = fmt::format("{}_{:02}_{:02}_2_001.png"_spr, iconName, iconID, tag);
        std::string extraTexture = fmt::format("{}_{:02}_{:02}_extra_001.png"_spr, iconName, iconID, tag);
        std::string glowTexture = fmt::format("{}_{:02}_{:02}_glow_001.png"_spr, iconName, iconID, tag);

        if (auto frame1 = frameCache->spriteFrameByName(frame1Texture.c_str()))
        {
            spritePart->setBatchNode(nullptr);
            spritePart->setDisplayFrame(frame1);
        }

        if (auto secondSprite = static_cast<CCSprite *>(sprite->m_secondArray->objectAtIndex(i)))
        {
            if (auto frame2 = frameCache->spriteFrameByName(frame2Texture.c_str()))
            {
                secondSprite->setBatchNode(nullptr);
                secondSprite->setDisplayFrame(frame2);
                secondSprite->setPosition(spritePart->getContentSize() / 2);
            }
        }

        if (auto glowChild = static_cast<CCSprite *>(sprite->m_glowSprite->getChildren()->objectAtIndex(i)))
        {
            if (auto frameGlow = frameCache->spriteFrameByName(glowTexture.c_str()))
            {
                glowChild->setBatchNode(nullptr);
                glowChild->setDisplayFrame(frameGlow);
            }
        }

        if (spritePart == sprite->m_headSprite)
        {
            if (auto frameExtra = frameCache->spriteFrameByName(extraTexture.c_str()))
            {
                if (sprite->m_extraSprite)
                {
                    sprite->m_extraSprite->setBatchNode(nullptr);
                    sprite->m_extraSprite->setDisplayFrame(frameExtra);
                }
                else
                {
                    sprite->m_extraSprite = CCSprite::createWithSpriteFrame(frameExtra);
                    sprite->m_headSprite->addChild(sprite->m_extraSprite, 2);
                }

                sprite->m_extraSprite->setPosition(spritePart->getContentSize() / 2);
                sprite->m_extraSprite->setVisible(true);
            }
        }
    }
}

void IconUtils::unlockObject(int iconID, int type)
{
    auto gm = GameManager::sharedState();

    std::string icon = "i";

    auto typeCast = static_cast<UnlockType>(type);

    switch (typeCast)
    {
    case UnlockType::Cube:
        icon = "icon";
        break;
    case UnlockType::Ship:
        icon = "ship";
        break;
    case UnlockType::Ball:
        icon = "ball";
        break;
    case UnlockType::Bird:
        icon = "bird";
        break;
    case UnlockType::Dart:
        icon = "dart";
        break;
    case UnlockType::Robot:
        icon = "robot";
        break;
    case UnlockType::Spider:
        icon = "spider";
        break;
    case UnlockType::Swing:
        icon = "swing";
        break;
    case UnlockType::Jetpack:
        icon = "jetpack";
        break;
    case UnlockType::Death:
        icon = "death";
        break;
    case UnlockType::ShipFire:
        icon = "shipstreak";
        break;
    case UnlockType::Streak:
        icon = "special";
        break;
    case UnlockType::GJItem:
        icon = "item";
        break;
    case UnlockType::Col1:
        icon = "col1";
        break;
    case UnlockType::Col2:
        icon = "col2";
        break;
    }

    std::string iconKey = fmt::format("{}_{}", icon, iconID);

    if (typeCast == UnlockType::Col1 || typeCast == UnlockType::Col2)
        return;

    auto var = CCString::createWithFormat("%i", true);

    gm->m_valueKeeper->setObject(var, iconKey.c_str());
}

void IconUtils::addCredits(std::pair<int, UnlockType> pair, int accountID)
{
    GameStatsManager::sharedState()->m_accountIDForIcon.insert(std::make_pair(pair, accountID));
}

bool IconUtils::isIconCustom(int id, IconType type)
{
    if (id > 485 && type == IconType::Cube)
        return true;
    if (id > 169 && type == IconType::Ship)
        return true;
    if (id > 118 && type == IconType::Ball)
        return true;
    if (id > 149 && type == IconType::Ufo)
        return true;
    if (id > 96 && type == IconType::Wave)
        return true;
    if (id > 68 && type == IconType::Robot)
        return true;
    if (id > 69 && type == IconType::Spider)
        return true;
    if (id > 43 && type == IconType::Swing)
        return true;
    if (id > 8 && type == IconType::Jetpack)
        return true;
    if (id > 17 && type == IconType::Item)
        return true;
    if (static_cast<int>(type) >= 900)
        return true;

    return false;
}

bool IconUtils::isIconSecret(int id, IconType type)
{
    if ((id >= 511 && id <= 515) && type == IconType::Cube)
        return true;
    if ((id >= 176 && id <= 177) && type == IconType::Ship)
        return true;
    if ((id >= 123 && id <= 127) && type == IconType::Ball)
        return true;
    if ((id >= 150 && id <= 154) && type == IconType::Ufo)
        return true;
    if ((id >= 99) && type == IconType::Wave)
        return true;
    if ((id >= 9) && type == IconType::Jetpack)
        return true;

    return false;
}

int IconUtils::currentVehicleID()
{
    auto gm = GameManager::get();
    switch (gm->m_playerIconType)
    {
    case IconType::Ship:
        return gm->getPlayerShip();
    case IconType::Ball:
        return gm->getPlayerBall();
    case IconType::Ufo:
        return gm->getPlayerBird();
    case IconType::Wave:
        return gm->getPlayerDart();
    case IconType::Robot:
        return gm->getPlayerRobot();
    case IconType::Spider:
        return gm->getPlayerSpider();
    case IconType::Swing:
        return gm->getPlayerSwing();
    case IconType::Jetpack:
        return gm->getPlayerJetpack();
    default:
        return gm->getPlayerFrame();
    }
}