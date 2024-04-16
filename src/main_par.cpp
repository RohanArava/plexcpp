#include "./PreDefined.h"
#include "./parallel/DPrescan.h"
int main(){
    auto pd = PreDefined();
    auto dlex = pd.example_dlex();
    auto dprescan = DPrescan::construct(dlex);
    return 0;
}