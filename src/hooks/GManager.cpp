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
		if (Mod::get()->getSavedValue<bool>("purge-save"))
		{
			auto saveDirectory = dirs::getSaveDir();
			auto modDirectory = Mod::get()->getSaveDir();
	
			std::filesystem::remove(modDirectory / "saved.json");
			std::filesystem::remove(modDirectory / "settings.json");
			std::filesystem::remove(saveDirectory / "CCGameManagerOdyssey.dat");
			std::filesystem::remove(saveDirectory / "CCGameManagerOdyssey2.dat");

			return;
		}

		GManager::save();
	}
};