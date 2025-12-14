#ifndef STUDENT_H
#define STUDENT_H

class student {
    int id;
    int private_points;
    int num_courses;
    int base_points;
    

 public:

    
    student(int id, int global_offset)
        : id(id),
          private_points(0),
          num_courses(0),
          base_points(global_offset)
    {}    
    ~student()=default;
    int getId() const { return id; }
    int getPersonalPoints() const { return private_points; }
    int getNumCourses() const { return num_courses; }
    int getBasePoints() const { return base_points; }
    void addCourse() { num_courses++; }
    void removeCourse() { num_courses--; }
    void addPoints(int p) {private_points += p; }


};
#endif // STUDENT_H
