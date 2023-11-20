#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "ArrayFunctions.h"

#define WIDTH 800
#define HEIGHT 600
#define CELL_SIZE 20
#define ROWS (HEIGHT / CELL_SIZE)
#define COLS (WIDTH / CELL_SIZE)

typedef struct 
{
    int visited;
    int SolvedPath;

} Cell;

typedef struct STRUCTURE
{
    int Row;
    int Col;
    struct STRUCTURE* next; 

}STACK;

STACK* Push(STACK* head,int e1,int e2)
{
   STACK* Newnode =(STACK*)malloc(sizeof(STACK));
   Newnode->Row=e1;
   Newnode->Col=e2;
   if (head==NULL)
   {
        Newnode->next=NULL;
        return Newnode;
   }
   Newnode->next=head;
   return Newnode;
}

STACK* Pop(STACK* head)
{
    STACK* current =head;
   if(head==NULL)return head;

   head=head->next;
   free(current);
   return head;
}

STACK* Free(STACK* head)
{
    STACK* current =head;
    while (head!=NULL)
    {
        head=head->next;
        free(current);
        current=head;
    }
    return head;    
}

Cell maze[ROWS][COLS];

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void initSDL() 
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Random Maze Generator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void QuitSDL() 
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void drawMaze() 
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < ROWS; ++i) 
    {
        for (int j = 0; j < COLS; ++j) 
        {
            if (maze[i][j].visited) 
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_Rect MazeTrack = {j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE};
                SDL_RenderFillRect(renderer, &MazeTrack);
            }
        }
    }
    SDL_Delay(30);
    SDL_RenderPresent(renderer);
}

void drawPath() 
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    for (int i = 0; i < ROWS; ++i) 
    {
        for (int j = 0; j < COLS; ++j) 
        {
            if (maze[i][j].SolvedPath) 
            {
                SDL_Rect Path = {j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE};
                SDL_RenderFillRect(renderer, &Path);
            }
        }
    }
    SDL_Delay(30);
    SDL_RenderPresent(renderer);
}

void generateMaze(STACK* StackHead) 
{

    for (int i = 0; i < ROWS; ++i) 
        for (int j = 0; j < COLS; ++j) 
            maze[i][j].visited = 0;
        
    int StartRow=0;int StartCol=0;
    StackHead=Push(StackHead,StartRow,StartCol);
    maze[StartRow][StartCol].visited = 1;
    int DirectionListCopy[4][2];

    while (StackHead!=NULL) 
    {   
        int EndNode=0;
        int currentRow = StartRow;
        int currentCol = StartCol;
        copyArray(DirectionListCopy,DirectionList);int ValidDirections=4;

        for (int i = 1; i <=4; i++)
        {
                                
            int Random_Direction = rand()% ValidDirections;
            int nextCol = currentCol + DirectionListCopy[Random_Direction][0] * 2;// x-value
            int nextRow = currentRow + DirectionListCopy[Random_Direction][1] * 2;// y-value

            if (nextRow >= 0 && nextRow < ROWS && nextCol >= 0 && nextCol < COLS && !maze[nextRow][nextCol].visited) 
            {
                maze[nextRow][nextCol].visited = 1;
                maze[currentRow + DirectionListCopy[Random_Direction][1]][currentCol + DirectionListCopy[Random_Direction][0]].visited = 1;
                if(maze[ROWS-2][COLS-2].visited==1)maze[ROWS-2][COLS-1].visited=1;
                drawMaze();

                StartRow=nextRow;
                StartCol=nextCol;
                StackHead=Push(StackHead,StartRow,StartCol);
                EndNode=0;
                break;

            }
            else 
            {   
                DeleteDirection(DirectionListCopy,Random_Direction,ValidDirections);
                ValidDirections--;
                EndNode=1;
            }
            
        }
        
        if (EndNode)
        {
            StackHead=Pop(StackHead);
            if(StackHead!=NULL)
            {
                StartRow=StackHead->Row;
                StartCol=StackHead->Col;
            }

        }
    
        
    }

}

void SolveMaze(STACK* StackHead) 
{

    int StartRow=0;int StartCol=0;
    StackHead=Push(StackHead,StartRow,StartCol);
    maze[StartRow][StartCol].SolvedPath = 1;

    while (StackHead!=NULL) 
    {   
        int EndNode=0;
        int currentRow = StartRow;
        int currentCol = StartCol;

        for (int i = 0; i<4; i++)
        {
            int nextCol = currentCol + DirectionList[i][0];// x-value
            int nextRow = currentRow + DirectionList[i][1];// y-value

            if (nextRow >= 0 && nextRow < ROWS && nextCol >= 0 && nextCol < COLS && maze[nextRow][nextCol].visited && !maze[nextRow][nextCol].SolvedPath) 
            {
                maze[nextRow][nextCol].SolvedPath = 1;
                if(maze[ROWS-2][COLS-2].SolvedPath==1)
                {
                    maze[ROWS-2][COLS-1].SolvedPath=1;
                    StackHead=Free(StackHead);

                }drawPath();

                if(StackHead==NULL)break;
                StartRow=nextRow;
                StartCol=nextCol;
                StackHead=Push(StackHead,StartRow,StartCol);
                EndNode=0;
                break;

            }
            else  EndNode=1;
            
        }
        
        if (EndNode)
        {
            StackHead=Pop(StackHead);
            if(StackHead!=NULL)
            {
                StartRow=StackHead->Row;
                StartCol=StackHead->Col;
            }

        }
    
        
    }

}

void PrintMaze()
{
    for (int i = 0; i < ROWS; ++i) 
    {
        for (int j = 0; j < COLS; ++j) 
        {
           printf("%d ",maze[i][j].visited);
        }
        printf("\n");
    }
}

int main() 
{
    srand(time(NULL));

    initSDL();STACK* StackHead=NULL;
    generateMaze(StackHead);

    int quit=0;
    SDL_Event e;
    PrintMaze();
    SolveMaze(StackHead);

    while (!quit) 
    {
        while (SDL_PollEvent(&e) != 0)if (e.type == SDL_QUIT)quit = 1;
        
    }

    QuitSDL();

}
