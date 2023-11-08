#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"
#include "Sprite.hpp"

namespace RSDK
{

namespace Graphics
{

struct Mesh {
    uint16 id;

    inline void Init() { id = (uint16)-1; }

    inline void Load(const char *path, Scopes scope) { id = RSDKTable->LoadMesh(path, scope); }

    inline bool32 Loaded() { return id != (uint16)-1; }

    inline bool32 Matches(SpriteSheet &other) { return this->id == other.id; }
    inline bool32 Matches(SpriteSheet *other)
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

    inline void Init() { id = (uint16)-1; }

    inline void Create(const char *identifier, uint16 faceCount, Scopes scope) { id = RSDKTable->Create3DScene(identifier, faceCount, scope); }
    inline void Prepare() { RSDKTable->Prepare3DScene(id); }
    inline void Draw() { RSDKTable->Draw3DScene(id); }

    inline void SetDiffuseColor(int32 x, int32 y, int32 z) { RSDKTable->SetDiffuseColor(id, x, y, z); }
    inline void SetDiffuseIntensity(int32 x, int32 y, int32 z) { RSDKTable->SetDiffuseIntensity(id, x, y, z); }
    inline void SetSpecularIntensity(int32 x, int32 y, int32 z) { RSDKTable->SetSpecularIntensity(id, x, y, z); }

    inline void AddModel(Mesh &modelFrames, DrawTypes drawMode, Matrix *matWorld, Matrix *matView, color color)
    {
        RSDKTable->AddModelTo3DScene(modelFrames.id, id, drawMode, matWorld, matView, color);
    }
    inline void AddMesh(Mesh &modelFrames, Animator *animator, DrawTypes drawMode, Matrix *matWorld, Matrix *matNormal, color color)
    {
        RSDKTable->AddMeshFrameTo3DScene(modelFrames.id, id, animator, drawMode, matWorld, matNormal, color);
    }

    inline bool32 Loaded() { return id != (uint16)-1; }

    inline bool32 Matches(SpriteSheet &other) { return this->id == other.id; }
    inline bool32 Matches(SpriteSheet *other)
    {
        if (other)
            return this->id == other->id;
        else
            return this->id == (uint16)-1;
    }
};

} // namespace Graphics
} // namespace RSDK