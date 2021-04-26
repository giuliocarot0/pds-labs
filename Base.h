//
// Created by giuli on 21/04/2021.
//

#ifndef LAB2_PDS_BASE_H
#define LAB2_PDS_BASE_H
#include <string>

using namespace std;

class Base{
private:
    string name;

public:
    Base(string name): name(name){};
    ~Base(){};

    string getName() const{
        return name;
    };
    virtual int mType() const = 0;
    virtual void ls(int indent) const = 0;
};


#endif //LAB2_PDS_BASE_H
