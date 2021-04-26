//
// Created by giuli on 21/04/2021.
//

#ifndef LAB2_PDS_DIRECTORY_H
#define LAB2_PDS_DIRECTORY_H
#include <map>
#include "File.h"
#include <memory>

class Directory : public Base {
    weak_ptr<Directory> parent;
    map<string,shared_ptr<Base>> children;

public:

    Directory(string name, shared_ptr<Directory> parent) : Base(name){
        this->parent = parent;
        children[".."] = parent;

    }

    ~Directory(){
    }

    shared_ptr<File> addFile(const string &name, uintmax_t size){
        if(this->children[name] != nullptr) return nullptr;

        try {
             shared_ptr<File> newFile(new File(name,size,size));
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
    weak_ptr<Directory> getRoot(){
        if(this->parent.lock() == nullptr)
            return shared_ptr<Directory> (this);
        else this->parent.lock()->getRoot();
    }

    /*add a directory to the current one*/
    shared_ptr<Directory> addDirectory(const string &name){
        shared_ptr<Base> element = this->children[name];
        if(element != nullptr) {
            if (element->mType()) return dynamic_pointer_cast<Directory>(element);
            else return nullptr;
        }
        else {
            try {
                shared_ptr<Directory>newdir(new Directory(name, shared_ptr<Directory>(this)));
                this->children[name] = newdir;
                return newdir;
            }
            catch (exception &e){
                return nullptr;
            }
        }
    }

    /*get an item */
    shared_ptr<Base> get(const string &name){
        return this->children[name];
    }

    map<string, shared_ptr<Base>> getChildren(){
        return this->children;
    }

    shared_ptr<Directory> getDirectory(const string &name){
        return (this->children[name]->mType()) ? dynamic_pointer_cast<Directory>(this->children[name]) : nullptr;
    }
    shared_ptr<File> getFile(const string &name){
        return (!this->children[name]->mType()) ? dynamic_pointer_cast<File>(this->children[name]) : nullptr;
    }
    bool remove(const string &name){
        if(name == ".." || name == "." || this->get(name) == nullptr) return false;
        shared_ptr<Base> item = get(name);
        if(!item->mType()) {
            children.erase(children.find(name));
        }
        else {
            dynamic_pointer_cast<Directory>(item)->rmchildren();
            children.erase(children.find(name));
        }
        return true;
    }

    void rmchildren(){
        int offset;
        map<string, shared_ptr<Base>>::iterator  it;
        for (it=this->children.begin(); it!=this->children.end(); it++) {
            if(remove(it->first))
                it = this->children.begin();
        }
    }

    bool move(const string& name,shared_ptr<Directory> target){
        if(target->appendChild(this->get(name))){
            this->children.erase(this->children.find(name));
        }
    }

    bool appendChild(shared_ptr<Base> item){
        shared_ptr<Base> element = this->children[item->getName()];
        if(element != nullptr )
            return false;
        else {
            this->children[item->getName()] = item;
            return true;
        }


    }
};


#endif //LAB2_PDS_DIRECTORY_H
