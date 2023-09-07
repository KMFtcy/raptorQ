#include "main.h"
#include <iostream>
#include <algorithm> // std::random_shuffle
#include <vector>    // std::vector
#include <ctime>     // std::time
#include <cstdlib>   // std::rand, std::srand
#include <time.h>
#include <stdio.h>

#include "LT_block.h"

char test_file[5] = {'H', 'e', 'l', 'l', 'o'};
vector<LT_code> block_buffer;

int main()
{
    using namespace std;
    srand((unsigned)time(NULL));

    cout << "ascii of test file: ";
    for (int i = 0; i < 5; i++)
    {
        printf("%d", test_file[i]);
        printf(" ");
    }
    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        // initialize vector with numbers 0-4
        std::vector<int> index_vector;
        for (int i = 0; i < 5; ++i)
        {
            index_vector.push_back(i);
        }
        // shuffle index vector and use the first m elements
        std::random_shuffle(index_vector.begin(), index_vector.end());
        // std::cout << "myvector contains:"; // print out content:
        // for (std::vector<int>::iterator it = index_vector.begin(); it != index_vector.end(); ++it)
        //     std::cout << ' ' << *it;
        // std::cout << '\n';
        // Encoding
        int selected_num = (rand() % 5) + 1;
        // cout << "Select " << selected_num << " blocks" << endl;
        std::vector<int> data_vector;
        int xor_save = test_file[index_vector[0]];
        data_vector.push_back(index_vector[0]);
        for (int i = 1; i < selected_num; i++)
        {
            xor_save = xor_save ^ test_file[index_vector[i]];
            data_vector.push_back(index_vector[i]);
            // cout << "xor result for step " << i << " : " << xor_save << endl;
        }
        LT_code *lt_code = new LT_code(xor_save, data_vector);
        // cout << "LT code data: " << lt_code->data << endl;
        // cout << "LT code source index: ";
        // for (int i = 0; i < lt_code->source_index_arr.size(); i++)
        // {
        //     cout << lt_code->source_index_arr[i] << " ";
        // }
        // cout << endl;
        block_buffer.push_back(*lt_code);
    }

    // Decoding
    char result[5];
    bool can_decode = true;
    while (block_buffer.size() > 0 && can_decode)
    {
        cout << "Decoding..." << endl;
        can_decode = false;
        for (int i = 0; i < block_buffer.size(); i++)
        {
            if (block_buffer[i].source_index_arr.size() == 1)
            {
                can_decode = true;
                int decoded_index = block_buffer[i].source_index_arr[0];
                int decoded_data = block_buffer[i].data;
                // decode block if it contains only one source index
                cout << "Decoded block: " << block_buffer[i].data << endl;
                result[block_buffer[i].source_index_arr[0]] = block_buffer[i].data;
                block_buffer.erase(block_buffer.begin() + i);
                i--;
                // remove decoded index from other blocks
                for (int j = 0; j < block_buffer.size(); j++)
                {
                    for (int k = 0; k < block_buffer[j].source_index_arr.size(); k++)
                    {
                        if (block_buffer[j].source_index_arr[k] == decoded_index)
                        {
                            block_buffer[j].data = block_buffer[j].data ^ decoded_data;
                            block_buffer[j].source_index_arr.erase(block_buffer[j].source_index_arr.begin() + k);
                            break;
                        }
                    }
                    if (block_buffer[j].source_index_arr.size() == 0)
                    {
                        block_buffer.erase(block_buffer.begin() + j);
                        j--;
                    }
                }
            }
        }
    }
    if (block_buffer.size() == 0)
    {
        cout << "Use all block" << endl;
    }
    if (!can_decode)
    {
        cout << "Can't decode" << endl;
    }
    for (int i = 0; i < 5; i++){
        printf("%c", result[i]);
        printf(" ");
    }
    return 0;
}