#pragma once
using namespace geode::prelude;

enum class MessageType
{
    Basic = 0,
    Special = 1,
    WrongAnswer = 2,
    CorrectAnswer = 3
};

class SecretVaultLayer2 : public CCLayer
{
protected:
    CCMenuItemSpriteExtra *m_doorBtn = nullptr;
    CCLabelBMFont *m_response = nullptr;
    TextInput *m_textInput = nullptr;
    bool m_spanish = false;

    int m_messageID;
    int m_messageIDX;
    int m_randomMessageIDX = 0;

    virtual bool init();
    virtual void keyBackClicked();

    void onBack(CCObject *);
    void onSubmit(CCObject *);

    void enableGate();
    void getOgreDialog();
    void onExtraLevels(CCObject *);

public:
    static SecretVaultLayer2 *create();
    CCScene *scene();

    void updateMessage(std::string, MessageType);
    std::string getBasicMessage();
    std::string getMessage();
    std::string getThreadMessage(int, int);
};