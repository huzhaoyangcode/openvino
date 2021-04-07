// Copyright (C) 2016-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "ocl_common.hpp"
#include "ocl_memory.hpp"
#include "cldnn/runtime/kernel_args.hpp"
#include "cldnn/runtime/kernel.hpp"

#include <memory>
#include <vector>

namespace cldnn {
namespace gpu {

class ocl_kernel : public kernel {
    kernel_type _compiled_kernel;
    std::string _kernel_id;

public:
    ocl_kernel(kernel_type compiled_kernel, const std::string& kernel_id)
        : _compiled_kernel(compiled_kernel)
        , _kernel_id(kernel_id) {
            std::cerr << "CREATE OCL KERNEL: " << compiled_kernel.getInfo<CL_KERNEL_FUNCTION_NAME>() << std::endl;
        }

    const kernel_type& get_handle() const { return _compiled_kernel; }
    std::shared_ptr<kernel> clone() const override { return std::make_shared<ocl_kernel>(get_handle().clone(), _kernel_id); }
};

}  // namespace gpu
}  // namespace cldnn
