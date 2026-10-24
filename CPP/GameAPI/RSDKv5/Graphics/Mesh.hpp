#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace RSDK
{

namespace Graphics
{

struct Mesh {
    uint16 id;

    RSDK_FORCE_INLINE void Init() { id = (uint16)-1; }

    RSDK_FORCE_INLINE void Load(const char *path, Scopes scope) { id = RSDKTable->LoadMesh(path, scope); }

    RSDK_FORCE_INLINE bool32 Loaded() { return id != (uint16)-1; }

    RSDK_FORCE_INLINE bool32 Matches(Mesh &other) { return this->id == other.id; }
    RSDK_FORCE_INLINE bool32 Matches(Mesh *other)
    {
        if (other)
            return this->id == other->id;
        else
            return this->id == (uint16)-1;
    }
};

struct Scene3D {
    enum DrawTypes {
        Wireframe,
        SolidColor,

        Unused1,
        Unused2,

        Wireframe_Shaded,
        SolidColor_Shaded,

        SolidColor_Shaded_Blended,

        Wireframe_Screen,
        SolidColor_Screen,

        Wireframe_Shaded_Screen,
        SolidColor_Shaded_Screen,

        SolidColor_Shaded_Blended_Screen,
    };

    uint16 id;

    RSDK_FORCE_INLINE void Init() { id = (uint16)-1; }

    RSDK_FORCE_INLINE void Create(const char *identifier, uint16 faceCount, Scopes scope) { id = RSDKTable->Create3DScene(identifier, faceCount, scope); }
    RSDK_FORCE_INLINE void Prepare() { RSDKTable->Prepare3DScene(id); }
    RSDK_FORCE_INLINE void Draw() { RSDKTable->Draw3DScene(id); }

    RSDK_FORCE_INLINE void SetDiffuseColor(int32 x, int32 y, int32 z) { RSDKTable->SetDiffuseColor(id, x, y, z); }
    RSDK_FORCE_INLINE void SetDiffuseIntensity(int32 x, int32 y, int32 z) { RSDKTable->SetDiffuseIntensity(id, x, y, z); }
    RSDK_FORCE_INLINE void SetSpecularIntensity(int32 x, int32 y, int32 z) { RSDKTable->SetSpecularIntensity(id, x, y, z); }

    RSDK_FORCE_INLINE void AddModel(Mesh &modelFrames, DrawTypes drawMode, Matrix *matWorld, Matrix *matView, color color)
    {
        RSDKTable->AddModelTo3DScene(modelFrames.id, id, drawMode, matWorld, matView, color);
    }
    RSDK_FORCE_INLINE void AddMesh(Mesh &modelFrames, Animator *animator, DrawTypes drawMode, Matrix *matWorld, Matrix *matNormal, color color)
    {
        RSDKTable->AddMeshFrameTo3DScene(modelFrames.id, id, animator, drawMode, matWorld, matNormal, color);
    }

    RSDK_FORCE_INLINE bool32 Loaded() { return id != (uint16)-1; }

    RSDK_FORCE_INLINE bool32 Matches(Scene3D &other) { return this->id == other.id; }
    RSDK_FORCE_INLINE bool32 Matches(Scene3D *other)
    {
        if (other)
            return this->id == other->id;
        else
            return this->id == (uint16)-1;
    }
};

} // namespace Graphics
} // namespace RSDK