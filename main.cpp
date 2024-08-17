#include <algorithm>
#include <limits>
#include <vector>

#include "AbstractStaffFactory.h"
#include "iostream"
#include "conio.h"
#include "Boss.h"
#include "Manger.h"
#include "CommenStaff.h"
#include "fstream"
#include "StaffFactory.h"
using namespace std;

// 存放员工数据的目录
const char* STAFF_TXT_PATH = "staff.txt";
// 函数列表
int getNum();
bool staffNumExist(int num);
bool writeStaffToFile(Staff* staff);
bool writeStaffVectorToFile(vector<Staff*> &staffVector,bool ifAdd);
bool addStaff();
bool readStaffFileToVector(vector<Staff*> &staffVector);
bool showStaffTable();
void testFunction();
bool menu();
bool deleteStaffByStaffNum(int staffNum);
bool deleteStaffVectorMemory(vector<Staff*> &staffVector);
vector<Staff*>::iterator getIteratorByStaffNum(vector<Staff*> &staffVector,int staffNum);
bool updateStaffByStaffNum(int staffNum);
bool sortStaffByStaffNum(int rule);
bool srotStaffRuleS(Staff* staff1,Staff* staff2);
bool srotStaffRuleJ(Staff* staff1,Staff* staff2);
bool updateStaff();
bool sortStaff();
bool clearFile();
bool clearAllStaff();
/**
 * 主函数
 * @return 0
 */
int main() {

    while(menu()) {

    }

    //testFunction();
}

/**
 * 获取控制台输入整数
 * @return 从控制台输入的整数（非整数会进入循环，直到输入整数）
 */
int getNum() {
    int num;
    bool flag = true;
    while (flag) {
        cin >> num;
        if (cin.fail()) {
            cin.clear(); // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃错误输入
            cout << "输入无效，请输入一个整数..." << endl;
        }else {
            flag = false;
        }
    }
    return num;
}


/**
 * 释放员工列表内存
 * @param staffVector 员工列表
 * @return 释放成功返回true
 */
bool deleteStaffVectorMemory(vector<Staff*> &staffVector) {
    vector<Staff*> ::iterator iter = staffVector.begin();
    for(;iter != staffVector.end(); ++iter) {
        delete (*iter);
    }
    return true;
}

/**
 *
 * @param staffVector 员工列表
 * @param staffNum 职工编号
 * @return 返回该员工编号处的迭代器
 */
vector<Staff*>::iterator getIteratorByStaffNum(vector<Staff*> &staffVector,int staffNum) {
    vector<Staff*> ::iterator iter = staffVector.begin();
    for(;iter != staffVector.end(); ++iter) {
        if(staffNum == (*iter)->staffNum)
            return iter;
    }
    return staffVector.end();
}
/**
 *
 *  判断员工编号是否存在
 * @param num 员工编号
 * @return 该编号已存在返回true 不存在返回false
 */
bool staffNumExist(int num) {
    vector<Staff*> staffVector;
    bool flag = false;
    if(!readStaffFileToVector(staffVector))
        return false;
    for(vector<Staff*>::iterator iter = staffVector.begin();iter != staffVector.end(); ++iter) {
        if(num == (*iter)->staffNum) {
            flag = true;
            delete (*iter);
        }
    }
    return flag;
}

/**
 * 写入单个员工数据
 * @param staff 要写入文件的员工
 * @return 写入成功返回true
 */
bool writeStaffToFile(Staff* staff) {
    ofstream ofs(STAFF_TXT_PATH,ios::out|ios::app);
    if(!ofs.is_open()) {
        cout << "文件打开失败！" << endl;
        return false;
    }
    ofs << staff->staffNum << " " << staff->name << " " << staff->postNum << endl;
    delete staff;
    ofs.close();
    return true;
}

/**
 *
 * @param staffVector 写入到文件中的员工列表
 * @return 打开文件失败返回false
 */
