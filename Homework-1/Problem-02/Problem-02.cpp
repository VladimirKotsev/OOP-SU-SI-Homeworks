#include <iostream>

namespace GlobalConstants
{
    unsigned const SONG_NAME_MAX = 64;
}

class Song
{
    char name[GlobalConstants::SONG_NAME_MAX];
    int length;

};

int main()
{
    
}