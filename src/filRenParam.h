#pragma once


#include <pxr/imaging/hd/renderDelegate.h>
#include <filament/View.h>
#include <iostream>


PXR_NAMESPACE_OPEN_SCOPE
class FilRenParam final : public HdRenderParam {
public:
    FilRenParam(filament::Engine* engine, filament::Renderer* renderer, filament::Scene* scene,
        filament::SwapChain* swapChain, filament::View* view) :
        m_engine(engine), m_renderer(renderer), m_scene(scene),
        m_swapChain(swapChain), m_view(view)
    {
        std::cout << "[ o Param Ctor ] created successfully\n";
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

    void SetCamera(filament::Camera* camera) {
        if(camera) {
            m_camera = camera;

            if (m_view) 
                m_view->setCamera(m_camera);
        }
    }

    filament::Camera* GetCamera() const {
        return m_camera;
    }

private:
    filament::Engine*    m_engine{};
    filament::Renderer*  m_renderer{};
    filament::Scene*     m_scene{};
    filament::SwapChain* m_swapChain{};
    filament::View*      m_view{};
    filament::Camera*    m_camera{};
};

PXR_NAMESPACE_CLOSE_SCOPE