#pragma once
using namespace geode::prelude;

enum class MessageType
{
    Basic = 0,
    Special = 1,
    WrongAnswer = 2,
    CorrectAnswer = 3
};

class SecretVaultLayer : public CCLayer
{
protected:
    CCMenuItemSpriteExtra *m_keeperBtn = nullptr;
    CCMenuItemSpriteExtra *m_backBtn = nullptr;
    CCLabelBMFont *m_title = nullptr;
    CCLabelBMFont *m_response = nullptr;
    TextInput *m_textInput = nullptr;
    TextArea *m_spookyText = nullptr;
    bool m_spanish = false;

    CCSprite *m_background = nullptr;
    CCSprite *m_bg_2 = nullptr;
    CCSprite *m_bg_3 = nullptr;

    CCSprite *m_background_2A = nullptr;
    CCSprite *m_background_2B = nullptr;

    CCSprite *m_background_3A = nullptr;
    CCSprite *m_background_3B = nullptr;

    CCSprite *m_keeper = nullptr;
    CCSprite *keeper_body = nullptr;
    CCSprite *keeper_eyes = nullptr;
    CCSprite *keeper_eyesGlow = nullptr;
    CCSprite *keeper_lock = nullptr;

    CCParticleSystemQuad *bg_particle_01 = nullptr;
    CCParticleSystemQuad *bg_particle_02 = nullptr;
    CCParticleSystemQuad *keeper_auraParticles = nullptr;
    CCParticleSystemQuad *keeper_angerParticles_01 = nullptr;
    CCParticleSystemQuad *keeper_angerParticles_02 = nullptr;
    CCParticleSystemQuad *keeper_angerParticles_03 = nullptr;

    gd::string m_achievementName;

    int m_messageID;
    int m_messageIDX;
    int m_garganIDX = 0;

    virtual bool init();
    virtual void keyBackClicked();

    //  Yes, this is terrible, I will look for a way to fix it later
    void executeJumpscare();
    void scareText01();
    void scareText02();
    void scareText03();
    void scareText04();
    void scareText05();
    void scareEnding();
    void scareKick();

    void enableKeeper();
    void disableKeeper();
    void onSubmit(CCObject *);
    void onBack(CCObject *);
    void onSecret(CCObject *);

    CCNode * m_levelNode = nullptr;
    CCMenuItemSpriteExtra * m_levelBtn = nullptr;
    CCLabelBMFont * m_levelTitle = nullptr;
    void addLevelAnimation();

public:
    static SecretVaultLayer *create();
    CCScene *scene();

    void updateMessage(std::string, MessageType);
    std::string getBasicMessage();
    std::string getMessage();
    std::string getThreadMessage(int, int);

    void fadeInLabel(bool, bool);
};