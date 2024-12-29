#pragma once
using namespace geode::prelude;

class OdysseyFangamePopup : public geode::Popup<const char *, const char *>
{
protected:
    const char *m_link = nullptr;
    const char *m_buttonText = "Text";
    CCMenuItemSpriteExtra *m_linkButton = nullptr;

    bool setup(const char *, const char *) override;
    void onLink(CCObject *);

public:
    static OdysseyFangamePopup *create(const char *, const char *);
    void setButtonText(const char *);
};