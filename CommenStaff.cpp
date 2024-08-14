//
// Created by Administrator on 24-8-5.
//

#include "CommenStaff.h"
#include "iostream"


std::string CommenStaff::getPost() {
    return "普通员工";
}

CommenStaff::CommenStaff() {
}

CommenStaff::CommenStaff(int staffNum, char *name, int post) {
    this->staffNum = staffNum;
    this->name = name;
    this->postNum = post;
}

void CommenStaff::display() {
    std::cout << "员工编号：" << staffNum << "\t姓名" << name << "\t职位：" << getPost() << "\t职责：" << duty << std::endl;
}
