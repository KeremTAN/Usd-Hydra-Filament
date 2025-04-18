#include "filMesh.h"

PXR_NAMESPACE_OPEN_SCOPE

HdDirtyBits FilMesh::GetInitialDirtyBitsMask() const { }

void FilMesh::Sync(HdSceneDelegate* delegate, HdRenderParam* renderParam,
            HdDirtyBits* dirtyBits, TfToken const& reprToken) { }

TfTokenVector const& FilMesh::GetBuiltinPrimvarNames() const { }

HdDirtyBits FilMesh::_PropagateDirtyBits(HdDirtyBits bits) const { }

void FilMesh::_InitRepr(TfToken const& reprToken, HdDirtyBits* dirtyBits) { }

PXR_NAMESPACE_CLOSE_SCOPE