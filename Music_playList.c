#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char song_name[50];
char artist_name[50];
struct Music {
  char artist[50];
  char song[50];
  struct Music* next;
  struct Music* prev;
};

struct Music *head = NULL, *current = NULL;

int Display_Specific_Music(struct Music* Node){ 
  if(Node!=NULL){
    printf("SONG NAME:%s\tARTIST NAME:%s",Node->song,Node->artist);
  }
}
int Create_Music(){//pranav
struct Music* Create_Music(char* title, char* artist) {
    struct Music* newNode = (struct Music*)malloc(sizeof(struct Music));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->song, title);
    strcpy(newNode->artist, artist);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}
}
void Display_PlayList() {
    struct Music* temp = head;
    int idx = 1;

    if (temp == NULL) {
        printf("Playlist is empty.\n");
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
void Add_Music(char*title, char*artist)//Richa
{
  struct Music*newNode = Create_Music(title,artist);
  if(head == NULL)
    head = current = newNode;
  else{
    struct Music*temp = head;
    while(temp->next!=NULL)
      temp=temp->next;
    temp->next=newNode;
    newNode->prev=temp;
  }
  printf("Added:%s by %s\n",title,artist);  
}
void Remove_Music(char*title)// richa
{
  struct Music*temp = head;
  while(temp!=NULL)
  {
    if(strcmp(temp->song,title)==0)
    {
      if(temp->prev!=NULL)
        temp->prev->next=temp->next;
      else
        head=temp->next;
      if(temp->next!=NULL)
        temp->next->prev=temp->prev;
      if(current==temp)
        current=head;
      free(temp);
      printf("The removed: %s\n",title);
      return;
    }
    temp=temp->next;
  }
  printf("Song not found\n");  
}
int Search_Music() {
    char title[50];
    struct Music* temp = head;

    printf("ENTER THE SONG NAME: ");
    scanf("%49s", title); 

    while (temp != NULL) {
        if (strcmp(temp->song, title) == 0) {
            printf("Found!\n");
            Display_Specific_Music(temp);
            printf("\n");
            current = temp; //found song = current song
            return 1;
        }
        temp = temp->next;
    }

    printf("Song not found\n");
    return 0;
}
int Search_Music_Artist(char artistname[]){//ram
  struct Music* temp=head;
  int i=0; 
  while(temp!=NULL){
    if(strcmp(temp->artist,artistname)==0){
      Display_Specific_Music(temp);
      i=1;
    }
    else{
      temp=temp->next;
    }
  }
  if(i==0){
    printf("Oops... NO ARTIST IS PRESENT\n");
  }
}
int PlayNext(){//parvathy
      if (current == NULL) {
        printf("No song is currently selected.\n");
        return 0;
    }
    if (current->next == NULL) {
        printf("You are at the last song. No next song available.\n");
        return 0;
    }
    current = current->next;
    printf("Now playing: %s by %s\n", current->song, current->artist);
    return 1;
}
int PlayPrev(){//parvathy
   if (current == NULL) {
        printf("No song is currently selected.\n");
        return 0;
    }
    if (current->prev == NULL) {
        printf("You are at the first song. No previous song available.\n");
        return 0;
    }
    current = current->prev;
    printf("Now playing: %s by %s\n", current->song, current->artist);
    return 1;
}
void Shuffle_PlayList() {
    if (head == NULL || head->next == NULL) {
        printf("Playlist is too short to shuffle.\n");
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
        nodeArray[i]->next = nodeArray[i+1];
        nodeArray[i+1]->prev = nodeArray[i];
    }
    nodeArray[count-1]->next = NULL;
    
    free(nodeArray);
    printf("Playlist has been shuffled! 🔀\n");
}
}
int main(){//ram
  int choice;
  struct Music* playlist=NULL;
  printf("----------------------------[   MUSIC PLAYLIST   ]--------------------------------");
  do{
    printf("PRESS \n1:CREATE A PLAY LIST\n2:REMOVE A SONG FROM PLAYLIST\n3:SEARCH A SONG\n4:SEARCH A SONG BY ARTIST\n");
    printf("5:PLAY NEXT SONG\n6:PLAY PREVIOUS SONG\n7:SHUFFLE PLAYLIST\n8:DISPLAY PLAYLIST\n9:EXIT");
    switch (choice){
      case 1:Add_Music();
              break;
      case 2:Remove_Music();
              break;
      case 3:Search_Music();
              break;
      case 4: printf("ENTER THE NAME OF ARTIST:");
              scanf("%s",artist_name);
              Search_Music_Artist(artist_name);
              break;
      case 5:PlayNext();
              break;
      case 6:PlayPrev();
              break;
      case 7:Shuffle_Playlist();
              break;
      case 8:Display_PlayList();
              break;
      case 9:exit(0);
              break;
      default: printf("PROVIDED REQUESTS ARE INVALID,CHOOSE THE PROPER INPUTS");
    }
  }while(choice!=9);
}
