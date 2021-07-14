## LIBRARY MANAGEMENT SYSTEM

# Overview

The Library management system (LMS) manages all the books in a given directory.
	-	A library of books contains many books. Each book is stored in a text file in a given directory, which contains the library. Each book has a title, an author, a release date, and a Language.	
	-   A book can contain many types of content, e.g. a novel, a play, etc. This project implements for a novel and play, but the software design is such that other types of books can be easily added.
	-	A novel can contain many chapters. Each chapter has a title followed by
	many paragraphs. Each paragraph contains many sentences, and each sentence is a sequence of words.
	-	A play has a optional prologue followed by many acts. Each act has many scenes, and each scene is a sequence of dialogues. Additionally, a play also has a list of characters or personae, where each dialogue is spoken by a character.

# Contents

The main folder contains several parts:
	1)	Books Folder : It contains different kinds of books for testing, both Plays and Novels.
	2)	LMS.cpp : It contains the entire working code for this project.
	3)  index.txt : The LMS will maintain the type of each book in the library, in this file.

# Instructions (How to run) :

Follow the steps to run the Library Management System :
	1)  Run the file by -  g++ LMS.cpp --std=c++17
	2)	The program will start with a directory as input, and will manage the books in that directory, we have to input the directory name after changing path to parent location in LMS.cpp file.
	3)	It automatically detect all files in the directory and is able to detect the newly added books. It then asks the user for type of each of the newly added books and add them to “index.txt”.
	4)  After that user can perform different types of functionalities related to books.


END

CONTRIBUTERS - 

- Divyansh Bhatia
