#pragma once
#include <string>
#include <vector>
#include <memory>

class ITest{
private:
    const std::string _testName;
public:
    virtual bool runTest()=0;
    std::string getTestName() const;
    ITest(const std::string& name) : _testName(name){}
    virtual ~ITest()=default;
};

class Tester{
private:
    std::vector<std::unique_ptr<ITest>> _testCases;
    int _succesfulTests=0;
public:
    Tester& add(ITest* testCase);
    Tester& add(std::unique_ptr<ITest>& testCase);
    bool runAllTests();
    int getTotalTests() const;
    int getSuccessfulTests() const;
};
