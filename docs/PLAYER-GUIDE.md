# AiLive player guide

[AiLive](../README.md) · [Downloads](https://github.com/KennyG1990/AiLive/releases) · [Community](https://discord.gg/5zwxzRvDY)

AiLive uses text communication. This guide covers installation, requirements and help with the packaged mod.

## Installation

**Grab the packaged mod archive from the latest release candidate's assets.** GitHub's automatic **Source code** ZIP/TAR.GZ downloads contain this public repository's documentation, not the playable mod.

1. Install and launch **[Player2](https://player2.game)**, then sign in. Keep it running during play.
2. [download the latest release here](https://github.com/KennyG1990/AiLive/releases), choose the packaged mod archive from its assets, and extract it with a compatible archive tool.
3. Place the included **`x4_ai_influence`** folder inside your **`X4 Foundations/extensions/`** directory. The final layout must include:

   ```text
   X4 Foundations/
     extensions/
       x4_ai_influence/
         content.xml
         ui.xml
         md/
         ui/
         lua3p/
   ```

4. Keep the folder name **`x4_ai_influence`** exactly as supplied. Avoid an extra nested `x4_ai_influence/x4_ai_influence` folder or a second installation of the same mod.
5. Start X4, check that AiLive is enabled under **Extensions**, and use **Speak to AI** on an eligible NPC. The **Comm-link (AiLive)** map interaction provides another entry point on supported targets.

**Requirements:** X4: Foundations on Windows and the Player2 desktop app. The package includes Windows native transport libraries. Recent project validation records reference **X4 9.00**; a compatibility matrix for older versions, other operating systems and other mods has not been established for this archive.

Player2's available models, connectivity and AI allowance affect responses. A local connection to the desktop app does not mean the selected model necessarily runs offline.

## Release-candidate notes

- **Back up your save and use a separate test save for RC testing.** This is an experimental build with systems that can affect orders, ownership, money and relationships.
- Feature coverage draws on the project's Notion tracker and developer live campaign reviews. The courier, diplomatic-delivery, interception and missing-officer examples in the [feature and development notes](FEATURES-AND-DEVELOPMENT.md#peace-has-to-make-it-through-the-gates) come from the review shared October 26, 2026. Check each release's notes for which changes it includes and its validation details.
- Some features have only partial coverage; AI replies, UI layouts, persistence and interactions with other mods can still expose defects.
- Use the installation instructions in **this guide and the notes accompanying your downloaded release**.
- Report problems through **[AiLive Issues](https://github.com/KennyG1990/AiLive/issues)**. Include your X4 version, RC version, other installed mods, reproduction steps, and relevant redacted log lines or screenshots. Say what the character promised and what the game actually did.

## Further reading

See the [feature and development notes](FEATURES-AND-DEVELOPMENT.md) for the detailed briefings, earlier gameplay records, development material and historical package checks moved from the front page. The [release page](https://github.com/KennyG1990/AiLive/releases) retains the release notes and downloadable assets.
