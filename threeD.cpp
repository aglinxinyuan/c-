#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
 
using namespace std;
 
void placeShip(unsigned int length, bool ocean[10][10][10], unsigned int row, unsigned int col, unsigned int depth, unsigned int rowSub[],unsigned int colSub[], unsigned int depthSub[], unsigned int dirSub[]);
void placeShips(bool ocean[10][10][10], unsigned int row, unsigned int col, unsigned int depth,  unsigned int rowSub[], unsigned int colSub[], unsigned int depthSub[], unsigned int dirSub[]);
void display(bool ocean[10][10][10], unsigned int row, unsigned int col, unsigned int depth);
void displayShipPlacement(unsigned int rowSub[], unsigned int colSub[], unsigned int depthSub[], unsigned int dirSub[]);
 
int main(int argc, char *argv[])
{
    bool ocean[10][10][10];
    unsigned int subRow[5], subCol[5],subDepth[5],subDir[5];
    placeShips(ocean,10,10,10,subRow,subCol,subDepth,subDir);
    display(ocean,10,10,10);
    displayShipPlacement(subRow,subCol,subDepth,subDir);
    return 0;
}
 
void displayShipPlacement(unsigned int rowSub[], unsigned int colSub[], unsigned int depthSub[], unsigned int dirSub[])
{
    cout<<"Your subs are at:"<<endl;
    for(unsigned int i = 0; i < 5; ++i)
    {
        cout<<"Sub of length: "<<i+2<<" is at row = "<<rowSub[i]<<" col = "<<colSub[i]
            <<" depth = "<<depthSub[i]<<" and is facing ";
        switch(dirSub[i])
        {
            case 0: cout<<"North"<<endl;
                    break;
            case 1: cout<<"South"<<endl;
                    break;
            case 2: cout<<"East"<<endl;
                    break;
            case 3: cout<<"West"<<endl;
                    break;
        }
    }
}
 
 
 
void placeShip(unsigned int size, bool ocean[10][10][10], unsigned int row, unsigned int col, unsigned int depth, unsigned int rowSub[], unsigned int colSub[5], unsigned int depthSub[5], unsigned int dirSub[])
{
    unsigned int subDepth, subDir, subRow, subCol;
    subDepth = rand()%depth;
    subCol = (size - 1) + rand()%(col - (size - 1));
    subRow = (size - 1) + rand()%(row - (size - 1));
    subDir = rand()%4;
    rowSub[size - 2] = subRow;
    colSub[size - 2] = subCol;
    depthSub[size - 2] = subDepth;
    dirSub[size - 2] = subDir;
    switch(subDir)
    {
        case 0 : for(unsigned int i = 0; i < size; ++i)
                    ocean[subRow - i][subCol][subDepth] = true;
                 break;
 
        case 1 : for(unsigned int i = 0; i < size; ++i)
                    ocean[subRow + i][subCol][subDepth] = true;
                 break;
 
        case 2 : for(unsigned int i = 0; i < size; ++i)
                    ocean[subRow][subCol - i][subDepth] = true;
                 break;
 
        case 3 : for(unsigned int i = 0; i < size; ++i)
                    ocean[subRow][subCol + i][subDepth] = true;
                 break;
    }
}
 
void placeShips(bool ocean[10][10][10], unsigned int row, unsigned int col, unsigned int depth, unsigned int rowSub[], unsigned int colSub[], unsigned int depthSub[], unsigned int dirSub[])
{
    for(unsigned int i = 0; i < row; ++i)
        for(unsigned int j = 0; j < col; ++j)
            for(unsigned int k = 0; k < depth; ++k)
                ocean[i][j][k] = false;
    for(unsigned int size = 2; size <= 6; ++size)
        placeShip(size,ocean,row,col,depth,rowSub, colSub, depthSub,dirSub);
}
 
void display(bool ocean[10][10][10], unsigned int row, unsigned int col, unsigned int depth)
{
    cout<<"Ocean looks like: "<<endl;
    for(unsigned int d = 0; d < depth; ++d)
    {
        cout<<endl<<"At depth "<<d<<" the enemy is at:"<<endl<<endl
            <<setw(21)<<setfill('-')<<"-"<<setfill(' ')<<endl;
        for(unsigned int r = 0; r < row; ++r)
        {
            cout<<"|";
            for(unsigned int c = 0; c < col; ++c)
                if(ocean[r][c][d])
                    cout<<"*|";
                else
                    cout<<" |";
            cout<<endl<<setw(21)<<setfill('-')<<"-"<<setfill(' ')<<endl;
        }
    }
}
