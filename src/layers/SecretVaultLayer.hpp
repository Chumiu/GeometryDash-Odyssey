#pragma once
using namespace geode::prelude;

enum class MessageType {
    Basic = 0,
    Special = 1,
    WrongAnswer = 2,
    CorrectAnswer = 3
};

class SecretVaultLayer : public CCLayer
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
    static SecretVaultLayer *create();
    CCScene *scene();

    void updateMessage(std::string, MessageType);
    std::string getBasicMessage();
    std::string getMessage();
    std::string getThreadMessage(int, int);
};