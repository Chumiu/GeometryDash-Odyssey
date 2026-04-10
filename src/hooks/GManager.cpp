#include <Geode/Geode.hpp>
#include <Geode/modify/GManager.hpp>

using namespace geode::prelude;

class $modify(OdysseyGManager, GManager)
{
    void setup()
    {
        auto compare = std::string(m_fileName);
        compare.insert(std::string_view(compare).find(".dat"), "Odyssey");
        m_fileName = compare;
        GManager::setup();
    }

    void save()
    {
        //  I know this looks awful, but for this value to be true
        //  The player must have said yes to all THREE alerts that were given about this.
        //  (I might believe the casual players don't read warnings)
        if (Mod::get()->getSavedValue<bool>("purge-save"))
        {
            auto saveDirectory = dirs::getSaveDir();
            std::filesystem::remove(saveDirectory / "CCGameManagerOdyssey.dat");
            std::filesystem::remove(saveDirectory / "CCGameManagerOdyssey2.dat");

            Mod::get()->getSaveContainer().clear();
            Mod::get()->getSavedSettingsData().clear();

            return;
        }

        GManager::save();
    }
};