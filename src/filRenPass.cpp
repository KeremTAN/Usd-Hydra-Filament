#include <pxr/imaging/hd/camera.h>
#include <pxr/imaging/hd/renderPassState.h>
#include <pxr/base/gf/vec4d.h>

#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/Viewport.h>
#include <filament/View.h>
#include <filament/Camera.h>
#include <filament/TransformManager.h>
#include <math/mat4.h> // filament::math::mat4f


#include "filRenPass.h"
#include "filRenParam.h"
#include <iostream>

PXR_NAMESPACE_OPEN_SCOPE

FilRenPass::FilRenPass(HdRenderIndex* index, HdRprimCollection const& collection, FilRenParam* param) : 
    HdRenderPass(index, collection),
    m_engine(param->GetEngine()),
    m_renderer(param->GetRenderer()),
    m_scene(param->GetScene()),
    m_swapChain(param->GetSwapChain()),
    m_view(param->GetView()),
    m_camera(param->GetCamera())
{
    if (!m_engine || !m_renderer || !m_scene || !m_swapChain || !m_view  || !m_camera) {
        TF_CODING_ERROR("Missing Filament components");
        std::cout << "[ X PASS ] Missing Filament components\n";
        return;
    }
}

void FilRenPass::_Execute(HdRenderPassStateSharedPtr const& renderPassState, TfTokenVector const& renderTags) {

    if (!renderPassState) {
        std::cout << "[ X PASS _Execute ] Invalid render pass state!\n";
        return;
    }

    std::cout << "[ PASS _Execute ] is working...\n";
    // Viewport'u al ve Filament Viewport'a çevir
    const GfVec4f& vp = renderPassState->GetViewport();
    m_view->setViewport(filament::Viewport(
        static_cast<uint32_t>(vp[0]),
        static_cast<uint32_t>(vp[1]),
        static_cast<uint32_t>(vp[2] + 0.5f),    // +0.5 for avoiding from missing pixel
        static_cast<uint32_t>(vp[3] + 0.5f)));

    // Kamerayı al
    HdCamera const* hdCam { renderPassState->GetCamera() }; //TODO: hdCam type will be converted to FilCamera
    
    if (!hdCam) {
        std::cout << "[ X PASS _Execute ] No camera sprim\n";
        return;
    }

    // Clipping range
    GfRange1f clipRange { hdCam->GetClippingRange() };
    float near { clipRange.GetMin() };
    float far  { clipRange.GetMax() };

    GfMatrix4d gfProj = hdCam->ComputeProjectionMatrix();
    m_camera->setCustomProjection(GfMatrixToFilament(gfProj), near, far);     // Projeksiyonu ve clipping'i ayarla

    // Kamera transformasyonu
    GfMatrix4d gfTransform { hdCam->GetTransform() };
    filament::TransformManager& tcm = m_engine->getTransformManager();
    tcm.setTransform(tcm.getInstance(m_camera->getEntity()), GfMatrixToFilament(gfTransform)); //TODO: get instance may moved to ctor

    // View'a kamerayı bağla
    m_view->setCamera(m_camera);

    if (m_renderer->beginFrame(m_swapChain)) {
        m_renderer->render(m_view);       // sahne & kamera zaten view’de
        m_renderer->endFrame();
    } 
    else {
        std::cout << "[ X PASS _Execute ] beginFrame returned false  swapchain resize?\n";
    }

    std::cout << "[ o PASS _Execute ]\n";
}

/**
 * @brief 
 * matrix of GfMatrix4d is transformed into matrix filament::math::math4 by taking the TRANSPOSE!
 * The reason for that is;
 * GfMatrix4d uses row-major system
 * filament::math::mat4 uses col-major system
 * @param matrix
 * @return filament::math::mat4
 * TODO: for-loop may be optimized in future (OMP or std::parallel)
 */
filament::math::mat4 FilRenPass::GfMatrixToFilament(GfMatrix4d const& matrix) {
    filament::math::mat4 result{};
    
    for (int row{}; row < 4; ++row) {
        for (int col{}; col < 4; ++col) {
            result[col][row] = static_cast<filament::math::mat4::value_type>(matrix[row][col]);
        }
    }
    return result;
}

PXR_NAMESPACE_CLOSE_SCOPE