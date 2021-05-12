#include<iostream>
#include<algorithm>

//There are n meetings; the i -th meeting starts at start[i] and ends at end[i]
//There is only one available meeting room 
//Find the maximum number of meetings that can be accommodaded so that meetings
//do not overlap in the time

struct Meeting
    {
        int start;
        int end;
    };
    bool comparator( Meeting m1, Meeting m2)
    {
        return m1.end < m2.end;
    }
    
    int maxMeetings(int start[], int end[], int n)
    {
        Meeting* m = new Meeting[n];
        for(int i=0;i<n;i++)
        {
            m[i].start = start[i];
            m[i].end = end[i];
        }
        
        std::sort(m,m+n,comparator);
        int counter = 1;
        int endTime =  m[0].end;
        for(int i=1;i<n;i++)
        {
            if(m[i].start > endTime)
            {
                counter++;
                endTime = m[i].end;
            }
        }
        
        delete[] m;
        return counter;
    }

    int main()
    {
        int start[] = {1,3,0,5,8,5};
        int final[] = {2,4,6,7,9,9};
        std::cout<<maxMeetings(start,final,6)<<std::endl;
    }