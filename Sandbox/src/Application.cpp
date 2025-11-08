#include "test.h"

#include <iostream>

int main(){
    Engine::Print();
    std::cout << "Loaded config -> Engine.dll:\n";
    std::cout << Engine::GetConfig() << "\n";
    
    return 0;
}