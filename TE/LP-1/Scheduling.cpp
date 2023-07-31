#include <iostream>
#include <algorithm>
#include <iterator>
#include <queue>
using namespace std;

#define MAX 999

class Process
{
    string id;
    int at;
    int bt;
    int ct;
    int tt;
    int wt;
    int rt;
    int pr;
    
    public:
    Process() {
        id = "";
        at = 0;
        bt = 0;
        ct = 0;
        wt = 0;
        tt = 0;
        rt = 0;
        pr = 0;
    }

    Process(string n, int a, int b)
    {
        id = n;
        at = a;
        bt = b;
    }

    friend class Scheduler;
};


class Scheduler
{
    Process* arr;
    int num;
    int* remainingTime;

    public:
    void getProcess();
    void getPriorityProcess();
    void fcfs();
    void sjf();
    void srtf();
    void priority();
    void roundRobin(int);
    void average();
    void ganttChart();
    void display();

    // used by std::sort()
    // returns lower value of arrival time
    static bool compareAT(Process x, Process y) {
        return x.at < y.at;
    }

    // used by std::sort()
    // returns lower value of completion time
    static bool compareCT(Process x, Process y) {
        return x.ct < y.ct;
    }
};


// get id, arrival time and burst time for each process
void Scheduler::getProcess()
{
    cout<<"\nEnter no. of processes: ";
    cin>>num;

    arr = new Process[num];

    for (int i=0; i<num; i++)
    {
        cout<<"\nProcess ID: ";
        cin>>arr[i].id;
        cout<<"Arrival Time: ";
        cin>>arr[i].at;
        cout<<"Burst Time: ";
        cin>>arr[i].bt;
    }
}


// get id, arrival time and burst time for each process
void Scheduler::getPriorityProcess()
{
    cout<<"\nEnter no. of processes: ";
    cin>>num;

    arr = new Process[num];

    for (int i=0; i<num; i++)
    {
        cout<<"\nProcess ID: ";
        cin>>arr[i].id;
        cout<<"Arrival Time: ";
        cin>>arr[i].at;
        cout<<"Burst Time: ";
        cin>>arr[i].bt;
        cout<<"Priority: ";
        cin>>arr[i].pr;
    }
}


// first come first served algorithm
void Scheduler::fcfs()
{   
    // sorting by arrival time
    sort(arr, arr+num, compareAT);

    // for 1st process
    arr[0].ct = arr[0].bt;
    arr[0].tt = arr[0].bt;
    arr[0].wt = 0;
    arr[0].rt = 0;

    // for the rest
    int completion = arr[0].bt;
    for (int i=1; i<num; i++)
    {
        completion += arr[i].bt;
        arr[i].ct = completion;
        arr[i].tt = arr[i].ct - arr[i].at;
        arr[i].wt = arr[i].tt - arr[i].bt;
        arr[i].rt = arr[i].wt;
    }
}


// shortest job first (non-preemptive)
void Scheduler::sjf()
{
    // initialize remaining time for all processes
    remainingTime = new int[num];

    for (int i=0; i<num; i++)
    {
        remainingTime[i] = arr[i].bt;
    }

    int currentTime = 0;
    int completedTasks = 0;
    int shortestTask = 0;
    int minBurst = MAX;

    while (completedTasks != num)
    {
        bool taskInput = false;
        for (int j=0; j<num; j++)
        {
            if (arr[j].at <= currentTime && arr[j].bt < minBurst && remainingTime[j]> 0)
            {
                shortestTask = j;
                minBurst = arr[j].bt;
                taskInput = true;
            }
        }

        if (taskInput == false)
        {
            currentTime++;
            continue;
        }

        currentTime += arr[shortestTask].bt;
        remainingTime[shortestTask] = 0;
        minBurst = MAX;
        completedTasks++;
        taskInput = false;

        arr[shortestTask].ct = currentTime;
        arr[shortestTask].tt = arr[shortestTask].ct - arr[shortestTask].at;
        arr[shortestTask].wt = arr[shortestTask].tt - arr[shortestTask].bt;
    }
}


