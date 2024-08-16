//
// Created by Administrator on 24-8-16.
//

#include "StaffFactory.h"

#include <iostream>

#include "Boss.h"
#include "CommenStaff.h"
#include "Manger.h"

Staff *StaffFactory::CreateCommenStaff()  {
    return new CommenStaff();
}
Staff *StaffFactory::CreateBoss() {
    return new Boss();
}
Staff *StaffFactory::CreateManager() {
    return new Manger();
}
Staff *StaffFactory::CreateStaffByPostNum(int postNum) {
    switch (postNum) {
        case 1:
            return CreateCommenStaff();
        case 2:
            return CreateManager();
        case 3:
            return CreateBoss();
        default:
            return NULL;
    }
}



