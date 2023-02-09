#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;
const int n =10;
const int MAXSIZE = n*n;
vector<int> stack;
int top = -1;
int thickness =3;
int cellSize = 50;
struct cell
{
    int up ;
    int left ;
    int right ;
    int down ;
} typedef cell;
int a[n][n];
int x=0, y=0;
cell cells[n][n];
void printCell(int curr)
{
	setfillstyle(SOLID_FILL,15);
	int h = curr /n;
    int g = curr - n*h;
    for(int i=0;i<n;i++)
    {
		for(int j=0;j<n;j++)
		{
			int x1 = cellSize*j;
			int x2 = x1+cellSize;
			int y1 = cellSize* i;
			int y2 = y1 + cellSize;
			if(cells[i][j].up ==1)
				bar(x1,y1,x2,y1+thickness);
			if(cells[i][j].left ==1)
				bar(x1,y1,x1+thickness,y2);
			if(cells[i][j].right ==1)
				bar(x2-thickness,y1,x2,y2);
			if(cells[i][j].down ==1)
				bar(x1,y2-thickness,x2,y2);
		}
	}
	setfillstyle(SOLID_FILL,13);
	bar(g*cellSize+ cellSize/5,h*cellSize+ cellSize/5,g*cellSize+ cellSize*4/5,h*cellSize+ cellSize*4/5);
}
void zeroCells()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cells[i][j].left =1;
            cells[i][j].right =1;
            cells[i][j].up =1;
            cells[i][j].down =1;
        }
    }
}
void print(int a[n][n]) // ham de in ma tran a
{
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout <<a[i][j] 	;
        }
        cout <<"\n";
    }
    cout <<"\n";
}
void zeroOut() // ham de bien cac phan tu trong ma tran thanh 0
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            a[i][j] = 0;
        }
    }
}
int check(int pos) // ham de check xem con vi tri nao de di cua phan tu a hay khong
{
    int r = pos /n; //row
    int c = pos - n*r; // column
	if((r==n-1?1:a[r+1][c]) !=0 && (c==n-1?1:a[r][c+1]) !=0&& (r==0?1:a[r-1][c]) !=0&& (c==0?1:a[r][c-1]) !=0) // dung toan tu 3 ngoi de tranh xet cac phan tu nam ngoai ma tran
		return 0;
	else
		return 1;
}
int explore() // ham kham pha de tao ra me cung tu ma tran
{
    int curr;
    stack.push_back(0);
    a[0][0] =1;
    while(!stack.empty())
        {
        curr = *(stack.end()-1);
		cout <<*(stack.end()-1)<<endl;
        if(check(curr) ==0){
        	int aaa = *(stack.end()-1);
			stack.pop_back();
            cout <<"pop the :" << aaa<< endl;
			printCell(curr);
	        delay(50);
        	cleardevice();
        }
        else
        {
        	int r,c;
            while(check(curr)==1)
            {
                r = curr /n;
        		c = curr - n*r;
        		a[r][c] =1;
                while(1)
                {
            		int vect = rand() %4;
                    //cout <<"random number: %d\n",vect);
            		if (vect ==0 && a[r][c-1]==0 && c!=0)
                    {
            		    a[r][c-1]=1;
                        stack.push_back(curr -1);

                        cells[r][c-1].right =0;
                        cells[r][c].left =0;
                        break;
            		}
            		else if (vect ==1 && a[r+1][c]==0 && r!=n-1)  
                    {
            		    a[r+1][c]=1;
                        stack.push_back(curr +n);

                        cells[r+1][c].up =0;
                        cells[r][c].down =0;
                        break;
            		}
            		else if (vect ==2 && a[r][c+1]==0 && c!=n-1)
                    {
            		    a[r][c+1]=1;
                        stack.push_back(curr +1);

                        cells[r][c+1].left =0;
                        cells[r][c].right =0;
                        break;
            		}
            		else if (vect ==3 && a[r-1][c]==0 && r!=0)
                    {
            		    a[r-1][c]=1;
                        stack.push_back(curr -n);

                        cells[r-1][c].down =0;
                        cells[r][c].up =0;
                        break;
            		}
                }
                curr =*(stack.end()-1);
				printCell(curr);
        		delay(50);
        		cleardevice();
            }
        }
    }
}
void map()
{
	zeroCells();
	zeroOut();
	initwindow(3000,3000);
	setfillstyle(SOLID_FILL,15);
    explore();
    printCell(0);
}
int main()
{
	srand(time(0));
    map();
	getch();
	return 0;
}



