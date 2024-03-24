#include <iostream>

#include "Song.h"
#include "Utility.h"

const void Song::printGenres() const
{
	for (size_t i = 0; i < GlobalConstants::MAX_GENRES_PER_SONG; i++)
	{
		switch (this->getGenres()[i])
		{
		case Genre::HIPHOP:
			if (i > 0 && i != GlobalConstants::MAX_GENRES_PER_SONG - 1)
				std::cout << '&';

			std::cout << "HipHop";
			break;
		case Genre::ROCK:
			if (i > 0 && i != GlobalConstants::MAX_GENRES_PER_SONG - 1)
				std::cout << '&';

			std::cout << "Rock";
			break;
		case Genre::ELECTRO: 
			if (i > 0 && i != GlobalConstants::MAX_GENRES_PER_SONG - 1)
				std::cout << '&';

			std::cout << "Electro"; 
			break;
		case Genre::POP: 
			if (i > 0 && i != GlobalConstants::MAX_GENRES_PER_SONG - 1)
				std::cout << '&';
			
			std::cout << "Pop"; 
			break;
		case Genre::JAZZ: 
			if (i > 0 && i != GlobalConstants::MAX_GENRES_PER_SONG - 1)
				std::cout << '&';

			std::cout << "Jazz"; 
			break;
		default: std::cout << std::endl; return;
		}
	}
	std::cout << std::endl;
}

Song::Song(const char* name, unsigned hours, unsigned minutes, unsigned seconds, char* genres)
{
	setName(name);
	setDuration(hours, minutes, seconds);
	setGenre(genres);
}

const char* Song::getName() const
{
	return this->name;
}
const Time Song::getDuration() const
{
	return this->duration;
}
const Genre* Song::getGenres() const
{
	Genre genres[GlobalConstants::MAX_GENRES_PER_SONG];
	unsigned index = 0;
	char genre = this->genre;

	if (((int)genre | GlobalConstants::ROCK_GENRE_NUMBER) == (int)genre)
		genres[index++] = Genre::ROCK;
	if (((int)genre | GlobalConstants::POP_GENRE_NUMBER) == (int)genre)
		genres[index++] = Genre::POP;
	if (((int)genre | GlobalConstants::HIPHOP_GENRE_NUMBER) == (int)genre)
		genres[index++] = Genre::HIPHOP;
	if (((int)genre | GlobalConstants::ELECTRO_GENRE_NUMBER) == (int)genre)
		genres[index++] = Genre::ELECTRO;
	if (((int)genre | GlobalConstants::JAZZ_GENRE_NUMBER) == (int)genre)
		genres[index++] = Genre::JAZZ;

	return genres;
}
const char* Song::getNotes() const
{
	return this->notes;
}

void Song::setName(const char* name)
{
	if (!name)
	{
		std::cout << ErrorMessages::SONG_NAME_INVALID;
		strcpy_s(this->name, ErrorMessages::UNKNOWN_SONG_NAME);
		return;
	}

	strcpy_s(this->name, name);
}
void Song::setDuration(unsigned hours, unsigned minutes, unsigned seconds)
{
	this->duration = Time(hours, minutes, seconds);
}
void Song::setGenre(char* genre)
{
	int number = 0;
	while (*genre)
	{
		if (*genre == 'r')
			number += GlobalConstants::ROCK_GENRE_NUMBER;
		else if (*genre == 'p')
			number += GlobalConstants::POP_GENRE_NUMBER;
		else if (*genre == 'h')
			number += GlobalConstants::HIPHOP_GENRE_NUMBER;
		else if (*genre == 'e')
			number += GlobalConstants::ELECTRO_GENRE_NUMBER;
		else if (*genre == 'j')
			number += GlobalConstants::JAZZ_GENRE_NUMBER;

		genre++;
	}

	this->genre = (char)number;
}
void Song::setNotes(char* notes)
{
	size_t len = strlen(notes);
	if (len == 0)
		notes = NULL;
	else
		strcpy_s(this->notes, notes);
}

void Song::readContentFromFile(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs.is_open())
	{
		setNotes((char*)"\0");
		return;
	}

	char* buffer = new char[GlobalConstants::BUFFER_SIZE + 1];
	size_t fileSize = getFileSize(ifs);
	ifs.read(buffer, fileSize);
	ifs.close();

	buffer[fileSize] = '\0';
	this->setNotes(buffer);
	delete[] buffer;
}
size_t Song::getFileSize(std::ifstream& file)
{
	size_t currentPos = file.tellg();

	file.seekg(0, std::ios::end);
	size_t size = file.tellg();

	file.seekg(currentPos);
	return size;
}

const void Song::print() const //име, продължителност във формат часове:минути:секунди и жанр
{
	std::cout << "Song: " << this->getName() << ", ";
	this->duration.print();
	std::cout << ", ";
	this->printGenres();
}


