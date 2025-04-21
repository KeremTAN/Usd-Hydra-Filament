#include <pxr/imaging/hd/mesh.h>

PXR_NAMESPACE_OPEN_SCOPE

class FilMesh : public HdMesh {
public:
    FilMesh(SdfPath const& id) : HdMesh(id) { }

    HdDirtyBits GetInitialDirtyBitsMask() const override;

    void Sync(HdSceneDelegate* delegate, HdRenderParam* renderParam,
                HdDirtyBits* dirtyBits, TfToken const& reprToken) override;

    HdDirtyBits _PropagateDirtyBits(HdDirtyBits bits) const override;

    void _InitRepr(TfToken const& reprToken, HdDirtyBits* dirtyBits) override;
};

PXR_NAMESPACE_CLOSE_SCOPE