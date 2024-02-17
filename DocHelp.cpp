#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


// Structure to represent patient data
struct Patient {
    int patient_id;
    string name;
    string phone;
    string email;
    string address;
};

// Function to save patient data to a file
void savePatientData(const Patient& patient) {
    ofstream file("patient_data.txt", ios::app); // Open file in append mode

    if (file.is_open()) {
        // Write patient data to the file
        file << patient.patient_id << ',' << patient.name << ',' << patient.phone << ',' << patient.email << ',' << patient.address << '\n';

        // Close the file
        file.close();

        cout << "Patient data saved successfully.\n";
    } else {
        cout << "Error: Unable to open file for writing.\n";
    }
}

// Function to display patient data from the file
void displayPatientData(int patientId) {
    ifstream file("patient_data.txt");

    if (file.is_open()) {
        string line;

        // Read and display data for the specified patient ID
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            getline(ss, token, ',');
            int currentPatientID;

            // Use stringstream for conversion
            stringstream(token) >> currentPatientID;

            if (currentPatientID == patientId) {
                cout << "Patient Data for ID " << patientId << ":\n";
                cout << line << '\n';
                break;
            }
        }

        // Close the file
        file.close();
    } else {
        cout << "No patient data found.\n";
    }
}

// Function to generate a unique patient ID
int generatePatientID() {
    ifstream file("patient_data.txt");
    int lastPatientID = 0;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            getline(ss, token, ',');
            
            // Use stringstream for conversion
            stringstream(token) >> lastPatientID;
        }

        // Close the file
        file.close();
    }

    return lastPatientID + 1;
}

// Function to enter prescription for a patient
void enterPrescription(int patientId) {
    ofstream outFile("prescriptions.txt", ios::app);

    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    cout << "Enter prescription for patient ID " << patientId << ":" << endl;
    string prescription;
    cin.ignore();  // Clear the input buffer
    getline(cin, prescription);

    // Save the prescription to the file
    outFile << patientId << ":" << prescription << endl;

    cout << "Prescription saved successfully." << endl;

    outFile.close();
}



// Function to save patient amounts to a file
void saveData(const map<int, double>& patientAmounts, const string& filename) {
    ofstream file(filename.c_str());  // Convert string to C-style string

    if (file.is_open()) {
        for (map<int, double>::const_iterator it = patientAmounts.begin(); it != patientAmounts.end(); ++it) {
            file << it->first << " " << it->second << "\n";
        }

        file.close();
        cout << "Data saved successfully.\n";
    } else {
        cerr << "Unable to open the file for writing.\n";
    }
}

// Function to load patient amounts from a file or create a new file
void loadData(map<int, double>& patientAmounts, const string& filename) {
    ifstream file(filename.c_str());  // Convert string to C-style string

    if (file.is_open()) {
        int id;
        double amount;

        while (file >> id >> amount) {
            patientAmounts[id] = amount;
        }

        file.close();
        cout << "Data loaded successfully.\n";
    } else {
        cerr << "File not found. Creating a new file.\n";
        // Save an empty map to create the file
        saveData(patientAmounts, filename);
    }
}


// Function to display patient ID and amount for a specific patient
void displaySpecificData(const map<int, double>& patientAmounts, int specificPatientId) {
    map<int, double>::const_iterator it = patientAmounts.find(specificPatientId);
    if (it != patientAmounts.end()) {
        cout << "Amount for Patient ID " << specificPatientId << ": " << it->second << "\n";
    } else {
        cout << "Patient ID " << specificPatientId << " not found.\n";
    }
}

// Function to display prescriptions for a given patient ID
void displayPrescriptions(int patientId) {
    ifstream inFile("prescriptions.txt");

    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    cout << "Prescriptions for patient ID " << patientId << ":" << endl;
    string line;

    while (getline(inFile, line)) {
        size_t pos = line.find(":");
        int id;
        istringstream(line.substr(0, pos)) >> id;

        if (id == patientId) {
            cout << line.substr(pos + 1) << endl;
        }
    }

    inFile.close();
}

// Function to calculate and update the average rating
void updateAverage(float& totalRating, int& numberOfRatings, float newRating) {
    totalRating += newRating;
    numberOfRatings++;
}

// Function to display the current average rating
void displayAverage(float totalRating, int numberOfRatings) {
    if (numberOfRatings > 0) {
        float average = totalRating / numberOfRatings;
        std::cout << "Average rating: " << average << std::endl;
    } else {
        std::cout << "No ratings entered yet." << std::endl;
    }
}

