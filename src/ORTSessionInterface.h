#pragma once

#include <string>
#include <vector>
#include <onnxruntime_cxx_api.h>

class ORTSessionInterface {
    public:
        virtual ~ORTSessionInterface() = default;
        virtual void loadModel(
            const std::string modelPath, 
            int& optimizerLevel, 
            const std::string optimizerPath, 
            const std::string runModel,
            int numThreads) = 0;
        virtual void run(
            const Ort::Value& input, 
            Ort::Value& output,
            std::string runName) = 0;
        virtual void runAsync(
            const Ort::Value& input, 
            Ort::Value& output,
            std::string runName) = 0;
};
