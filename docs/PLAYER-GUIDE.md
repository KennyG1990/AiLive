# 📖 AiLive Player Guide — Installation & How to Play

[![Home](https://img.shields.io/badge/🌌_AiLive_Home-1d3557?style=for-the-badge)](../README.md)
[![Download AiLive](https://img.shields.io/badge/🚀_Download_AiLive-00b4d8?style=for-the-badge)](https://github.com/KennyG1990/AiLive/releases)
[![Releases](https://img.shields.io/badge/📦_Releases-0077b6?style=for-the-badge)](RELEASES.md)
[![Read Docs](https://img.shields.io/badge/📚_Read_Docs-2a9d8f?style=for-the-badge)](READ-DOCS.md)
[![Under the Hood](https://img.shields.io/badge/🛠️_Under_the_Hood-e63946?style=for-the-badge)](UNDER-THE-HOOD.md)
[![Feature Notes](https://img.shields.io/badge/📋_Feature_Notes-7209b7?style=for-the-badge)](FEATURES-AND-DEVELOPMENT.md)
[![Discord](https://img.shields.io/badge/💬_Join_the_Fleet-5865F2?style=for-the-badge)](https://discord.gg/5zwxzRvDY)

---

## ⚡ 1. Two-Minute Installation

> ⚠️ **Important:** Always download the **`x4_AiLive-*.zip`** archive from the **Assets** section of the [latest GitHub Release](https://github.com/KennyG1990/AiLive/releases). Do **not** download GitHub's automatic *"Source code (zip)"*—that only contains documentation!

1. **Install & Launch [Player2](https://player2.game):**
   * Download the free **Player2** desktop app, sign in, and leave it running in the background while you play.
   * AiLive connects directly to Player2 on `http://127.0.0.1:4315`—**no Python scripts and no API keys required.**
2. **Download the Mod Package:**
   * Grab **`x4_AiLive-2.4.0.zip`** (or the newest release) from **[GitHub Releases](https://github.com/KennyG1990/AiLive/releases)**.
3. **Extract into `extensions/`:**
   * Copy the **`x4_ai_influence`** folder from the zip into your `X4 Foundations/extensions/` directory so your layout looks exactly like this:
   ```text
   X4 Foundations/
     extensions/
       x4_ai_influence/
         content.xml
         ui.xml
         assets/
         aiscripts/
         libraries/
         lua3p/
         md/
         t/
         ui/
   ```
   * Keep the folder name **`x4_ai_influence`** exact (that is X4's internal extension ID). Make sure you don't accidentally nest `x4_ai_influence/x4_ai_influence/`.
4. **Launch X4 & Load Your Save:**
   * Confirm **x4 AiLive** is enabled under **Extensions** on the main menu.
   * **Upgrading from an older version?** Replace the entire `x4_ai_influence` folder and **load your save game** from the menu (a simple UI reload is not enough to register new Mission Director cues).

---

## 🎮 2. Your First 15 Minutes in AiLive

### 🎙️ Step 1: Open Your First Comm-Link
You can hail almost any named NPC in the galaxy—your own captains, alien traders, station managers, or faction representatives:
* **In Person or Standard Comms:** Hail an NPC and select **"Speak to AI"** from the radial conversation wheel.
* **From the Sector Map:** Right-click a suitable ship or station on the map and select **"Comm-link (AiLive)"**—even on targets where vanilla X4 offers no standard comm option!
* **Read the Room:** Watch the conversation rail for the speaker's **Mood**, **Trust**, **Confidence** (*unsure / steady / bold*), and **Morale**. Threats,broken promises, and caught lies will permanently shift how they view you.

---

### ⚓ Step 2: Command Your Captains in Plain English
Talk to any pilot or captain under your flag and tell them what you need in your own words:
* 🗣️ *"Patrol Second Contact II Flashpoint until told otherwise."*
* 🗣️ *"Escort the Wharf in Argon Prime."*
* 🗣️ *"Hold on the Aegis and screen her from fighters."*
* 🗣️ *"Reconnoitre Silent Witness I and report what you find."*
* 🗣️ *"Buy energy cells and resupply the carrier."*

**What happens next?**
* Your captain translates your order into **real X4 engine orders** and reports back what the game accepted, completed, or refused.
* **Courses of Action (Not Excuses):** If an order can't be executed as asked—for instance, you order a captain to drop satellites when their hold is empty—they won't just fail silently. They'll explain the problem and propose a real plan (*"We have no satellites aboard, Commander. Shall I fly to the Wharf and purchase some first?"*).

---

### 🎖️ Step 3: Commission Your Officer Corps & Write Fleet Doctrine
Open the **AiLive Hub** to manage your growing navy like a true Fleet Admiral:
1. **Promote & Post Officers (`CORPS` Tab):**
   * Promote capable pilots through **7 Naval Ranks** (*Lieutenant* → *Admiral*) and assign them to squadrons and permanent billets.
   * When an officer's ship is destroyed, the senior survivor immediately steps up as **ACTING** commander until you hold an **Appointment Review**.
2. **Author Your Fleet Doctrine (`DOCTRINE` Tab):**
   * Write up to **12 standing tenets** that every officer in your fleet reads and obeys—for example:
     * `engagement: never chase raiders outside our sectors`
     * `risk: withdraw any wing that loses half its ships`
   * Fence off dangerous sectors with **Doctrine Geofences** so your officers stay clear of kill-zones.
   * After combat quiets down, officers file **After-Action Reviews (AARs)**, record their wins and losses under each tenet, and submit formal recommendations if they think your doctrine needs revising!

---

### 📨 Step 4: Turn On Comms Range & Dispatch Couriers
Want distance and logistics to matter in your campaign?
1. **Enable Comms Range:**
   * Type `range on` (talk only to NPCs in your current sector) or `range satellite` (talk to any sector where you have a station or satellite) directly into the chat box—or toggle it in **SETTINGS > OTHER > Comms range**.
2. **Send a Physical Messenger (Courier):**
   * When an officer or station manager is beyond your comm range, hail one of your local pilots and say:
     * *"Take this message to Mumi Lu: hold the Erebus where she is."*
     * *"Deliver this to the manager of the HAT Argon Trading Station in Hatikvah's Choice I: we can supply your hull parts."*
   * Your courier pilot physically undocks, flies through the jump gates, tracks down the recipient (even if they moved a sector away!), delivers your letter, and flies back with their reply.
   * ⚠️ **Watch the Lanes:** Enemy spies can intercept couriers in deep space and leak the orders they carry!

---

### 👑 Step 5: Build Power Through Contracts, Councils & Vassals
You don't need to paint the map by force to dominate the galaxy:
* **🤝 Sign Standing Supply Contracts:** Hail station managers at starving shipyards or foundries and negotiate recurring supply contracts. Delivering on time earns **hourly reliability premiums** paid out of the buyer's real funds.
* **🏛️ Sway Faction Councils & Offer Peace:** Propose peace to a warring empire (their leaders will weigh it at their next Council session) or call on allied councils for a **Call to Arms** or **Counsel of Peace**.
* **⚖️ Establish Protectorates & Vassals (`POWER` Tab):** Bring weaker realms under your protection. They pay tribute from their **real economic income** and open their economy to you—but keep an eye on their **Three Estates (*Society, Military, Leaders*)** so they don't revolt!

---

## 🛠️ 3. Release-Candidate Tips & Reporting Issues

* **💾 Keep a Separate Backup Save:** AiLive is an ambitious, rapidly evolving mod that touches ship orders, credits, ownership, and faction politics. Always keep a clean backup save when testing new Release Candidates.
* **🔍 Helpful Chat Shortcuts:**
  * Type `whereis <name>` (e.g., `whereis Mumi`) to search every ship and station you own for an officer's exact location or `MISSING` status.
  * Type `/raw` in chat to ask an NPC to step out of character and explain the exact data and reasoning behind their last response.
* **🐛 Found a Bug or Wild Story?**
  * Report bugs on **[AiLive GitHub Issues](https://github.com/KennyG1990/AiLive/issues)** (include your X4 version, AiLive RC version, what the NPC promised, and what the game actually did) or drop into the **[Discord Community](https://discord.gg/5zwxzRvDY)**!
