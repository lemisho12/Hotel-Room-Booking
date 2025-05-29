#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>
#include <algorithm>
#include <regex>
#include <chrono>
#include <ctime>

using namespace std;

const int MAX_NAME_LEN = 30;
const int MAX_ID_LEN = 15;
const int ROOM_COUNT = 10;
const int PRICE_PER_DAY = 500;
const int MAX_INITIAL_STAY_DAYS = 30; 
const int EXTENSION_DAYS = 30;      

struct Customer {
    string id;
    string name;
    string phone;
    int roomNumber;
    string checkIn;
    string checkOut;
    long long stayDays;
    long long totalBill;
    Customer* next;
};

Customer* head = nullptr;
bool rooms[ROOM_COUNT + 1] = { false };

tm parseDate(const string& dateString) {
    tm t = {};
    stringstream ss(dateString);
    char slash;
    ss >> t.tm_mday >> slash >> t.tm_mon >> slash >> t.tm_year;
    t.tm_mon -= 1;
    t.tm_year -= 1900;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    t.tm_isdst = -1;
    return t;
}

string formatDate(const tm& dateTm) {
    char buffer[11]; 
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", &dateTm);
    return string(buffer);
}


tm getCurrentDate() {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm* localTime = localtime(&currentTime);

    tm current = *localTime;
    current.tm_hour = 0;
    current.tm_min = 0;
    current.tm_sec = 0;
    current.tm_isdst = -1;
    return current;
}

bool isDatePast(const tm& input, const tm& current) {
    time_t input_time = mktime(const_cast<tm*>(&input));
    time_t current_time = mktime(const_cast<tm*>(&current));
    return difftime(input_time, current_time) < 0;
}


long long calculateStayDays(const string& checkInStr, const string& checkOutStr) {
    tm checkInTm = parseDate(checkInStr);
    tm checkOutTm = parseDate(checkOutStr);

    time_t checkInTime = mktime(&checkInTm);
    time_t checkOutTime = mktime(&checkOutTm);

    double seconds = difftime(checkOutTime, checkInTime);
    return static_cast<long long>(seconds / (60 * 60 * 24));
}

bool isValidDate(const string& date) {
    if (!regex_match(date, regex("^\\d{2}/\\d{2}/\\d{4}$"))) {
        return false;
    }

    return true;
}

string inputID() {
    string id;
    regex idPattern("^[a-zA-Z0-9]{1,15}$");
    while (true) {
        cout << "Enter Customer ID (max 15 alphanumeric chars): ";
        getline(cin, id);
        if (regex_match(id, idPattern)) return id;
        cout << "Invalid ID! Only alphanumeric characters allowed, max 15 chars.\n";
    }
}

string inputName() {
    string name;
    regex namePattern("^[a-zA-Z ]{1,30}$");
    while (true) {
        cout << "Enter Name (max 30 chars, letters and spaces allowed): ";
        getline(cin, name);
        if (regex_match(name, namePattern)) return name;
        cout << "Invalid Name! Use letters and spaces only, max 30 chars.\n";
    }
}

string inputPhone() {
    string phone;
    regex phonePattern("^\\d{10,12}$");
    while (true) {
        cout << "Enter Phone Number (10 to 12 digits): ";
        getline(cin, phone);
        if (regex_match(phone, phonePattern)) return phone;
        cout << "Invalid Phone Number! Must be 10 to 12 digits.\n";
    }
}


string inputDate(const string& msg, const string& referenceDate = "", bool isCheckOut = false, const string& checkInDate = "") {
    string date;
    tm currentDateTm = getCurrentDate();
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", &currentDateTm);
    string currentDateStr(buffer);

    while (true) {
        cout << msg;
        if (referenceDate.empty()) {
            cout << " (Current date: " << currentDateStr << "): ";
        } else {
            cout << " (Must be after " << referenceDate << "): ";
        }

        getline(cin, date);
        if (!isValidDate(date)) {
            cout << "Invalid date format! Use DD/MM/YYYY.\n";
            continue;
        }

        tm inputTm = parseDate(date);


if (referenceDate.empty()) {
            if (isDatePast(inputTm, currentDateTm)) {
                cout << "Date cannot be in the past. Please enter a date on or after " << currentDateStr << ".\n";
            } else {
                return date;
            }
        } else {
            tm referenceTm = parseDate(referenceDate);
            if (isDatePast(inputTm, referenceTm)) { 
                cout << "Check-out date cannot be on or before Check-in date. Please enter a date after " << referenceDate << ".\n";
            } else {
                if (isCheckOut) {
                    long long calculatedDays = calculateStayDays(checkInDate, date);
                    if (calculatedDays > MAX_INITIAL_STAY_DAYS) {
                        cout << "Initial stay cannot exceed " << MAX_INITIAL_STAY_DAYS << " days. Please choose an earlier check-out date.\n";
                        continue;
                    }
                }
                return date;
            }
        }
    }
}

