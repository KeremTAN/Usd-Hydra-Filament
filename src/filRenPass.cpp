#include "filRenPass.h"


PXR_NAMESPACE_OPEN_SCOPE

bool FilRenPass::IsConverged() const { return true; }
void FilRenPass::_Execute(HdRenderPassStateSharedPtr const& renderPassState, TfTokenVector const& renderTags) {}
void FilRenPass::_MarkCollectionDirty() {}
void FilRenPass::_Sync() {}

PXR_NAMESPACE_CLOSE_SCOPE