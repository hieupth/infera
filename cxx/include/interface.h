#ifndef __MODEL_INTERFACE_H__
#define __MODEL_INTERFACE_H__

#include <string>
#include <map>
#include <future>
#include <onnxruntime_cxx_api.h>

namespace cinrt::model
{
    class modelInterface {
    public:
        virtual ~modelInterface() = default;
        
        virtual std::shared_ptr<Ort::Value> run(const Ort::Value& inputs, const Ort::RunOptions& runOptions) = 0;
        virtual std::future<std::shared_ptr<Ort::Value>> runAsync(const Ort::Value& inputs, const Ort::RunOptions runOptions) = 0;
    };
}

#endif // __MODEL_INTERFACE_H__