// shortest remaining time first (preemptive sjf)
void Scheduler::srtf()
{
    // initialize remaining time for all processes
    remainingTime = new int[num];

    for (int i=0; i<num; i++) {
        remainingTime[i] = arr[i].bt;
    }

    int currentTime = 0;
    int completedTasks = 0;
    int shortestTask = 0;
    int minBurst = MAX;
    bool active = false;

    while (completedTasks != num)
    {
        for (int j=0; j<num; j++)
        {
            if (arr[j].at <= currentTime && arr[j].bt < minBurst && remainingTime[j]> 0)
            {
                shortestTask = j;
                minBurst = arr[j].bt;
                active = true;
            }
        }

        if (active == false)
        {
            currentTime++;
            continue;
        }

        minBurst = --remainingTime[shortestTask];
        if (minBurst == 0) 
        {
            minBurst = MAX;
        }

        if (remainingTime[shortestTask] == 0)
        {
            completedTasks++;
            active = false;
            arr[shortestTask].ct = currentTime + 1;
            arr[shortestTask].tt = arr[shortestTask].ct - arr[shortestTask].at;
            arr[shortestTask].wt = arr[shortestTask].tt - arr[shortestTask].bt;

            if (arr[shortestTask].wt < 0)
            {
                arr[shortestTask].wt = 0;
            }
        }
        currentTime++;
    }
}


// priority algorithm (non-preemptive)
void Scheduler::priority()
{
    remainingTime = new int[num];

    for (int i=0; i<num; i++)
        remainingTime[i] = arr[i].bt;

    int currentTime = 0;
    int completedTasks = 0;
    int completionTime = 0;
    int higherPriority = 0;
    int remBurst = 0;
    int maxPriority = MAX;
    bool taskActive = false;

    while (completedTasks != num)
    {
        for (int j=0; j<num; j++)
        {
            if(arr[j].at <= currentTime && remainingTime[j] > 0 && arr[j].pr < maxPriority)
            {
                higherPriority = j;
                maxPriority = arr[j].pr;
                taskActive = true;
            }
        }

        if(!taskActive)
        {
            currentTime++;
            continue;
        }

        currentTime += arr[higherPriority].bt;
        remainingTime[higherPriority] = 0;
        maxPriority = MAX;
        taskActive = false;
        completedTasks++;
            
        arr[higherPriority].ct = currentTime;
        arr[higherPriority].tt =  arr[higherPriority].ct -  arr[higherPriority].at;
        arr[higherPriority].wt =  arr[higherPriority].tt -  arr[higherPriority].bt;
    }
}


// round robin algorithm (preemptive by nature)
void Scheduler::roundRobin(int tq)
{
    queue<int> readyQ;  // ready queue to hold process indices

    int currentTime = 0;
    int completedTasks = 0;
    int curr;  // holds the current process index
    
    // initialize remaining time array
    remainingTime = new int[num]; 
    for (int i=0; i<num; i++) 
    {
        remainingTime[i] = arr[i].bt;
    }
        
    // check for processes that have arrived at time 0 and push their indices to the Ready Queue
    for (int j=0; j<num; j++)
    {
        if (arr[j].at <= currentTime)
        {
            readyQ.push(j);
        }
    }

    // continue scheduling until all processes are completed
    while (completedTasks != num)
    {
        curr = readyQ.front(); // get the process index from the front of the Ready Queue
        readyQ.pop(); // remove the process from the front of the Ready Queue

        int counter = 0; // counter to keep track of time quantum spent on the current process

        // execute the process for a time quantum (ts) or its remaining burst time (whichever is smaller)
        while (counter!=tq && counter!=remainingTime[curr])
        {
            currentTime++; // increment the current time
            counter++; // increment the counter for time spent on the current process

            // check if any new processes have arrived at the current time and add them to the Ready Queue
            for (int j=0; j<num; j++)
            {
                if (arr[j].at == currentTime)
                {
                    readyQ.push(j);
                }
            }
        }

        remainingTime[curr] -= counter;  // reduce the remaining burst time of the current process by the time quantum spent on it

        // if the remaining burst time of the current process becomes zero, the process is completed
        if (remainingTime[curr] == 0)
        {
            arr[curr].ct = currentTime;
            arr[curr].tt = arr[curr].ct - arr[curr].at;
            arr[curr].wt = arr[curr].tt - arr[curr].bt;
            completedTasks++;
        }
        else
        {
            readyQ.push(curr); // if the process is not completed, push it back to the Ready Queue to be scheduled later
        }
    }
}



