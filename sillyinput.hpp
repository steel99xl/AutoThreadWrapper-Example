#pragma once
#include <cstring>

namespace sillyinput{

inline std::string UserInput(){
    std::string userinput;
    std::cout << "# ";
    std::cin >> userinput;
    return userinput;
}

inline std::string UserAutoCap(){
    std::string userinput;

    std::cout << "# ";
    std::cin >> userinput;

    for(char & i : userinput){
        i = toupper(i);
    }

    return userinput;
}

};