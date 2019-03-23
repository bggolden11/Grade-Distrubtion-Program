//Grade Distrubtion Program


#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>

#include "gradeutil.h"

using namespace std;

enum GradingType
{
  Letter,
  Satisfactory,
  Unknown
};
//
// API:
//

//
// ParseCourse:
//
// Parses a CSV (comma-separated values) line into a Course
// object, which is then returned.  The given line must have
// the following format:
//
//   Dept,Number,Section,Title,A,B,C,D,F,I,NR,S,U,W,Instructor
//
// Example:
//   BIOE,101,01,Intro to Bioengineering,22,8,2,1,0,1,0,0,0,5,Eddington
//
// Note the lack of spaces, except perhaps in the title.
// If the given line does not have this format, the behavior
// of the function is undefined (it may crash, it may throw
// an exception, it may return).
//
Course ParseCourse(string csvline)
{
  
  Course A;
  int i = 0;
  string dept;
  string number;
  string section;
  string title;
  string numA;
  string numB;
  string numC;
  string numD;
  string numF;
  string numI;
  string numNR;
  string numS;
  string numU;
  string numW;
  string intructor;
  stringstream ss(csvline);

  /*string  Dept;
  string  Title;
  int     Number;
  int     Section;
  string  Instructor;
  int     NumA, NumB, NumC, NumD, NumF, NumI, NumS, NumU, NumW, NumNR;*/

  getline(ss, dept, ',');
  getline(ss, number, ',');
  getline(ss, section, ',');
  getline(ss, title, ',');
  getline(ss, numA, ',');
  getline(ss, numB, ',');
  getline(ss, numC, ',');
  getline(ss, numD, ',');
  getline(ss, numF, ',');
  getline(ss, numI, ',');
  getline(ss, numNR, ',');
  getline(ss, numS, ',');
  getline(ss, numU, ',');
  getline(ss, numW, ',');
  getline(ss, intructor);

  A.Dept = dept;
  A.Title = title;

  A.Number = stoi(number);

  A.Section = stoi(section);

  A.Instructor = intructor;

  A.NumA = stoi(numA);

  A.NumB = stoi(numB);

  A.NumC = stoi(numC);

  A.NumD = stoi(numD);

  A.NumF = stoi(numF);

  A.NumI = stoi(numI);

  A.NumS = stoi(numS);

  A.NumU = stoi(numU);

  A.NumW = stoi(numW);

  A.NumNR = stoi(numNR);

  //cout << numA;
  return A;

  //
  // TODO:
  //

  return Course();
}

//
// GetDFWRate:
//
// Returns the DFW rate as a percentage for a given course,
// department, or college.  For a course whose grading type
// is defined as Course::Letter, the DFW rate is defined as
//
//   # of D grades + F grades + Withdrawals
//   -------------------------------------- * 100.0
//   # of A, B, C, D, F grades + Withdrawls
//
// The numerator is returned via the reference parameter DFW;
// the denominator is returned via the reference parameter N.
// If the course grading type is not Course::Letter, the DFW
// rate is 0.0, and parameters DFW and N are set to 0.
//
// When computed for a dept or college, all courses of type
// Course::Letter are considered in computing an overall DFW
// rate for the dept or college.  The reference parameters
// DFW and N are also computed across the dept or college.
//
double GetDFWRate(const Course &c, int &DFW, int &N)
{

   DFW = 0;
  N   = 0;

  //
  // how was course graded?  If not a letter, then cannot compute
  // DFW rate, so return 0.0:
  //
  Course::GradingType grading = c.getGradingType();

  if (grading != Course::Letter)
    return 0.0;

  //
  // we have letter grades (at least 1), so compute DFW rate:
  //
  DFW = c.NumD + c.NumF + c.NumW;
  N   = c.NumA + c.NumB + c.NumC + c.NumD + c.NumF + c.NumW;

  if (N == 0) // just in case, guard against divide by 0:
    return 0.0;

  return (static_cast<double>(DFW) / static_cast<double>(N)) * 100.0;
  /*DFW = 0;
  N = 0;
  double temp;
  double temp0;
  int tempDFW = c.NumD + c.NumF + c.NumW;

  temp0 = c.NumA + c.NumB + c.NumC + c.NumD + c.NumF;
  if (c.getGradingType()==Letter)
  {
    temp = temp + temp0 + c.NumW;
    DFW = DFW + tempDFW;
  }
  N = temp;
  return ((DFW / temp) * 100.0);

  //
  // TODO:
  //*/
}

