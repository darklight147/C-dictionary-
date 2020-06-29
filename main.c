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

struct Blob *ajoute(struct Blob *tete, char *pch, char *pch1)
{
    struct Blob *New = (struct Blob *)malloc(sizeof(struct Blob));

    New->word = pch1;
    New->meaning = pch;


    New->next = tete;

    tete = New;

    return tete;
}
void afficher(struct Blob *tete)
{
    struct Blob *p = tete;
    int i = 0;
    while (p != NULL)
    {
        i++;
        printf("la lettre: %c = %s\n\n", get_first_char(p->word), p->meaning);
        p = p->next;
        printf("total de %d mots\n", i);
    }
    // printf("\n\n");
}

int main()
{
    int i;
    struct Blob *T[25];
    for (i = 0; i <= 25; i++)
    {
        T[i] = NULL;
    }
    // pour savoir la position de chaque list chain�

    FILE *fp;
    char ch[100] = "";
    fp = fopen("file.txt", "rb");

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    char *token;
    char *pch, *pch1;
    char cc;
    char *content = get_line(fp);
    int isMeaning = 0;
    int y = 0;

    /* get the first token */
    pch = strtok(content, "=\n"); // mabin word and word - ya espace or '=' or '\n'
    char z;
    while (pch != NULL)
    {

        // printf("%s\n", pch);
        // printf(" %s is a word\n", pch);
        // printf("%c\n", cc);

        z = get_first_char(pch);
        pch1 = pch;
        // printf(" pch1 : %s \n", pch1);

        pch = strtok(NULL, "=\n");
        // printf(" pch : %s  \n", pch);
        // printf(" %s is a meaning \n", pch);
        if (y % 2 == 0)
        {
            T[(int)z - ASCII] = ajoute(T[(int)z - ASCII], pch, pch1);
        }
        

        afficher(T[(int)z - ASCII]);
        pch = strtok(NULL, " =\n");
        y++;
    }

    for (i = 0; i < 25; i++)
    {
        afficher(T[i]);
    }
    
    // printf("%d", y);

    fclose(fp);
    return 0;
}
