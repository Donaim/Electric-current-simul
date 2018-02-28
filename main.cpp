
#include "atom.cpp"
#include "network_creator.cpp"
#include "helpers.cpp"
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
    // srand(time(0));

    Shape& sh = *new RectangleF{0, 0, 10, 10};
    ConnectedNetwork nt = SimpleCreator{}.create_solid_random_network(sh, 0.1);
    cout << "network connected!" << endl;

    cout << nt << endl;
    nt.lap();
    cout << "lap finished" << endl;
    cout << nt << endl;

    cout << "end" << endl;
    return 0;
}
