//      Guess the BOLLYWOOD movie game
//      Author : Nithin
//      Date : 11-05-2011

#include <stdio.h>
#include <stdlib.h>

int table[256];

void shift_table(char[],int);
int horspool(char[],char[],int[]);
int select_movie(char[][100],int);
void bollywood_game(char[]);

int main()
{
    int n,num;
    char movie_list[][100]={"DON","Om Shanti Om","3 Idiots","Mera Naam Joker","Ready"};
    char text[100];
    n=5;
    num=select_movie(movie_list,n);
    strcpy(text,movie_list[num]);

    printf("\n\n\n\t\t\tBOLLYWOOD\n\n");
    printf("*****************************************************************************");
    printf("\n\n\t\tRules : \n\n\t1. You need to guess the movie by entering the letter and filling the missing letters."
           "\n\n\t2. You have only 9 chances.");
    printf("\n\n*****************************************************************************\n\n");
    bollywood_game(text);

    return 0;
}

int select_movie(char movie_list[5][100],int n)
{
    return rand()%n;
}

void shift_table(char pattern[100],int m)
{
    int i;
    for(i=0;i<256;i++)
        table[i]=m;
    for(i=0;i<m-1;i++)
        table[pattern[i]]=m-1-i;
}

int horspool(char text[100],char pattern[100],int shadow[100])
{
    int n=strlen(text),m=strlen(pattern),i=m-1,k,flag=0;
    while(i<n)
    {
        k=0;
        while(k<m && pattern[m-1-k]==text[i-k])
            k++;
        if(k==m)
        {
            shadow[i-m+1]=1;
            i=i+table[text[i]];
            flag=1;
        }
        else
            i=i+table[text[i]];
    }
    if(flag==0)
        return -1;
    else
        return 1;
}

void bollywood_game(char text[100])
{
    int n,shadow[100],i,chance,win,m,result,temp;
    char pattern[100],name[50]="BOLLYWOOD";
    n=strlen(text);
    temp='a'-'A';
    for(i=0;i<n;i++)
        if(text[i]>='A' && text[i]<='Z')
            text[i]+=temp;
    for(i=0;i<n;i++)
    {
        if(text[i]==' ')
            shadow[i]=1;
        else
            shadow[i]=0;
    }
    for(chance=9,win=0;chance>0 && win==0;)
    {
        printf("Number of chances left : ");
        for(i=9-chance;i<9;i++)
            printf("%c ",name[i]);
        printf("\n\n\tMovie name is : \n\n\t\t");
        for(i=0;i<n;i++)
        {
            if(shadow[i]==1)
                printf("%c",text[i]);
            else
                printf("%c",'_');
            printf(" ");
        }
        printf("\n\nEnetr the letter : ");
        gets(pattern);
        m=strlen(pattern);
        for(i=0;i<m;i++)
            if(pattern[i]>='A' && pattern[i]<='Z')
                pattern[i]+=temp;
        shift_table(pattern,m);
        result=horspool(text,pattern,shadow);
        if(result==-1)
        {
            printf("Letter not found!\n");
            chance--;
        }
        else
            for(i=0,win=1;i<n;i++)
                if(shadow[i]==0)
                    win=0;
    }
    if(win==1)
        printf("Correct movie! You have won the game! \n\n\tMovie name : %s",text);
    else
        printf("You have run out of chances! Sorry you lose the game...\n\tMovie name : %s",text);
}
