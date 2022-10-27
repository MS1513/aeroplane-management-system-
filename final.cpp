#include <bits/stdc++.h>
using namespace std;
// forward declaration
class Person;
class Flight;
class Queue;
/* ----CLASSES---- */

class Menu //class for managing the app's menu
{
	public:
		static void displayMenu(); // displays the menu
		static void select(int selection); // receives user's input and performs the corresponding function
		static void exit_prog(); // exits the app
};
struct Time // structure for managing the Arrival and Departing times
{
	int min;
	int hour;
};
class Flight // class for managing the availabe functions of a flight
{
	private:

		int flightNo, cost, seats, booked_seats;
		string from, to, plane_type;
		Time t_leave, t_arrive;

	public:
		/* --ADD/REMOVE FLIGHTS--*/
		void addFlight(); //manages the addition of flights (menu option No. 1)
		/* --DISPLAY FLIGHTS--*/
		static void displaySchedule(); //displays the flights registered in the system (menu option No. 3)
        /* --BOOK SEATS--*/
		static void resSeat(int num, int val); // fluctuates the reserved seats of a flight
        /* --FLIGHT CHECKERS--*/
		static bool flightExists(int num); // check flight is booked
		static bool checkForSeats(int num); // checks for already registered flight in the system
        /* --GETTERS--*/
		int getFlightNo() { return this -> flightNo; }
		Time getLeavingTime() { return this -> t_leave; }
		Time getArrivingTime() { return this -> t_arrive; }
		string getDeparture() { return this -> from; }
		string getDestination() { return this -> to; }
};
class Person //class for managing the functions of a passenger
{
	private:

		int passportNo, tel;
		list<int> flights;
		string name, surname, nationallity, address;

	public:
		/* --BOOK FLIGHT-- */
		void book(); // book flight for each customer (Menu Option ?? 6)
		void bookFromQueue(int num); // book flight for the oldest customer in
					    // (call ONLY when a reservation is canceled)
		void cancel(); //cancel a reservation (Menu Option ?? 7)

		/* --SHOW PASSENGER'S INFO-- */
		static bool displayPersonInfo(int passport);
/* --CHECHKER FOR UNIQUE PASSPORT-- */
		static bool uniquePass(int passport);
     	/* --GETTERS-- */
		int getPassport() { return this -> passportNo; }
		string getName() { return this -> name; }
		string getSurname() { return this -> surname; }

};
struct Node //structure for managing each flight's queue
{
    Person person;
    Node* next;
};
class Queue // class that stores passengers on each flight's queue
{

    private:

	int queueNo;
        Node* rear;
        Node* front;

	public:
		/* --CREATE NEW QUEUE-- */
        Queue(int queueId); // queueID is the same as the flight number for each flight

		/* --ADD/REMOVE ELEMENTS-- */
        void enqueue(Person p); // add a new passenger
        void dequeue(); // remove the passenger add last

		/* --VIEW OF DATA-- */
		static void display(int num); // displays registered customers
									 // in the waiting queue of each flight
		Person oldest();//returns the object of the oldest client, through the Person class
        /* --CHECK FOR EMPTY QUEUE-- */
		bool isEmpty(); // returns true if queue is empty
		/* --GETTERS-- */
		int getNo() { return this -> queueNo; }
		Node* getFront() { return this -> front; }
		Node* getRear() { return this -> rear; }
        /* --SETTERS-- */
		void setFront(Node* f) {
			if (f == 0){
				this -> front = NULL;
			}else{
				this -> front = f;
			}
		}
		void setRear(Node* r) {
			this -> rear = r;
		}
};

