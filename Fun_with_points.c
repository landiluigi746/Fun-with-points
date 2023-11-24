/*
	C program that creates an array of random points, 
	sorts it using double selection sort (iterative version) 
	and puts them in a graph
	
	Every point in the array has different coordinates from the others

	Made by: landiluigi746
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define SIZE 10 //constant for the max size of the array

const int ROWS = 25; //constant for the rows of the graph
const int COLS = 25; //constant for the cols of the graph

typedef struct point
{ //defines the point
    int x;
    int y;
} point;

//Functions prototypes
void fill(point *arr);
void sort(point *arr);
void swap(point *pt1, point *pt2);
void printPointsArr(point *arr);
void drawGraph(point *arr);
point newPoint(int a, int b);
int smallestPos(point *arr, int arrStart, int arrEnd);
int largestPos(point *arr, int arrStart, int arrEnd);
bool isSorted(point *arr);
bool isAlreadyInArray(point *arr, int arrEnd, point pt);

int main()
{
    point *ptArr = (point*) malloc(SIZE * sizeof(point));
    clock_t startProgram, endProgram, startSorting, endSorting, startDrawing, endDrawing;
    double execTime, sortTime, drawTime;

    startProgram = clock(); //Program start time

	//Filling the array
	printf("Filling array...\n");
	fill(ptArr);

	//Printing the initial array
	printf("Initial array: \n");
	printPointsArr(ptArr);

	if( (!isSorted(ptArr)) )
	{ //Sorting the array only if it isn't already sorted
		startSorting = clock(); //Sorting start time
		printf("Sorting array...\n");
		sort(ptArr);
		endSorting = clock(); //Sorting end time
		sortTime = ((double) (endSorting - startSorting)) / (double) CLOCKS_PER_SEC;

		//Printing the sorted array
		printf("Sorted array: \n");
		printPointsArr(ptArr);
	}
	else
		printf("The array is already sorted!!\n\n");

	//Drawing array graph
	startDrawing = clock(); //Drawing start time
	printf("Array graph: \n");
	drawGraph(ptArr);
	endDrawing = clock(); //Drawing end time
	drawTime = ((double) (endDrawing - startDrawing)) / (double) CLOCKS_PER_SEC;

    endProgram = clock(); //Program end time
	execTime = ((double) (endProgram - startProgram)) / (double) CLOCKS_PER_SEC;

	printf("Sorting time: %lf seconds.\n", sortTime);
	printf("Drawing time: %lf seconds.\n\n", drawTime);
	printf("Total execution time: %lf seconds.\n\n", execTime);

    free(ptArr);

    getchar();
    return 0;
}

void fill(point *arr)
{
    int i;
    srand(time(NULL));

	arr[0] = newPoint((rand() % 20) + 1, (rand() % 20) + 1);
    for(i = 1; i < SIZE; i++)
        do
            arr[i] = newPoint((rand() % 20) + 1, (rand() % 20) + 1);
        while(isAlreadyInArray(arr, i, arr[i]));

    return;
}

void swap(point *pt1, point *pt2)
{
	point temp = *pt1;
	*pt1 = *pt2;
	*pt2 = temp;
	
	return;	
}

void sort(point *arr)
{ //this function implements the double selection sort (iterative version)
    int i, minPos, maxPos;

	for(i = 0; i < SIZE / 2; i++)
	{
		minPos = smallestPos(arr, i, SIZE - i);
		maxPos = largestPos(arr, i, SIZE - i);
		if(maxPos == i)
			maxPos = minPos;
		if(i != minPos)
			swap(&arr[i], &arr[minPos]);
		if(SIZE - i - 1 != maxPos)
			swap(&arr[SIZE - i - 1], &arr[maxPos]);
	}

    return;
}

void printPointsArr(point *arr)
{
    int i;

    for(i = 0; i < SIZE; i++)
        printf("Point no.%d: x: %d, y: %d\n", i, arr[i].x, arr[i].y);

	printf("\n\n");

    return;
}

void drawGraph(point *arr)
{ //draws the graph of the array
	int i, j, k;
	char graph[ROWS][COLS];

	for(i = COLS - 1; i >= 0; i--)
	{
		for(j = 0; j < ROWS; j++)
		{
			if(j == 0)
				graph[j][i] = '|';
			else
				graph[j][i] = ' ';
			
			for(k = 0; k < SIZE; k++)
				if(i == arr[k].y - 1 && j == arr[k].x)
					graph[j][i] = 'o';
		}
	}
	
	printf("y\n^\n");

	for(i = COLS - 1; i >= 0; i--)
	{
		for(j = 0; j < ROWS; j++)
			printf("%c", graph[j][i]);

		printf("\n");
	}

	for(i = 0; i < ROWS; i++)
		printf("-");
	
	printf("---> x\n");

	return;
}

point newPoint(int a, int b)
{
	point pt = {a, b};
	return pt;
}

int smallestPos(point *arr, int arrStart, int arrEnd)
{
	int i, pos = arrStart;
	point min = arr[arrStart];

	for(i = arrStart; i < arrEnd; i++)
	{
		if(arr[i].y < min.y || (arr[i].y == min.y && arr[i].x < min.x))
		{
			min = arr[i];
			pos = i;
		}
	}

	return pos;
}

int largestPos(point *arr, int arrStart, int arrEnd)
{
	int i, pos = arrStart;
	point max = arr[arrStart];

	for(i = arrStart; i < arrEnd; i++)
	{
		if(arr[i].y > max.y || (arr[i].y == max.y && arr[i].x > max.x))
		{
			max = arr[i];
			pos = i;
		}
	}

	return pos;
}

bool isSorted(point *arr)
{
	int i;

	for(i = 0; i < SIZE - 1; i++)
		if(arr[i].y > arr[i + 1].y || (arr[i].y == arr[i + 1].y && arr[i].x > arr[i + 1].x))
			return false;

	return true;
}

bool isAlreadyInArray(point *arr, int arrEnd, point pt)
{
	int i;

	for(i = 0; i < arrEnd; i++)
		if(arr[i].x == pt.x && arr[i].y == pt.y)
			return true;
	
	return false;
}