#include <iostream>
#include <fstream>
#include <ctype.h>

int get_priority_sum();
int get_alphabet_num(char);
int get_shared_priority(std::string, std::string);

int main(int argc, char **argv)
{
    std::cout << "sum of priorities: " << get_priority_sum() << "\n";
    return 0;
}

int get_priority_sum()
{
    std::string currentLine;
    std::string firstHalf;
    std::string secondHalf;

    int priority_sum = 0;
    int halves_sum = 0;

    std::ifstream MyReadFile("day3input.txt");
    
    while(getline(MyReadFile, currentLine))
    {
        if(!currentLine.empty())
        {
            firstHalf = currentLine.substr(0, currentLine.length() / 2);
            secondHalf = currentLine.substr(currentLine.length() / 2);
            
            priority_sum += get_shared_priority(firstHalf, secondHalf);
        }
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

int get_shared_priority(std::string firstHalf, std::string secondHalf)
{
    
    for(int i = 0; i < firstHalf.length(); i++)
    {
        for(int j = 0; j < secondHalf.length(); j++)
        {
            if(firstHalf[i] == secondHalf[j])
            {
                return get_alphabet_num(firstHalf[i]);
            }
        }
    }

    return -1;
}