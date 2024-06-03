#include <iostream>
#include "core.h"
#include "serviceManager.h"
#include <onnxruntime_cxx_api.h>
#include <chrono>
#include <thread>

using namespace cinrt::model;

Ort::Value createMockInput(Ort::MemoryInfo& memoryInfo, int64_t batchSize = 1, int64_t channels = 9, int64_t height = 256, int64_t width = 256) {
    // const std::array<int64_t, 4> inputShape = {1, 9, 256, 256};
    // std::vector<float> inputValues(1 * 9 * 256 * 256, 1.0f);
    const std::array<int64_t, 4> inputShape = {batchSize, channels, height, width};
    std::vector<float> inputValues(batchSize * channels * height * width, 1.0f);
    return Ort::Value::CreateTensor<float>(memoryInfo, inputValues.data(), inputValues.size(), inputShape.data(), inputShape.size());
}

int main() {
    std::shared_ptr<Ort::Env> env = std::make_shared<Ort::Env>(ORT_LOGGING_LEVEL_WARNING, "test");
    // std::shared_ptr<Ort::Allocator> allocator = std::make_shared<Ort::AllocatorWithDefaultOptions>();

    serviceManager manager(env);

    // Create and test model
    std::string modelPath1 = "../models/test_wb.onnx";
    std::string modelPath2 = "../models/yolov7-headface-v1.onnx";
    Model* model = manager.createModel(modelPath1);
    Model* model2 = manager.createModel(modelPath2);
    
    Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    Ort::Value inputTensor1 = createMockInput(memoryInfo , 1, 9, 256, 256);
    Ort::Value inputTensor2 = createMockInput(memoryInfo, 1, 3, 640, 640);

    
    try {
        std::shared_ptr<std::vector<Ort::Value>> outputTensor1 = model->run(inputTensor1);
        float* outputData1 = outputTensor1->at(0).GetTensorMutableData<float>();
        std::cout << "Model output: " << outputData1[0] << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    // Test session clock update and retrieval
    manager.updateSessionClock(modelPath1);
    float sessionDuration = manager.getSessionClock(modelPath1);
    std::cout << "Initial session duration: " << sessionDuration << " seconds" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2)); // wait for 2 seconds

    sessionDuration = manager.getSessionClock(modelPath1);
    std::cout << "Session duration after 2 seconds: " << sessionDuration << " seconds" << std::endl;

    // Start garbage collection and let it run for a short while
    // manager.startGC();
    int Time = 5;
    std::this_thread::sleep_for(std::chrono::seconds(Time)); // simulate some time passing
    std::cout << "After " << Time << " seconds, start garbage collection" << std::endl;

    // Stop garbage collection and join thread
    manager.stopGC();
    std::cout << "Garbage collector stopped." << std::endl;

    return 0;
}