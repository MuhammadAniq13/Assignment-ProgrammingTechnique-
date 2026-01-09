#include <iostream> // input/output
#include <iomanip> // used for ouput formatting exp: setprecision(2) --> to display gpa
#include <string> // work with text (store names or student id) exp: getline (cin,name);
#include <limits>
#include <sstream> // Added for string conversion

using namespace std;

const int MAX_STUDENTS = 100;
const int NUM_SUBJECTS = 4;
const int CREDIT_PER_SUBJ = 3;
const int TOTAL_CREDITS = NUM_SUBJECTS * CREDIT_PER_SUBJ;

string SUBJECT_NAMES[NUM_SUBJECTS] = {    // string because its a word
   "Programming Technique",             // subject_name is name of array 
   "Computer Org & Arch",               // num_subject is size of array its hold 4 because of const int
   "Multimedia System",
   "Linear & Discrete Math"
};

string studentIDs[MAX_STUDENTS]; // declare an array and size which is =< 100      store student id
string studentNames[MAX_STUDENTS]; // same as line 21                              store student name
double studentGPAs[MAX_STUDENTS];  // gpa with 2 decimal places                    store gpa
string studentGrades[MAX_STUDENTS][NUM_SUBJECTS]; // 2d array                      store grade
int studentCount = 0; // start with 0 student

// --- Improved Helper: Strict Validation ---
int getValidMarks(string subjectName) {    // getValidMarks is declared function  subjectname for what subject nak put marks
    string input;     // input is where you store the marks 
    int marks;

    while (true) {
        cout << "  Marks for " << subjectName << " (0-100): ";  // the instruction
        cin >> input;

        // Check if every character in the string is a digit
        bool isNumeric = true;           // isNumeric means "does the input contain only digits?"
        for (char const& c : input) {
            if (!isdigit(c)) {           // ! = if is not digit so false
                isNumeric = false;
                break;                   // break stops checking after the first non-digit is found.
            }
        }

        if (isNumeric) {                    // if only digits are entered just go proceed 
            // Convert string to integer
            stringstream ss(input);         // C++ tool to read data from a string like a stream
            ss >> marks;

            if (marks >= 0 && marks <= 100) {    // so it means = 0 till 100 only can be entered
                return marks; // Success
            }
        }

        // If we reach here, input was "57h", "abc", or "-5"
        cout << "  >> [Invalid] '" << input << "' is not a valid mark. Use numbers 0-100 only." << endl;   //for validation
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string getLetterGrade(int marks, double& point) {       // classify grade
    if (marks >= 80) { point = 4.00; return "A"; }
    if (marks >= 75) { point = 3.67; return "A-"; }
    if (marks >= 70) { point = 3.33; return "B+"; }
    if (marks >= 65) { point = 3.00; return "B"; }
    if (marks >= 60) { point = 2.67; return "B-"; }
    if (marks >= 55) { point = 2.33; return "C+"; }
    if (marks >= 50) { point = 2.00; return "C"; }
    if (marks >= 45) { point = 1.67; return "C-"; }
    if (marks >= 40) { point = 1.33; return "D+"; }
    if (marks >= 35) { point = 1.00; return "D"; }
    point = 0.00; return "F";
}

string getClassification(double cgpa) {               // classify class
    if (cgpa >= 3.75) return "First Class";
    if (cgpa >= 3.00) return "Second Class Upper";
    if (cgpa >= 2.50) return "Second Class Lower";
    if (cgpa >= 2.00) return "Third Class";
    return "Fail";
}

void addStudent() {                                     // if over 100
    if (studentCount >= MAX_STUDENTS) {
        cout << "Database full!" << endl;
        return;
    }

    cout << "\n--- Adding New Student ---" << endl;
    cout << "Enter Student ID: ";
    getline(cin, studentIDs[studentCount]);                    //get student name and id
    cout << "Enter Full Name: ";
    getline(cin, studentNames[studentCount]);

    double totalPoints = 0.0;

    for (int i = 0; i < NUM_SUBJECTS; i++) {
        int marks = getValidMarks(SUBJECT_NAMES[i]);               //get valid marks 
        double pt;
        studentGrades[studentCount][i] = getLetterGrade(marks, pt);           //calculate gpa 
        totalPoints += (pt * CREDIT_PER_SUBJ);
    }

    studentGPAs[studentCount] = totalPoints / TOTAL_CREDITS;
    studentCount++;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // store 
    cout << "Record saved successfully!" << endl;
}

void displayAll() {
    if (studentCount == 0) {
        cout << "\nNo records found." << endl;          // if no studentCount
        return;
    }

    cout << "\n" << left << setw(15) << "ID" << setw(30) << "NAME";
    cout << "S1  S2  S3  S4  " << setw(8) << "GPA" << "CLASS" << endl;
    cout << string(95, '-') << endl;

    for (int i = 0; i < studentCount; i++) {
        cout << left << setw(15) << studentIDs[i] << setw(30) << studentNames[i];             // arrange display
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            cout << left << setw(4) << studentGrades[i][j];
        }
        cout << fixed << setprecision(2) << setw(8) << studentGPAs[i]
            << getClassification(studentGPAs[i]) << endl;
    }
}

void searchByID() {
    string query;
    cout << "Enter Student ID: ";
    getline(cin, query);

    for (int i = 0; i < studentCount; i++) {
        if (studentIDs[i] == query) {
            cout << "\n--- Academic Transcript ---" << endl;
            cout << "Name: " << studentNames[i] << " (" << studentIDs[i] << ")" << endl;        // arrange transcript
            cout << "-----------------------------------" << endl;
            for (int j = 0; j < NUM_SUBJECTS; j++) {
                cout << left << setw(40) << SUBJECT_NAMES[j] << ": " << studentGrades[i][j] << endl;
            }
            cout << "-----------------------------------" << endl;
            cout << "Final GPA: " << fixed << setprecision(2) << studentGPAs[i] << endl;
            cout << "Result    : " << getClassification(studentGPAs[i]) << endl;
            return;
        }
    }
    cout << "Record not found." << endl;         // if student id not found
}

int main() {
    int choice = 0;
    while (choice != 4) {
        cout << "\n==== UNIVERSITY GPA SYSTEM ====" << endl;
        cout << "1. Add Student\n2. View All (Grades Summary)\n3. Search Student (Transcript)\n4. Exit" << endl;
        cout << "Choice: ";

        if (!(cin >> choice)) {
            cout << ">> [Error] Enter a valid menu number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) addStudent();
        else if (choice == 2) displayAll();                   // menu
        else if (choice == 3) searchByID();
    }
    return 0;
}
