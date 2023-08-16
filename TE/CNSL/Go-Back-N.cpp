#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class GoBackN
{
    int frames;
    int windowSize;
    int transmitted;

    public:
    GoBackN()
    {
        frames = 0;
        windowSize = 0;
        transmitted = 0;
    }

    void input()
    {
        cout<<"\nEnter no. of frames: ";
        cin>>frames;
        cout<<"Enter window size: ";
        cin>>windowSize;
    }


    void simulate()
    {
        srand(time(NULL));
        int i = 1;

        while (i <= frames)
        {
            int x = 0;
            for (int j=i; j<i+windowSize && j<=frames; j++)
            {
                cout<<"Sent Frame "<<j<<endl;
                transmitted++;
            }

            for (int j=i; j<i+windowSize && j<=frames; j++)
            {
                bool received = rand()%2;

                if (received)
                {
                    cout<<"\nPositive Acknowledgement for Frame "<<j<<endl;
                    x++;
                }
                else
                {
                    cout<<"\nNegative Acknowledgement for Frame "<<j<<". Retransmitting Window"<<endl;
                    break;
                }
            }
            cout<<endl;
            i += x;
        }

        cout.width(70);
        cout.fill('-');
        cout<<"\nTotal no. of transmissions = "<<transmitted<<endl;
        cout.width(41);
        cout.fill('-');
        cout<<"\n";
    }
};


int main()
{
    GoBackN obj;
    obj.input();
    obj.simulate();
}