double GetDFWRate(const Dept &dept, int &DFW, int &N)
{
  DFW = 0;
  N = 0;
  double temp;
  double temp0;
  for (Course S : dept.Courses)
  {
    int tempDFW = S.NumD + S.NumF + S.NumW;

    temp0 = S.NumA + S.NumB + S.NumC + S.NumD + S.NumF;
    if (S.getGradingType()==Letter)
    {
      temp = temp + temp0 + S.NumW;
      DFW = DFW + tempDFW;
    }
  }
  N = temp;

  //
  // TODO:
  //

  return ((DFW / temp) * 100.0);
}

double GetDFWRate(const College &college, int &DFW, int &N)
{
  DFW = 0;
  N = 0;

  //
  // TODO:
  //
  double temp;
  double temp0;
  for (Dept A : college.Depts)
  {
    for (Course S : A.Courses)
    {
      int tempDFW = S.NumD + S.NumF + S.NumW;

      temp0 = S.NumA + S.NumB + S.NumC + S.NumD + S.NumF;
      if (S.getGradingType()==Letter)
      {
        temp = temp + temp0 + S.NumW;
        DFW = DFW + tempDFW;
      }
    }
  }
  N = temp;
//  cout << "The DFW is  " << DFW << endl
  //     << "THe N is " << N;

  return ((DFW / temp) * 100.0);
}

//
// GetGradeDistribution
//
// Returns an object containing the grade distribution for a given
// course, dept or college.  For a course whose grading type is
// defined as Course::Letter, the grade distribution is defined by
// the following values:
//
//   N: the # of A, B, C, D, F grades
//   NumA, NumB, NumC, NumD, NumF: # of A, B, C, D, F grades
//   PercentA, PercentB, PercentC, PercentD, PercentF: % of A, B,
//     C, D, F grades.  Example: PercentA = NumA / N * 100.0
//
// If the course grading type is not Course::Letter, all values
// are 0.  When computed for a dept or college, all courses of
// type Course::Letter are considered in computing an overall
// grade distribution for the dept or college.
//
GradeStats GetGradeDistribution(const Course &c)
{

  GradeStats a;
  if (c.getGradingType() == Letter)
  {
    a.NumA = c.NumA;
    a.NumB = c.NumB;
    a.NumC = c.NumC;
    a.NumD = c.NumD;
    a.NumF = c.NumF;
    a.N = c.NumA + c.NumB + c.NumC + c.NumD + c.NumF;
    double N1 = c.NumA + c.NumB + c.NumC + c.NumD + c.NumF;
    a.PercentA = (c.NumA / N1) * 100.0;
    a.PercentB = (c.NumB / N1) * 100.0;
    a.PercentC = (c.NumC / N1) * 100.0;
    a.PercentD = (c.NumD / N1) * 100.0;
    a.PercentF = (c.NumF / N1) * 100.0;
  }
  else
  {
    a.NumA = 0;
    a.NumB = 0;
    a.NumC = 0;
    a.NumD = 0;
    a.NumF = 0;
    a.N = 0;
    //double N1 = 0;
    a.PercentA = 0;
    a.PercentB = 0;
    a.PercentC = 0;
    a.PercentD = 0;
    a.PercentF = 0;
    a.PercentA = 0;
  }
  if(a.N==0)
      {
        return GradeStats(0,0,0,0,0,0,0.0,0.0,0.0,0.0,0.0);
      }
  //
  // TODO:
  //

  return a;
}

