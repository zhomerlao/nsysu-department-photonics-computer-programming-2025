#include <stdio.h>
#include <stdlib.h>

/*
 * Circular Doubly Linked List with:
 * - integer data
 * - prev & next pointers
 * - current pointer
 * - total length stored
 */

/* Node definition */
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

/* List controller */
typedef struct {
    Node *head;
    Node *current;
    int length;
} LinkedList;

/* Create an empty circular list */
LinkedList* createList() {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for LinkedList.\n");
        return NULL;
    }
    list->head = NULL;
    list->current = NULL;
    list->length = 0;
    return list;
}


/* Insert a new node AFTER the current node */
void insertElement(LinkedList *list, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;

    if (list->length == 0) {
        // First node: points to itself
        newNode->next = newNode;
        newNode->prev = newNode;
        list->head = list->current = newNode;
    } else {
        Node *cur = list->current;
        Node *nextNode = cur->next;

        // Insert between cur and cur->next
        newNode->next = nextNode;
        newNode->prev = cur;
        cur->next = newNode;
        nextNode->prev = newNode;

        // If inserting after tail (current == tail), update tail?  
        // We track only head, so no need for separate tail pointer.
    }

    list->length++;
    list->current = newNode;
}

/* Remove the current node */
void removeElement(LinkedList *list) {
    if (list->length == 0 || list->current == NULL)
        return;

    Node *rm = list->current;

    if (list->length == 1) {
        // Last element
        list->head = NULL;
        list->current = NULL;
        free(rm);
        list->length = 0;
        return;
    }

    Node *prevNode = rm->prev;
    Node *nextNode = rm->next;

    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    // Update head if needed
    if (rm == list->head)
        list->head = nextNode;

    // Move current
    list->current = nextNode;

    free(rm);
    list->length--;
}

/* Move current pointer 
 * direction = 1 → next
 * direction = -1 → prev
 * Always possible because circular
 */
void moveCurrent(LinkedList *list, int direction) {
    if (list->current == NULL) return;

    if (direction == 1)
        list->current = list->current->next;
    else if (direction == -1)
        list->current = list->current->prev;
}

/* Print entire circular list */
void printList(LinkedList *list) {
    if (list->length == 0) {
        printf("List (length=0): <empty>\n");
        return;
    }

    printf("List (length=%d): ", list->length);

    Node *temp = list->head;
    do {
        if (temp == list->current)
            printf("[%d]* ", temp->data);
        else
            printf("%d ", temp->data);

        temp = temp->next;
    } while (temp != list->head);

    printf("\n");
}

int main() {
    LinkedList *list = createList();

    insertElement(list, 10);
    insertElement(list, 20);
    insertElement(list, 30);
    printList(list);

    moveCurrent(list, 1);
    printList(list);
    insertElement(list, 99);
    printList(list);

    removeElement(list);
    printList(list);

    moveCurrent(list, -1);
    printList(list);

    return 0;
}
