#include <iostream>
#include <sdsl/int_vector.hpp>
#include <sdsl/bit_vectors.hpp>
#include "xxhash.h"
#include "MPHF.h"
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace sdsl;
using namespace std::chrono;

int main() {

    vector<string> keys;
    ifstream in("n_10000.txt");
    string str;
    while(getline(in,str)) {
        if (str.size() > 0) {
            keys.push_back(str);
        }
    }

    vector<string> alien_keys;
    ifstream out("alien_1000.txt");
    string rts;
    while(getline(out,rts)) {
        if (rts.size() > 0) {
            alien_keys.push_back(rts);
        }
    }


    //vector<string> keys = {"abc", "abd", "ghi"};

    //bit_vector b = {0,0,1,1,0};
    //rank_support_v<1> b_rank(&b);
    //int rank = b_rank(4);
    //cout << rank << endl;

    // construct MPHF with keys vector, n=3, gamma=10, and last=3
    MPHF b(&keys, 1, 3);
    vector<bit_vector> bv = b.MPHF_construct();
    int result;
    result = b.lookup("AAA");
    cout << "result of lookup on AAA: " << result << endl;

    /*cout << "size of bit_arrays at end: " << bv.size() << endl;
    for (int i = 0; i < bv.size(); i++) {
        cout << "size of bv[" << i << "]: " << bv[i].size() << endl;
    }*/

    /*for (int i = 0; i < keys.size(); i++) {
        result = b.lookup(keys[i]);
        cout << "result of lookup for " << keys[i] << ": " << result << endl;
    }*/

    /*
    for (int x = 0; x < alien_keys.size(); x++) {
        result = b.lookup(alien_keys[x]);
        cout << "alien key hash value: " << result << endl;
    }
     */

    // result = b.lookup("AAME");
    // cout << "alien key hash value: " << result << endl;
    // result = b.lookup("WXCI");
    // cout << result << endl;

/*
    auto start = high_resolution_clock::now();
    result = b.lookup("HDBB");
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "N keys = " << keys.size() << endl;
    cout << "time to lookup key (mphf): " << duration.count() << endl;
    cout << "data structure size: " << b.data_struct_size() << endl;

    //result = b.lookup("aaa");
    //cout << "result of lookup for alien key: " << result << endl;

    unordered_map<string, uint64_t> basic_hash = b.basic_hash(keys);
    start = high_resolution_clock::now();
    uint64_t basic_lookup = b.basic_hash_lookup("YMJ", basic_hash);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "time to lookup key (basic hash map): " << duration.count() << endl;
*/


}

