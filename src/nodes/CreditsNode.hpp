#pragma once
using namespace geode::prelude;

class CreditsNode : public cocos2d::CCNode
{
protected:
    int m_accountID = 0;
    SimplePlayer *m_userIcon = nullptr;
    cocos2d::CCLabelBMFont *m_userName = nullptr;
    cocos2d::CCLabelBMFont *m_userReason = nullptr;
    CCMenuItemSpriteExtra *m_userButton = nullptr;

    bool init(const char *name, int iconID, int color1, int color2, int color3, bool glow, int accountID)
    {
        if (!CCNode::init())
            return false;

        auto GM = GameManager::get();

        if (accountID != 71)
        {
            m_userName = CCLabelBMFont::create(name, "bigFont.fnt");
            m_userName->setScale(0.6f);
            m_userName->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
            m_userName->setColor(GM->colorForIdx(color2));
            m_userName->limitLabelWidth(22.0f, 0.6f, 0.3f);
        }
        else
        {
            m_userName = CCLabelBMFont::create(name, "goldFont.fnt");
            m_userName->setScale(0.6f);
            m_userName->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
            m_userName->limitLabelWidth(22.0f, 0.6f, 0.3f);
        }

        std::string lower;

        for (auto elem : std::string(name))
            lower += std::tolower(elem);

        m_userButton = CCMenuItemSpriteExtra::create(m_userName, this, menu_selector(CreditsNode::onUser));

        m_userIcon = SimplePlayer::create(iconID);

        m_userIcon->setColor(GM->colorForIdx(color1));
        m_userIcon->setSecondColor(GM->colorForIdx(color2));

        if (glow)
        {
            m_userIcon->setGlowOutline(GM->colorForIdx(color3));
            m_userIcon->enableCustomGlowColor(GM->colorForIdx(color3));
        }

        m_userIcon->setPosition({0, 0});
        m_userIcon->setScale(1.2f);

        CCMenu *userMenu = CCMenu::create();
        userMenu->setPosition({0, -31});

        userMenu->addChild(m_userButton);
        addChild(userMenu);
        addChild(m_userIcon);

        m_accountID = accountID;
        setID(""_spr + lower + "-credit-node");

        return true;
    }

public:
    static CreditsNode *create(const char *name, int iconID, int color1, int color2, int color3, bool glow, int accountID)
    {
        auto ret = new CreditsNode();
        if (ret && ret->init(name, iconID, color1, color2, color3, glow, accountID))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    };

    void onUser(CCObject *sender)
    {
        ProfilePage::create(m_accountID, false)->show();
    }
};