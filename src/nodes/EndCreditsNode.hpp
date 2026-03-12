#pragma once
using namespace geode::prelude;

class EndCreditsNode : public CCNode
{
protected:
    int m_accountID = 0;
    SimplePlayer *m_userIcon = nullptr;
    CCLabelBMFont *m_userName = nullptr;

    bool init(const char *name, int accountID = 0, int iconID = 1, int color1 = 1, int color2 = 3, int color3 = -1)
    {
        if (!CCNode::init())
            return false;

        auto GM = GameManager::get();

        if (utils::string::equalsIgnoreCase(name, "RobTop"))
        {
            m_userName = CCLabelBMFont::create(name, "goldFont.fnt");
            m_userName->setScale(0.8f);
        }
        else
        {
            m_userName = CCLabelBMFont::create(name, "bigFont.fnt");
            m_userName->setColor(GM->colorForIdx(color2));
            m_userName->setScale(0.6f);
        }

        m_userName->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
        m_userName->limitLabelWidth(24.0f, 0.6f, 0.3f);

        std::string lower;
        for (auto elem : std::string(name))
            lower += std::tolower(elem);

        m_userIcon = SimplePlayer::create(iconID);
        m_userIcon->setColor(GM->colorForIdx(color1));
        m_userIcon->setSecondColor(GM->colorForIdx(color2));

        if (color3 != -1)
        {
            m_userIcon->setGlowOutline(GM->colorForIdx(color3));
            m_userIcon->enableCustomGlowColor(GM->colorForIdx(color3));
        }

        m_userIcon->setPosition({0, 0});
        m_userIcon->setScale(1.2f);

        CCMenu *userMenu = CCMenu::create();
        userMenu->setPosition({0, -31});

        userMenu->addChild(m_userName);
        addChild(userMenu);
        addChild(m_userIcon);

        setID(""_spr + lower + "-credit-node");

        return true;
    }

public:
    static EndCreditsNode *create(const char *name, int accountID = 0, int iconID = 1, int color1 = 1, int color2 = 3, int color3 = -1)
    {
        auto ret = new EndCreditsNode();

        if (ret && ret->init(name, accountID, iconID, color1, color2, color3))
        {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }
};