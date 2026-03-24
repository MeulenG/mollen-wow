#ifndef MOLLEN_OBJECT_GUID_HPP
#define MOLLEN_OBJECT_GUID_HPP

#include <cstdint>
#include <cstddef>
#include <functional>

namespace mwow {

// Wrath 3.3.5a GUID bit layout (64-bit):
//   Bits  0-23: Counter (low 24 bits, unique per type)
//   Bits 24-47: Entry ID (creature/item template ID)
//   Bits 48-63: High type (distinguishes Player, Unit, Item, etc.)
//
// Common high values:
//   0x0000 = Player
//   0x0008 = Item
//   0xF130 = Creature/Unit
//   0xF110 = Pet
//   0xF150 = Vehicle
//   0xF400 = GameObject (spawned)
//   0xF100 = DynamicObject
//   0xF101 = Transport
//   0xF500 = Corpse

class ObjectGuid {
public:
    ObjectGuid() : m_value(0) {}
    explicit ObjectGuid(uint64_t raw) : m_value(raw) {}

    uint64_t GetRaw() const { return m_value; }

    // Bit field extraction
    uint32_t GetCounter() const { return static_cast<uint32_t>(m_value & 0xFFFFFF); }
    uint32_t GetEntry()   const { return static_cast<uint32_t>((m_value >> 24) & 0xFFFFFF); }
    uint16_t GetHigh()    const { return static_cast<uint16_t>(m_value >> 48); }

    // State queries
    bool IsEmpty() const { return m_value == 0; }

    // Type queries
    bool IsPlayer()     const { return GetHigh() == 0x0000 && !IsEmpty(); }
    bool IsItem()       const { return GetHigh() == 0x0008; }
    bool IsGameObject() const { return GetHigh() == 0xF400; }
    bool IsDynObject()  const { return GetHigh() == 0xF100; }
    bool IsTransport()  const { return GetHigh() == 0xF101; }
    bool IsCorpse()     const { return GetHigh() == 0xF500; }

    bool IsCreature() const {
        uint16_t high = GetHigh();
        return high == 0xF130 || high == 0xF110 || high == 0xF150;
    }

    bool IsUnit() const {
        return IsPlayer() || IsCreature();
    }

    // Comparison operators
    bool operator==(const ObjectGuid& other) const { return m_value == other.m_value; }
    bool operator!=(const ObjectGuid& other) const { return m_value != other.m_value; }
    bool operator<(const ObjectGuid& other)  const { return m_value < other.m_value; }

    // Hash functor for unordered containers
    struct Hash {
        std::size_t operator()(const ObjectGuid& guid) const {
            uint64_t v = guid.m_value;
            return static_cast<std::size_t>(v ^ (v >> 32));
        }
    };

private:
    uint64_t m_value;
};

} // namespace mwow

// std::hash specialization
namespace std {
template<>
struct hash<mwow::ObjectGuid> {
    size_t operator()(const mwow::ObjectGuid& guid) const {
        return mwow::ObjectGuid::Hash{}(guid);
    }
};
} // namespace std

#endif // MOLLEN_OBJECT_GUID_HPP
