#include <iostream>
# include <format>
# include "bitoperations.h"

int main(){
    std::cout<< "-- TESTING BIT WEIS OPERATIONS __ .\n";

    auto set = 0b00000000;
    std::cout << std::format("original Binary : {:016b}\n", set);
    SB(set,3);
    std::cout << std::format("Binary after SB(VALUE,3) : {:016b}\n", set);
    SB(set,2);
    std::cout << std::format("Binary after SB(VALUE,2): {:016b}\n", set);
    CB(set,2);
    std::cout << std::format("Binary after CB(VALUE,2) : {:016b}\n", set);
    TB(set,0);
    std::cout << std::format("Binary after TB(VALUE,0) : {:016b}\n", set);
    SB(set,15);
    std::cout<< IBS(set,3);
    std::cout << std::format(" = Binary after IBS(VALUE,3) : {:016b}\n", set);
}