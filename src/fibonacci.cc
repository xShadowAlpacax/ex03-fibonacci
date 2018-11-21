/*                                                                                                          */
/* CS V15 Data Structures and Algorithms                                                                    */
/* CRN: ?????                                                                                               */
/* Assignment: Fibonacci                                                                                    */
/*                                                                                                          */
/* Statement of code ownership: I hereby state that I have written all of this                              */
/* code and I have not copied this code from any other person or source.                                    */
/*                                                                                                          */
/* @author Jack Sherlock                                                                                    */
/*                                                                                                          */


#ifndef EX03_FIBONACCI_FIBONACCI_H
#define EX03_FIBONACCI_FIBONACCI_H
#include <cstdint>
#include <iostream>

namespace edu { namespace vcccd { namespace vc { namespace csv15 {


                uint64_t fibonacci(uint64_t n){
                    if(n==0) return n;
                    if(n==1) return n;

                    uint64_t fib0 = 0;
                    uint64_t fib1 = 1;

                    for(uint64_t k = 2; k <= n; k++){
                        uint64_t next = fib0 + fib1;
                        fib0 = fib1;
                        fib1 = next;
                    }
                    return fib1;
                }

            }}}}

#endif //EX03_FIBONACCI_FIBONACCI_H
