#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "nconnectors.h"
// #include "network.h"
#include "atom_rec.h"
#include "network_rec.h"

using namespace std;

int main() {
    srand(time(0));

    auto sh = *new RectangleF{0, 0, 1, 1};
    // auto p = *new DensityParams{sh, connectors::TreeLike{}, SimpleConstructor{}, 20.0};
    auto p = *new DensityParams{sh, connectors::TreeLike{}, RecConstructor{}, AtomRecConstructor{}, 1000.0};
    NetworkRec& nt = (NetworkRec&) SimpleCreator{}.create_solid_random_network(p);
    cout << "network connected!" << endl;

    // cout << nt << " : " << nt.total_charge() << '(' << nt.avg_abscharge() << ')' << endl;
    cout << nt.total_charge() << '(' << nt.avg_abscharge() << ')' << endl;
    nt.lap();
    cout << "lap finished" << endl;
    // cout << nt << " : " << nt.total_charge() << '(' << nt.avg_abscharge() << ')' << endl;
    cout << nt.total_charge() << '(' << nt.avg_abscharge() << ')' << endl;

    cout << "end" << endl;
    return 0;
}
