#pragma once

#include "Song.h"
#include "GlobalConstants.h"

class Playlist
{
private:
	Song songs[GlobalConstants::MAX_SONGS_PLAYLIST];
	unsigned songsCount = 0;
	const Genre getGenreFromChar(char c) const;

	const int countTrailingZeros(unsigned char value) const;
	const int countLeadingZeros(unsigned char value) const;
	const void getNextMask(unsigned char mask, unsigned char& resultMask, int k) const;
public:
	Playlist() = default;
	void addSong(Song song);
	void addSong(const char* name, unsigned hours, unsigned minutes, unsigned seconds, char* genre, const char* fileName);
	const void printAll() const;
	Song& findSongByName(const char* name);
	const Song* findSongsByGenre(const char genre) const;
	void mixSongs(const char* songName1, const char* songName2);
	void mixSongByBits(const char* name, int k);
	void sortSongsByDuration();
	void sortSongsByName();
	const void saveContentToFile(const char* songName, const char* fileName);
};