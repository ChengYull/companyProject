#include <limits>

#include "iostream"
#include "conio.h"
#include "Boss.h"
#include "Manger.h"
#include "CommenStaff.h"
#include "fstream"
using namespace std;

// 存放员工数据的目录
const char* STAFF_TXT_PATH = "staff.txt";

int getNum() {
    int num;
    cin >> num;
    if (cin.fail()) {
        cin.clear(); // 清除错误标志
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃错误输入
        cout << "输入无效，请输入一个整数..." << endl;
        return 0;
    }else {
        return num;
    }
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
 *  增加员工
 */
void addStaff() {
    cout << "请输入要增加的职工数量：";
    int num = getNum();
    Staff *staffList[num];
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
        Staff *staff;
        switch (staff_post) {
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
        }
    }
    for (int i = 0; i < num; ++i) {
        staffList[i]->display();
    }
}

int menu() {
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
        exit(0);
        case 1:
            // 增加职工信息
                addStaff();
                break;
        case 2:
            // 显示职工信息

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
    return 1;
}

void testFunction() {
    Staff *s1 = new Boss(1,"程渝",1);
    Staff *s2 = new CommenStaff(2,"张三",2);
    Staff *s3 = new Manger(3,"李四",3);
    Staff *staffList[] = {s1,s2,s3};
    addStaffListToFile(staffList);

}

int main() {
    /*Staff *s = new CommenStaff(1,"zs",1);
    saveStaff(s);
    getStaff();*/
    /*while(menu()) {

    }*/

    testFunction();
}