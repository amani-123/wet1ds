// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"


TechSystem::TechSystem()
{
    global_points=0;
}



TechSystem::~TechSystem()
{
    
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
    return StatusType::FAILURE;
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
    return StatusType::FAILURE;
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
    return StatusType::FAILURE;
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
    return 0;
}