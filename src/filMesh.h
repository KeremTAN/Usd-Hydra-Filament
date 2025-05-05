#include <pxr/imaging/hd/mesh.h>

#include <filament/Engine.h>
#include <filament/Scene.h>
#include <filament/VertexBuffer.h>
#include <filament/IndexBuffer.h>
#include <filament/RenderableManager.h>
#include <utils/Entity.h>

PXR_NAMESPACE_OPEN_SCOPE

class FilMesh : public HdMesh {
public:
    FilMesh(SdfPath const& id) : HdMesh(id) { }

    HdDirtyBits GetInitialDirtyBitsMask() const override;

    void Sync(HdSceneDelegate* delegate, HdRenderParam* renderParam,
                HdDirtyBits* dirtyBits, TfToken const& reprToken) override;
    
    bool NeedsGpuUpload() const;
    void UploadToFilament(filament::Engine* eng, filament::Scene* scene, filament::MaterialInstance* mat);
    
protected:
    HdDirtyBits _PropagateDirtyBits(HdDirtyBits bits) const override;

    void _InitRepr(TfToken const& reprToken, HdDirtyBits* dirtyBits) override;

private:
    // CPU tarafı
    VtVec3fArray m_points{};
    VtIntArray   m_indices{};
    GfMatrix4d   m_xf{};

    bool m_needsGpuUpload{};
    bool m_gpuReady{};

    // Filament kaynakları
    filament::VertexBuffer* m_vb{};
    filament::IndexBuffer*  m_ib{};
    utils::Entity           m_entity{};
};

PXR_NAMESPACE_CLOSE_SCOPE