# 📦 AiLive Releases & Version History

[![Home](https://img.shields.io/badge/🌌_AiLive_Home-1d3557?style=for-the-badge)](../README.md)
[![Download AiLive](https://img.shields.io/badge/🚀_Download_AiLive-00b4d8?style=for-the-badge)](https://github.com/KennyG1990/AiLive/releases)
[![Player Guide](https://img.shields.io/badge/📖_Player_Guide-f77f00?style=for-the-badge)](PLAYER-GUIDE.md)
[![Read Docs](https://img.shields.io/badge/📚_Read_Docs-2a9d8f?style=for-the-badge)](READ-DOCS.md)
[![Under the Hood](https://img.shields.io/badge/🛠️_Under_the_Hood-e63946?style=for-the-badge)](UNDER-THE-HOOD.md)
[![Feature Notes](https://img.shields.io/badge/📋_Feature_Notes-7209b7?style=for-the-badge)](FEATURES-AND-DEVELOPMENT.md)
[![Discord](https://img.shields.io/badge/💬_Join_the_Fleet-5865F2?style=for-the-badge)](https://discord.gg/5zwxzRvDY)

---

## 🚀 Latest Release: `v3.0.7-rc.1` — *Officers Who Do What They Say*

> 📥 **[Download `x4_AiLive-3.0.7.zip` on GitHub Releases](https://github.com/KennyG1990/AiLive/releases/tag/v3.0.7-rc.1)**
> *(Always download the **`x4_AiLive-*.zip`** package under **Assets**—do not download GitHub's automatic "Source code" zip!)*

**Upgrading from `3.0.6`:** replace the whole `x4_ai_influence` folder, make sure X4's **Protected UI Mode** is off, then restart X4 and load your save. The extension list shows **3.07**. Keep a backup of your save.

### ⚠️ Still important if you skipped `2.4.0`: the save-safety fix
Builds **`2.3.0` and earlier** could corrupt AiLive's saved memory if the AI model emitted multibyte typographic characters that were split in half during string truncation. **`v2.4.0-rc.1` and later sanitize every text string before it reaches the save.**

---

## 🗓️ Release Timeline & What's Inside Each Build

### 📦 [`v3.0.7-rc.1` — Officers Who Do What They Say](https://github.com/KennyG1990/AiLive/releases/tag/v3.0.7-rc.1) *(Nov 25, 2026)*
**Seventeen builds on top of 3.0.6 RC1.** **A beta: expect bugs.**

* **New (seen in game):** officers do what they say: on Player2 and OpenRouter a separate step reads your order and the receipt checks it against what the officer said (OTHER > CONNECTION "How orders are written": AUTO / IN THE SAME REPLY); consulted officers remember their superior's answer; governors really file military requests (MILITARY > SUPPORT "Requests to your commanders"; OFF sends them to you in the governor's words); INBOX HAIL works on fleet SITREPs; withheld order steps are remembered; written operation orders show their length; lighter background load
* **Built, waiting to be seen:** hide civilian pilots from promotion lists (MILITARY > PROMOTIONS "Civilian pilots in promotion lists": SHOWN / HIDDEN); rescue after a loss call; adrift pilots never story speakers; AI agents stop re-filing old intel; supplier talks survive a long wait; OFF switches stop their scans; negotiation rounds and hull clauses; doctrine and envoy fixes; re-withdraw under fire
* **Known:** on Player2 a slow order step is skipped after 8 seconds; several items are rare events not yet seen in play

### 📦 [`v3.0.6-rc.1` — Orders You Can Send, and an Inbox That Keeps Them](https://github.com/KennyG1990/AiLive/releases/tag/v3.0.6-rc.1) *(Nov 23, 2026)*
**Thirteen builds on top of 3.0.5 RC1.** **A beta: expect bugs.**

* **New (seen in game):** send a written operation order straight to an officer from DOCTRINE > OPERATION ORDER (MILITARY > DOCTRINE "Operation order SEND": INTO THE CHAT / SENDS AT ONCE); the AiLive INBOX tab - reports sorted into NEEDS YOU / LOSSES / CONTACTS / REPORTS / RECORDS, read, delete, show on map, kept across saves (OTHER > COMMS "AiLive reports go to"); negotiation table: name your freighter after accepting terms, lists that scroll, prices with cents; consulted officers call you back with the answer; newscasts publish reliably; garbled replies never show raw code.
* **Built, waiting to be seen:** the strict hourly allowance reserves what it sends; shorter changes-only plan reviews; order priority keeps untracked orders visible.
* **Known:** an officer can say one thing while his ship does another (root fix in progress - trust the receipt line); an officer can say a consultation has not been answered yet when it has; INBOX HAIL is greyed on consolidated SITREPs.

### 📦 [`v3.0.5-rc.1` — Governors Who Know Their Limits, and Every Button Answers](https://github.com/KennyG1990/AiLive/releases/tag/v3.0.5-rc.1) *(Nov 23, 2026)*
**Ten builds on top of 3.0.4 RC1.** **A beta: expect bugs.**

* **New (seen in game):** governors say when a request is beyond them (warships go to military command; no promised cargo drones); every attempt button beside the chat box answers (GitHub #143); newscasts every half hour (SOCIAL > THE PRESS "Galaxy newscast every": 15 / 30 / 60 MIN); long-serving officers get life stories; "hold for thirty seconds" means seconds; holds are acknowledged only once the ship takes them; your own people are never offered a bribe.
* **Built, waiting to be seen:** plan reviews brief with changes only (MILITARY > ORDERS); scouts report only what their radar sees; commanders' stand-downs; lent ships returning to their fleet; the billet requirement; governors' requests kept; a failing per-layer model falls back to the default and shows as FAILING; radio promises need a sent message; formation counts in consultations; newscast loss counts; clearer SA briefings and war-supply news.
* **Known:** a governor caught promising drones loses his honest warship answer too; a direct order to a captain can read as unconfirmed in his commander's plan review. Fixes in progress.

### 📦 [`v3.0.4-rc.1` — Characters With a Life of Their Own, and Settings You Can Find](https://github.com/KennyG1990/AiLive/releases/tag/v3.0.4-rc.1) *(Nov 22, 2026)*
**Twenty builds on top of 3.0.3 RC1.** **A beta: expect bugs.**

* **New (seen in game):** characters write down their own life the first time you talk to them and answer from it (SOCIAL > CONVERSATION "Characters' life stories"); a search box and starter presets (SIMPLE / STANDARD / FULL MILITARY) in SETTINGS; the hub shows what your OpenRouter replies cost; outgunned ships pull back; an empty answer is asked again; a refused satellite order stays refused.
* **Fixed (checked by tests):** "cut short" on a good answer that came wrapped in an extra layer; officers know every charted sector; "Career requirements" OFF keeps the command limits.
* **Built, waiting to be seen:** routine order results folded into the SITREP; rescue our people (AUTOMATIC / ASK ME / OFF); SAVE KEY checks your OpenRouter key; FLEET > OPERATION; and more in the release notes.
* **Known:** long-serving officers' life stories can't be saved yet (records full; fix next); characters can still agree to things the mod can't do (fix next); "follow you" is refused honestly instead of carried out.

### 📦 [`v3.0.3-rc.1` — No More Career Grind, and Ships That Fight on Their Orders](https://github.com/KennyG1990/AiLive/releases/tag/v3.0.3-rc.1) *(Nov 19, 2026)*
**Ten builds on top of 3.0.2 RC1.** **A beta: expect bugs.**

* **New (seen in game):** switch off the career grind and keep the chain of command (MILITARY > CAREERS "Career requirements"); ships engage raiders in reach on their standing orders instead of waiting for the model (MILITARY > ORDERS "When raiders come in range"); combat reports say when the target left; allied trade pacts run from council vote to fulfilled delivery; crisis supply contracts get posted; a repeated delegation gives one conflict report instead of a flood.
* **Fixed (tests):** a station manager can no longer call a broken supply contract active.
* **Built, waiting:** withdrawal playbooks (MILITARY > ORDERS "How operations advance"), and several witnesses carried from 3.0.2.
* **Known:** officers see only the first 24 sectors you know (fix in progress); "order your ships to follow you" can move the captain instead of her wing.
* Full notes: [the release page](https://github.com/KennyG1990/AiLive/releases/tag/v3.0.3-rc.1).

### 📦 [`v3.0.2-rc.1` — Where Things Stand, and Warships for Sale](https://github.com/KennyG1990/AiLive/releases/tag/v3.0.2-rc.1) *(Nov 19, 2026)*
**Eleven builds on top of 3.0.1 RC1.** **A beta: expect bugs.**

* **New (seen in game):** people are reminded where things stand now before they answer you (SOCIAL > MEMORY "Where things stand now"); outnumbered realms can buy warships too, and a real paid sale moved a destroyer and its price between two treasuries exactly once (ECONOMIC > WARSHIP TRADE "Who may seek warships"); councils are no longer offered moves the game would refuse; council warnings list both demands together; an expired OpenRouter key gives one message instead of silent retries.
* **Fixed:** a gift's goodwill shows its fade and its lasting part (INFLUENCE > THE PEOPLE); CORPS discards saved self-recommendations; no false "link failing" warning on an empty reply; trade is never OVERDUE while its councils are OFF; a stale trade reply can no longer sign terms.
* Full notes: [the release page](https://github.com/KennyG1990/AiLive/releases/tag/v3.0.2-rc.1).

### 📦 [`v3.0.1-rc.1` — Governors You Can Appoint, and a Tested Model for Every Layer](https://github.com/KennyG1990/AiLive/releases/tag/v3.0.1-rc.1) *(Nov 19, 2026)*
Appoint a governor from the GOVERNMENT tab; tested results for every model layer except ORDERS; CORPS fixes. Full notes on the release page.

### 📦 [`v3.0.0-rc.1` — The Right Model for Each Job](https://github.com/KennyG1990/AiLive/releases/tag/v3.0.0-rc.1) *(Nov 18, 2026)*
A model per layer with tested picks. Full notes on the release page.

### 📦 [`v2.9.9-rc.1` — Pick Your Own Models](https://github.com/KennyG1990/AiLive/releases/tag/v2.9.9-rc.1) *(Nov 18, 2026)*
**Twelve builds on top of 2.9.8 RC1.** **A beta: expect bugs.**

* **New:**
  * **OpenRouter as a conversation service** (OTHER > CONNECTION): any OpenRouter model can voice the characters; the key is saved from the clipboard and kept encrypted by Windows, never in your save; the page shows what the last hour cost.
  * **Pick models in game:** REFRESH MODELS lists OpenRouter's text models by cost, reply-format fit, thinking and role-play.
  * **A model for each part of the game** (OTHER > MODELS): talk, officers, leaders, combat, command, strategy, government, economy, intelligence, careers, story and upkeep each take their own model, or the default; per-layer cost; CLEAR ALL LAYERS.
  * **How hard each layer thinks:** AUTO / LOW / MEDIUM / HIGH per layer.
  * **Reasoning models get room to think,** so a council decision is not cut off half-written.
  * **A wing ship you send alone leaves the wing** for that task; "take your wing" keeps it together.
* **Fixed:** a named attack can no longer become another ship's flight (seen in play); gate-tested: sparing a named faction in an attack, a courier keeping your later standing order, the report after a second "Do it anyway", dashes in contract talk, code examples in your message.
* **Known Issues:** an officer can still say she gave an order when none went out (the record line is right); the ORDERS layer's model is not used yet; a FREE OpenRouter model's rate limit pauses OpenRouter for every layer; a lone captain refuses "all ships, attack"; releasing a supply deal by agreement does not go through yet; invented personal details are not remembered; controller use of the hub is untested.

### 📦 [`v2.9.8-rc.1` — Orders With a Spine](https://github.com/KennyG1990/AiLive/releases/tag/v2.9.8-rc.1) *(Nov 17, 2026)*
**Twelve builds on top of 2.9.7 RC1.** **A beta: expect bugs.**

* **New:**
  * **Officers refuse a fight they cannot win, and break off when hurt:** small craft stay off station defences; "Do it anyway" or "That is an order" sends the refused order once; a badly hurt ship withdraws and asks for resupply (MILITARY > ORDERS: Withdraw when badly hurt, Keep small craft off station defences, Break off at hull, Break off at shield).
  * **You are told how to insist** when an order is refused as too risky.
  * **An attack keeps its target:** an order naming the wrong station or faction is refused before anything moves.
  * **Couriers go home** after bringing back an answer (MILITARY > ORDERS: When a courier is back).
  * **SYSTEMS HEALTH says what is probably wrong** and what to do (Player2 outage, a local server error, hotkeys that could not start).
  * **"Fly there and hold"** is one movement order that holds on arrival.
* **Fixed:**
  * Contract talk is no longer read as poaching; a commander's plan never targets his own ships; "without a signed contract" is no claim; the classic MILITARY settings list opens every row again; TRADE's HAIL greys out during a channel; a local server error is never blamed on Player2.
* **Known Issues:** a wing ship given its own patrol is pulled back by its commander after about a minute (fix agreed); after a second "Do it anyway" an officer may deny a running patrol; a lone captain refuses "all ships, attack"; releasing a supply deal by agreement does not go through yet; invented personal details are not remembered; controller use of the hub is untested.

### 📦 [`v2.9.7-rc.1` — Officers Who Are People](https://github.com/KennyG1990/AiLive/releases/tag/v2.9.7-rc.1) *(Nov 17, 2026)*
**Thirteen builds on top of 2.9.6 RC1.** **A beta: expect bugs.**

* **New:**
  * **Talk to your officers as people:** ask about their life, family or home, or invite them to dinner, and they answer as themselves; they serve your own private fleet, never a navy or an empire.
  * **Governors know their stations** from the day they are appointed and answer from today's readings, saying what each station needs (ECONOMIC > GOVERNORS: Station reports, Station watch).
  * **A lone captain really withdraws** when told to; resupply is asked for only once the withdrawal is under way.
  * **On your own server, the briefing follows your question:** the fleet's facts for a fleet question, the officer's character for a personal one, the matching entries from long lists (OTHER > CONNECTION: How much each character is told).
* **Fixed:**
  * On your own server, an order passed down the chain is carried out (a 2.9.6 known issue).
  * Secrets stay secret in long memory; what you told an officer is remembered as your claim; recall stays quiet when nothing fits.
  * No false "Not done" on a relayed hand-off; a governor's first answer comes from his readings.
* **Known Issues:** a lone captain refuses "all ships, attack" when he commands only his own ship; releasing a supply deal by agreement does not go through yet; personal details an officer invents are not remembered yet; a small model can muddle numbers; controller use of the hub is untested.

### 📦 [`v2.9.6-rc.1` — Small Models, Faithful Orders](https://github.com/KennyG1990/AiLive/releases/tag/v2.9.6-rc.1) *(Nov 17, 2026)*
**Thirteen builds on top of 2.9.5 RC1.** **A beta: expect bugs.**

* **New:**
  * **Your own model server at 8K context:** each character is told what fits in the room your server has, and every system keeps running (SETTINGS > OTHER > CONNECTION: How much each character is told).
  * **Orders on your own server are worked out first,** then carried out as worked out or refused - never just promised (How orders are written).
  * **Doctrine by branch:** command doctrine for everyone, plus the branch of what each officer's ship is doing - combat, supply, extraction, construction or reconnaissance (MILITARY > DOCTRINE).
  * **Your direct order stands** against a commander's own plan; **"your ships hold"** holds the whole wing; **wing ships answer through the chain**.
* **Fixed:**
  * **Accords now found for real** - proposal, petition, the council's sitting and the signature, with no more Accords errors in the log.
  * On your own server, an officer recites every doctrine tenet even when the briefing is cut to fit.
* **Known Issues:** on your own server an order passed down the chain ("have Keppel send the Calypso...") is refused - give it to the officer who commands the ship; a small model's speech can be stiff or embellished; controller use of the hub is untested.

### 📦 [`v2.9.5-rc.1` — Your Own Model, and Accords](https://github.com/KennyG1990/AiLive/releases/tag/v2.9.5-rc.1) *(Nov 16, 2026)*
**Nineteen builds on top of 2.9.0 RC1.** **A beta: expect bugs.**

* **New:**
  * **Run AiLive on your own model server.** SETTINGS > OTHER > CONNECTION: PLAYER2 or YOUR OWN SERVER at a typed address (llama.cpp, KoboldCpp, Ollama, LM Studio, or another PC). Qwen3.5-4B with 32K context runs beside X4 on a 12 GB card, replying in 2-8 s; weaker than Player2, so give simple orders.
  * **Small talk stays small talk on small models:** a greeting or a plain question gives no order and rolls no dice.
  * **Accords:** POWER > ACCORDS shows who could found a common-defence Accord with you and the threat you share (see Known Issues).
  * **Player2 keeps trying:** a conversation Player2's own service turns away is retried for up to 15 seconds.
  * **A gift's goodwill partly lasts;** **over-ranked officers are posted up;** **a supply talk shows the other side;** **the GOVERNMENT board lists what your stations need;** **the first-days letter stays on GETTING STARTED.**
* **Fixed:**
  * People you talk to know whose people they are and their own temperament.
  * A held promotion says who the grade's open places are owed to.
  * A supply pitch is heard as one; an unsigned supply talk keeps the manager's own words.
* **Known Issues:** an Accord proposal reaches the council but it cannot answer yet, and the debug log then repeats an Accords error - please do not propose an Accord in this build; rarer orders on a small local model (attack, mine, trade, buy) can come out as a different order; your own officers' conversations need a 32K-context server; a three-letter ship name is not recognised without its ID code; controller use of the hub is untested.

### 📦 [`v2.9.0-rc.1` — Errands and the Whole Fleet](https://github.com/KennyG1990/AiLive/releases/tag/v2.9.0-rc.1) *(Nov 14, 2026)*
**Eleven builds on top of 2.8.0 RC2.** **A beta: expect bugs.**

* **New:**
  * **Delivery errands.** A station manager asks for a set amount within a number of hours; take it by word, every sale by your ships counts, and the manager tells you how it ended. Settings under ECONOMIC > CONTRACTS.
  * **A top-up for an errand kept in full**, up to 25% on what the dock pays, paid by the manager's realm as its treasury can.
  * **Senior officers know the whole fleet.** Asked about the fleet, an officer answers for every ship that answers to them through the corps chain, not only their own wing, and names the day's losses.
* **Fixed:**
  * A supply deal is never signed for more than you offered ("2,000 in total" can no longer become 2,000 an hour).
  * An officer cannot hand down a mission naming a ship the subordinate does not command; they say so.
  * Officers commanding a ship are addressed by their real grade; receipts say "now holding position" and "now moving".
  * No other mod is listed as a dependency.
* **Known Issues:** closing a supply deal is hard in this build (a manager may repeat "I have not signed those terms"); an order for a ship several seats down the chain is relayed officer by officer; a false "Not done" line can appear beside a correct "ACCEPTED - Mission passed"; controller use of the hub is untested.

### 🧭 [`v2.8.0-rc.2` — First Days in Command](https://github.com/KennyG1990/AiLive/releases/tag/v2.8.0-rc.2) *(Nov 14, 2026)*
**Two builds on top of RC1.** Everything in RC1 still applies. **A beta: expect bugs.**

* **Fixed since RC1:**
  * A lone move order now ends: the ship is reported as having reached the sector and ORDER FLOW shows it done.
  * An order cancelled while the ship is in a highway is held until the ship leaves it, then carried out.
  * ORDER FLOW says "now moving" for a move order; the conversation rail names a filed report ("AAR filed", "SITREP filed").
* **Known Issues:** a letter that arrives while the hub is open is easy to miss (it is in Messages); an offer that names a total can be signed as an hourly contract; controller use of the hub is untested.

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
