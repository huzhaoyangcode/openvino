// Copyright (C) 2018-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <atomic>
#include <cpp/ie_executable_network.hpp>
#include <cpp/ie_infer_request.hpp>
#include <cpp_interfaces/interface/ie_iinfer_request_internal.hpp>
#include <ie_blob.h>
#include <ie_common.h>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace AutoPlugin {

class AutoInferRequest : public InferenceEngine::IInferRequestInternal {
public:
    using Ptr = std::shared_ptr<AutoInferRequest>;
    explicit AutoInferRequest(const InferenceEngine::InputsDataMap&  networkInputs,
                              const InferenceEngine::OutputsDataMap& networkOutputs,
                              const InferenceEngine::InferRequest&   inferRequest);
    std::map<std::string, InferenceEngine::InferenceEngineProfileInfo> GetPerformanceCounts() const override;
    void InferImpl() override;
    void SetBlob(const std::string& name, const InferenceEngine::Blob::Ptr& data) override;
    InferenceEngine::Blob::Ptr GetBlob(const std::string& name) override;
    void Cancel() override;

private:
    InferenceEngine::InferRequest _inferRequest;
};

}  // namespace AutoPlugin
