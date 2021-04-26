//
// Created by giuli on 21/04/2021.
//

#ifndef LAB2_PDS_DIRECTORY_H
#define LAB2_PDS_DIRECTORY_H
#include <map>
#include "File.h"


class Directory : public Base {
    Directory *parent;
    map<string,Base *> children;







public:

    Directory(string name, Directory *parent) : Base(name){
        this->parent = parent;
        children["."] = this;
        children[".."] = this->parent;

    }

    ~Directory(){
    }

    File *addFile(const string &name, uintmax_t size){
        if(this->children[name] != nullptr) return nullptr;

        try {
             auto *newFile = new File(name,size,size);
             this->children[name] = newFile;
             return newFile;
        }
        catch(exception &e){
            return nullptr;
        }
    }

    int mType () const override {
        return 1;
    }

    void ls (int indent) const override{
        int offset=4;
        string ind = "";
        for (int s = 0; s < indent; s++)
            ind += " ";
        if(indent!=0) offset=indent;

        cout <<  ind << Base::getName() <<"\\"<<endl;
        for (auto const& [key, val] : children){
            if(key=="." || key==".."){continue;}
            val->ls(indent+offset);
        }
    }

    /*get the path parent*/
    Directory* getRoot(){
        if(this->parent == nullptr)
            return this;
        else this->parent->getRoot();
    }

    /*add a directory to the current one*/
    Directory* addDirectory(const string &name){
        Base* element = this->children[name];
        if(element != nullptr) {
            if (element->mType()) return dynamic_cast<Directory *> (element);
            else return nullptr;
        }
        else {
            try {
                auto *newdir = new Directory(name, this);
                this->children[name] = newdir;
                return newdir;
            }
            catch (exception &e){
                return nullptr;
            }
        }
    }

    /*get an item */
    Base* get(const string &name){
        return this->children[name];
    }

    map<string, Base*> getChildren(){
        return this->children;
    }

    Directory* getDirectory(const string &name){
        return (this->children[name]->mType()) ? dynamic_cast<Directory*> (this->children[name]) : nullptr;
    }
    File* getFile(const string &name){
        return (!this->children[name]->mType()) ? dynamic_cast<File*> (this->children[name]) : nullptr;
    }
    bool remove(const string &name){
        if(name == ".." || name == "." || this->get(name) == nullptr) return false;
        Base* item = get(name);
        if(!item->mType()) {
            children.erase(children.find(name));
            delete dynamic_cast<File*>(item);
        }
        else {
            dynamic_cast<Directory*>(item)->rmchildren();
            children.erase(children.find(name));
            delete dynamic_cast<Directory*>(item);
        }
        return true;
    }

    void rmchildren(){
        int offset;
        map<string, Base*>::iterator  it;
        for (it=this->children.begin(); it!=this->children.end(); it++) {
            if(remove(it->first))
                it = this->children.begin();
        }
    }

    bool move(const string& name, Directory* target){
        if(target->appendChild(this->get(name))){
            this->children.erase(this->children.find(name));
        }
    }

    bool appendChild(Base* item){
        Base* element = this->children[item->getName()];
        if(element != nullptr )
            return false;
        else {
            this->children[item->getName()] = item;
            return true;
        }


    }
};


#endif //LAB2_PDS_DIRECTORY_H
