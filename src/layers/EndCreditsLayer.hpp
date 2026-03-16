#pragma once
using namespace geode::prelude;

class EndCreditsLayer : public CCLayer
{
private:
    CCLayer *createCredits(int list, const char *reason);

protected:
    CCSize m_winSize;
    CCSprite *m_background = nullptr;
    CCLayer *m_mainCreditsLayer = nullptr;
    int m_speed = 0;

    virtual bool init();
    virtual void keyBackClicked();
    virtual void createEndCredits();
    void onBack(CCObject *);

public:
    void backMenuLayer();

    static EndCreditsLayer *create();
    CCScene *scene();
};

const std::vector<std::vector<gd::string>> creditsManagers = {
    {"SwitchstepGDYT", "10158911", "106", "18", "12", "9"},
    {"ZapManiac", "1605650", "80", "6", "0", "8"},
    {"MathisCreator", "9250716", "143", "6", "3", "1"},
    {"Sear15", "28639090", "371", "8", "12", "12"},
};

const std::vector<std::vector<gd::string>> creditsModders = {
    {"ML500", "2102", "296", "22", "106", "106"},
    {"Chumiu", "25521533", "457", "94", "52", "12"},
    {"Cypher", "6332919", "31", "9", "1", "1"},
};

const std::vector<std::vector<gd::string>> creditsCreatorsOne = {
    {"SwitchstepGDYT", "10158911", "106", "18", "12", "9"},
    {"ZapManiac", "1605650", "80", "6", "0", "8"},
    {"MathisCreator", "9250716", "143", "6", "3", "1"},
    {"Sear15", "28639090", "371", "8", "12", "12"},
    {"Jinta22", "4257871", "231", "18", "9", "3"},
    {"KoromiGD", "1683840", "98", "17", "2", "44"},
    {"Danky99", "14178231", "11", "9", "11", "3"},
    {"MasterTheCube5", "13319860", "107", "6", "10", "11"},
    {"GenaMorphosis", "10026833", "467", "6", "83", "40"},
    {"NotKaizer", "10075800", "135", "41", "11", "12"},
    {"DogneR", "22859812", "12", "33", "2", "2"},
    {"JoshuaGD23", "14831460", "459", "12", "12", "12"},
    {"Bonntu", "23438222", "35", "12", "17", "70"},
    {"TheBreadCat24", "14604196", "371", "12", "3", "3"},
    {"ReyBenGDYT", "13492478", "359", "82", "11", "1"},
};

const std::vector<std::vector<gd::string>> creditsCreatorsTwo = {
    {"ElDanielYT", "26443361", "151", "8", "3", "12"},
    {"Lojickal", "22472683", "267", "35", "3", "12"},
    {"ExMarker", "132634158", "143", "21", "72", "12"},
    {"AzCl", "119157505", "1", "77", "2", "72"},
    {"Emilixito", "10656247", "35", "9", "3", "3"},
    {"Zaxvort", "27686509", "206", "49", "72", "70"},
    {"StudioBois", "17028382", "263", "4", "2", "2"},
};

const std::vector<std::vector<gd::string>> creditsArtists = {
    {"Danky99", "14178231", "11", "9", "11", "3"},
    {"ReyBenGDYT", "13492478", "1", "86", "0", "0"},
    {"3lipng", "29170137", "465", "12", "17", "17"},
    {"ML500", "2102", "296", "22", "106", "106"},
    {"MinoX28", "13284787", "283", "94", "12", "12"},
    {"Vaughners", "2180460", "350", "87", "3", "40"},
    {"cyanflower", "21113321", "2", "12", "3", "3"},
    {"AngelozDD", "18718615", "431", "0", "3", "12"},
    {"MasterTheCube5", "13319860", "107", "6", "10", "11"},
    {"SweeSwag", "21644186", "102", "12", "8", "8"},
};

const std::vector<std::vector<gd::string>> creditsTesters = {
    {"Andrexel", "8327873", "114", "8", "11", "11"},
    {"cyanflower", "21113321", "2", "12", "3", "3"},
    {"DAPixelhero", "1826718", "72", "5", "9", "12"},
    {"DolphinOFFICIAL", "16564836", "371", "4", "14", "14"},
    {"dreen", "15960627", "1", "0", "3", "3"},
    {"Emmmanuel2014", "5911554", "42", "15", "3", "3"},
    {"hsibz", "6169431", "456", "93", "83", "83"},
    {"idkguyGD", "27015597", "12", "90", "70", "3"},
    {"ObsidianAJ", "11368602", "48", "6", "3", "44"},
    {"OccularPixel", "26757914", "351", "4", "3", "3"},
    {"MichTopGDMT", "8983710", "22", "3", "12", "3"},
    {"MinoX28", "13284787", "283", "94", "12", "12"},
    {"RJ04", "25359829", "27", "93", "11", "11"},
    {"Robertjrtineo1", "21054982", "1", "0", "3", "3"},
    {"Statronic", "19130132", "19", "6", "3", "1"},
    {"TochyGMD", "26108122", "98", "12", "12", "3"},
    {"ZerkGMD", "27986840", "37", "12", "15", "12"},
};

const std::vector<std::vector<gd::string>> creditsSpecials = {
    {"RobTop", "71", "275", "6", "3", "1"},
    {"Colon", "106255", "60", "18", "10", "10"},
    {"EVW", "710192", "28", "12", "9", "9"},
    {"im fernando", "5398449", "56", "35", "3", "3"},
    {"StivenelXD", "167848", "50", "12", "3", "3"},
    {"Capeling", "18226543", "70", "41", "12", "12"},
    {"LimeGradient", "7214334", "46", "98", "12", "43"},
    {"Mxst0", "24326682", "296", "89", "2", "44"},
    {"Bluespace", "10206148", "37", "3", "6", "6"},
    {"DaPixelHero", "1826718", "72", "5", "9", "9"},
    {"RetroAdvance64", "617383", "298", "94", "14", "14"},
    {"StudioBois", "17028382", "263", "4", "2", "2"},
};