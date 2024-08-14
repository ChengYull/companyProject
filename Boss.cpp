//
// Created by Administrator on 24-8-5.
//

#include "Boss.h"
#include "iostream"


std::string Boss::getPost() {
    return "老板";
}

Boss::Boss() {
}

Boss::Boss(int staffNum, char *name, int post) {
    this->staffNum = staffNum;
    this->name = name;
    this->postNum = post;
}
void Boss::display() {
    std::cout << "员工编号：" << staffNum << "\t姓名" << name << "\t职位：" << getPost() << "\t职责：" << duty << std::endl;
}