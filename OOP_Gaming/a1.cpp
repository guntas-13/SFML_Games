#include <iostream>
#include <vector>
#include <fstream>

class Student
{
    std::string m_first = "First";
    std::string m_last  = "Last";
    int         m_id    = 0;
    float       m_avg   = 0;

public:
    Student() {}
    
    Student(std::string first, std::string last, int id, float avg)
        : m_first (first)
        , m_last  (last)
        , m_id    (id)
        , m_avg   (avg)
    {    
    }

    float getAvg() const
    {
        return m_avg;
    }

    int getID() const
    {
        return m_id;
    }

    std::string getFirst() const
    {
        return m_first;
    }

    std::string getLast() const
    {
        return m_last;
    }

    void print() const
    {
        std::cout << m_first << " " << m_last << " " << m_id << " " << m_avg << "\n";
    }
};


class Course
{
    std::string m_name = "Course";
    std::vector<Student> m_students;

public:
    Course() {}

    // call by reference on the parameters as we don't want 
    // to copy the entire string object to our local variable

    Course(const std::string& name)   
        : m_name(name)
    {
    }

    void loadFromFile(const std::string& filename)
    {
        std::ifstream fin(filename);
        std::string first, last;
        int id;
        float avg;

        while (fin >> first)
        {
            fin >> last >> id >> avg;
            addStudent(Student(first, last, id, avg));
        }
    }

    void addStudent(const Student& s)
    {
        m_students.push_back(s);
    }

    // since we are returning the reference to out Student object
    // we don't want it to be changed hence first "const" for std::vector<Student>&
    // the second "const" is for the function -> meaning that
    // the getStudent() function will not change the object
    const std::vector<Student>& getStudent() const
    {
        return m_students;
    }

    void print()
    {
        for (const auto& s : m_students)
        {
            s.print();
        }
    }
};

int main(int argc, char * argv[])
{
    // Student s1;
    // Student s2("Guntas", "Saran", 22110089, 9.61);
    // const Student s3("Rakesh", "Sharma", 22110300, 9.0);
    /*
    const objects need const functions -> hence declare all functions in class as const too.
    */

    
//    cs101.addStudent(s1);
//    cs101.addStudent(s2);
//    cs101.addStudent(s3);
//    cs101.addStudent(Student("Nihar", "Shah", 22110237, 8.76));

    Course cs101("CS 101");
    cs101.loadFromFile("students.txt");
    cs101.print();
    return 0;
}