#include "LinkedList.hpp"

template <typename T>

/*
* Default Constructor: Initializes the private variables to 0 or empty.
 */
LinkedList<T>::LinkedList() {
	// initializing the private variables to 0/empty.
	head = nullptr;
	count = 0;
}

template <typename T>
/* This is the copy constructor. It make a copy of the parameter.  It is also used by the operator= in the copy-swap paradigm.
	@param rhs - the LinkedList we are copying during construction
   */
LinkedList<T>::LinkedList(const LinkedList& rhs) {
	this->count = rhs.count;
	Node<T>* newNode = rhs.head;

	// if newNode isn't a null pointer
	if (newNode != nullptr) {
		head = new Node<T>(newNode->getItem(), newNode->getNext());
		newNode = newNode->getNext();
		Node<T>* pointyBoy = this->head;

		// while it still continues
		while (newNode != nullptr) {
			Node<T>* nextPointyBoy = new Node<T>(newNode->getItem(), newNode);
			pointyBoy->setNext(nextPointyBoy);
			pointyBoy = pointyBoy->getNext();
			newNode = newNode->getNext();
		}
	}

	// if it is a nullptr, then make the head the nullptr.
	else {
		this->head = nullptr;
	}
}

/*
* Destructor. Destroys the object that the constructor creates after running by using the 'clear()' function
*/
template <typename T>
LinkedList<T>::~LinkedList() {
	clear();
}

/** Sees whether this list is empty.
	@return  True if the list is empty; otherwise returns false.
   */
template <typename T>
bool LinkedList<T>::isEmpty() const {
	// if count is 0, then list is empty
	return (count == 0);
}

/** Gets the current number of entries in this list.
	@return  The integer number of entries currently in the list.
   */
template <typename T>
int LinkedList<T>::getLength() const {
	// returns the count of nodes, which is infact the length
	return count;
}

/** Inserts an entry into this list at a given position.
	@pre None.
	@post  If 1 <= position <= getLength() + 1 and the insertion is
		successful, newEntry is at the given position in the list,
		other entries are renumbered accordingly, and the returned
		value is true.
	@param newPosition  The list position at which to insert newEntry.
	@param newEntry  The entry to insert into the list.
	@return  True if the insertion is successful, or false if not.
   */
template <typename T>
bool LinkedList<T>::insert(int newPosition, const T& newEntry) {
	// checking post condition
	if ((1 <= newPosition) && (newPosition <= (getLength() + 1))) {
		// if element is added at position 1
		if (newPosition == 1) {
			Node<T>* newNode = new Node<T>(newEntry, this->head);	// create new node at head
			this->count++;	// increase count as node is added
			this->head = newNode;	// this new node is added at the first position
			return true;
		}

		// if element is added to an empty list
		else if (this->isEmpty()) {
			Node<T>* newNode = new Node<T>(newEntry, nullptr); // create new node at pos 0
			this->count++; // increase count to 1
			this->head = newNode; // this new node is added at the first position
			return true;
		}

		// in any other condition
		else {
			// set previous node to the node before it, and the new node at the original position of the previous node.
			Node<T>* prevNode = this->getNodeAt(newPosition - 1);
			Node<T>* newNode = new Node<T>(newEntry, prevNode->getNext());
			// set this node to the specific position
			prevNode->setNext(newNode);
			this->count++;
			return true;
		}
	}

	// if condition doesn't match
	else
	{
		return false;
	}
}

/** Removes the entry at a given position from this list.
	@pre  None.
	@post  If 1 <= position <= getLength() and the removal is successful,
		the entry at the given position in the list is removed, other
		items are renumbered accordingly, and the returned value is true.
	@param position  The list position of the entry to remove.
	@return  True if the removal is successful, or false if not.
   */
