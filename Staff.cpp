//
// Created by Administrator on 24-8-5.
//

#include "Staff.h"
#include "iostream"
#include "cstring"

Staff::Staff() {
    staffNum = 0;
    name = "";
    postNum = 0;
}
Staff::Staff(int staffNum, const std::string &name,int postNum) {
    this->staffNum = staffNum;
    this->name = name;
    this->postNum = postNum;
}
Staff::~Staff() {

}


