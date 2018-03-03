#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "atom_rec.h"
#include "network_rec.h"

using namespace std;

int main() {
    cout << "kek" << endl;
    srand(time(0));

    auto sh = *new RectangleF{0, 0, 1, 1};
    // auto p = *new DensityParams{sh, connectors::Intuitive{}, 100000.0};
    auto p = *new DensityParams{sh, connectors::TreeLike{}, SimpleConstructor{}, 20.0};
    ConnectedNetwork nt = SimpleCreator{}.create_solid_random_network(p);
    cout << "network connected!" << endl;

    cout << nt << " : " << nt.total_charge() << '(' << nt.avg_abscharge() << ')' << endl;
    nt.lap();
    cout << "lap finished" << endl;
    cout << nt << " : " << nt.total_charge() << '(' << nt.avg_abscharge() << ')' << endl;

    cout << "end" << endl;
    return 0;
}
