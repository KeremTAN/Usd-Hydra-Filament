#include <pxr/imaging/hd/renderPass.h>

PXR_NAMESPACE_OPEN_SCOPE

class FilRenPass final : public HdRenderPass {
public:
    FilRenPass(HdRenderIndex* index, HdRprimCollection const& collection) : 
        HdRenderPass(index, collection) 
    {}

    ~FilRenPass() = default;

    void _Execute(HdRenderPassStateSharedPtr const& renderPassState, TfTokenVector const& renderTags) override;
};

PXR_NAMESPACE_CLOSE_SCOPE