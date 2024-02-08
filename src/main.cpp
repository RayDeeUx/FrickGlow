#include <Geode/Geode.hpp>
#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <regex>

using namespace geode::prelude;
using namespace geode::utils::string;

const std::regex glowSprite(".*_\\d+_.*\\.png");
const std::regex glowGameplay("(?:\\w+)?(?:[Bb](?:ump|oost)|[Rr]ing)_(?:\\d+_)?glow_001\\.png");
const std::regex glowPlayer(".*(?:robot|spider|ship|player|ball|bird|ufo|dart|wave|swing).*");

// hide gradients via GameObject (hooking, static_cast, m_fields by dank_meme, matcool, Firee) (string utils suggested by cgytrus)
// WINDOWS ONLY
#if defined(GEODE_IS_WINDOWS)
class $modify(MyGameObject, GameObject) {
    bool isGradient = false;
    static void onModify(auto & self)
    {
        self.setHookPriority("GameObject::createWithFrame", 1000);
        self.setHookPriority("GameObject::setVisible", 1000);
    }
    static GameObject* createWithFrame(char const* frameName) {
        GameObject* gameObject = GameObject::createWithFrame(frameName);
        if (!(Mod::get()->getSettingValue<bool>("enabled"))) return gameObject;
		if (!(Mod::get()->getSettingValue<bool>("hideGlowDeco"))) return gameObject;
        if (((strcmp(frameName, "emptyFrame.png") == 0) || (string::contains(frameName, "_gradient_"))))
            static_cast<MyGameObject*>(gameObject)->m_fields->isGradient = true;
		if (!(Mod::get()->getSettingValue<bool>("hideGlowDecoAdvanced"))) return gameObject;
		if (strcmp(frameName, "blockOutline_14_001.png") == 0 || strcmp(frameName, "blockOutline_15_001.png") == 0)
            static_cast<MyGameObject*>(gameObject)->m_fields->isGradient = true;
        return gameObject;
    }
    void setVisible(bool p0) {
        if (m_fields->isGradient)
			GameObject::setVisible(false);
		else
			GameObject::setVisible(p0);
    }
};
#endif

// hide glow via CCSprite (string utils suggested by cgytrus)
class $modify(MyCCSprite, CCSprite) {
	bool isGlowSprite = false;
    static void onModify(auto & self)
    {
        self.setHookPriority("CCSprite::createWithSpriteFrameName", 1000);
        self.setHookPriority("CCSprite::setVisible", 1000);
    }
	static CCSprite* createWithSpriteFrameName(char const* frameName) {
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(frameName);
        if (!(Mod::get()->getSettingValue<bool>("enabled"))) return sprite;
		if (Mod::get()->getSettingValue<bool>("hideGlowGameplayElements") && std::regex_match(frameName, glowGameplay))
			static_cast<MyCCSprite*>(sprite)->m_fields->isGlowSprite = true;
        if ((Mod::get()->getSettingValue<bool>("hideGlowFromBlocks")) && string::contains(frameName, "_glow_") && !(std::regex_match(frameName, glowGameplay)) && (std::regex_match(frameName, glowSprite) && !(std::regex_match(frameName, glowPlayer))))
			static_cast<MyCCSprite*>(sprite)->m_fields->isGlowSprite = true;
        return sprite;
    }
    void setVisible(bool p0) {
        if (m_fields->isGlowSprite)
			CCSprite::setVisible(false);
		else
			CCSprite::setVisible(p0);
    }
};

// disable gradient trigger (idea by ItsLever, optimization by PoweredByPie)
// WINDOWS AND ANDROID
#if defined(GEODE_IS_WINDOWS) || defined(GEODE_IS_ANDROID)
class $modify(MyPlayLayer, PlayLayer) {
	static void onModify(auto & self)
    {
        self.setHookPriority("PlayLayer::addObject", 1000);
    }
	TodoReturn addObject(GameObject* p0) {
        if (Mod::get()->getSettingValue<bool>("enabled") && Mod::get()->getSettingValue<bool>("disableGradientTriggers")) {
            bool dontSkip = true;
            if (p0->m_objectID == 2903) dontSkip = false;
            if (dontSkip) PlayLayer::addObject(p0);
        } else PlayLayer::addObject(p0);
	}
};
#endif