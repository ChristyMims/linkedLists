///////////////////////////////////////////////////////////////////////////////////////////////////
//  This program allows a user to enter a number between 20 and 100 in the user prompt window or the 
//  command line. The program will also write to a binary file called "numbers.bin" and then 
//  randomly generate however many numbers the user entered. The randomly generated numbers will
//  then be put in a linked list in the order they are generated, backwards, low to high, and 
//  high to low. There are also functions to print and delete the built linked lists.
//
//  Christy Mims
//
//  06/20/2019
///////////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<ctime>
#include<fstream>

using namespace std;

struct  node
{
	int number;
	node *next;
};

// function headers
int promptUser(int);
int writeBinaryFile(int);
int generatedOrder(int);
int backwardOrder(int);
int lowToHigh(int);
int highToLow(int);
void deleteList(node *);
void printLinkedList(node *);
void callFunctions(int);


int main(int argc, char *argv[])
{
	// see if the list size was passed in from the command line
	if (argc == 2)
	{
		// cast the list size from ascii to int
		int listSize = atoi(argv[1]);

		// checks to see if valid list size was entered
		if ((listSize < 20) && (listSize > 100))
		{
			// calls all the functions to perform work
			callFunctions(listSize);
		}

		// if nonvalid number was entered
		else
		{
			// calls the promptUser function to get valid list size
			int listSize = 0;
			listSize = promptUser(listSize);

			// calls all the functions to perform work
			callFunctions(listSize);
		}
	}
	
	// if list size was not entered in the command line
	else
	{
		// calls the promptUser function to get list size
		int listSize = 0;
		listSize = promptUser(listSize);

		// calls all the functions to perform work
		callFunctions(listSize);

	}




	//system("pause");
	return(0);

}

int promptUser(int listSize)
{

	// user prompt
	cout << "Enter a number between 20 and 100." << endl;

	// loop to make sure user enters number within range
	while(listSize < 20 || listSize > 100)
	{
		// take in list size from the user
		cin >> listSize;
		
		// formatting
		cout << endl;

		if (cin.fail() || listSize < 20 || listSize > 100)
		{
			// clears cin and the buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// notify the user to enter a number in specified range
			cout << endl << "Please enter a number between 20 and 100." << endl;
		}

	}

	// returns the amount of data the user wants to generate
	return(listSize);
}

void callFunctions(int listSize)
{
	// calls the write binary function
	writeBinaryFile(listSize);

	// calls function to put generated order in linked list
	generatedOrder(listSize);

	// calls function to put generated order last to first in linked list
	backwardOrder(listSize);

	// calls the high to low function
	highToLow(listSize);

	// calls the low to high function
	lowToHigh(listSize);
}

int writeBinaryFile(int listSize)
{
	// create and name out stream writer 
	ofstream writeBinaryFile;

	// create the file and write it as binary
	writeBinaryFile.open("numbers.bin", ios::out | ios::binary);

	if (!writeBinaryFile)
	{
		cout << "Binary file was not opened or created for writing." << endl << endl;
		return(2);
	}

	// 'seeds' the number random function with time from the computer
	srand(time(NULL));

	// tells user how much data will be generatedz
	cout << "List size to be generated " << listSize << endl;
	cout << "Start writing data to file." << endl << endl;

	// variable to hold the numbers that are randomly generated
	int fileNumbers = 0;

	// for loop to generate the amount of data the user specified
	for (int i = 0; i < listSize; i++)
	{
		// generate numbers between 0 and 99
		fileNumbers = (rand() * rand()) % 100;

		// outputs the numbers to the console for user to see
		cout << fileNumbers << endl;

		// writes numbers to the binary file
		writeBinaryFile.write(reinterpret_cast<const char *>(&fileNumbers), sizeof(int));
	}

	// formatting
	cout << endl << endl;
	
	// closes the binary file
	writeBinaryFile.close();

}

