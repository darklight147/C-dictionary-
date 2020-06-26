#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHA "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LENGTH 26
#define ASCII 97

char *get_line(FILE *f)
{
    char *buffer = 0;
    long length;

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer)
        {
            fread(buffer, 1, length, f);
            buffer[length] = 0;
        }
        fclose(f);
    }

    if (buffer)
    {
        char ch;
        int i;
        int isMeaning = 0;
        char *final = "";
        char *pch;
        // printf("Splitting string \"%s\" into tokens:\n", buffer);
        return buffer;
    }
}

struct Blob
{
    char *word;
    char *meaning;

    struct Blob *next;
};

//check if string is a word
int isWord(char *str)
{
    int i;
    char temp;
    for (i = 0; i < 26; i++)
    {
        temp = str[i];
        if (strchr(ALPHA, temp) == NULL)
        {
            printf("%d\t", str[i]);
            return 0;
        }
    }
    return 1;
}

char get_first_char(char *str)
{
    //always convert first letter to lowercase
    return tolower(str[0]);
}

void ajoute(struct Blob* tete, char *data, int isMeaning) {
    struct Blob *New = (struct Blob *)malloc(sizeof(struct Blob));

    if (isMeaning)
    {
        // New->meaning = data;
        New->meaning = (char*) malloc(64);
        strcpy(New->meaning, data);
        puts(New->meaning);
    }
    else {
        New->word = (char*) malloc(64);
        strcpy(New->word, data);
        // printf("%s \n", New->word);
        puts(New->word);
    }
    if (tete == NULL)
    {
        New->next = NULL;
        tete = New;
    } else {
        New->next =  NULL;
        tete->next = New;
    }
}

int main()
{

    struct Blob *T[25];
    // pour savoir la position de chaque list chainé

    FILE *fp;
    char ch[100] = "";
    fp = fopen("file.txt", "rb");

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    char *token;
    char *pch;
    char cc;
    char *content = get_line(fp);
    int isMeaning = 0;
    int y = 0;

    /* get the first token */
    pch = strtok(content, "=\n"); // mabin word and word - ya espace or '=' or '\n'
    char z;
    while (pch != NULL)
    {
        // printf("%s", pch);
        // printf("%s\n", pch);
        // printf("%s\n is a %s\n", pch, isMeaning ? "meaning" : "word");
        // printf("%s and its a %s\n", pch, isMeaning ? "meaning" : "word");
        // printf("-----%c--------\n", get_first_char(pch));
        cc = get_first_char(pch);
        if ((y % 2) == 0)
        {
            z = cc;
        }
        T[(int)z - ASCII] = (struct Blob *)malloc(sizeof(struct Blob));
        ajoute(T[(int)z - ASCII], pch, isMeaning);
        // printf("%s\n", );

        // if (isMeaning)
        // {
        //     printf("%s \n",  T[(int)z - ASCII]->meaning);
        // } else {
        //     printf("%s \n",  T[(int)z - ASCII]->word);
        // }
        puts((char *) T[(int)z - ASCII]->word);

        
        // printf("%s",  T[(int)z - ASCII]->next);
        

        
        //reset
        isMeaning = !isMeaning;
        pch = strtok(NULL, "=\n");
        y++;
    }
    // printf("%d", y);

    fclose(fp);
    return 0;
}