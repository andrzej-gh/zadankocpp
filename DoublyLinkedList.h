#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

class DoublyLinkedList
{
	public:
		DoublyLinkedList(std::string name, bool byText);
		~DoublyLinkedList();
		void addEntry(std::string text, int number);
		unsigned int getNumberOfElements();
		void printList();
		void sortList();

	protected:
		bool isFirst(Entry* entry);
		bool isLast(Entry* entry);
		bool isEmpty();
		
		unsigned int numberOfElements_ = 0;
		Entry* first_ = nullptr;
		Entry* last_ = nullptr;
		Entry* cur_ = nullptr;
		std::string name_;
		std::mutex mutex_;
		bool byText_;
};

#endif

