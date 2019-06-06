#include <iostream>

using namespace std;

struct node
{
	int no;			//process number
	int brst;		//burst time
	int wait;		//wait time updated time to time
	int tot;		//turn around time will calculated for every process at the end
	node *next;
};
class que
{
	private:
		node *front, *rear;			//actual ready que
		node *nfront , *nrear;		//this que for new and interupted proceses
	public:
		que()						//constructor
		{	
			front = NULL;
			rear = NULL;
			nfront = NULL;
			nrear = NULL;
		}
		void enque(int brst)			//when new process arrives burst time required and no is given automatically 
		{
			if (front == NULL)			//if que in empty
			{
				front = new node;
				front->no = 1;
				front->brst = brst;
				front->tot = brst;
				front->wait = 0;
				rear = front;
				return;
			}
			else if(rear->no >= 4)		//if ready que is completely filled
			{
				cout<<"do something else";
				if (nfront == NULL)			//if interupted and new process que is empty
				{
					nfront = new node;
					nfront->no = 1;
					nfront->brst = brst;
					nfront->tot = brst;
					nfront->wait = 0;
					nfront->tot = 0;
					nfront->next = NULL;
					nrear = nfront;
				}
				else
				{
					node *temp = new node;
					temp->no = nrear->no + 1;
					temp->brst = brst;
					temp->wait = 0;
					temp->tot = brst;
					temp->next = NULL;
					nrear->next = temp;
					nrear = temp;
				}
				
			}
			else
			{
				node *temp = new node;
				temp->no = rear->no + 1;
				temp->brst = brst;
				temp->wait = 0;
				temp->tot = brst;
				temp->next = NULL;
				rear->next = temp;
				rear = temp;
			}
		}
		void schedule(int quant)			//scheduling function
		{
			node *temp = front;
			int j =0;
			int p =0;
			while(front != NULL)			//go into scheduling loop if ready que have something
			{
				if (front->brst<quant)		//if burst is smaller then time quantum
				{
					if(front->next != NULL)		//que doesn't has only one ready process
					{	
						temp = front->next;		// if multiple nodes processes then add wait time in other processes
						while(temp!=NULL)
						{
							temp->wait += front->brst;
							temp = temp->next;
						}
					}
				}
				else							//if burst is greater then time auatum then simply add time quantum in wait time
				{
					if(front->next != NULL)		
					{
						temp = front->next;
						while(temp!=NULL)
						{
							temp->wait += quant;
							temp = temp->next;
						}
					}
				}
				front->brst -= quant;			//when we are done with wait time then subtract time quantum from process burst time
				cout<<front->brst<<":"<<front->no<<"    ";
				if (front->brst <= 0)			//if process is fully processed
				{
					cout<<"wait time for p "<<front->no<<"="<<front->wait<<"and tot = "<<(front->tot+front->wait)<<endl;
					front = front->next;
					
					//check_new();		//function to check new process in new pocess que
				}
				else						//if process is not fully processed go to next prcess
				{
					rear->next = front;
					front = front->next;
					rear = rear->next;
					rear->next = NULL;
					
				}
				j++;
				if(j==4)
				{
					cout<<endl;
					j =0;
				}
			}
		}
		void check_new()				//function for synchronization between new process que and ready que
		{
			if(nfront == NULL)			//if interrupted and new process is empty
			{
				return;
			}
			node *temp = front;
			int max = 1;
			if(front != NULL)			//if ready has no processes then add process from new que to ready que
			{
				while(temp != NULL)
				{
					temp->no = max;
					temp = temp->next;
					max++; 
				}
			}
			temp = front;
			
			
			
			while(rear->no != 4)		// if ready que have some space for processes then add from new to readu que
			{
				rear->next = new node;
				rear->next->no = rear->no+1;
				rear = rear->next;
				rear->brst = nfront->brst;
				nfront = nfront->next;
				rear->wait = 0;
				rear->tot = 0;
				rear->next = NULL;
			}
			
		}
		void print()
		{
			cout<<front->no;
			cout<<front->next->no;
			cout<<endl<<nfront->no;
			cout<<nfront->next->no;
		}
		~que()
		{
			delete front;
			delete rear;
	}
};

int main()
{
	que l;				//class object
	l.enque(3);
	l.enque(2);
	l.enque(1);
    l.enque(5);			//ready que is filled upto here
    //l.enque(15);		//from here onwards processes go to new processes que
    //l.enque(17);
	l.schedule(2);		//when processes are put into que then schedule them
	cout<<"processes schedulled successfully";
	l.print();
}
