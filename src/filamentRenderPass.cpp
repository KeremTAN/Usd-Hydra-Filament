#include "filamentRenderPass.h"


PXR_NAMESPACE_OPEN_SCOPE

bool FilamentRenderPass::IsConverged() const { return true; }
void FilamentRenderPass::_Execute(HdRenderPassStateSharedPtr const& renderPassState, TfTokenVector const& renderTags) {}
void FilamentRenderPass::_MarkCollectionDirty() {}
void FilamentRenderPass::_Sync() {}

PXR_NAMESPACE_CLOSE_SCOPE