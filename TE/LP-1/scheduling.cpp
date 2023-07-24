#include <iostream>
#include <algorithm>
#include <iterator>
#include <queue>
using namespace std;

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
    int num;
    Process* arr;
    Process* readyQ;

    public:

    // get id, arrival time and burst time for each process
    void getProcess() {
        cout<<"\nEnter no. of processes: ";
        cin>>num;

        arr = new Process[num];

        for (int i=0; i<num; i++) {
            cout<<"\nProcess ID: ";
            cin>>arr[i].id;
            cout<<"Arrival Time: ";
            cin>>arr[i].at;
            cout<<"Burst Time: ";
            cin>>arr[i].bt;
        }
    }


    // get id, arrival time and burst time for each process
    void getPriorityProcess() {
        cout<<"\nEnter no. of processes: ";
        cin>>num;

        arr = new Process[num];

        for (int i=0; i<num; i++) {
            cout<<"\nProcess ID: ";
            cin>>arr[i].id;
            cout<<"Burst Time: ";
            cin>>arr[i].bt;
            cout<<"Priority: ";
            cin>>arr[i].pr;
        }
    }


    // used by std::sort()
    // returns lower value of arrival time
    static bool compareAT(Process x, Process y) {
        return x.at < y.at;
    }


    // used by std::sort()
    // returns lower value of burst time
    static bool compareBT(Process x, Process y) {
        return x.bt < y.bt;
    }


    // used by std::sort()
    // returns lower value of priority
    static bool comparePR(Process x, Process y) {
        return x.pr < y.pr;
    }


    // first come first serve
    void fcfs() {
        // sorting by arrival time
        sort(arr, arr+num, compareAT);

        // for 1st process
        arr[0].ct = arr[0].bt;
        arr[0].tt = arr[0].bt;
        arr[0].wt = 0;
        arr[0].rt = 0;

        // for the rest
        int completion = arr[0].bt;
        for (int i=1; i<num; i++) {
            completion += arr[i].bt;
            arr[i].ct = completion;
            arr[i].tt = arr[i].ct - arr[i].at;
            arr[i].wt = arr[i].tt - arr[i].bt;
            arr[i].rt = arr[i].wt;
        }
    }


    // shortest job first (non-preemptive)
    void sjf() {
        // sorting by burst time
        sort(arr, arr+num, compareBT);

        // for 1st process
        arr[0].ct = arr[0].bt;
        arr[0].tt = arr[0].bt;
        arr[0].wt = 0;
        arr[0].rt = 0;

        // for the rest
        int completion = arr[0].bt;
        for (int i=1; i<num; i++) {
            completion += arr[i].bt;
            arr[i].ct = completion;
            arr[i].tt = arr[i].ct - arr[i].at;
            arr[i].wt = arr[i].tt - arr[i].bt;
            arr[i].rt = arr[i].wt;
        }
    }


    //shortest remaining time first (preemptive sjf)
    void srtf() {
        // initialize remaining time for all processes
        int remainingTime[num];
        for (int i=0; i<num; i++) {
            remainingTime[i] = arr[i].bt;
        }

        int currentTime = 0;
        int completedTasks = 0;
        int minBurst = 999;
        int finishTime = 0;
        int shortestTask;
        bool active = false;

        while (completedTasks != num) {
            for (int j=0; j<num; j++) {
                if (arr[j].at <= currentTime && arr[j].bt < minBurst && remainingTime[j]> 0) {
                    shortestTask = j;
                    minBurst = arr[j].bt;
                    active = true;
                }
            }

            if (active == false) {
                currentTime++;
                continue;
            }

            minBurst = --remainingTime[shortestTask];
            if (minBurst == 0) {
                minBurst = 999;
            }

            if (remainingTime[shortestTask] == 0) {
                completedTasks++;
                finishTime = currentTime + 1;
                active = false;
                arr[shortestTask].wt = finishTime - arr[shortestTask].at - arr[shortestTask].bt;
                if (arr[shortestTask].wt < 0) {
                    arr[shortestTask].wt = 0;
                }
            }

            currentTime++;
        }
    }


    // priority (non-preemptive)
    void priority() {
        // sorting by priority
        sort(arr, arr+num, comparePR);

        // for 1st process
        arr[0].ct = arr[0].bt;
        arr[0].tt = arr[0].bt;
        arr[0].wt = 0;
        arr[0].rt = 0;

        // for the rest
        int completion = arr[0].bt;
        for (int i=1; i<num; i++) {
            completion += arr[i].bt;
            arr[i].ct = completion;
            arr[i].tt = arr[i].ct - arr[i].at;
            arr[i].wt = arr[i].tt - arr[i].bt;
            arr[i].rt = arr[i].wt;
        }
    }


    // displays average waiting time and turnaround time
    void average() {
        double awt = 0;
        double att = 0;
        
        for (int i=0; i<num; i++) {
            awt += arr[i].wt;
        }
        awt /= num;
        cout<<"\nAverage Waiting Time: "<<awt<<" secs";

        for (int i=0; i<num; i++) {
            att += arr[i].tt;
        }
        att /= num;
        cout<<"\nAverage Turn-Around Time: "<<att<<" secs";
        cout<<endl;
    }


    // displays gantt chart of process
    void ganttChart() {
        cout<<"\n------------------------------------\n";
        cout<<"|";
        for (int i=0; i<num; i++) {
            cout<<"  "<<arr[i].id<<"  |";
        }
        cout<<"\n------------------------------------\n";
        cout<<0<<"      ";
        for (int j=0; j<num; j++) {
            cout<<arr[j].ct<<"     ";
        }
        cout<<endl;
    }


    // displays process table
    void display() {
        cout<<"\n-------------------------------------------------------------------------------------------------------";
        cout<<"\nProcess ID | Arrival Time | Burst Time | Completion Time | Turn-Around Time | Wait Time | Response Time";
        cout<<"\n-------------------------------------------------------------------------------------------------------\n";

        for (int i=0; i<num; i++) {
            cout<<"    "<<arr[i].id<<"\t\t"<<arr[i].at<<"\t\t"<<arr[i].bt<<"\t\t"<<arr[i].ct<<"\t\t"<<arr[i].tt<<"\t\t"<<arr[i].wt<<"\t\t"<<arr[i].rt<<endl;
        }
        cout<<"-------------------------------------------------------------------------------------------------------\n";
    }
};


int main() {
    Scheduler obj;
    int ch;
    char ans = 'y';

    do
    {
        cout<<"\nChoose algorithm: \n1. FCFS\n2. SRTF\n3. Priority (Non-Preemptive)\nEnter choice: ";
        cin>>ch;

        switch(ch)
        {
            case 1:
            obj.getProcess();
            obj.fcfs();
            break;

            case 2:
            obj.getProcess();
            obj.srtf();
            break;

            case 3:
            obj.getPriorityProcess();
            obj.priority();
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