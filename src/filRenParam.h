#pragma once

#include <pxr/pxr.h>
#include <pxr/imaging/hd/renderDelegate.h>
#include <pxr/imaging/hd/renderThread.h>


PXR_NAMESPACE_OPEN_SCOPE

class FilamentRenderParam final : public HdRenderParam {
    public:
    FilamentRenderParam(filament::Engine* engine, filament::Renderer* renderer, filament::Scene* scene)
        : m_engine(engine), m_renderer(renderer), m_scene(scene)
    {}

    ~FilamentRenderParam() = default;

   
    filament::Engine& GetEngine() const {
        return *m_engine;
    }


    filament::Renderer& GetRenderer() const {
        return *m_renderer;
    }


    filament::Scene& GetScene() const {
        return *m_scene;
    }

private:
    filament::Engine*   m_engine{};
    filament::Renderer* m_renderer{};
    filament::Scene*    m_scene{};

};

PXR_NAMESPACE_CLOSE_SCOPE