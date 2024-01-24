#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void get_most_calories();
void get_top_three_calories();

int main(int argc, char **argv)
{
    get_most_calories();
    get_top_three_calories();
    return 0;
}

void get_most_calories()
{
    int currentMaxCalories = 0;
    int currentElfCount = 0;

    std::string currentLine;
    std::ifstream MyReadFile("day1input.txt");

    while(getline(MyReadFile, currentLine))
    {
        if(!currentLine.empty())
            currentElfCount += atoi(currentLine.c_str());
        else 
        {
            if(currentMaxCalories < currentElfCount)
                currentMaxCalories = currentElfCount;

            currentElfCount = 0;
        }
    }

    std::cout << "Maximum calorie count: " << currentMaxCalories << "\n";
}

void get_top_three_calories()
{
    int currentElfCount = 0;

    std::string currentLine;
    std::ifstream MyReadFile("day1input.txt");
    std::vector<int> elfCalorieList;

    while(getline(MyReadFile, currentLine))
    {
        if(!currentLine.empty())
            currentElfCount += atoi(currentLine.c_str());
        else 
        {
            elfCalorieList.insert(elfCalorieList.end(), currentElfCount);
            currentElfCount = 0;
        }
    }

    sort(elfCalorieList.begin(), elfCalorieList.end());

    std::cout << 
    "Top 3 calories: " 
    << 
    elfCalorieList[elfCalorieList.size() - 1] 
    + elfCalorieList[elfCalorieList.size()-2] 
    + elfCalorieList[elfCalorieList.size()-3] 
    << "\n";


}