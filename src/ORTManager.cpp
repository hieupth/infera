#include "ORTManager.h"
#include "ORTSession.h"

ORTManager::ORTManager() {}
ORTManager::~ORTManager() {}

void ORTManager::createSession(
    const std::string& sessionName, 
    const std::string& modelPath,
    int optimizerLevel,
    const std::string& optimizerPath,
    const std::string& runModel,
    int numThreads = 0) {
    
    // check if session already exists
    if (sessions.find(sessionName) != sessions.end()) {
        throw std::runtime_error("Session already exists");
        return;
    }

    std::unique_ptr<ORTSessionInterface> session = std::make_unique<ORTSession>();
    session->loadModel(modelPath, optimizerLevel, optimizerPath, runModel, numThreads);
    sessions[sessionName] = std::move(session);
}

void ORTManager::deleteSession(const std::string& sessionName) {
    // check if session exists
    auto it = sessions.find(sessionName);
    if (it == sessions.end()) {
        throw std::runtime_error("Session does not exist");
        return;
    } else {
        sessions.erase(it);
    }
}

void ORTManager::run(
    const std::string& sessionName,
    const Ort::Value& input,
    Ort::Value& output,
    int numThreads = 0,
    std::string runType) {
    
    // check if session exists
    auto it = sessions.find(sessionName);
    if (it == sessions.end()) {
        throw std::runtime_error("Session does not exist");
        return;
    } else {
        if (runType == "run") {
            it->second->run(input, output, sessionName);
        } else if (runType == "async") {
            it->second->runAsync(input, output, sessionName);
        } else {
            throw std::runtime_error("Invalid run type");
        }
    }
}