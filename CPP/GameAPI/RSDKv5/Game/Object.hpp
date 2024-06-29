#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"
#include "../Math/Math.hpp"
#include <list>

#if __clang__
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#endif

// 0x800 scene objects, 0x40 reserved ones, and 0x100 spare slots for creation
#define RESERVE_ENTITY_COUNT (0x40)
#define TEMPENTITY_COUNT     (0x100)
#define SCENEENTITY_COUNT    (0x800)
#define ENTITY_COUNT         (RESERVE_ENTITY_COUNT + SCENEENTITY_COUNT + TEMPENTITY_COUNT)
#define TEMPENTITY_START     (ENTITY_COUNT - TEMPENTITY_COUNT)

#define TYPE_COUNT      (0x100)
#define TYPEGROUP_COUNT (TYPE_COUNT + 4)

#define RSDK_GET_ENTITY(slot, class)      (GameObject::Get<class>(slot))
#define RSDK_GET_ENTITY_GEN(slot)         (GameObject::Get(slot))
#define CREATE_ENTITY(object, data, x, y) (GameObject::Create<object>(data, x, y))

#define foreach_active(type, entityOut)                                                                                                              \
    for (auto entityOut : GameObject::GetEntities<type>(FOR_ACTIVE_ENTITIES))
#define foreach_all(type, entityOut)                                                                                                                 \
    for (auto entityOut : GameObject::GetEntities<type>(FOR_ALL_ENTITIES))
#if RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER >= 2
#define foreach_group(type, entityOut)                                                                                                               \
    for (auto entityOut : GameObject::GetEntities<type>(FOR_GROUP_ENTITIES))
#endif

namespace RSDK
{

enum ActiveFlags {
    ACTIVE_NEVER,
    ACTIVE_ALWAYS,
    ACTIVE_NORMAL,
    ACTIVE_PAUSED,
    ACTIVE_BOUNDS,
    ACTIVE_XBOUNDS,
    ACTIVE_YBOUNDS,
    ACTIVE_RBOUNDS,

    // Not really even a real active value, but some objects set their active states to this so here it is I suppose
    ACTIVE_DISABLED = 0xFF,
};

enum VarTypes {
    VAR_UINT8,
    VAR_UINT16,
    VAR_UINT32,
    VAR_INT8,
    VAR_INT16,
    VAR_INT32,
    VAR_ENUM,
    VAR_BOOL,
    VAR_STRING,
    VAR_VECTOR2,
    VAR_FLOAT,
    VAR_COLOR,
};

enum ForeachTypes {
    FOR_ALL_ENTITIES,
    FOR_ACTIVE_ENTITIES,
#if RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER >= 2
    FOR_GROUP_ENTITIES,
#endif
};

enum ForeachGroups {
    GROUP_ALL,

    GROUP_CUSTOM0 = TYPE_COUNT,
    GROUP_CUSTOM1,
    GROUP_CUSTOM2,
    GROUP_CUSTOM3,
};

enum ObjectClassIDs {
    TYPE_BLANK,
#if RETRO_REV02
    TYPE_DEVOUTPUT,
#endif
};

enum TileCollisionModes {
    TILECOLLISION_NONE, // no tile collisions
    TILECOLLISION_DOWN, // downwards tile collisions
#if RETRO_REV0U
    TILECOLLISION_UP, // upwards tile collisions
#endif
};

struct GameObject {

    struct Static {
        uint16 classID;
        uint8 active;

        inline void EditableVar(uint8 type, const char *name, uint32 offset) { RSDKTable->SetEditableVar(type, name, (uint8)this->classID, offset); }

        inline int32 Count(bool32 isActive = false) { return RSDKTable->GetEntityCount(this->classID, isActive); }

#if RETRO_USE_MOD_LOADER
        inline void Super(int32 callback, void *data = nullptr) { modTable->Super(this->classID, callback, data); }
#endif
    };

    struct Entity {
        void Create(void *data){};
        void Update(){};
        void Draw(){};
        void LateUpdate(){};
#if GAME_INCLUDE_EDITOR
        void EditorDraw(){};
#endif

