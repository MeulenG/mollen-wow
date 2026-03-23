# mollen-wow

A from-scratch World of Warcraft game engine, starting with Wrath of the Lich King 3.3.5a.

---

## What is this?

mollen-wow is a ground-up reconstruction of the World of Warcraft client engine in modern C++20. Not an emulator. Not a private server. A complete, clean-room engine implementation that reads art assets from an existing WoW installation and handles everything else from scratch: networking, game logic, rendering, asset loading, the works.

No Blizzard code is copied. The implementation is informed by reverse engineering and publicly available community documentation. This project does not include any Blizzard Entertainment proprietary data, assets, or code.

World of Warcraft is a registered trademark of Blizzard Entertainment, Inc.

## Current status

- [x] Memory allocator with tiered allocation, hook callbacks, and heap fallback
- [x] CDataStore packet buffer for sequential network data read/write
- [ ] ObjectGuid (64-bit for Wrath)
- [ ] Object model and ObjectMgr
- [ ] Descriptor system (8 Wrath types, 373 named fields)
- [ ] Network layer (611 Wrath opcodes)
- [ ] Asset pipeline (MPQ archives, DBC tables, BLP textures, M2 models, ADT terrain)
- [ ] Renderer
- [ ] Game systems

## Project structure

```
mollen-wow/
    memory/        Custom memory allocator (static lib)
    datastore/     Packet read/write buffer (static lib)
    core/          Object model, GUIDs, type system
    expansions/
        wrath/     Wrath 3.3.5a: descriptors, opcodes, packet formats
        legion/    Legion 7.3.5: descriptors, opcodes, packet formats (future)
    network/       Client-server protocol, cipher (planned)
    server/        Auth server, world server (planned)
    game/          Spells, auras, combat, movement (planned)
    world/         Maps, terrain, pathfinding (planned)
    assets/        MPQ reader, DBC loader, BLP decoder (planned)
    render/        Renderer (planned)
    ui/            Game UI framework, Lua runtime (planned)
```

## Roadmap

### M1 - Foundation *(in progress)*

The bones. Memory management, packet serialization, and the basic type system that everything else builds on.

- Memory allocator with debug tracking and hook injection
- CDataStore for packet serialization
- ObjectGuid (64-bit Wrath format)
- Base type definitions and object type enum

### M2 - Object Model

How the game represents every entity in the world.

- ObjectMgr: object factory, GUID-based lookup, lifecycle management
- Descriptor system for all 8 Wrath types (373 named fields across Object, Item, Container, Unit, Player, GameObject, DynamicObject, Corpse)
- Class hierarchy from CGObject through CGPlayer
- Update mask parsing for selective field synchronization

### M3 - Network Layer

The protocol that lets client and server talk.

- 611 Wrath opcodes with packet parsing
- Auth server handshake (SRP6 challenge/proof)
- World server session with encryption
- SMSG/CMSG packet serialization in both directions

### M4 - Game Systems

Making the data come alive.

- Descriptor field access on live objects (read UNIT_FIELD_HEALTH off a unit, etc.)
- Unit, Player, Item, and GameObject entity classes with typed field accessors
- Update mask application from SMSG_UPDATE_OBJECT
- Basic spell and aura data structures

### M5 - Asset Pipeline and Renderer

Reading Blizzard's content files and putting pixels on screen.

- MPQ archive reader for Wrath's data files
- DBC table loader (spells, items, creatures, maps)
- BLP texture decoding
- M2 model parsing and ADT terrain loading
- Basic 3D rendering with camera controls

### M6 - World Integration

Tying it all together.

- Login screen flow: auth, realm list, character select, world entry
- Entity create/update/destroy pipeline
- Chat and social systems
- Lua scripting runtime for UI and addon support

### M7+ - Legion Expansion

Extending the engine to support WoW Legion 7.3.5.

- 128-bit ObjectGuid (up from 64-bit)
- 762 opcodes (up from 611)
- 12 descriptor types with 4,625 player slots (up from 8 types and 1,326 slots)
- Legion-specific systems: artifacts, garrisons, world quests, mythic+, order halls
- CASC archive reader (replaces MPQ)
- DB2 table loader (replaces DBC)

## Releases

| Release | Gate | What you get |
|---------|------|--------------|
| Alpha | M3 + M4 | Client and server communicate. Game data is parsed and inspectable. |
| Beta | M5 + M6 | The world renders. You can log in, see entities, move around. |
| v1.0 | M6 complete | Playable Wrath 3.3.5a experience. |
| v2.0 | M7+ | Legion 7.3.5 expansion support. |

## Building

```bash
cmake -B build -G Ninja
cmake --build build --config Release
```

Requirements:
- C++20 compiler (MSVC 19.29+, GCC 12+, or Clang 14+)
- CMake 3.22 or newer

## Contributing

This is a personal project in its early stages. If you're interested in contributing, open an issue first to discuss what you'd like to work on.

## License

MIT -- see [LICENSE](LICENSE) for details.
