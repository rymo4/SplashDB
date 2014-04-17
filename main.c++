#include <iostream>
#include <vector>

#ifdef INT_2_BYTES
typedef long int32;
#else
typedef int int32;
#endif

class SplashTree {
  private:
    int numHashFns, numReinserts, capacity;
    std::vector<int> keys;
    std::vector<int> vals;
    std::vector<int> hashVals;
    bool bucketHasSpace(int);
    void fillHashVals();
    int hashFromID(int, int);
  public:
    SplashTree(int, int, int);
    void insert(int, int);
    int get(int);
};

SplashTree::SplashTree(int h, int r, int c) {
  numHashFns = h;
  numReinserts = r;
  capacity = c;

  keys.resize(c);
  vals.resize(c);

  hashVals.resize(h);
  fillHashVals();
}

void SplashTree::fillHashVals(){
  for (int i = 0; i < numHashFns; i++){
    // random 32 bit odd numbers
    hashVals[i] = (rand() / 2 * 2 + 1);
  }
}

int SplashTree::hashFromID(int k, int hashID){
  // TODO: make this what the actual hash function should be doing
  return (k * hashVals[hashID]) % capacity;
}

int SplashTree::get(int k){
  for (int i = 0; i < numHashFns; i++){
    int bucket = hashFromID(k, i);
    if (keys[bucket] == k){
      return vals[bucket];
    }
  }
  // TODO error case when k not in hash
  return NULL;
}

void SplashTree::insert(int k, int v){
  // try hash functions successively until object fits in bucket
  for (int i = 0; i < numHashFns; i++){
    int bucket = hashFromID(k, i);
    if (bucketHasSpace(bucket)){
      keys[bucket] = k;
      vals[bucket] = v;
      return;
    }
  }
  //TODO:  error case if failed # inserts
}

bool SplashTree::bucketHasSpace(int id){
  // TODO buckets should not be size 1 always, make linked list
  return keys[id] == 0;
}

int main()
{
  int k = 101;
  int v = 300;
  SplashTree s(10, 5, 20);
  s.insert(k, v);
  if (s.get(k) != v){
    std::cout << "FAIL\n";
    return 0;
  }

  std::cout << "PASS!\n";
}
