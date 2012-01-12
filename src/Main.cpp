#include <iostream>
#include <allegro.h>

#include "Util.h"
#include "System.h"
using namespace std;

int main(int argc, char** argv)
{
    System::get(new System());
    if(System::ptr() && System::get().hasError()) {
        std::cout << System::get().getError() << std::endl;
        return 1;
    }
    return System::get().run() ? 0 : 1;
}

