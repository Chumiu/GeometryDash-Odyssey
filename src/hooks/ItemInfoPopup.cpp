#include <Geode/Geode.hpp>
#include <Geode/modify/ItemInfoPopup.hpp>
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(GDOItemInfoPopup, ItemInfoPopup)
{
    bool init(int p0, UnlockType p1)
    {
        if (!ItemInfoPopup::init(p0, p1))
            return false;

        int type = static_cast<int>(p1);

        if (type >= 900)
        {
            auto player = SimplePlayer::create(0);

            log::info("{}\n", type);
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
            const char *titleString = "Default";
            std::string descriptionString = fmt::format("You can <cl>get</c> this <cg>{}</c> in the full version of <cy>Geometry Dash</c>!", iconName);

            if ((p1 == UnlockType::Cube && p0 <= 4) || p0 == 1 || ((p1 == UnlockType::Col1 || p1 == UnlockType::Col2) && p0 <= 3))
                descriptionString = fmt::format("This <cg>{}</c> is <cl>unlocked</c> by default.", iconName);

            if (Odyssey::isCustomIcon(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))) && GameStatsManager::sharedState()->getItemUnlockState(p0, p1) == 5)
            {
                descriptionString = fmt::format("You can <cl>buy</c> this <cg>{}</c> in the <cd>Carp's shop</c>!", iconName);
                titleString = "Carp's Shop";
            }

            if (auto descriptionArea = static_cast<TextArea *>(m_mainLayer->getChildByID("description-area")))
            {
                descriptionArea->setString(descriptionString);
            }

            if (auto achievementLabel = static_cast<CCLabelBMFont *>(m_mainLayer->getChildByID("achievement-label")))
                achievementLabel->setString(titleString);
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