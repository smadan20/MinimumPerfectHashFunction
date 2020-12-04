//
// Created by Madan, Sanna (NIH/NCI) [F].
//

#ifndef BBHASH_IMPLEMENTATION_MPHF_H
#define BBHASH_IMPLEMENTATION_MPHF_H
#include <sdsl/bit_vectors.hpp>
#include <stdint.h>
#include <list>
#include <string>
#include "xxhash.h"
#include <vector>

using namespace std;
using namespace sdsl;

class MPHF {
public:

    vector<string> F0;
    uint64_t gamma;
    uint64_t last;

    vector<bit_vector> bit_arrays;
    unordered_map<string, uint64_t> terminal_hash;

    MPHF (vector<string> *keys, uint64_t param, uint64_t l) {
        F0 = *keys;
        gamma = param;
        last = l;
        //cout << "F0 size: " << F0.size() << endl;
        //cout << "gamma: " << gamma << endl;
        //cout << "last: " << last << endl;
    };

    vector<bit_vector> MPHF_construct () {
        vector<vector<string>> key_sets;
        key_sets.push_back(F0);
        XXH64_hash_t hash; // initialize hash function
        int i = 0;
        int seed = 0;
        bit_vector tmp;
        cout << "i: " << i <<  endl;
        cout << "last: " << last << endl;
        cout << "size of F[" << i << "] pushed onto key_sets: " << key_sets[i].size() << endl;
        // iterate through each set of keys
        while (key_sets[i].size() != 0 and i < last) {
            cout << "entered while loop" << endl;
            int N = key_sets[i].size();
            cout << "N: " << N << endl;
            cout << "CURRENT KEY SET i = " << i << ": ";
            for (int b = 0; b < key_sets[i].size(); b++) {
                cout << key_sets[i][b] << " ";
            }
            cout << endl;
            tmp = ArrayFill(key_sets[i], seed);
            bit_arrays.push_back(tmp); // create A[i]
            cout << "size of bit_arrays: " << bit_arrays.size() << endl;
            cout << "size of bit_arrays[" << i << "]:" << bit_arrays[0].size() << endl;
            bit_vector curr_A_vec = bit_arrays[i];
            cout << "curr_A_vec.size(): " << curr_A_vec.size() << endl;

            vector<string> new_vec(0, "");
            key_sets.push_back(new_vec); // adding F[i+1] to add colliding keys to.
            for (int x = 0; x < key_sets[i].size(); x++) {
                cout << "entered for loop " << endl;
                cout << "x (key index of current key set) = " << x << endl;
                //string curr_key = key_sets[i][x];
                cout << "current key (key_sets[i][x]: " << key_sets[i][x] << endl;
                hash = XXH64(&key_sets[i][x], key_sets[i][x].size(), seed) % (gamma * N);
                cout << "hash value: " << hash << endl;
                cout << "A[i][hash]: " << curr_A_vec[hash] << endl;
                int temp_var = i+1;
                if (curr_A_vec[hash] == 0) {
                    key_sets[temp_var].push_back(key_sets[i][x]);
                }
            }
            i = i+1;
            seed += 1;
        }
        // construct H from remaining elements from F[last + 1]
        cout << "final size of key_sets: " << key_sets.size() << endl;
        cout << "last (levels +1): " << last << endl;
        int last_plus_1 = last + 1;
        if (key_sets.size() == last_plus_1 and key_sets[last].size() != 0) {
            cout << "entered hash table terminal loop " << endl;
            HashMapTerminal(key_sets);
        }
        //bit_arrays.push_back(terminal_hash);
        // construct H using remaining elements from F[last+1]
        // return {A0, A1, ..., Alast, H}
        cout << "size of final bit_arrays: " << bit_arrays.size() << endl;
        for (int f = 0; f < key_sets.size(); f ++ ) {
            cout << "size of key set " << f << ": " << key_sets[f].size() << endl;
        }
        return bit_arrays;
    }

