#ifndef TASKFIXTURE_H
#define TASKFIXTURE_H

class Task;
#include <memory>

struct TaskFixture {
    TaskFixture();
    ~TaskFixture();

    std::shared_ptr<Task> sptask;
};

#endif //TASKFIXTURE_H
