#include <ninxout.options_api/include/API.hpp>
#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

static const std::set<int> iHateGradients = {503, 504, 505, 1008, 1009, 1010, 1011, 1012, 1013, 1269, 1270, 1271, 1272, 1273, 1274, 1291, 1292, 1293, 1758, 1759, 1760, 1761, 1762, 1763, 1886, 1887, 1888};
static const std::set<int> gameplayElements = {10, 11, 12, 13, 35, 36, 45, 46, 47, 67, 84, 99, 101, 111, 140, 141, 200, 201, 202, 203, 286, 287, 660, 745, 746, 747, 748, 1022, 1330, 1331, 1332, 1333, 1334, 1594, 1704, 1751, 1933, 2063, 2064, 2902, 2926, 3004, 3005, 3027};
static const std::set<int> invisibleObjects = {144, 145, 146, 147, 204, 205, 206, 459, 673, 674, 740, 741, 742, 1340, 1341, 1342, 1343, 1344, 1345};

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
		const bool inGameplayElements = std::binary_search(gameplayElements.begin(), gameplayElements.end(), theObject->m_objectID);
		const bool isInvisibleObject = std::binary_search(invisibleObjects.begin(), invisibleObjects.end(), theObject->m_objectID);
		if (Mod::get()->getSettingValue<bool>("hideGlowGameplayElements") && inGameplayElements) theObject->m_hasNoGlow = true;
		if (Mod::get()->getSettingValue<bool>("hideGlowFromBlocks") && !inGameplayElements && (theObject->m_objectType == GameObjectType::Solid || theObject->m_objectType == GameObjectType::Hazard || theObject->m_objectType == GameObjectType::Breakable || theObject->m_objectType == GameObjectType::Slope)) {
			if (!Mod::get()->getSettingValue<bool>("excludeInvisibleFromHideGlow") || !isInvisibleObject) theObject->m_hasNoGlow = true;
		}
		PlayLayer::addObject(theObject);
	}
};

#define ADD_TOGGLE(displayName, settingsID, detailedDesc)\
	OptionsAPI::addPreLevelSetting<bool>(\
		displayName,\
		settingsID""_spr,\
		[](GJGameLevel*) {\
			const bool origValue = Mod::get()->getSettingValue<bool>(settingsID);\
			Mod::get()->setSettingValue<bool>(settingsID, !origValue);\
		},\
		[](GJGameLevel*) {\
			return Mod::get()->getSettingValue<bool>(settingsID);\
		},\
		"<cl>(From FrickGlow)</c>\n" detailedDesc\
	);

$on_mod(Loaded) {
	if (!Mod::get()->getSettingValue<bool>("optionsAPI")) return;
	ADD_TOGGLE("Hide Glow/Gradient Decoration", "hideGlowDecoFinal", "Hides all glow/gradient decoration in a level.")
	ADD_TOGGLE("Hide Glow from Solids", "hideGlowFromBlocks", "Hide glow from solid objects.")
	ADD_TOGGLE("Exclude Invisible Objects from Hidden Glow", "excludeInvisibleFromHideGlow", "Excludes invisible objects when <cl>Hide Glow from Solids</c> is enabled.")
	ADD_TOGGLE("Hide Glow from Gameplay Elements", "hideGlowGameplayElements", "Hide glow from gameplay elements.\nMore specifically: jump orbs, speed portals, and jump pads.")
	ADD_TOGGLE("Hide Glow from Gradient Triggers", "disableGradientTriggers", "Hide glow from gradient triggers.\n<c_>(Not recommended unless if you know what you're doing.)</c>")
}