#include <iostream>

#include "Song.h"
#include "Time.h"
#include "Playlist.h"

int main()
{
	//Съдържание на song1.dat:
	//“V“
	//	// 0101 0110

	//	Съдържание на song2.dat :
	//	“Ua“
		// 0101 0101 0110 0001

	Playlist p;
	p.addSong("Song 1", 0, 1, 5, (char*)"p", "song1.txt");
	//p.addSong("Song 2", 0, 1, 55, (char*)"rp", "song2.txt");

	p.mixSongByBits("Song 1", 3);
	p.printAll();

	//p.printAll();
	//// Song 2, 00:01:55, Pop&Rock
	//// Song 1, 00:01:05, Pop

	//p.sortSongsByName();
	//p.printAll(); //works!!!!
	//// Song 1, 00:01:05, Pop
	//// Song 2, 00:01:55, Pop&Rock

	//p.findSongByName("Song 3"); //works!!!!
	// Song 1, 00:01:05, Pop

	//p.findSongsByGenre('p');
	// Song 1, 00:01:05, Pop
	// Song 2, 00:01:55, Pop&Rock
	//p.findSongsByGenre('r');
	// Song 2, 00:01:55, Pop&Rock

	//p.mixSongs("Song 1", "Song 2");
	//p.saveContentToFile("Song 1", "song3.dat");
	// съдържание на song3.dat: “S” //0000 0011 

}