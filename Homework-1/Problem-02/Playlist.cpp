#include <iostream>

#include "Playlist.h"
#include "GlobalConstants.h"
#include "Utility.h"

const int Playlist::countTrailingZeros(unsigned char value) const
{
	int count = 0;
	while ((value & 1) == 0)
	{
		++count;
		value >>= 1;
	}
	return count;
}

const int Playlist::countLeadingZeros(unsigned char value) const
{
	int count = 0;
	while ((value & (1 << 7)) == 0)
	{
		++count;
		value <<= 1;
	}
	return count;
}

const void Playlist::getNextMask(unsigned char mask, unsigned char &resultMask, int k) const
{
	resultMask = 1 << k - 1;
	for (size_t i = 0; i < 8; i++)
	{
		resultMask <<= 1;
		resultMask |= 1;
		resultMask <<= k - 1;
	}

	int leadingZeros = countLeadingZeros(mask);
	for (size_t i = 0; i < 8; i++)
	{
		int trailingZeros = countTrailingZeros(resultMask);

		if (leadingZeros + trailingZeros == k - 1)
			break;

		resultMask <<= 1;
		if (trailingZeros + 1 == k)
			resultMask |= 1;
	}
}

const Genre Playlist::getGenreFromChar(char c) const
{
	Genre genre;
	switch (c)
	{
	case 'r': genre = Genre::ROCK; break;
	case 'h': genre = Genre::HIPHOP; break;
	case 'j': genre = Genre::JAZZ; break;
	case 'e': genre = Genre::ELECTRO; break;
	case 'p': genre = Genre::POP; break;
	}

	return genre;
}

void Playlist::addSong(Song song)
{
	this->songs[this->songsCount++] = song;
}
void Playlist::addSong(const char* name, unsigned hours, unsigned minutes, unsigned seconds, char* genre, const char* fileName)
{
	char* notes = new char[GlobalConstants::BUFFER_SIZE];
	Song song(name, hours, minutes, seconds, genre); //inner validation

	song.readContentFromFile(fileName);
	this->addSong(song);
}

const void Playlist::printAll() const
{
	for (size_t i = 0; i < this->songsCount; i++)
		this->songs[i].print();
}

Song& Playlist::findSongByName(const char* name)
{
	if (!name)
	{
		std::cout << ErrorMessages::SONG_NAME_INVALID << std::endl;
		Song song;
		return song;
	}
	for (size_t i = 0; i < this->songsCount; i++)
	{
		if (strcmp(this->songs[i].getName(), name) == 0)
			return this->songs[i];
	}

	std::cout << ErrorMessages::UNKNOWN_SONG << std::endl;
	Song song;
	return song;
}
const Song* Playlist::findSongsByGenre(const char genre) const
{
	Song songs[GlobalConstants::MAX_SONGS_PLAYLIST];
	unsigned index = 0;

	for (size_t i = 0; i < this->songsCount; i++)
	{
		for (size_t j = 0; j < GlobalConstants::MAX_GENRES_PER_SONG; j++)
		{
			int currGenre = (int)this->songs[i].getGenres()[j];
			int genreToFind = (int)this->getGenreFromChar(genre);
			if (currGenre == genreToFind)
				songs[index++] = this->songs[i];
		}
	}
	return songs;
}

void Playlist::sortSongsByDuration()
{
	for (int i = 1; i < this->songsCount; i++)
	{
		Song currentElement = this->songs[i];
		int currentIndex = i - 1;
		while (currentIndex >= 0 && this->songs[currentIndex].getDuration().getTimeInSeconds() > currentElement.getDuration().getTimeInSeconds())
		{
			this->songs[currentIndex + 1] = this->songs[currentIndex];
			currentIndex--;
		}
		this->songs[currentIndex + 1] = currentElement;
	}
}
void Playlist::sortSongsByName()
{
	for (int i = 1; i < this->songsCount; i++)
	{
		Song currentElement = this->songs[i];
		int currentIndex = i - 1;
		while (currentIndex >= 0 && (strcmp(this->songs[currentIndex].getName(), currentElement.getName()) > 0))
		{
			this->songs[currentIndex + 1] = this->songs[currentIndex];
			currentIndex--;
		}
		this->songs[currentIndex + 1] = currentElement;
	}
}
void Playlist::mixSongByBits(const char* name, int k)
{
	if (!name)
	{
		std::cout << ErrorMessages::SONG_NAME_INVALID;
		return;
	}
	Song& song = this->findSongByName(name);
	const char* currNotes = song.getNotes();
	size_t notesLength = strlen(currNotes);

	char* result = new char[notesLength + 1];
	unsigned char mask = 1 << k - 1;
	for (size_t i = 0; i < GlobalConstants::BIT_SIZE; i++)
	{
		mask <<= 1;
		mask |= 1;
		mask <<= k - 1;
	}

	currNotes += notesLength - 1;
	int index = 0;
	while (index < notesLength)
	{
		char c = *currNotes;

		result[index] = c | mask;
		
		this->getNextMask(mask, mask, k);

		index++;
		currNotes--;
	}

	for (size_t i = 0; i < notesLength / 2; i++)
	{
		std::swap(result[i], result[notesLength - i - 1]);
	}

	result[index] = '\0';

	song.setNotes(result);
	delete[] result;
}
void Playlist::mixSongs(const char* songName1, const char* songName2)
{
	if (!songName1 || !songName2)
		return;

	Song& first = this->findSongByName(songName1);
	const Song second = this->findSongByName(songName2);

	const char* song1Notes = first.getNotes();
	const char* song2Notes = second.getNotes();

	char* result = new char[GlobalConstants::SONG_NOTES_MAX + 1];
	int currentIndex = 0;

	while ((*song1Notes) && (*song2Notes))
	{
		char firstSymbol = *song1Notes;
		char secondSymbol = *song2Notes;

		int mask = (int)firstSymbol ^ (int)secondSymbol;
		result[currentIndex++] = (int)firstSymbol ^ (int)secondSymbol;

		song1Notes++;
		song2Notes++;
	}

	while ((*song1Notes))
	{
		result[currentIndex++] = *song1Notes;
		song1Notes++;
	}
	result[currentIndex] = '\0';

	first.setNotes(result);
	delete[] result;
}

const void Playlist::saveContentToFile(const char* songName, const char* fileName)
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open() || !songName)
		return;

	Song song = this->findSongByName(songName);
	const char* notes = song.getNotes();
	ofs.write(notes, strlen(notes));
	ofs.close();
}