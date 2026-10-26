# 📋 AiLive Feature Notes, Live Records & 4X Roadmap

[![Home](https://img.shields.io/badge/🌌_AiLive_Home-1d3557?style=for-the-badge)](../README.md)
[![Download AiLive](https://img.shields.io/badge/🚀_Download_AiLive-00b4d8?style=for-the-badge)](https://github.com/KennyG1990/AiLive/releases)
[![Releases](https://img.shields.io/badge/📦_Releases-0077b6?style=for-the-badge)](RELEASES.md)
[![Player Guide](https://img.shields.io/badge/📖_Player_Guide-f77f00?style=for-the-badge)](PLAYER-GUIDE.md)
[![Read Docs](https://img.shields.io/badge/📚_Read_Docs-2a9d8f?style=for-the-badge)](READ-DOCS.md)
[![Under the Hood](https://img.shields.io/badge/🛠️_Under_the_Hood-e63946?style=for-the-badge)](UNDER-THE-HOOD.md)
[![Discord](https://img.shields.io/badge/💬_Join_the_Fleet-5865F2?style=for-the-badge)](https://discord.gg/5zwxzRvDY)

---

## 🎬 1. Verified Live Campaign Records

These aren't scripted cutscenes or marketing hypotheticals—every moment below occurred organically in recorded live *X4: Foundations* test campaigns and is tracked in the project's Notion & GitHub specs:

### 🕊️ Peace Has to Make It Through the Gates (`SPEC-828`)
A faction council decides it wants peace. A fighter undocks with the proposal. Two jump gates stand between that decision and the people who need to hear it.
* **Seen Live in Campaign:** The **Antigone Republic** council sought peace with the **Holy Order of the Pontifex**. Because the two realms were at war with no direct comm-link, an Antigone fighter physically flew two jump gates to deliver the proposal. Only after the envoy arrived in sector did the Holy Order council sit to weigh it.

### 🕵️‍♂️ Put a Spy in the Path of a Courier (`SPEC-739`)
* **Seen Live in Campaign:** A **Duke's Buccaneers** spy intercepted one of the player's physical couriers mid-route and leaked the player's orders through the espionage network—completely unprompted by the player.
* **Why It Matters:** Councils make decisions, ships carry the messages, physical delivery determines when orders or treaties take effect, and espionage can expose dispatches travelling through that same universe.

### 📡 Your Intelligence Has a Journey (`SPEC-739`)
* **Seen Live in Campaign:** A player scout ship compiled a reconnaissance report deep in frontier space, but was outside of sector communications range. The report was held aboard the hull. With no free courier pilots nearby to relay it, the scout reasoned that it had to deliver the intelligence personally, burned back to friendly comm range, and delivered the briefing.
* **Pinned Down in Argon Prime:** In another test, a courier hunting for a moving recipient travelled to the last known sector, searched one gate out, and—when pinned down in Argon Prime—reported back why it never made it through.

### ⚓ An Empty Chair Still Belongs to Someone
* **Seen Live in Campaign:** **Commodore Xiaowen Jackson** was missing from her post and unaccounted for across the crews of the player's 42 ships and 2 stations. **CORPS** marked her **`MISSING`** beside her billet and held the command slot for her while the fleet census searched for word of her fate.

---

## ✅ 2. Current Feature Inventory (`v2.1.0` → `v2.4.0-rc.1`)

| Domain | Proven in Live Game Sessions | Built & Gate-Tested (Awaiting Live Triggers) |
| :--- | :--- | :--- |
| **🎙️ Comms & Personalities** | • Natural-language comm-link (`Speak to AI` & remote map `Comm-link`)<br>• Species personalities, mood, trust, fear & resentment<br>• Long-term memory & UTF-8 save-safe persistence<br>• Caught-lie penalties, threats, and mess-hall gossip | • Unprompted captain call-ins during vanilla inspections, contraband scans, lockboxes & low ammo<br>• Hiring real NPCs directly through conversation |
| **🎖️ Officer Corps & Command** | • 7 Naval Ranks (*Lieutenant* to *Admiral*) & dynamic org chart<br>• Full dossiers, Acting ranks, battlefield succession & Appointment Reviews<br>• Natural-language orders (patrol, escort, follow, move, recon, resupply) with real queue readbacks<br>• Courses of Action when an order cannot be executed as asked<br>• Officers name ships, assign callsigns & track **Named Operations**<br>• **Fleet Doctrine** (12 tenets, win/loss records) & visual **Honours** tab | • **22+ automated service medals & ribbons** unlocking promotions above Captain<br>• **Bold Officer initiative** (confidence 75+ acts immediately)<br>• **After-Action Reviews (AARs)** & officer doctrine recommendations<br>• **Doctrine Geofences** keeping orders out of fenced sectors<br>• **Missing in Action** (`ADRIFT` spacesuit rescue / `RECOVERED` / `FALLEN`)<br>• Friendly-fire tracking, **Boards of Inquiry** & **Mentors/Protégés** |
| **📨 Comms Range, Couriers & Envoys** | • Configurable **Comms Range** (`OFF`, `ON`, `SATELLITE`)<br>• Physical **Courier Ships** carrying single or multi-letter pouches<br>• Couriers hunting moving recipients across jump gates<br>• Out-of-range officer reports held until comms are restored<br>• `whereis <name>` fleet-wide crew locator<br>• **AI Faction Envoys** flying peace/diplomatic proposals between realms | • Autonomous faction-to-faction protection offers via envoy |
| **🕵️‍♂️ Espionage & Secrets** | • Three-way espionage (Player ↔ Faction & Faction ↔ Faction)<br>• Agent placement, recall on improved relations, and exposure fallout<br>• Spontaneous enemy spy interception of player couriers | • **Need-to-Know personal ledgers** (secrets only live on those who know them)<br>• Leaking of stored operational plans to enemy operatives<br>• **Foreign captain defection** & faction memory of turncoats<br>• **Recurring Rival Officers** tracked across multiple battles |
| **👑 Power, Economy & Politics** | • **POWER** tab separating holdings, standing, trade & vassals<br>• **Standing Supply Contracts** with real hourly reliability premiums<br>• **Warship sales** (Player-to-Faction & Faction-to-Faction) with real reserve checks<br>• **Vassalage & Protection Pacts** (real income tribute, **Three Estates** revolt tension)<br>• **Political Sway** (*Call to Arms* / *Counsel Peace*) & Faction Councils<br>• Galactic News & Chronicle memory | • **The Money Ledger** auditing every credit moved by AiLive with its cause<br>• Rear-echelon reinforcement requests from real reserve ships |

---

## 🧭 3. The 4X Pillars × Politics, Economy, Military & Social

From the **AiLive Notion Design Map**, every system in the mod is built to turn *X4*'s four classic 4X pillars (*Explore, Expand, Exploit, Exterminate*) from solo spreadsheet clicks into a living human drama across **Politics, Economy, Military, and Social** dimensions:

### 🔭 Pillar 1: EXPLORE — *Intelligence Has a Journey*
* **Military:** Dispatch officers on sector reconnaissance orders; scouts compile real sightings of hostile fleets and stations instead of instant map fog-of-war reveals.
* **Social & Comms:** Out-of-range scouts must weigh whether to hold their watch in silence, dispatch a courier, or fly home personally to warn you.
* **Politics & Espionage:** Plant agents inside foreign factions and use the `DEBUG` / intelligence views and personal secret ledgers to discover what rival councils are planning before their fleets launch.
* **Economy:** Spot real material shortages at frontier shipyards and trading stations to open lucrative contract negotiations.

### 🌱 Pillar 2: EXPAND — *From Lone Captain to Imperial Hierarchy*
* **Military:** Grow your command structure organically—from a handful of Lieutenants to a full seven-rank **Officer Corps** with squadrons, wings, and permanent sector billets.
* **Comms Infrastructure:** Expand your **Satellite & Station Comm Network** (`range satellite`) so your voice and your officers' reports can span the jump gates without courier delays.
* **Politics:** Bring vulnerable minor factions and battered realms under your wing through **Protection Agreements**, expanding your sphere of influence without firing a shot.
* **Social:** Watch your officers build careers, christen their ships, mentor protégés, and compete for permanent appointments as new billets open.

### 💰 Pillar 3: EXPLOIT — *Leverage, Contracts & Tribute*
* **Economy:** Lock in **Standing Supply Contracts** with station managers—delivering needed hull parts or weapon components on schedule for real hourly reliability premiums.
* **Military-Industrial Complex:** Sell surplus warships directly to warring factions from real funds in their faction reserves, arming the side you want to win.
* **Politics:** Collect recurring **Tribute** from sworn vassal realms (paid strictly from their real income, never conjured credits) while gaining access to their faction economy.
* **Social & Intrigue:** Exploit personal greed, fear, or resentment to bribe station contacts, buy intelligence, or turn an enemy captain into an informant.

### ⚔️ Pillar 4: EXTERMINATE — *Doctrine, Operations & Total War*
* **Military:** Author your **Fleet Doctrine** and sector **geofences**, launch **Named Operations** (*OPERATION SILENT ORCHARD*), and let high-confidence **Bold Officers** execute tactical courses of action in the heat of battle.
* **Politics:** March into allied or vassal **Faction Councils** to issue a **Call to Arms**, or intercept an enemy's peace envoy fighter before it can reach a rival capital to stop a war you profit from.
* **Espionage:** Steal enemy operational plans off intercepted couriers, expose moles in your command tree, and convince enemy destroyer captains to **defect** mid-campaign.
* **Social Stakes:** Every battle carries human weight—recurring **Enemy Rival Officers** who remember you across engagements, **Boards of Inquiry** after heavy losses, **Battle Honours ribbons**, and **MISSING / ADRIFT** search-and-rescue missions when a flagship goes down.

---

## 🔭 4. The Horizon — Future Roadmap Ambitions

The items below are tracked in the Notion roadmap as **future explorations and planned expansions** (not promises for the current release candidate):

* **🏛️ Deeper Treaty & Sector Statecraft:** War reparations, formal sector-transfer treaties, deeper war-fatigue mechanics, and minor-faction reintegration.
* **⚖️ Interactive Offer / Counteroffer Negotiation Table:** Visual *You Give / Balance / They Give* deal-making shaped by visible value, trust, suspicion, and faction purchasing power.
* **📦 Expanded Logistics, Mining & Salvage Verbs:** Broader natural-language command coverage for mining fleets, salvage crews, cargo collection, and automated fleet supply lines.
* **🏥 Station Crises & Security Standoffs:** Sector medical outbreaks (quarantine, medbay tiers, inoculant runs) and conversational station-security standoffs that can escalate into panic or firefights.
