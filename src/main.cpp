#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <list>

using namespace geode::prelude;

std::list<int> iHateGradients = {503, 504, 505, 1008, 1009, 1010, 1011, 1012, 1013, 1269, 1270, 1271, 1272, 1273, 1274, 1291, 1292, 1293, 1758, 1759, 1760, 1761, 1762, 1763, 1886, 1887, 1888};
std::list<int> gameplayElements = {10, 11, 12, 13, 35, 36, 45, 46, 47, 67, 84, 99, 101, 111, 140, 141, 200, 201, 202, 203, 286, 287, 660, 745, 746, 747, 748, 1022, 1330, 1331, 1332, 1333, 1334, 1594, 1704, 1751, 1933, 2063, 2064, 2902, 2926, 3004, 3005, 3027, };

// disable glowy objects (idea by TechStudent10)
class $modify(MyPlayLayer, PlayLayer) {
	TodoReturn addObject(GameObject* p0) {
        if (Mod::get()->getSettingValue<bool>("enabled")) {
            bool dontSkip = true;
            if (Mod::get()->getSettingValue<bool>("disableGradientTriggers") && p0->m_objectID == 2903) {
                dontSkip = false;
            }
            if (Mod::get()->getSettingValue<bool>("hideGlowDeco") && std::find(iHateGradients.begin(), iHateGradients.end(), p0->m_objectID) != iHateGradients.end()) {
                dontSkip = false;
            }
            if (Mod::get()->getSettingValue<bool>("hideGlowGameplayElements") && std::find(gameplayElements.begin(), gameplayElements.end(), p0->m_objectID) != gameplayElements.end()) {
                p0->m_hasNoGlow = true;
            }
            if (Mod::get()->getSettingValue<bool>("hideGlowFromBlocks") && !(std::find(gameplayElements.begin(), gameplayElements.end(), p0->m_objectID) != gameplayElements.end())) {
                p0->m_hasNoGlow = true;
            }
            if (dontSkip) PlayLayer::addObject(p0);
        }
        else PlayLayer::addObject(p0);
	}
};