class dochelp
{
	public:
		int existingAppointment();			//done
		void addamount();					//done
		int bookAppointment();				//done
		void paidamount();					//done
};

int dochelp::bookAppointment() 
{
    system("cls");
    cout<<"\n ----- Book Your Appointment ---- \n";	
    cout<<"\n ----- Availbale slots ---- \n";	 
    ifstream read;
    read.open("appointment.dat");
    int hoursbook = 8;
    int arr[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    int recordFound =0; 
    if(read)
    {     
	string line;
	char key = 'A';
	int i = 9;
	while(getline(read, line)) {
		char temp = line[0];
		int index = (temp - 65);
		arr[index]=1;  
		recordFound = 1;
	}
	if(recordFound == 1)
	{
	cout<<"\n Appointment Summary by hours:";
	char key = 'A';
	int hours = 9;
	for(int i = 0; i<=12; i++)
	{
	if(i == 0){
	if(arr[i] == 0) 
	cout<<"\n "<<key<<"-> 0"<<hours<<" - Available";
	else
	cout<<"\n "<<key<<"-> 0"<<hours<<" - Booked";
	}
	else
	{								           	
	if(arr[i] == 0) 
	cout<<"\n "<<key<<"->"<<hours<<" - Available";
	else
	cout<<"\n "<<key<<"->"<<hours<<" - Booked";
	}
	hours++; key++;
	}       
	}	
	read.close();
    }
	if(recordFound == 0){
	cout<<"\n Appointment Available for following hours :";
	char key = 'A';
	for(int i = 9; i<=21; i++)
	{
		if(i==9)
		cout<<"\n "<<key<<" -> 0"<<i<<" - Available";
		else
		cout<<"\n "<<key<<" -> "<<i<<" - Available";
		key++;
	}
	}
   char choice;
   cout<<"\n\n Input your choice : ";
   cin>>choice;
   if( !(choice >= 'A' && choice <='Z'))
   {
	cout<"\n Error : Invalid Selection";
	cout<<"\n Please selction correct value from menu A- Z";
	cout<"\n Press any key to continue";
	getchar();getchar();
	system("cls");
	bookAppointment();
   }
   int index = (choice-65 );
   int isBooked = 1;
   if(arr[index] == 0) 
      isBooked = 0;
   if(isBooked ==1)
   {
   	cout<<"\n Error : Appointment is already booked for this Hour";
   	cout<<"\n Please select different time !!";
   	cout<<"\n Press any key to continue!!";
   	getchar();getchar();
   	system("cls");
   	bookAppointment();
   }
   string name;
   cout<<"\n Enter your first name:";
   cin>>name;  
   ofstream out;
   out.open("appointment.dat", ios::app);
   if(out){
	   out<<choice<<":"<<name.c_str()<<"\n";
	   out.close();
	   cout<<"\n Appointment booked for Hours : "<< (choice-65) + 9 <<" successfully !!";
    }
    else
    {
    	cout<<"\n Error while saving booking";
    }
    cout<<"\n Please any key to continue..";
	getchar(); getchar();
	return 0;		
}

int dochelp::existingAppointment()
{
    system("cls");
    cout<<"\n ----- Appointments Summary ---- \n";	
    //check if record already exist..
    ifstream read;
    read.open("appointment.dat");
    
    int hoursbook = 8;
    
    int arr[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
     int recordFound =0; 
     
    if(read)
    {     
	string line;
	char key = 'A';
	int i = 9;
	       
	   while(getline(read, line)) {
	   	   char temp = line[0];
	   	   int index = (temp - 65);
	   	   arr[index]=1;  
		   recordFound = 1;
	  }
        if(recordFound == 1)
        {
        cout<<"\n Appointment Summary by hours:";
        char key = 'A';
        int hours = 9;
        for(int i = 0; i<=12; i++)
        {
        	if(arr[i] == 0) 
        	cout<<"\n "<<key<<"->"<<hours<<" - Available";
        	else
        	cout<<"\n "<<key<<"->"<<hours<<" - Booked";
        	hours++; key++;
        }
            
	}
		
	read.close();
    }
    else
    {
    char key = 'A';
	for(int i = 9; i<=21; i++)
	{
	if(i==9)
	cout<<"\n "<<key<<" -> 0"<<i<<" - Available";
	else
	cout<<"\n "<<key<<" -> "<<i<<" - Available";
	key++;
	}
    }
    
    cout<<"\n Please any key to continue..";
    getchar(); getchar();
    return 0;	 
}

int main()
{
	start:
	int a,b,c,d, id, pass;
	dochelp ob;
	cout << " ----------------------------- Welcome to DocHelp-ABC HOSPITAL Pvt Ltd -----------------------------" << endl;
	cout << "\n 1. Doctor \n 2. Patient \n 3. Admin" << endl ;
	cin >> a;
	switch (a)
	{
		case 1 : 
			doctor : 
			cout << "Enter doctor id : " << endl;
			cin >> id;
			cout << "Enter password : " << endl;
			cin >> pass;
			if (id == pass)
			{
				cout << "\n 1. Check patient record \n 2. Add prescription \n  3. Check schedule  \n 4.Add patient" << endl;
				cin >> b;
				switch (b)
				{
					case 1:
						{
							 // Ask the user for a specific patient ID
    int specificPatientID;
    cout << "Enter a specific patient ID to display details: ";
    cin >> specificPatientID;

    // Display data for the specific patient ID
    displayPatientData(specificPatientID);

    return 0;
    break;
						}
					case 2:
						{int patientId;

    cout << "Enter patient ID: ";
    cin >> patientId;

    enterPrescription(patientId);
    break;
						}
					case 3 :
						ob.existingAppointment();
						break;
					
    case 4:
    	{
		 Patient patient;

    // Generate a unique patient ID
    patient.patient_id = generatePatientID();

    // Input patient data
    cout << "Enter patient name: ";
    cin>> patient.name;

    cout << "Enter phone number: ";
    cin>>patient.phone;

    cout << "Enter email address: ";
   cin>> patient.email;

    cout << "Enter address: ";
    cin>>patient.address;

    // Save patient data to file
    savePatientData(patient);
break;}
				
			}
			}else 
			{
				cout << "Invalid password" << endl;
				goto doctor;
			}
			break;
			
		case 2 :
			cout << "\n 1. Book Appointment \n 2. Check prescription \n 3. Add doctor review " << endl;
			cin >> c;
			switch (c)
			{
				
				case 2:
					{
						int patientId;

    cout << "Enter patient ID to display prescriptions: ";
    cin >> patientId;

    displayPrescriptions(patientId);

    return 0;
					}
				case 1:
					ob.bookAppointment();
					break;
				
	case 3:
					std::ifstream inputFile("ratings.txt");
    float totalRating = 0.0;
    int numberOfRatings = 0;

    // Read existing ratings from the file
    float rating;
    while (inputFile >> rating) {
        updateAverage(totalRating, numberOfRatings, rating);
    }

    inputFile.close();

    char choice;
    do {
        // Input new rating
        std::cout << "Enter a rating out of 5: ";
        std::cin >> rating;

        // Validate the rating
        if (rating < 0 || rating > 5) {
            std::cout << "Invalid rating. Please enter a rating between 0 and 5." << std::endl;
            continue;
        }

        // Update average and display it
        updateAverage(totalRating, numberOfRatings, rating);
        displayAverage(totalRating, numberOfRatings);

        // Save the new rating to the file
        std::ofstream outputFile("ratings.txt", std::ios::app);
        outputFile << rating << std::endl;
        outputFile.close();

        // Ask if the user wants to enter another rating
        std::cout << "Do you want to enter another rating? (y/n): ";
        std::cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
			}
			break;
			
		case 3 : 
			admin :
			cout << "Enter admin id : " << endl;
			cin >> id;
			cout << "Enter password : " << endl;
			cin >> pass;
			if (id == pass)
			{
				cout << "\n 1. Add Appointment \n 2. Check Patient Record  \n    \n 3.Add patient" << endl ;
				cin >> d;
				switch (d)
				{
					case 2:
						{
							 // Ask the user for a specific patient ID
    int specificPatientID;
    cout << "Enter a specific patient ID to display details: ";
    cin >> specificPatientID;

    // Display data for the specific patient ID
    displayPatientData(specificPatientID);

    return 0;
						}
					case 3:
						 {
						 Patient patient;

    // Generate a unique patient ID
    patient.patient_id = generatePatientID();

    // Input patient data
    cout << "Enter patient name: ";
    cin>>patient.name;

    cout << "Enter phone number: ";
    cin>>patient.phone;

    cout << "Enter email address: ";
   cin>> patient.email;

    cout << "Enter address: ";
    cin>>patient.address;

    // Save patient data to file
    savePatientData(patient);}

					case 1:
						ob.bookAppointment(); 
						break;
					
			
		default :
				cout << "INVALID ENTRY" << endl;
				break;
	}
	
	cout << "(c) Registered Trademark ABC hospitals pvt ltd" << endl;
	goto start;
	
}}}
