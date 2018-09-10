// Copyright 2018, Allan Knight.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Allan Knight nor the names of other
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A unit tester for EX05-String in CS140 at Santa Barbara City College.
//
// Author: ahknight@pipeline.sbcc.edu (Allan Knight)


// Includes for google test and the unit under test.

#include <climits>
#include <sstream>

#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>

#include "fibonacci.h"
#include "gtest/gtest.h"
namespace {

// Tests edu::sbcc:cs140::String.

    using edu::sbcc::cs140::FibonacciSolver;
    using edu::sbcc::cs140::RecursiveFibonacciSolver;
    using edu::sbcc::cs140::DynamicFibonacciSolver;
#ifdef SUPPORTS_CLOSED_FORM
    using edu::sbcc::cs140::ClosedFormFibonacciSolver;
#endif

#ifdef SUPPORTS_ITERATIVE
    using edu::sbcc::cs140::IterativeFibonacciSolver;
#endif

    using std::chrono::system_clock;
    using std::chrono::microseconds;
    using std::chrono::duration_cast;

    static constexpr uint32_t TEST_ITERATIONS = 1000;
    static constexpr uint32_t FIBONACCI_NUMBER = 44;

    using std::istringstream;
    using std::ostringstream;
    using std::string;

    using namespace ::testing_internal;

    template <typename T>
    uint64_t measureExecTime(const std::function<void(void)> &measured) {
        system_clock::time_point start = system_clock::now();
        measured();
        system_clock::time_point stop = system_clock::now();
        T elapsed = duration_cast<T>(stop - start);
        return elapsed.count();
    }

    class FibonacciTest : public ::testing::Test {
    protected:
        static const uint MAX_TESTED_SCORE = 20;
        static const uint MAX_OVERALL_SCORE = 25;
        static uint _testScore;

    protected:
        static void TearDownTestCase() {
            if (_testScore == MAX_TESTED_SCORE) {
                std::cout << std::endl << "Your unit test score is "
                          << _testScore << " out of "
                          << MAX_TESTED_SCORE << std::endl;
            } else {
                std::cout << "Your unit test score is "
                          << _testScore << " out of "
                          << MAX_TESTED_SCORE << " ("<< (int)(_testScore - MAX_TESTED_SCORE)
                          << ")" << std::endl;
            }

            std::cout << "The assignment is worth a total of " << MAX_OVERALL_SCORE
                      << " where the remaining points" << std::endl;
            std::cout << "comes from grading related to documentation, algorithms, and other"
                      << std::endl;
            std::cout << "criteria." << std::endl << std::endl;
        }
    };

    uint FibonacciTest::_testScore = 0;

    TEST_F(FibonacciTest, Recursive) {
        // This test is named "Identity", it checks that the basic identity
        // complex number, i, has the correct values for real and imaginary
        // parts.
        RecursiveFibonacciSolver recursive;
        ASSERT_EQ(0, recursive(0));
        ASSERT_EQ(1, recursive(1));
        ASSERT_EQ(1, recursive(2));
        ASSERT_EQ(2, recursive(3));
        ASSERT_EQ(13, recursive(7));
        ASSERT_EQ(832040, recursive(30));

        _testScore += 10;
    }

    TEST_F(FibonacciTest, Dynamic) {
        // This test is named "Identity", it checks that the basic identity
        // complex number, i, has the correct values for real and imaginary
        // parts.
        DynamicFibonacciSolver dynamic;
        ASSERT_EQ(0, dynamic(0));
        ASSERT_EQ(1, dynamic(1));
        ASSERT_EQ(1, dynamic(2));
        ASSERT_EQ(2, dynamic(3));
        ASSERT_EQ(13, dynamic(7));
        ASSERT_EQ(832040, dynamic(30));

        _testScore += 10;
    }

#ifdef SUPPORTS_CLOSED_FORM
    TEST_F(FibonacciTest, ClosedForm) {
        // This test is named "Identity", it checks that the basic identity
        // complex number, i, has the correct values for real and imaginary
        // parts.
        ClosedFormFibonacciSolver closedFrom;
        ASSERT_EQ(0, closedFrom(0));
        ASSERT_EQ(1, closedFrom(1));
        ASSERT_EQ(1, closedFrom(2));
        ASSERT_EQ(2, closedFrom(3));
        ASSERT_EQ(13, closedFrom(7));
        ASSERT_EQ(832040, closedFrom(30));

        _testScore += 2;
    }
#endif

#ifdef SUPPORTS_ITERATIVE
    TEST_F(FibonacciTest, Iterative) {
        // This test is named "Identity", it checks that the basic identity
        // complex number, i, has the correct values for real and imaginary
        // parts.
        IterativeFibonacciSolver iterative;
        ASSERT_EQ(0, iterative(0));
        ASSERT_EQ(1, iterative(1));
        ASSERT_EQ(1, iterative(2));
        ASSERT_EQ(2, iterative(3));
        ASSERT_EQ(13, iterative(7));
        ASSERT_EQ(832040, iterative(30));

        _testScore += 3;
    }
#endif

    TEST_F(FibonacciTest, Timing) {
        static FibonacciSolver *solvers[] = {
                new RecursiveFibonacciSolver,
                new DynamicFibonacciSolver,
#ifdef SUPPORTS_CLOSED_FORM
                new ClosedFormFibonacciSolver,
#endif

#ifdef SUPPORTS_ITERATIVE
                new IterativeFibonacciSolver,
#endif
        };

        auto time = measureExecTime<microseconds>([&]() {
            (*solvers[0])(FIBONACCI_NUMBER);
        });
        std::cout << "Elapsed time: " << time << " us (" << solvers[0]->getName() << ")" << std::endl;

        for (uint32_t i = 1; i < sizeof(solvers) / sizeof(solvers[0]); i++) {
            FibonacciSolver &solver = *solvers[i];
            auto elapsed = measureExecTime<microseconds>([&]() {
                for (uint j = 1; j < TEST_ITERATIONS; j++) {
                    solver(FIBONACCI_NUMBER);
                }
            });
            std::cout << "Elapsed time: " << elapsed << " us (" << solver.getName() << ")" << std::endl;
        }
    }
}