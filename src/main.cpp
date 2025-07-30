#include <ninxout.options_api/include/API.hpp>
#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

static const std::set iHateGradients = {503, 504, 505, 1008, 1009, 1010, 1011, 1012, 1013, 1269, 1270, 1271, 1272, 1273, 1274, 1291, 1292, 1293, 1758, 1759, 1760, 1761, 1762, 1763, 1886, 1887, 1888};
static const std::set gameplayElements = {10, 11, 12, 13, 35, 36, 45, 46, 47, 67, 84, 99, 101, 111, 140, 141, 200, 201, 202, 203, 286, 287, 660, 745, 746, 747, 748, 1022, 1330, 1331, 1332, 1333, 1334, 1594, 1704, 1751, 1933, 2063, 2064, 2902, 2926, 3004, 3005, 3027};
static const std::set invisibleObjects = {144, 145, 146, 147, 204, 205, 206, 459, 673, 674, 740, 741, 742, 1340, 1341, 1342, 1343, 1344, 1345};
// numbers collected by alphalaneous from Object Summary mod. i'm sure they won't mind if i yoink this
static const std::set solidObjects = { 1, 2, 3, 4, 6, 7, 40, 62, 63, 64, 65, 66, 68, 69, 70, 71, 72, 74, 75, 76, 77, 78, 81, 82, 83, 90, 91, 92, 93, 94, 95, 96, 116, 117, 118, 119, 121, 122, 143, 146, 147, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 192, 194, 195, 196, 197, 204, 206, 207, 208, 209, 210, 212, 213, 215, 219, 220, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 260, 261, 263, 264, 265, 267, 268, 269, 270, 271, 272, 274, 275, 289, 291, 294, 295, 305, 307, 321, 323, 326, 327, 331, 333, 337, 339, 343, 345, 349, 351, 353, 355, 369, 370, 371, 372, 467, 468, 469, 470, 471, 475, 483, 484, 492, 493, 651, 652, 661, 662, 663, 664, 665, 666, 673, 674, 711, 712, 726, 727, 728, 729, 886, 887, 1154, 1155, 1156, 1157, 1202, 1203, 1204, 1208, 1209, 1210, 1220, 1221, 1222, 1226, 1227, 1260, 1262, 1264, 1338, 1339, 1340, 1341, 1342, 1343, 1344, 1345, 1743, 1744, 1745, 1746, 1747, 1748, 1749, 1750, 1903, 1904, 1905, 1906, 1907, 1910, 1911 };
static const std::set hazardObjects = { 8, 9, 39, 61, 88, 89, 98, 103, 135, 144, 145, 177, 178, 179, 183, 184, 185, 186, 187, 188, 205, 216, 217, 218, 243, 244, 363, 364, 365, 392, 397, 398, 399, 421, 422, 446, 447, 458, 459, 667, 678, 679, 680, 720, 740, 741, 742, 768, 918, 919, 989, 991, 1327, 1328, 1582, 1584, 1619, 1620, 1701, 1702, 1703, 1705, 1706, 1707, 1708, 1709, 1710, 1711, 1712, 1713, 1714, 1715, 1716, 1717, 1718, 1719, 1720, 1721, 1722, 1723, 1724, 1725, 1726, 1727, 1728, 1729, 1730, 1731, 1732, 1733, 1734, 1735, 1736, 2012, 3034, 3035, 3036, 3037, 3610, 3611 };
// numbers collected by ery again
static const std::set particleSpriteObjects = { 3825, 3828, 3958, 3959, 3960 };
static const std::set particleSpriteObjectExtras = { 3827, 3832, 3961, 3963, 3969, 3973 };

