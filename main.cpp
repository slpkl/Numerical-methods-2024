#include <iostream>
#include "StandartAtmosphereModel.hpp"

int main(){
    // example of usage
    double height = 15000.0;
    StandartAtmosphereModel atmosphere(height);
    atmosphere.display();
    return 0;
}
