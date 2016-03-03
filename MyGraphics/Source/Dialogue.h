/******************************************************************************/
/*!
\file	Dialogue.h
\author Chuan Guang Zhe
\par	email: 152104G@mymail.nyp.edu.sg
\brief
	Class to define dialogues
*/
/******************************************************************************/\
#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "SharedData.h"
#include <fstream>

/******************************************************************************/
/*!
Class Dialogue:
\brief
	Defines Dialogue and its methods
*/
/******************************************************************************/
class Dialogue
{
public:
	Dialogue();
	~Dialogue();

	void GenLine(string File);
	void RNGLine();

	int RNG;
	string Line;
};

#endif