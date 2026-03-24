#ifndef MOLLEN_OBJECT_MGR_HPP
#define MOLLEN_OBJECT_MGR_HPP

#include "object_guid.hpp"
#include "object_type.hpp"
#include <cstdint>
#include <cstddef>
#include <unordered_map>
#include <memory>

namespace mwow {

// Minimal game object representation.
// Holds a GUID, a type, and a flat descriptor array (uint32_t slots).
// This will evolve into a full class hierarchy (CGObject -> CGUnit -> CGPlayer)
// in M2; for now it's enough to get ObjectMgr working.
struct GameObject {
    ObjectGuid  guid;
    ObjectType  type = ObjectType::Object;
    uint32_t*   descriptors     = nullptr;
    uint32_t    descriptorCount = 0;

    GameObject();
    ~GameObject();

    // Non-copyable
    GameObject(const GameObject&)            = delete;
    GameObject& operator=(const GameObject&) = delete;

    // Movable
    GameObject(GameObject&& other) noexcept;
    GameObject& operator=(GameObject&& other) noexcept;
};

class ObjectMgr {
public:
    ObjectMgr();
    ~ObjectMgr();

    // Create an object of the given type, assign it the given GUID,
    // allocate its descriptor array, and register it in the map.
    // Returns a non-owning pointer to the object, or nullptr on failure.
    GameObject* CreateObject(ObjectType type, ObjectGuid guid);

    // Look up an object by GUID. Returns nullptr if not found.
    GameObject* FindByGUID(const ObjectGuid& guid) const;

    // Remove and destroy an object. Returns true if it existed.
    bool DestroyObject(const ObjectGuid& guid);

    // Local player management.
    void SetLocalPlayer(const ObjectGuid& guid);
    GameObject* GetLocalPlayer() const;

    // Stats.
    std::size_t GetObjectCount() const;

    // Destroy all managed objects.
    void Clear();

private:
    using ObjectMap = std::unordered_map<
        ObjectGuid,
        std::unique_ptr<GameObject>,
        ObjectGuid::Hash
    >;

    ObjectMap   m_objects;
    ObjectGuid  m_localPlayerGuid;
};

} // namespace mwow

#endif // MOLLEN_OBJECT_MGR_HPP
