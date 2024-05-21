#pragma once

#include <string>
#include <ORTSessionInterface.h>
#include <onnxruntime_cxx_api.h>

class ORTSession : public ORTSessionInterface{
private:
    Ort::Env env;
    Ort::Session* session;
    Ort::SessionOptions sessionOptions;
    std::string modelPath;
    std::string optimizerPath;
    Ort::RunOptions runOptions;
    int optimizerLevel;
public:
    ORTSession();
    ~ORTSession();
    void loadModel(
        const std::string modelPath, 
        int& optimizerLevel, 
        const std::string optimizerPath, 
        const std::string runModel,
        int numThreads) override;
    void run(
        const Ort::Value& input, 
        Ort::Value& output,
        std::string runName) override;
    void runAsync(
        const Ort::Value& input, 
        Ort::Value& output, 
        std::string runName) override;
};