void Scheduler::average()
{
    double awt = 0;
    double att = 0;
        
    for (int i=0; i<num; i++)
    {
        awt += arr[i].wt;
    }
    awt /= num;
    cout<<"\nAverage Waiting Time: "<<awt<<" secs";

    for (int i=0; i<num; i++)
    {
        att += arr[i].tt;
    }
    att /= num;
    cout<<"\nAverage Turn-Around Time: "<<att<<" secs";
    cout<<endl;
}


// displays gantt chart from 0 to end time
void Scheduler::ganttChart()
{
    Process displayQ[num];

    // copy arr into new array displayQ
    copy(arr, arr+num, displayQ);

    // sort displayQ by completion time
    sort(displayQ, displayQ+num, compareCT);

    // print the processes
    cout<<"\n-";
    for (int i=0; i<num; i++)
    {
        cout<<"-------";
    }
    cout<<"\n|";
    for (int i=0; i<num; i++)
    {
        cout<<"  "<<displayQ[i].id<<"  |";
    }
    cout<<"\n-";
    for (int i=0; i<num; i++)
    {
        cout<<"-------";
    }

    // print the completion time of each process
    cout<<endl;
    cout<<0<<"      ";
    for (int j=0; j<num; j++)
    {
        cout<<displayQ[j].ct;
        if (displayQ[j].ct > 9)
            cout<<"     ";
        else
            cout<<"      ";
    }
    cout<<endl;
}


// displays the process table
void Scheduler::display()
{
    cout<<"\n-------------------------------------------------------------------------------------------------------";
    cout<<"\nProcess ID | Arrival Time | Burst Time | Completion Time | Turn-Around Time | Wait Time | Response Time";
    cout<<"\n-------------------------------------------------------------------------------------------------------\n";

    for (int i=0; i<num; i++) {
        cout<<"    "<<arr[i].id<<"\t\t"<<arr[i].at<<"\t\t"<<arr[i].bt<<"\t\t"<<arr[i].ct<<"\t\t"<<arr[i].tt<<"\t\t"<<arr[i].wt<<"\t\t"<<arr[i].rt<<endl;
    }
    cout<<"-------------------------------------------------------------------------------------------------------\n";
}



int main() {
    Scheduler obj;
    int ch, quantum;
    char ans = 'y';

    do
    {
        cout<<"\nChoose algorithm: \n1. FCFS\n2. SJF\n3. SRTF\n4. Priority\n5. Round Robin\n\nEnter choice: ";
        cin>>ch;

        switch(ch)
        {
            case 1:
            obj.getProcess();
            obj.fcfs();
            break;

            case 2:
            obj.getProcess();
            obj.sjf();
            break;

            case 3:
            obj.getProcess();
            obj.srtf();
            break;

            case 4:
            obj.getPriorityProcess();
            obj.priority();
            break;

            case 5:
            cout<<"\nEnter time quantum: ";
            cin>>quantum;
            obj.getProcess();
            obj.roundRobin(quantum);
            break;            

            default:
            cout<<"\nInvalid choice!";
            break;
        }

        cout<<"\nGANTT CHART:";
        obj.ganttChart();

        cout<<"\nPROCESS TABLE:";
        obj.display();

        obj.average();

        cout<<"\nContinue? (y/n): ";
        cin>>ans;
    } while (ans=='y' || ans=='Y');
}
