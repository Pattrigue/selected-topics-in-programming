#include <iostream>
#include "NumberSeries.h"

int main() {
    NumberSeries series = NumberSeries::make_random(10, -10, 10);
    std::cout << series << std::endl;
    
    return 0;
}
