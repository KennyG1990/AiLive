# AiLive feature and development notes

[AiLive](../README.md) · [Player guide](PLAYER-GUIDE.md) · [Release notes and downloads](https://github.com/KennyG1990/AiLive/releases) · [Issue tracker](https://github.com/KennyG1990/AiLive/issues)

## About these records

This page preserves the detailed feature briefings, campaign records, development notes and historical package checks previously published on AiLive's front page. They were moved from README revision `fb4ce5d16e7080ce37b4e57a05ce2b9ef161ebcf` on October 26, 2026.

The status descriptions below reflect their original records. Some roadmap entries predate later work; they are not a current release inventory. Consult the notes accompanying the release you download for its included changes. The earlier voice proposal is historical: AiLive uses text communication.

> **Boarding notice:** AiLive is an experimental Windows mod available as release candidates. Core systems are implemented; newer systems have partial coverage and ongoing validation. See each release's notes for its included changes and validation details. Bring a separate test save. The paint is still drying.

## Peace has to make it through the gates.

A council decides it wants peace. A fighter leaves with the proposal. Two gates stand between that decision and the people who need to hear it.

**This happened in a live X4 campaign:** the Antigone council sought peace with the Holy Order. An Antigone fighter flew two gates to deliver the proposal. Only after it arrived did the Holy Order council weigh it.

Now put a spy in the path of a courier.

In another live encounter, a Buccaneers spy intercepted one of the player's couriers and leaked his orders through the existing espionage system. It happened without the player prompting the interception.

**The connection is the gameplay: councils make decisions, ships carry the messages, delivery determines when they can be considered, and espionage can expose the orders travelling through that same universe.**

### Your intelligence has a journey.

A scout had a reconnaissance report, but was out of communications range. The report was held. With no free pilots available to carry it, the scout reasoned that it had to deliver the report personally, flew back, and the report arrived.

A courier looking for a missing recipient travels to the last known location and searches. If it cannot get through, it reports what happened. One courier, pinned down in Argon Prime, reported that it never got out.

Distance matters. A delayed ship means delayed information. Your next briefing has a journey behind it.

### An empty chair still belongs to someone.

Commodore Xiaowen Jackson was missing from her post and from the crews of the player's 42 ships and two stations. CORPS marked her **MISSING** beside her billet and held the position for her. The command structure reflected the person who was actually absent.

*From the developer's live campaign review, shared October 26, 2026. These are demonstrated gameplay examples; future ambitions appear separately in the roadmap.*

**Give an order. Send the messenger. See who learns about it before you do.**

## 📡 What's on the other end of the comm-link?

| Talk to your universe | Command your people | Follow the consequences |
| :--- | :--- | :--- |
| Natural-language NPC conversations with personality, mood, trust and remembered context. | Natural-language captain orders, seven naval ranks and a working chain of command. | Espionage, galactic news and an influence engine connecting decisions to bounded game actions. |
| Remote contact with suitable ship and station NPCs. | Mandates, officer delegation and situation reports travelling back up the chain. | A record of losses, sector captures and diplomatic events that can feed future conversations. |

### “Captain, here's the plan.”

Put the mission into words. AiLive's command system has recorded live results for patrol, follow, escort, movement and resupply—including an energy-cell purchase followed through to delivered cargo.

There is something deeply satisfying about a captain doing the job you actually asked for. There is also something very useful about hearing what the game refused. AiLive reports accepted, refused and completed orders; exact command coverage is still expanding.

### Lieutenant today. Admiral is your call.

Seven ranks, persistent authority, enforced command limits. Promote your officers, assign responsibilities and delegate down the chain. Watch the friendly battle tracker bring ranks, reporting relationships and order flow together.

You are building a navy. Give it a chain of command.

### Loose lips. Expensive ships.

Player-to-faction and faction-to-player espionage are implemented, and the newer faction-to-faction network has recorded live placement, recall and exposure consequences. Who knows a fact—and whether they can share it—matters.

Warship sales are also taking shape, with recorded ownership and payment checks in player-to-faction and faction-to-faction transactions. The broader negotiation experience is still developing; commissioning new ships is parked.

### The news is about the galaxy you're playing in.

Capital losses. Sector captures. Diplomatic declarations. Events feed the logbook and conversational context, giving the next exchange something more interesting to draw on than small talk.

The ambition: that familiar corner of space starts feeling like somewhere with a history.

<details>
<summary><strong>📖 Open the field manual: implemented features and evidence</strong></summary>

### The complete feature briefing

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


</details>

<details>
<summary><strong>🔧 Look inside the shipyard: councils, doctrine, distress calls and other developing systems</strong></summary>

### Under construction — what works and what is still open

These systems have recorded live results or substantial implementation, but their full feature scope is **not yet complete**:

| System | What is working / recorded | What remains |
| --- | --- | --- |
| **Faction councils and strategic leadership** | Faction leaders reason from military strength, losses, relations and doctrine. Autonomous council activity has been observed. In a live campaign, an Antigone peace proposal travelled two gates by fighter before the Holy Order council considered it. | Further live proof for sector claims, war goals, negotiated peace outcomes and event-driven escalation. |
| **Warship negotiations** | Player-to-faction and faction-to-faction ship sales have recorded owner and payment checks. | Commissioning new ships is parked; the broader pricing and negotiation flow continues to evolve. |
| **Faction purchasing power** | Economic purchasing limits and a mod-side reserve system exist; the tracker records a signed sale debiting a faction reserve. | Deferred initialization and remaining economic edge cases need further validation. |
| **Doctrine** | Player doctrine reaches officers; faction doctrine informs council reasoning. The field manual and structured operation-order example have live proof. | Broader after-action learning, lesson reassessment and the complete on-screen record. |
| **Longer conversation recall** | Conversation archiving, embedding and recall have been observed working. | An isolated recall test is still needed to distinguish retrieved history from facts also stored as important memories. |
| **Distress calls** | A real emergency produced a contact, a resolved outcome and a remembered result. | Interactive accept/decline paths still need their specific live checks. |
| **Order lifecycle reporting** | Finished and cancelled outcomes are observed, with newer outcomes implemented. | More proof for destruction, invalidation and superseded-order cases. |
| **Veterancy and battle honours** | Initial veterancy and battle-history work is built. | Decorated careers, promotion pacing and a unified promotion authority remain open. |

**These are the systems to explore with an RC mindset: working foundations, meaningful progress, and rough edges worth reporting.**


</details>

## 🔭 The horizon: where we want to take this

The Notion feature tracker separates specified plans from partial implementations and exploratory ideas. These are **roadmap items, not a promise that every feature is finished in the current release candidate**, and no delivery dates are implied.

### Deeper diplomacy

Tribute, reparations, sector-transfer agreements, broader war-fatigue mechanics, and minor-faction defection or reintegration. The ambition is political relationships with stakes beyond a single conversation.

### More authority to delegate

Expand the working officer-to-officer command system toward governors, sector authority and vassal relationships. Further mandate work includes doctrine inheritance, broader intelligence consequences, objections and stronger links between an officer's decisions and their outcomes.

### A richer negotiation table

Further development of the **you give / balance / they give** offer-and-counteroffer experience: visible value, personality, trust, need, suspicion and purchasing power shaping a deal. Table-related implementation and live transactions exist, while the tracker still carries open negotiation design and completion work.

### Broader orders and logistics

Expand command coverage across trading and mining, fleet supply, collection, salvage, rescue and prospecting. Commander reinforcement requests are implemented but still await their live-loss validation; they rely on real replacement ships, not conjured fleets.

### Characters with longer careers

Cultural loyalty, crew pledges, relationship decay, decorated officer careers and richer histories for fallen captains. The planned destruction-history system aims to give a long-serving character a send-off worthy of the time you spent with them.

### Crises beyond the next fleet engagement

Specified outbreak systems include quarantine, medbay tiers and inoculant logistics. Planned station-security gameplay includes conversational standoffs and escalation into security responses, panic and combat.

### Historical voice proposal, richer context and backend controls

The earlier roadmap listed species-oriented text-to-speech as planned. That proposal is retained here as history; the current direction is text communication. Context retrieval and prompt architecture continue to develop, alongside a proposed endpoint/model picker with a clear connection test. Player2 remains the documented default for this release.

### Research directions, not committed features

Commander intelligence requests that create customers for espionage; factions remembering completed service when deciding how to treat you next; doctrine-aware refusals; and clearer map-level fronts. These are tracked opportunities, not scheduled promises.

<details>
<summary><strong>🧾 Inspect the cargo manifest: archive checks and SHA-256</strong></summary>

### Historical package verification — initial release candidate

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

</details>