bool writeStaffVectorToFile(vector<Staff*> &staffVector,bool ifAdd) {
    ofstream ofs;
    if(ifAdd) {
        ofs.open(STAFF_TXT_PATH,ios::out|ios::app);
    }else {
        ofs.open(STAFF_TXT_PATH,ios::out);
    }

    if(!ofs.is_open()) {
        cout << "文件打开失败！" << endl;
        return false;
    }
    for(vector<Staff*>::iterator iter = staffVector.begin(); iter != staffVector.end(); ++iter) {
        // 写入文件
        ofs << (*iter)->staffNum << " " << (*iter)->name << " " << (*iter)->postNum << endl;
        delete (*iter);// 展示完成后 释放掉内存
    }
    ofs.close();
    return true;
}
/**
 *  增加员工
 */
bool addStaff() {
    cout << "请输入要增加的职工数量：";
    int num = getNum();
    AbstractStaffFactory *staff_factory = new StaffFactory();  // 创建一个员工创建工厂  便于多次创建对象
    // 改为单个存储 防止批量存储中存在重复的员工编号
    //vector<Staff*> staffVector;  // 存储批量增加的员工
    for (int i = 0; i < num; ++i) {
        int staff_post = 0;
        while(1) {
            cout << "请选择该职工的岗位" << endl;
            cout << "1、普通员工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            staff_post = getNum();
            if(staff_post > 0 && staff_post <= 3) {
                break;
            }
            cout << "请在1-3中选择..." << endl;
        }
        cout << "请输入该职工的编号" << endl;
        int staff_num = getNum();
        while(staffNumExist(staff_num)) {
            cout << "已存在，请重新输入该职工的编号" << endl;
            staff_num = getNum();
        }
        // 处理输入后残留的换行符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "请输入该职工的姓名" << endl;
        char *staff_name = new char[20];
        cin.getline(staff_name,20);
        Staff *staff = staff_factory->CreateStaffByPostNum(staff_post);
        staff->name = staff_name;
        staff->staffNum = staff_num;
        staff->postNum = staff_post;
        if(!writeStaffToFile(staff)) {
            cout << "写入文件发生错误！" << endl;
            return false;
        }
        //staffVector.push_back(staff);
        /*采用工厂模式  可以更加简便
         *switch (staff_post) {
            case 1:
                staff = new CommenStaff(staff_num,staff_name,staff_post);
                staffList[i] = staff;
                break;
            case 2:
                staff = new Manger(staff_num,staff_name,staff_post);
                staffList[i] = staff;
                break;
            case 3:
                staff = new Boss(staff_num,staff_name,staff_post);
                staffList[i] = staff;
                break;
        }*/
    }
    /*if(writeStaffVectorToFile(staffVector,true)) {
        cout << "成功写入到文件中！" << endl;
        return true;
    }*/
    cout << "成功写入到文件中！" << endl;
    return true;
}



/**
 *
 * @param staffVector 存储员工列表的容器
 * @return 打开文件失败返回 false
 */
bool readStaffFileToVector(vector<Staff*> &staffVector) {
    ifstream ifs(STAFF_TXT_PATH,ios::in);
    if(!ifs.is_open()) {
        cout << "文件打开失败！" << endl;
        return false;
    }
    // 创建员工的工厂类
    AbstractStaffFactory * staffFactory = new StaffFactory();
    string buf;  // 缓冲字符串
    while(getline(ifs,buf)) {
        //cout << buf << endl;
        int space1 = buf.find(' ');
        int space2 = buf.find_last_of(' ');
        int staffNum = atoi(&buf[0]);  // 将字符类型转换为整数类型 （根据字符的数值直接转换而非根据ASCII码转换）
        // TODO: 名字长度似乎有问题  以后再改
        string name = buf.substr(space1,space2-space1);
        //cout << name << endl;
        int postNum = atoi(&buf[space2 + 1]);
        // 根据员工职位编号创建
        Staff *staff_read = staffFactory->CreateStaffByPostNum(postNum);
        staff_read->staffNum = staffNum;
        staff_read->name = name;
        staff_read->postNum = postNum;
        staffVector.push_back(staff_read);
        //delete staff_read;  // 不能立即释放内存  要把这部分内存交给staffVector来管理
    }
    delete staffFactory;
    ifs.close();
    return true;
}

/**
 *  展示员工列表
 */
