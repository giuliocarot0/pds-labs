#include <iostream>
#include "File.h"
#include "Directory.h"


int main() {
    /*File *file1 = new File("file1.txt", 123, 24328472);
    /*File *file2 = new File("file2.txt", 123, 24328472);
    /*File *file3 = new File("file3.txt", 123, 24328472);
    /*File *file4 = new File("file4.txt", 123, 24328472);*/
    Directory *d0 = new Directory("dir0", nullptr);
    string fileName[] = {"file1.txt","file2.txt","file3.txt","file4.txt", "dir1", "dir2","dir3","dir4"};
    d0->addFile( fileName[0], 123);
    d0->addFile( fileName[1], 123);
    d0->addFile( fileName[2], 123);
    d0->addFile( fileName[3], 123);
    Directory* d1 = d0->addDirectory(fileName[4]);
    Directory* d2 = d0->addDirectory(fileName[5]);
    Directory* d3 = d1->addDirectory(fileName[6]);
    d1->addFile( fileName[0], 123);
    d2->addFile( fileName[2], 123);
    d1->addFile( fileName[2], 123);
    d3->addFile( fileName[3], 123);
    //  d0->ls(0);
    // d1->ls(0);
    d1->remove(fileName[6]);
    d0->ls(0);
    d0->move("dir1", d2);
    d0->ls(0);

    /*file1->ls(4);
    file2->ls(4);
    file3->ls(4);
    file4->ls(4);*/

    return 0;
}
