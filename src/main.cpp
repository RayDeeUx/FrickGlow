#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

constexpr std::array iHateGradients = {503, 504, 505, 1008, 1009, 1010, 1011, 1012, 1013, 1269, 1270, 1271, 1272, 1273, 1274, 1291, 1292, 1293, 1758, 1759, 1760, 1761, 1762, 1763, 1886, 1887, 1888};
constexpr std::array gameplayElements = {10, 11, 12, 13, 35, 36, 45, 46, 47, 67, 84, 99, 101, 111, 140, 141, 200, 201, 202, 203, 286, 287, 660, 745, 746, 747, 748, 1022, 1330, 1331, 1332, 1333, 1334, 1594, 1704, 1751, 1933, 2063, 2064, 2902, 2926, 3004, 3005, 3027};

class $modify(MyGameObject, GameObject) {
	static void onModify(auto & self) {
		(void) self.setHookPriority("GameObject::setVisible", -3999);
	}
	void setVisible(bool isVisible) {
		if (!PlayLayer::get() || !Mod::get()->getSettingValue<bool>("hideGlowDecoFinal")) return GameObject::setVisible(isVisible);
		if (std::ranges::find(iHateGradients, this->m_objectID) != iHateGradients.end()) return GameObject::setVisible(false);
		GameObject::setVisible(isVisible);
	}
};

// disable glowy objects (idea by TechStudent10, original concept by ItzLever)
class $modify(MyPlayLayer, PlayLayer) {
	void addObject(GameObject* theObject) {
		if (!Mod::get()->getSettingValue<bool>("enabled")) return PlayLayer::addObject(theObject);
		if (Mod::get()->getSettingValue<bool>("disableGradientTriggers") && theObject->m_objectID == 2903) return;
		const bool inGameplayElements = std::ranges::find(gameplayElements, theObject->m_objectID) != gameplayElements.end();
		if (Mod::get()->getSettingValue<bool>("hideGlowGameplayElements") && inGameplayElements) theObject->m_hasNoGlow = true;
		if (Mod::get()->getSettingValue<bool>("hideGlowFromBlocks") && !inGameplayElements) theObject->m_hasNoGlow = true;
		PlayLayer::addObject(theObject);
	}
};