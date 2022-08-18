#pragma once
#include "Tester.hpp"
#include <optional>
#include <xxhash.h>
#include <Windows.h>
#include <Psapi.h>

class MemoryTest : public ITest{
private:
    const std::string _moduleName;
    const XXH64_hash_t _hash;
    std::optional<MODULEINFO>  getModuleInformation();
    XXH64_hash_t calculateModuleHash();
public:
    MemoryTest(const std::string& testName, const std::string& moduleName, XXH64_hash_t hash);
    bool runTest() override;
};