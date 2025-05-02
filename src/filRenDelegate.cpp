#include "filRenDelegate.h"
#include "filRenPass.h"
#include "filMesh.h"
#include "filCamera.h"

PXR_NAMESPACE_OPEN_SCOPE

/**
 * delete ptr is not healty way to deallocate Filament eng.
 * Therefore, custom deleter is defined while shared_ptr is used
 */
FilRenDelegate::FilRenDelegate()
    : m_resourcesRegistry(std::make_shared<HdResourceRegistry>())
    , m_engine(
          filament::Engine::create(filament::Engine::Backend::METAL),
          [](filament::Engine* e) noexcept { 
            filament::Engine::destroy(&e);})
{
    const auto& eng = m_engine.get();

    if(eng) {
        m_renderer = std::shared_ptr<filament::Renderer>(eng->createRenderer(),
            [eng](filament::Renderer* renderer) noexcept {
                if (renderer) eng->destroy(renderer);
        });
    
        m_scene = std::shared_ptr<filament::Scene>(eng->createScene(),
            [eng](filament::Scene* scene) noexcept {
                if (scene) eng->destroy(scene);
        });
    
        m_swapChain = std::shared_ptr<filament::SwapChain>(eng->createSwapChain(nullptr),
            [eng](filament::SwapChain* swapChain) noexcept {
                if (swapChain) eng->destroy(swapChain);
        });
        
        m_view = std::shared_ptr<filament::View>(eng->createView(),
            [eng](filament::View* view) noexcept {
                if (view) eng->destroy(view);
        });

        m_cameraEntity = utils::EntityManager::get().create();
        m_camera = std::shared_ptr<filament::Camera>(m_engine->createCamera(m_cameraEntity),
            [eng = m_engine, ce = m_cameraEntity](filament::Camera* camera) noexcept {
                if (camera && !ce.isNull()) {
                    eng->destroyCameraComponent(ce);
                    utils::EntityManager::get().destroy(ce);
                }
            }
        );

        m_renderParam = std::make_shared<FilRenParam>(
            eng, m_renderer.get(), m_scene.get(), m_swapChain.get(), m_view.get(), m_camera.get());
        
        std::cout << "[ o Delegate Ctor ] initializing...\n";
    }
    else { // TODO: add a assert of hydra or std c++
        std::cerr << "[ X Delegate Ctor ] Empty Filament Engine...!\n";
        return;
    }

    
    if (!m_engine.get() || !m_renderer.get() || !m_scene.get() || !m_swapChain.get() || !m_view.get() || !m_camera.get()) {
        std::cerr << "[ X Delegate Ctor ] There is a Missing Part of Filament engine..!\n";
        return;
    }
    
    m_rPrimTypes.push_back(HdPrimTypeTokens->mesh);
    m_sPrimTypes.push_back(HdPrimTypeTokens->camera);
    // m_sPrimTypes.push_back(HdPrimTypeTokens->material);
    // m_sPrimTypes.push_back(HdPrimTypeTokens->light);
    // m_bPrimTypes.push_back(HdPrimTypeTokens->renderBuffer);
    std::cout << "[ o Delegate Ctor ] created successfully\n";
} // end of FilRenDelegate Ctor

FilRenDelegate::~FilRenDelegate() = default;

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
    std::cout << "[ o CreateRenderPass ] Called \n";
    return std::make_shared<FilRenPass>(index, collection, m_renderParam.get());
}

//TODO: implement HdInstancer in the next steps
HdInstancer* FilRenDelegate::CreateInstancer(HdSceneDelegate* delegate, SdfPath const& instancerId) { 
    return nullptr;
}

void FilRenDelegate::DestroyInstancer(HdInstancer* instancer) {
    // if(instancer){
    //     delete instancer;
    //     instancer = nullptr;
    // }
}
    
HdRprim* FilRenDelegate::CreateRprim(TfToken const& typeId, SdfPath const& rprimId) {
    std::cout << "[ o CreateRprim ] Called \n";

    if (typeId == HdPrimTypeTokens->mesh) {
        return new FilMesh(rprimId);
    }
    else {
        TF_CODING_ERROR("[ X CreateRprim ] Unsupported prim type: %s", typeId.GetText());
        std::cout << "[ X CreateRprim ] Unsupported prim type: " << typeId.GetText() <<'\n';
        return nullptr;
    }
}

void FilRenDelegate::DestroyRprim(HdRprim* rPrim) { 
    delete rPrim;
}
    
HdSprim* FilRenDelegate::CreateSprim(TfToken const& typeId, SdfPath const& sprimId) { 
    std::cout << "[ o CreateSprim ] Called \n";

    if (typeId == HdPrimTypeTokens->camera) {
        return new FilCamera(sprimId);
    }
    else {
        TF_CODING_ERROR("[ X CreateSprim ] Unsupported prim type: %s", typeId.GetText());
        std::cout << "[ X CreateSprim ] Unsupported prim type: " << typeId.GetText() <<'\n';
        return nullptr;
    }
}

HdSprim* FilRenDelegate::CreateFallbackSprim(TfToken const& typeId) {
    return nullptr;
}

void FilRenDelegate::DestroySprim(HdSprim* sPrim) {
    delete sPrim;
}

HdBprim* FilRenDelegate::CreateBprim(TfToken const& typeId, SdfPath const& bprimId) { 
    return nullptr;
}

HdBprim* FilRenDelegate::CreateFallbackBprim(TfToken const& typeId) {
    return nullptr;
 }

void FilRenDelegate::DestroyBprim(HdBprim* bPrim) {
    delete bPrim;
}

void FilRenDelegate::CommitResources(HdChangeTracker* tracker) {}

PXR_NAMESPACE_CLOSE_SCOPE