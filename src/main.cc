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


#include "fibonacci.h"
#include <time.h>
#include <random>
using namespace edu::vcccd::vc::csv15;
using namespace std;

int main(int argc, char *argv[]){
    srand(time(NULL));
    uint64_t n = rand() % 10 + 1;
    std::cout << "fib(" << n << ") = " << fibonacci(n) << std::endl;
    return fibonacci(n);
}