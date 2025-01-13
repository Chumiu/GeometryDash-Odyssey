#include <Geode/Geode.hpp>
#include <Geode/modify/GameLevelManager.hpp>

using namespace geode::prelude;

class $modify(GDO_GameLevelManager, GameLevelManager)
{
public:
    $override GJGameLevel *getMainLevel(int levelID, bool loaded)
    {
        auto level = GameLevelManager::getMainLevel(levelID, loaded);

        switch (levelID)
        {
        case 7001:
        case 7002:
            level->m_creatorName = "MathisCreator";
            level->m_accountID = 9250716;
            break;

        case 7004:
            level->m_creatorName = "Jinta22";
            level->m_accountID = 4257871;
            break;

        case 7006:
            level->m_creatorName = "DanKy99";
            level->m_accountID = 14178231;
            break;

        case 7007:
        case 7502:
            level->m_creatorName = "TeamTCM";
            level->m_accountID = 26527850;
            break;

        case 7501:
            level->m_creatorName = "NotKaizer";
            level->m_accountID = 10075800;
            break;

        case 7601:
            level->m_creatorName = "ElDanideYT";
            level->m_accountID = 236725152;
            break;

        case 7602:
            level->m_creatorName = "Lojickal";
            level->m_accountID = 201256736;
            break;

        case 7603:
            level->m_creatorName = "Emilixito";
            level->m_accountID = 99431668;
            break;

        case 7604:
            level->m_creatorName = "Zaxvort";
            level->m_accountID = 236473480;
            break;

        default:
            level->m_creatorName = "SwitchstepGDYT";
            level->m_accountID = 10158911;
            break;
        }

        level->m_levelDesc = "Hello there";
        return level;
    }
};