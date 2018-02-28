
#include "atom.cpp"
#include "network_creator.cpp"
#include "helpers.cpp"
#include <iostream>

using namespace std;

int main() {

    Shape& sh = *new RectangleF{0, 0, 100, 100};
    Network nt = SimpleCreator{}.create_solid_random_network(sh, 10);
    nt.lap();

    cout << "end" << endl;
    return 0;
}
