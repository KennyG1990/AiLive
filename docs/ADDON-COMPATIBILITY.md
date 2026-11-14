# AiLive add-on compatibility notes

For authors of add-ons that run beside AiLive. We post here **before** a release when something an add-on touches is going to change, so you can adjust in time. Watch this file (or the repository) to be told when it changes; the commit history is the change log.

Last updated: 13 Nov 2026.

- [1. Current release and your contact points](#1-current-release-ailive-280-rc1)
- [2. Advance notice: planned changes](#2-advance-notice-planned-changes)
- [3. The add-on interface, version 1](#3-the-add-on-interface-version-1)
- [4. Requests we have received](#4-requests-we-have-received)
- [5. What is stable and what is not](#5-what-is-stable-and-what-is-not)

---

## 1. Current release: AiLive 2.8.0 RC1

Released 13 Nov 2026, build `#1110b646`.

We checked every contact point on the AiLive Voice list against the 2.8.0 release files, the same way as for 2.7.0.

**Result: every function, table, event, MD reference and prompt marker on that list is still present in 2.8.0, with the same name and the same arguments.** Nothing was removed or renamed. The table under "Earlier release" below still describes them.

### What changed in 2.8.0 that may affect an add-on

1. **`SendDirectChat(ctx, text, onReply)` grew again** (about 5%). Same arguments. A wrapper that calls the original should hold; re-test anything that depends on what happens inside it.
2. **The hub's own key opens the hub with no tab asked for.** `AIC_Hub_Menu.open(tab)` is unchanged, but the built-in key now calls `open(nil)`; the hub keeps its remembered tab, and on a save where it has not been shown yet it lands once on a new GETTING STARTED page. If you open the hub yourself and want a particular page, pass the tab as before.
3. **A new kind of voiced message.** During a save's first days the commander's second-in-command writes short letters (voice family `guide`, counted with the other `voices` calls, at most ten on a save). Off with SETTINGS > OTHER > INTERFACE > Getting started > NOTICES ONLY.
4. **`_officerCalls` has one more reader.** A courier feature reads `delivered`; the table and its fields are as before.
5. **`AIChat.open` has more listeners** inside AiLive (the getting-started page ticks "hail" from it). The event and its payload are unchanged.
6. **The add-on interface (section 3) ships in this release** as described there; nothing in it changed since it was first published here.

## Earlier release: AiLive 2.7.0 RC1

Released 11 Nov 2026, build `#1110b555`.

The first add-on we know of, "AiLive Voice", was written against 2.6.0. We checked every contact point its author listed against the 2.7.0 release files.

**Result: every function, table, event, MD reference and prompt marker on that list is still present in 2.7.0, with the same name and the same arguments.** Nothing was removed or renamed.

| Contact point | 2.7.0 | Note |
| --- | --- | --- |
| `ActiveBackend()`, `SendDirect(messages, opts, callback)`, `ReceiptDonePrompt(who, said, ok)`, `ReceiptRewritePrompt(who, said, bad, coa, facts, ways, acted)` | Unchanged | Same arguments, same body |
| `SendDirectChat(ctx, text, onReply)` | Same arguments, **body changed** | It grew by about 12%. A wrapper that calls the original should hold; anything that depends on what happens inside it should be re-tested |
| `RankEffective(tok, ctx)`, `RankPostKey`, `RankN`, `RANK_TITLES` | Unchanged | See the Marine ranks note below |
| `OrderFailuresRead(ship)`, `PlayerDoctrineAdd(text)`, `LoadCard`, `StoreCard`, `NewCard`, card `aic_doctrine`, `_docs.player` | Present | |
| `_officerCalls` (`calls`, `opened`, `delivered`) | Present | |
| `AIC_HTTP`, `X4_Terminal_Menu`, `AIC_Comm_Menu`, `AIC_Hub_Menu` | Present | The hub gained tabs and pages; see below |
| Events `aic.http.update`, `AIChat.open`, `AIChat.officer_call_state`; UI events `log_article`, `log_diplomacy`, `log_alerts` | Present | |
| Conversation `aic_speak`, section `AIInf_Speak`, `State.$current_npc` | Present | |
| `md.aic_contracts.Registry.$ByJob`, offer cue `$job $fid $title $desc $reward $d $Client` | Present | |
| Prompt text `YOU SERVE THE PLAYER`, `Say it again, in the same voice` | Present, same wording | |
| Conversation `max_tokens` 2000 | Unchanged | Other calls changed, see below |

### What changed in 2.7.0 that may affect an add-on

1. **Token limits on background calls moved.** Several short calls were raised (for example 120 to 240, and 260 to 420) so realms and newscasts can write longer. If you sort calls into model tiers by `max_tokens`, some calls now land in a different tier than on 2.6.0. You do not need to guess: see `opts.cat` in section 4, and the request labels in section 3.
2. **New kinds of call.** Realm councils write proclamations, there is a newscast anchor, and many notices are written in a person's voice. More calls reach a replacement backend than on 2.6.0, in categories `councils`, `news`, `voices`, `reports`, `careers`, `governors`, `economy`, `colour`.
3. **Marine ranks.** Fighter and scout pilots now hold non-commissioned ranks on their own ladder. If you use rank to decide what an officer may do, check what `RankEffective` returns for them.
4. **The hub has new tabs and pages** (GOVERNMENT, NEWS, STORYLINES, THE COURT and more) and every tab lost its caption rows. Controller navigation that walks our tables should be re-tested.
5. **The conversation window:** the message box no longer moves down a line after the first reply. If you draw the chat plate at an offset, check that it still sits where you expect.
6. **A new setting, SETTINGS > SOCIAL > CONVERSATION > "Prompt layout".** CLASSIC is the default and is the layout you know. SECTIONED arranges the same briefing under headings. Text appended after the prompt still arrives last, but anything that depends on where a line sits may not.
7. **New inbound messages.** A captain may write to the player asking for orders when an ultimatum or war reaches space their ship is in. It arrives through the same message path as other officer messages.

---

## 2. Advance notice: planned changes

Nothing in this section is released. Dates are not promised. We update each item as it firms up.

| Planned change | What it will touch | Status |
| --- | --- | --- |
| **The add-on interface, version 1** (section 3) | New file `aic_addon.lua`; headers on model requests when an add-on asks; two Lua events | **Built, ships in the next build after 2.7.0 RC1** |
| **An officer who cannot help names who can.** A refusal for want of authority will carry a referral and an offer to pass the order on. | The refusal text and the reply's `refuse` field; the text near the chain-of-command rule in own-officer prompts | Specified, not started |
| **An aide.** One person the player can tell anything, who routes it to the right officer. | A new staff post in the officer registry; a new HAIL entry in the hub | Specified, not started |
| **Suggested lines built from what the officer can really do.** The three opening choices and one of the three after each reply will be computed from the officer's post. | The choices shown in the conversation window; a full order becomes possible without typing | Specified, not started |
| **Controller reach of the hub and conversation screens** will be measured as part of the above. Notes on what you had to change would help us. | Hub and conversation tables | Not started |

---

## 3. The add-on interface, version 1

**Built 11 Nov 2026. Not yet released.** It ships in the next AiLive build after 2.7.0 RC1. It has passed our automated checks and a live request to Player2 with the new headers; it has not yet been run inside the game. Treat this as the plan of record and tell us if something does not fit.

It is read-only: it labels model requests and announces two moments. It changes no prompt, no order, no money and no dice.

### Turning it on

Call this once from your Lua, any time after AiLive's files have loaded:

```lua
local v = AI_Influence.AddonEnable("my_addon")   -- returns 1, or nil if the player switched it off
```

Until an add-on calls this, AiLive sends and announces nothing extra. The player's setting is SETTINGS > OTHER > INTERFACE > "Add-on interface": WHEN AN ADD-ON ASKS (default), ALWAYS, or OFF.

### Request labels

HTTP headers on every model request. Each value is one line of printable ASCII, at most 80 characters; other characters arrive as `?`. The request body is unchanged.

| Header | Value | Replaces |
| --- | --- | --- |
| `X-AiLive-Addon-Api` | `1` | |
| `X-AiLive-Category` | `conv`, `plans`, `autonomy`, `news`, `voices`, `councils`, `diplomacy`, `reports`, `careers`, `governors`, `economy` ... | Sorting by `max_tokens` |
| `X-AiLive-Reask` | `done`, `rewrite` or `promotion`; absent on a normal turn | Matching "Say it again, in the same voice" |
| `X-AiLive-Speaker-Seed` | The speaker's seed, on conversation turns only | |
| `X-AiLive-Speaker-Name` | The speaker's name | Matching "You are (name)" |
| `X-AiLive-Speaker-Serves-Player` | `1` or `0` | Matching "YOU SERVE THE PLAYER" |
| `X-AiLive-Speaker-Rank` | Their rank title; absent if they do not serve the player | |

### Events

```lua
AI_Influence.AddonOn("my_addon", "reply", function(p)
    -- p.seed, p.name, p.serves_player, p.ok, p.text, p.said (what the player said), p.n
end)

AI_Influence.AddonOn("my_addon", "officer_report", function(p)
    -- p.id, p.seed, p.text
end)
```

- `reply` fires after the chat has received the reply. `p.n` is 1 for the first reply of a turn and 2 when a re-said line replaces it.
- `officer_report` fires when a report is opened into the chat.
- `AddonOn` returns `true`, or `false` and a reason. An error inside your listener is logged once and never reaches the game.

With these an add-on can stop wrapping `SendDirectChat`, polling `_officerCalls`, and matching prompt text. Wrapping `ActiveBackend` to point AiLive at your own server is unaffected.

---

## 4. Requests we have received

From "AiLive Voice: what we built on top of AiLive" (11 Nov 2026).

| Request | Status |
| --- | --- |
| A category on each request | **Built** (section 3). Also readable today in Lua: every call passes `opts.cat` to `SendDirect(messages, opts, callback)` |
| The speaker's identity on conversation requests | **Built** (section 3). Also readable today in Lua: `SendDirectChat(ctx, text, onReply)` receives `ctx.npc_seed`, `ctx.target_name`, `ctx.real_facid` (`"player"` means they serve the player) and `ctx.npc_owned` (`"1"` for a person on one of the player's ships or stations) |
| A flag on the receipt re-ask | **Built** (section 3). Until it ships there is none: the re-ask goes out as category `conv` with `max_tokens` 600 |
| A Lua event when a reply is delivered to the chat | **Built** (section 3) |
| A Lua event when an officer report is opened into the chat | **Built** (section 3) |
| A UI event for news written straight to the logbook | Not built. We want this for our own reasons and will do it when that news is given a voice |
| A supported way for an officer to accept a contract offer | Not built. This changes who may commit the player to a contract, so it needs a design decision, not only an event |
| A hook for extra briefing text per officer | Not built. Needs a design decision: it changes what the model reads |
| Suggestion: charted gates in the officer's briefing; refuse an identical order that just failed as unreachable | Received. The log of an officer repeating the same move five times is useful evidence |
| Suggestion: let the receipt re-ask return the first line unchanged when it made no false claim | Received |

---

## 5. What is stable and what is not

- **Stable from the build that ships it:** everything in section 3. We will not rename or remove it without a notice here first, and the version number will change if its meaning does.
- **Least likely to change:** the names and arguments of `SendDirect`, `ActiveBackend`, `LoadCard`, `StoreCard`, the `aic.http.update` clock, the `AIChat.open` event, and the `aic_speak` conversation.
- **May change with notice here:** rank helpers, officer-call state, the contract registry's fields, the hub's tables.
- **Will change without being treated as breaking:** prompt wording (including the two marker sentences above), `max_tokens` values, the internals of `SendDirectChat`, and the layout of any screen.

If you depend on something in the last group, tell us which, and we will either give you something steadier or warn you here before it moves.

### One note for add-ons that use `AIC_HTTP`

A request left open at all times (a long poll) holds AiLive's HTTP pump at its 50 ms rate instead of letting it fall back to 1 second when idle. It works, but it costs frame time for the whole session. A short poll on your own timer, or a longer idle interval, avoids it.

---

Questions or corrections: tell Ken in the AiLive Discord.
