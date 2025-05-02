#pragma once

#include <iostream>
#include <pxr/imaging/hd/renderPass.h>
#include "filRenParam.h"
#include <math/mat4.h> // filament::math::mat4f

PXR_NAMESPACE_OPEN_SCOPE

class FilRenPass final : public HdRenderPass {
public:
    FilRenPass(HdRenderIndex* index, HdRprimCollection const& collection, FilRenParam* param);

    ~FilRenPass() = default;

    void _Execute(HdRenderPassStateSharedPtr const& renderPassState, TfTokenVector const& renderTags) override;

    filament::math::mat4 GfMatrixToFilament(GfMatrix4d const& matrix);
private: 
    filament::Engine*    m_engine{};
    filament::Renderer*  m_renderer{};
    filament::Scene*     m_scene{};
    filament::SwapChain* m_swapChain{};
    filament::View*      m_view{};
    filament::Camera*    m_camera{};
};

PXR_NAMESPACE_CLOSE_SCOPE