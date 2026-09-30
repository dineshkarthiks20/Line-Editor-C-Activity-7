#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 200

char *lines[MAX_LINES];
int lineCount = 0;

void insertLine(int position, char text[])
{
    if (lineCount >= MAX_LINES)
    {
        printf("Document is full.\n");
        return;
    }

    if (position < 1 || position > lineCount + 1)
    {
        printf("Invalid line number.\n");
        return;
    }

    for (int i = lineCount; i >= position; i--)
    {
        lines[i] = lines[i - 1];
    }

    lines[position - 1] = malloc(strlen(text) + 1);

    if (lines[position - 1] == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(lines[position - 1], text);
    lineCount++;

    printf("Line inserted successfully.\n");
}

void deleteLine(int position)
{
    if (position < 1 || position > lineCount)
    {
        printf("Invalid line number.\n");
        return;
    }

    free(lines[position - 1]);

    for (int i = position - 1; i < lineCount - 1; i++)
    {
        lines[i] = lines[i + 1];
    }

    lineCount--;

    printf("Line deleted successfully.\n");
}

void displayLines()
{
    if (lineCount == 0)
    {
        printf("Document is empty.\n");
        return;
    }

    printf("\n----- DOCUMENT -----\n");

    for (int i = 0; i < lineCount; i++)
    {
        printf("%d: %s\n", i + 1, lines[i]);
    }

    printf("--------------------\n");
}

int main()
{
    char command;
    int position;
    char text[MAX_LENGTH];

    printf("===== SIMPLE LINE EDITOR =====\n");

    while (1)
    {
        printf("\nCommands:\n");
        printf("I - Insert line\n");
        printf("D - Delete line\n");
        printf("L - Display document\n");
        printf("Q - Quit\n");

        printf("\nEnter command: ");
        scanf(" %c", &command);

        if (command == 'I' || command == 'i')
        {
            printf("Enter line number: ");
            scanf("%d", &position);

            getchar();

            printf("Enter text: ");
            fgets(text, MAX_LENGTH, stdin);

            text[strcspn(text, "\n")] = '\0';

            insertLine(position, text);
        }
        else if (command == 'D' || command == 'd')
        {
            printf("Enter line number: ");
            scanf("%d", &position);

            deleteLine(position);
        }
        else if (command == 'L' || command == 'l')
        {
            displayLines();
        }
        else if (command == 'Q' || command == 'q')
        {
            break;
        }
        else
        {
            printf("Invalid command.\n");
        }
    }

    for (int i = 0; i < lineCount; i++)
    {
        free(lines[i]);
    }

    printf("Exiting editor...\n");

    return 0;
}