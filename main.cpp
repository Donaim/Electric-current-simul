
#include "nconnectors.cpp"
#include "network_creator.cpp"
#include "network_creator_params.cpp"
#include "helpers.cpp"
#include "atom.cpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void test_list() {
    SList<char> t{1};
    t.push_back('A');
    t.push_back('B');
    t.push_back('\0');
    cout << '\"' << t.source() << '\"' << endl;
    t.forget_and_alloc_new(2);
    t.push_back('X');
    t.push_back('Y');
    t.push_back('6');
    t.push_back('\0');
    cout << '\"' << t.source() << '\"' << endl;
}

int main() {
    srand(time(0));

    auto sh = *new RectangleF{0, 0, 1, 1};
    // auto p = *new DensityParams{sh, connectors::Intuitive{}, 100000.0};
    auto p = *new DensityParams{sh, connectors::TreeLike{}, 100000.0};
    ConnectedNetwork nt = SimpleCreator{}.create_solid_random_network(p);
    cout << "network connected!" << endl;

    // cout << nt << " : " << nt.total_charge() << endl;
    // nt.lap();
    cout << "lap finished" << endl;
    // cout << nt << " : " << nt.total_charge() << endl;

    cout << "end" << endl;
    return 0;
}
