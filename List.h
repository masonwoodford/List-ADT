/*
 * File:   List.h
 * Author: Mason Woodford (mwoodfor@ucsc.edu)
 */

 // Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object.
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
// Pre: List != NULL
void freeList(List* pL);

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
// Pre: List != NULL
int length(List L); 

// index()
// Returns index of cursor element if defined, -1 otherwise.
// Pre: List != NULL
int index(List L); 

// front()
// Returns front element of L. Pre: length()>0, List != NULL
int front(List L); 

// back()
// Returns back element of L. Pre: length()>0, List != NULL
int back(List L); 

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
// Pre: List!= NULL, length() > 0, index() >= 0 
int get(List L); 

// equals()
// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
// Pre: List!= NULL
int equals(List A, List B); 

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
// Pre: List!= NULL
void clear(List L); 

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
// Pre: List!= NULL
void moveFront(List L); 

// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
// Pre: List!= NULL
void moveBack(List L); 

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
// Pre: List!= NULL
void movePrev(List L); 

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
// Pre: List != NULL
void moveNext(List L); 

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
// Pre: List!= NULL
void prepend(List L, int data); 
								
// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
// Pre: List != NULL
void append(List L, int data); 

// Insert new element before cursor.
// Pre: length()>0, index()>=0, List != NULL
void insertBefore(List L, int data); 
										 
// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0, List != NULL									
void insertAfter(List L, int data); 

// deleteFront()
// Delete the front element. Pre: length()>0, List != NULL
void deleteFront(List L); 

// deleteBack()
// Delete the back element. Pre: length()>0, List != NULL
void deleteBack(List L); // Delete the back element. Pre: length()>0

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0, List != NULL
void delete(List L); 

// Other operations -----------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
// Pre: file != NULL, List != NULL
void printList(FILE* out, List L); 

// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
// Pre: List!= NULL								
List copyList(List L); 

//concatList()
// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B); 

