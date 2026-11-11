# Item Scale (Kyubu port)

> This is a **port to Kyubu** of the original mod [`SirLefti/Cube-World-Item-Scale-Mod`](https://github.com/SirLefti/Cube-World-Item-Scale-Mod).
> Original author: **SirLefti**. This port is not an official release by the author.

**What it does:** Draws item models in the interface at one size on every resolution.

**Original:** <https://github.com/SirLefti/Cube-World-Item-Scale-Mod>

**Release of the original this was ported from:** <https://github.com/SirLefti/Cube-World-Item-Scale-Mod/releases/latest>

**Side:** client (`sides` in `mod.toml`).

## Installation

Requirements: **Cube World Alpha** (the 2013-07-20 `Cube.exe`, SHA-256 `84a7a132...30bf`, unpatched) and **Kyubu** (the mod loader, <https://github.com/kyubumods/kyubu>; this mod needs `kyubu = "^1.1"`, see `mod.toml`).

1. Install Kyubu with its own installer (`install\install.cmd`). The loader is not part of this mod.
2. Put **`item_scale.zip`** (do not unpack it) into the **`Mods\`** folder next to `Cube.exe`. If `item_scale.zip` is already there, replace it.
3. Start the game. `kyubu\logs\latest.log` should have a line saying `item_scale` loaded.
4. To turn the mod off or remove it, take `item_scale.zip` out of `Mods\` (or switch it off in the mod manager: **Mods** on the title screen).

The old Cube World Mod Launcher is **not needed** for this port and is not compatible with it: do not put the original mod's DLL next to it.

## Settings

File `kyubu\config\item_scale.toml` (Kyubu creates it on first run) or the mod manager. Settings marked *restart* take effect on the next start of the game.

| Setting | Default | Range | What it does |
|---|---|---|---|
| `scale` | `0.87` | 0.2 .. 2.0 | Size of item models in the UI at a 1080p screen (1.0 = vanilla size; smaller on higher resolutions is compensated). |


Mod id: `item_scale`. Source: `Mods\item_scale\src\main.cpp`.
