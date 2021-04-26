//
// Created by giuli on 21/04/2021.
//
#include "Base.h"

#ifndef LAB2_PDS_FILE_H
#define LAB2_PDS_FILE_H
class File : public Base {
private:
    uintmax_t size;
    uintmax_t date;
public:
    File(string name,uintmax_t size, uintmax_t date ) : Base(name){
        this->size = size;
        this->date = date;
    }
    ~File(){}

    uintmax_t getSize() const {
        return size;
    }
    uintmax_t getDate() const {
        return date;
    }

    int mType () const override {
        return 0;
    }
    void ls (int indent) const override{
        string ind = "";
        for (int s= 0; s < indent; s++)
            ind += " ";
        cout <<  ind << Base::getName() << " " << this->size << endl;
    }
};
#endif //LAB2_PDS_FILE_H
