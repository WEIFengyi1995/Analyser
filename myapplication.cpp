#include "myapplication.h"

QThread * MyApplication::t = nullptr;

MyApplication::MyApplication(int &argc,char** argv):
    QApplication(argc,argv)
{
    t = new QThread();
}

QThread * MyApplication::getThread(){
    if(t == nullptr){
        return nullptr;
    }
    else{
        return t;
    }

}
