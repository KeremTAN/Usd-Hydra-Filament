#include "filCamera.h"


PXR_NAMESPACE_OPEN_SCOPE

FilCamera::FilCamera(SdfPath const& id) : HdCamera(id) {}

void FilCamera::Sync(HdSceneDelegate* sd, HdRenderParam*, HdDirtyBits*) {}

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