#include<iostream>


int maxSumSubarray(int arr[], size_t n)
{
    int currentMax = arr[0];
    int globalMax = arr[0];
    for(size_t i=1;i<n;i++)
    {
        currentMax = std::max(arr[i], currentMax + arr[i]);
        if(currentMax > globalMax)
            globalMax = currentMax;
    }
    return globalMax;
}

void testKadaneAlgorithm()
{
    int arr1[] = {-2,3,2,-1}; //[3,2] -> 5
    int arr2[] = {-2,-3,4,-1,-2,1,5,-3}; //[4,-1,-2,1,5] -> 7

    std::cout<< maxSumSubarray(arr1, 4)<<std::endl;
    std::cout<<maxSumSubarray(arr2, 8)<<std::endl;
}
int main()
{
    testKadaneAlgorithm();   
    return 0;
}
