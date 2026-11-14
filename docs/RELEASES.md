# 📦 AiLive Releases & Version History

[![Home](https://img.shields.io/badge/🌌_AiLive_Home-1d3557?style=for-the-badge)](../README.md)
[![Download AiLive](https://img.shields.io/badge/🚀_Download_AiLive-00b4d8?style=for-the-badge)](https://github.com/KennyG1990/AiLive/releases)
[![Player Guide](https://img.shields.io/badge/📖_Player_Guide-f77f00?style=for-the-badge)](PLAYER-GUIDE.md)
[![Read Docs](https://img.shields.io/badge/📚_Read_Docs-2a9d8f?style=for-the-badge)](READ-DOCS.md)
[![Under the Hood](https://img.shields.io/badge/🛠️_Under_the_Hood-e63946?style=for-the-badge)](UNDER-THE-HOOD.md)
[![Feature Notes](https://img.shields.io/badge/📋_Feature_Notes-7209b7?style=for-the-badge)](FEATURES-AND-DEVELOPMENT.md)
[![Discord](https://img.shields.io/badge/💬_Join_the_Fleet-5865F2?style=for-the-badge)](https://discord.gg/5zwxzRvDY)

---

## 🚀 Latest Release: `v2.8.0-rc.1` — *First Days in Command*

> 📥 **[Download `x4_AiLive-2.8.0.zip` on GitHub Releases](https://github.com/KennyG1990/AiLive/releases/tag/v2.8.0-rc.1)**
> *(Always download the **`x4_AiLive-*.zip`** package under **Assets**—do not download GitHub's automatic "Source code" zip!)*

**Upgrading from `2.7.0`:** replace the whole `x4_ai_influence` folder, then **load your save** (not just a UI reload). The extension list shows **2.80**. Keep a backup of your save: this is a beta build.

### ⚠️ Still important if you skipped `2.4.0`: the save-safety fix
Builds **`2.3.0` and earlier** could corrupt AiLive's saved memory if the AI model emitted multibyte typographic characters that were split in half during string truncation. **`v2.4.0-rc.1` and later sanitize every text string before it reaches the save.**

---

## 🗓️ Release Timeline & What's Inside Each Build

### 🧭 [`v2.8.0-rc.1` — First Days in Command](https://github.com/KennyG1990/AiLive/releases/tag/v2.8.0-rc.1) *(Nov 13, 2026)*
**A new commander can now find their feet.** The hub opens on nine things to try, your second-in-command writes to you as you do them, orders report how they really ended, and losses are answered for. About 90 builds since 2.7.0. **A beta: expect bugs.**

* **In this build:**
  * **🎓 Getting Started:** nine first-days tasks ticked by really doing them, letters from your second-in-command, a guide page for every part of AiLive and a plain-words glossary (`THE WORLD > GETTING STARTED`).
  * **📡 Orders that tell the truth:** a ship that arrived says so, ORDER FLOW names orders in plain words, orders reach ships down the chain, and a captain can take a matter to their superior and bring back the answer.
  * **🕯️ Losses:** survivors are a call that asks you, the memorial keeps a loss file for each ship, and officers remember where ships were lost.
  * **💰 Trade:** station managers ask you to supply real open orders and thank you on delivery; captains sell as well as buy and can read the local market; `POWER > TRADE > REQUESTS TO YOU`.
  * **🗣️ The People:** what each realm's people believe about you and how far it moves their council (`INFLUENCE > THE PEOPLE`).
  * **💬 Conversations:** the rail names what the other person knows in whole words; the expanded view keeps SEND clear of the video.
* **Built & Gate-Tested (Waiting for First Live Occurrence):** a battle of six or more sides on a news card; a manager's counter-offer; a council hearing the people's pressure again after refusing it.
* **Known Issues:** a letter that arrives while the hub is open is easy to miss (it is in Messages); an offer that names a total can be signed as an hourly contract; a lone move order shows as under way after arrival; controller use of the hub is untested.

### 🌌 [`v2.7.0-rc.1` — The Living Galaxy](https://github.com/KennyG1990/AiLive/releases/tag/v2.7.0-rc.1) *(Nov 11, 2026)*
**The galaxy now has a story you are in the middle of.** Crises between realms run as storylines with chapters, rulers proclaim their moves, a newscast reports them, and your own territory, trade and officers each get their own screens and voices. About 450 changes since 2.6.0. **A beta: expect bugs.**

* **In this build:**
  * **📜 Storylines & Proclamations:** tension, ultimatum, war and peace as chapters (INFLUENCE > STORYLINES); rulers proclaim public moves on a full card (`CTRL+SHIFT+N`); councils sit about every 8 game hours and an ultimatum runs its full deadline.
  * **📰 Galactic News:** an anchor who remembers recent headlines, a weekly summary, and reports on power crises, sector control and epidemics.
  * **🏛️ GOVERNMENT & THE COURT:** your sectors and stations and who governs them, how other realms are ruled, and who speaks for you at each court.
  * **💰 POWER & Trade:** sworn realms, loans, trade pressure, standing supply contracts agreed in conversation with station managers, and "buy nearby, then deliver" orders for captains.
  * **🎓 Fleet School Battle Exam:** officers escort a convoy against raiders on radar alone, with a briefing, questions, a plan and a turn-by-turn review.
  * **🎖️ Officers:** promotions inside the chain, Marine pilots with their own ranks, more mission kinds, and every notice written in a person's own words.
  * **🧹 The Hub:** explainer captions removed from every tab; many fixes.
* **Built & Gate-Tested (Waiting for First Live Occurrence):** an order for a ship further down the chain passed on by your admiral; a captain abroad asking you for orders when an ultimatum lands; a realm with no reserves no longer repeating reinforcement orders; one-message "buy and sell" orders.
* **Known Issues:** the chain of command is hard to learn without a military background and an officer who cannot help does not yet say who can (a fix is planned); controller use of the hub is untested; a 2.6.0 save has not been tested against this build specifically.

### 🧭 [`v2.6.0-rc.1` — The Command Hub](https://github.com/KennyG1990/AiLive/releases/tag/v2.6.0-rc.1) *(Nov 5, 2026)*
**Your whole command on one screen.** The hub (`CTRL+SHIFT+U`) gains a tab for every part of it - FLEET, CORPS, DOCTRINE, DOSSIER, INFLUENCE, INTEL, POWER, THE WORLD, SETTINGS and DEBUG - your officers call you and file routine reports in the native Logbook, and you can write your own lore and rules for how the galaxy tells its story.

* **Proven in Game:**
  * **🧭 The Command Hub:** FLEET (the operations room and the campaigns you uncovered), CORPS (chain of command, insignia, offices, honours, bonds), DOCTRINE (honours, the operation order sheet, ranks), DOSSIER (every realm you know and its representative), INFLUENCE (the councils), INTEL (what you know, what your ships saw, who wants it), POWER, SETTINGS on one page, DEBUG systems health.
  * **🌍 THE WORLD:** HOUSE RULES, PUBLIC FACTS and each people's TRADITIONS reach the characters they touch (an Argon representative quoted the commander's fact back), and never change dice, money, ships or orders.
  * **📞 Officers Call and Report:** an officer's call rings (answer with `CTRL+SHIFT+B`); routine reports go to the **Logbook** with Show on Map; reports carry the engine's own failure records.
  * **🤝 Officer Ties:** your officers know who they served with and where, from the service record ("fifty days within Squadron 1").
  * **🧭 First-Run Guide:** a short setup guide the first time you open the hub on a save.
* **Built & Gate-Tested (Waiting for First Live Occurrence):** earned contacts across a full save/load, council grievance pacing, capture memory, comrades and at-odds ties in conversation.
* **Known Issues:** selling intelligence can show a PAYMENT REQUESTED card with you paying - do not confirm it; an unreachable operation leg is re-issued every review until you stand the operation down; "your wing" can be given to the commander's own ship.

### 🎖️ [`v2.5.0-rc.1` — The Chain of Command](https://github.com/KennyG1990/AiLive/releases/tag/v2.5.0-rc.1) *(Oct 29, 2026)*
**Your officers now serve in a real chain of command.** The CORPS board shows every seat and who holds it, officers learn by doing, a commander forms a wing from the ships you name, people tell fact from rumour, and news travels at the speed of the jump gates.

* **Proven in Game:**
  * **🎖️ The CORPS Board (`AiLive hub > CORPS`):** Every seat from Ship Command to the Fleet, who holds it, acting or in his own right, and who he reports to. Open an officer's file and **HAIL** him from it; **Orders of the Day** list what waits for your decision, and **KEEP ACTING** settles an officer acting above his rank.
  * **📈 Officers Learn by Doing:** Skill rises from the real tasks an officer carries out (seen live: a finished patrol raised a captain's piloting from 0 to 1).
  * **✈️ A Wing From the Ships You Name:** *"Take Dragon Raiders CPJ-448 and RXO-385 under your command as a defence wing for the Aurora"* — the named ships are taken first and the wing holds its defence role.
  * **📰 The Newspaper (`NEWS` tab):** The galaxy's news laid out as THE PRESS.
  * **🛰️ News at the Game's Pace:** Far-off events reach people a quarter of an hour per jump gate later; those who have not heard yet do not know.
  * **💾 Journal Restore:** The backup journal restores AiLive's records end to end.
* **Built & Gate-Tested (Waiting for First Live Occurrence):**
  * **⚓ An Acting Officer Holds His Post in Full:** command, knowledge and the decision under fire follow the post; pay, honours and promotion follow his own rank. New settings: *An acting appointment carries its post's command* and *Ships a post commands* (`SETTINGS > MILITARY > PROMOTIONS`).
  * **🪪 Fleet Rank on the Comm Channel:** your captain's rank first, then his job.
  * **🛡️ Officers Under Fire:** ships defend themselves under your standing orders; a Commander or above decides how to fight or sends a situation report up the chain.
  * **🧠 People Who Think for Themselves:** fact told from rumour, belief shaped by character, bluffs rolled, memories that fade and condense.
  * **🕵️ Spies and Secrets:** named agents with character sheets, factions that decide to spy, security clearances, counter-intelligence run by a named officer.
  * **⚖️ Careers and Justice:** superiors look after careers, promotions by the regulations, and a Code of Service Discipline.
  * **🏛️ Councils and the Economy:** councils cite dated harms, war fatigue wears realms down, every credit you spend lands once in the payee's treasury, and the evening newscast keeps the war fronts its news is about.

---

### 📡 [`v2.4.0-rc.1` — Comms Are a Resource](https://github.com/KennyG1990/AiLive/releases/tag/v2.4.0-rc.1) *(Oct 26, 2026)*
**Who you can reach now depends on where you are.** Beyond your sector comm range, you dispatch physical courier ships that fly through jump gates, track down moving recipients, and return with their answer—and AI faction rulers must do the exact same thing.

* **Proven in Game:**
  * **📡 Comms Range (`SETTINGS > OTHER > Comms range`):** Choose `OFF` (talk anywhere), `ON` (current sector only), or `SATELLITE` (any sector where you own a station or satellite). Toggle anytime via `range off`, `range on`, or `range satellite`.
  * **📨 Physical Messengers (Couriers):** Order any of your pilots to carry one or more letters across the galaxy. Each recipient reads only their own letter. Letters from you carry full command authority (e.g., *"Take this message to Mumi Lu: hold the Erebus where she is"*), and couriers actively hunt moving ships up to one gate away.
  * **🕵️ Courier Interception:** Enemy agents can intercept couriers in transit and leak the dispatches they carry.
  * **⏱️ Delayed Reports Beyond Comms:** Reports from out-of-range officers are held with their ship until they return to comm coverage—or for urgent news, the officer decides whether to hold, send a courier, or fly back in person.
  * **🔍 `whereis <name>` Crew Search:** Searches every ship and station you own to report whether an officer is `AT A POST`, `OFF POST (aboard X)`, or `MISSING`.
  * **🕊️ Envoys Between Realms:** AI faction councils without direct comms must dispatch physical envoy ships across jump gates to propose peace or diplomacy.
  * **👑 The `POWER` Tab, Vassalage & Supply Contracts:**
    * Separate ledger for your holdings, standing, trade contracts, and sworn realms.
    * **Vassalage:** Tribute is paid as a capped share of a vassal's **real income** (never invented money), opening their economy to you while balancing the revolt risk of their **Three Estates (*Society, Military, Leaders*)**.
    * **Standing Supply Contracts:** Station managers sign contracts to buy your deliveries at a real hourly reliability premium tied to actual station shortages.
    * **Political Sway:** Call on sworn realms for a *Call to Arms* or *Counsel of Peace*.
* **Built & Gate-Tested (Waiting for First Live Occurrence):**
  * **🚨 Missing in Action (`ADRIFT` / `RECOVERED` / `FALLEN`):** When a ship goes down, nearby spacesuits are scanned for the commanding officer.
  * **🚧 Doctrine Geofences:** Your Fleet Doctrine can fence off hazardous sectors so officer orders stay out of them.
  * **🧾 The Money Ledger:** Records every single credit moved by AiLive alongside its exact cause.
  * **🤝 Hire in Conversation:** Recruit NPCs directly through live dialogue using X4's native hiring system.

---

### 🎖️ [`v2.3.0-rc.1` — Officers With Judgement](https://github.com/KennyG1990/AiLive/releases/tag/v2.3.0-rc.1) *(Oct 25, 2026)*
**Your officers now come to you with options, not just problems.** They name their ships, plan named operations, and their confidence rises and falls with how the war goes.

* **Proven in Game:**
  * **🧠 Courses of Action, Not Excuses:** When an order can't be fulfilled as given (e.g., ordering a satellite drop with no satellites in cargo), officers explain why in plain speech and propose a real alternative (*"Shall I fetch satellites from the shipyard first?"*).
  * **📈 Confidence & Morale Rail:** Every officer tracks dynamic Confidence (`unsure` / `steady` / `bold`) and Morale on the conversation rail, shifting with promotions, victories, and defeats.
  * **🚢 Officers Name Their Ships & Operations:** Posted or promoted officers christen factory-named hulls in their own voice, assign numbered callsigns to their wing, and register **Named Operations** (e.g., *OPERATION SILENT ORCHARD (Security)*) in the `FLEET` tab and X4's **Mission Manager**.
  * **🔭 Sector Reconnaissance & Standing Withdrawals:** Officers reconnoitre sectors and report what they saw; damaged wings execute vanilla retreats before resuming standing patrol orders.
  * **🏅 Redesigned `HONOURS AND AWARDS` & `DEBUG` Tabs:** Visual ribbon showcase explaining every decoration, plus a ground-truth `DEBUG` inspector for all AI faction fleets and admirals.
* **Built & Gate-Tested:**
  * **🎖️ 22+ New Service Honours:** Including the *Order of Merit*, *Distinguished Command Medal*, *Fleet Cross*, *Silver Nova*, *Bronze Comet*, *Star of the Void*, *Strike Cross*, *Station Command Insignia*, and *Lifeline Medal*—unlocking merit-based promotions above Captain.
  * **⚡ Bold Initiative:** High-confidence officers (75+) execute their best tactical option immediately and inform you, rather than waiting for permission.
  * **🏳️ Foreign Captain Defection & Need-to-Know Ledgers:** Turn rival captains to your banner, and keep secrets compartmentalized on per-person ledgers.

---

### ⚓ [`v2.2.0-rc.1` — The Officer Corps](https://github.com/KennyG1990/AiLive/releases/tag/v2.2.0-rc.1) *(Oct 24, 2026)*
**Your officers are people with careers.** They rise, they fall, they remember who stood beside them—and who didn't.

* **Proven in Game:**
  * **🏛️ The Officer Corps Org Chart:** Billets from **Lieutenant to Admiral**, dynamically sized to your fleet, with full dossiers (loyalty, trust, fear, resentment, engine skills, memories, mess talk, private thoughts, dated citations, and doctrine).
  * **⚔️ Acting Ranks, Succession & Appointment Reviews:** When a commander falls, the senior survivor takes command as **ACTING** immediately. Superior officers review candidates and recommend a permanent replacement—and passed-over officers remember your choice.
  * **🤥 Caught Lies, Threats & Mess Talk:** Officers track fear, resentment, and trust separately, gossip with peers in the mess, and penalize you when caught lying.
  * **📋 Real Order Queue Readbacks:** Ask any captain what their ship is doing and they read back the real X4 order queue and standing mandate.
* **Built & Gate-Tested:**
  * **🏴‍☠️ Recurring Rival Officers:** Enemy captains who clash with your fleet across two real battles become named nemeses tracked by Fleet Intelligence.
  * **⚖️ Friendly-Fire Incidents & Boards of Inquiry:** Grave losses (3+ ships) or friendly-fire incidents trigger formal inquiries before a superior officer.
  * **🎓 Mentors & Protégés:** Senior officers take promising juniors under their wing, passing down combat doctrine.
  * **📻 Unprompted Captain Call-Ins:** Captains hail you when vanilla events trigger (police inspections, contraband found, lockboxes spotted, out of ammo).

---

### 🌌 [`v2.1.0-rc.1`](https://github.com/KennyG1990/AiLive/releases/tag/v2.1.0-rc.1) & [`v2.1.0`](https://github.com/KennyG1990/AiLive/releases/tag/v2.1.0) — *The Galaxy Has Something to Say* *(Oct 23, 2026)*
* Initial public release of the **AiLive** overhaul:
  * Natural-language NPC comm-link (`Speak to AI` in person and `Comm-link (AiLive)` on the sector map).
  * Natural-language captain orders for patrol, escort, follow, movement, and resupply.
  * Three-way espionage framework (player-to-faction, faction-to-player, and faction-to-faction).
  * Galactic News & Chronicle memory driven by real capital ship kills, sector captures, and diplomatic shifts.
  * Direct **Player2** desktop HTTP integration with zero Python bridge required.

---

### ⚡ [`v2.0.2`](https://github.com/KennyG1990/AiLive/releases/tag/2.0.2) & [`v2.0.1`](https://github.com/KennyG1990/AiLive/releases/tag/2.0.1) — *Serverless Standalone Foundation* *(Jul 2026)*
* Removed external Python server dependencies in favor of a self-contained native transport architecture inside `x4_ai_influence/`.
