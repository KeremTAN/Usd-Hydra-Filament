#include <pxr/pxr.h>
#include <pxr/imaging/hd/tokens.h>
#include <pxr/imaging/hd/extComputation.h>
#include <pxr/imaging/hd/resourceRegistry.h>
#include <pxr/imaging/hd/camera.h>
#include <pxr/imaging/hd/bprim.h>
#include <pxr/imaging/hd/renderDelegate.h>

#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>

PXR_NAMESPACE_OPEN_SCOPE

class FilRenDelegate final : public HdRenderDelegate {
public:
    /**
     * delete ptr is not healty way to deallocate Filament eng.
     * Therefore, custom deleter is defined while shared_ptr is used
     */
    FilRenDelegate() :
        m_recourcesRegistry(std::make_shared<HdResourceRegistry>()),
        m_engine(filament::Engine::create(),
            [](filament::Engine* e) { 
                filament::Engine::destroy(&e);
            }
        ) // end of m_engine 
    {
        m_rprimTypes.push_back(HdPrimTypeTokens->mesh);
        m_sprimTypes.push_back(HdPrimTypeTokens->camera);
        m_sprimTypes.push_back(HdPrimTypeTokens->material);
        m_sprimTypes.push_back(HdPrimTypeTokens->light);
    
        m_bprimTypes.push_back(HdPrimTypeTokens->renderBuffer);
    } // end of FilRenDelegate

    ~FilRenDelegate() = default;

    const TfTokenVector& GetSupportedRprimTypes() const override;
    const TfTokenVector& GetSupportedSprimTypes() const override;
    const TfTokenVector& GetSupportedBprimTypes() const override;

    HdResourceRegistrySharedPtr GetResourceRegistry() const override;

    HdRenderPassSharedPtr CreateRenderPass(HdRenderIndex* index, HdRprimCollection const& collection) override;

    HdInstancer* CreateInstancer(HdSceneDelegate* delegate, SdfPath const& instancerId) override;

    void DestroyInstancer(HdInstancer* instancer) override;
    
    HdRprim* CreateRprim(TfToken const& typeId, SdfPath const& rprimId) override;
    
    void DestroyRprim(HdRprim* rPrim) override;
    
    HdSprim* CreateSprim(TfToken const& typeId, SdfPath const& sprimId) override;

    HdSprim* CreateFallbackSprim(TfToken const& typeId) override;

    void DestroySprim(HdSprim* sprim) override;

    HdBprim* CreateBprim(TfToken const& typeId, SdfPath const& bprimId) override;

    HdBprim* CreateFallbackBprim(TfToken const& typeId) override;

    void DestroyBprim(HdBprim* bprim) override;

    void CommitResources(HdChangeTracker* tracker) override;

private:
    std::shared_ptr<filament::Engine> m_engine{};
    TfTokenVector m_rprimTypes{};
    TfTokenVector m_sprimTypes{};
    TfTokenVector m_bprimTypes{};
    HdResourceRegistrySharedPtr m_recourcesRegistry{};
};

PXR_NAMESPACE_CLOSE_SCOPE