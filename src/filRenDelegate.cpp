#include "filRenDelegate.h"
#include "filRenPass.h"
#include "filMesh.h"

PXR_NAMESPACE_OPEN_SCOPE

const TfTokenVector& FilRenDelegate::GetSupportedRprimTypes() const {
    return m_rPrimTypes;
}

const TfTokenVector& FilRenDelegate::GetSupportedSprimTypes() const {
    return m_sPrimTypes;
}

const TfTokenVector& FilRenDelegate::GetSupportedBprimTypes() const { 
    return m_bPrimTypes;
}

HdRenderParam* FilRenDelegate::GetRenderParam() const {
    return m_renderParam.get();
}


HdResourceRegistrySharedPtr FilRenDelegate::GetResourceRegistry() const {
    return m_recourcesRegistry;
}

HdRenderPassSharedPtr FilRenDelegate::CreateRenderPass(HdRenderIndex* index, HdRprimCollection const& collection) { 
    return HdRenderPassSharedPtr(new FilRenPass(index, collection));
}

HdInstancer* FilRenDelegate::CreateInstancer(HdSceneDelegate* delegate, SdfPath const& instancerId) { }

void FilRenDelegate::DestroyInstancer(HdInstancer* instancer) {
    if(instancer){
        delete instancer;
        instancer = nullptr;
    }
}
    
HdRprim* FilRenDelegate::CreateRprim(TfToken const& typeId, SdfPath const& rprimId) { 
    if (typeId == HdPrimTypeTokens->mesh) {
        return new FilMesh(rprimId);
    } else {
        TF_CODING_ERROR("[ X ] Unsupported prim type: %s", typeId.GetText());
        return nullptr;
    }
}
    
void FilRenDelegate::DestroyRprim(HdRprim* rPrim) { 
    if(rPrim){
        delete rPrim;
        rPrim = nullptr;
    }
}
    
HdSprim* FilRenDelegate::CreateSprim(TfToken const& typeId, SdfPath const& sprimId) { 

}

HdSprim* FilRenDelegate::CreateFallbackSprim(TfToken const& typeId) { }

void FilRenDelegate::DestroySprim(HdSprim* sPrim) {
    if(sPrim){
        delete sPrim;
        sPrim = nullptr;
    }
}

HdBprim* FilRenDelegate::CreateBprim(TfToken const& typeId, SdfPath const& bprimId) { }

HdBprim* FilRenDelegate::CreateFallbackBprim(TfToken const& typeId) { }

void FilRenDelegate::DestroyBprim(HdBprim* bPrim) { 
    if(bPrim){
        delete bPrim;
        bPrim = nullptr;
    }
}

void FilRenDelegate::CommitResources(HdChangeTracker* tracker) {}

PXR_NAMESPACE_CLOSE_SCOPE