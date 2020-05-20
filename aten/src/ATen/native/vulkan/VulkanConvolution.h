#pragma once

#include <ATen/Tensor.h>
#include <ATen/native/vulkan/VulkanCommon.h>
#include <ATen/native/vulkan/VulkanOpContext.h>

namespace at {
namespace native {
namespace vulkan {
namespace detail {
namespace convolution2d {

c10::intrusive_ptr<vulkan::Conv2dOpContext> createConv2dClampPrePackOpContext(
    Tensor weight,
    c10::optional<Tensor> bias,
    std::vector<int64_t> stride,
    std::vector<int64_t> padding,
    std::vector<int64_t> dilation,
    int64_t groups,
    c10::optional<Scalar> output_min,
    c10::optional<Scalar> output_max);

class Conv2dClampRun final : public torch::OperatorKernel {
 public:
  Tensor operator()(
      const Tensor& input,
      const c10::intrusive_ptr<vulkan::Conv2dOpContext>& op_context);
};

ContextConv2D create(
    const Tensor& weight,
    const c10::optional<Tensor>& bias,
    const IntArrayRef padding,
    const IntArrayRef stride,
    const IntArrayRef dilation,
    const int64_t groups,
    const float output_min,
    const float output_max);

Tensor run(const ContextConv2D& context, const Tensor& input);

} // namespace convolution2d
} // namespace detail
} // namespace vulkan
} // namespace native
} // namespace at
