#pragma once

#include <iostream>
#include <pxr/imaging/hd/renderPass.h>
#include "filRenParam.h"

PXR_NAMESPACE_OPEN_SCOPE

class FilRenPass final : public HdRenderPass {
public:
    FilRenPass(HdRenderIndex* index, HdRprimCollection const& collection, FilRenParam* param) : 
        HdRenderPass(index, collection) 
    {
        m_engine = param->GetEngine();
        m_renderer = param->GetRenderer();
        m_scene = param->GetScene();
        m_swapChain = param->GetSwapChain();
        m_view = param->GetView();

        if (!m_engine || !m_renderer || !m_scene || !m_swapChain || !m_view) {
            TF_CODING_ERROR("Missing Filament components");
            std::cout << "[ PASS X ] Missing Filament components\n";
            return;
        }
    }

    ~FilRenPass() = default;

    void _Execute(HdRenderPassStateSharedPtr const& renderPassState, TfTokenVector const& renderTags) override;
private: 
    filament::Engine*    m_engine{};
    filament::Renderer*  m_renderer{};
    filament::Scene*     m_scene{};
    filament::SwapChain* m_swapChain{};
    filament::View*      m_view{};
};

PXR_NAMESPACE_CLOSE_SCOPE