GradeStats GetGradeDistribution(const Dept &dept)
{
  GradeStats a;
  a.NumA = 0;
    a.NumB = 0;
    a.NumC = 0;
    a.NumD = 0;
    a.NumF = 0;
    a.N = 0;
    //double N1 = 0;
    a.PercentA = 0;
    a.PercentB = 0;
    a.PercentC = 0;
    a.PercentD = 0;
    a.PercentF = 0;
    a.PercentA = 0;
    double N1 = 0;
    for(Course c : dept.Courses)
    {
        if (c.getGradingType() == Letter)
          {
            a.NumA = a.NumA+ c.NumA;
            a.NumB =  a.NumB+ c.NumB;
            a.NumC =  a.NumC+ c.NumC;
            a.NumD =  a.NumD+ c.NumD;
            a.NumF =  a.NumF+ c.NumF;
            a.N = a.N+c.NumA + c.NumB + c.NumC + c.NumD + c.NumF;
            N1 = N1+c.NumA + c.NumB + c.NumC + c.NumD + c.NumF;

          }

    }
    if(a.N==0)
      {
        return GradeStats(0,0,0,0,0,0,0.0,0.0,0.0,0.0,0.0);
      }
     a.PercentA = (a.NumA / N1) * 100.0;
            a.PercentB = (a.NumB / N1) * 100.0;
            a.PercentC = (a.NumC / N1) * 100.0;
            a.PercentD = (a.NumD / N1) * 100.0;
            a.PercentF = (a.NumF / N1) * 100.0;
  //
  // TODO:
  //

  return a;
}

GradeStats GetGradeDistribution(const College &college)
{

   GradeStats a;
  a.NumA = 0;
    a.NumB = 0;
    a.NumC = 0;
    a.NumD = 0;
    a.NumF = 0;
    a.N = 0;
    //double N1 = 0;
    a.PercentA = 0;
    a.PercentB = 0;
    a.PercentC = 0;
    a.PercentD = 0;
    a.PercentF = 0;
    a.PercentA = 0;
    double N1 = 0;
    for(Dept A : college.Depts)
    {
      for(Course c : A.Courses)
      {
          if (c.getGradingType() == Letter)
            {
              a.NumA = a.NumA+ c.NumA;
              a.NumB =  a.NumB+ c.NumB;
              a.NumC =  a.NumC+ c.NumC;
              a.NumD =  a.NumD+ c.NumD;
              a.NumF =  a.NumF+ c.NumF;
              a.N = a.N+c.NumA + c.NumB + c.NumC + c.NumD + c.NumF;
              N1 = N1+c.NumA + c.NumB + c.NumC + c.NumD + c.NumF;

            }

      }
    }
    if(a.N==0)
      {
        return GradeStats(0,0,0,0,0,0,0.0,0.0,0.0,0.0,0.0);
      }
     a.PercentA = (a.NumA / N1) * 100.0;
            a.PercentB = (a.NumB / N1) * 100.0;
            a.PercentC = (a.NumC / N1) * 100.0;
            a.PercentD = (a.NumD / N1) * 100.0;
            a.PercentF = (a.NumF / N1) * 100.0;
  //
  // TODO:
  //

  return a;
}

//
// FindCourses(dept, courseNumber)
//
// Searches the courses in the department for those that match
// the given course number.  If none are found, then the returned
// vector is empty.  If one or more courses are found, copies of
// the course objects are returned in a vector, and returned in
// ascending order by section number.
//
vector<Course> FindCourses(const Dept &dept, int courseNumber)
{
  vector<Course> courses;
  for(Course a : dept.Courses)
    {
        if(a.Number==courseNumber)
          {
            courses.push_back(a);
          }
    }
  sort(courses.begin(),courses.end(),
  [](Course s1, Course s2)
    {
        if(s1.Section<s2.Section)
          {
            return true;
          }
          else{
            return false;
          }
    }
  );

  //
  // TODO:
  //

  return courses;
}

