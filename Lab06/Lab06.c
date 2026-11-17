// By: Duel Mood
// TA: Anthony Smith
// Lab time: 11:30am on Tuesdays

#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef struct
{
    char firstName[50];
    char lastName[50];
    char PUID[11];
    int age;
} Data;

typedef struct Node
{
    Data data;
    struct Node *next;
} Node;

int comparePUID(const char *puid1, const char *puid2)
{
    for (int i = 0; i < 10; i++)
    {
        if (puid1[i] < puid2[i])
        {
            return -1;
        }
        else if (puid1[i] > puid2[i])
        {
            return 1;
        }
    }
    return 0; // PUIDs are equal
}

Node *CreateListNoNodes()
{
    return malloc(sizeof(Node));
}

Node *CreateListNode(Data data)
{
    Node *nodePtr = CreateListNoNodes();
    nodePtr->data = data;
    nodePtr->next = NULL;
    return nodePtr;
}

void InsertFront(Data data, Node *nodePtr)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = nodePtr;
    nodePtr = newNode;
}

Node *InsertMiddle(Data data, Node *nodePtr)
{
    Node *newNode = CreateListNode(data);

    if (comparePUID(data.PUID, nodePtr->data.PUID) < 0)
    {
        newNode->next = nodePtr;
        return newNode;
    }

    Node *current = nodePtr;
    while (current->next != NULL && // Not at the end of the list
           comparePUID(data.PUID, current->next->data.PUID) >= 0)
    { // And current PUID is smaller than the next node's PUID
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    return nodePtr;
}

void InsertEnd(Data data, Node *nodePtr)
{
    Node *temp = nodePtr;
    while (temp->next != NULL)
    {
        // Iterate to end of the list
        temp = temp->next;
    }

    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    temp->next = newNode;
}

void DeleteFront(Node *nodePtr)
{
    if (nodePtr == NULL)
    {
        return; // List is empty
    }

    Node *temp = nodePtr;
    nodePtr = nodePtr->next; // Move head to next node
    free(temp);              // Free the old head
}

void DeleteMiddle(char PUID[11], Node *nodePtr)
{
    if (nodePtr == NULL || nodePtr->next == NULL)
    {
        return; // List is empty or has only one node
    }

    Node *current = nodePtr;
    Node *previous = NULL;

    while (current != NULL && // Not at the end of the list
           comparePUID(current->data.PUID, PUID))
    { // PUIDs do not match
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    { // Node with given PUID not found
        return;
    }

    previous->next = current->next; // Bypass the node
    free(current);                  // Free the memory of the deleted node
}

void DeleteEnd(Node *nodePtr)
{
    Node *temp = nodePtr;
    Node *previous = NULL;
    while (temp->next != NULL)
    {
        previous = temp;
        temp = temp->next;
    }

    free(temp);
    if (previous != NULL)
    {
        previous->next = NULL;
    }
}

Node *Traverse(char PUID[11], Node *nodePtr)
{
    while (nodePtr != NULL && comparePUID(nodePtr->data.PUID, PUID))
    {
        nodePtr = nodePtr->next;
    }
    return nodePtr;
}

int Search(char PUID[11], Node *nodePtr)
{
    int i = 0;
    while (nodePtr != NULL && comparePUID(nodePtr->data.PUID, PUID))
    {
        nodePtr = nodePtr->next;
        i++;
    }
    if (nodePtr == NULL)
    {
        return -1; // PUID not found
    }
    return i; // Return the index of the found node
}

void PrintNode(Node *nodePtr)
{
    printf("First Name: %s, Last Name: %s, PUID: %s, Age: %d\n",
           nodePtr->data.firstName,
           nodePtr->data.lastName,
           nodePtr->data.PUID,
           nodePtr->data.age);
}

void Print(Node *nodePtr)
{
    while (nodePtr != NULL)
    {
        PrintNode(nodePtr);
        nodePtr = nodePtr->next;
    }
}

void inputData(Data *data)
{
    printf("Enter First Name: ");
    scanf("%s", data->firstName);
    printf("Enter Last Name: ");
    scanf("%s", data->lastName);
    printf("Enter PUID: ");
    scanf("%s", data->PUID);
    printf("Enter Age: ");
    scanf("%d", &data->age);
}

void main()
{
    Node *head = NULL; // Start pointer for the linked list

    while (true)
    {
        int selection;

        printf("Select an option:\n");
        printf("1. Create List with No Nodes\n");
        printf("2. Create List with a Single Node\n");
        printf("3. Insert Node at Front\n");
        printf("4. Insert Node in Middle\n");
        printf("5. Insert Node at End\n");
        printf("6. Delete Node from Front\n");
        printf("7. Delete Node from Middle\n");
        printf("8. Delete Node from End\n");
        printf("9. Traverse List\n");
        printf("10. Search for Node\n");
        printf("11. Print List\n");
        printf("12. Exit\n");
        scanf("%d", &selection);

        switch (selection)
        {
        case 1: // Create List with No Nodes
        {
            head = CreateListNoNodes();
            break;
        }

        case 2: // Create List with a Single Node
        {
            Data data;
            inputData(&data);
            head = CreateListNode(data);
            break;
        }

        case 3: // Insert Node at Front
        {
            Data data;
            inputData(&data);
            InsertFront(data, head);
            break;
        }

        case 4: // Insert Node in Middle
        {
            Data data;
            inputData(&data);
            head = InsertMiddle(data, head);
            break;
        }

        case 5: // Insert Node at End
        {
            Data data;
            inputData(&data);
            InsertEnd(data, head);
            break;
        }

        case 6: // Delete Node from Front
        {
            DeleteFront(head);
            break;
        }

        case 7: // Delete Node from Middle
        {
            char PUID[11];
            printf("Enter PUID of the node to delete: ");
            scanf("%s", PUID);
            DeleteMiddle(PUID, head);
            break;
        }

        case 8: // Delete Node from End
        {
            DeleteEnd(head);
            break;
        }

        case 9: // Traverse List
        {
            char PUID[11];
            printf("Enter PUID of the node to traverse: ");
            scanf("%s", PUID);
            Node *foundNode = Traverse(PUID, head);
            if (foundNode != NULL)
            {
                PrintNode(foundNode);
            }
            else
            {
                printf("Node with PUID %s not found.\n", PUID);
            }
            break;
        }

        case 10: // Search for Node
        {
            char PUID[11];
            printf("Enter PUID of the node to search: ");
            scanf("%s", PUID);
            int index = Search(PUID, head);
            if (index != -1)
            {
                printf("Node with PUID %s found at index %d.\n", PUID, index);
            }
            else
            {
                printf("Node with PUID %s not found.\n", PUID);
            }
            break;
        }

        case 11: // Print List
        {
            Print(head);
            break;
        }

        case 12:
            return;
        }
        printf("\n");
    }
}