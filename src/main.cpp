#include <Geode/Geode.hpp>
#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <list>
#include <regex>

using namespace geode::prelude;
using namespace geode::utils::string;

bool isGradient = false;

std::list<int> iHateGradients = {503, 504, 505, 1008, 1009, 1010, 1011, 1012, 1013, 1269, 1270, 1271, 1272, 1273, 1274, 1291, 1292, 1293, 1758, 1759, 1760, 1761, 1762, 1763, 1886, 1887, 1888};
std::list<int> gameplayElements = {10, 11, 12, 13, 35, 36, 45, 46, 47, 67, 84, 99, 101, 111, 140, 141, 200, 201, 202, 203, 286, 287, 660, 745, 746, 747, 748, 1022, 1330, 1331, 1332, 1333, 1334, 1594, 1704, 1751, 1933, 2063, 2064, 2902, 2926, 3004, 3005, 3027 };

// hide gradients via GameObject (hooking, static_cast, m_fields by dank_meme, matcool, Firee) (string utils suggested by cgytrus)
class $modify(MyGameObject, GameObject) {
	static void onModify(auto & self)
	{
		self.setHookPriority("GameObject::createWithFrame", 1000);
		self.setHookPriority("GameObject::setVisible", 1000);
	}
	static GameObject* createWithFrame(char const* frameName) {
		GameObject* gameObject = GameObject::createWithFrame(frameName);
		if (!PlayLayer::get()) return gameObject;
		if (typeinfo_cast<PlayerObject*>(gameObject) != nullptr) return gameObject;
		if (typeinfo_cast<EffectGameObject*>(gameObject) && std::string(frameName).starts_with("secretCoin_")) {
			return gameObject;
		}
		if (!(Mod::get()->getSettingValue<bool>("enabled"))) return gameObject;
		if (Mod::get()->getSettingValue<int64_t>("hideGlowDecoNew") != 1) return gameObject;
		if (((strcmp(frameName, "emptyFrame.png") == 0) || (string::contains(frameName, "_gradient_")))) {
			isGradient = true;
		} else {
			isGradient = false;
		}
		return gameObject;
	}
	void setVisible(bool p0) {
		if (typeinfo_cast<PlayerObject*>(this) != nullptr || typeinfo_cast<EffectGameObject*>(this) != nullptr) GameObject::setVisible(p0);
		else if (isGradient) GameObject::setVisible(false);
		else GameObject::setVisible(p0);
	}
};

// disable glowy objects (idea by TechStudent10, original concept by ItzLever)
class $modify(MyPlayLayer, PlayLayer) {
	void addObject(GameObject* p0) {
		if (Mod::get()->getSettingValue<bool>("enabled")) {
			bool dontSkip = true;
			if (Mod::get()->getSettingValue<bool>("disableGradientTriggers") && p0->m_objectID == 2903) dontSkip = false;
			if (Mod::get()->getSettingValue<int64_t>("hideGlowDecoNew") == 2 && std::find(iHateGradients.begin(), iHateGradients.end(), p0->m_objectID) != iHateGradients.end()) dontSkip = false;
			if (Mod::get()->getSettingValue<bool>("hideGlowGameplayElements") && std::find(gameplayElements.begin(), gameplayElements.end(), p0->m_objectID) != gameplayElements.end()) p0->m_hasNoGlow = true;
			if (Mod::get()->getSettingValue<bool>("hideGlowFromBlocks") && !(std::find(gameplayElements.begin(), gameplayElements.end(), p0->m_objectID) != gameplayElements.end())) p0->m_hasNoGlow = true;
			if (dontSkip) PlayLayer::addObject(p0);
		}
		else PlayLayer::addObject(p0);
	}
};