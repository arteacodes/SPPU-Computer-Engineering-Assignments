#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

class Paging
{
    int frames;
    int num;
    int* pages;
    int hit;
    int miss;

    public:
    Paging()
    {
        frames = 0;
        num = 0;
        hit = 0;
        miss = 0;
    }

    void getReferenceString();
    void FIFO();
    void OPRA();
    void LRU();
    void search();
    int predict(int, int, unordered_set<int>);
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
    // unordered set to store current page set for quick lookup
    unordered_set<int> set;

    // queue to implement FIFO technique
    queue<int> q;

    for (int i=0; i<num; i++) 
    {
        // if there are empty frames
        if (set.size() < frames)
        {
            // if incoming page is absent from set of current pages
            if (set.find(pages[i])==set.end())
            {
                set.insert(pages[i]);
                q.push(pages[i]);
                miss++;
            }
            // if incoming page is already in set of current pages
            else
            {
                hit++;
            }
        }
        // if all frames are full, replace the page that entered before the rest
        else 
        {
            // if incoming page is not already in set of current pages
            if (set.find(pages[i])==set.end())
            {
                // remove the first page from queue
                int page = q.front();
                q.pop();

                // remove the page from set of current pages
                set.erase(page);

                // push new page into set of current pages and queue
                set.insert(pages[i]);
                q.push(pages[i]);
                miss++;
            }
            // if incoming page is already in set of current pages
            else
            {
                hit++;
            }
        }
    }

    // print the no. of hits and misses
    cout<<"\nNo. of hits = "<<hit;
    cout<<"\nNo. of page faults = "<<miss;
    cout<<endl;
}


// returns the number/page from current set that occurs farthest in the future
int Paging::predict(int page, int index, unordered_set<int> set)
{
    int maxIndex = -1;
    unordered_set<int>::iterator itr;

    for (itr=set.begin(); itr!=set.end(); itr++)
    {
        
    }

    for (int i=index; i<num; i++)
    {
        itr = set.begin();
        
    }
}


// optimal page replacement algorithm
void Paging::OPRA()
{
    int incoming;
    unordered_set<int> set;

    unordered_set<int>::iterator itr;

    for (int i=0; i<num; i++)
    {
        incoming = pages[i];

        // if there are empty frames
        if (set.size() < frames)
        {
            // if incoming page is absent from set of current pages
            if (set.find(incoming) == set.end())
            {
                set.insert(incoming);
                miss++;
            }
            else
            {
                hit++;
            }
        }
        // if all frames are full, replace the page that will occur farthest in the future
        else
        {

        }
        
    }
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

            default:
            cout<<"\nInvalid choice!";
            break;
        }

        cout<<"\nContinue? (y/n): ";
        cin>>ans;
    } while (ans=='y' || ans=='Y');
}