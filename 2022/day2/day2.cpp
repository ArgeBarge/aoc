#include <iostream>
#include <fstream>

#define WIN_SCORE 6
#define DRAW_SCORE 3
#define LOSE_SCORE 0

#define ROCK 1
#define PAPER 2
#define SCISSORS 3

#define LOSE 1
#define DRAW 2
#define WIN 3

void tokenise_line(std::string, char *);
int get_round_score(int, int);
int get_int_value(char token);
void get_part_one_score();
void get_part_two_score();
int get_set_move(int, int);

int main(int argc, char **argv)
{
    get_part_one_score();
    get_part_two_score();
    return 0;
}

void get_part_one_score()
{
    int totalScore = 0;
    std::string currentLine;
    std::ifstream MyReadFile("day2input.txt");
    char tokens[2];

    while(getline(MyReadFile, currentLine))
    {
        if(!currentLine.empty())
        {   
            tokenise_line(currentLine, tokens);
            totalScore += get_round_score(
                get_int_value(tokens[0]), 
                get_int_value(tokens[1])
            );
        }
            
    }
    std::cout << totalScore << "\n";
}

void get_part_two_score()
{
    int totalScore = 0;
    std::string currentLine;
    std::ifstream MyReadFile("day2input.txt");
    char tokens[2];

    while(getline(MyReadFile, currentLine))
    {
        if(!currentLine.empty())
        {
            tokenise_line(currentLine, tokens);
            std::cout << tokens[0] << " " << tokens[1] << "\n";
            std::cout << get_set_move(get_int_value(tokens[0]), get_int_value(tokens[1])) << "\n";
            totalScore += get_round_score(
                get_int_value(tokens[0]), 
                get_set_move(get_int_value(tokens[0]), get_int_value(tokens[1]))
            );
        }
    }

    std::cout << "total score: " << totalScore << "\n";
}

void tokenise_line(std::string currentLine, char *tokens)
{
    tokens[0] = currentLine[0];
    tokens[1] = currentLine[2];
}

int get_round_score(int token1, int token2)
{
    if(token1 == token2)
        return token2 + 3;
    
    switch(token1)
    {
        case 1:
            if(token2 == 2)
                return token2 + WIN_SCORE;
            else if(token2 == 3)
                return token2 + LOSE_SCORE;
            break;
        case 2:
            if(token2 == 1)
                return token2 + LOSE_SCORE;
            else if(token2 == 3)
                return token2 + WIN_SCORE;
            break;
        case 3:
            if(token2 == 1)
                return token2 + WIN_SCORE;
            else if(token2 == 2)
                return token2 + LOSE_SCORE;
            break;
        default:
            return -1;
    }

    return -1;
}

int get_int_value(char token)
{
    if(token == 'A' || token == 'X')
        return 1;
    else if(token == 'B' || token == 'Y')
        return 2;
    else if(token == 'C' || token == 'Z')
        return 3;
    
    return -1;
}

int get_set_move(int enemyMove, int gameOutcome)
{
    if(gameOutcome == DRAW)
        return enemyMove;

    switch(enemyMove)
    {
        case ROCK:
            if(gameOutcome == LOSE)
                return SCISSORS;
            else if(gameOutcome == WIN)
                return PAPER; 
            break;
        case PAPER:
            if(gameOutcome == LOSE)
                return ROCK;
            else if(gameOutcome == WIN)
                return SCISSORS; 
            break;
        case SCISSORS:
            if(gameOutcome == LOSE)
                return PAPER;
            else if(gameOutcome == WIN)
                return ROCK; 
            break;
        default:
            break;
    }

    return -1;
}

// rock - beaten by paper but beats scissors
// paper - beats rock but beaten by scissors
// scissors - beats paper but beaten by rock