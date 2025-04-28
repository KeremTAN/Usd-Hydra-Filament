#pragma once

#include <pxr/pxr.h>
#include <pxr/imaging/hd/tokens.h>
#include <pxr/imaging/hd/extComputation.h>
#include <pxr/imaging/hd/resourceRegistry.h>
#include <pxr/imaging/hd/camera.h>
#include <pxr/imaging/hd/renderDelegate.h>

#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>

#include "filRenParam.h"
#include <iostream>

PXR_NAMESPACE_OPEN_SCOPE

class FilRenDelegate final : public HdRenderDelegate {
public:
    FilRenDelegate();
    ~FilRenDelegate() override;

    const TfTokenVector& GetSupportedRprimTypes() const override;
    const TfTokenVector& GetSupportedSprimTypes() const override;
    const TfTokenVector& GetSupportedBprimTypes() const override;

    HdRenderParam* GetRenderParam() const override;

    HdResourceRegistrySharedPtr GetResourceRegistry() const override;

    HdRenderPassSharedPtr CreateRenderPass(HdRenderIndex* index, HdRprimCollection const& collection) override;

    HdInstancer* CreateInstancer(HdSceneDelegate* delegate, SdfPath const& instancerId) override;

    void DestroyInstancer(HdInstancer* instancer) override;
    
    HdRprim* CreateRprim(TfToken const& typeId, SdfPath const& rprimId) override;
    
    void DestroyRprim(HdRprim* rPrim) override;
    
    HdSprim* CreateSprim(TfToken const& typeId, SdfPath const& sprimId) override;

    HdSprim* CreateFallbackSprim(TfToken const& typeId) override;

    void DestroySprim(HdSprim* sPrim) override;

    HdBprim* CreateBprim(TfToken const& typeId, SdfPath const& bprimId) override;

    HdBprim* CreateFallbackBprim(TfToken const& typeId) override;

    void DestroyBprim(HdBprim* bPrim) override;

    void CommitResources(HdChangeTracker* tracker) override;

private:
    std::shared_ptr<filament::Engine>    m_engine{};
    std::shared_ptr<filament::Renderer>  m_renderer{};
    std::shared_ptr<filament::Scene>     m_scene{};
    std::shared_ptr<filament::SwapChain> m_swapChain{};
    
    //TODO: check, does location of primTypes at stack on memory is fine or should they moved to static area
    TfTokenVector                       m_rPrimTypes{};
    TfTokenVector                       m_sPrimTypes{};
    TfTokenVector                       m_bPrimTypes{};
    std::shared_ptr<FilRenParam>        m_renderParam{};
    HdResourceRegistrySharedPtr         m_resourcesRegistry{};
};

PXR_NAMESPACE_CLOSE_SCOPE