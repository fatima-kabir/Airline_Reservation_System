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
Flight flights[MAX_FLIGHTS];
int n = 0;
Node* head = NULL;
int nextBookingID = 101;
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
    else if(hasBookings(id)){
        cout << "Cancel its bookings before deleting this flight." << endl;
    }
    else{
        for(int i = position; i < n - 1; i++)
            flights[i] = flights[i + 1];
			n--;
			cout << "Flight deleted successfully." << endl;
		}
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
    else if(flights[position].availableSeats == 0){
        cout << "No seats available." << endl;
    }
    else{
        cout << "Enter Passenger Name: ";
        cin >> name;

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
        int position = searchFlightIndex(temp->flightID);
        if(prev == NULL)
            head = temp->next;
        else
            prev->next = temp->next;

        if(position != -1)
            flights[position].availableSeats++;

        delete temp;
        cout << "Booking cancelled successfully." << endl;
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
            case 0: cout << "Program ended." << endl; break;
            default: cout << "Invalid choice." << endl;
        }
    } 
	while(choice != 0);
	return 0;
}
