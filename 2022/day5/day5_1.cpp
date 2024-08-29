#include <iostream>
#include <vector>
#include <cctype>
#include "parser.h"

#define STACK_NUM 9

std::vector<char>* get_initial_state(std::vector<std::string>*);
void get_final_state(std::vector<std::string>*, std::vector<char>*);
void move_crates(const int*, std::vector<char>*);

int main(int argc, char **argv)
{
    std::vector<std::string> lineList = parse_lines("day5.txt");
    std::vector<char>* initialState = get_initial_state(&lineList);

    for(int i = 0; i < STACK_NUM; i++)
    {
        for(auto it = initialState[i].begin(); it != initialState[i].end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";

    get_final_state(&lineList, initialState);
    
    for(int i = 0; i < STACK_NUM; i++)
    {
        for(auto it = initialState[i].begin(); it != initialState[i].end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }

    delete[] initialState;
    return 0;
}

std::vector<char>* get_initial_state(std::vector<std::string>* lineList)
{
    //deallocate
    std::vector<char> *initialState = new std::vector<char>[STACK_NUM];
    
    for(auto it = lineList->begin(); it != lineList->end(); it++)
    {
        for(int i = 0; i < (*it).length(); i++)
        {
            if(std::isupper((*it)[i])) 
                initialState[(i - 1) / 4].insert(initialState[(i - 1) / 4].begin(), (*it)[i]);
            else if(std::islower((*it)[i]))
            {
                lineList->erase(lineList->begin(), it);
                return initialState;
            }
        }     
    }

    return NULL;
}

void get_final_state(std::vector<std::string>* lineList, std::vector<char>* currentState)
{
    int currentCommand[3];
    int number_buffer[2] = {0};
    int i = 0;

    for(auto l : *lineList)
    {
        //std::cout << "resetting i\n";
        i = 0;
        for(auto it = l.begin(); it != l.end(); it++)
        {
            
            if(std::isdigit(*it))
            {
                number_buffer[0] == 0 ? number_buffer[0] = *it - '0' : number_buffer[1] = *it - '0';

                if(std::isdigit(*(it+1)))
                    continue;
                else 
                {
                    if(number_buffer[1] == 0)
                        currentCommand[i % 3] = number_buffer[0];
                    else 
                        currentCommand[i % 3] = number_buffer[0] * 10 + number_buffer[1];

                    i++;

                    if(i % 3 == 0 && i != 0)
                        move_crates(currentCommand, currentState);
                
                    number_buffer[0] = 0;
                    number_buffer[1] = 0;
                }
            }        
        }
    }
}

void move_crates(const int* currentCommand, std::vector<char>* currentState)
{
    int quant = currentCommand[0];
    int from = currentCommand[1]-1;
    int to = currentCommand[2]-1;

    std::cout << "current command: " << currentCommand[0] << " " << currentCommand[1] << " " << currentCommand[2] << std::endl;

    for(int i = 0; i < quant; i++)
    {
        currentState[to].push_back(currentState[from].back()); 
        currentState[from].pop_back();
    }

    for(int i = 0; i < STACK_NUM; i++)
    {
        for(auto it = currentState[i].begin(); it != currentState[i].end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }
}   
// tried answers: LJWCSSZ