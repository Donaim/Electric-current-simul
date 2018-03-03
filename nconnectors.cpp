#pragma once

#include "atom.cpp"
#include "rng.cpp"
#include "atom_collection.h"
#include "nconnectors.h"

namespace connectors {
    struct Intuitive : Connector {
        virtual void connect(const AtomCollection& net) const override { // complexity ~ n^2
            Atom ** arr = net.atoms;
            int n = net.a_count;
            float dist = pow2(MAX_CONNECTION_DIST);

            float avg_neighbors = 10; // helps with allocation
            SList<Atom*> list(avg_neighbors);

            for (int x = 0; x < n; x++ ) {
                Atom * tmp = arr[x];
                list.forget_and_alloc_new((int)avg_neighbors + 1);
    
                for (int y = 0; y < n; y++) {
                    if (Atom::dist2(tmp, arr[y]) < dist) {
                        list.push_back(arr[y]);
                    }
                }

                tmp->neighbors = list.source();
                tmp->n_count = list.size();

                avg_neighbors = (avg_neighbors * (x) + list.size()) / (float)(x + 1);
            }
            
            std::cout << "avg network connections: " << avg_neighbors << std::endl;
        }
    };
    struct TreeLike : Connector {
        int avg_neighbors = 10;
        int neighbors_dev = 3;

        virtual void connect(const AtomCollection& net) const override { // complexity ~ n or (2n + ~n)
            Atom ** arr = net.atoms;
            int n = net.a_count;
            
            AtomIndexed ** indexed = new AtomIndexed*[n];
            for (int i = 0; i < n; i++) {
                int nbc = rand_i_min_max(avg_neighbors - neighbors_dev, avg_neighbors + neighbors_dev);
                indexed[i] = new AtomIndexed(nbc, arr[i]);
            }

            for (int i = 0, c = 0; i < n; i++ ) {
                indexed[i]->find_neighbors(indexed, n, i, &c); // actual connecting
            }

            for (int i = 0; i < n; i++) {
                arr[i]->neighbors = indexed[i]->get_raw_nb();
                arr[i]->n_count = indexed[i]->get_curr_count();
            }

            // destruct
            for (int i = 0; i < n; i++ ) {
                delete indexed[i];
            }
            delete[] indexed;
        }
        class AtomIndexed {
            AtomIndexed * parent;
            AtomIndexed ** nb;

            Atom * me;
            int target_count;
            int curr_count;
            
            bool try_adopt(AtomIndexed * o) {
                if (o->parent != nullptr) { return false; }
                if (!try_connect(this, o)) { return false; }
                
                o->parent = this;
                
                return true;
            }

            static bool try_connect(AtomIndexed * a, AtomIndexed * b) {
                if (a == b) { return false; } // adress the same : objects the same
                if (a->curr_count >= a->target_count || b->curr_count >= b->target_count) { return false; }

                a->nb[a->curr_count++] = b;
                b->nb[b->curr_count++] = a;
                return true;
            }
        public:
                                                        // even though atom can have less than t_count neighbors, i allocate more, just to assure everyone fits
            AtomIndexed(int t_count, Atom * m) : me(m), parent(nullptr), nb(new AtomIndexed*[t_count]), target_count(t_count), curr_count(0)
            {

            }
            void find_neighbors(AtomIndexed ** indexed, int indexed_len, int my_index, int * c_ptr) {
                if( parent != nullptr ) { // false only if root
                    for (int i = 0; i < parent->curr_count; i++) {
                        try_connect(this, parent->nb[i]);
                        if (curr_count >= target_count) { break; }
                    }
                }
                while (curr_count < target_count) {
                    if ( (*c_ptr) >= indexed_len - 1 ) { break; }
                    try_adopt(indexed[ ++(*c_ptr) ]);
                }
            }

            Atom ** get_raw_nb() {
                Atom ** re = new Atom*[curr_count];
                for (int i = 0; i < curr_count; i++ ) {
                    re[i] = nb[i]->me;
                }
                return re;
            }
            int get_curr_count() { return curr_count; }

            ~AtomIndexed() {
                delete [] nb;
                // delete me; // for some reason bad
            }
        };
    };
}