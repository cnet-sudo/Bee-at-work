#include "Engine.h"


int main()
{   
    auto game = std::make_unique<Engine>();
    game->run();
    return 0;
}

