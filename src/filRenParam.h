#pragma once

#include <pxr/pxr.h>
#include <pxr/imaging/hd/renderDelegate.h>
#include <pxr/imaging/hd/renderThread.h>

#include <filament/Engine.h>


PXR_NAMESPACE_OPEN_SCOPE
class FilRenParam final : public HdRenderParam {
    public:
    FilRenParam(filament::Engine* engine, filament::Renderer* renderer,
        filament::Scene* scene, filament::SwapChain* swapChain) :
        m_engine(engine), m_renderer(renderer), m_scene(scene), m_swapChain(swapChain)
    {}

    ~FilRenParam() = default;
   
    filament::Engine* GetEngine() const {
        return m_engine;
    }

    filament::Renderer* GetRenderer() const {
        return m_renderer;
    }

    filament::Scene* GetScene() const {
        return m_scene;
    }

    filament::SwapChain* GetSwapChain() const {
        return m_swapChain;
    }

private:
    filament::Engine*   m_engine{};
    filament::Renderer* m_renderer{};
    filament::Scene*    m_scene{};
    filament::SwapChain* m_swapChain{};
};

PXR_NAMESPACE_CLOSE_SCOPE