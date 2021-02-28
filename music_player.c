#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct music 
{
	int data;
	struct music *backMusic;
	struct music *frontMusic;
} Music;

void initMusic();
void playMusic();
void Next();
void Back();
void addMusic(int);
void deleteMusic();
void allFree();


Music *headerPointer;
Music *currentMusic;

int main(void)
{
	int newdata;
	int i;

	initMusic();
	currentMusic = headerPointer;
	char command[10];
	for(i=0; i++; i<7)
	{
		command[i] = '\0';
	}

	for (;;)
	{
		printf("\n\n[Play] [Next] [Back] [Add] [Delete] [Exit]\n");
		scanf("%s", command);

		if(strcmp(command, "Exit") == 0)
		{
			break;
		}
	
		else if(strcmp(command, "Play") == 0)
		{	
			playMusic();
		}
		
		else if(strcmp(command, "Next") == 0)
		{
			Next();
		}

		else if(strcmp(command, "Back") == 0)
		{
			Back();
		}

		else if(strcmp(command, "Add") == 0)
		{
			printf("input the song data\n");
			scanf("%d", &newdata);
			addMusic(newdata);
		}

		else if(strcmp(command, "Delete") == 0)
		{
			deleteMusic();
		}

		else
			printf("!! Please note the uppercase and rewrite it !!\n");	
	}

	allFree();
	return 0;
}

void initMusic()
{
	headerPointer = (Music *)malloc(sizeof(Music));
	headerPointer -> data = 0x00;
	headerPointer -> backMusic = headerPointer;
	headerPointer -> frontMusic = headerPointer;
}

void playMusic()
{
	if(headerPointer -> frontMusic == headerPointer)
	{
		printf("There is no music to Play\n");
	}
	else
	{
		if(currentMusic == headerPointer)
			currentMusic = headerPointer -> frontMusic;
	
		printf("The song is %d\n", currentMusic -> data);
	}
}


void Next()
{
	if(currentMusic == headerPointer)
	{ 
		printf("There is no Music\n");
	}
	else
	{
		if(currentMusic -> frontMusic == headerPointer)
			currentMusic = headerPointer -> frontMusic;
		else
			currentMusic = currentMusic -> frontMusic;

		printf("Current Music is [%d]\n", currentMusic -> data);
	}
}



void Back()
{
	if(currentMusic == headerPointer)
	{
		printf("There is no Music\n");
	}
	else
	{
		if(currentMusic -> backMusic == headerPointer)
			currentMusic = headerPointer -> backMusic;
		else
			currentMusic = currentMusic -> backMusic;

		printf("Current Music is [%d]\n", currentMusic -> data);
	}
}




void addMusic(int newdata)
{
	Music *newMusic;
	newMusic = (Music *)malloc(sizeof(Music));
	newMusic -> data = newdata;
	headerPointer -> backMusic -> frontMusic = newMusic;
	headerPointer -> backMusic -> frontMusic -> backMusic = headerPointer -> backMusic;
	headerPointer -> backMusic = headerPointer -> backMusic -> frontMusic;
	headerPointer -> backMusic -> frontMusic = headerPointer;
	
	printf("Add Completed\n");
}



void deleteMusic()
{
	if(headerPointer -> frontMusic == headerPointer)
	{
		printf("There is no music here\n");
	}
	else
	{
		Music *deletePointer;
		deletePointer = currentMusic;
		printf("[[%d]]\n", deletePointer -> data);
		Next(headerPointer, currentMusic);
		deletePointer -> backMusic -> frontMusic = deletePointer -> frontMusic;
		deletePointer -> frontMusic -> backMusic = deletePointer -> backMusic;
		free(deletePointer);

		printf("Delete Completed\n");
	}
}


void allFree()
{
	Music *iter = headerPointer;
	Music *iterNext = NULL;
	do {
		printf("Music [%d] was deleted.\n", iter -> data);
		iterNext = iter -> frontMusic;
		free(iter);
		iter = iterNext;
	} while(iter != headerPointer);

	printf("____________________\n\n");
}