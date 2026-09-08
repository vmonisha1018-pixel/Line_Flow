#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 200


typedef struct Node
{
    char text[MAX_LENGTH];
    struct Node *prev;
    struct Node *next;
} Node;

Node *head = NULL;
Node *tail = NULL;
int lineCount = 0;

Node *findLine(int position);
void insertLine();
void deleteLine();
void displayDocument();
void replaceText();
void freeDocument();

int main()
{
    char command;

    printf("===== LINEFLOW =====\n");
    printf("i - Insert line\n");
    printf("d - Delete line\n");
    printf("p - Display document\n");
    printf("r - Replace text\n");
    printf("q - Quit\n");

    while (1)
    {
        printf("\nEnter command: ");
        scanf(" %c", &command);

        switch (command)
        {
            case 'i':
                insertLine();
                break;

            case 'd':
                deleteLine();
                break;

            case 'p':
                displayDocument();
                break;
            case 'r':
                 replaceText();
                break;

            case 'q':
                freeDocument();
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid command.\n");
        }
    }

    return 0;
}

Node *findLine(int position)
{
    Node *current = head;

    for (int i = 1; i < position && current != NULL; i++)
    {
        current = current->next;
    }

    return current;
}
void insertLine()
{
    int position;
    char text[MAX_LENGTH];

    printf("Enter line number: ");
    scanf("%d", &position);
if (position < 1)
{
    printf("Invalid line number.\n");
    return;
}
    getchar();

    printf("Enter text: ");
    fgets(text, MAX_LENGTH, stdin);

    text[strcspn(text, "\n")] = '\0';
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(newNode->text, text);

    if (head == NULL)
    {
        newNode->prev = NULL;
        newNode->next = NULL;

        head = newNode;
        tail = newNode;
    }
    else if (position <= 1)
    {
        newNode->prev = NULL;
        newNode->next = head;

        head->prev = newNode;
        head = newNode;
    }
    else
    {
        Node *current = findLine(position);

        if (current == NULL)
        {
            newNode->next = NULL;
            newNode->prev = tail;

            tail->next = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = current;
            newNode->prev = current->prev;

            current->prev->next = newNode;
            current->prev = newNode;
        }
    }

    lineCount++;

    printf("Line inserted successfully.\n");
}
void deleteLine()
{
    int position;

    printf("Enter line number to delete: ");
    scanf("%d", &position);

    Node *current = findLine(position);

    if (current == NULL)
    {
        printf("Invalid line number.\n");
        return;
    }

    if (current->prev != NULL)
        current->prev->next = current->next;
    else
        head = current->next;

    if (current->next != NULL)
        current->next->prev = current->prev;
    else
        tail = current->prev;

    free(current);

    lineCount--;

    printf("Line deleted successfully.\n");
}

void displayDocument()
{
    Node *current = head;
    int number = 1;

    if (head == NULL)
    {
        printf("Document is empty.\n");
        return;
    }

    printf("\n===== DOCUMENT =====\n");

    while (current != NULL)
    {
        printf("%d. %s\n", number, current->text);

        current = current->next;
        number++;
    }

    printf("====================\n");
}
void replaceText()
{
    char oldText[MAX_LENGTH];
    char newText[MAX_LENGTH];

    getchar();

    printf("Enter text to find: ");
    fgets(oldText, MAX_LENGTH, stdin);
    oldText[strcspn(oldText, "\n")] = '\0';

    printf("Enter replacement text: ");
    fgets(newText, MAX_LENGTH, stdin);
    newText[strcspn(newText, "\n")] = '\0';

    if (strlen(oldText) == 0)
    {
        printf("Search text cannot be empty.\n");
        return;
    }

    Node *current = head;
    int replaced = 0;

    while (current != NULL)
    {
        char result[MAX_LENGTH] = "";
        char *start = current->text;
        char *found;

        while ((found = strstr(start, oldText)) != NULL)
        {
            strncat(result, start, found - start);
            strcat(result, newText);

            start = found + strlen(oldText);
            replaced++;
        }

        strcat(result, start);

        if (strlen(result) < MAX_LENGTH)
            strcpy(current->text, result);

        current = current->next;
    }

    if (replaced > 0)
        printf("%d replacement(s) made successfully.\n", replaced);
    else
        printf("Text not found.\n");
}
void freeDocument()
{
    Node *current = head;

    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;

        free(temp);
    }

    head = NULL;
    tail = NULL;
    lineCount = 0;
}