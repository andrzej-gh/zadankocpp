#ifndef ENTRY_H
#define ENTRY_H

class Entry
{
	public:
		Entry(std::string text, int number);

		void setNext(Entry* next);
		void setPrev(Entry* prev);
		std::string getText();
		Entry* getNext();
		Entry* getPrev();
		int getNumber();

	protected:
		Entry* next_ = nullptr;
		Entry* prev_ = nullptr;
		std::string text_;
		int number_;
};

#endif

