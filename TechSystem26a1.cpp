// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"


TechSystem::TechSystem()
{
    global_points=0;
}



TechSystem::~TechSystem()
{
    /*global_points=0;
    
    destroyCourseStudents(courses.m_root);

    courses.destroyTree(courses.m_root);
    courses.m_root = nullptr;
    courses.m_size = 0;

    students.destroyTree(students.m_root);
    students.m_root = nullptr;
    students.m_size = 0;*/
    
}

/*void destroyCourseStudents(AVLnode<int, std::shared_ptr<course>>* node) {
    if (!node) return;

    destroyCourseStudents(node->left);
    destroyCourseStudents(node->right);

    node->data->getStudentsTree().destroyTree(node->data->getStudentsTree().m_root);
    node->data->getStudentsTree().m_root = nullptr;
    node->data->getStudentsTree().m_size = 0;
}*/



StatusType TechSystem::addStudent(int studentId)
{
    if(studentId<=0){
        return StatusType::INVALID_INPUT;
    }
    if(students.ifExist(studentId)){
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
    if (studentId <= 0)
        return StatusType::INVALID_INPUT;

    if (!students.ifExist(studentId))
        return StatusType::FAILURE;

    std::shared_ptr<student> s = students.getData(studentId);
    if (s->getNumCourses() != 0)
        return StatusType::FAILURE;

    try {
        students.eraseKey(studentId);
    }
    catch (...) {
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

    if (!courses.ifExist(courseId))
        return StatusType::FAILURE;

    std::shared_ptr<course> c = courses.getData(courseId);
    if (c->getStudentCount() != 0)
        return StatusType::FAILURE;

    try {
        courses.eraseKey(courseId);
    }
    catch (...) {
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

    if (!courses.ifExist(courseId))
        return StatusType::FAILURE;

    auto& tree = courses.getData(courseId)->getStudentsTree();

    if (!tree.ifExist(studentId))
        return StatusType::FAILURE;

    std::shared_ptr<student> s = tree.getData(studentId);
    std::shared_ptr<course> c = courses.getData(courseId);

    s->addPoints(c->getPoints());
    s->removeCourse();

    try {
        tree.eraseKey(studentId);
    }
    catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }

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
    
    if (studentId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);

    if (!students.ifExist(studentId))
        return output_t<int>(StatusType::FAILURE);

    std::shared_ptr<student> s = students.getData(studentId);

       int total_points =
        global_points - s->getBasePoints() + s->getPersonalPoints();

    return output_t<int>(total_points);
}
