//quicksort
#include <iostream>
#include <vector>
#include "RectStash.h"



using namespace std;


//vec + 2 indices in, swap the values at the 2 indices in the given arrays
void swap(vector<Rect*>& vec, int x, int y)
{
	//PULL THE LEVER KRONK

	Rect* tempx = vec[x];
	Rect* tempy = vec[y];

	// SWITCH LEVERS KRONK

	vec[x] = tempy;
	vec[y] = tempx;

	//i like the emporers new groove

	return;
}




int partition(vector<Rect*>& vec, int low, int high)
{
	//pivot selection/sorting mini algo
	Rect* pivot = vec[low];
	int left = low;
	int right = high - 1;
	int j = low + 1;
	for (int i = low + 1; i < high; i++)
	{

		if ( (*pivot).compare( vec[j] ))
		{
			//put things less than the pivot on the left of the pivot
			swap(vec, j, left);
			left++;
			j++;
		}

		else
		{
			swap(vec, j, right);
			right--;
			//put things bigger than the pivot to the right of the pivot
		}

	}

	return left;

}



void quicksort(vector<Rect*>& vec, int low, int high)
{
	//sorting main branching algo
	int pivot = 0;
	if (low < high)
	{
		//find pivot
		pivot = partition(vec, low, high);

		//sort based on pivot
		quicksort(vec, low, pivot);
		quicksort(vec, pivot + 1, high);

	}
	return;
}