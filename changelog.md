# FrickGlow Changelog
## v1.4.5
- Forgot about spikes. Kicking myself in the shins right now.
## v1.4.4
- Make sure that `Hide Glow from Solids` actually hides glow from solid objects only.
  - ...except it's done properly this time, so solid objects marked as `NoTouch` also have their glow removed.
  - This actually restores the first change mentioned under v1.4.2, and remains that way because someone was (in)sane enough to ~~give me~~ compose a list of the object ID(s) of every solid in the game. Thanks Alphalaneous!
- Added `Exclude NoTouch Solid Objects` for those who prefer old behavior.
- Minor refactors here and there.
## v1.4.3
- Fix the bug where solids marked as NoTouch did not have their glow removed.
  - This actually undoes the first change mentioned under v1.4.2, and remains that way until someone is (in)sane enough to give me a list of the object ID of every solid in the game.
- Made Options API an optional dependency.
## v1.4.2
- Make sure that `Hide Glow from Solids` actually hides glow from solid objects only.
- Added `Exclude Invisible Objects from Hidden Glow` for when `Hide Glow from Solids` is enabled.
## v1.4.1
- Experimental iOS support.
## v1.4.0
- Finally found a consistent solution to hiding all glow decoration without crashing the game.
- Added Options API support.
## v1.3.5
- Port to 2.2074.
## v1.3.4
- Port to 2.206. Big thanks to CatXus, Aktimoose, ninXout, and hiimjustin000 for helping out with testing!
- Rename the mod ID per the Geode index's new anti-profanity guidelines.
- Refactor some member fields.
## v1.3.3
- macOS support! Yay!
- Option 1 of "Hide Glow Deco" is no longer exclusive to Windows.
## v1.3.2
- Fix a conflict with Weebify's Coins in Pause Menu mod, and hopefully all other mods in the future.
## v1.3.1
- *Finally* manage to resolve the incredibly rare incompat with Capeling's Gamemode Swapper mod. If anyone was curious what it was, FrickGlow would sometimes mistakenly hide the player if a level started with a mini-sized player (regardless of Testmode status). Sorry for putting you through the update fatigue!
## v1.3.0
- Refactor return type responsible for skipping objects, because alk is (rightfully) allergic to `TodoReturn` return types. Regardless of whether or not you understood the previous sentence, almost nothing changes for you, the enduser.
- Fix a trailing comma at one of the lists.
- Bring back (toggleable) original methods of hiding glow in light of levels such as Tether Trials by choccymilk15 and Space Invaders by Manix and LazerBlitz.
## v1.2.0
- Renaming per new Geode mod naming guidelines.
## v1.1.0
- Remove conflict with Capeling's Gamemode Swapper mod. As a consequence, macOS support removed.
## v1.0.0
- Initial release.