int inputRoom() {
    int room;
    while (true) {
        cout << "Enter Room Number (1-10): ";
        cin >> room;
        if (!cin.fail() && room >= 1 && room <= ROOM_COUNT && !rooms[room]) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return room;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid or already booked room. Try again.\n";
    }
}


void saveCustomersToFile() {
   
    
    
}

void loadCustomersFromFile() {
   
    
       
    
        
    
}

void displayAvailableRooms() {
 
    
    
    
}


void bookRoom() {
  
    

    
}

void printCustomerDetails(Customer* customer) {
   
    
}


void updateBooking() {
   
    
            
    
}

void deleteBooking() {
    
    
    
}

void searchCustomerByID() {
    
    
}

void searchCustomerByName() {
   
    
}

void sortCustomersByID() {
     if (  !head->next) {
        cout << "Not enough customers to sort.\n";
        return;
    }

    for (Customer* i = head; i != nullptr; i = i->next) {
        for (Customer* j = i->next; j != nullptr; j = j->next) {
            if (i->id > j->id) {

                swap(i->id, j->id);
                swap(i->name, j->name);
                swap(i->phone, j->phone);
                swap(i->roomNumber, j->roomNumber);
                swap(i->checkIn, j->checkIn);
                swap(i->checkOut, j->checkOut);
                swap(i->stayDays, j->stayDays);
                swap(i->totalBill, j->totalBill);
            }
        }
    }
    cout << "Customers sorted by ID.\n";
    saveCustomersToFile();
    
}

void sortCustomersByName() {
      if (  !head->next) {
        cout << "Not enough customers to sort.\n";
        return;
    }

    for (Customer* i = head; i != nullptr; i = i->next) {
        for (Customer* j = i->next; j != nullptr; j = j->next) {
            if (i->name > j->name) {

                swap(i->id, j->id);
                swap(i->name, j->name);
                swap(i->phone, j->phone);
                swap(i->roomNumber, j->roomNumber);
                swap(i->checkIn, j->checkIn);
                swap(i->checkOut, j->checkOut);
                swap(i->stayDays, j->stayDays);
                swap(i->totalBill, j->totalBill);
            }
        }
    }
    cout << "Customers sorted by Name.\n";
    saveCustomersToFile();
    
}

void displayBookedRooms() {


        if (!head) {
        cout << "No bookings found.\n";
        return;
    }

    char sortChoice;
    cout << "Do you want to sort the displayed customers? (y/n): ";
    cin >> sortChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (tolower(sortChoice) == 'y') {
        char sortCriteria;
        cout << "Sort by (N)ame or (I)D?: ";
        cin >> sortCriteria;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (tolower(sortCriteria) == 'n') {
            sortCustomersByName();
        } else if (tolower(sortCriteria) == 'i') {
            sortCustomersByID();
        } else {
            cout << "Invalid sort criteria. Displaying unsorted.\n";
        }
    }

    char searchChoice;
    cout << "Do you want to search for a specific customer? (y/n): ";
    cin >> searchChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
if (tolower(searchChoice) == 'y') {
        char searchCriteria;
        cout << "Search by (N)ame or (I)D?: ";
        cin >> searchCriteria;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (tolower(searchCriteria) == 'n') {
            searchCustomerByName();
        } else if (tolower(searchCriteria) == 'i') {
            searchCustomerByID();
        } else {
            cout << "Invalid search criteria. Displaying all booked customers.\n";
            Customer* temp = head;
            cout << left << setw(16) << "ID" << setw(32) << "Name" << setw(14)
                 << "Phone" << setw(8) << "Room" << setw(14) << "Check-In"
                 << setw(14) << "Check-Out" << setw(8) << "Days" << "Bill\n";

            while (temp) {
                printCustomerDetails(temp);
                temp = temp->next;
            }
        }
    } else {
        Customer* temp = head;
        cout << left << setw(16) << "ID" << setw(32) << "Name" << setw(14)
             << "Phone" << setw(8) << "Room" << setw(14) << "Check-In"
             << setw(14) << "Check-Out" << setw(8) << "Days" << "Bill\n";

        while (temp) {
            printCustomerDetails(temp);
            temp = temp->next;
        }
    }
            
}

int main() {
    loadCustomersFromFile();

    while (true) {
        cout << "\nHotel Management Menu:\n";
        cout << "1. Display Available Rooms\n";
        cout << "2. Book Room\n";
        cout << "3. Display Booked Rooms (with Sort & Search)\n";
        cout << "4. Update Check-out Date\n";
        cout << "5. Delete Booking (Archive)\n";
        cout << "0. Exit\n"; 
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: displayAvailableRooms(); break;
            case 2: bookRoom(); break;
            case 3: displayBookedRooms(); break; 
            case 4: updateBooking(); break;
            case 5: deleteBooking(); break;
            case 0:
                cout << "Exiting...\n";

                while (head) {
                    Customer* temp = head;
                    head = head->next;
                    delete temp;
                }
                return 0;
            default:
                cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}