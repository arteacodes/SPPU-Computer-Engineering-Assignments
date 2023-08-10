#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

class Paging
{
    int frames;
    int num;
    int* pages;

    public:
    Paging()
    {
        frames = 0;
        num = 0;
    }

    void getReferenceString();
    void FIFO();
    void OPRA();
    void LRU();
    void display();
};


// accepts an array of integers which forms the reference string
void Paging::getReferenceString()
{
    cout<<"\nEnter no. of frames: ";
    cin>>frames;

    cout<<"Enter no. of pages: ";
    cin>>num;

    pages = new int[num];

    cout<<"Enter the reference string: ";
    for (int i=0; i<num; i++) 
    {
        cin>>pages[i];
    }
}


// first in first out algorithm
void Paging::FIFO()
{
    int hit = 0;
    int miss = 0;

    // unordered set to store current page set for quick lookup
    unordered_set<int> currentSet;

    // queue to implement FIFO technique
    queue<int> q;

    cout<<"\nPage\tPage Frames";
    cout<<"\n----------------------------\n";

    // for iteration over reference string
    for (int i=0; i<num; i++) 
    {
        // if there are empty frames
        if (currentSet.size() < frames)
        {
            // if incoming page is absent from set of current pages
            if (currentSet.find(pages[i]) == currentSet.end())
            {
                currentSet.insert(pages[i]);
                q.push(pages[i]);
                miss++;

                // print the page number and the frames
                cout<<pages[i]<<"\t";
                for (auto f=currentSet.begin(); f!=currentSet.end(); f++)
                {
                    cout<<*f<<"\t";
                }
                cout<<endl;
            }
            // if incoming page is already in set of current pages
            else
            {
                hit++;

                // print only page number since it is a hit
                cout<<pages[i]<<endl;
                break;
            }
        }
        // if all frames are full, replace the page that entered before the rest
        else 
        {
            // if incoming page is not already in set of current pages
            if (currentSet.find(pages[i]) == currentSet.end())
            {
                // remove the first page from queue
                int page = q.front();
                q.pop();

                // remove the page from set of current pages
                currentSet.erase(page);

                // push new page into set of current pages and queue
                currentSet.insert(pages[i]);
                q.push(pages[i]);
                miss++;

                // print the page number and the frames
                cout<<pages[i]<<"\t";
                for (auto f=currentSet.begin(); f!=currentSet.end(); f++)
                {
                    cout<<*f<<"\t";
                }
                cout<<endl;
            }
            // if incoming page is already in set of current pages
            else
            {
                hit++;

                // print only page number since it is a hit
                cout<<pages[i]<<endl;
                break;
            }
        }
    }

    // print the no. of hits and misses
    cout<<"\nNo. of hits = "<<hit;
    cout<<"\nNo. of page faults = "<<miss;
    cout<<endl;
}


// optimal page replacement algorithm
void Paging::OPRA()
{
    int hit = 0;
    int miss = 0;

    // array containing current pages
    int currentSet[frames];
    for (int f=0; f<frames; f++)
    {
        currentSet[f] = -1;
    }

    cout<<"\nPage\tPage Frames";
    cout<<"\n----------------------------\n";

    // for iteration over reference string
    for (int i=0; i<num; i++)
    {
        bool found = false;
        for (int j=0; j<frames; j++)
        {
            // if incoming page is present in set of current pages
            if (currentSet[j] == pages[i])
            {
                found = true;
                hit++;

                // print only page number since it is a hit
                cout<<pages[i]<<endl;
                break;
            }
        }

        // if incoming page is absent from set of current pages
        if (!found)
        {
            // find an empty frame
            bool freeFrame = false;
            for (int k=0; k<frames; k++)
            {
                if (currentSet[k] == -1)
                {
                    freeFrame = true;

                    // insert page into the empty frame
                    currentSet[k] = pages[i];
                    miss++;

                    // print the page number and the frames
                    cout<<pages[i]<<"\t";
                    for (int f=0; f<frames; f++)
                    {
                        cout<<currentSet[f]<<"\t";
                    }
                    cout<<endl;

                    break;
                }
            }

            // if no empty frame is available
            if (!freeFrame)
            {
                // initialize array to store next index of each page in current set
                // default value is 1 + size of ref string
                int nextIndex[frames];
                for (int f=0; f<frames; f++)
                {
                    nextIndex[f] = num+1;
                }

                // assign the next index
                for (int m=0; m<frames; m++)
                {
                    for (int n=i; n<num; n++)
                    {
                        if (pages[n] == currentSet[m])
                        {
                            nextIndex[m] = n;
                            break;
                        }
                    }
                }

                // find the frame that occurs farthest from current page
                int farthest = 0;
                for (int p=0; p<frames; p++)
                {
                    if (nextIndex[p] > nextIndex[farthest])
                    {
                        farthest = p;
                    }
                }
                
                // replace the farthest occuring page with the incoming page
                currentSet[farthest] = pages[i];
                miss++;

                // print the page number and the frames
                cout<<pages[i]<<"\t";
                for (int f=0; f<frames; f++)
                {
                    cout<<currentSet[f]<<"\t";
                }
                cout<<endl;
            }
        }
    }
    
    // print the no. of hits and misses
    cout<<"\nNo. of hits = "<<hit;
    cout<<"\nNo. of page faults = "<<miss;
    cout<<endl;
}


