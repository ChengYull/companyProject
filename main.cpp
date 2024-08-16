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

/**
 * 
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

/*
 *  存储员工至文件中
 */
/*void saveStaff(Staff *staff) {
    ofstream ofs("staff.txt",ios::out|ios::app|ios::binary);
    if(!ofs.is_open()) {
        cout << "文件打开失败！"<< endl;
        return;
    }
    ofs.write((const char *)staff,sizeof(Staff));
    cout << "存储成功..." << endl;
    ofs.close();
}*/

/*
 *  读取文件中的员工列表
 */
/*void getStaff() {
    ifstream ifs(STAFF_TXT_PATH,ios::in|ios::binary);
    if(!ifs.is_open()) {
        cout << "文件打开失败！"<< endl;
        return;
    }
    Staff *staff = new CommenStaff();
    cout << "开始读取..." << endl;
    while(ifs.read((char *)staff,sizeof(Staff))) {
        cout << staff->name << endl;
        cout << staff->staffNum << endl;
        staff->display();
    }
    ifs.close();
}*/

/**
 *  添加员工列表至文件中
 */
bool addStaffListToFile(Staff *staffList[]) {
    ofstream ofs(STAFF_TXT_PATH,ios::out|ios::binary);
    if(!ofs.is_open()) {
        cout << "文件打开失败！" << endl;
        return false;
    }
    ofs.write((const char *)staffList,sizeof(staffList));
    cout << "size:" << sizeof(staffList) << endl;

    ofs.close();
    return true;
}
/**
 *  从文件中读取员工列表
 */
bool readFileToGetStaffList(Staff* staffList[]) {
    ifstream ifs(STAFF_TXT_PATH,ios::in|ios::binary);
    if(!ifs.is_open()) {
        cout << "文件打开失败！" << endl;
        return false;
    }
    Staff *buffer;
    while(ifs.read((char *) buffer,sizeof buffer)) {
        buffer->display();
    }
    return true;
}
/**
 *
 * @param staffVector 写入到文件中的员工列表
 * @return 打开文件失败返回false
 */
bool writeStaffVectorToFile(vector<Staff*> &staffVector) {
    ofstream ofs(STAFF_TXT_PATH,ios::out|ios::app);
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
    vector<Staff*> staffVector;  // 存储批量增加的员工
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
        // 处理输入后残留的换行符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "请输入该职工的姓名" << endl;
        char *staff_name = new char[20];
        cin.getline(staff_name,20);
        Staff *staff = staff_factory->CreateStaffByPostNum(staff_post);
        staff->name = staff_name;
        staff->staffNum = staff_num;
        staff->postNum = staff_post;
        staffVector.push_back(staff);
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
    if(writeStaffVectorToFile(staffVector)) {
        cout << "成功写入到文件中！" << endl;
        return true;
    }
    return false;
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
 *  测试函数
 */
void testFunction() {
    Staff *s1 = new Boss(1,"程渝",1);
    Staff *s2 = new CommenStaff(2,"张三",2);
    Staff *s3 = new Manger(3,"lisi",3);
    Staff *staffList[] = {s1,s2,s3};
    //addStaffListToFile(staffList);


    //Staff *buf;

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

                break;
        case 4:
            // 修改职工信息

                break;
        case 5:
            // 查找职工信息

                break;
        case 6:
            // 按照编号排序

                break;
        case 7:
            // 清空所有文档

                break;
        default:
            cout << "输入无效，请输入0到7之间的整数..." << endl;
            break;
    }

    system("cls");
    return true;
}



int main() {
    Staff *s = new CommenStaff(1,"zs",1);

    while(menu()) {

    }

    //testFunction();
}