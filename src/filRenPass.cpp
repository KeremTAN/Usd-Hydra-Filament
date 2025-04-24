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

    // std::cout << "Execute called for render pass, primitive count: " << GetRprimIDs().size() << std::endl;

    FilRenParam* renderParam = static_cast<FilRenParam*>(GetRenderIndex()->GetRenderDelegate()->GetRenderParam());

    if (!renderParam) {
        TF_CODING_ERROR("Failed to get FilRenParam");
        std::cout << "[ PASS X ] Failed to get FilRenParam\n";
        return;
    }

    filament::Engine*    engine    = const_cast<filament::Engine*>(renderParam->GetEngine());
    filament::Renderer*  renderer  = const_cast<filament::Renderer*>(renderParam->GetRenderer());
    filament::Scene*     scene     = const_cast<filament::Scene*>(renderParam->GetScene());
    filament::SwapChain* swapChain = renderParam->GetSwapChain();

    if (!engine || !renderer || !scene || !swapChain) {
        TF_CODING_ERROR("Missing Filament components");
        std::cout << "[ PASS X ] Missing Filament components\n";
        return;
    }

    // Base of render loop
    if (renderer->beginFrame(swapChain)) {
        // TODO: in the future, take viewport directly 
        uint32_t width = 800;
        uint32_t height = 600;
        
        // Render hedefini temizleme
        renderer->setClearOptions({
            .clearColor = {0.0f, 0.1f, 0.2f, 1.0f},
            .clear = true
        });
        
        filament::View* view = engine->createView();
        filament::Viewport viewport(0, 0, width, height);
        view->setViewport(viewport);
        view->setScene(scene);
        
        renderer->render(view);
        
        engine->destroy(view);
        
        renderer->endFrame();
    }

    std::cout << "[ PASS √ ]\n";
}

PXR_NAMESPACE_CLOSE_SCOPE