#pragma once
using namespace geode::prelude;

class ComicPopup : public Popup{
    protected:
        bool init();
        void onComic(CCObject *);

        public:
        static ComicPopup *create();
};