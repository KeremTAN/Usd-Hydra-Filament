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

void FilRenPass::_Execute(HdRenderPassStateSharedPtr const& renderPassState, TfTokenVector const& renderTags) {

    std::cout << "[ PASS ] _Execute is working...\n";
    // Viewport'u al ve Filament Viewport'a çevir
    const GfVec4f& vp = renderPassState->GetViewport();
    m_view->setViewport(filament::Viewport(vp[0], vp[1], vp[2], vp[3]));

    // Kamerayı al
    HdCamera const* hdCam = renderPassState->GetCamera();
    if (!hdCam) return;


    // Clipping range
    GfRange1f clipRange = hdCam->GetClippingRange();
    float near  = clipRange.GetMin();
    float far   = clipRange.GetMax();



    GfMatrix4d gfProj = hdCam->ComputeProjectionMatrix();     // Projeksiyon matrisini hesapla TODO: transpoz gerekebilir
    m_camera->setCustomProjection(GfMatrixToFilament(gfProj), near, far);     // Projeksiyonu ve clipping'i ayarla

    // Kamera transformasyonu
    GfMatrix4d gfTransform = hdCam->GetTransform();
    filament::math::mat4 filTransform = GfMatrixToFilament(gfTransform);
    filament::TransformManager& tcm = m_engine->getTransformManager();
    tcm.setTransform(tcm.getInstance(m_camera->getEntity()), filTransform);

    // View'a kamerayı bağla
    m_view->setCamera(m_camera);

    std::cout << "[ √ PASS ]\n";
}

filament::math::mat4 FilRenPass::GfMatrixToFilament(GfMatrix4d const& m) { //TODO: matris dönüşümü doğru mu kontrol et
    return filament::math::mat4(*reinterpret_cast<const filament::math::mat4::value_type*>(m.data()));
}

PXR_NAMESPACE_CLOSE_SCOPE