bool showStaffTable() {
    vector<Staff*> staffVector;
    if(readStaffFileToVector(staffVector)) {
        for(vector<Staff*>::iterator iter = staffVector.begin(); iter != staffVector.end(); ++iter) {
            // TODO: 名字过长 对齐问题
            (*iter)->display();
            delete (*iter);// 展示完成后 释放掉内存
        }
        /*建议使用迭代器方式访问
         *for (int i = 0;i < staffVector.size(); ++i) {
            // TODO: 名字过长 对齐问题
            staffVector[i]->display();
            delete staffVector[i];
        }*/
        return true;
    }
    return false;
}

/**
 * 根据员工编号删除
 * @param staffNum 员工编号
 * @return 删除成功返回true
 */
bool deleteStaffByStaffNum(int staffNum) {
    vector<Staff*> staffVector;
    bool flag = false;
    if(!readStaffFileToVector(staffVector))
        return false;
    /*for(vector<Staff*>::iterator iter = staffVector.begin();iter != staffVector.end();++iter) {
        if(staffNum == (*iter)->staffNum) {
            flag = true;
            delete (*iter);
            iter-- = staffVector.erase(iter);

        }
    }*/
    vector<Staff*>::iterator iter = getIteratorByStaffNum(staffVector,staffNum);
    if(staffVector.end() != iter) {
        cout << "员工：" << (*iter)->name << "将被删除，确定要继续吗？(1、继续  2、返回)" << endl;
        int comfirm = getNum();
        if(comfirm != 1) {
            cout << "取消了删除操作！" << endl;
            return false;
        }
        flag = true;
        delete (*iter);
        staffVector.erase(iter);
        cout << "删除成功！" << endl;
    }else {
        cout << "未找到该员工" << endl;
        return false;
    }

    if(!writeStaffVectorToFile(staffVector,false)) {
        cout << "文件写入失败" << endl;
        return false;
    }
    return true;
}

/**
 * 删除员工
 * @return
 */
bool deleteStaff() {
    cout << "请输入要删除的员工编号：" << endl;
    int staffNum = getNum();
    return deleteStaffByStaffNum(staffNum);
}

bool showStaffInfoByStaffNum(int staffNum) {
    vector<Staff*> staffVector;
    if(!readStaffFileToVector(staffVector)) {
        cout << "获取员工列表发生错误" << endl;
        return false;
    }
    vector<Staff*>::iterator iter = getIteratorByStaffNum(staffVector,staffNum);
    if(iter == staffVector.end()) {
        cout << "不存在该员工！" << endl;
        return false;
    }
    cout << "员工信息：" << endl;
    (*iter)->display();
    deleteStaffVectorMemory(staffVector); // 清理占用的内存
    return true;
}

/**
 * 查找职工信息
 * @return
 */
bool findStaffInfo() {
    cout << "请输入你要查找的员工编号:" << endl;
    int staffNum = getNum();
    return showStaffInfoByStaffNum(staffNum);
}

/**
 * 根据员工编号修改员工信息
 * @param staffNum 员工编号
 * @return
 */
bool updateStaffByStaffNum(int staffNum) {
    vector<Staff*> staffVector;
    if(!readStaffFileToVector(staffVector)) {
        cout << "获取员工列表发生错误" << endl;
        return false;
    }
    vector<Staff*>::iterator iter = getIteratorByStaffNum(staffVector,staffNum);
    if(staffVector.end() != iter) {
        cout << "员工信息：" << endl;
        (*iter)->display();
        cout << "请重新填写职工信息：" << endl;
        int staff_post = 0;
        while(1) {
            cout << "请选择该职工修改后的岗位" << endl;
            cout << "1、普通员工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            staff_post = getNum();
            if(staff_post > 0 && staff_post <= 3) {
                break;
            }
            cout << "请在1-3中选择..." << endl;
        }
        // 处理输入后残留的换行符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "请输入该职工的修改后姓名" << endl;
        char *staff_name = new char[20];
        cin.getline(staff_name,20);

        (*iter)->name = staff_name;
        (*iter)->postNum = staff_post;
        if(writeStaffVectorToFile(staffVector,false)) {
            cout << "员工信息修改成功！" << endl;
            return true;
        }

        return false;
    }else {
        cout << "未找到该员工" << endl;
        return false;
    }
}

