#include<iostream>
#include<string>
#include<chrono>
#include<fstream>
#include<vector>
#include<utility>
struct TaskInfo
{
    std::string name;
    std::string message;
};
class TaskSession
{
    private:
        std::string Name;
        std::chrono::steady_clock::time_point StartTime;
        std::ofstream logFile;
    public:
        TaskSession(const std::string newName);
        ~TaskSession();
};
class TaskRunner
{
    private:
        std::vector<TaskInfo> tasks;
    public:
        void addTask(const TaskInfo& task);
        void addTask(TaskInfo&& task);
        void runAll() const;
};
TaskSession::TaskSession(const std::string newName)
:Name(newName),
StartTime(std::chrono::steady_clock::now()),
logFile("tasks.log",std::ios::app)
{
    std::cout << "Start:" << Name << '\n';
    if(!logFile)
    {
        std::cerr << "Failed to open tasks.log\n";
    }
    else
    {
        logFile << "Start:" << Name << '\n';
    }
}
TaskSession::~TaskSession()
{
    auto EndTime = std::chrono::steady_clock::now();
    std::chrono::duration<double,std::milli> elapsed = EndTime - StartTime;
    std::cout << "End:" << Name  << ",elapsed:" << elapsed.count() << "ms\n";
    if(logFile)
    {
        logFile << "End:" << Name  << ",elapsed:" << elapsed.count() << "ms\n";
    }
}
void TaskRunner::addTask(const TaskInfo& task)
{
    std::cout << "Copy submission\n";
    tasks.push_back(task);
    return;
}
void TaskRunner::addTask(TaskInfo&& task)
{
    std::cout << "Move submission\n";
    tasks.push_back(std::move(task));
    return;
}
void runTask(const TaskInfo& task)
{
    TaskSession session{task.name};
    std::cout << task.message << '\n';
    return;
}
void TaskRunner::runAll() const
{
    for(const auto& task:tasks)
    {
        runTask(task);
    }
}
int main()
{
    TaskRunner runner;
    TaskInfo First{"hello","Hello from task"};
    TaskInfo Second{"hello","Hello from task"};
    runner.addTask(First);
    runner.addTask(std::move(Second));
    runner.runAll();
    return 0;
}