        static void StageLoad(){};
        static void Serialize(){};
        static void StaticUpdate(){};
#if RETRO_REV0U
        static void StaticLoad(Static *sVars)
        {
            sVars->classID = TYPE_BLANK;
            sVars->active  = ACTIVE_NEVER;
        };
#endif
#if GAME_INCLUDE_EDITOR
        static void EditorLoad(){};
#endif

#if RETRO_REV0U
        void *vfTable;
#endif
        Vector2 position;
        Vector2 scale;
        Vector2 velocity;
        Vector2 updateRange;
        int32 angle;
        int32 alpha;
        int32 rotation;
        int32 groundVel;
        int32 zdepth;
        uint16 group;
        uint16 classID;
        bool32 inRange;
        bool32 isPermanent;
        int32 tileCollisions;
        bool32 interaction;
        bool32 onGround;
        uint8 active;
#if RETRO_REV02
        uint8 filter;
#endif
        uint8 direction;
        uint8 drawGroup;
        uint8 collisionLayers;
        uint8 collisionPlane;
        uint8 collisionMode;
        uint8 drawFX;
        uint8 inkEffect;
        uint8 visible;
        uint8 onScreen;

        inline uint16 Slot() { return RSDKTable->GetEntitySlot(this); }
        inline void Destroy() { RSDKTable->ResetEntity(this, 0, nullptr); }

        inline void Reset(uint32 type, void *data) { RSDKTable->ResetEntity(this, type, data); }
        inline void Reset(uint32 type, int32 data) { RSDKTable->ResetEntity(this, type, INT_TO_VOID(data)); }

        void Copy(Entity *dst, bool32 clearThis) { RSDKTable->CopyEntity(dst, this, clearThis); }

        inline bool32 CheckOnScreen(Vector2 *range) { return RSDKTable->CheckOnScreen(this, range); }

        inline void AddDrawListRef(uint8 drawGroup) { RSDKTable->AddDrawListRef(drawGroup, Slot()); }

        inline bool32 TileCollision(uint16 collisionLayers, uint8 collisionMode, uint8 collisionPlane, int32 xOffset, int32 yOffset, bool32 setPos)
        {
            return RSDKTable->ObjectTileCollision(this, collisionLayers, collisionMode, collisionPlane, xOffset, yOffset, setPos);
        }

        inline bool32 TileGrip(uint16 collisionLayers, uint8 collisionMode, uint8 collisionPlane, int32 xOffset, int32 yOffset, int32 tolerance)
        {
            return RSDKTable->ObjectTileGrip(this, collisionLayers, collisionMode, collisionPlane, xOffset, yOffset, tolerance);
        }

        inline void ProcessMovement(Hitbox *outerBox, Hitbox *innerBox) { return RSDKTable->ProcessObjectMovement(this, outerBox, innerBox); }

        inline bool32 CheckCollisionTouchBox(RSDK::Hitbox *thisHitbox, Entity *other, RSDK::Hitbox *otherHitbox)
        {
            return RSDKTable->CheckObjectCollisionTouchBox(this, thisHitbox, other, otherHitbox);
        }

        inline bool32 CheckCollisionTouchCircle(int32 thisRadius, Entity *other, int32 otherRadius)
        {
            return RSDKTable->CheckObjectCollisionTouchCircle(this, thisRadius, other, otherRadius);
        }

        inline uint8 CheckCollisionBox(RSDK::Hitbox *thisHitbox, Entity *other, RSDK::Hitbox *otherHitbox, bool32 setPos = true)
        {
            return RSDKTable->CheckObjectCollisionBox(this, thisHitbox, other, otherHitbox, setPos);
        }

        inline bool32 CheckCollisionPlatform(RSDK::Hitbox *thisHitbox, Entity *other, RSDK::Hitbox *otherHitbox, bool32 setPos = true)
        {
            return RSDKTable->CheckObjectCollisionPlatform(this, thisHitbox, other, otherHitbox, setPos);
        }

#if RETRO_USE_MOD_LOADER
        inline void Super(int32 callback, void *data = nullptr) { modTable->Super(this->classID, callback, data); }
#endif
    };

    static inline Entity *Create(void *data, int32 x, int32 y) { return (Entity *)RSDKTable->CreateEntity(0, data, x, y); }
    static inline Entity *Create(int32 data, int32 x, int32 y) { return (Entity *)RSDKTable->CreateEntity(0, INT_TO_VOID(data), x, y); }

    template <typename T> static inline T *Create(void *data, int32 x, int32 y)
    {
        return (T *)RSDKTable->CreateEntity(T::sVars->classID, data, x, y);
    }

    template <typename T> static inline T *Create(int32 data, int32 x, int32 y)
    {
        return (T *)RSDKTable->CreateEntity(T::sVars->classID, INT_TO_VOID(data), x, y);
    }

