#include <Geode/Geode.hpp>
#include <Geode/modify/ItemInfoPopup.hpp>
#include "../utils/IconUtils.hpp"

using namespace geode::prelude;

class $modify(GDOItemInfoPopup, ItemInfoPopup)
{
    bool init(int p0, UnlockType p1)
    {
        if (!ItemInfoPopup::init(p0, p1))
            return false;

        int type = static_cast<int>(p1);

        if (IconUtils::isIconCustom(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))))
        {
            auto winSize = CCDirector::sharedDirector()->getWinSize();
            auto popupSize = m_mainLayer->getChildByID("background")->getContentSize();

            auto odysseyLabel = CCSprite::createWithSpriteFrameName("GDO_OdysseyText_001.png"_spr);
            odysseyLabel->setPosition({winSize.width / 2 - popupSize.width / 2 + 44, winSize.height / 2 + popupSize.height / 2 - 28});
            odysseyLabel->setID("odyssey-label"_spr);
            odysseyLabel->setScale(0.70f);

            m_mainLayer->addChild(odysseyLabel);
        }

        log::info("{}", type);

        if (type >= 900)
        {
            auto player = SimplePlayer::create(0);

            player->updatePlayerFrame(1, static_cast<IconType>(type));
            player->setColor(GameManager::sharedState()->colorForIdx(17));

            auto itemIcon = m_mainLayer->getChildByID("item-icon");
            itemIcon->removeAllChildrenWithCleanup(true);

            player->setPosition(itemIcon->getContentSize() / 2);
            itemIcon->addChild(player);
        }

        if (GameStatsManager::sharedState()->getItemUnlockState(p0, p1) != 1)
        {
            std::string iconName = nameForUnlockType(p0, p1);
            const char *titleString = "Full version";
            std::string descriptionString = fmt::format("You can <cl>get</c> this <cg>{}</c> in the full version of <cy>Geometry Dash</c>!", iconName);

            //  Default Icons
            if ((p1 == UnlockType::Cube && p0 <= 4) || p0 == 1 || ((p1 == UnlockType::Col1 || p1 == UnlockType::Col2) && p0 <= 3))
            {
                descriptionString = fmt::format("This <cg>{}</c> is <cl>unlocked</c> by default.", iconName);
                titleString = "Default";
            }

            //  This icon comes from Carp's Shop
            if (IconUtils::isIconCustom(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))) && GameStatsManager::sharedState()->getItemUnlockState(p0, p1) == 5)
            {
                descriptionString = fmt::format("You can <cl>buy</c> this <cg>{}</c> in the <cd>Carp's shop</c>!", iconName);
                titleString = "Carp's Shop";
            }

            //  Icon is for a future update
            if (IconUtils::isIconCustom(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))) && GameStatsManager::sharedState()->getItemUnlockState(p0, p1) == 6)
            {
                descriptionString = fmt::format("This <cg>{}</c> can be <cl>unlocked</c> in update <cy>2.0</c>.", iconName);
                titleString = "Coming Soon";
            }

            //  Icon is from a chest
            if (IconUtils::isIconCustom(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))) && GameStatsManager::sharedState()->getItemUnlockState(p0, p1) == 7)
            {
                descriptionString = fmt::format("You can <cl>get</c> this <cg>{}</c> from a <cy>Special Chest</c>.", iconName);
                titleString = "Special Reward";
            }

            if (auto descriptionArea = static_cast<TextArea *>(m_mainLayer->getChildByID("description-area")))
                descriptionArea->setString(descriptionString);

            if (auto achievementLabel = static_cast<CCLabelBMFont *>(m_mainLayer->getChildByID("achievement-label")))
                achievementLabel->setString(titleString);
        }
        else
        {
            if (IconUtils::isIconSecret(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))))
            {
                if (auto descriptionArea = static_cast<TextArea *>(m_mainLayer->getChildByID("description-area")))
                {
                    std::string iconName = nameForUnlockType(p0, p1);
                    std::string descriptionString = fmt::format("A <cy>secret</c> is required to <cl>unlock</c> this <cg>{}</c>!", iconName);
                    descriptionArea->setString(descriptionString);
                }
            }
        }

        return true;
    }

    static gd::string nameForUnlockType(int p0, UnlockType p1)
    {
        switch (static_cast<int>(p1))
        {
        case 900:
            return "Boat";
        case 901:
            return "Drone";
        case 902:
            return "Slider";
        case 903:
            return "Minecart";
        default:
            return ItemInfoPopup::nameForUnlockType(p0, p1);
        }
    }
};