/**
 * 更新员工
 * @return
 */
bool updateStaff() {
    cout << "请输入你要修改的员工编号:" << endl;
    int staffNum = getNum();
    return updateStaffByStaffNum(staffNum);
}

/**
 * 降序规则
 * @param staff1
 * @param staff2
 * @return
 */
bool srotStaffRuleJ(Staff* staff1,Staff* staff2) {
    if(staff1->staffNum > staff2->staffNum)
        return true;
    return false;
}

/**
 * 升序规则
 * @param staff1
 * @param staff2
 * @return
 */
bool srotStaffRuleS(Staff* staff1,Staff* staff2) {
    if(staff1->staffNum < staff2->staffNum)
        return true;
    return false;
}

/**
 * 对员工列表进行排序
 * @param rule 排序规则 （1 代表升序 其他代表降序）
 * @return
 */
bool sortStaffByStaffNum(int rule) {
    vector<Staff*> staffVector;
    if(!readStaffFileToVector(staffVector)) {
        cout << "获取员工列表发生错误" << endl;
        return false;
    }
    if(1 == rule) {
        sort(staffVector.begin(),staffVector.end(),srotStaffRuleS);
    }else {
        sort(staffVector.begin(),staffVector.end(),srotStaffRuleJ);
    }
    writeStaffVectorToFile(staffVector,false);
    return true;
}

/**
 * 对员工列表排序排序
 * @return
 */
bool sortStaff() {
    cout << "请选择排序规则：" << endl;
    cout << "1、升序" << endl;
    cout << "2、降序" << endl;
    int rule = getNum();
    return sortStaffByStaffNum(rule);
}

bool clearFile() {
    ofstream ofs(STAFF_TXT_PATH,ios::out);
    if(!ofs.is_open()) {
        cout << "文件打开失败！" << endl;
        return false;
    }
    ofs.clear();
    ofs.close();
    return true;
}

bool clearAllStaff() {
    cout << "这是一个高危操作，所有员工数据将被删除，确定要继续吗？(1、继续  2、返回)" << endl;
    int comfirm1 = getNum();
    if(comfirm1 != 1) {
        cout << "取消了清空操作！" << endl;
        return false;
    }
    cout << "真的确定要继续吗？(1、继续  2、返回)" << endl;
    int comfirm2 = getNum();
    if(comfirm2 != 1) {
        cout << "取消了清空操作！" << endl;
        return false;
    }

    return true;
}

/**
 *  测试函数
 */
void testFunction() {

}

/**
 *  菜单显示
 * @return 菜单输入无效返回false
 */
bool menu() {
    cout << "*******************************************" << endl;
    cout << "************ 欢迎使用职工管理系统！ ***********" << endl;
    cout << "***************  0.退出管理程序  ************" << endl;
    cout << "***************  1.增加职工信息  ************" << endl;
    cout << "***************  2.显示职工信息  ************" << endl;
    cout << "***************  3.删除职工信息  ************" << endl;
    cout << "***************  4.修改职工信息  ************" << endl;
    cout << "***************  5.查找职工信息  ************" << endl;
    cout << "***************  6.按照编号排序  ************" << endl;
    cout << "***************  7.清空所有文档  ************" << endl;
    cout << "*******************************************" << endl;
    cout << "请输入您的选择：" << endl;


    int op = getNum();
    switch (op) {
        case 0:
            // 退出管理程序
        cout << "程序退出成功！" << endl;
        return false;
        case 1:
            // 增加职工信息
                addStaff();
                //testFunction();
                break;
        case 2:
            // 显示职工信息
                showStaffTable();
                break;
        case 3:
            // 删除职工信息
                deleteStaff();
                break;
        case 4:
            // 修改职工信息
                updateStaff();
                break;
        case 5:
            // 查找职工信息
                findStaffInfo();
                break;
        case 6:
            // 按照编号排序
                sortStaff();
                break;
        case 7:
            // 清空所有文档
                clearAllStaff();
                break;
        default:
            cout << "输入无效，请输入0到7之间的整数..." << endl;
            break;
    }

    system("cls");
    return true;
}