int generatedOrder(int listSize)
{
	// creates pointer to head and keeps track of beginning of list
	struct node *Head;

	// creates a new nod and sets it equal to head
	Head = new(node);

	// checks to see if new node got created
	if (Head == NULL)
	{
		cout << endl << "Fatal error, could not create head node." << endl;
		system("PAUSE");
		return(1);
	}

	// if head was created it sets head pointer to null since it is last in the list
	Head->next = NULL;

	// creates the stream reader
	ifstream generatedOrder;

	// opens the file
	generatedOrder.open("numbers.bin", ios::in | ios::binary);

	// lets the user know if the file did not open
	if (!generatedOrder)
	{
		cout << "Could not open binary file for reading" << endl << endl;
		return(2);
	}

	// lets the user know reading from file has begun
	cout << "Begin reading from file" << endl;
	//
	cout << "Generated Order" << endl << endl;

	// loop until reaches end of file
	for(int i = 0; i < listSize; i++)
	{
		// set equal to head so can traverse list  without losing head
		struct node *Current = Head;

		// creates pointer to new node
		struct node *newNode;

		// read in from file
		int num = 0;
		generatedOrder.read((char *)&num, sizeof(int));

		// while loop to look for the end of the list
		while (Current->next != NULL)
		{
			// increments current pointer
			Current = Current->next;
		}

		// outputs if not enough memory
		if ((newNode = new(node)) == NULL)
		{
			cout << "Not enough memory!!" << endl;
			return(1);
		}

		// puts data into new node
		newNode->number = num;

		// output to know if data was put into new node
		//cout << newNode->number << endl;

		// inserts the node into the linked list
		newNode->next = Current->next;
		Current->next = newNode;
	}

	// prints and formats the linked list
	printLinkedList(Head);

	// Deletes the linked list
	deleteList(Head);

	// close the file
	generatedOrder.close();
}

int backwardOrder(int listSize)
{
	// creates pointer to head and keeps track of beginning of list
	struct node *Head;

	// creates a new node and sets it equal to head
	Head = new(node);

	// checks to see if new node got created
	if (Head == NULL)
	{
		cout << endl << "Fatal error, could not create head node." << endl;
		system("PAUSE");
		return(1);
	}

	// if head was created it sets head pointer to null since it is last in the list
	Head->next = NULL;

	// creates the stream reader
	ifstream backwardOrder;

	// opens the file
	backwardOrder.open("numbers.bin", ios::in | ios::binary);

	// lets the user know if the file did not open
	if (!backwardOrder)
	{
		cout << "Could not open binary file for reading" << endl << endl;
		return(2);
	}

	// lets the user know reading from file has begun
	cout << "Begin reading from file" << endl;
	cout << "Generated Order from last to first" << endl << endl;

	// loop until reaches end of file
	for (int i = 0; i < listSize; i++)
	{
		// set equal to head so can traverse list  without losing head
		struct node *Current = Head;

		// creates pointer to new node
		struct node *newNode;

		// read in from file
		int num = 0;
		backwardOrder.read((char *)&num, sizeof(int));

		// outputs if not enough memory
		if ((newNode = new(node)) == NULL)
		{
			cout << "Not enough memory!!" << endl;
			return(1);
		}

		// puts data into new node
		newNode->number = num;

		// output to know if data was put into new node
		//cout << newNode->number << endl;

		// inserts the node into the linked list
		newNode->next = Current->next;
		Current->next = newNode;
	}

	// prints and formats the linked list
	printLinkedList(Head);

	// Deletes the linked list
	deleteList(Head);

	// close the file
	backwardOrder.close();
}

