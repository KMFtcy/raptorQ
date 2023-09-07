#ifndef LT_BLOCK_H
#define LT_BLOCK_H

#include <algorithm> // std::random_shuffle
#include <vector>    // std::vector
#include <ctime>     // std::time
#include <cstdlib>   // std::rand, std::srand
#include <time.h>
#include <stdio.h>
using namespace std;

class LT_code
{
public:
    int data;
    vector<int> source_index_arr;
    LT_code(char, vector<int> source_block_index);
    ~LT_code();
protected:
private:
};

LT_code::LT_code(char data, vector<int> source_block_index)
{
    this->data = data;
    source_index_arr = source_block_index;
}

LT_code::~LT_code()
{
}


#endif // LT_CODE_H