// least recently used algorithm
void Paging::LRU()
{
    int hit = 0;
    int miss = 0;

    // array containing current pages
    int currentSet[frames];
    for (int f=0; f<frames; f++)
    {
        currentSet[f] = -1;
    }

    cout<<"\nPage\tPage Frames";
    cout<<"\n----------------------------\n";

    // for iteration over reference string
    for (int i=0; i<num; i++)
    {
        bool found = false;
        for (int j=0; j<frames; j++)
        {
            // if incoming page is present in set of current pages
            if (currentSet[j] == pages[i])
            {
                found = true;
                hit++;

                // print only page number since it is a hit
                cout<<pages[i]<<endl;
                break;
            }
        }

        // if incoming page is absent from set of current pages
        if (!found)
        {
            // find an empty frame
            bool freeFrame = false;
            for (int k=0; k<frames; k++)
            {
                if (currentSet[k] == -1)
                {
                    freeFrame = true;

                    // insert page into the empty frame
                    currentSet[k] = pages[i];
                    miss++;

                    // print the page number and the frames
                    cout<<pages[i]<<"\t";
                    for (int f=0; f<frames; f++)
                    {
                        cout<<currentSet[f]<<"\t";
                    }
                    cout<<endl;

                    break;
                }
            }

            // if no empty frame is available
            if (!freeFrame)
            {
                // initialize array to store last/previous index of each page in current set
                int prevIndex[frames];

                // assign the next index
                for (int m=0; m<frames; m++)
                {
                    for (int n=i; n>=0; n--)
                    {
                        if (pages[n] == currentSet[m])
                        {
                            prevIndex[m] = n;
                            break;
                        }
                    }
                }

                // find the frame that occurred most recently (lowest index)
                int closest = 0;
                for (int p=0; p<frames; p++)
                {
                    if (prevIndex[p] < prevIndex[closest])
                    {
                        closest = p;
                    }
                }
                
                // replace the closest occuring page with the incoming page
                currentSet[closest] = pages[i];
                miss++;

                // print the page number and the frames
                cout<<pages[i]<<"\t";
                for (int f=0; f<frames; f++)
                {
                    cout<<currentSet[f]<<"\t";
                }
                cout<<endl;
            }
        }
    }
    
    // print the no. of hits and misses
    cout<<"\nNo. of hits = "<<hit;
    cout<<"\nNo. of page faults = "<<miss;
    cout<<endl;
}



int main()
{
    Paging p;
    int ch;
    char ans = 'y';

    do
    {
        cout<<"\n1. Input\n2. FIFO\n3. OPRA\n4. LRU\n5. Exit\nEnter choice: ";
        cin>>ch;

        switch(ch)
        {
            case 1:
            p.getReferenceString();
            break;

            case 2:
            p.FIFO();
            break;

            case 3:
            p.OPRA();
            break;

            case 4:
            p.LRU();
            break;

            default:
            cout<<"\nInvalid choice!";
            break;
        }

        cout<<"\nContinue? (y/n): ";
        cin>>ans;
    } while (ans=='y' || ans=='Y');
}
