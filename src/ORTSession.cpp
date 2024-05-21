#include <iostream>
#include <thread>
#include "ORTSession.h"


ORTSession::ORTSession() : env(ORT_LOGGING_LEVEL_WARNING, "ORTSession"), session(nullptr), optimizerLevel(0) {}

ORTSession::~ORTSession() {
    if (session != nullptr) {
        delete session;
    }
}

void ORTSession::loadModel(
    const std::string modelPath, 
    int& optimizerLevel, 
    const std::string optimizerPath,
    const std::string runModel,
    int numThreads = 0) {
    switch (optimizerLevel)
    {
    case 0:
        sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_DISABLE_ALL);
        break;
    case 1:
        sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_BASIC);
        break;
    case 2:
        sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);
        break;
    case 3:
        sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
        break;
    default:
        break;
    }
    if (!optimizerPath.empty()) {
        sessionOptions.SetOptimizedModelFilePath(optimizerPath.c_str());
    }
    if (runModel == "async") {
        sessionOptions.SetExecutionMode(ExecutionMode::ORT_PARALLEL);
    }
    else if (runModel == "run") {
        sessionOptions.SetExecutionMode(ExecutionMode::ORT_SEQUENTIAL);
    }
    if (numThreads == 0) {
        const int numThreads = std::thread::hardware_concurrency();
    }
    else {
        const int numThreads = numThreads;
    }
}


void ORTSession::run(
    const Ort::Value& input, 
    Ort::Value& output, 
    std::string runName) {
    Ort::AllocatorWithDefaultOptions ort_alloc;
    Ort::AllocatedStringPtr inputName = session->GetInputNameAllocated(0, ort_alloc);
    Ort::AllocatedStringPtr outputName = session->GetOutputNameAllocated(0, ort_alloc);
    const std::array<const char*, 1> inputNames = {inputName.get()};
    const std::array<const char*, 1> outputNames = {outputName.get()};
    // loadModel(modelPath, optimizerLevel, optimizerPath, "run");
    session = new Ort::Session(env, modelPath.c_str(), sessionOptions);
    try {
        session->Run(runOptions, inputNames.data(), &input, 1, outputNames.data(), &output, 1);
    }
    catch (Ort::Exception& exception) {
        std::cout << "Error: " << exception.what() << std::endl;
    }
}

void ORTSession::runAsync(
    const Ort::Value& input, 
    Ort::Value& output, 
    std::string runName) {
    // loadModel(modelPath, optimizerLevel, optimizerPath, "async");
    runOptions.SetRunTag(runName.c_str());
    session = new Ort::Session(env, modelPath.c_str(), sessionOptions);
    Ort::AllocatorWithDefaultOptions ort_alloc;
    Ort::AllocatedStringPtr inputName = session->GetInputNameAllocated(0, ort_alloc);
    Ort::AllocatedStringPtr outputName = session->GetOutputNameAllocated(0, ort_alloc);
    const std::array<const char*, 1> inputNames = {inputName.get()};
    const std::array<const char*, 1> outputNames = {outputName.get()};
    try {
        session->Run(runOptions, inputNames.data(), &input, 1, outputNames.data(), &output, 1);
    }
    catch (Ort::Exception& exception) {
        std::cout << "Error: " << exception.what() << std::endl;
    }
}
    