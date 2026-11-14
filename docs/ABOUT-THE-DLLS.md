# About the three DLL files

AiLive ships three small Windows libraries (DLLs). People ask about them, and they should. This page says what each one is, what it does, why the mod cannot work without them, and how you can check them yourself.

## Why a mod for X4 needs DLLs at all

X4 runs mod scripts in a sandbox that has no way to open a network connection. AiLive's characters think through the **Player2** app running on your own computer, so the game has to be able to talk to that app. The only way to give X4's scripts a network connection is to load a small native library. That is the whole reason these files exist.

Without them the mod still loads and the hub still opens, but nobody ever answers you.

**AiLive needs no other mod.** These three files are everything it relies on besides the game and the Player2 app. Earlier versions used SirNukes' Mod Support APIs for hotkeys; that ended when we wrote our own hotkey reader (the third file below), and any note that still says otherwise is out of date.

## The three files

| File | What it is | What it does in AiLive |
| :--- | :--- | :--- |
| `lua3p/luasocket/core.dll` | **LuaSocket 3.1.0**, a widely used open-source networking library (MIT licence). Not written by us. (It reports itself as "LuaSocket 3.0.0" in the game's log; the 3.1.0 release kept the old version text in its source.) | Lets the game send a request to the Player2 app on your own machine (`127.0.0.1:4315`) and read the reply. If you point AiLive at another service yourself in its settings (a local Ollama or KoboldCpp, for example), it talks to that address instead. It connects to nothing you have not set. |
| `lua3p/cjson/cjson.dll` | **lua-cjson 2.1.0.19** from OpenResty, an open-source JSON reader and writer (MIT licence). Not written by us. | Packs and unpacks the mod's own saved records quickly. It has no network or file access of its own. |
| `lua3p/aickeys/aickeys.dll` | **Our own**, 58 lines of C. The full source is in this repository: [`native/aickeys/aickeys.c`](../native/aickeys/aickeys.c). | Makes the hub hotkeys work (`CTRL+SHIFT+U` and the others). X4 gives mods no way to read a key combination, so this asks Windows "is this key down right now?" |

### What the hotkey reader does and does not do

Because a library that reads keys deserves the closest look, here is exactly what it does. You can confirm every point in the 58 lines of source.

- It only answers while **X4 is the window in front**. If you are typing in your browser, a chat, or a password box in another program, it returns nothing.
- It can only be asked about a fixed list of keys: Shift, Ctrl, Alt, letters, digits, the number pad and F1 to F12. Anything else is refused.
- It answers "down or not" at that moment. It keeps no record, installs no keyboard hook, writes no file and has no network code at all.

## You do not have to take our word for it

- **The source is public.** LuaSocket: <https://github.com/lunarmodules/luasocket>. lua-cjson: <https://github.com/openresty/lua-cjson>. Our hotkey reader: [`native/aickeys/aickeys.c`](../native/aickeys/aickeys.c).
- **The build is written down.** [`lua3p/BUILD.md`](../lua3p/BUILD.md) lists the exact upstream commits, the checksum of every download, the compiler and the commands. [`tools/build_lua3p.py`](../tools/build_lua3p.py) is the script that builds all three from those sources; it uses only Python's standard library and never runs a downloaded program. Anyone with Microsoft's free build tools can rebuild the files and compare.
- **The licences ship with the mod**, in the `lua3p` folder.
- **The files are free**, like the rest of the mod.

### Check the files you downloaded

These are the SHA-256 checksums of the three files in **2.8.0 RC2**. They change only when a library is rebuilt, and this page is updated when that happens.

| File | SHA-256 |
| :--- | :--- |
| `lua3p/luasocket/core.dll` | `b0ad8ab91f4ba40ca0cbb6fe11207a91b4b853f44b7515e1ec5c1c5f52269b9f` |
| `lua3p/cjson/cjson.dll` | `75cde82d74d0d2f350bd0fee30bbf5971787d11f5b657a9381ab946132a11051` |
| `lua3p/aickeys/aickeys.dll` | `449931735c7d2c719d085b03a4e90a0cf9b88d5da6aa457ae20f4ac29d68caf7` |

In PowerShell, from the `x4_ai_influence` folder:

```
Get-FileHash lua3p\luasocket\core.dll, lua3p\cjson\cjson.dll, lua3p\aickeys\aickeys.dll
```

If a checksum does not match, you did not get the file from us. Download the mod again from the [official releases](https://github.com/KennyG1990/AiLive/releases).

## On the Steam Workshop: the same files, named `.txt`

The tool Egosoft gives modders for uploading to the Steam Workshop only accepts a short list of file types, and `.dll` is not on it. So on the Workshop (in preparation; AiLive is not there yet) the same three libraries are shipped with a `.txt` ending, and the mod loads them by that name.

We are telling you this plainly because a program file with a text-file name is exactly the kind of thing that should make you look twice.

- They are the **same three files**, byte for byte. Only the name differs, so the checksums above still apply.
- We did not invent this and we are not the only ones who do it. It is how X4 mods that need a native library get onto the Workshop; SirNukes' Mod Support APIs, for example, ships its library the same way. (That mod is only an example of the practice. AiLive does not use it or need it.)
- The mod cannot work on the Workshop without it, for the reason at the top of this page.

If you would rather not have it that way, install the zip from the [releases page](https://github.com/KennyG1990/AiLive/releases) instead: there the files keep their `.dll` names.

## Questions

Ask on [Discord](https://discord.gg/5zwxzRvDY). If your antivirus flags one of the files, please tell us which file and which product, so we can look into it.
