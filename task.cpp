#include <sstream>
#include <ctime>
#include <iomanip>
#include <task.h>

#include <profile.h>
#include <QMessageBox>
#include <atlaswelcome.h>

Task::Task(string& name, string& start, string& end, string& due, string& catName,Profile *User):
    task_name(name),
    start_date_time(start),
    end_date_time(end),
    due_date_time(due),
    completeFlag(false){
    try{
        category = findCategory(catName);
    }catch(TaskException e){
        cout << e.what() << endl;
    }
    TaskUser = User;
    setTimes();
}
Task::Task(string& name, string& start, string& end, string& due, string& catName):
    task_name(name),
    start_date_time(start),
    end_date_time(end),
    due_date_time(due),
    completeFlag(false){
    try{
        category = findCategory(catName);
    }catch(TaskException e){
        cout << e.what() << endl;
    }
    setTimes();
}

Task::Task(string& name, QDateTime start, QDateTime end, QDateTime due, string& catName,Profile *User):
    task_name(name),
    completeFlag(false){

    time_t holder = time_t(start.toTime_t());
    start_date_time = ctime(&holder);
    holder = time_t(end.toTime_t());
    end_date_time = ctime(&holder);
    holder = time_t(due.toTime_t());
    due_date_time = ctime(&holder);

    start_date_time.erase(remove(start_date_time.begin(),start_date_time.end(),'\n'),start_date_time.end());
    end_date_time.erase(remove(end_date_time.begin(),end_date_time.end(),'\n'),end_date_time.end());
    due_date_time.erase(remove(due_date_time.begin(),due_date_time.end(),'\n'),due_date_time.end());
    catName.erase(remove(catName.begin(),catName.end(),'\n'),catName.end());

    try{
        category = findCategory(catName);
    }catch(TaskException e){
        cout << e.what() << endl;
    }
    TaskUser = User;
    setTimes();
}

Task::Task(string& in, Profile *User):
    completeFlag(false){
    string inputs[5];
    TaskUser = User;
    int i = 0;
    size_t pos = in.find(',');
    while(pos != string::npos && i < 6){
        inputs[i] = in.substr(0,pos);
        in.erase(0,pos+1);
        i++;
        pos = in.find(",");
    }


    try{
        category = findCategory(inputs[4]);
    }catch(TaskException e){
        cout << e.what() << endl;
    }
    task_name = inputs[0];
    start_date_time = inputs[1];
    end_date_time = inputs[2];
    due_date_time = inputs[3];
    setTimes();
}

Category* Task::findCategory(string& catName){
    Category* ptr = NULL;
    int i;
    for(i = 0; i < Profile::categories.size(); i++){
        if(Profile::categories[i]->getName() == catName){
            ptr = Profile::categories[i];
            break;
        }
    }
    if(ptr == NULL){
        throw TaskException("No category exists with this name");
    }
    else
        return ptr;
}

void Task::updateTimeString(){
    start_date_time = ctime(&task_time.start);
    start_date_time.erase(std::remove(start_date_time.begin(), start_date_time.end(), '\n'), start_date_time.end());

    end_date_time = ctime(&task_time.end);
    end_date_time.erase(std::remove(end_date_time.begin(), end_date_time.end(), '\n'), end_date_time.end());

    due_date_time = ctime(&due);
    due_date_time.erase(std::remove(due_date_time.begin(), due_date_time.end(), '\n'), due_date_time.end());

}

void Task::setTimes(){
    task_time.start = strToTime(start_date_time);
    task_time.end = strToTime(end_date_time);
    due = strToTime(due_date_time);
    task_time.duration = difftime(task_time.end,task_time.start);
}

time_t Task::strToTime(string& t){
    //string must have structure DDD MMM NN hh:mm:ss YYYY
    struct tm tm;
    istringstream ss(t);
    ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
    return mktime(&tm);
}

void Task::setStart(const time_t& time){
    task_time.start = time;
    time_t t = static_cast<time_t>(task_time.duration);
    task_time.end = task_time.start + t;
    updateTimeString();
}

bool Task::getComplete() const{ return completeFlag; }

void Task::setComplete(bool t) {
    completeFlag = t;
    increment();
}

void Task::increment(){

    QMessageBox msgBox;
    msgBox.setText("Congratulations, you have unlocked new items in your treasure chest!");

    if (TaskUser->Stats.productivity==100){
        msgBox.exec();
        //TODO unlock item here
        //TaskUser->unlockItem();
        TaskUser->lockedItem=true;
        TaskUser->Stats.productivity=0;
    }
    TaskUser->Stats.productivity+=50;

    if(task_time.end<due){
        if (TaskUser->Stats.timeManagement==100){
            msgBox.exec();
            //TODO unlock item here
            //TaskUser->unlockItem();
            TaskUser->lockedItem=true;
            TaskUser->Stats.timeManagement=0;
        }
        TaskUser->Stats.timeManagement+=50;
    }
}