int highToLow(int listSize)
{
	// creates pointer to head and keeps track of beginning of list
	struct node *Head;

	// creates a new nod and sets it equal to head
	Head = new(node);

	// checks to see if new node got created
	if (Head == NULL)
	{
		cout << endl << "Fatal error, could not create head node." << endl;
		system("PAUSE");
		return(1);
	}

	// if head was created it sets head pointer to null since it is last in the list
	Head->next = NULL;

	// creates the stream reader
	ifstream highToLow;

	// opens the file
	highToLow.open("numbers.bin", ios::in | ios::binary);

	// lets the user know if the file did not open
	if (!highToLow)
	{
		cout << "Could not open binary file for reading" << endl << endl;
		return(2);
	}

	// lets the user know reading from file has begun and that the list will be
	// lowest number to highest number
	cout << "Begin reading from file" << endl;
	cout << "List will be printed Highest to Lowest." << endl << endl;


	// loop until reaches end of file
	for (int i = 0; i < listSize; i++)
	{
		// set equal to head so can traverse list  without losing head
		struct node *Current = Head;

		// creates pointer to new node
		struct node *newNode;

		// read in from file
		int num = 0;
		highToLow.read((char *)&num, sizeof(int));

		// while loop to look for the end of the list and for a number higher than current
		while ((Current->next != NULL) && (Current->next->number > num))
		{
			// increments current pointer
			Current = Current->next;
		}

		// outputs if not enough memory
		if ((newNode = new(node)) == NULL)
		{
			cout << "Not enough memory!!" << endl;
			return(1);
		}

		// puts data into new node
		newNode->number = num;

		// output to know if data was put into new node
		//cout << newNode->number << endl;

		// inserts the node into the linked list
		newNode->next = Current->next;
		Current->next = newNode;
	}

	// prints and formats the linked list
	printLinkedList(Head);

	// Deletes the linked list
	deleteList(Head);

	// close the file
	highToLow.close();
}

int lowToHigh(int listSize)
{
	// creates pointer to head and keeps track of beginning of list
	struct node *Head;

	// creates a new nod and sets it equal to head
	Head = new(node);

	// checks to see if new node got created
	if (Head == NULL)
	{
		cout << endl << "Fatal error, could not create head node." << endl;
		system("PAUSE");
		return(1);
	}

	// if head was created it sets head pointer to null since it is last in the list
	Head->next = NULL;

	// creates the stream reader
	ifstream lowToHigh;

	// opens the file
	lowToHigh.open("numbers.bin", ios::in | ios::binary);

	// lets the user know if the file did not open
	if (!highToLow)
	{
		cout << "Could not open binary file for reading" << endl << endl;
		return(2);
	}

	// lets the user know reading from file has begun and that the list will be
	// lowest number to highest number
	cout << "Begin reading from file" << endl;
	cout << "List will be printed Lowest to Highest." << endl << endl;


	// loop until reaches end of file
	for (int i = 0; i < listSize; i++)
	{
		// set equal to head so can traverse list  without losing head
		struct node *Current = Head;

		// creates pointer to new node
		struct node *newNode;

		// read in from file
		int num = 0;
		lowToHigh.read((char *)&num, sizeof(int));

		// while loop to look for the end of the list and for a number higher than current
		while ((Current->next != NULL) && (Current->next->number < num))
		{
			// increments current pointer
			Current = Current->next;
		}

		// outputs if not enough memory
		if ((newNode = new(node)) == NULL)
		{
			cout << "Not enough memory!!" << endl;
			return(1);
		}

		// puts data into new node
		newNode->number = num;

		// output to know if data was put into new node
		//cout << newNode->number << endl;

		// inserts the node into the linked list
		newNode->next = Current->next;
		Current->next = newNode;
	}

	// prints and formats the linked list
	printLinkedList(Head);

	// Deletes the linked list
	deleteList(Head);

	// close the file
	lowToHigh.close();
}


void printLinkedList(node *Head)
{
	// create a temp pointer and set it equal to head
	struct node *temp;
	temp = Head->next;


	// used for formatting output to the console
	int counter = 1;

	while (temp != NULL)
	{
		// print the node then a tab to separate the numbers
		cout << temp->number << "\t";

		// formatting: after every 5 nodes are printed the a newline is inserted
		// then the counter is reset
		if (counter % 5 == 0)
		{
			cout << endl;
			counter = 0;
		}

		// advances pointer
		temp = temp->next;

		// increments the counter
		counter = counter + 1;

	}

	// formatting for console
	cout << endl << endl;
}

void deleteList(node *Head)
{
	struct node *temp;

	// Loops through the list and deletes the list starting after head, then sets head equal
	// to temp
	while (Head != NULL)
	{
		temp = Head->next;
		delete(Head);
		Head = temp;
	}
}

