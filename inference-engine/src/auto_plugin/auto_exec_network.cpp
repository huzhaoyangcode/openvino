// Copyright (C) 2018-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>

#include "ie_metric_helpers.hpp"
#include "auto_exec_network.hpp"
#include "auto_infer_request.hpp"

namespace AutoPlugin {
    using namespace InferenceEngine;

AutoExecutableNetwork::AutoExecutableNetwork(const ExecutableNetwork& network,
                                             const DeviceInformation& deviceInfo,
                                             const bool               needPerfCounters) :
    _deviceInfo(deviceInfo),
    _network(network),
    _config(deviceInfo.config.begin(), deviceInfo.config.end()),
    _needPerfCounters(needPerfCounters) {
}

AutoExecutableNetwork::~AutoExecutableNetwork() = default;

IInferRequestInternal::Ptr AutoExecutableNetwork::CreateInferRequestImpl(InputsDataMap networkInputs,
                                                                         OutputsDataMap networkOutputs) {
    auto inferRequest = _network.CreateInferRequest();
    return std::make_shared<AutoInferRequest>(networkInputs, networkOutputs, inferRequest);
}

void AutoExecutableNetwork::Export(std::ostream& networkModel) {
    _network.Export(networkModel);
}

RemoteContext::Ptr AutoExecutableNetwork::GetContext() const {
  return _network.GetContext();
}

InferenceEngine::CNNNetwork AutoExecutableNetwork::GetExecGraphInfo() {
    return _network.GetExecGraphInfo();
}

Parameter AutoExecutableNetwork::GetMetric(const std::string &name) const {
    return _network.GetMetric(name);
}

void AutoExecutableNetwork::SetConfig(const std::map<std::string, Parameter>& config) {
    _network.SetConfig(config);
}

Parameter AutoExecutableNetwork::GetConfig(const std::string& name) const {
    return _network.GetConfig(name);
}

}  // namespace AutoPlugin
