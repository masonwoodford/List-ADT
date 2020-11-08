/*
 * File:   List.c
 * Author: Mason Woodford (mwoodfor@ucsc.edu)
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

 // private NodeObj type
typedef struct NodeObj {
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int cursor_index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object.
List newList(void) {
    List L;
    L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->cursor_index = -1;
    return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
// Pre: List != NULL
void freeList(List* pL) {
    if (*pL == NULL) {
        fprintf(stderr, "List Error: calling freeList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (pL != NULL && *pL != NULL) {
        while (length(*pL) != 0) { 
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
    return;
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
// Pre: List != NULL
int length(List L) { 
    if (L == NULL) {
        fprintf(stderr, "List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
// Pre: List != NULL
int index(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if ((L->cursor_index) < 0 || L->cursor == NULL) {
        return -1;
    }
    else {
        return L->cursor_index;
    }
}

// front()
// Returns front element of L. Pre: length()>0, List != NULL
int front(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling front() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

// back()
// Returns back element of L. Pre: length()>0, List != NULL
int back(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling back() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
// Pre: List!= NULL, length() > 0, index() >= 0 
int get(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling get() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (!(index(L) >= 0)) {
        fprintf(stderr, "List Error: calling get() on an undefined cursor element\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

// equals()
// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
// Pre: List!= NULL
int equals(List A, List B) {
    int eq = 0;
    Node N = NULL;
    Node M = NULL;

    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    eq = (A->length == B->length);
    N = A->front;
    M = B->front;
    while (eq && N != NULL)
    {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
// Pre: List!= NULL
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (!(L->length == 0)) {
        while (L->length != 0) {
            deleteFront(L);
        };
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->cursor_index = -1;
    }
    return;
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
// Pre: List!= NULL
void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        return;
    }
    L->cursor_index = 0;
    L->cursor = L->front;
    return;
}

// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
// Pre: List!= NULL
void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        return;
    }
    L->cursor_index = L->length-1;
    L->cursor = L->back;
    return;
}

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
// Pre: List!= NULL
void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor_index >= 0) {
        L->cursor_index--;
        L->cursor = L->cursor->prev;
    }
    else if (L->cursor_index == 0) {
        L->cursor_index = -1;
        L->cursor = NULL;
    }
    else if (L->cursor_index < 0  || L->cursor == NULL) {
        return;
    }
    return;
}

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
// Pre: List != NULL
void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor_index == (L->length - 1)) {
        L->cursor_index = -1;
        L->cursor = NULL;
    }
    else if (L->cursor_index >= 0 && L->cursor_index != (L->length-1)) {
        L->cursor_index++;
        L->cursor = L->cursor->next;
    }
    else if (L->cursor_index < 0 || L->cursor == NULL) {
        return;
    }
    return;
}
// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
// Pre: List!= NULL
void prepend(List L, int data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node M = newNode(data);
    if (L->length == 0) {
        L->length++;
        L->front = M;
        L->back = M;
    } else {
        if (L->cursor_index != -1) {
            L->cursor_index++;
        }
        L->length++;
        L->front->prev = M;
        M->next = L->front;
        M->prev = NULL;
        L->front = M;
    }
    return;
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
// Pre: List != NULL
void append(List L, int data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node M = newNode(data);
    if (L->length == 0) {
        L->length++;
        L->front = M;
        L->back = M;
    } else {
        L->back->next = M;
        M->prev = L->back;
        M->next = NULL;
        L->back = M;
        L->length++;
    }
    return;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0, List != NULL
void insertBefore(List L, int data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    } 
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling insertBefore() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (!(index(L) >= 0)) {
        fprintf(stderr, "List Error: calling insertBefore() on an undefined cursor element\n");
        exit(EXIT_FAILURE);
    }
    Node M = newNode(data);
    if (L->length == 1 && L->cursor_index == 0) {
        L->cursor->prev = M;
        M->next = L->cursor;
        L->front = M;
    }
    else if (L->cursor_index == 0) {
        M->next = L->front;
        L->front->prev = M;
        L->front = M;
        M->prev = NULL;
    }
    else {
        L->cursor->prev->next = M;
        M->prev = L->cursor->prev;
        L->cursor->prev = M;
        M->next = L->cursor;
    }
    L->cursor_index++;
    L->length++;
    return;
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0, List != NULL
void insertAfter(List L, int data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling insertAfter() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (!(index(L) >= 0)) {
        fprintf(stderr, "List Error: calling insertAfter() on an undefined cursor element\n");
        exit(EXIT_FAILURE);
    }
    Node M = newNode(data);
    if (L->length == 1 && L->cursor_index == 0) {
        L->cursor->next = M;
        M->prev = L->cursor;
        L->back = M;
    }
    else if (L->cursor_index == (L->length - 1)) {
        M->prev = L->back;
        L->back->next = M;
        L->back = M;
        M->next = NULL;
    }
    else {
        L->cursor->next->prev = M;
        M->next = L->cursor->next;
        M->prev = L->cursor;
        L->cursor->next = M;
    }
    L->length++;
    return;
}
// deleteFront()
// Delete the front element. Pre: length()>0, List != NULL
void deleteFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling deleteFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    Node N = NULL;
    N = L->front;
    if (L->length > 1) {
        L->front = L->front->next;
        L->front->prev = NULL;
    }
    else {
        L->front = L->back = NULL;
    }
    if (L->cursor_index <= 0) {
        L->cursor = NULL;
        L->cursor_index = -1;
    }
    else {
        L->cursor_index--;
    }
    freeNode(&N);
    L->length--;
    return;
}
// deleteBack()
// Delete the back element. Pre: length()>0, List != NULL
void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling deleteBack() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    Node N = NULL;
    N = L->back;
    if (L->length > 1) {
        L->back = L->back->prev;
        L->back->next = NULL;
    } 
    else {
        L->front = L->back = NULL;
    }
    if (L->cursor_index >= L->length - 1) {
        L->cursor = NULL;
        L->cursor_index = -1;
    }
    freeNode(&N);
    L->length--;
    return;
}
// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0, List != NULL
void delete(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List Error: calling delete() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (!(index(L) >= 0)) {
        fprintf(stderr, "List Error: calling delete() on an undefined cursor element\n");
        exit(EXIT_FAILURE);
    }
    Node N = NULL;
    N = L->cursor;
    if (L->cursor_index == 0) {
        deleteFront(L);
    }
    else if (L->cursor_index == L->length - 1) {
        deleteBack(L);
    } 
    else {
        N->next->prev = L->cursor->prev;
        N->prev->next = L->cursor->next;
        freeNode(&N);
        L->length--;
    }
    L->cursor_index = -1;
    return;
}

// Other operations -----------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
// Pre: file != NULL, List != NULL
void printList(FILE* out, List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (out == NULL) {
        fprintf(stderr, "File Error: calling printList() on NULL file pointer");
        exit(EXIT_FAILURE);
    }
    Node N = NULL;
    N = L->front;
    while (N != NULL) {
        fprintf(out, "%d ", N->data);
        N = N->next;
    }
    return;
}

// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
// Pre: List!= NULL
List copyList(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling copyList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    List Y = newList();
    Node N = NULL;
    N = L->front;
    Y->cursor_index = -1;
    while (N != NULL) {
        append(Y, N->data);
        N = N->next;
    }
    return Y;
}

// concatList()
// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "List Error: calling copyList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    List Y = newList();
    Node temp = A->front;
    while (temp != NULL) {
        append(Y, temp->data);
        temp = temp->next;
    }
    temp = B->front;
    while (temp != NULL) {
        append(Y, temp->data);
        temp = temp->next;
    }
    return Y;
}



