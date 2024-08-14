//
// Created by Administrator on 24-8-5.
//

#include "Manger.h"
#include "iostream"


std::string Manger::getPost() {
    return "经理";
}

Manger::Manger() {
}

Manger::Manger(int staffNum, char *name, int post) {
    this->staffNum = staffNum;
    this->name = name;
    this->postNum = post;
}

void Manger::display() {
    std::cout << "员工编号：" << staffNum << "\t姓名：" << name << "\t职位：" << getPost() << "\t职责：" << duty << std::endl;
}