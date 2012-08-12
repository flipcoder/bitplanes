#include <iostream>

#include "Util.h"
#include "System.h"
using namespace std;

int main(int argc, const char** argv)
{
    try{
        System::get(new System());
    }catch(const std::exception& e){
        std::cout << e.what() << std::endl;
        return 1;
    }
    if(System::ptr() && System::get().hasError()) {
        std::cout << System::get().getError() << std::endl;
        return 1;
    }
    return System::get().run() ? 0 : 1;
}

