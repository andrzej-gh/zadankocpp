#include "Entry.h"

Entry::Entry(std::string text, int number):
	text_(text),
	number_(number)
{
#ifdef DEBUG_LOGS
	std::cout << "New Entry number = " << number << ", text = \"" << text << "\"." << std::endl;
#endif
}

int Entry::getNumber()
{
	return number_;
}

std::string Entry::getText()
{
	return text_;
}

void Entry::setNext(Entry* next)
{
	next_ = next;
}

void Entry::setPrev(Entry* prev)
{
	prev_ = prev;
}

Entry* Entry::getPrev()
{
	return prev_;
}

Entry* Entry::getNext()
{
	return next_;
}