    static inline Entity *Get(uint16 slot) { return (Entity *)RSDKTable->GetEntity(slot); }
    template <typename T> static inline T *Get(uint16 slot) { return (T *)RSDKTable->GetEntity(slot); }

    template <typename T> static inline int32 Count(bool32 isActive = false) { return RSDKTable->GetEntityCount(T::sVars->classID, isActive); }

    static inline void Copy(Entity *dst, Entity *src, bool32 clearSrc) { RSDKTable->CopyEntity(dst, src, clearSrc); }
    static inline void Copy(void *dst, void *src, bool32 clearSrc) { RSDKTable->CopyEntity(dst, src, clearSrc); }

    static inline void Reset(int32 slot, uint32 type, void *data) { RSDKTable->ResetEntitySlot(slot, type, data); }
    static inline void Reset(int32 slot, uint32 type, int32 data) { RSDKTable->ResetEntitySlot(slot, type, INT_TO_VOID(data)); }

    template <typename T> static inline std::list<T *> GetEntities(ForeachTypes type)
    {
        std::list<T *> list;

        uint16 group = T::sVars ? T::sVars->classID : GROUP_ALL;

        T *entity = nullptr;
        if (type == FOR_ALL_ENTITIES) {
            while (RSDKTable->GetAllEntities(group, (void **)&entity)) list.push_back(entity);
        }
        else if (type == FOR_ACTIVE_ENTITIES) {
            while (RSDKTable->GetActiveEntities(group, (void **)&entity)) list.push_back(entity);
        }

        return list;
    }

    template <typename T> static inline std::list<T *> GetEntities(ForeachTypes type, uint16 group)
    {
        std::list<T *> list;

        T *entity = nullptr;
        if (type == FOR_ALL_ENTITIES) {
            while (RSDKTable->GetAllEntities(group, (void **)&entity)) list.push_back(entity);
        }
        else if (type == FOR_ACTIVE_ENTITIES) {
            while (RSDKTable->GetActiveEntities(group, (void **)&entity)) list.push_back(entity);
        }
#if RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER >= 2
        else if (type == FOR_GROUP_ENTITIES) {
            while (modTable->GetGroupEntities(group, (void **)&entity)) list.push_back(entity);
        }
#endif

        return list;
    }

    static inline std::list<Entity *> GetEntities(ForeachTypes type)
    {
        std::list<Entity *> list;

        Entity *entity = nullptr;
        if (type == FOR_ALL_ENTITIES) {
            while (RSDKTable->GetAllEntities(GROUP_ALL, (void **)&entity)) list.push_back(entity);
        }
        else if (type == FOR_ACTIVE_ENTITIES) {
            while (RSDKTable->GetActiveEntities(GROUP_ALL, (void **)&entity)) list.push_back(entity);
        }
#if RETRO_USE_MOD_LOADER && RETRO_MOD_LOADER_VER >= 2
        else if (type == FOR_GROUP_ENTITIES) {
            while (modTable->GetGroupEntities(GROUP_ALL, (void **)&entity)) list.push_back(entity);
        }
#endif

        return list;
    }

    static inline std::list<Entity *> GetEntities(ForeachTypes type, uint16 group)
    {
        std::list<Entity *> list;

        Entity *entity = nullptr;
        if (type == FOR_ALL_ENTITIES) {
            while (RSDKTable->GetAllEntities(group, (void **)&entity)) list.push_back(entity);
        }
        else if (type == FOR_ACTIVE_ENTITIES) {
            while (RSDKTable->GetActiveEntities(group, (void **)&entity)) list.push_back(entity);
        }

        return list;
    }

