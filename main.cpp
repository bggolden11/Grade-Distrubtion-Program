#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <functional>

#include "gradeutil.h"
using namespace std;
College sortDepartment(College A)
{
  cout << i;
    sort(A.Depts.begin(), A.Depts.end(),
         [](Dept a, Dept b) {
             if (a.Name > b.Name)
             {
                 return false;
             }
             else
             {
                 return true;
             }
         });
    return A;
}

//Function to sort first by DFW then by deptartment then number then by section
vector<Course> sortThisDFW(vector<Course> bye)
{
  cout << i;
    sort(bye.begin(), bye.end(),
         [](Course s1, Course s2) {
             int DFW1, N;
             if (GetDFWRate(s1, DFW1, N) < GetDFWRate(s2, DFW1, N))
             {
                 return false;
             }
             else if (GetDFWRate(s2, DFW1, N) < GetDFWRate(s1, DFW1, N))
             {
                 return true;
             }

             else
             {
                 if (s1.Dept < s2.Dept)
                 {
                     return true;
                 }
                 else if (s1.Dept > s2.Dept)
                 {
                     return false;
                 }
                 else
                 {
                     if (s1.Number < s2.Number)
                     {
                         return true;
                     }
                     else if (s1.Number > s2.Number)
                     {
                         return false;
                     }
                     else
                     {
                         if (s1.Section < s2.Section)
                         {
                             return true;
                         }
                         else
                         {
                             return false;
                         }
                     }
                 }
             }
         });
    return bye;
}
//Function to sort first by percent then by deptartment then number then by section
vector<Course> sortThisPercent(vector<Course> bye)
{

    sort(bye.begin(), bye.end(),
         [=](Course s1, Course s2) {
             GradeStats A;
                GradeStats B;
             A = GetGradeDistribution(s1);
             B =GetGradeDistribution(s2);

             if (A.PercentA <B.PercentA)
             {
                 return false;
             }
             else if (A.PercentA >B.PercentA)
             {
                 return true;
             }
            else{
                 if (s1.Dept < s2.Dept)
                 {
                     return true;
                 }
                 else if (s1.Dept >s2.Dept)
                 {
                     return false;
                 }
                 else
                 {
                     if (s1.Number < s2.Number)
                     {
                         return true;
                     }
                     else if (s1.Number > s2.Number)
                     {
                         return false;
                     }
                     else
                     {
                         if (s1.Section < s2.Section)
                         {
                             return true;
                         }
                         else
                         {
                             return false;
                         }
                     }
                 }
         }
         }
         );
    return bye;
}

//function to return a vector full with the required courses that fill the DFW requiremnt (Deparmtent as paramter)
vector<Course> findDFW(Dept A, double DFW)
{
    vector<Course> hi;
    for (Course B : A.Courses)
        {

            int DFW1, N;
            //cout <<"PLAS WORK!!!";
            double DFW2 = GetDFWRate(B, DFW1, N);
            if (DFW2 > DFW)
            {
                hi.push_back(B);
                //cout <<"PLAS WORK!!!";
            }
        }
    return sortThisDFW(hi);


}


