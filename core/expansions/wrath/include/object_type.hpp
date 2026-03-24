#ifndef MOLLEN_OBJECT_TYPE_HPP
#define MOLLEN_OBJECT_TYPE_HPP

#include <cstdint>

namespace mwow {

// Wrath 3.3.5a object type IDs (used in SMSG_UPDATE_OBJECT)
enum class ObjectType : uint8_t {
    Object        = 0,
    Item          = 1,
    Container     = 2,
    Unit          = 3,
    Player        = 4,
    GameObject    = 5,
    DynamicObject = 6,
    Corpse        = 7,

    Count         = 8
};

// Type mask bits (used in update object type mask field)
enum class TypeMask : uint16_t {
    Object        = 0x0001,
    Item          = 0x0002,
    Container     = 0x0004,
    Unit          = 0x0008,
    Player        = 0x0010,
    GameObject    = 0x0020,
    DynamicObject = 0x0040,
    Corpse        = 0x0080,
};

// Wrath descriptor field counts per type.
// Each value is the number of uint32_t slots in that type's own descriptor block.
// A full object's descriptors are the cumulative chain of its type hierarchy.
namespace DescriptorSlots {
    inline constexpr uint32_t Object        = 6;
    inline constexpr uint32_t Item          = 58;
    inline constexpr uint32_t Container     = 74;
    inline constexpr uint32_t Unit          = 142;
    inline constexpr uint32_t Player        = 1178;
    inline constexpr uint32_t GameObject    = 12;
    inline constexpr uint32_t DynamicObject = 6;
    inline constexpr uint32_t Corpse        = 30;
}

// Returns the total descriptor slot count for a given object type.
// This is the cumulative chain: e.g. Player = Object + Unit + Player.
inline constexpr uint32_t GetTotalDescriptorSlots(ObjectType type) {
    switch (type) {
        case ObjectType::Object:
            return DescriptorSlots::Object;
        case ObjectType::Item:
            return DescriptorSlots::Object + DescriptorSlots::Item;
        case ObjectType::Container:
            return DescriptorSlots::Object + DescriptorSlots::Item + DescriptorSlots::Container;
        case ObjectType::Unit:
            return DescriptorSlots::Object + DescriptorSlots::Unit;
        case ObjectType::Player:
            return DescriptorSlots::Object + DescriptorSlots::Unit + DescriptorSlots::Player;
        case ObjectType::GameObject:
            return DescriptorSlots::Object + DescriptorSlots::GameObject;
        case ObjectType::DynamicObject:
            return DescriptorSlots::Object + DescriptorSlots::DynamicObject;
        case ObjectType::Corpse:
            return DescriptorSlots::Object + DescriptorSlots::Corpse;
        default:
            return 0;
    }
}

} // namespace mwow

#endif // MOLLEN_OBJECT_TYPE_HPP