    static inline uint16 Find(const char *name) { return RSDKTable->FindObject(name); }

#if RETRO_USE_MOD_LOADER
    static inline void *FindClass(const char *name) { return modTable->FindObject(name); }
#endif

#if GAME_INCLUDE_EDITOR
    static inline void SetActiveVariable(int32 classID, const char *name) { RSDKTable->SetActiveVariable(classID, name); }
    static inline void AddVarEnumValue(const char *name) { RSDKTable->AddVarEnumValue(name); }
#endif
};

struct ObjectRegistration {
    const char *name;
    void *padding;
    void (*update)(void);
    void (*lateUpdate)(void);
    void (*staticUpdate)(void);
    void (*draw)(void);
    void (*create)(void *data);
    void (*stageLoad)(void);
    void (*editorLoad)(void);
    void (*editorDraw)(void);
    void (*serialize)(void);
#if RETRO_REV0U
    void (*staticLoad)(void *staticVars);
#endif
    void **staticVars;
    uint32 entityClassSize;
    uint32 staticClassSize;

#if RETRO_USE_MOD_LOADER
    void **modStaticVars;
    uint32 modStaticClassSize;
    const char *inherit;
    bool32 isModded;
#endif
};

struct EntityBase : public GameObject::Entity {
    void *data[0x100];
#if RETRO_REV0U
    void *unknown;
#endif
};

extern int32 registerObjectListCount;
extern ObjectRegistration registerObjectList[0x400];
#if RETRO_REV02
extern int32 registerStaticListCount;
extern ObjectRegistration registerStaticList[0x400];
#endif

template <typename E> static inline typename E::Static *RegisterObject(typename E::Static **sVars, const char *name)
{
    if (registerObjectListCount < 0x400) {
        ObjectRegistration *object = &registerObjectList[registerObjectListCount++];
        memset(object, 0, sizeof(ObjectRegistration));
        object->name = name;

        if (&E::Update != &GameObject::Entity::Update)
            object->update = E::_Update;

        if (&E::LateUpdate != &GameObject::Entity::LateUpdate)
            object->lateUpdate = E::_LateUpdate;

        if (&E::StaticUpdate != &GameObject::Entity::StaticUpdate)
            object->staticUpdate = E::StaticUpdate;

        if (&E::Draw != &GameObject::Entity::Draw)
            object->draw = E::_Draw;

        if (&E::Create != &GameObject::Entity::Create)
            object->create = E::_Create;

        if (&E::StageLoad != &GameObject::Entity::StageLoad)
            object->stageLoad = E::StageLoad;

#if GAME_INCLUDE_EDITOR
        if (&E::EditorLoad != &GameObject::Entity::EditorLoad)
            object->editorLoad = E::EditorLoad;

        if (&E::EditorDraw != &GameObject::Entity::EditorDraw)
            object->editorDraw = E::_EditorDraw;
#endif

#if RETRO_REV0U
        if (((void (**)(void *)) & E::StaticLoad) != ((void (**)(void *)) & GameObject::Entity::StaticLoad))
            object->staticLoad = (void (*)(void *))E::StaticLoad;
#endif

        if (&E::Serialize != &GameObject::Entity::Serialize)
            object->serialize = E::Serialize;

        object->staticVars      = (void **)sVars;
        object->entityClassSize = sizeof(E);
        object->staticClassSize = sizeof(typename E::Static);
    }
    *sVars = nullptr;

    return nullptr;
}

#if RETRO_REV02
template <typename E> static inline typename E::Static *RegisterStaticVars(typename E::Static **sVars, const char *name)
{
    if (registerStaticListCount < 0x400) {
        ObjectRegistration *object = &registerStaticList[registerStaticListCount++];
        memset(object, 0, sizeof(ObjectRegistration));
        object->name = name;

        object->staticVars      = (void **)sVars;
        object->staticClassSize = sizeof(E);
    }
    *sVars = nullptr;

    return nullptr;
}
#endif

#define RSDK_REGISTER_OBJECT(obj) obj::Static *obj::sVars = RSDK::RegisterObject<obj>(&obj::sVars, #obj);

#if RETRO_REV02
#define RSDK_REGISTER_STATIC_VARS(stVars) stVars::Static *stVars::sVars = RSDK::RegisterStaticVars<stVars>(&stVars::sVars, #stVars);
#endif

#define RSDK_EDITABLE_VAR(object, type, var) sVars->EditableVar(type, #var, offsetof(object, var))

#define RSDK_INIT_STATIC_VARS(object) memset(sVars, 0, sizeof(object::Static))

#define RSDK_DECLARE(obj)                                                                                                                            \
    static Static *sVars;                                                                                                                            \
                                                                                                                                                     \
    static void _Create(void *data) { ((obj *)RSDK::sceneInfo->entity)->Create(data); }                                                              \
    static void _Draw() { ((obj *)RSDK::sceneInfo->entity)->Draw(); }                                                                                \
    static void _Update() { ((obj *)RSDK::sceneInfo->entity)->Update(); }                                                                            \
    static void _LateUpdate() { ((obj *)RSDK::sceneInfo->entity)->LateUpdate(); }                                                                    \
    static void _EditorDraw() { ((obj *)RSDK::sceneInfo->entity)->EditorDraw(); }

// Some extra precaution to prevent crashes in editor
#define RSDK_ACTIVE_VAR(sVars, var)                                                                                                                  \
    if (sVars) {                                                                                                                                     \
        RSDK::GameObject::SetActiveVariable(sVars->classID, #var);                                                                                   \
    }                                                                                                                                                \
    else {                                                                                                                                           \
        RSDK::GameObject::SetActiveVariable(-1, #var);                                                                                               \
    }
#define RSDK_ENUM_VAR(name, ...) RSDK::GameObject::AddVarEnumValue(name)

// not in the original, used for RE2 :]
#if GAME_INCLUDE_EDITOR
#define showGizmos()                           (sceneInfo->listPos == sceneInfo->entitySlot || sceneInfo->effectGizmo)
#define RSDK_DRAWING_OVERLAY(isDrawingOverlay) sceneInfo->debugMode = isDrawingOverlay

#else
#define RSDK_DECLARE(obj)                                                                                                                            \
    static Static *sVars;                                                                                                                            \
                                                                                                                                                     \
    static void _Create(void *data) { static_cast<obj *>(RSDK::sceneInfo->entity)->Create(data); }                                                   \
    static void _Draw() { static_cast<obj *>(RSDK::sceneInfo->entity)->Draw(); }                                                                     \
    static void _Update() { static_cast<obj *>(RSDK::sceneInfo->entity)->Update(); }                                                                 \
    static void _LateUpdate() { static_cast<obj *>(RSDK::sceneInfo->entity)->LateUpdate(); }
#endif

#if RETRO_USE_MOD_LOADER
namespace Mod
{
template <typename E>
static inline typename E::Static *RegisterObject(typename E::Static **sVars, typename E::ModStatic **modSVars, const char *name,
                                                 const char *inherit = "")
{
    if (registerObjectListCount < 0x400) {
        ObjectRegistration *object = &registerObjectList[registerObjectListCount++];
        memset(object, 0, sizeof(ObjectRegistration));
        object->name = name;

        if (&E::Update != &GameObject::Entity::Update)
            object->update = E::_Update;

        if (&E::LateUpdate != &GameObject::Entity::LateUpdate)
            object->lateUpdate = E::_LateUpdate;

        if (&E::StaticUpdate != &GameObject::Entity::StaticUpdate)
            object->staticUpdate = E::StaticUpdate;

        if (&E::Draw != &GameObject::Entity::Draw)
            object->draw = E::_Draw;

        if (&E::Create != &GameObject::Entity::Create)
            object->create = E::_Create;

        if (&E::StageLoad != &GameObject::Entity::StageLoad)
            object->stageLoad = E::StageLoad;

#if GAME_INCLUDE_EDITOR
        if (&E::EditorLoad != &GameObject::Entity::EditorLoad)
            object->editorLoad = E::EditorLoad;

        if (&E::EditorDraw != &GameObject::Entity::EditorDraw)
            object->editorDraw = E::_EditorDraw;
#endif

#if RETRO_REV0U
        if (((void (**)(void *)) & E::StaticLoad) != ((void (**)(void *)) & GameObject::Entity::StaticLoad))
            object->staticLoad = (void (*)(void *))E::StaticLoad;
#endif

        if (&E::Serialize != &GameObject::Entity::Serialize)
            object->serialize = E::Serialize;

        object->staticVars         = (void **)sVars;
        object->modStaticVars      = (void **)modSVars;
        object->entityClassSize    = sizeof(E);
        object->staticClassSize    = sizeof(typename E::Static);
        object->modStaticClassSize = sizeof(typename E::ModStatic);

        object->isModded = true;
        object->inherit  = inherit;
    }
    *sVars    = nullptr;
    *modSVars = nullptr;

    return nullptr;
}
} // namespace Mod

#define MOD_DECLARE(obj)                                                                                                                             \
    static ModStatic *modSVars;                                                                                                                      \
    RSDK_DECLARE(obj)

#define MOD_REGISTER_OBJECT(obj)                                                                                                                     \
    obj::Static *obj::sVars       = RSDK::Mod::RegisterObject<obj>(&obj::sVars, &obj::modSVars, #obj);                                               \
    obj::ModStatic *obj::modSVars = nullptr;

#define MOD_REGISTER_OBJECT_HOOK(obj) obj::Static *obj::sVars = RSDK::Mod::RegisterObjectHook<obj>(&obj::sVars, #obj);

#endif

} // namespace RSDK