class $modify(MyGameObject, GameObject) {
	static void onModify(auto & self) {
		(void) self.setHookPriority("GameObject::setVisible", -3999);
	}
	void setVisible(bool isVisible) {
		if (!PlayLayer::get() || !Mod::get()->getSettingValue<bool>("enabled") || !Mod::get()->getSettingValue<bool>("hideGlowDecoFinal")) return GameObject::setVisible(isVisible);
		if (const bool isGradientObject = std::ranges::binary_search(iHateGradients.begin(), iHateGradients.end(), this->m_objectID)) return GameObject::setVisible(false);
		GameObject::setVisible(isVisible);
	}
};

// disable glowy objects (idea by TechStudent10, original concept by ItzLever)
class $modify(MyPlayLayer, PlayLayer) {
	void addObject(GameObject* theObject) {
		if (!Mod::get()->getSettingValue<bool>("enabled")) return PlayLayer::addObject(theObject);
		const int theID = theObject->m_objectID;
		if (Mod::get()->getSettingValue<bool>("disableGradientTriggers") && theID == 2903) return;
		const bool inGameplayElements = std::ranges::binary_search(gameplayElements.begin(), gameplayElements.end(), theID);
		const bool isInvisibleObject = std::ranges::binary_search(invisibleObjects.begin(), invisibleObjects.end(), theID);
		const bool isSolidObject = std::ranges::binary_search(solidObjects.begin(), solidObjects.end(), theID);
		const bool isHazardObject = std::ranges::binary_search(hazardObjects.begin(), hazardObjects.end(), theID);
		const bool isParticleSprite = std::ranges::binary_search(particleSpriteObjects.begin(), particleSpriteObjects.end(), theID);
		const bool isParticleSpriteExtra = std::ranges::binary_search(particleSpriteObjectExtras.begin(), particleSpriteObjectExtras.end(), theID);
		if (Mod::get()->getSettingValue<bool>("hideGlowParticles") && isParticleSprite) return;
		if (Mod::get()->getSettingValue<bool>("hideGlowParticlesExtra") && isParticleSpriteExtra) return;
		if (Mod::get()->getSettingValue<bool>("hideGlowGameplayElements") && inGameplayElements) theObject->m_hasNoGlow = true;
		if (Mod::get()->getSettingValue<bool>("hideGlowFromBlocks") && (isSolidObject || isHazardObject)) {
			if (theObject->m_objectType == GameObjectType::Decoration) {
				if (!Mod::get()->getSettingValue<bool>("excludeNoTouch")) theObject->m_hasNoGlow = true;
			} else if (isInvisibleObject) {
				if (!Mod::get()->getSettingValue<bool>("excludeInvisibleFromHideGlow")) theObject->m_hasNoGlow = true;
			} else {
				theObject->m_hasNoGlow = true;
			}
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
	ADD_TOGGLE("Hide Glow/Gradient Particles", "hideGlowParticles", "Hides the following object IDs: 3825, 3828, 3958, 3959, and 3960.")
	ADD_TOGGLE("Hide Glow/Gradient Particles (Part Two)", "hideGlowParticlesExtra", "Hides the following object IDs: 3827, 3832, 3961, 3963, 3969, and 3973.")
	ADD_TOGGLE("Hide Glow from Solids", "hideGlowFromBlocks", "Hide glow from solid objects.")
	ADD_TOGGLE("Exclude NoTouch Solid Objects", "excludeNoTouch", "Exclude solid objects marked as NoTouch when <cl>Hide Glow from Solids</c> is enabled.")
	ADD_TOGGLE("Exclude Invisible Objects from Hidden Glow", "excludeInvisibleFromHideGlow", "Excludes invisible objects when <cl>Hide Glow from Solids</c> is enabled.")
	ADD_TOGGLE("Hide Glow from Gameplay Elements", "hideGlowGameplayElements", "Hide glow from gameplay elements.\nMore specifically: jump orbs, speed portals, and jump pads.")
	ADD_TOGGLE("Hide Glow from Gradient Triggers", "disableGradientTriggers", "Hide glow from gradient triggers.\n<c_>(Not recommended unless if you know what you're doing.)</c>")
}