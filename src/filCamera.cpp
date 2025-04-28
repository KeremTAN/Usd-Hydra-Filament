#include "filCamera.h"
#include <pxr/imaging/hd/sceneDelegate.h>


PXR_NAMESPACE_OPEN_SCOPE

FilCamera::FilCamera(SdfPath const& id) : HdCamera(id) {}

void FilCamera::Sync(HdSceneDelegate* sceneDelegate, HdRenderParam* renderParam, HdDirtyBits* dirtyBits) {
    HdCamera::Sync(sceneDelegate, renderParam, dirtyBits);

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