#include "filRenDelegate.h"

PXR_NAMESPACE_OPEN_SCOPE

const TfTokenVector& FilRenDelegate::GetSupportedRprimTypes() const {
    return m_rprimTypes;
}

const TfTokenVector& FilRenDelegate::GetSupportedSprimTypes() const {
    return m_sprimTypes;
}

const TfTokenVector& FilRenDelegate::GetSupportedBprimTypes() const { 
    return m_bprimTypes;
}

HdResourceRegistrySharedPtr FilRenDelegate::GetResourceRegistry() const {
    return m_recourcesRegistry;
}

HdRenderPassSharedPtr FilRenDelegate::CreateRenderPass(HdRenderIndex* index, HdRprimCollection const& collection) { }

HdInstancer* FilRenDelegate::CreateInstancer(HdSceneDelegate* delegate, SdfPath const& instancerId) { }

void FilRenDelegate::DestroyInstancer(HdInstancer* instancer) { }
    
HdRprim* FilRenDelegate::CreateRprim(TfToken const& typeId, SdfPath const& rprimId) { }
    
void FilRenDelegate::DestroyRprim(HdRprim* rPrim) { }
    
HdSprim* FilRenDelegate::CreateSprim(TfToken const& typeId, SdfPath const& sprimId) { }

HdSprim* FilRenDelegate::CreateFallbackSprim(TfToken const& typeId) { }

void FilRenDelegate::DestroySprim(HdSprim* sprim) { }

HdBprim* FilRenDelegate::CreateBprim(TfToken const& typeId, SdfPath const& bprimId) { }

HdBprim* FilRenDelegate::CreateFallbackBprim(TfToken const& typeId) { }

void FilRenDelegate::DestroyBprim(HdBprim* bprim) { }

void FilRenDelegate::CommitResources(HdChangeTracker* tracker) { }

PXR_NAMESPACE_CLOSE_SCOPE