#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Enum for vehicle type
enum VehicleType { GT3 = 1, Formula, Rally };

// Struct to model a motorsport session
struct Session
{
    string driverName;
    string trackName;
    VehicleType vehicle;
    double lapTimes[3];
};

//////// Function prototypes ////////
void showBanner();
string getNonEmptyString(const string& prompt);
int getIntInRange(const string& prompt, int min, int max);
VehicleType chooseVehicle();
void generateLapTimes(Session& s);
double averageLap(const Session& s);
void printSession(const Session& s);
void saveReport(const Session sessions[], int count);
/////////////////////////////////////

int main()
{
    srand(static_cast<unsigned>(time(0)));

    const int MAX_SESSIONS = 5;
    Session sessions[MAX_SESSIONS];
    int sessionCount = 0;

    showBanner();

    int choice;
    do
    {
        cout << "\nMenu\n";
        cout << "1. Add Driving Session\n";
        cout << "2. View All Sessions\n";
        cout << "3. Save Report\n";
        cout << "4. Quit\n";

        choice = getIntInRange("Enter choice (1-4): ", 1, 4);

        switch (choice)
        {
        case 1:
            if (sessionCount < MAX_SESSIONS)
            {
                Session s;
                s.driverName = getNonEmptyString("Enter driver name: ");
                s.trackName = getNonEmptyString("Enter track name: ");
                s.vehicle = chooseVehicle();
                generateLapTimes(s);

                sessions[sessionCount] = s;
                sessionCount++;

                cout << "\nSession added!\n";
                printSession(s);

                // Compound if/else example
                double avg = averageLap(s);
                if (avg < 75 && s.vehicle == Formula)
                    cout << "Excellent pace for a Formula car!\n";
                else if (avg >= 75 && avg <= 100)
                    cout << "Solid and consistent driving.\n";
                else
                    cout << "Room for improvement. Keep practicing!\n";
            }
            else
            {
                cout << "Session limit reached.\n";
            }
            break;

        case 2:
            if (sessionCount == 0)
            {
                cout << "No sessions recorded.\n";
            }
            else
            {
                for (int i = 0; i < sessionCount; i++)
                {
                    printSession(sessions[i]);
                }
            }
            break;

        case 3:
            saveReport(sessions, sessionCount);
            cout << "Report saved to report.txt\n";
            break;

        case 4:
            cout << "Goodbye!\n";
            break;
        }

    } while (choice != 4);

    return 0;
}

// Function for intro banner
void showBanner()
{
    cout << "========================================\n";
    cout << "   Welcome to the Motorsports Simulator \n";
    cout << "========================================\n";
}

// This Function is used to collect the driver's name and track name
string getNonEmptyString(const string& prompt)
{
    string input;
    do
    {
        cout << prompt;
        getline(cin, input);
    } while (input.empty());

    return input;
}

// Function is used to get one of the starting menu options
int getIntInRange(const string& prompt, int min, int max)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value && value >= min && value <= max)
        {
            cin.ignore(1000, '\n');
            return value;
        }
        else
        {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

// This Function allows you to choose one of the allowed vehicles as a number than converts it to the enum type
VehicleType chooseVehicle()
{
    cout << "\nChoose Vehicle:\n";
    cout << "1. GT3 Car\n";
    cout << "2. Formula Car\n";
    cout << "3. Rally Car\n";

    int choice = getIntInRange("Select (1-3): ", 1, 3);
    return static_cast<VehicleType>(choice);
}

// This Function will generate random lap times based on the selected vehicle seleced and based on time
void generateLapTimes(Session& s)
{
    double base = 0.0;

    switch (s.vehicle)
    {
    case GT3: base = 95.0; break;
    case Formula: base = 70.0; break;
    case Rally: base = 120.0; break;
    }

    for (int i = 0; i < 3; i++)
    {
        double variation = (rand() % 1000) / 100.0; // 0.00–9.99
        s.lapTimes[i] = base + variation;
    }
}

// This Function averages the 3 lap times
double averageLap(const Session& s)
{
    double total = 0;
    for (int i = 0; i < 3; i++)
        total += s.lapTimes[i];
    return total / 3.0;
}

// This Function prints out all of your selections and your lap times with average
void printSession(const Session& s)
{
    cout << "\n----------------------------------------\n";
    cout << left << setw(15) << "Driver:" << s.driverName << endl;
    cout << left << setw(15) << "Track:" << s.trackName << endl;

    string vehicleName;
    if (s.vehicle == GT3) vehicleName = "GT3";
    else if (s.vehicle == Formula) vehicleName = "Formula";
    else vehicleName = "Rally";

    cout << left << setw(15) << "Vehicle:" << vehicleName << endl;

    cout << fixed << setprecision(2);
    for (int i = 0; i < 3; i++)
    {
        cout << "Lap " << i + 1 << ": " << s.lapTimes[i] << " sec\n";
    }

    cout << "Average: " << averageLap(s) << " sec\n";
}

// This Function saves the previous session to report.txt, it shows 5 sessions
void saveReport(const Session sessions[], int count)
{
    ofstream out("report.txt");

    out << left << setw(15) << "Driver"
        << setw(15) << "Track"
        << setw(12) << "Vehicle"
        << setw(10) << "Avg Lap\n";
    out << "-----------------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        string vehicleName;
        if (sessions[i].vehicle == GT3) vehicleName = "GT3";
        else if (sessions[i].vehicle == Formula) vehicleName = "Formula";
        else vehicleName = "Rally";

        out << left << setw(15) << sessions[i].driverName
            << setw(15) << sessions[i].trackName
            << setw(12) << vehicleName
            << fixed << setprecision(2)
            << setw(10) << averageLap(sessions[i]) << endl;
    }

    out.close();
}

