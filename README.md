# AiLive — The Galaxy Has Something to Say

**X4: Foundations gives you an empire. AiLive gives you people to answer to.**

Your captain has orders. Your rivals have reasons. The station you just saved has a story. And the officer you keep sending into impossible situations might have something to say about your leadership.

AiLive brings AI-driven conversation, memory, command and faction politics into X4's living universe through **Player2**. Talk to the people behind the ships. Give an officer a mission in your own words. Negotiate over a warship. Follow the intelligence, losses and decisions shaping the galaxy around you.

**Build the fleet. Know the people. Live with the consequences.**

This is **AiLive 2.1.0 RC1**, a public **release candidate** for players who want to help put that vision through its paces. Core systems are implemented; several newer systems have working, observed portions with further validation and development still underway. The feature sections below make that distinction explicit.

## Download

**[Download AiLive 2.1.0 RC1](https://github.com/KennyG1990/AiLive/releases/tag/v2.1.0-rc.1)** · **[Get the mod archive](https://github.com/KennyG1990/AiLive/releases/download/v2.1.0-rc.1/x4_ai_influence.rar)** · **[Report an issue](https://github.com/KennyG1990/AiLive/issues)**

Download **`x4_ai_influence.rar`** from the RC1 release assets. This is the supplied mod archive, published without repacking or changing its contents.

**Do not download GitHub's automatically generated “Source code” ZIP or TAR.GZ.** Those contain this public repository's documentation, not the playable mod.

## Implemented features — the people inside your empire

### Conversations with a past

Open the AiLive comm-link and speak to NPCs in natural language. Species personalities, mood, trust, memories and contextual suggestions give the exchange something to build on. The aim is a conversation that belongs to the character and the campaign you are actually playing.

The compact conversation panel and expanded comm channel bring the correspondent, conversation history, remembered facts and proposals into view. Remote comm-link support lets you reach suitable ship and station NPCs from the map, including cases where the normal interaction offers no Comm option.

### A navy you can actually talk to

Issue natural-language orders to subordinate captains and receive reports of what the game accepted, refused or completed. The implemented command system covers portions of combat, patrol, movement, follow, logistics and autonomous planning; exact command coverage is still being expanded and tested.

This is already more than a character saying “Aye, Commander.” The project tracker records live execution and engine readbacks for orders including patrol, follow, escort, movement and resupply, plus an energy-cell purchase followed through to delivered cargo. Other verbs still need specific live scenarios before they can be treated as proven.

### Rank means responsibility

Promote your officers through **seven naval ranks, from Lieutenant to Admiral**. Rank carries duties, reporting relationships and enforced command limits. An officer's authority persists, and the command system checks it when ships and wings are delegated.

Give an officer a mandate, delegate through the chain of command, relieve them when priorities change, and let reports travel back up. Mandate records, delegation, reporting lines, completion history and routed situation reports have recorded in-game proof. Officers can also recognize when an aging mission no longer fits their available forces.

### See the command structure behind the battle

The battle tracker brings your friendly command tree, ranks and order flow together. Follow who answers to whom and what orders are moving through the fleet. The friendly command view has been checked against live engine state; enemy intelligence and faction-specific views continue to receive further validation.

### Intelligence travels both ways

AiLive includes the player-to-faction and faction-to-player espionage systems, with character knowledge constrained by access and disclosure. The newer faction-to-faction network is also running in recorded live sessions: agents are placed between hostile factions, recalled when relations improve, and exposure creates consequences.

That does not make everyone all-knowing. The design is built around who has access to a fact, how it reached them, and whether it can be disclosed. The intelligence-broker sales portion remains under validation.

### A galaxy with a memory

Capital losses, sector captures and diplomatic declarations feed galactic news, the logbook and conversational context. The implemented influence engine combines measured pressure, model decisions and bounded game actions with chronicle memory.

The result is a foundation for a campaign whose history can matter after the notification disappears.

### Direct Player2 integration

The mod connects to **Player2 running on your PC** through its bundled HTTP transport. The default Player2 setup needs **no separate Python bridge and no user-supplied API key**. Keep Player2 running and signed in while you play.

## Already taking shape — implemented portions, work still underway

These systems have recorded live results or substantial implementation, but their full feature scope is **not yet complete**:

| System | What is working / recorded | What remains |
| --- | --- | --- |
| **Faction councils and strategic leadership** | Faction leaders reason from military strength, losses, relations and doctrine. Autonomous council activity has been observed. | Further live proof for sector claims, war goals, peace terms and event-driven escalation. |
| **Warship negotiations** | Player-to-faction and faction-to-faction ship sales have recorded owner and payment checks. | Commissioning new ships is parked; the broader pricing and negotiation flow continues to evolve. |
| **Faction purchasing power** | Economic purchasing limits and a mod-side reserve system exist; the tracker records a signed sale debiting a faction reserve. | Deferred initialization and remaining economic edge cases need further validation. |
| **Doctrine** | Player doctrine reaches officers; faction doctrine informs council reasoning. The field manual and structured operation-order example have live proof. | Broader after-action learning, lesson reassessment and the complete on-screen record. |
| **Longer conversation recall** | Conversation archiving, embedding and recall have been observed working. | An isolated recall test is still needed to distinguish retrieved history from facts also stored as important memories. |
| **Distress calls** | A real emergency produced a contact, a resolved outcome and a remembered result. | Interactive accept/decline paths still need their specific live checks. |
| **Order lifecycle reporting** | Finished and cancelled outcomes are observed, with newer outcomes implemented. | More proof for destruction, invalidation and superseded-order cases. |
| **Veterancy and battle honours** | Initial veterancy and battle-history work is built. | Decorated careers, promotion pacing and a unified promotion authority remain open. |

**These are the systems to explore with an RC mindset: working foundations, meaningful progress, and rough edges worth reporting.**

## Upcoming features — where the galaxy goes next

The Notion feature tracker separates specified plans from partial implementations and exploratory ideas. These are **roadmap items, not a promise that every feature is finished in RC1**, and no delivery dates are implied.

### Deeper diplomacy

Tribute, reparations, sector-transfer agreements, broader war-fatigue mechanics, and minor-faction defection or reintegration. The ambition is political relationships with stakes beyond a single conversation.

### More authority to delegate

Expand the working officer-to-officer command system toward governors, sector authority and vassal relationships. Further mandate work includes doctrine inheritance, intelligence leaks, objections and stronger links between an officer's decisions and their outcomes.

### A richer negotiation table

Further development of the **you give / balance / they give** offer-and-counteroffer experience: visible value, personality, trust, need, suspicion and purchasing power shaping a deal. Table-related implementation and live transactions exist, while the tracker still carries open negotiation design and completion work.

### Broader orders and logistics

Expand command coverage across trading and mining, fleet supply, collection, salvage, rescue and prospecting. Commander reinforcement requests are implemented but still await their live-loss validation; they rely on real replacement ships, not conjured fleets.

### Characters with longer careers

Cultural loyalty, crew pledges, relationship decay, decorated officer careers and richer histories for fallen captains. The planned destruction-history system aims to give a long-serving character a send-off worthy of the time you spent with them.

### Crises beyond the next fleet engagement

Specified outbreak systems include quarantine, medbay tiers and inoculant logistics. Planned station-security gameplay includes conversational standoffs and escalation into security responses, panic and combat.

### Voices, richer context and better backend controls

Species-oriented text-to-speech remains planned. Context retrieval and prompt architecture continue to develop, alongside a proposed endpoint/model picker with a clear connection test. Player2 remains the documented default for this release.

### Research directions, not committed features

Commander intelligence requests that create customers for espionage; factions remembering completed service when deciding how to treat you next; doctrine-aware refusals; and clearer map-level fronts. These are tracked opportunities, not scheduled promises.

## Install RC1

1. Install and launch **[Player2](https://player2.game)**, then sign in. Keep it running during play.
2. Download **`x4_ai_influence.rar`** from the [RC1 release assets](https://github.com/KennyG1990/AiLive/releases/tag/v2.1.0-rc.1) and extract it with a RAR-capable archive tool.
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
- Implemented features and live observations above are grounded in the project's Notion tracker. **This exact uploaded archive has not received a fresh end-to-end gameplay qualification as part of publication.**
- Some features have only partial coverage; AI replies, UI layouts, persistence and interactions with other mods can still expose defects.
- Use the installation instructions in **this README or the linked RC1 release page**. The archive's older README contains development-repository links, a ZIP filename and roadmap references that do not match this public RAR release.
- Report problems through **[AiLive Issues](https://github.com/KennyG1990/AiLive/issues)**. Include your X4 version, RC version, other installed mods, reproduction steps, and relevant redacted log lines or screenshots. Say what the character promised and what the game actually did.

## Package verification

| Item | Result |
| --- | --- |
| Archive | `x4_ai_influence.rar` |
| Release tag | `v2.1.0-rc.1` |
| Internal manifest | version `210`, dated `2026-10-22` |
| Archive size | 2,984,872 bytes |
| Contents | 67 files under one `x4_ai_influence/` directory |
| Archive integrity | Passed 7-Zip archive test |
| XML | All 23 XML files parsed successfully |
| UI manifest | All 33 referenced UI scripts present |
| Credential-pattern check | No matches for the checked common token/private-key patterns; not a full security audit |

SHA-256:

```text
4b2d26925dbc49bd82796754e7fb2f042147c050812873c200d19515d6d2502a
```

---

**Your next order could become an officer's mission. Your next deal could change who owns a warship. Your next conversation could give a familiar corner of the galaxy a face you remember.**

**Welcome aboard AiLive.**



## About this repository

This is AiLive's public release home: mod information, packaged downloads and issue reports. Development source and history are maintained separately.
