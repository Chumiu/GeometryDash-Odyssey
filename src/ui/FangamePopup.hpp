#pragma once
using namespace geode::prelude;

class FangamePopup : public Popup
{
protected:
    const char *m_link;
    const char *m_buttonText = "Test";
    CCMenuItemSpriteExtra *m_linkBtn = nullptr;

    TaskHolder<web::WebResponse> m_listener;
    LoadingCircle *m_circle = nullptr;

    LazySprite *m_sprite = nullptr;
    const char *m_spriteName = nullptr;

    bool init(const char *, const char *);
    void onLink(CCObject *);

    void loadImage();
    void onImageSuccess();
    void onImageFail();
    void fadeLoadingCircle();

public:
    static FangamePopup *create(const char *, const char *);
    void setButtonText(const char *);
};