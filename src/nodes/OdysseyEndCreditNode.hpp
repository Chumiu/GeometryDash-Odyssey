#pragma once
using namespace geode::prelude;

class OdysseyEndCreditNode : public cocos2d::CCNode
{
protected:
    SimplePlayer *m_userIcon = nullptr;
    cocos2d::CCLabelBMFont *m_userName = nullptr;

    bool init(const char *name, int iconID, int color1, int color2, int color3, bool glow)
    {
        if (!CCNode::init())
            return false;

        auto GM = GameManager::get();

        if (name != "RobTop")
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

        userMenu->addChild(m_userName);
        addChild(userMenu);
        addChild(m_userIcon);

        setID(""_spr + lower + "-credit-node");

        return true;
    }

public:
    static OdysseyEndCreditNode *create(const char *name, int iconID, int color1, int color2, int color3, bool glow)
    {
        auto ret = new OdysseyEndCreditNode();
        if (ret && ret->init(name, iconID, color1, color2, color3, glow))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    };
};