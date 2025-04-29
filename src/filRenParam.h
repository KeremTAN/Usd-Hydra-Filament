#pragma once

#include <pxr/pxr.h>
#include <pxr/imaging/hd/renderDelegate.h>
#include <pxr/imaging/hd/renderThread.h>

#include <filament/Engine.h>
#include <iostream>


PXR_NAMESPACE_OPEN_SCOPE
class FilRenParam final : public HdRenderParam {
    public:
    FilRenParam(filament::Engine* engine, filament::Renderer* renderer,
                filament::Scene* scene, filament::SwapChain* swapChain, filament::View* view) :
        m_engine(engine), m_renderer(renderer), m_scene(scene), m_swapChain(swapChain), m_view(view)
    {
        std::cout << "[ √ FilRenParam is created ]" << '\n';
    }

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

    filament::View* GetView() const {
        return m_view;
    }

private:
    filament::Engine*    m_engine{};
    filament::Renderer*  m_renderer{};
    filament::Scene*     m_scene{};
    filament::SwapChain* m_swapChain{};
    filament::View*      m_view{};

};

PXR_NAMESPACE_CLOSE_SCOPE