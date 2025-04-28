#include "filRenDelegate.h"
#include "filRenPass.h"
#include "filMesh.h"

PXR_NAMESPACE_OPEN_SCOPE

/**
 * delete ptr is not healty way to deallocate Filament eng.
 * Therefore, custom deleter is defined while shared_ptr is used
 * TODO: if m_engine, m_renderer, etc. can not created, it tries to destroy garbage address. 
 * FIX: above problem
 */
FilRenDelegate::FilRenDelegate() :
    m_resourcesRegistry(std::make_shared<HdResourceRegistry>()),
    m_engine(filament::Engine::create(filament::Engine::Backend::METAL),
        [](filament::Engine* e) noexcept { 
            filament::Engine::destroy(&e);
        }
    ), // end of m_engine
    m_renderer(m_engine->createRenderer(),
        [eng = m_engine.get()](filament::Renderer* r) noexcept {
            eng->destroy(r);
        }
    ), // end of m_renderer
    m_scene(m_engine->createScene(),
        [eng = m_engine.get()](filament::Scene* s) noexcept {
            eng->destroy(s);
        }
    ), // end of m_scene
    m_swapChain(m_engine->createSwapChain(nullptr), // native window pointer
        [eng = m_engine.get()](filament::SwapChain* sc) noexcept {
            eng->destroy(sc);
        }
    ),
    m_renderParam(std::make_shared<FilRenParam>(m_engine.get(),m_renderer.get(), m_scene.get(), m_swapChain.get()))
{
    std::cout << "[ Delegate Ctor ] Filament RenderDelegate initializing...\n";
    if (!m_engine.get() || !m_renderer.get() || !m_scene.get() || !m_swapChain.get()) {
        std::cerr << "[ ERROR ]: Failed to create Filament engine..!\n";
    }
    m_rPrimTypes.push_back(HdPrimTypeTokens->mesh);
    m_sPrimTypes.push_back(HdPrimTypeTokens->camera);
    m_sPrimTypes.push_back(HdPrimTypeTokens->material);
    m_sPrimTypes.push_back(HdPrimTypeTokens->light);
    m_bPrimTypes.push_back(HdPrimTypeTokens->renderBuffer);
    std::cout << "[ Delegate Ctor √ ] Filament Engine created successfully\n";
} // end of FilRenDelegate Ctor

FilRenDelegate::~FilRenDelegate() {
    m_renderParam.reset();
    m_scene.reset();
    m_renderer.reset();
    m_engine.reset();
};

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
    return m_resourcesRegistry;
}

HdRenderSettingDescriptorList FilRenDelegate::GetRenderSettingDescriptors() const {
    return m_settingDescriptors;
}

HdRenderPassSharedPtr FilRenDelegate::CreateRenderPass(HdRenderIndex* index, HdRprimCollection const& collection) { 
    std::cout << "[ CreateRenderPass √ ] Called \n";
    return HdRenderPassSharedPtr(new FilRenPass(index, collection));
}

//TODO: implement HdInstancer in the next steps
HdInstancer* FilRenDelegate::CreateInstancer(HdSceneDelegate* delegate, SdfPath const& instancerId) { 
    return nullptr;
}

void FilRenDelegate::DestroyInstancer(HdInstancer* instancer) {
    if(instancer){
        delete instancer;
        instancer = nullptr;
    }
}
    
HdRprim* FilRenDelegate::CreateRprim(TfToken const& typeId, SdfPath const& rprimId) {
    std::cout << "[ CreateRprim √ ] Called \n";

    if (typeId == HdPrimTypeTokens->mesh) {
        return new FilMesh(rprimId);
    } else {
        TF_CODING_ERROR("[ CreateRprim X ] Unsupported prim type: %s", typeId.GetText());
        std::cout << "[ CreateRprim X ] Unsupported prim type: " << typeId.GetText() <<'\n';
        return nullptr;
    }
}

//TODO: what happend if rPrim, sPrim, bPrim has a garbage value. 
void FilRenDelegate::DestroyRprim(HdRprim* rPrim) { 
    if(rPrim){
        delete rPrim;
        rPrim = nullptr;
    }
}
    
HdSprim* FilRenDelegate::CreateSprim(TfToken const& typeId, SdfPath const& sprimId) { 
    return nullptr;
}

HdSprim* FilRenDelegate::CreateFallbackSprim(TfToken const& typeId) {
    return nullptr;
}

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