//------------------------------------------------------------
//Function to return a vector that is filled with courses that fulfill the DFw requirement
vector<Course> findDFW(College A, double DFW)
{
    //DFW = 40;
    vector<Course> hi;
    for (Dept C : A.Depts)
    {
        for (Course B : C.Courses)
        {
            int DFW1, N;
            //cout <<"PLAS WORK!!!";
            double DFW2 = GetDFWRate(B, DFW1, N);
            if (DFW2 > DFW)
            {
                hi.push_back(B);
                //cout <<"PLAS WORK!!!";
            }
        }
    }
    //return hi;
    return sortThisDFW(hi);
}
//-----------------------------------------------------------
//Fucntion to print out sumary fo each course
void summary(College col)
{
    cout << "dept name, or all? ";
    string input;
    cin >> input;
    //cout << endl;
    if (input == "all")
    {
        College colNew = sortDepartment(col);
        for (Dept i : colNew.Depts)
        {
            i.summary();
            GradeStats grades = GetGradeDistribution(i);
            cout << " grade distribution (A-F): " << grades.PercentA << "%, " << grades.PercentB << "%, " << grades.PercentC << "%, " << grades.PercentD << "%, " << grades.PercentF << "%" << endl;
            int DFW, N;
            cout << " DFW rate: " << GetDFWRate(i, DFW, N) << "%" << endl;
        }
    }
    else
    {
        //find if function used to find departments that fulfill name requirement
        auto iter = find_if(col.Depts.begin(), col.Depts.end(),
                            [=](Dept A) {
                                if (A.Name == input)
                                {
                                    return true;
                                }
                                else
                                {
                                    return false;
                                }
                            });
        if (iter == col.Depts.end())
        {
            cout
                 << "**dept not found" << endl; //No departments found
        }
        else
        {
            //cout << endl;
            iter->summary(); //Print summary
            GradeStats grades = GetGradeDistribution(*iter);
            cout << " grade distribution (A-F): " << grades.PercentA << "%, " << grades.PercentB << "%, " << grades.PercentC << "%, " << grades.PercentD << "%, " << grades.PercentF << "%" << endl;
            int DFW, N;
            cout << " DFW rate: " << GetDFWRate(*iter, DFW, N) << "%" << endl;
        }
    }
}
//---------------------------------------------------------------------------------
//Print summary of courses reduces amount of code needed to be written
void summary(Course i)
{
    cout << i.Dept << " " << i.Number << " (section " << i.Section << ")"
         << ": " << i.Instructor << endl;
    cout << " # students: " << i.getNumStudents() << endl;
    cout << " course type: ";
    if (i.getGradingType() == Course::Letter) //checks letter
    {
        cout << "letter";
    }
    else if (i.getGradingType() == Course::Unknown)
    {
        cout << "unknown";
    }
    else
    {
        cout << "satisfactory";
    }
    cout << endl;
    GradeStats grades = GetGradeDistribution(i);
    cout << " grade distribution (A-F): " << grades.PercentA << "%, " << grades.PercentB << "%, " << grades.PercentC << "%, " << grades.PercentD << "%, " << grades.PercentF << "%" << endl;
    int DFW, N;
    cout << " DFW rate: " << GetDFWRate(i, DFW, N) << "%" << endl;
}
//-----------------------------------------------------------------------
//Function that returns a vector full of courses that fulfill the letter requirent threshold college as paramete
vector<Course> findALetter(College col, double thresHold)
    {
        GradeStats a;
        vector<Course> hi;
        for(Dept i : col.Depts)
            {
                for(Course j : i.Courses)
                    {
                        a = GetGradeDistribution(j);
                        if(a.PercentA > thresHold)
                            {
                                hi.push_back(j);
                            }
                    }
            }
            return sortThisPercent(hi);  //returns the sortated vector

    }

//--------------------------------------------------------
//-----------------------------------------------------------------------
//Function that returns a vector full of courses that fulfill the letter requirent threshold department as paramete
vector<Course> findALetter(Dept A, double thresHold)
    {
        GradeStats a;
        vector<Course> hi;
        for(Course j : A.Courses)
                    {
                        a = GetGradeDistribution(j);
                        if(a.PercentA > thresHold)
                            {
                                hi.push_back(j);
                            }
                    }
            return sortThisPercent(hi);
    }
//--------------------------------------------------------
//Function call to find letterA percentages for a given threshold
void lettA(College col)
    {
        cout << "dept name, or all? ";
        string input;
        cin >> input;
        //cout << endl;
        vector<Course> hi;
        double thresHold;
        if(input == "all")
            {
                cout << "letter A threshold? ";
                cin >> thresHold;
                //cout << endl;
                hi = findALetter(col, thresHold);

            }
        else
        {
            auto iter = find_if(col.Depts.begin(), col.Depts.end(), //fnnd if function used to find a certain department by name
                            [=](Dept A) {
                                if (A.Name == input)
                                {
                                    return true;
                                }
                                else
                                {
                                    return false;
                                }
                            }

        );
         cout << "letter A threshold? ";
         cin >> thresHold;
        if (iter == col.Depts.end())
        {
            cout << "**dept not found" << endl; //No departments found
            return;
        }
        else
        {

                //cout << endl;
                hi = findALetter(*iter, thresHold);
        }
        }
        if(hi.empty())
            {
                cout << "**none found" << endl; //vector is empty nothing found within that threshold
                return;
            }
        for(Course i : hi)
        {
            summary(i); //print sumary of everything in the vector
        }


    }
