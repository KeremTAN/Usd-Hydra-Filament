#include "filCamera.h"
#include <pxr/imaging/hd/sceneDelegate.h>


PXR_NAMESPACE_OPEN_SCOPE

FilCamera::FilCamera(SdfPath const& id) : HdCamera(id) {
  std::cout << "[ o Camera Ctor ] created successfully\n";
}

void FilCamera::Sync(HdSceneDelegate* sceneDelegate, HdRenderParam* renderParam, HdDirtyBits* dirtyBits) {
    HdCamera::Sync(sceneDelegate, renderParam, dirtyBits);

    const auto filRenParam { static_cast<FilRenParam*>(renderParam) };

    if(!m_camera.get()) {
      auto engine = filRenParam->GetEngine();
      m_cameraEntity = utils::EntityManager::get().create();
      m_camera = std::shared_ptr<filament::Camera>(
          engine->createCamera(m_cameraEntity),
          [engine, ce = m_cameraEntity](filament::Camera* camera) noexcept {
              if (camera && !ce.isNull()) {
                  engine->destroyCameraComponent(ce);
                  utils::EntityManager::get().destroy(ce);
              }
          }
      );
      
      filRenParam->SetCamera(m_camera.get());
    }

    const VtValue& fStop { sceneDelegate->GetCameraParamValue(GetId(), HdCameraTokens->fStop) };

    const VtValue& horizontalAperture { sceneDelegate->GetCameraParamValue(GetId(), HdCameraTokens->horizontalAperture) };

    const VtValue& verticalAperture { sceneDelegate->GetCameraParamValue(GetId(), HdCameraTokens->verticalAperture) };

    const VtValue& focusDistance { sceneDelegate->GetCameraParamValue(GetId(), HdCameraTokens->focusDistance) };

    const VtValue& focalLength { sceneDelegate->GetCameraParamValue(GetId(), HdCameraTokens->focalLength) };

    if (fStop.IsHolding<float>())
        m_fStop = fStop.Get<float>();

    if (horizontalAperture.IsHolding<float>())
        m_horizontalAperture = horizontalAperture.Get<float>();

    if (verticalAperture.IsHolding<float>())
        m_verticalAperture = verticalAperture.Get<float>();
        
    if (focalLength.IsHolding<float>())
        m_focalLength = focalLength.Get<float>();

    if (focusDistance.IsHolding<float>())
        m_focusDistance = focusDistance.Get<float>();
}

float FilCamera::GetFStop() const {
  return m_fStop;
}

float FilCamera::GetFocalLength() const {
  return m_focalLength;
}

float FilCamera::GetFocusDistance() const {
  return m_focusDistance;
}

float FilCamera::GetHorizontalAperture() const {
  return m_horizontalAperture;
}

float FilCamera::GetVerticalAperture() const {
  return m_verticalAperture;
}

PXR_NAMESPACE_CLOSE_SCOPE