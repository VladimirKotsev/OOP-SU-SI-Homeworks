#pragma once
#include <cstdint>

#include "GlobalConstants.h"
#include "Enums.h"
#include "Time.h"

class Song
{
private:
    char name[GlobalConstants::SONG_NAME_MAX + 1] = "\0";
    Time duration;
    unsigned char genre = 0;
    char notes[GlobalConstants::SONG_NOTES_MAX + 1] = "\0";

    const void printGenres() const;
public:
    Song() = default;
    Song(const char* name, unsigned hours, unsigned minutes, unsigned seconds, char* genres);

    const char* getName() const;
    const Time getDuration() const;
    const Genre* getGenres() const;
    const char* getNotes() const;

    void setName(const char* name);
    void setDuration(unsigned hours, unsigned minutes, unsigned seconds);
    void setGenre(char* genre);
    void setNotes(char* notes);

    void readContentFromFile(const char* fileName);
    size_t getFileSize(std::ifstream& file);

    const void print() const;
};