#pragma once 

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<std::string> parse_lines(std::string f)
{
    std::fstream i(f);
    std::vector<std::string> lineList;
    std::string currentLine;

    while(getline(i, currentLine))
        if(!currentLine.empty()) { lineList.push_back(currentLine); }

    return lineList;
}