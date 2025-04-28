#pragma once

#include <pxr/imaging/hd/camera.h>

PXR_NAMESPACE_OPEN_SCOPE

class FilCamera final : public HdCamera {
public:
    FilCamera(SdfPath const& id);
    
    void Sync(HdSceneDelegate* sceneDelegate, HdRenderParam* renderParam,
        HdDirtyBits* dirtyBits) override final;

    float GetFStop() const;

    float GetFocalLength() const;

    float GetFocusDistance() const;

    float GetHorizontalAperture() const;
    
    float GetVerticalAperture() const;

private:
    float m_fStop {};
    float m_horizontalAperture { 20.955f };
    float m_verticalAperture { 15.2908f };
    float m_focalLength {};
    float m_focusDistance { 1.f };
};

PXR_NAMESPACE_CLOSE_SCOPE
    