template <typename T>
bool LinkedList<T>::remove(int position) {

	// post condition check
	if (!((position <= this->getLength()) && (position >= 1)))
	{
		return false;
	}

	// if node is being added at the first position
	if (position == 1) {
		Node<T>* newNode = this->head;
		this->head = this->head->getNext();
		this->count--;
		delete newNode;
		return true;
	}

	// if its empty
	else if (this->isEmpty()) {
		return false;
	}

	// otherwise if it is any other position
	else {
		Node<T>* prevNode = this->getNodeAt(position - 1);
		Node<T>* currNode = this->getNodeAt(position);
		Node<T>* nextNode = this->getNodeAt(position + 1);
		prevNode->setNext(nextNode);
		// decrease the length
		this->count--;
		delete currNode;
		return true;
	}
}

/** Removes all entries from this list.
	@post  The list contains no entries and the count of items is 0.
   */
template <typename T>
void LinkedList<T>::clear() {
	// using a while loop to check till isnt empty
	while (!(this->isEmpty())) {
		this->remove(1);
	}
}

/** Gets the entry at the given position in this list.
	@pre  1 <= position <= getLength().
	@post  The desired entry has been returned.
	@param position  The list position of the desired entry.
	@return  The entry at the given position.
   */
template <typename T>
T LinkedList<T>::getEntry(int position) const {
	if ((1 <= position) && (position <= getLength() + 1))
		return (this->getNodeAt(position)->getItem());

	else
		// throw exception
		throw std::logic_error("Sin Suerte");
}

/** Sets the entry at the given position in this list with the new value.
	@pre  1 <= position <= getLength().
	@post  The value at the given position has new value
	@param position  The list position of the entry to set the new value
	@param newVAlue  The new value to set at the givien position.
	@return  The replaced entry.
   */
template <typename T>
T LinkedList<T>::setEntry(int position, const T& newValue) {
	if ((1 <= position) && (position <= getLength() + 1)) {
		T tempHolder = this->getNodeAt(position)->getItem();
		this->getNodeAt(position)->setItem(newValue);
		return tempHolder;
	}
	else
		//throw exception
		throw std::logic_error("Sin Suerte");
}

/**This is the swap method. It will swap the internals of the two lists.  Notably it is used in the operator= to implement the copy swap paradigm.  It is also used by other C++ paradigms.
	 @param lhs - the LinkedList on the left...Left Hand Side (lhs)
	 @param rhs - the LinkedList on the right...Right Hand Side (rhs)
   */
template <typename T>
void LinkedList<T>::swap(LinkedList& lhs, LinkedList& rhs) {
	// swapping variables with a temp 3rd variable.
	LinkedList<T> swapper = rhs;
	rhs = lhs;
	lhs = swapper;
}

/** Locates a specified node in this linked list.
	 @pre  position is the number of the desired node;
		   position >= 1 and position <= itemCount.
	 @post  The node is found and a pointer to it is returned.
	 @param position  The number of the node to locate.
	 @return  A pointer to the node at the given position.
	*/
template <typename T>
Node<T>* LinkedList<T>::getNodeAt(int position) const {
	//checking pre condition
	if ((position >= 1) && (position <= this->count)) {
		Node<T>* currNodePtr = this->head;
		int x = 1;

		// while the current node isn't null
		while (currNodePtr != nullptr) {
			if (x == position)
				break;
			currNodePtr = currNodePtr->getNext();
			// increase current position
			x++;
		}
		return currNodePtr;
	}
	// else if condition isn't matched
	else
		return nullptr;
}


template <typename T>

/** This is the assignment operator. It uses the copy-swap paradigm to create a copy of the parameter
	@param rhs - the LinkedList we are assigning to this
	@return a reference to the list that was copied into, a.k.a. *this
   */

   //implementation is similar to copy constructor
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> rhs) {
	this->count = rhs.count;
	Node<T>* newNode = rhs.head;

	// if newNode isn't nullPtr
	if (newNode != nullptr) {
		head = new Node<T>(newNode->getItem(), newNode->getNext());
		newNode = newNode->getNext();
		Node<T>* pointyBoy = this->head;
		// while this continues
		while (newNode != nullptr) {
			Node<T>* nextPointyBoy = new Node<T>(newNode->getItem(), newNode);
			pointyBoy->setNext(nextPointyBoy);
			pointyBoy = pointyBoy->getNext();
			newNode = newNode->getNext();
		}
	}

	// if it isn't
	else {
		this->head = nullptr;
	}
	// return the class object
	return *this;
}

