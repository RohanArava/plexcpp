#include "PreDefined.h"
#include <iostream>
int main(int argc, char** argv){
    PreDefined pd;
    if(argc < 2){
        std::cout << "Please provide data file name" << std::endl;
    }
    pd.CSV(argv[1]);
    return 0;
}