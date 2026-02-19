#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/GeodeUI.hpp>
using namespace geode::prelude;

class ComicPopup : public Popup{
    protected:
        bool init();
        void onComic(CCObject *);

        public:
        static ComicPopup *create();
};