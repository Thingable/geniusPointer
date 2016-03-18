/**
 * @file    GeniusPtr.h
 *
 * @author  Darrell Henderson
 * @date    3/16/16
 */

#ifndef GENIUSPTR_H
#define GENIUSPTR_H

#include <iostream>
    using std::cout;
    using std::endl;
#include "GeniusPtrArray.h"

class GeniusPtr{
      public:
            GeniusPtr();
            GeniusPtr(int value);
            GeniusPtr(const GeniusPtr &); 
            ~GeniusPtr();
            int sharedCount();
            int& operator* () const;
            int* operator->() const;               
            GeniusPtr& operator=(const int&);
      private:
            int* _ptr;
            static GeniusPtrArray a;
};

GeniusPtrArray GeniusPtr::a;

GeniusPtr::GeniusPtr(){
      cout << "New blank pointer" << endl;
      _ptr = new int;
      
}

GeniusPtr::GeniusPtr(int value){
      cout << "New pointer to: " << value << endl;
      _ptr = new int(value);
}

GeniusPtr::GeniusPtr(const GeniusPtr& ptr){
     cout << "New (copy constructor) pointer to: " << *ptr << endl;
     _ptr = ptr._ptr;
     a.newPtr(_ptr);
}

GeniusPtr::~GeniusPtr(){
      if(a.deletePtr(_ptr)){
            delete _ptr;
      }
      _ptr = nullptr;
}

int GeniusPtr::sharedCount(){
      return a.get_count(_ptr);
}

int& GeniusPtr::operator* () const{
      return *_ptr;
}

int* GeniusPtr::operator->() const{
      return _ptr;
}


#endif