    unordered_map<string, uint64_t> HashMapTerminal(vector<vector<string>> key_sets) {
        int value = F0.size() - key_sets[last].size() + 1;
        for (int z = 0; z < key_sets[last].size(); z++) {
            string key = key_sets[last][z];
            terminal_hash[key] = value;
            cout << "value for key " << key << ": " << terminal_hash[key] << endl;
            value += 1;
        }
        return terminal_hash;
    }

    bit_vector ArrayFill(vector<string> key_set, uint64_t seed) {
        cout << "entered ArrayFill method" << endl;
        int key_count = key_set.size();
        cout << "key_count at iteration i: " << endl;
        XXH64_hash_t h;
        bit_vector A(gamma*key_count, 0);
        bit_vector C(gamma*key_count,0);
        cout << "length of A[i]: " << A.size() << endl;
        cout << "length of C[i]: " << C.size() << endl;
        cout << "gamma = " << gamma << ", key_count = " << key_count << ", gamma*key_count= " << gamma*key_count << endl;
        for (int x = 0; x < key_count; x++) { // for each key x of F
            cout << "key_set.size() for i: " << key_set.size() << endl;
            //string curr_key = key_set[x];
            cout << "current key (key_set[x]): " << key_set[x] << endl;
            h = XXH64(&key_set[x], key_set[x].size(), seed) % (gamma * key_count);
            cout << "hash value: " << h << endl;
            if (A[h] == 0 and C[h] == 0) {
                A[h] = 1;
            }
            else if (A[h] == 1 and C[h] == 0) {
                A[h] = 0;
                C[h] = 1;
            }
            else if (A[h] == 0 and C[h] == 1) {
                continue;
            }
        }
        cout << "A array: ";
        for (int z = 0; z < A.size(); z++) {
            cout << A[z] << " ";
        }
        cout << endl;
        cout << "C array: ";
        for (int z = 0; z < C.size(); z++) {
            cout << C[z] << " ";
        }
        cout << endl;
        cout << "exiting ArrayFill method" << endl;
        return A;
    }

    uint64_t lookup(string x) {
        cout << "LOOKUP: " << endl;
        string key = x;
        XXH64_hash_t h;
        int i = 0;
        int seed;
        //while (i < last) {
        while (i < bit_arrays.size()) {
            seed = i;
            h = XXH64(&x, x.size(), seed) % bit_arrays[i].size();
            cout << "h: " << h << endl;
            //cout << "bit_arrays[i].size() = " << bit_arrays[i].size() << endl;
            if (bit_arrays[i][h] == 1) {
                //cout << "success at i=" << i << endl;
                int to_return = 0;
                for (int j = 0; j < i; j++) {
                    for (int z = 0; z < bit_arrays[j].size(); z++) {
                        to_return += bit_arrays[j][z];
                    }
                }
                rank_support_v<1> b_rank(&bit_arrays[i]);
                to_return += b_rank(h+1); // h+1 because bit_vector rank doesn't count the current index.
                return to_return;
            }
            i = i+1;
        }
        //cout << "terminal_hash[x]: " << terminal_hash[x] << endl;
        //if (terminal_hash[x] == 0) {
        //    return F0.size() + 1;
        //}
        return terminal_hash[x];
    }

    unordered_map<string, uint64_t> basic_hash(vector<string> keys) {
        unordered_map<string, uint64_t> basic_hashmap;
        hash<string> my_hash;
        for (int i = 0; i < keys.size(); i++) {
            basic_hashmap[keys[i]] = my_hash(keys[i]);
        }
        return basic_hashmap;
    }

    uint64_t basic_hash_lookup(string key, unordered_map<string, uint64_t> map) {
        return map[key];
    }

    uint64_t data_struct_size() {
        int final_size = 0;
        for (int i =0; i<bit_arrays.size(); i++) {
            final_size += bit_arrays[i].size();
        }
        final_size += terminal_hash.size();
        return final_size;
    }

};


#endif //BBHASH_IMPLEMENTATION_MPHF_H
