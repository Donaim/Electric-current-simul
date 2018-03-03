
#include "sipipis.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
    srand(time(0));

    auto sh = *new RectangleF{0, 0, 1, 1};
    // auto p = *new DensityParams{sh, connectors::Intuitive{}, 100000.0};
    auto p = *new DensityParams{sh, connectors::TreeLike{}, SimpleConstructor{}, 20.0};
    ConnectedNetwork nt = SimpleCreator{}.create_solid_random_network(p);
    cout << "network connected!" << endl;

    cout << nt << " : " << nt.total_charge() << endl;
    nt.lap();
    cout << "lap finished" << endl;
    cout << nt << " : " << nt.total_charge() << endl;

    cout << "end" << endl;
    return 0;
}
