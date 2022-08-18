#include "Tester.hpp"
#include <algorithm>

std::string ITest::getTestName() const{
    return _testName;
}

Tester& Tester::add(ITest* testCase){
    _testCases.emplace_back(testCase);
    return *this;
}

Tester& Tester::add(std::unique_ptr<ITest>& testCase){
    _testCases.push_back(std::move(testCase));
    return *this;
}

bool Tester::runAllTests(){
    _succesfulTests=std::count_if(
                    _testCases.begin(), 
                    _testCases.end(), 
                    [](std::unique_ptr<ITest>& test){return test->runTest();}
                );
    return _succesfulTests == _testCases.size();
}

int Tester::getTotalTests() const{
    return _testCases.size();
}

int Tester::getSuccessfulTests() const{
    return _succesfulTests;
}