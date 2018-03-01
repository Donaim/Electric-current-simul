#include "atom.cpp"
#include "network.cpp"
#include "rng.cpp"

namespace connectors {
    struct Intuitive : Connector {
        virtual Atom ** connect(const Network& net) const override {
            AtomBase ** arr = net.atoms;
            int n = net.a_count;
            float dist = pow2(MAX_CONNECTION_DIST);
            Atom ** re = new Atom*[n];

            float avg_neighbors = 10; // helps with allocation
            SList<AtomBase*> list(avg_neighbors);

            for (int x = 0; x < n; x++ ) {
                AtomBase * tmp = arr[x];
                list.forget_and_alloc_new((int)avg_neighbors + 17);
    
                for (int y = 0; y < n; y++) {
                    if (Atom::dist2(tmp, arr[y]) < dist) {
                        list.push_back(arr[y]);
                    }
                }

                re[x] = new Atom(*tmp, list.source(), list.size());
                avg_neighbors = (avg_neighbors * (x) + list.size()) / (float)(x + 1);
            }
            
            std::cout << "avg network connections: " << avg_neighbors << std::endl;

            return re;
        }
    };
    struct TreeLike : Connector {

        virtual Atom ** connect(const Network& net) const override {
            AtomBase ** arr = net.atoms;
            int n = net.a_count;

            for (int x = 0; x < n; x++ ) {
                
            }

            throw "not implemented";
            return nullptr;
        }
        struct AtomIndexed {
            AtomIndexed * prev;

            AtomBase * me;
            AtomBase ** nb;
            int nb_count;

            AtomIndexed(int nb_count) : prev(nullptr), nb(new AtomBase*[nb_count]), nb_count(nb_count) {

            }
        };
    };
}