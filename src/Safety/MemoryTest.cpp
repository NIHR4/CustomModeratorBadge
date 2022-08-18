#include "MemoryTest.hpp"
#include <memory>
#include <TlHelp32.h>
#include <spdlog/spdlog.h>



std::optional<MODULEINFO> MemoryTest::getModuleInformation(){
    HMODULE moduleHandle = GetModuleHandleA(_moduleName.c_str());
    if(moduleHandle == NULL){
        spdlog::error("Call to GetModuleHandle failed. Error code {}", GetLastError());
        return std::nullopt;
    }
    MODULEINFO moduleInfo;
    if(GetModuleInformation(GetCurrentProcess(), moduleHandle, &moduleInfo, sizeof(MODULEINFO)) == 0){
        spdlog::error("Call to GetCurrentProcess failed. Error code {}", GetLastError());
        return std::nullopt;
    }
    return moduleInfo;
}


XXH64_hash_t MemoryTest::calculateModuleHash(){
    XXH64_state_t* state = XXH64_createState();
    if(state == NULL){
        spdlog::error("XXH64_createState() was null");
        return 0;
    }
    
    if(XXH64_reset(state, 0) == XXH_ERROR){
        spdlog::error("XXH64_reset() returned XXH_ERROR");
        XXH64_freeState(state);
        return 0;
    }
    
    constexpr uint32_t bufferSlice = 4096u;
    auto moduleInfo = getModuleInformation();
    
    if(!moduleInfo.has_value()) {
        XXH64_freeState(state);
        return 0;
    }
    
    DWORD remainingBytes = moduleInfo->SizeOfImage;
    VOID* readAddr= moduleInfo->lpBaseOfDll;
    while(remainingBytes > 0){
        uint32_t bufSize = remainingBytes > bufferSlice
            ? bufferSlice
            : remainingBytes;
        remainingBytes -= bufferSlice;
        std::unique_ptr<char[]> buffer = std::make_unique<char[]>(bufSize);
        std::memcpy(buffer.get(), readAddr, bufSize);
        *reinterpret_cast<DWORD*>(&readAddr) += bufSize;
    };
    XXH64_hash_t hashResult = XXH64_digest(state);
    XXH64_freeState(state);
    return hashResult;
}

bool MemoryTest::runTest(){
    auto calculatedHash = calculateModuleHash();
    if(calculatedHash ==0) return false;
    spdlog::info("Hash for module '{0}' was '{1:x}'. The expected hash is '{2:x}'", _moduleName, calculatedHash, _hash);
    return calculatedHash == _hash;
}


MemoryTest::MemoryTest(const std::string& testName, const std::string& moduleName, XXH64_hash_t hash) : ITest(testName), _moduleName(moduleName), _hash(hash){};
