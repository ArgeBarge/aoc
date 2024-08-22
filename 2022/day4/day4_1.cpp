#include <iostream>
#include "parser.h"
#include <string>
#include <sstream>

int get_pair_overlap(std::string);
std::pair<std::string, std::string> tokenize_pair(std::string);
int* tokenize_ranges(std::pair<std::string, std::string>);

int main(int argc, char **argv)
{
    int overlap_count = 0;
    std::vector<std::string> lines = parse_lines("../../input/day4.txt");

    // checking whether each pair overlaps 
    for(auto it = lines.begin(); it != lines.end(); it++)
        if(get_pair_overlap(*it)) { overlap_count++; }


    std::cout << "overlap count:" << overlap_count << "\n";
    return 0;
}

int get_pair_overlap(std::string s)
{
    // splitting the strings up 
    std::pair<std::string, std::string> currentPair = tokenize_pair(s);
    int* rangeArr = tokenize_ranges(currentPair);
    int diff1 = rangeArr[0] - rangeArr[2];
    int diff2 = rangeArr[1] - rangeArr[3];

    delete rangeArr;

    // checks if there is a complete overlap 
    // this will only happen if the difference between the first number in each pair is negative and
    // the difference between the second number in each pair is positive or vice versa (or the difference is both 0)
    // for example 91 - 93 is -2 and 6 - 92 is -86 both negative so dont overlap 
    if(diff1 <= 0 && diff2 >= 0 || diff1 >= 0 && diff2 <= 0)
        return 1;

    return 0;
}

// splits the pairs up, for example 91-93,6-92 is tokenized into 
// 91-93 and 6-92
std::pair<std::string, std::string> tokenize_pair(std::string s)
{
    std::vector<std::string> tokens;
    // uses a string stream to tokenize 
    std::stringstream currentPair(s);
    std::string token;
    std::pair<std::string, std::string> pair;
    // each 'line' is a new token
    while(std::getline(currentPair, token, ','))
        tokens.push_back(token);

    return { tokens[0], tokens[1] };
        
}

// splits the range of numbers up for example 91-93 is tokenized into 
// 91 and 93 
int* tokenize_ranges(std::pair<std::string, std::string> p)
{
    std::string token;
    std::vector<std::string> tokens;
    std::stringstream streamPair[2];
    streamPair[0].str(p.first);
    streamPair[1].str(p.second);

    for(int i = 0; i < 2; i++)
    {
        while(getline(streamPair[i], token, '-'))
            tokens.push_back(token);
    }
    
    int *rangeArr = new int(4);

    // converts string numbers into ints
    for(int i = 0; i < 4; i++)
        rangeArr[i] = atoi(tokens[i].c_str());

    return rangeArr;
}