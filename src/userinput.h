#ifndef USER_INPUT_H
#define USER_INPUT_H

class TaskManager;
class TaskView;

class UserInput {
public:
    UserInput(TaskManager& tm, const TaskView& tv);
    ~UserInput();

    void commands(int ac, const char* av[]) const;
private:
    TaskManager& taskmanager;
    const TaskView& taskview;
};

#endif // USER_INPUT_H

