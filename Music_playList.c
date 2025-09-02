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
int Display_Specific_Music(struct Music* Node){
  if(Node!=NULL){
    printf("SONG NAME:%s\tARTIST NAME:%s",Node->song,Node->artist);
  }
}
int Create_Music(){//pranav
  
}
void Display_PlayList(){// rishabh

}
int Add_Music(){//richa

}
int Remove_Music(){// richa

}
int Search_Music(){// rishabh

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
  
}
int PlayPrev(){//parvathy
  
}
int Shuffle_PlayList(){//pranav
  
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
