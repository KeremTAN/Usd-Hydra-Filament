#include <pxr/pxr.h>
#include <pxr/imaging/hd/renderDelegate.h>

#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>

PXR_NAMESPACE_OPEN_SCOPE

class FilamentRenderDelegate : public HdRenderDelegate {
public:
    FilamentRenderDelegate() : m_engine(
        filament::Engine::create(),
        [](filament::Engine* e) { 
            filament::Engine::destroy(&e);
        }) // end of m_engine 
    {}

    virtual ~FilamentRenderDelegate()  = default;

    virtual const TfTokenVector& GetSupportedRprimTypes() const override;
    virtual const TfTokenVector& GetSupportedSprimTypes() const override;
    virtual const TfTokenVector& GetSupportedBprimTypes() const override;

    virtual HdResourceRegistrySharedPtr GetResourceRegistry() const override;

    virtual HdRenderPassSharedPtr CreateRenderPass(HdRenderIndex *index,
                HdRprimCollection const& collection) override;

    virtual HdInstancer* CreateInstancer(HdSceneDelegate *delegate, SdfPath const &instancerId) override;

    virtual void DestroyInstancer(HdInstancer *instancer) override;
    
    virtual HdRprim* CreateRprim(TfToken const& typeId, SdfPath const& rprimId) override;
    
    virtual void DestroyRprim(HdRprim *rPrim) override;
    
    virtual HdSprim* CreateSprim(TfToken const& typeId, SdfPath const& sprimId) override;

    virtual HdSprim* CreateFallbackSprim(TfToken const &typeId) override;

    virtual void DestroySprim(HdSprim *sprim) override;

    virtual HdBprim* CreateBprim(TfToken const& typeId, SdfPath const& bprimId) override;

    virtual HdBprim* CreateFallbackBprim(TfToken const &typeId) override;

    virtual void DestroyBprim(HdBprim *bprim) override;

    virtual void CommitResources(HdChangeTracker *tracker) override;
private:
    std::shared_ptr<filament::Engine> m_engine{};
};

PXR_NAMESPACE_CLOSE_SCOPE