#include <iostream>
#include <mutex>
#include "Entry.cpp"
#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList(std::string name, bool byText):
	name_(name),
	byText_(byText)
{
#ifdef DEBUG_LOGS
	std::cout<<"Created New List Name = \"" << name << "\"."<< std::endl;
#endif
}

unsigned int DoublyLinkedList::getNumberOfElements()
{
	return numberOfElements_;
}

DoublyLinkedList::~DoublyLinkedList()
{
	Entry* next;

	cur_ = first_;
	while (cur_ != nullptr) {
		next = cur_->getNext();
		delete cur_;
		numberOfElements_--;
		cur_ = next;
	}
}

void DoublyLinkedList::printList()
{
	const std::lock_guard<std::mutex> lock(mutex_);

	unsigned int i = 1;
	std::cout << "******************************************************************" << std::endl;
	std::cout << "List \"" << name_ << "\" has " << numberOfElements_ << " Elements." << std::endl;
	std::cout << "******************************************************************" << std::endl;
	for (cur_ = first_; cur_ != nullptr; cur_ = cur_->getNext(), i++) {
		if(byText_) {
			std::cout << "Entry #" << i << ": Text = \"" << cur_->getText() << "\", Number = " << cur_->getNumber() << "." << std::endl;
		} else {
			std::cout << "Entry #" << i << ": Number = " << cur_->getNumber() << ", Text = \"" << cur_->getText() << "\"." << std::endl;
		}
	}
	std::cout << "******************************************************************" << std::endl;
}

void DoublyLinkedList::sortList()
{
	const std::lock_guard<std::mutex> lock(mutex_);
	if (first_ != nullptr && first_->getNext() != nullptr) {
		for (Entry* i = first_; i != nullptr; i = i->getNext()) {
			for (Entry* j = first_->getNext(); j != nullptr; j = j->getNext()) {
				Entry* leftElement = j->getPrev();
				Entry* rightElement = j;
				if ((leftElement->getNumber() > rightElement->getNumber() && !byText_) ||
					((leftElement->getText()).compare(rightElement->getText()) > 0 && byText_)) {
					Entry* tempElement = leftElement->getPrev();
					if (isFirst(leftElement)) {
						first_ = rightElement;
					} else {
						leftElement->getPrev()->setNext(rightElement);
					}
					if (isLast(rightElement)) {
						last_ = leftElement;
					} else {
						rightElement->getNext()->setPrev(leftElement);
					}
					leftElement->setNext(rightElement->getNext());
					leftElement->setPrev(rightElement);
					rightElement->setNext(leftElement);
					rightElement->setPrev(tempElement);
				}
			}
		}
	}
}

bool DoublyLinkedList::isEmpty()
{
	return (first_ == nullptr);
}

bool DoublyLinkedList::isFirst(Entry* entry)
{
	return (entry == first_);
}

bool DoublyLinkedList::isLast(Entry* entry)
{
	return (entry == last_);
}

void DoublyLinkedList::addEntry(std::string text, int number)
{
	const std::lock_guard<std::mutex> lock(mutex_);

	Entry* newEntry = new Entry(text, number);

	if(this->isEmpty()) {
		first_ = newEntry;
		cur_ = newEntry;
		last_ = newEntry;
	} else {
		last_->setNext(newEntry);
		newEntry->setPrev(last_);
		last_ = newEntry;
		cur_ = last_;
	}
	numberOfElements_++;
}