//
// FindCourses(dept, instructorPrefix)
//
// Searches the courses in the department for those whose
// instructor name starts with the given instructor prefix.
// For example, the prefix "Re" would match instructors "Reed"
// and "Reynolds".
//
// If none are found, then the returned vector is empty.  If
// one or more courses are found, copies of the course objects
// are returned in a vector, with the courses appearing in
// ascending order by course number.  If two courses have the
// same course number, they are given in ascending order by
// section number.  Note that courses are NOT sorted by instructor
// name.
//
vector<Course> FindCourses(const Dept &dept, string instructorPrefix)
{
  vector<Course> courses;
   for(Course a : dept.Courses)
    {
        if(a.Instructor.compare(0,instructorPrefix.length(), instructorPrefix)==0)
          {
            courses.push_back(a);
          }
    }
  sort(courses.begin(),courses.end(),
  [](Course s1, Course s2)
    {
        if(s1.Number<s2.Number)
          {
            return true;
          }
          else if(s1.Number>s2.Number){
            return false;
          }
          else
          {
            if(s1.Section<s2.Section)
              {
                return true;
              }
              else{
            return false;
          }
          }

    }
  );

  //
  // TODO:
  //

  return courses;
}

//
// FindCourses(college, courseNumber)
//
// Searches for all courses in the college for those that match
// the given course number.  If none are found, then the returned
// vector is empty.  If one or more courses are found, copies of
// the course objects are returned in a vector, with the courses
// appearing in ascending order by department, then course number,
// and then section number.
//
vector<Course> FindCourses(const College &college, int courseNumber)
{
  vector<Course> courses;
  for(Dept d : college.Depts)
    {
      for(Course a : d.Courses )
        {
          if(a.Number == courseNumber)
            {
              courses.push_back(a);
            }
        }
    }
    sort(courses.begin(),courses.end(),
  [](Course s1, Course s2)
    {
        if(s1.Dept<s2.Dept)
          {
            return true;
          }
          else if(s1.Dept>s2.Dept){
            return false;
          }
          else
          {
            if(s1.Number<s2.Number)
              {
                return true;
              }
              else if (s1.Number>s2.Number)
                {
                     return false;
                }
              else{
                  if(s1.Section<s2.Section)
                    {
                      return true;
                    }
                    else{
                      return false;
                    }
              }
          }

    }
    );



  //
  // TODO:
  //

  return courses;
}

//
// FindCourses(college, instructorPrefix)
//
// Searches all the courses in the college for those whose
// instructor name starts with the given instructor prefix.
// For example, the prefix "Re" would match instructors "Reed"
// and "Reynolds".  If none are found, then the returned
// vector is empty.  If one or more courses are found, copies of
// the course objects are returned in a vector, with the courses
// appearing in ascending order by instructor, then course number,
// and then section number.
//
vector<Course> FindCourses(const College &college, string instructorPrefix)
{

  vector<Course> courses;
  for(Dept d : college.Depts)
    {
      for(Course a : d.Courses )
        {
          if(a.Instructor.compare(0,instructorPrefix.length(), instructorPrefix)==0)
            {
              courses.push_back(a);
            }
        }
    }
    sort(courses.begin(),courses.end(),
  [](Course s1, Course s2)
    {
        if(s1.Instructor<s2.Instructor)
          {
            return true;
          }
          else if(s1.Instructor>s2.Instructor){
            return false;
          }
          else
          {
            if(s1.Number<s2.Number)
              {
                return true;
              }
              else if (s1.Number>s2.Number)
                {
                     return false;
                }
              else{
                  if(s1.Section<s2.Section)
                    {
                      return true;
                    }
                    else{
                      return false;
                    }
              }
          }

    }
    );

  //
  // TODO:
  //

  return courses;
}
