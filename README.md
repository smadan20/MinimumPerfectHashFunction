# MinimumPerfectHashFunction

## CMSC858D Homework #2: Implementing a minimum perfect hash function
### Implementation by: Sanna Madan



### Instructions for building:
Enter the following in command line/terminal:
```
make
./main
```


### Using the implementation:

In main.cpp, specify the input file containing line-separated keys.
Optionally, specify the input file containing line-separated alien keys as well.

To create a MPHF object b (input reference to keys, gamma, and last):
```
MPHF b(&keys, 1, 3);
```

To construct the MPHF on b:
```
vector<bit_vector> bv = b.MPHF_construct();
```

To lookup a key in b:
```
uint64_t result = b.lookup("key");
```

To create a standard hash table (unordered map) for b:
```
unordered_map<string, uint64_t> basic_hash = b.basic_hash(keys);
```

To lookup a key in a standard hash table for b:
```
uint64_t basic_lookup = b.basic_hash_lookup("key", basic_hash);
```

To get the mphf data structure size for b:
```
uint64_t size = b.data_struct_size();
```


## Citation:
	Limasset, A., Rizk, G., Chikhi, R., & Peterlongo, P. (2017). Fast and scalable minimal perfect hashing for massive key sets. arXiv preprint arXiv:1702.03154.
