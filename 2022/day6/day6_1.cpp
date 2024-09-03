#include <iostream>
#include <vector>
#include <cstring>
#include "parser.h"

namespace Hash {

    struct HashTable 
    {
        int *tableContents;
        int size = 0;
    };

    int hashInit(HashTable* k, int s);
    int hashDestroy(HashTable* h);
    int hashFunction(HashTable*, int);
    int insert(HashTable*, int);
    int search(HashTable* h, int k);
    int clear(HashTable* h);
}

int check_previous_chars(std::string::iterator*, Hash::HashTable*);

int main(int argc, char **argv)
{
    int character_count = 4;
    std::vector<std::string> lineList = parse_lines("day6.txt");
    
    std::string buffer = lineList.front();
    
    Hash::HashTable h;
    Hash::hashInit(&h, 13);

    auto it = buffer.begin();
    
    
    for(it += 4; it != buffer.end(); it++)
    {
        if(check_previous_chars(&it, &h))
        {
            character_count++;
            continue;
        }
            
        
        std::cout << *(it-4) << *(it-3) << *(it-2) << *(it-1) << "\n";
        
        std::cout << character_count << std::endl;
        
        exit(EXIT_SUCCESS);
    }


}

int Hash::hashInit(Hash::HashTable *h, int s) { h->size = s; h->tableContents = new int[s]; memset(h->tableContents, -1, s * sizeof(int)); return 1; }
int Hash::hashFunction(Hash::HashTable* h, int k) { return k % h->size; }

int Hash::insert(Hash::HashTable* h, int k) 
{ 
    int i = 0;
    int value = -1;
    while((value = h->tableContents[(Hash::hashFunction(h, k) + i) % h->size]) != -1)
    {
        std::cout << "I am stuck";
        if(value == k)
            return k;
        i++;
    }
        
    h->tableContents[(Hash::hashFunction(h, k) + i) % h->size] = k;

    return 1;
}

int Hash::search(Hash::HashTable* h, int k) 
{
    int value = -1;

    int i = 0;
    while((value = h->tableContents[(Hash::hashFunction(h, k) + i) % h->size]) != k)
    {
        //std::cout << "value: " << value << std::endl;
        if(value == -1)
            return value;
        
        i++;
    }

    return value;
        
}

int Hash::clear(HashTable *h) { memset(h->tableContents, -1, h->size * sizeof(int)); return 1; }

int Hash::hashDestroy(HashTable* h) { delete[] h->tableContents; return 1; }

int check_previous_chars(std::string::iterator* it, Hash::HashTable* h)
{
    for(int i = 4; i > 0; i--)
    {
        std::cout << "inserting: " << *(*(it)-i) << " " << Hash::hashFunction(h, *(*(it)-i)) << std::endl;
        std::cout << Hash::search(h, *(*(it)-i)) << std::endl;
        if(Hash::insert(h, *(*(it)-i)) == *(*(it)-i))
        {
            std::cout << "I ran\n";
            Hash::clear(h);
            return 1;
        }
        
    }

    return 0;
}