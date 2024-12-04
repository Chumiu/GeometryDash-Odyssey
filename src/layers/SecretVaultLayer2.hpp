#pragma once
using namespace geode::prelude;

enum class MessageType {
    Basic = 0,
    Special = 1,
    WrongAnswer = 2,
    CorrectAnswer = 3
};

enum class SpecialCodes {
    odyssey = 0,
    invaders = 1,
    astral = 2,
    dumbledalf = 3,
    carp = 4,
    comfort_food = 5,
    colon = 6,
    robtop = 7,
    elemental = 8
};

class SecretVaultLayer2 : public CCLayer
{
protected:
    CCLabelBMFont *m_response = nullptr;
    TextInput *m_textInput = nullptr;

    int m_messageID;
    int m_messageIDX;

    virtual bool init();
    virtual void keyBackClicked();

    void onSubmit(CCObject *);
    void onBack(CCObject *);

public:
    static SecretVaultLayer2 *create();
    CCScene *scene();

    void updateMessage(std::string, MessageType);
    std::string getBasicMessage();
    std::string getMessage();
    std::string getThreadMessage(int, int);
};