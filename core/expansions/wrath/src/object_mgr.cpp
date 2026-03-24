#include "../include/object_mgr.hpp"
#include <cstring>
#include <utility>

namespace mwow {


// GameObject
GameObject::GameObject() = default;

GameObject::~GameObject() {
    delete[] descriptors;
}

GameObject::GameObject(GameObject&& other) noexcept
    : guid(other.guid)
    , type(other.type)
    , descriptors(other.descriptors)
    , descriptorCount(other.descriptorCount)
{
    other.descriptors     = nullptr;
    other.descriptorCount = 0;
}

GameObject& GameObject::operator=(GameObject&& other) noexcept {
    if (this != &other) {
        delete[] descriptors;

        guid            = other.guid;
        type            = other.type;
        descriptors     = other.descriptors;
        descriptorCount = other.descriptorCount;

        other.descriptors     = nullptr;
        other.descriptorCount = 0;
    }
    return *this;
}

// ObjectMgr
ObjectMgr::ObjectMgr()  = default;
ObjectMgr::~ObjectMgr() = default;

GameObject* ObjectMgr::CreateObject(ObjectType type, ObjectGuid guid) {
    // Validate inputs
    if (guid.IsEmpty()) {
        return nullptr;
    }
    if (static_cast<uint8_t>(type) >= static_cast<uint8_t>(ObjectType::Count)) {
        return nullptr;
    }

    // Reject duplicates
    if (m_objects.contains(guid)) {
        return nullptr;
    }

    // Allocate the object
    auto obj = std::make_unique<GameObject>();
    obj->guid = guid;
    obj->type = type;

    // Allocate descriptor storage (zero-initialized)
    uint32_t slotCount = GetTotalDescriptorSlots(type);
    if (slotCount > 0) {
        obj->descriptors     = new uint32_t[slotCount]();
        obj->descriptorCount = slotCount;
    }

    // Insert into the map and return a non-owning pointer
    GameObject* raw = obj.get();
    m_objects.emplace(guid, std::move(obj));
    return raw;
}

GameObject* ObjectMgr::FindByGUID(const ObjectGuid& guid) const {
    auto it = m_objects.find(guid);
    if (it != m_objects.end()) {
        return it->second.get();
    }
    return nullptr;
}

bool ObjectMgr::DestroyObject(const ObjectGuid& guid) {
    auto it = m_objects.find(guid);
    if (it == m_objects.end()) {
        return false;
    }

    // Clear local player reference if it matches
    if (m_localPlayerGuid == guid) {
        m_localPlayerGuid = ObjectGuid{};
    }

    m_objects.erase(it);
    return true;
}

void ObjectMgr::SetLocalPlayer(const ObjectGuid& guid) {
    m_localPlayerGuid = guid;
}

GameObject* ObjectMgr::GetLocalPlayer() const {
    return FindByGUID(m_localPlayerGuid);
}

std::size_t ObjectMgr::GetObjectCount() const {
    return m_objects.size();
}

void ObjectMgr::Clear() {
    m_objects.clear();
    m_localPlayerGuid = ObjectGuid{};
}

} // namespace mwow