/* ----FUNCTIONS-CHECKERS FOR THE INPUTS---- */
/* --CHECKERS FOR DIRECT FLIGHTS-- */
bool checkTime(string time) { // check the validity of the time (must be xx:xx, where x = Natural number)
// enter ONLY if string is NOT empty
	if(!time.empty()){
		for (int i=0; i < time.length(); i++) {
			if (i==2){
				if (time.at(i) != ':') {
				return false;
				}

			}else if ( !(time.at(i) >= '0' && time.at(i) <= '9') ) {
				return false;
			}
		}
		return true;
	}else{
		return false;
	}

}
bool checkNumber(string s){ // checks if the input string consists ONLY of numbers

	// enter if string is NOT empty
	if(!s.empty()){
		for (int i = 0; i < s.length(); i++){
			if ( ((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z') || (s.at(i) == ' ')) ){
				return false;
			}
		}

		// check if string is a postive number
		if ( atoi(s.c_str()) > 0 ){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}
bool checkString(string s){ // checks if string consists only of letters
    if(!s.empty()){
		for (int i = 0; i < s.length(); i++){
			if ( !((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z')) ){
				return false;
			}
		}
		return true;
	}
	else{ //return false
		return false;
	}
}
/* --CHECKER FOR NON-DIRECT FLIGHTS-- */
bool checkTime2(Time tLeaving, Time tArriving){	// checks the validity of arrival and departure time
	if(tLeaving.hour > tArriving.hour){
		return true;
	}else if(tLeaving.hour == tArriving.hour){
		if(tLeaving.min > tArriving.min){
			return true;
		}
	}
	return false;
}
/*
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
																IMPLEMENTATION
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
/* ----GLOBAL VARS---- */
list<Flight> flist; // store the flights of the system
list<Person> plist; // store the passengers
list<Queue> qlist; // store the customers in the flights waiting queues

/* ----FUNCTION OF CLASS Queue---- */

Queue::Queue(int queueId){

	this -> queueNo = queueId;
    this -> rear = NULL;
    this -> front = NULL;
}
void Queue::enqueue(Person p){
    Node* temp = new Node;
    temp -> person = p;
    temp -> next = NULL;
    if(this -> front == NULL){
       this -> front = temp;
   }else{
        this -> rear -> next = temp;
    }
    this -> rear = temp;
}
void Queue::dequeue(){
    Node* temp = new Node;
    temp = this -> front;
	this -> front = this -> front -> next;
	delete temp;
}
void Queue::display(int num){
	for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i) {
		if(num == i -> queueNo){
			Node* p = new Node;
			p = i -> front;
			if(i -> front == NULL){
				cout<<"\nEmpty queue.\n";
			}else{
				cout << "\nPassengers waiting on queue:" << endl;
				cout << left << setw(15) << "Passport" << left << setw(15) << "Name" << left << setw(15) << "Surame" << endl;
				while(p!=NULL){
					cout << left << setw(15) << p -> person.getPassport() << left << setw(15) << p -> person.getName() << left << setw(15) << p -> person.getSurname() << endl;
					p = p -> next;
				}
			}
		}
	}
}
Person Queue::oldest(){
	return this -> front -> person;
}
bool Queue::isEmpty(){
 if(this -> front == NULL && this -> rear == NULL){
  return true;
 }
 return false;
}
/* ----FUNCTIONS OF CLASS Menu---- */

void Menu::displayMenu(){
	int selection;	// user's menu choice
	string temp; // temp to store user's input
	do{
			cout << "-----------------------------------------------";

			cout << "\n\t AIRLINE RESERVATION SYSTEM \n\n";
			cout << "Please pick an option from the menu below. \n";
			cout << "1. Add new flights \n";
			cout << "2. Display flight schedule \n";
			cout << "3. Display passenger personal info \n";
			cout << "4. Book reservation \n";
			cout << "5. Cancel reservation \n";
			cout << "6. Exit \n\n";

			cout << "-----------------------------------------------" << endl;

			cout << "Enter the number of a menu option: ";
			cin >> temp;
			// check validity of input
			while (!checkNumber(temp)) {
				cout << "Please enter a number!" << endl;
				cin.clear();
				cin.ignore(256,'\n');
				cin >> temp;
			}
			cout << endl;
			selection = atoi(temp.c_str());
			select(selection);
	}while(true);
}
void  Menu::select(int selection){
	Flight f; // FLight's object
	Person p; // class Person's object
	string temp; // temp to store input
	switch(selection){
		case 1:
			f.addFlight();
			break;
		case 2:
			if (!flist.empty()) {
				Flight::displaySchedule();
			}else {
				cout << "There are no scheduled flights!" << endl;
			}
			break;
		case 3:
			if (!plist.empty()){
				cout << "Please insert passport number: ";
				cin >> temp;
				while (!Person::displayPersonInfo( atoi(temp.c_str()) )) {
					cout << "Wrong passport number!" << endl;
					cin.clear();
					cin.ignore(256,'\n');
					cin >> temp;
					cout << endl;
				}
			}else{
				cout << "There are no registered clients at the moment!" << endl;
			}
			break;
		case 4:
			p.book();
			break;
		case 5:
			p.cancel();
			break;
		case 6:
			Menu::exit_prog();
			break;
		default:
			cout << "Invalid selection \n";
	}
}
void Menu::exit_prog(){
	cout << "Thank you for using our system! \n";
	exit(1); // exit
}

