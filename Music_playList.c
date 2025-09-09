#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char song_name[50];
char artist_name[50];

struct Music {
    char artist[50];
    char song[50];
    struct Music* next;
    struct Music* prev;
};

struct Music *head = NULL, *current = NULL;

int Display_Specific_Music(struct Music* Node) {
    if (Node != NULL) {
        printf("SONG NAME: %s\tARTIST NAME: %s\n", Node->song, Node->artist);
        return 1;
    }
    return 0;
}

struct Music* Create_Music(char* title, char* artist) {
    struct Music* newNode = (struct Music*)malloc(sizeof(struct Music));
    if (newNode == NULL) {
        printf("Oops, FAILED TO CREATE PLAYLIST!\n");
        exit(1);
    }
    strcpy(newNode->song, title);
    strcpy(newNode->artist, artist);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void Display_PlayList() {
    struct Music* temp = head;
    int idx = 1;

    if (temp == NULL) {
        printf("PLAYLIST IS EMPTY.\n");
        return;
    }

    printf("\n----- PLAYLIST -----\n");
    while (temp != NULL) {
        printf("%d. %s - %s\n", idx, temp->song, temp->artist);
        temp = temp->next;
        idx++;
    }
    printf("--------------------\n");
}

void Add_Music(char* title, char* artist) {
    struct Music* newNode = Create_Music(title, artist);
    if (head == NULL)
        head = current = newNode;
    else {
        struct Music* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }
    printf("ADDED: %s BY %s\n", title, artist);
    printf("--------------------\n");
}

void Remove_Music(char* title) {
    struct Music* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->song, title) == 0) {
            if (temp->prev != NULL)
                temp->prev->next = temp->next;
            else
                head = temp->next;
            if (temp->next != NULL)
                temp->next->prev = temp->prev;
            if (current == temp)
                current = head;
            free(temp);
            printf("THE REMOVED SONG: %s\n", title);
            return;
        }
        temp = temp->next;
    }
    printf("Oops... NO SONG IS PRESENT\n");
  printf("--------------------\n");
}

int Search_Music() {
    char title[50];
    struct Music* temp = head;

    printf("ENTER THE SONG NAME: ");
    scanf("%49s", title);

    while (temp != NULL) {
        if (strcmp(temp->song, title) == 0) {
            printf("FOUND!\n");
            Display_Specific_Music(temp);
            current = temp; // found song = current song
            return 1;
        }
        temp = temp->next;
    }

    printf("Oops... NO SONG IS PRESENT\n");
    printf("--------------------\n");
    return 0;
}

int Search_Music_Artist(char artistname[]) {
    struct Music* temp = head;
    int i = 0;
    while (temp != NULL) {
        if (strcmp(temp->artist, artistname) == 0) {
            Display_Specific_Music(temp);
            i = 1;
        }
        temp = temp->next;
    }
    if (i == 0) {
        printf("Oops... NO ARTIST IS PRESENT\n");
    }
    printf("--------------------\n");
    return i;
}

int PlayNext() {
    if (current == NULL) {
        printf("NO SONG IS CURRENTLY SELECTED.\n");
        return 0;
    }
    if (current->next == NULL) {
        printf("YOU ARE AT THE LAST SONG. NO NEXT SONG AVAILABLE.\n");
        return 0;
    }
    current = current->next;
    printf("NOW PLAYING: %s by %s\n", current->song, current->artist);
   printf("--------------------\n");
    return 1;
}

int PlayPrev() {
    if (current == NULL) {
        printf("NO SONG IS CURRENTLY SELECTED.\n");
        return 0;
    }
    if (current->prev == NULL) {
        printf("YOU ARE AT THE FIRST SONG. NO PREVIOUS SONG AVAILABLE.\n");
        return 0;
    }
    current = current->prev;
    printf("NOW PLAYING: %s by %s\n", current->song, current->artist);
    printf("--------------------\n");
    return 1;
}

void Shuffle_PlayList() {
    if (head == NULL || head->next == NULL) {
        printf("PLAYLIST IS TOO SHORT TO SHUFFLE.\n");
        return;
    }
    int count = 0;
    struct Music* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    struct Music** nodeArray = (struct Music**)malloc(count * sizeof(struct Music*));
    temp = head;
    for (int i = 0; i < count; i++) {
        nodeArray[i] = temp;
        temp = temp->next;
    }
    srand(time(NULL));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct Music* swapTemp = nodeArray[i];
        nodeArray[i] = nodeArray[j];
        nodeArray[j] = swapTemp;
    }
    head = nodeArray[0];
    head->prev = NULL;
    current = head;

    for (int i = 0; i < count - 1; i++) {
        nodeArray[i]->next = nodeArray[i + 1];
        nodeArray[i + 1]->prev = nodeArray[i];
    }
    nodeArray[count - 1]->next = NULL;

    free(nodeArray);
    printf("PLAYLIST HAS BEEN SHUFFLED!\n");
    printf("--------------------\n");
}

int main() {
    int choice;

    printf("----------------------------[   MUSIC PLAYLIST   ]--------------------------------\n");
    do {
        printf("\nSELECT \n1:ADD A SONG TO PLAYLIST\n2:REMOVE A SONG FROM PLAYLIST\n3:SEARCH A SONG\n4:SEARCH A SONG BY ARTIST\n");
        printf("5:PLAY NEXT SONG\n6:PLAY PREVIOUS SONG\n7:SHUFFLE PLAYLIST\n8:DISPLAY PLAYLIST\n9:EXIT\n");
        printf("ENTER CHOICE: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("ENTER THE SONG NAME: ");
                scanf("%s", song_name);
                printf("ENTER THE ARTIST NAME: ");
                scanf("%s", artist_name);
                Add_Music(song_name, artist_name);
                break;
            case 2:
                printf("ENTER THE SONG TO REMOVE: ");
                scanf("%s", song_name);
                Remove_Music(song_name);
                break;
            case 3:
                Search_Music();
                break;
            case 4:
                printf("ENTER THE NAME OF ARTIST: ");
                scanf("%s", artist_name);
                Search_Music_Artist(artist_name);
                break;
            case 5:
                PlayNext();
                break;
            case 6:
                PlayPrev();
                break;
            case 7:
                Shuffle_PlayList();
                break;
            case 8:
                Display_PlayList();
                break;
            case 9:
                printf("Exiting...\n");
                printf("--------------------\n");
                exit(0);
            default:
                printf("PROVIDED REQUEST IS INVALID, CHOOSE THE PROPER INPUT.\n");
        }
    } while (choice != 9);
    return 0;
}
