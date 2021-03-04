#include<iostream>

void printArray(int* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void merge(int* arr, size_t l, size_t m, size_t r)
{
	size_t leftSize = m - l + 1;
	size_t rightSize = r - m;
	int* leftArr = new int[leftSize];
	int* rightArr = new int[rightSize];

	for (size_t i = 0; i < leftSize; i++)
	{
		leftArr[i] = arr[l + i];
	}
	for (size_t i = 0; i < rightSize; i++)
	{
		rightArr[i] = arr[m + 1 + i];
	}

	size_t i = 0, j = 0, k = l;
	while (i < leftSize && j < rightSize)
	{
		if (leftArr[i] < rightArr[j])
		{
			arr[k] = leftArr[i];
			i++;
		}
		else
		{
			arr[k] = rightArr[j];
			j++;
		}
		k++;
	}
	while (i < leftSize)
	{
		arr[k] = leftArr[i];
		i++;
		k++;
	}
	while (j < rightSize)
	{
		arr[k] = rightArr[j];
		j++;
		k++;
	}

	delete[] leftArr, rightArr;
}

void mergeSort(int* arr, size_t l, size_t r)
{
	if (l < r)
	{
		size_t m = l + (r - l) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
size_t partition(int* arr, size_t l, size_t h)
{
	int pivot = arr[h];
	int i = l - 1;

	for (size_t j = l; j < h; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[h]);
	return i + 1;
}
void quickSort(int* arr, size_t l, size_t h)
{
	if (l < h)
	{
		size_t pi = partition(arr, l, h);
		quickSort(arr, l, pi-1);
		quickSort(arr, pi + 1, h);
	}
}

void countSort(int* arr, size_t size, size_t range)
{
	int* outputArr = new int[range];
	int* countArr = new int[range];

	for (size_t i = 0; i < range; i++)
	{
		countArr[i] = 0;
	}
	for (size_t i = 0; i < size; i++)
	{
		countArr[arr[i]]++;
	}
	for (size_t i = 1; i < range; i++)
	{
		countArr[i] += countArr[i - 1];
	}
	for (size_t i = 0; i < size; i++)
	{
		outputArr[countArr[arr[i]] - 1] = arr[i];
		countArr[arr[i]]--;
	}
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = outputArr[i];
	}

	delete[] outputArr, countArr;
}
void testSorting()
{
	int arr[] = { 1,5,4,3,2,11,8,0 }; // size = 8
	printArray(arr, 8);
	mergeSort(arr, 0, 7);
	//quickSort(arr, 0, 7);
	//countSort(arr, 8, 12);
	printArray(arr, 8);
	
}
int main()
{
	testSorting();
	return 0;
}