Category* Task::getCategory() const{ return category; }

string Task::getName() const{ return task_name; }

string Task::getDue() const{ return due_date_time; }

int Task::getDrawingDay() const {
   struct tm* tm = localtime(&task_time.start);
   int day = ++(tm->tm_wday);
   return day;
}

std::string Task::getStart() const{ return start_date_time; }

pair<int, int> Task::getDrawingStart() const{
    pair<int, int> pr;
    struct tm* tm = localtime(&task_time.start);
    pr.first = tm->tm_hour;
    pr.second = tm->tm_min;
    return pr;
}

pair<int, int> Task::getDrawingEnd() const{
    pair<int, int> pr;
    struct tm* tm = localtime(&task_time.end);
    pr.first = tm->tm_hour;
    pr.second = tm->tm_min;
    return pr;
}

string Task::getEnd() const{ return end_date_time; }

string Task::getDuration() const{ return duration_date_time; }

string Task::fileWrite() const{
    string output = task_name+","+start_date_time+","+end_date_time+","+due_date_time+","+ category->getName()+",";
    return output;
}

bool Task::compare(const Task& right){
    if(due > right.due)
        return false;
    else if (due < right.due)
        return true;
    else{
        if(task_time.duration > right.task_time.duration)
            return false;
        else if(task_time.duration < right.task_time.duration)
            return true;
        else{
            if(category->getPriority() > right.getCategory()->getPriority())
               return false;
            else if(category->getPriority() < right.getCategory()->getPriority())
               return true;
            else
               return getName() < right.getName();
        }
    }
}

bool Task::operator<(const Task& right){
    return compare(right);
}

bool Task::operator==(const Task& right){
    return task_time == right.task_time &&
            task_name == right.getName() &&
            duration_date_time == right.getDuration() &&
            due_date_time == right.getDue();
}

bool Task::time_period::operator==(const time_period& right){
    return start == right.start && end == right.end;
}

bool Task::time_period::operator<( const time_period& right){
    if(duration != right.duration)
        return duration < right.duration;
    else{
        return start < right.start;
    }
}

void Task::print(){
    std::string s_start(ctime(&task_time.start)),
                s_end(ctime(&task_time.end));
    std::cout << "name: " << task_name << std::endl
              << "start: " << s_start
              << "end:   " << s_end;
}

void Task::time_period::print(){
    std::string s_start(ctime(&start)),
                s_end(ctime(&end));
    std::cout << "start: " << s_start
              << "end:   " << s_end;
}

TaskException::TaskException(string msg) : message(msg){}
string& TaskException::what() { return message; }
//----------------------------------------------------------------------------


Category::Category(string& name, int colour, int p){
    init(name,colour,p);

}

Category::Category(string& in){
    string inputs[3];
    size_t pos = 0;
    int i = 0;
    pos = in.find(',');
    while(pos != string::npos && i < 4){
        inputs[i] = in.substr(0,pos);
        in.erase(0,pos+1);
        i++;
        pos = in.find(',');
    }

    int colour = atoi(inputs[1].c_str()),
        p = atoi(inputs[2].c_str());

    init(inputs[0],colour,p);
}

void Category::init(string& name, int colour, int p){
    this->catName = name;
    this->colour = colour;
    this->priority = p;
    visible = true;
}

void Category::incPriority(){
    if(priority > 3){
        swap(*Profile::categories[priority-1]);
        priority--;
    }
}

void Category::decPriority(){
    if(priority < Profile::categories.size() - 1){
        swap(*Profile::categories[priority + 1]);
        priority++;
    }
}

void Category::setPriority(int n){
    priority = n;
}

void Category::swap(Category& c){
    iter_swap(Profile::categories.begin()+priority, Profile::categories.begin()+c.getPriority());
    c.setPriority(priority);
}

string Category::fileWrite() const{
    string c = to_string(colour),
                p = to_string(priority);

    string output = catName+","+c+","+p+",";
    return output;
}

QColor Category::getColour()
{
    if(colour >= 1670000){
        categorycolour = red;
        return Qt::red;
    }else if( colour >= 65000){
        categorycolour = green;
        return Qt::green;
    }else{
        categorycolour = mauve;
        return Qt::blue;
    }
}

int Category::getPriority() const{return priority;}

string Category::getName() const{return catName;}

void Category::changeVisible(){ visible = !visible; }

bool Category::isVisible() const { return visible; }

void Category::setVisible(bool newValue) { visible = newValue; }