//----------------------------------------------
//prints out all unknown letter type courses
void unknown(College col)
{
    cout << "dept name, or all? ";
    string input;
    cin >> input;
    //cout << endl;
    if (input == "all")
    {
        vector<Course> hi = col.findUnknown(); //Function call to get vector full of unknown courses
        for (Course i : hi)
        {
            summary(i); //Print summary of each
        }
    }
    else
    {
        auto iter = find_if(col.Depts.begin(), col.Depts.end(), //Find if cll to find all departments that fulfill name requirements
                            [=](Dept A) {
                                if (A.Name == input)
                                {
                                    return true;
                                }
                                else
                                {
                                    return false;
                                }
                            }

        );
        if (iter == col.Depts.end())
        {
            //cout << endl
               cout  << "**none found" << endl; //No departments found
               return;
        }
        else
        {
            vector<Course> hi = iter->findUnknown();
            if(hi.size() == 0)
                {
                   cout  << "**none found" << endl; //nothing found
                    return;
                }
            for (Course i : hi)
            {
                summary(i); //print summary of each course within vector
            }
            /* code */
        }
    }
    return;
}
//----------------------------
//function to find courses that fullfill a dfw within a threshold
void dfw(College col)
{
    cout << "dept name, or all? ";
    string input;
    cin >> input;
    //cout << endl;
    double DFW;
    vector<Course> hi;
    if (input == "all")
    {
        cout << "dfw threshold? ";
        cin >> DFW;
        //cout << endl;
        hi = findDFW(col, DFW);

    }
    else
    {
        cout << "dfw threshold? ";
        cin >> DFW;
       // cout << endl;
     auto iter = find_if(col.Depts.begin(), col.Depts.end(), //Find if statem-ent used to find a department with a given name
                            [=](Dept A) {
                                if (A.Name == input)
                                {
                                    return true;
                                }
                                else
                                {
                                    return false;
                                }
                            }

        );
        if (iter == col.Depts.end())
        {
            //cout << endl
              cout << "**dept not found" << endl; //Department not found
              return;
        }
        else
        {
            hi = findDFW(*iter,DFW);
        }
    }
    if (hi.empty())
        {
            cout <<"**none found" << endl; //Empty vector nothing fullfilling requirement
            return;
        }
    else{
     for (Course i : hi)
        {
            summary(i); //print summary
        }
    }
}
//Function used to sarch for deptarment, course or instructor
void search(College col)
{
    cout << "dept name, or all? ";
    string instructorPrefix;
    int courseNum;
    string store;
    cin >> store;

    //cout << "Course"
    if (store == "all")
    {
        //cout << endl
        cout << "course # or instructor prefix? ";
        cin >> instructorPrefix;
        stringstream ss(instructorPrefix);
        ss >> courseNum;
        //if statment to check if string or integer
        if ((ss.fail()))
        {
            vector<Course> hi = FindCourses(col, instructorPrefix);
            if(hi.size()==0)
                {
                    cout << "**none found" << endl;
                    return;
                }
            for (Course i : hi)
            {
                summary(i);
            }
        }
        else
        {
            vector<Course> hi = FindCourses(col, courseNum); //calls helper function
            if(hi.size()==0)
                {
                    cout << "**none found" << endl;
                    return;
                }
            for (Course i : hi)
            {
                summary(i);
            }
        }
    }
    else
    {
        cout << "course # or instructor prefix? ";
        cin >> instructorPrefix;
        auto iter = find_if(col.Depts.begin(), col.Depts.end(),
                            [=](Dept A) {
                                if (A.Name == store)
                                {
                                    return true;
                                }
                                else
                                {
                                    return false;
                                }
                            }

        );
        if (iter == col.Depts.end())
        {
            cout << "**dept not found" << endl;
        }
        else
        {
            //cout << endl

            stringstream ss(instructorPrefix);
            ss >> courseNum;
            if ((ss.fail()))
            {
                vector<Course> hi = FindCourses(*iter, instructorPrefix);
                if(hi.size()==0)
                {
                    cout << "**none found" << endl;
                    return;
                }
                for (Course i : hi)
                {
                    summary(i);
                }
            }
            else
            {
                vector<Course> hi = FindCourses(*iter, courseNum);
                if(hi.size()==0)
                {
                    cout << "**none found" << endl;
                    return;
                }
                for (Course i : hi)
                {
                    summary(i);
                }
            }
        }
        return;
    }
}


