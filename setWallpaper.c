/*
    USAGE: ./setWallpaper [DIRECTORY] [left|right]

    Wallpaper setter for X11 using feh and written in C and Bash.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINES 50
#define MAX_LENGTH 500

void changeWallpaper ( char wallpapers[MAX_LINES][MAX_LENGTH], char argv[10], int indexWallpaper )
{
    char setter[MAX_LENGTH] = "feh --bg-fill ";
    int index = 1;
    FILE *count, *init, *indexWrite;
    count = fopen("index", "r");

    // if index doesn't exist, create a file named index with 0 in it
    if (count == NULL) {
        printf("Creating index..");
        init = fopen("index", "w");
        fputs("0", init);
        fclose(init);
    }

    fscanf(count, "%d", &index);
    fclose(count);

    if (strcmp(argv, "left") == 0) {
        index--;
    } else if (strcmp(argv, "right") == 0) {
        index++;
    } else {
        printf("error: Invalid arguments. Usage: ./setWallpaper [directory] [left|right]\n");
        return;
    }

    if (index > indexWallpaper - 1) 
        index = 0;

    if (index < 0) 
        index = indexWallpaper - 1;

    indexWrite = fopen("index", "w+");
    fseek(indexWrite, 0, SEEK_SET);
    fprintf(indexWrite, "%d", index);
    fclose(indexWrite);

    strcat(setter, wallpapers[index]);
    system(setter);
}

int main ( int argc, char *argv[] )
{
    if (argc == 3) {
        char wallpapers[MAX_LINES][MAX_LENGTH];
        char wallListScr[MAX_LENGTH] = "./wallpaperFileList.sh ";
        char wallList[MAX_LENGTH] = "wallpaperList.txt";

        strcat(wallListScr, argv[1]);
        system(wallListScr);

        FILE *file;
        file = fopen(wallList, "r");

        // if file doesn't exist, exit with error.
        if (file == NULL) {
            printf("error: problem with opening wallpaperList.txt.\n");
            printf("Please try again.\n");
            return 1;
        }

        int lineIndex = 0;

        while ((!feof(file) && !ferror(file)) && lineIndex < MAX_LINES)
            if (fgets(wallpapers[lineIndex], MAX_LENGTH, file) != NULL)
                lineIndex++;

        fclose(file);

        changeWallpaper(wallpapers, argv[2], lineIndex); 
    }
    else {
        printf("error: Invalid arguments. Usage: ./setWallpaper [directory] [left|right]\n");
        return 1;
    }

    return 0;
}
