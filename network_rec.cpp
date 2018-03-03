#include "network_rec.h"

using me = NetworkRec;

me::NetworkRec(AtomCollection& net, const NCreatorParams& p) :  ConnectedNetwork(net, p) {
    atomsrec = (AtomRec**) atoms;
}

void me::lap() {
    for (int i = 0; i < a_count; i++ ) {
        atomsrec[i]->turn();
    }
}