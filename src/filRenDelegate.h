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
    /**
     * delete ptr is not healty way to deallocate Filament eng.
     * Therefore, custom deleter is defined while shared_ptr is used
     */
    FilRenDelegate() :
        m_recourcesRegistry(std::make_shared<HdResourceRegistry>()),
        m_engine(filament::Engine::create(filament::Engine::Backend::METAL),
            [](filament::Engine* e) { 
                filament::Engine::destroy(&e);
            }
        ), // end of m_engine
        m_renderer(m_engine->createRenderer(),
            [eng = m_engine.get()](filament::Renderer* r){
                eng->destroy(r);
            }
        ), // end of m_renderer
        m_scene(m_engine->createScene(),
            [eng = m_engine.get()](filament::Scene* s){
                eng->destroy(s);
            }
        ), // end of m_scene
        m_swapChain(m_engine->createSwapChain(nullptr), // native window pointer
            [eng = m_engine.get()](filament::SwapChain* sc){
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

    ~FilRenDelegate() {
        m_renderParam.reset();
        m_scene.reset();
        m_renderer.reset();
        m_engine.reset();
    };

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
    
    TfTokenVector                       m_rPrimTypes{};
    TfTokenVector                       m_sPrimTypes{};
    TfTokenVector                       m_bPrimTypes{};
    std::shared_ptr<FilRenParam>        m_renderParam{};
    HdResourceRegistrySharedPtr         m_recourcesRegistry{};
};

PXR_NAMESPACE_CLOSE_SCOPE