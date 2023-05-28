#include <stdio.h>
#include <stdlib.h>

// Struktura węzła listy
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Funkcja do wstawiania elementu na początek listy
void insertAtBeginning(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
    printf("Inserted %d at the beginning\n", value);
}

// Funkcja do wyświetlania zawartości listy w przód
void displayForward(struct Node* head) {
    printf("Linked List Forward: ");
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Funkcja do wyświetlania zawartości listy w tył
void displayBackward(struct Node* tail) {
    printf("Linked List Backward: ");
    struct Node* current = tail;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

// Funkcja główna
int main() {
    struct Node* head = NULL; // Inicjalizacja głowy listy jako NULL

    // Wstawianie elementów do listy
    insertAtBeginning(&head, 10);
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 30);

    // Wyświetlanie zawartości listy w przód
    displayForward(head);

    // Wyświetlanie zawartości listy w tył
    struct Node* tail = NULL;
    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    tail = current;
    displayBackward(tail);

    return 0;
}
