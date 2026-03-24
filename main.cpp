#include <cstdio>
#include "mollen_alloc.h"
#include "object_mgr.hpp"

int main() {
    mwow::ObjectMgr mgr;

    // Create a player object (Wrath: 1326 descriptor slots)
    auto* player = mgr.CreateObject(
        mwow::ObjectType::Player,
        mwow::ObjectGuid(0x0000000000000001)
    );

    if (player) {
        std::printf("Created player object, descriptor slots: %u\n",
                    player->descriptorCount);

        mgr.SetLocalPlayer(player->guid);

        auto* found = mgr.GetLocalPlayer();
        std::printf("Local player lookup: %s\n", found ? "OK" : "FAIL");
    }

    // Create a creature
    auto* creature = mgr.CreateObject(
        mwow::ObjectType::Unit,
        mwow::ObjectGuid(0xF130000100000001ULL)
    );

    if (creature) {
        std::printf("Created creature, descriptor slots: %u\n",
                    creature->descriptorCount);
        std::printf("  IsCreature: %s\n",
                    creature->guid.IsCreature() ? "yes" : "no");
    }

    std::printf("Object count: %zu\n", mgr.GetObjectCount());

    mgr.DestroyObject(mwow::ObjectGuid(0xF130000100000001ULL));
    std::printf("After destroying creature: %zu\n", mgr.GetObjectCount());

    mgr.Clear();
    std::printf("After clear: %zu\n", mgr.GetObjectCount());

    return 0;
}
