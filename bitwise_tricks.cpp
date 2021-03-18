#include<iostream>
#include<string>

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


//Inserts m into n such that m starts at bit j and ends at bit i
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

//Prints the binary representation of num
std::string printFloatingPoint(double num)
{
    if(num >= 1 || num <=0 )
    {
        return "Error!";
    }

    std::string result = "0.";
    while(num > 0)
    {
        if(result.length() >= 32)
        {
            return "Error!";
        }
        double r = num * 2;
        if(r >= 1)
        {
            result += '1';
            num  = r - 1;
        }
        else
        {
            result += '0';
            num = r;
        }
    }
    return result;
}

//Returns the longest sequence of 1s in the binary respresentation of num 
//after flipping only one bit
int flipBit(int num)
{
    if(~num == 0)
    {
        return sizeof(num)*8;
    }

    int previousLength = 0, currentLength = 0;
    int maxLength = 1;

    while(num != 0)
    {
        if((num & 1) == 1) // current bit is 1
        {
            currentLength++;
        }
        else if((num & 1) == 0) // current bit is 0
        {
            previousLength = (num & 2) == 0 ? 0 : currentLength;
            currentLength = 0;
        }
        maxLength = std::max(currentLength + previousLength + 1,maxLength);
        num = num >> 1;
    }
    return  maxLength;
}

void bitTricksTest()
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
}
void insertTest()
{
    int N = 1<<10;
    int M = 19;
    int result = insert(N,M,2,6);
    std::cout<<"N: ";
    decToBinary(N);
    std::cout<<"M: ";
    decToBinary(M);
    std::cout<<"Result: ";
    decToBinary(result);
}
void floatinPointTest()
{
    std::cout<<printFloatingPoint(0.75)<<std::endl;//0.11
    std::cout<<printFloatingPoint(0.95)<<std::endl;//Error!
    std::cout<<printFloatingPoint(0.25)<<std::endl;//0.01
    std::cout<<printFloatingPoint(1.95)<<std::endl;//Error!

}

void flipTest()
{
     std::cout<<flipBit(1775)<<std::endl;//11011101111 -> the length of 1s after flipping one bit is 8
     std::cout<<flipBit(16)<<std::endl;//10000 -> the lenght is 2
     std::cout<<flipBit(0)<<std::endl;//000...000 -> the length is 1
     std::cout<<flipBit(7)<<std::endl;//000..0111 -> the length is 4 (000...001111)
     std::cout<<flipBit(9)<<std::endl;//1001 -> the length is 2
}

int main()
{
    bitTricksTest();
    std::cout<<"=========================\n";

    insertTest();
    std::cout<<"=========================\n";

    floatinPointTest();
    std::cout<<"=========================\n";

    flipTest();
    return 0;
}