# 🛠️ Under the Hood — How AiLive Works Inside X4

[![Home](https://img.shields.io/badge/🌌_AiLive_Home-1d3557?style=for-the-badge)](../README.md)
[![Download AiLive](https://img.shields.io/badge/🚀_Download_AiLive-00b4d8?style=for-the-badge)](https://github.com/KennyG1990/AiLive/releases)
[![Releases](https://img.shields.io/badge/📦_Releases-0077b6?style=for-the-badge)](RELEASES.md)
[![Player Guide](https://img.shields.io/badge/📖_Player_Guide-f77f00?style=for-the-badge)](PLAYER-GUIDE.md)
[![Read Docs](https://img.shields.io/badge/📚_Read_Docs-2a9d8f?style=for-the-badge)](READ-DOCS.md)
[![Feature Notes](https://img.shields.io/badge/📋_Feature_Notes-7209b7?style=for-the-badge)](FEATURES-AND-DEVELOPMENT.md)
[![Discord](https://img.shields.io/badge/💬_Join_the_Fleet-5865F2?style=for-the-badge)](https://discord.gg/5zwxzRvDY)

---

## ⚙️ 1. The Core Architecture: *"AI Proposes, X4 Disposes"*

Most "AI mods" in gaming fail because they either let an LLM hallucinate things that never happen in the game world, or they cheat by spawning fake units out of thin air. **AiLive is engineered from the ground up to prevent both.**

```
┌─────────────────────────────────────────────────────────────────────────┐
│ 1. DETERMINISTIC X4 ENGINE STATE (Mission Director XML + UI Lua)        │
│    • Real ship hulls, cargo holds, order queues, credits, sector gates  │
│    • Per-character memory cards, trust/fear/resentment, secret ledgers  │
└──────────────────────────────────┬──────────────────────────────────────┘
                                   │ Ground-Truth Context Snapshot
                                   ▼
┌─────────────────────────────────────────────────────────────────────────┐
│ 2. LOCAL PLAYER2 INFERENCE (Bundled Native HTTP Transport -> :4315)     │
│    • In-character dialogue, tactical Courses of Action, Council votes   │
│    • Structured JSON action proposals + After-Action doctrine reviews   │
└──────────────────────────────────┬──────────────────────────────────────┘
                                   │ Proposed Intent / Action Payload
                                   ▼
┌─────────────────────────────────────────────────────────────────────────┐
│ 3. DETERMINISTIC VALIDATOR & ENGINE EXECUTOR                            │
│    • Verifies ship existence, command rank limits, doctrine geofences   │
│    • Debits real faction/player credits (recorded in the Money Ledger)  │
│    • Queues real X4 aiscripts & reads back accepted/refused outcomes    │
└─────────────────────────────────────────────────────────────────────────┘
```

### 🛡️ Ironclad Simulation Rules
* **No Magic Spawns:** Neither your officers nor AI factions can ever conjure a ship, ware, or credit out of thin air. If a faction council votes to reinforce a border, it must pull an existing warship from its reserve fleet.
* **Every Credit Has a Receipt:** Tribute payments from vassals are capped percentages of their real economic income. Supply contract bonuses are debited from the buyer's actual funds. Every single credit moved by AiLive is logged in the **Money Ledger** with its cause.
* **Engine Readbacks:** When an officer issues or receives an order, AiLive inspects X4's live order queue after execution. If the engine rejected the order (or if someone manually overrode the ship's queue on the map), the captain knows and says so in conversation.

---

## 🔌 2. Direct Player2 Transport (Zero Python Bridge)

Earlier generations of X4 AI mods required players to install Python, manage `pip` dependencies, run background console windows, and paste commercial API keys into config files.

* **Native `lua3p` Transport:** AiLive ships with its own lightweight native transport layer inside `x4_ai_influence/lua3p/`.
* **Localhost Loopback (`127.0.0.1:4315`):** The mod talks directly to the **Player2** desktop application running on your PC, including automatic `/v1/health` gameplay heartbeats and incremental streaming reply parsers so the UI never freezes during long responses.
* **Bounded Performance:** Background scans are throttled, queues are strictly bounded, and live context refreshes only run while a conversation or scheduled council tick is active.

---

## 🧠 3. Need-to-Know Intelligence & Person-Level Ledgers

In AiLive, information is a physical object that travels at the speed of ships:

* **Individual Knowledge Ledgers:** Every NPC has a personal knowledge ledger stored on their character card. When you brief an officer in confidence or hand a dispatch to a courier, that fact is written **only** to that person's ledger.
* **Compartmentalized Courier Pouches:** When a courier pilot carries three letters to three different captains, each recipient only receives the contents of their own letter.
* **Organic Leaks & Interceptions:** Because enemy spies target specific people and couriers in real sectors, a rival faction can only learn your battle plan if they intercept the courier carrying it, turn an officer who holds it on their ledger, or overhear a loose-lipped captain in the mess!

---

## 📜 4. The Doctrine & After-Action Review (AAR) Engine

AiLive features a two-tier doctrine system connecting your strategic vision to individual officer growth:

1. **Commander's Fleet Doctrine (Top-Down):**
   * Stored in `aic_doctrine.lua` (up to 12 scoped tenets). Injected directly into every subordinate officer's command prompt with the rule: *"An order from the player always comes first."*
   * Every mission won or ship lost while a tenet is active increments its `[won, lost]` combat tally.
2. **Combat Ledger & Quiet-Window AARs (Bottom-Up):**
   * During battle, Mission Director cues (`ai_influence_combat.xml`) record every ship kill and loss by name and hull ID into a per-officer combat ledger (`_aar`), explicitly filtering out defence drones (`$sh.isunit`) and `ship_xs` craft so disposable drones never trigger false reviews or succession.
   * Once a fight has been quiet for **2 minutes**, the officer conducts a single bounded **After-Action Review**:
     * They write an in-character combat report from the engine facts.
     * They may **revise, add, or drop** one of their own personal combat lessons—**only if they cite a concrete reason from the battle** (preserving the old lesson in `.was`).
     * Because your Fleet Doctrine is yours alone to change, an officer can only submit a **Doctrine Recommendation** (with a reason), which waits in your `DOCTRINE` hub tab for you to **Accept** or **Reject**.

---

## 💾 5. Save-Safety, Versioning & the 90+ Gate Test Suite

* **UTF-8 Save Sanitization (`utf8gate`):** X4's `LIBXML2` save parser will reject an entire save attribute if a multibyte Unicode character (like an LLM-generated narrow no-break space or em-dash) is sliced mid-character during string truncation. AiLive sanitizes all model text to clean save-safe bytes before persistence.
* **Versioned Stores & Routed Hydration:** Every persistent store (Officer Corps, Doctrine, Chronicles, Faction Councils) carries a schema version stamp and routed load callbacks so records are never scrambled across save loads.
* **90+ Automated Verification Gates:** Before any release zip is built by `package_release.py`, over 90 automated Python + `lupa` gate suites (`corpsgate`, `couriergate`, `envoygate`, `docgate`, `estatesgate`, `supplygate`, `neggate`, `stratgate`, etc.) execute the real Lua and XML logic against simulated combat, espionage, courier, and save-load scenarios. Furthermore, `package_release.py` strips development-only telemetry (`aic_perf.lua`), verifies XML integrity, scans for accidental credentials, and validates the final zip archive before it can ship.
