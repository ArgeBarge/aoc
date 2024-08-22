#include <iostream>
#include <fstream>
#include <ctype.h>
#include <vector>
#include <set>
#include <algorithm>
#include "parser.h"

int get_priority_sum();
int get_alphabet_num(char);
int get_group_priority(std::string, std::string, std::string);

int main(int argc, char **argv)
{
    std::cout << "sum of priorities: " << get_priority_sum() << "\n";
    return 0;
}

int get_priority_sum()
{
    std::string currentLine;
    std::string member1;
    std::string member2;
    std::string member3;

    int priority_sum = 0;
    
    std::vector<std::string> lines = parse_lines("day3input.txt");

    // iterating through the groups
    for(int i = 0; i < lines.size(); i+=3)
    {
        std::string member1 = lines[i];
        std::string member2 = lines[i+1];
        std::string member3 = lines[i+2];
        priority_sum += get_group_priority(member1, member2, member3);
    }
        
    return priority_sum;
}

int get_alphabet_num(char c)
{
    if(c == toupper(c))
        return toupper(c) - 38;
    else 
        return toupper(c) - 64;
}

int get_group_priority(std::string m1, std::string m2, std::string m3)
{
    // using set intersection to find common element
    std::set<char> sm1(m1.begin(), m1.end());
    std::set<char> sm2(m2.begin(), m2.end());
    std::set<char> sm3(m3.begin(), m3.end());

    // intersection of first and second member rucksack
    std::set<char> intersection12;
    std::set_intersection(
        sm1.begin(), sm1.end(),
        sm2.begin(), sm2.end(),
        std::inserter(intersection12, intersection12.begin())
    );

    // intersection of (first and second) and third
    std::set<char> intersection123;
    std::set_intersection(
        intersection12.begin(), intersection12.end(),
        sm3.begin(), sm3.end(),
        std::inserter(intersection123, intersection123.begin())
    );

    // if empty something has gone wrong, else return priority of common element
    if(intersection123.empty())
        return -1;
    else
        return get_alphabet_num(*(intersection123.begin()));
}