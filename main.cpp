
#include "atom.cpp"
#include "network_creator.cpp"
#include "helpers.cpp"
#include <iostream>

using namespace std;

int main() {

    Shape& sh = *new RectangleF{0, 0, 100, 100};
    Network nt = SimpleCreator{}.create_solid_random_network(sh, 100000);
    cout << "network connected!" << endl;

    // cout << nt << endl;
    nt.lap();
    cout << "lap finished" << endl;
    // cout << nt << endl;

    cout << "end" << endl;
    return 0;
}
