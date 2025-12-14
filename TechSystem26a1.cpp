// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"


TechSystem::TechSystem()
{
    global_points=0;
}



TechSystem::~TechSystem()
{
    global_points=0;
    
    destroyCourseStudents(courses.m_root);

    courses.destroyTree(courses.m_root);
    courses.m_root = nullptr;
    courses.m_size = 0;

    students.destroyTree(students.m_root);
    students.m_root = nullptr;
    students.m_size = 0;
    
}

void destroyCourseStudents(AVLnode<int, std::shared_ptr<course>>* node) {
    if (!node) return;

    destroyCourseStudents(node->left);
    destroyCourseStudents(node->right);

    node->data->getStudentsTree().destroyTree(node->data->getStudentsTree().m_root);
    node->data->getStudentsTree().m_root = nullptr;
    node->data->getStudentsTree().m_size = 0;
}



StatusType TechSystem::addStudent(int studentId)
{
    if(studentId<=0){
        return StatusType::INVALID_INPUT;
    }
    if(!students.ifExist(studentId)){
        return StatusType::FAILURE;
    }
    try {
        std::shared_ptr<student> s = std::make_shared<student>(studentId, global_points);
        students.insert(studentId, s);
    }
    catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}



StatusType TechSystem::removeStudent(int studentId)
{
    if(studentId <= 0){
        return StatusType::INVALID_INPUT;
    }

    std::shared_ptr<student> s = students.getData(studentId);


    if(!s || s.getNumCourses() ){
        return StatusType::FAILURE;
    }
    try {
        students.erase(s);

    }
    catch(...){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;


}



StatusType TechSystem::addCourse(int courseId, int points)
{

    if (courseId <= 0 || points <= 0)
        return StatusType::INVALID_INPUT;

    if (courses.ifExist(courseId))
        return StatusType::FAILURE;

    try {
        std::shared_ptr<course> c = std::make_shared<course>(courseId, points);
        courses.insert(courseId, c);
    }
    catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}



StatusType TechSystem::removeCourse(int courseId)
{
    if (courseId <= 0)
        return StatusType::INVALID_INPUT;

    std::shared_ptr<course> c = courses.getData(courseId);

    if(!c || c->getStudentCount())
        return StatusType::FAILURE;
    try {
        courses.erase(c);
    }

    catch(...){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}



StatusType TechSystem::enrollStudent(int studentId, int courseId)
{
     if (studentId <= 0 || courseId <= 0)
        return StatusType::INVALID_INPUT;

    std::shared_ptr<student> s = students.getData(studentId);
    std::shared_ptr<course> c = courses.getData(courseId);

    if (!s || !c)
        return StatusType::FAILURE;

    auto& tree = c->getStudentsTree();

    // Already enrolled?
    if (tree.ifExist(studentId))
        return StatusType::FAILURE;

    try {
        tree.insert(studentId, s);
    }
    catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }

    s->addCourse();
    return StatusType::SUCCESS;
}



StatusType TechSystem::completeCourse(int studentId, int courseId)
{
    if (studentId <= 0 || courseId <= 0)
        return StatusType::INVALID_INPUT;

    std::shared_ptr<course> c = courses.getData(courseId);


    if(!c )
         return StatusType::FAILURE;

    auto& tree = c->getStudentsTree();
    std::shared_ptr<student> s = tree.getData(studentId);

    if(!s)
        return StatusType::FAILURE;

    s->addPoints( c->getPoints());

    try {
        tree.erase(s);
    }
    catch(...){
        return StatusType::ALLOCATION_ERROR;

    }
    s->removeCourse();
    return StatusType::SUCCESS;

}



StatusType TechSystem::awardAcademicPoints(int points)
{
    if (points <= 0)
        return StatusType::INVALID_INPUT;
    global_points += points;
    return StatusType::SUCCESS;

}



output_t<int> TechSystem::getStudentPoints(int studentId)
{
    if(studebtId <= 0)
        return output_t(StatusType::INVALID_INPUT);

    std::shared_ptr<student> s = students.getData(studentId);
    if(!s)
        return output_t(StatusType::FAILURE);

    return output_t(global_points - s->getBasePoints() + s->getPersonalPoints());


}
