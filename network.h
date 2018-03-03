#pragma once

struct Network {
    Atom ** atoms;
    int a_count;
    ~Network() { // should not destruct this
        // std::cout << "Network destructed" << std::endl;
        // for (int i = 0; i < a_count; i++) {
        //     delete atoms[i];
        // }
        // delete[] atoms;
    }
};
