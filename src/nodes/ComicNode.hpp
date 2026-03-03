#pragma once
using namespace geode::prelude;

class ComicNode : public CCLayer
{
protected:
    TaskHolder<web::WebResponse> m_listener;
    LoadingCircle *m_circle = nullptr;

    LazySprite * m_sprite = nullptr;
    const char *m_spriteName = nullptr;

    bool init(const char *comicPage);

    void loadImage();
    void onImageSuccess();
    void onImageFail();
    void fadeLoadingCircle();

public:
    static ComicNode *create(const char *comicPage);
};