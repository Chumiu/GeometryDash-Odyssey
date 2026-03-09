#pragma once
using namespace geode::prelude;

class CreditsNode : public CCNode
{
protected:
    int m_accountID = 0;
    SimplePlayer *m_userIcon = nullptr;
    CCLabelBMFont *m_userName = nullptr;
    CCLabelBMFont *m_userReason = nullptr;
    CCMenuItemSpriteExtra *m_userButton = nullptr;

    bool init(const char *name, int accountID = 0, int iconID = 1, int color1 = 1, int color2 = 3, int color3 = 0);

public:
    static CreditsNode *create(const char *name, int accountID = 0, int iconID = 1, int color1 = 1, int color2 = 3, int color3 = 0);

    void setUserButtonVisible(bool value);
    void setIconVisible(bool value);
    void onUser(CCObject *);
};