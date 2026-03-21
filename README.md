# mollen-wow

A from-scratch World of Warcraft game engine targeting Legion.

---

## About

mollen-wow is a ground-up reconstruction of the World of Warcraft Legion client and server. The entire engine — networking, game logic, rendering, asset loading, everything — is being written from scratch in modern C++20. No code is copied from Blizzard's binaries. This project does not include any Blizzard Entertainment proprietary data, assets, or code. World of Warcraft is (c) 2004-2026 Blizzard Entertainment, Inc. All rights reserved.

The project reads art assets (models, textures, terrain, data tables) from an existing WoW 7.3.5 client installation. These are Blizzard's content files stored in CASC archives — mollen-wow just needs to know how to parse them. The code itself is entirely ours.

The long-term goal is a fully self-contained, playable World of Warcraft experience: client, server, world, and everything in between.

## Current Status

- [x] **Memory allocator** — Tiered allocation system with hook callbacks, pool stubs, and heap fallback
- [x] **CDataStore** — Sequential packet buffer for reading/writing network data
- [ ] Object model and descriptor system
- [ ] Asset pipeline (CASC, DB2, BLP, M2, ADT)
- [ ] Networking and packet dispatch
- [ ] Server architecture
- [ ] Vulkan renderer
- [ ] Game systems (spells, auras, movement, combat)
- [ ] UI framework and Lua scripting

## Project Structure

```
mollen-wow/
    memory/        Custom memory allocator (static lib)
    datastore/     Packet read/write buffer (static lib)
    core/          Object model, GUIDs, descriptors (planned)
    network/       Client-server protocol, opcodes, cipher (planned)
    server/        Auth server, world server, game logic (planned)
    game/          Entity classes, spells, auras, combat (planned)
    world/         Maps, terrain, movement (planned)
    casc/          CASC archive reader for WoW assets (planned)
    render/        Vulkan renderer (planned)
    ui/            Game UI framework, Lua runtime (planned)
```

## Milestones

### M1 - Foundation *(in progress)*
The bones. Get the fundamental data structures right so everything else can build on top of them.

- Memory allocator with debug tracking
- CDataStore for packet serialization
- ObjectGuid (128-bit Legion GUID type)
- Base type definitions and project scaffold

### M2 - Object Model
How the game represents every entity in the world — players, creatures, items, everything.

- ObjectMgr: object factory, GUID-based lookup, lifecycle management
- Descriptor system covering all 12 types (CGObjectData through CGPlayerDynamicData)
- Class hierarchy: CGObject_C, CGUnit_C, CGPlayer_C, CGItem_C, CGGameObject_C, and friends
- Update mask parsing for selective field synchronization

### M3 — Asset Pipeline
Reading Blizzard's content files so we have something to actually render and work with.

- CASC archive reader to access the WoW installation
- DB2/DBC data table loader (spells, items, creatures, maps, and hundreds more)
- BLP texture decoding
- M2 model parsing (character models, creatures, props)
- WDT/ADT terrain loading (the actual world geometry)

### M4 — Network Layer
The protocol that lets client and server talk to each other.

- Client-server architecture with auth server and world server
- Packet cipher implementation
- Opcode dispatch for all 762 known opcodes
- SMSG/CMSG packet serialization in both directions
- Session authentication and management

### M5 — Renderer
Putting pixels on screen.

- Vulkan device setup, swap chain, render passes, shader pipeline
- ADT terrain rendering with texture splatting
- M2 model rendering with basic animation
- WMO indoor/outdoor rendering (buildings, dungeons, cities)
- Camera system with WoW-style controls
- Sky, fog, and lighting driven by DB2 light data

### M6 — Game Systems
The actual game mechanics that make it feel like WoW.

- Full entity classes with descriptor field access (Unit, Player, GameObject)
- Spell casting and aura system
- Combat log and damage/healing pipeline
- Client-side movement with server reconciliation
- Inventory, equipment, and item tooltips

### M7 — World Loop
Tying it all together into a playable experience.

- Login screen, realm selection, character select, world entry
- Entity create/update/destroy pipeline on both client and server
- Real-time synchronization of all entities in the world
- Chat and social systems
- Lua scripting runtime for UI and addon support
- Server-side world state, NPC spawning, basic AI

## Releases

| Release | When | What you get |
|---------|------|--------------|
| **Alpha** | After M3 + M4 | Client and server communicate. Assets load from disk. You can inspect game data. |
| **Beta** | After M5 + M6 | The world renders. Entities are visible. Basic gameplay works. |
| **v1.0** | After M7 | Fully playable, self-contained World of Warcraft Legion. |

## Building

```bash
cmake -B build -G Ninja
cmake --build build --config Release
```

**Requirements:**
- C++20 compiler (MSVC 19.29+, GCC 12+, or Clang 14+)
- CMake 3.22 or newer
- Vulkan SDK

## Contributing

This is a personal project in its early stages. If you're interested in contributing, open an issue first to discuss what you'd like to work on.

## License

MIT — see [LICENSE](LICENSE) for details.
