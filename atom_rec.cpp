#include "atom_rec.h"
#include "network_rec.h"



void AtomRec::turn() {
    Atom * partner = select_partner();
    if (partner != nullptr) {
        exchange_e(*this, *partner);
        net->aquenue.push_back(partner);
    }
}

Atom * AtomRecConstructor::construct(const AtomBase& base, const NCreatorParams& p) const {
    return new AtomRec(base);
};
