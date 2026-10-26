# 📚 AiLive Field Manual & Reference Docs

[![Home](https://img.shields.io/badge/🌌_AiLive_Home-1d3557?style=for-the-badge)](../README.md)
[![Download AiLive](https://img.shields.io/badge/🚀_Download_AiLive-00b4d8?style=for-the-badge)](https://github.com/KennyG1990/AiLive/releases)
[![Releases](https://img.shields.io/badge/📦_Releases-0077b6?style=for-the-badge)](RELEASES.md)
[![Player Guide](https://img.shields.io/badge/📖_Player_Guide-f77f00?style=for-the-badge)](PLAYER-GUIDE.md)
[![Under the Hood](https://img.shields.io/badge/🛠️_Under_the_Hood-e63946?style=for-the-badge)](UNDER-THE-HOOD.md)
[![Feature Notes](https://img.shields.io/badge/📋_Feature_Notes-7209b7?style=for-the-badge)](FEATURES-AND-DEVELOPMENT.md)
[![Discord](https://img.shields.io/badge/💬_Join_the_Fleet-5865F2?style=for-the-badge)](https://discord.gg/5zwxzRvDY)

---

## ⌨️ 1. Chat Box Commands & Quick Reference

You can type these commands directly into the AiLive conversation input box at any time:

| Command | What It Does | Example |
| :--- | :--- | :--- |
| `whereis <name>` | Searches every crew of every ship and station you own for an officer and reports `AT A POST`, `OFF POST (aboard X)`, or `MISSING`. | `whereis Mumi` → *"AT A POST - Erebus XWS-229 (Argon Prime)"* |
| `range off` | Sets Comms Range to **OFF** (default): talk to any eligible NPC anywhere in the galaxy. | `range off` |
| `range on` | Sets Comms Range to **ON**: live comms only reach NPCs in your **current sector**. Beyond that, use a courier. | `range on` |
| `range satellite` | Sets Comms Range to **SATELLITE**: live comms reach your sector plus **any sector where you own a station or satellite**. | `range satellite` |
| `/raw` | Asks the NPC to step out of character and explain the exact game state, temperament, and reasoning behind their last reply. | `/raw` |

---

## 🖥️ 2. The AiLive Hub — Tab-by-Tab Guide

| Hub Tab | Purpose & Key Controls |
| :--- | :--- |
| **🏛️ CORPS** | Displays your naval chain of command org chart, open and filled billets, and full **Officer Dossiers** (loyalty, trust, fear, resentment, engine skill ratings, memories of you, knowledge ledger, mess talk, private thoughts, mentor/protégé links, dated citations, and doctrine). Also hosts **Appointment Reviews** and **Boards of Inquiry**. |
| **🚀 FLEET** | Tracks your organized wings (*Alpha*, *Beta*, etc.), active standing mandates, and **Named Operations** (e.g., *OPERATION SILENT ORCHARD (Security)*) with one-click tracking into X4's Mission Manager. |
| **📜 DOCTRINE** | Author up to **12 Fleet Doctrine tenets** (with optional scope prefixes like `engagement:`, `risk:`, `fleet-structure:`), view each tenet's live `[won, lost]` battle record, set sector **geofences**, and accept or reject doctrine amendments recommended by your officers after combat. |
| **👑 POWER** | Separates what you own, your diplomatic standing, active **Standing Supply Contracts**, the **Money Ledger** (every credit moved by AiLive with its cause), and your sworn **Vassal Realms** (tribute share and the health of their *Society, Military, and Leaders* estates). |
| **🏅 HONOURS AND AWARDS** | The complete visual ribbon rack: displays every medal and honour in AiLive, its ribbon texture, what feats earn it, who awards it, and which of your officers currently wear it. |
| **⚙️ SETTINGS** | Configure **Comms Range** (`OFF` / `ON` / `SATELLITE`), **Doctrine toggles** (*Enable Documents*, *Officers' Own Lessons*, *Faction Council Amendments*), **Rear-Echelon Reinforcement** (default `OFF`), and **Faction Council Frequency**. |
| **🔍 DEBUG** | Ground-truth intelligence inspector showing every AI faction's live warships, active fleets, and commanding Fleet Admiral. |

---

## 🎖️ 3. The 7 Naval Ranks & Promotion Regulations

Your Officer Corps enforces a structured seven-tier naval hierarchy. Promotions require an **open billet**, **time in service**, and (for senior ranks above Captain) **service decorations**:

| Rank | Tier | Command Role & Authority | Promotion Path & Notes |
| :--- | :---: | :--- | :--- |
| **Lieutenant (LT)** | 1 | Junior ship commander / wing element pilot | Entry commissioned officer rank. |
| **Lieutenant Commander (LCDR)** | 2 | Senior patrol leader / corvette or frigate captain | Requires time in grade and clean service record. |
| **Commander (CDR)** | 3 | Squadron / tactical wing commander | Can mentor junior officers and lead named operations. |
| **Captain (CAPT)** | 4 | Capital ship captain / senior line commander | Eligible to sit on Boards of Inquiry and hold major billets. |
| **Commodore (CDRE)** | 5 | Flotilla / multi-wing task group commander | Requires qualifying service medals/honours and an open senior billet. |
| **Rear Admiral (RADM)** | 6 | Sector defense / battle group commander | Reviews acting appointments and advises on theater strategy. |
| **Admiral (ADM)** | 7 | Supreme Fleet Commander | Top of the naval chain of command. |

* **⚡ Acting Ranks & Battlefield Succession:** If an officer's ship is destroyed in combat, the senior surviving subordinate immediately assumes the post as **ACTING** (even if they lack the formal qualifications for permanent rank) so your chain of command never breaks mid-battle.

---

## 🏅 4. Medals, Ribbons & Battle Honours Reference

AiLive includes **22+ coded service decorations** awarded automatically from real engine events, complete with custom ribbon art and dated, sector-specific citations:

* **⚔️ Combat & Valor Decorations:**
  * **Star of the Void** · **Fleet Cross** · **Silver Nova** · **Bronze Comet** · **Strike Cross** — Awarded for valor, capital ship kills, and decisive victories in named engagements.
* **🎖️ Command & Merit Decorations:**
  * **Order of Merit** · **Distinguished Command Medal** · **Station Command Insignia** — Awarded for sustained leadership, successful operation completions, and station governance.
* **🧭 Campaign, Expeditionary & Rescue Awards:**
  * **Campaign & Deployment Ribbons** · **Expeditionary Medal** · **Lifeline Medal** — Awarded for frontier exploration, long-range deployments, and search-and-rescue recoveries.
* **🚩 Ship & Unit Battle Honours:**
  * Ships and wings accumulate permanent combat history and callsigns under their commanding officer.

---

## 📡 5. Comms, Couriers & Casualty States Reference

### 📨 Courier & Messenger Rules
* **Multi-Letter Pouches:** A single courier pilot can carry letters to multiple recipients on one run; each recipient only ever reads their own letter.
* **Target Hunting:** If the recipient ship has moved since the courier launched, the courier flies to the last known sector and follows leads up to **one jump gate away**.
* **Authority:** Written orders signed by you carry the exact same execution authority as a live face-to-face order.

### 🚨 Officer Location & Casualty States
When a ship is lost or an officer is away from their billet, CORPS tracks their physical person across the universe:
* **`AT A POST`** — Actively commanding their assigned ship or station.
* **`OFF POST (aboard X)`** — Alive and aboard another one of your ships or stations, awaiting reassignment.
* **`MISSING`** — Unaccounted for across your fleet census; CORPS holds their billet open while searching.
* **`ADRIFT`** — Their ship was destroyed, and their spacesuit has been detected floating near the wreckage—launch a rescue immediately!
* **`RECOVERED`** — Rescued from a spacesuit and safely back aboard a friendly hull or station.
* **`FALLEN`** — Confirmed lost when the ship and spacesuit are both gone; triggers formal succession and mentor/crew remembrance.
