#include "student.h"
#include "AVLtree.h"
#include <memory>
class course{
    
    int course_id;
    int course_points;
    AVLtree<int,std::shared_ptr<student>> students;
    public:
    course(int course_id,int course_points );
    ~course()=default;
    int getId() const { return course_id; }
    int getPoints() const { return course_points; }
    int getStudentCount() const { return students.m_size; }
    AVLtree<int, std::shared_ptr<student>>& getStudentsTree() {
        return students;
    }
};