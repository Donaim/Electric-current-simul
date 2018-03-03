#include "network_rec.h"
#include <iostream>

NetworkRec::NetworkRec(AtomCollection& net, const NCreatorParams& p) :  ConnectedNetwork(net, p) {
    atomsrec = (AtomRec**) atoms;

    for (int i = 0; i < a_count; i++) {
        atomsrec[i]->net = this;
    }

    std::cout << "Recurent network initialized!" << std::endl;
}

void NetworkRec::lap() {
    for (int i = 0; i < a_count; i++ ) {
        atomsrec[i]->turn();
        std::cout << "qsize=" << aquenue.size() << std::endl;

        while(aquenue.size() > 0) {
            for (int k = 0, to = aquenue.size(); k < to; k++) {
                aquenue[k]->turn();
            }
            aquenue.clear_dont_free();
        }
    }
}