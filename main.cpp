#include <iostream>
#include <random>
#include <array>

//this function checks if the str is in the appropriate form
bool checkAppropriate(std::string str)
{
    if(str.length() != 4) return false;//check if it has four characters
    else
    {
        for(int i = 0; i < 4; i++)
        {
            if('0' <= str[i] && str[i] <= '9')//check if it is a number
                continue;
            else return false;
        }
    }
    return true;
}

//this function compares answer and guess
//returned array will contain the number of strikes and balls
std::array<unsigned int, 2> compareAnswerGuess(std::array<char, 4> answer, std::string guess)
{
    unsigned int strike = 0;
    unsigned int strike_plus_ball = 0;
    unsigned int ball = 0;

    //check for strikes
    for(int i = 0; i < 4; i++)
    {
        if(answer[i] == guess[i]) strike++;
    }
    //check for strikes and balls
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(answer[j] == guess[i]) strike_plus_ball++;
        }
    }

    ball = strike_plus_ball - strike;

    return std::array<unsigned int, 2>{strike, ball};
}

int main()
{
    //make random_device object to get seed value.
    std::random_device rd;
    //initialize random number generator via random_device
    std::mt19937 gen(rd());
    //set the distribution which you want to use
    std::uniform_int_distribution<int> dis(0, 9);

    //four numbers that player will guess about
    //it must have four distinct values
    std::array<char, 4> answer;
    for(int i = 0; i < 4; i++)
    {
        int tmp = dis(gen);
        answer[i] = tmp +'0';

        for(int j = 0; j < i; j++)
        {
            if(answer[j] == tmp)
            {
                i--;//it's okay, since we will break the loop directly after decreasing i
                break;
            }
        }
    }

    //tell the player to guess the number
    //player will have limited guessing chances
    const unsigned int chances = 10;
    std::string guess;

    for(int i = 0; i < chances; i++)
    {
        std::cout << "guess the number!(" << chances - i << " times left): "; 
        std::cin >> guess;
        if(checkAppropriate(guess))
        {
            auto SB = compareAnswerGuess(answer, guess);
            std::cout << SB[0] << "S" << SB[1] << "B" << std::endl;

            if(SB[0] == 4)
            {
                std::cout << "You've won the game!!" << std::endl;
                break;
            }
        }
        else
        {
            std::cout << "Please write in correct form. Four numbers!" << std::endl;
        }
    }
    


    return 0;
}