//----------------------------------------
//Start of main
int main(int argc, char *argv[])
{

    cout << std::fixed;
    cout << std::setprecision(2);
    string filename;
    cin >> filename;
    ifstream infile(filename);
    string line;
    if (!infile.good())
    {
        cout << "**Error: cannot open input file!" << endl; //Cannot open file error
        return 0;
    }
    string name;
    getline(infile, line);
    //cout << name << endl;
    cout << "**  College of ";
    stringstream ss(line);
    getline(ss, name, ',');
    cout << name;
    //cout << name;
    getline(ss, name, ',');
    cout << ", " << name;
    string year;
    getline(ss, year);
    cout << " " << year << " **";
    //cout << " " << name;
    //cout << "  **" << endl
     cout << endl;
    //cout << "HELLO";
    getline(infile, line);
    getline(infile, line);
    College A;
    //Begin organizing into data structure
    while (!infile.eof())
    {
        Course B = ParseCourse(line);
        auto iter = find_if(A.Depts.begin(), A.Depts.end(), //Checks if department is already been used
                            [=](Dept C) {
                                if (C.Name == B.Dept)
                                {
                                    return true;
                                }
                                else
                                {
                                    return false;
                                }
                            });
        if (iter == A.Depts.end())
        {
            Dept E;
            E.Name = B.Dept;
            E.Courses.push_back(B); //Pushes if has been used
            A.Depts.push_back(E);
        }
        else
        {
            iter->Courses.push_back(B);
        }
        getline(infile, line);
    }
    infile.close();
    int numClasses = 0;
    int numStudents = 0;
    //Used to calculate numCourses and students
    for (Dept i : A.Depts)
    {
        numClasses += i.Courses.size();
        for (Course j : i.Courses)
        {
            numStudents += j.getNumStudents();
        }
    }
    //summary statemetn
    cout << "# of courses taught: " << numClasses << endl;
    cout << "# of students taught: " << numStudents << endl;
    GradeStats grades = GetGradeDistribution(A);
    cout << "grade distribution (A-F): " << grades.PercentA << "%, " << grades.PercentB << "%, " << grades.PercentC << "%, " << grades.PercentD << "%, " << grades.PercentF << "%" << endl;
    int DFW, N;
    cout << "DFW rate: " << GetDFWRate(A, DFW, N) << "%" << endl
         << endl;
    cout << "Enter a command> ";
    string cmd;
    cin >> cmd;
   // cout << endl;

   //Main while loop to check which function to call based on user inputfgfgddfbhello
    while (cmd != "#")
    {

        if (cmd != "summary" && cmd != "search" && cmd != "unknown" && cmd != "dfw" && cmd != "letterA")
        {
            cout << "**unknown command" << endl;
        }
        if (cmd == "summary")
        {
            summary(A);
            //cout << endl;
        }
        if (cmd == "search")
        {
            search(A);
        }
        if (cmd == "unknown")
        {
            unknown(A);
        }
        if (cmd == "dfw")
        {
            dfw(A);
        }
        if(cmd == "letterA")
            {
                lettA(A);
            }
        cout <<"Enter a command> ";

        cin >> cmd;
    }

    return 0;
}
