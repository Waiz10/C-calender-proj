// cs103 project 
// waiz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<sstream>
//#include <bits/stdc++.h>

using namespace std;


void create()
{
    // file pointer
    fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open("result.csv", ios::out | ios::app);

    cout << "Enter the details of 7 days"
        << " time wise" << endl;

    int i, month, date;
    string name, morning_8am, morning_11am, e_2pm, e_5pm, n_9pm;

    // Read the input
    for (i = 0; i < 7; i++) {


        cin >> date
            >> morning_8am
            >> morning_11am
            >> e_2pm
            >> e_5pm
            >> n_9pm;

        // Insert the data to file


        fout << date << ","
            << morning_8am << ","
            << morning_11am << ","
            << e_2pm << ","
            << e_5pm << ","
            << n_9pm << endl;
    }
}
void read_record()
{
    // File pointer
    fstream fin;

    // Open an existing file
    fin.open("result.csv", ios::in);

    // Get the date
    // of which the data is required
    int dte, x, count = 0;
    cout << "Enter the date " << endl;

    cin >> dte;

    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word;

    while (!fin.eof()) {

        row.clear();

        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);

        // used for breaking words
        stringstream s(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ',')) {
            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }

        // convert string to integer for comparision
        x = stoi(row[0]);
        // Compare the date
        if (x == dte) {

            // Print the found data
            count = 1;
            cout << "date : " << row[0] << endl;
            cout << "8 am in the morning : " << row[1] << endl;
            cout << "11 am in the morning : " << row[2] << endl;
            cout << "2 pm in the afternoon : " << row[3] << endl;
            cout << "5 pm in the afternoon : " << row[4] << endl;
            cout << "9 pm in the night :" << row[5] << endl;
            cout << endl;
            break;
        }
    }
    if (count == 0)
        cout << "Record not found!\n";
}
void update_record()
{

    // File pointer
    fstream fin, fout;

    // Open an existing record
    fin.open("result.csv", ios::in);

    // Create a new file to store updated data
    fout.open("resultnew.csv", ios::out);

    int dte, daate, y, found = 0, i;
    char sub;
    int index;
    string line, word, new_data;
    vector<string> row;

    // Get the date from the user
    cout << "enter the date" << endl;
    cin >> dte;

    // Get the data to be updated
    cout << "Enter the time "
        << "to be updated( morning_8am=a , morning_11am=b , e_2pm=c, e_5pm=d , n_9pm=e): ";
    cin >> sub;

    // Determine the index of the subject
    // where Maths has index 2,
    // Physics has index 3, and so on
    if (sub == 'a' || sub == 'A')
        index = 1;
    else if (sub == 'b' || sub == 'B')
        index = 2;
    else if (sub == 'c' || sub == 'C')
        index = 3;
    else if (sub == 'd' || sub == 'D')
        index = 4;
    else if (sub == 'e' || sub == 'E')
        index = 5;
    else {
        cout << "Wrong choice. Enter again\n";
        update_record();
    }

    // Get the new marks
    cout << "Enter new shecedule ";
    cin >> new_data;

    // Traverse the file
    while (!fin.eof()) {

        row.clear();

        getline(fin, line);
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        daate = stoi(row[0]);
        int row_size = row.size();

        if (daate == dte) {
            found = 1;
            // stringstream convert;

             // sending a number as a stream into output string
         //    convert << new_data;

             // the str() converts number into string
           //  row[index] = convert.str();

            if (!fin.eof()) {
                for (i = 0; i < row_size - 1; i++) {

                    // write the updated data
                    // into a new file 'resultnew.csv'
                    // using fout
                    fout << row[i] << ",";
                }

                fout << row[row_size - 1] << endl;
            }
        }
        else {
            if (!fin.eof()) {
                for (i = 0; i < row_size - 1; i++) {

                    // writing other existing records
                    // into the new file using fout.
                    fout << row[i] << ",";
                }

                // the last column data ends with a '\n'
                fout << row[row_size - 1] << endl;
            }
        }
        if (fin.eof())
            break;
    }
    if (found == 0)
        cout << "Record not found!" << endl;

    fin.close();
    fout.close();

    // removing the existing file
    remove("result.csv");
    // renaming the updated file with the existing file name
    rename("resultnew.csv", "result.csv");
}
void delete_record()
{

    // Open FIle pointers
    fstream fin, fout;

    // Open the existing file
    fin.open("result.csv", ios::in);

    // Create a new file to store the non-deleted data
    fout.open("resultnew.csv", ios::out);

    int dte, daate, y, count = 0, i;
    char sub;
    int index;
    string line, word, new_data;
    vector<string> row;

    // Get the roll number
    // to decide the data to be deleted
    cout << "Enter the date: ";
    cin >> dte;
    cout << endl;

    // Check if this record exists
    // If exists, leave it and
    // add all other data to the new file
    while (!fin.eof()) {

        row.clear();
        getline(fin, line);
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        int row_size = row.size();
        daate = stoi(row[0]);

        // writing all records,
        // except the record to be deleted,
        // into the new file 'resultnew.csv'
        // using fout pointer
        if (dte != daate) {
            if (!fin.eof()) {
                for (i = 0; i < row_size - 1; i++) {
                    fout << row[i] << ",";
                }
                fout << row[row_size - 1] << endl;
            }
        }
        else {
            count = 1;
        }
        if (fin.eof())
            break;
    }
    if (count == 1)
        cout << "Record deleted!" << endl;
    else
        cout << "Record not found!" << endl;

    // Close the pointers
    fin.close();
    fout.close();

    // removing the existing file
    remove("result.csv");

    // renaming the new file with the existing file name
    rename("resultnew.csv", "result.csv");
}
int main()
{
  //  create();


    int number;
    cout << "enter a number (1 to read record, 2 to update a record, 3 delete record) : " << endl;
    cin >> number;
    if (number == 1) {
        read_record();
    }
    else if (number == 2) {
        update_record();
    }
    else if (number == 3) {
        delete_record();
    }
    else {
        cout << "wrong output";
    }
  


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
