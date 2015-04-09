#include <stdint.h>
#include <iostream>

int32_t count_val(const int32_t val) {
    int32_t v = val;
    ++v;
    return v;
}

int32_t main(int32_t argc,const char** argv) {
    uint32_t val = 1024;

    std::cout << "count value result :"<< count_val(val)<< std::endl;
    return 0;
}

