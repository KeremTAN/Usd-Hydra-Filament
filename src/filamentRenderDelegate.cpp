#include "filamentRenderDelegate.h"




PXR_NAMESPACE_OPEN_SCOPE

const TfTokenVector& FilamentRenderDelegate::GetSupportedRprimTypes() const { }
const TfTokenVector& FilamentRenderDelegate::GetSupportedSprimTypes() const { }
const TfTokenVector& FilamentRenderDelegate::GetSupportedBprimTypes() const { }

HdResourceRegistrySharedPtr FilamentRenderDelegate::GetResourceRegistry() const { }

HdRenderPassSharedPtr FilamentRenderDelegate::CreateRenderPass(HdRenderIndex* index, HdRprimCollection const& collection) { }

HdInstancer* FilamentRenderDelegate::CreateInstancer(HdSceneDelegate* delegate, SdfPath const& instancerId) { }

void FilamentRenderDelegate::DestroyInstancer(HdInstancer* instancer) { }
    
HdRprim* FilamentRenderDelegate::CreateRprim(TfToken const& typeId, SdfPath const& rprimId) { }
    
void FilamentRenderDelegate::DestroyRprim(HdRprim* rPrim) { }
    
HdSprim* FilamentRenderDelegate::CreateSprim(TfToken const& typeId, SdfPath const& sprimId) { }

HdSprim* FilamentRenderDelegate::CreateFallbackSprim(TfToken const& typeId) { }

void FilamentRenderDelegate::DestroySprim(HdSprim* sprim) { }

HdBprim* FilamentRenderDelegate::CreateBprim(TfToken const& typeId, SdfPath const& bprimId) { }

HdBprim* FilamentRenderDelegate::CreateFallbackBprim(TfToken const& typeId) { }

void FilamentRenderDelegate::DestroyBprim(HdBprim* bprim) { }

void FilamentRenderDelegate::CommitResources(HdChangeTracker* tracker) { }

PXR_NAMESPACE_CLOSE_SCOPE