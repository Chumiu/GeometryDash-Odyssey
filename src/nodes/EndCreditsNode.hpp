#pragma once
using namespace geode::prelude;

class EndCreditsNode : public CCNode
{
protected:
    int m_accountID = 0;
    SimplePlayer *m_userIcon = nullptr;
    CCLabelBMFont *m_userName = nullptr;

    bool init(const char *name, int accountID = 0, int iconID = 1, int color1 = 1, int color2 = 3, int color3 = -1);

public:
    static EndCreditsNode *create(const char *name, int accountID = 0, int iconID = 1, int color1 = 1, int color2 = 3, int color3 = -1);
};