//
// Created by Administrator on 24-8-5.
//

#include "Staff.h"
#include "iostream"
#include "cstring"

Staff::Staff() {
    staffNum = 0;
    name = new char[1];
    name[0] = '\0';
    postNum = 0;
}
Staff::Staff(int staffNum,const char * name,int postNum) {
    this->staffNum = staffNum;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name,name);
    this->postNum = postNum;
}
Staff::~Staff() {
    delete this->name;
}


