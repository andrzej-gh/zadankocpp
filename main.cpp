#include <iostream>
#include <thread>
#include <chrono>
#include "DoublyLinkedList.cpp"

#define MAX_TEXT_LEN 10
//#define DEBUG_LOGS
bool byText = false;

static inline int randomNumber()
{
	return rand();
}

static std::string randomString()
{
	static const char chars[] = "abcdefghijklmnopqrstuvwxyz"
								"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
								"01234567890";
	std::string newText = "";
	unsigned int textLen;

	textLen = rand() % MAX_TEXT_LEN + 1;

	for (int i = 0; i < textLen; i++) {
		newText += chars[rand() % sizeof(chars) - 1];
	}

	return newText;
}

void ListGeneratorThread(DoublyLinkedList* list)
{
	std::cout<<"Start ListGeneratorThread" << std::endl;

	srand( (unsigned) time(NULL) * getpid());

	while(list->getNumberOfElements() < 100) {
		list->addEntry(randomString(), randomNumber());
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	
	std::cout<<"Exit ListGeneratorThread" << std::endl;
}

void ListSortThread(DoublyLinkedList* list)
{
	unsigned int sorted = 0;
	unsigned int elements = 0;

	std::cout<<"Start ListSortThread" << std::endl;

	while(sorted < 100) {
		if (elements - sorted >= 10) {
			std::cout<<"Sorting First " << elements << " Elements." << std::endl;
			list->sortList();
#ifdef DEBUG_LOGS
			list->printList();
#endif
			sorted = elements;
		}
		elements = list->getNumberOfElements();
	}

	std::cout<<"Exit ListSortThread" << std::endl;
}

int main() {

	DoublyLinkedList* list = new DoublyLinkedList("Moja Lista", byText);
	std::thread generator(ListGeneratorThread, list);
	std::thread sorter(ListSortThread, list);

	generator.join();
	sorter.join();

	list->printList();

	delete list;
	return 0;
}
