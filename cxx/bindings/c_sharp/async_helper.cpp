#include "async_helper.h"
#include <core.h>

namespace cinrt { 
namespace model {

std::future<std::shared_ptr<std::vector<Ort::Value>>> runModelAsync(
    std::shared_ptr<cinrt::model::Model> model,
    const Ort::Value& input,
    std::shared_ptr<const char*> outputNames,
    Ort::RunOptions runOptions
) {
    return model->runAsync(input, outputNames, std::move(runOptions));
}

} // namespace model
} // namespace cinrt