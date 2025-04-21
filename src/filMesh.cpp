#include "filMesh.h"

PXR_NAMESPACE_OPEN_SCOPE

// All bits set as true;
HdDirtyBits FilMesh::GetInitialDirtyBitsMask() const {

    HdDirtyBits mask { 
      HdChangeTracker::Clean            | HdChangeTracker::InitRepr
    | HdChangeTracker::DirtyPoints      | HdChangeTracker::DirtyTopology
    | HdChangeTracker::DirtyTransform   | HdChangeTracker::DirtyVisibility
    | HdChangeTracker::DirtyCullStyle   | HdChangeTracker::DirtyDoubleSided
    | HdChangeTracker::DirtyDisplayStyle| HdChangeTracker::DirtySubdivTags
    | HdChangeTracker::DirtyNormals     | HdChangeTracker::DirtyInstancer
    | HdChangeTracker::DirtyPrimID      | HdChangeTracker::DirtyRepr
    | HdChangeTracker::DirtyMaterialId  | HdChangeTracker::DirtyPrimvar };

    return mask;
}

// 
void FilMesh::Sync(HdSceneDelegate* delegate, HdRenderParam* renderParam, 
            HdDirtyBits* dirtyBits, TfToken const& reprToken) {
    
    if (*dirtyBits & HdChangeTracker::DirtyPoints) {}

    if (*dirtyBits & HdChangeTracker::DirtyTopology) {}

    if (*dirtyBits & HdChangeTracker::DirtyNormals) {}

    if (*dirtyBits & HdChangeTracker::DirtyTransform) {}

    if (*dirtyBits & HdChangeTracker::DirtyVisibility) {}

    if (*dirtyBits & HdChangeTracker::DirtyMaterialId) {}
    
}

// we do not need any filter for now
HdDirtyBits FilMesh::_PropagateDirtyBits(HdDirtyBits bits) const { 
    return bits;
}

// it used to update the repr's 
void FilMesh::_InitRepr(TfToken const& reprToken, HdDirtyBits* dirtyBits) {
    TF_UNUSED(dirtyBits);

    _ReprVector::iterator it = std::find_if(_reprs.begin(), _reprs.end(), _ReprComparator(reprToken));
    if (it == _reprs.end()) {
        _reprs.emplace_back(reprToken, HdReprSharedPtr());
    }
}

PXR_NAMESPACE_CLOSE_SCOPE