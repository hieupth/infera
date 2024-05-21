#pragma once

#include "ORTSessionInterface.h"
#include <map>
#include <string>
#include <memory>

class ORTManager {
    private:
        std::map<std::string, std::unique_ptr<ORTSessionInterface>> sessions;
    public:
        ORTManager();
        ~ORTManager();
        void createSession(
            const std::string& sessionName, 
            const std::string& modelPath,
            int optimizerLevel,
            const std::string& optimizerPath,
            const std::string& runModel,
            int numThreads);
        void deleteSession(const std::string& sessionName);
        void run(
            const std::string& sessionName,
            const Ort::Value& input,
            Ort::Value& output,
            int numThreads,
            std::string runType);
};