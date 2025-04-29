#include <pxr/imaging/hd/renderPassState.h>
#include <pxr/base/gf/vec4d.h>

#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/Viewport.h>
#include <filament/View.h>


#include "filRenPass.h"
#include "filRenParam.h"
#include <iostream>

PXR_NAMESPACE_OPEN_SCOPE

void FilRenPass::_Execute(HdRenderPassStateSharedPtr const& renderPassState, TfTokenVector const& renderTags) {

    std::cout << "[ PASS ] _Execute is working...\n";

    // Base of render loop
    if (m_renderer->beginFrame(m_swapChain)) {
        // TODO: in the future, take viewport directly 
        uint32_t width = 800;
        uint32_t height = 600;
        
        // Render hedefini temizleme
        m_renderer->setClearOptions({
            .clearColor = {0.0f, 0.1f, 0.2f, 1.0f},
            .clear = true
        });
        
        filament::Viewport viewport(0, 0, width, height);
        m_view->setViewport(viewport);
        m_view->setScene(m_scene);
        
        m_renderer->render(m_view);
        
        m_engine->destroy(m_view);
        
        m_renderer->endFrame();
    }

    std::cout << "[ √ PASS ]\n";
}

PXR_NAMESPACE_CLOSE_SCOPE