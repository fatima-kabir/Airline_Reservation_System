#include <iostream>
using namespace std;
const int MAX_FLIGHTS = 50;
struct Flight{
    int flightID;
    string flightName;
    string source;
    string destination;
    int totalSeats;
    int availableSeats;
    double ticketPrice;
};
struct Node{
    int bookingID;
    int flightID;
    string passengerName;
    Node* next;
};
struct WaitingNode{
    int waitingID;
    int flightID;
    string passengerName;
    WaitingNode* next;
};
struct StackNode{
    int bookingID;
    int flightID;
    string passengerName;
    bool passengerPromoted;
    int promotedBookingID;
    int promotedWaitingID;
    string promotedPassengerName;
    StackNode* next;
};
Flight flights[MAX_FLIGHTS];
int n = 0;
Node* head = NULL;
int nextBookingID = 101;
WaitingNode* front = NULL;
WaitingNode* rear = NULL;
int nextWaitingID = 1;
StackNode* top = NULL;
int searchFlightIndex(int id){
    for(int i = 0; i < n; i++){
        if(flights[i].flightID == id)
            return i;
    }
    return -1;
}
bool hasBookings(int id){
    Node* temp = head;
    while(temp != NULL){
        if(temp->flightID == id)
            return true;
        temp = temp->next;
    }
    return false;
}
bool hasWaitingPassengers(int id){
    WaitingNode* temp = front;
    while(temp != NULL){
        if(temp->flightID == id)
            return true;
        temp = temp->next;
    }
    return false;
}
void addFlight(){
    if(n == MAX_FLIGHTS){
        cout << "Flight storage is full." << endl;
        return;
    }
	int id;
    cout << "Enter Flight ID: ";
    cin >> id;
	if(searchFlightIndex(id) != -1){
        cout << "This Flight ID already exists." << endl;
        return;
    }
	cout << "Enter Flight Name: ";
    cin >> flights[n].flightName;
    cout << "Enter Source: ";
    cin >> flights[n].source;
    cout << "Enter Destination: ";
    cin >> flights[n].destination;
    cout << "Enter Total Seats: ";
    cin >> flights[n].totalSeats;
	cout << "Enter Ticket Price: ";
    cin >> flights[n].ticketPrice;
	flights[n].flightID = id;
    flights[n].availableSeats = flights[n].totalSeats;
    n++;
    cout << "Flight added successfully." << endl;
}
void displayFlights(){
    if(n == 0){
        cout << "No flights available." << endl;
        return;
    }
	for(int i = 0; i < n; i++){
        cout << "\nFlight ID: " << flights[i].flightID << endl;
        cout << "Flight Name: " << flights[i].flightName << endl;
        cout << "Source: " << flights[i].source << endl;
        cout << "Destination: " << flights[i].destination << endl;
        cout << "Total Seats: " << flights[i].totalSeats << endl;
        cout << "Available Seats: " << flights[i].availableSeats << endl;
        cout << "Ticket Price: " << flights[i].ticketPrice << endl;
    }
}
void searchFlight(){
    int id;
    cout << "Enter Flight ID: ";
    cin >> id;
	int position = searchFlightIndex(id);
    if(position == -1){
        cout << "Flight not found." << endl;
    }
    else{
        cout << "\nFlight found!" << endl;
        cout << "Flight ID: " << flights[position].flightID << endl;
        cout << "Flight Name: " << flights[position].flightName << endl;
        cout << "Source: " << flights[position].source << endl;
        cout << "Destination: " << flights[position].destination << endl;
        cout << "Available Seats: " << flights[position].availableSeats << endl;
        cout << "Ticket Price: " << flights[position].ticketPrice << endl;
    }
}
void deleteFlight(){
    int id;
    cout << "Enter Flight ID to delete: ";
    cin >> id;
	int position = searchFlightIndex(id);
    if(position == -1){
        cout << "Flight not found." << endl;
    }
    else if(hasBookings(id) || hasWaitingPassengers(id)){
        cout << "Cancel its bookings and waiting-list entries before deleting this flight." << endl;
    }
    else{
        for(int i = position; i < n - 1; i++)
            flights[i] = flights[i + 1];
			n--;
			cout << "Flight deleted successfully." << endl;
		}
}
void addToWaitingList(int id, string name){
    WaitingNode* newNode = new WaitingNode;
    newNode->waitingID = nextWaitingID;
    newNode->flightID = id;
    newNode->passengerName = name;
    newNode->next = NULL;
    if(front == NULL){
        front = newNode;
        rear = newNode;
    }
    else{
        rear->next = newNode;
        rear = newNode;
    }
    cout << "You have been added to the waiting list." << endl;
    cout << "Waiting ID: " << nextWaitingID << endl;
    nextWaitingID++;
}
void bookTicket(){
    int id;
    string name;
    cout << "Enter Flight ID: ";
    cin >> id;
	int position = searchFlightIndex(id);
    if(position == -1){
        cout << "Flight not found." << endl;
    }
    else{
        cout << "Enter Passenger Name: ";
        cin >> name;
        if(flights[position].availableSeats == 0){
            char choice;
            cout << "No seats available. Join waiting list? (y/n): ";
            cin >> choice;
            if(choice == 'y' || choice == 'Y')
                addToWaitingList(id, name);
            else
                cout << "Booking not made." << endl;
        }
        else{
            Node* newNode = new Node;
            newNode->bookingID = nextBookingID;
            newNode->flightID = id;
            newNode->passengerName = name;
            newNode->next = head;
            head = newNode;
            flights[position].availableSeats--;
            cout << "Ticket booked successfully." << endl;
            cout << "Booking ID: " << nextBookingID << endl;
            nextBookingID++;
        }
    }
}
void displayBookings(){
    if(head == NULL){
        cout << "No bookings available." << endl;
        return;
    }
	Node* temp = head;
    while(temp != NULL){
        cout << "\nBooking ID: " << temp->bookingID << endl;
        cout << "Passenger Name: " << temp->passengerName << endl;
        cout << "Flight ID: " << temp->flightID << endl;
        temp = temp->next;
    }
}
void pushCancelledBooking(int bookingID, int flightID, string name){
    StackNode* newNode = new StackNode;
    newNode->bookingID = bookingID;
    newNode->flightID = flightID;
    newNode->passengerName = name;
    newNode->passengerPromoted = false;
    newNode->promotedBookingID = 0;
    newNode->promotedWaitingID = 0;
    newNode->promotedPassengerName = "";
    newNode->next = top;
    top = newNode;
}
void giveSeatToWaitingPassenger(int flightID){
    WaitingNode* temp = front;
    WaitingNode* prev = NULL;
    while(temp != NULL && temp->flightID != flightID){
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL){
        int position = searchFlightIndex(flightID);
        if(position != -1)
            flights[position].availableSeats++;
        return;
    }
    Node* newBooking = new Node;
    newBooking->bookingID = nextBookingID;
    newBooking->flightID = temp->flightID;
    newBooking->passengerName = temp->passengerName;
    newBooking->next = head;
    head = newBooking;
	if(top != NULL){
        top->passengerPromoted = true;
        top->promotedBookingID = nextBookingID;
        top->promotedWaitingID = temp->waitingID;
        top->promotedPassengerName = temp->passengerName;
    }
    if(prev == NULL)
        front = temp->next;
    else
        prev->next = temp->next;
    if(temp == rear)
        rear = prev;
    cout << "Waiting passenger " << temp->passengerName << " has been given the seat." << endl;
    cout << "New Booking ID: " << nextBookingID << endl;
    nextBookingID++;
    delete temp;
}
void cancelBooking(){
    int id;
    cout << "Enter Booking ID to cancel: ";
    cin >> id;
    Node* temp = head;
    Node* prev = NULL;
    while(temp != NULL && temp->bookingID != id){
        prev = temp;
        temp = temp->next;
    }
	if(temp == NULL){
        cout << "Booking not found." << endl;
    }
    else{
        int flightID = temp->flightID;
		int bookingID = temp->bookingID;
        string name = temp->passengerName;
        if(prev == NULL)
            head = temp->next;
        else
            prev->next = temp->next;
        delete temp;
		pushCancelledBooking(bookingID, flightID, name);
        cout << "Booking cancelled successfully." << endl;
		giveSeatToWaitingPassenger(flightID);
    }
}
void displayCancellationHistory(){
    if(top == NULL){
        cout << "No cancellation history available." << endl;
        return;
    }
    StackNode* temp = top;
    cout << "\n===== CANCELLATION HISTORY (LATEST FIRST) =====" << endl;
    while(temp != NULL){
        cout << "Booking ID: " << temp->bookingID << endl;
        cout << "Passenger Name: " << temp->passengerName << endl;
        cout << "Flight ID: " << temp->flightID << endl;
        temp = temp->next;
    }
}
void restoreWaitingPassenger(int waitingID, int flightID, string name){
    WaitingNode* newNode = new WaitingNode;
    newNode->waitingID = waitingID;
    newNode->flightID = flightID;
    newNode->passengerName = name;
    newNode->next = NULL;
    if(front == NULL || waitingID < front->waitingID){
        newNode->next = front;
        front = newNode;
        if(rear == NULL)
            rear = newNode;
    }
    else{
        WaitingNode* temp = front;
        while(temp->next != NULL && temp->next->waitingID < waitingID)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
        if(newNode->next == NULL)
            rear = newNode;
    }
}
void undoLastCancellation(){
    if(top == NULL){
        cout << "No cancellation to undo." << endl;
        return;
    }
    StackNode* temp = top;
    int position = searchFlightIndex(temp->flightID);
    if(position == -1){
        cout << "The original flight no longer exists. Undo cannot be completed." << endl;
        return;
    }
    if(temp->passengerPromoted){
        Node* booking = head;
        Node* prevBooking = NULL;
        while(booking != NULL && booking->bookingID != temp->promotedBookingID){
            prevBooking = booking;
            booking = booking->next;
        }
        if(booking == NULL){
            cout << "Cannot undo because the promoted booking was changed." << endl;
            return;
        }
        if(prevBooking == NULL)
            head = booking->next;
        else
            prevBooking->next = booking->next;
        delete booking;
        restoreWaitingPassenger(temp->promotedWaitingID, temp->flightID, temp->promotedPassengerName);
    }
    else{
        flights[position].availableSeats--;
    }
    Node* newBooking = new Node;
    newBooking->bookingID = temp->bookingID;
    newBooking->flightID = temp->flightID;
    newBooking->passengerName = temp->passengerName;
    newBooking->next = head;
    head = newBooking;
    top = temp->next;
    delete temp;
    cout << "Last cancellation has been undone." << endl;
}
void displayWaitingList(){
    if(front == NULL){
        cout << "Waiting list is empty." << endl;
        return;
    }
    WaitingNode* temp = front;
    cout << "\n===== WAITING LIST (FIFO) =====" << endl;
    while(temp != NULL){
        cout << "Waiting ID: " << temp->waitingID << endl;
        cout << "Passenger Name: " << temp->passengerName << endl;
        cout << "Flight ID: " << temp->flightID << endl;
        temp = temp->next;
    }
}
void cancelWaitingPassenger(){
    int id;
    cout << "Enter Waiting ID to remove: ";
    cin >> id;
    WaitingNode* temp = front;
    WaitingNode* prev = NULL;
    while(temp != NULL && temp->waitingID != id){
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL){
        cout << "Waiting ID not found." << endl;
    }
    else{
        if(prev == NULL)
            front = temp->next;
        else
            prev->next = temp->next;
        if(temp == rear)
            rear = prev;
        delete temp;
        cout << "Waiting-list entry removed." << endl;
    }
}
int main(){
    int choice;
    do{
        cout << "\n===== AIRLINE RESERVATION SYSTEM =====" << endl;
        cout << "1. Add Flight" << endl;
        cout << "2. Display Flights" << endl;
        cout << "3. Search Flight" << endl;
        cout << "4. Delete Flight" << endl;
        cout << "5. Book Ticket" << endl;
        cout << "6. Display Bookings" << endl;
        cout << "7. Cancel Booking" << endl;
		cout << "8. Display Waiting List" << endl;
        cout << "9. Cancel Waiting-List Entry" << endl;
		cout << "10. Display Cancellation History" << endl;
        cout << "11. Undo Last Cancellation" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1: addFlight(); break;
            case 2: displayFlights(); break;
            case 3: searchFlight(); break;
            case 4: deleteFlight(); break;
            case 5: bookTicket(); break;
            case 6: displayBookings(); break;
            case 7: cancelBooking(); break;
			case 8: displayWaitingList(); break;
            case 9: cancelWaitingPassenger(); break;
			case 10: displayCancellationHistory(); break;
            case 11: undoLastCancellation(); break;
            case 0: cout << "Program ended." << endl; break;
            default: cout << "Invalid choice." << endl;
        }
    } 
	while(choice != 0);
	return 0;
}
