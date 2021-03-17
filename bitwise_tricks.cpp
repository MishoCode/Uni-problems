#include<iostream>

bool getBit(int n, int i)
{
    return (n & (1 << i)) != 0;
}

int setBit(int n, int i)
{
    return n | (1 << i);
}

int clearBit(int n, int i)
{
    int mask = ~(1 << i);
    return n & mask;
}

//clears all bits from the most significant bit to the i-th
int clearFromMSBToI(int n, int i)
{
    int mask = (1 << i) - 1;
    return n & mask;
}

//clears all bits from the i-th to the 0
int clearFromIthToZero(int n, int i)
{
    //-1 = sequence of 1s
    int mask = (-1 << (i + 1)); 
    return n & mask;
}

int updateBit(int n, int i, bool isOne)
{
    int value = isOne ? 1 : 0;
    int mask = ~(1 << i);
    return (n & mask) | (value << i);
}

int insert(int n,int m, int i, int j)
{
    int ones = ~0;
    int left = ones<<(j + 1); // only 1s left from position j
    int right = (1 << i ) - 1; // only 1s right from position i
    int mask = left | right; // the mask contains only 1s except for the 0s between i and j
                             // mask = 111...111|101000101|1111...11

    int cleared = n & mask; //clear the bits from i to j
                            // cleared = 111...1|000...0|1111...1
    int mPos = m << i;

    return cleared | mPos;
}
void decToBinary(int n) 
{ 
    int binaryNum[32]; 

    int i = 0; 
    while (n > 0) { 
  
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    } 
  
    for (int j = i - 1; j >= 0; j--) 
        std::cout << binaryNum[j]; 
    std::cout<<std::endl;
} 

int main()
{
    int n = 9; //1001
    std::cout<<setBit(n,3)<<std::endl;//9
    std::cout<<setBit(n,1)<<std::endl;//11
    std::cout<<clearBit(n,0)<<std::endl;//8
    std::cout<<clearBit(n,1)<<std::endl;//9
    std::cout<<updateBit(n,2,true)<<std::endl;//13
    std::cout<<updateBit(n,2,false)<<std::endl;//9
    std::cout<<clearFromMSBToI(n,2)<<std::endl;//1
    std::cout<<clearFromIthToZero(n,2)<<std::endl;//8

    std::cout<<"=========================\n";

    int N = 1<<10;
    int M = 19;
    int result = insert(N,M,2,6);
    std::cout<<"N: ";
    decToBinary(N);
    std::cout<<"M: ";
    decToBinary(M);
    std::cout<<"Result: ";
    decToBinary(result);
    return 0;
}