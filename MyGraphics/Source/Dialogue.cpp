/******************************************************************************/
/*!
\file	Dialogue.cpp
\author Chuan Guang Zhe
\par	email: 152104G@mymail.nyp.edu.sg
\brief
	Class to define Dialogues
*/
/******************************************************************************/
#include "Dialogue.h"

/******************************************************************************/
/*!
\brief
	Dialogue default constructor
*/
/******************************************************************************/
Dialogue::Dialogue()
{
	RNG = 0;
}

/******************************************************************************/
/*!
\brief
	Enemy default deconstructor
*/
/******************************************************************************/
Dialogue::~Dialogue()
{
}

/******************************************************************************/
/*!
\brief
	Randomly takes a line from the textfile

\param File
	Textfile's location / directory
*/
/******************************************************************************/
void Dialogue::GenLine(string File)
{
	RNGLine();
	int count = 0;
	std::ifstream Location(File);
	while (count <= RNG)
	{
		getline(Location, Line);
		count += 1;
	}
}

/******************************************************************************/
/*!
\brief
	Random number generator for choosing which line to take from textfile
*/
/******************************************************************************/
void Dialogue::RNGLine()
{
	RNG = (rand() % 12);
}