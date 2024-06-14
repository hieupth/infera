#ifndef CINRT_ASYNC_HELPER_H
#define CINRT_ASYNC_HELPER_H

#include <future>
#include <memory>
#include <vector>
#include <onnxruntime_cxx_api.h>
#include <core.h>

namespace cinrt { 
namespace model {

std::future<std::shared_ptr<std::vector<Ort::Value>>> runModelAsync(
    std::shared_ptr<cinrt::model::Model> model,
    const Ort::Value& input,
    std::shared_ptr<const char*> outputNames,
    Ort::RunOptions runOptions = Ort::RunOptions()
);

} // namespace model
} // namespace cinrt

#endif // CINRT_ASYNC_HELPER_H