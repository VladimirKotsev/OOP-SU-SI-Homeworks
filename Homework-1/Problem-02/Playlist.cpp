#include <iostream>

#include "Playlist.h"
#include "GlobalConstants.h"
#include "Utility.h"

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

const Song Playlist::findSongByName(const char* name) const
{
	for (size_t i = 0; i < this->songsCount; i++)
	{
		if (strcmp(this->songs[i].getName(), name) == 0)
		{
			this->songs[i].print();
			return this->songs[i];
		}
	}

	std::cout << "Song not found!" << std::endl;
	return Song();
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
			{
				this->songs[i].print();
				songs[index++] = this->songs[i];
			}
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
	Song song = this->findSongByName(name);
	if (strcmp(song.getName(), (char*)"\0") == 0)
	{
		std::cout << ErrorMessages::SONG_NAME_INVALID;
		return;
	}

	const char* notes = song.getNotes();
	char* newNotes = new char[GlobalConstants::BUFFER_SIZE + 1];
	unsigned index = 0;
	while (*notes)
	{
		char max = *notes | (1 << k);
		*notes++;
		newNotes[index++] = max;
	}

	newNotes[index] = '\0';
	song.setNotes(newNotes);
	delete[] newNotes;
}
void Playlist::mixSongs(const char* songName1, const char* songName2)
{
	Song song1 = this->findSongByName(songName1);
	Song song2 = this->findSongByName(songName2);
	if (strcmp(song1.getName(), (char *)"\0") == 0 && strcmp(song2.getName(), (char*)"\0") == 0)
	{
		std::cout << ErrorMessages::SONG_NAME_INVALID;
		return;
	}

	unsigned index= 0;
	const char* s1Notes = song1.getNotes();
	const char* s2Notes = song2.getNotes();
	char* notesToSave = new char[GlobalConstants::BUFFER_SIZE + 1];
	while (*(s1Notes + index) && *(s2Notes + index))
	{
		int mask = (int)(*(s1Notes + index)) ^ (int)(*(s2Notes + index));
		notesToSave[index] = (char)mask;

		index++;
	}
	notesToSave[index] = '\0';
	std::cout << notesToSave;
	song1.setNotes(notesToSave);
	delete[] notesToSave;
}

const void Playlist::saveContentToFile(const char* songName, const char* fileName)
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open() || !songName)
		return;
	Song song = this->findSongByName(songName);
	ofs.write(song.getNotes(), strlen(song.getNotes()));
	ofs.close();
}