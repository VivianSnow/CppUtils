#include <iostream>
using namespace std;

template <typename T>
class SmartPointer final{

protected:
    class U_Ptr{
    public:
        T *ptr;
        size_t count;
        U_Ptr(T* ptr): ptr(ptr), count(1){

        }

        ~U_Ptr(){
            delete (ptr);
        }
    };
    U_Ptr *p;

public:
    SmartPointer(T *_ptr): p(new U_Ptr(_ptr)){
    }

    SmartPointer(SmartPointer &another){
        cout << "Copy constructed fun called " << endl;
        p = another.p;
        p->count++;
    }

    SmartPointer& operator=(const SmartPointer& right){
        if (--(this->p->count) == 0) {
            delete (this->p);
        }
        this->p = right.p;
        this->p->count++;
        return *this;
    }

    T operator*(){
        return *(p->ptr);
    }

    T* operator->(){
        return p->ptr;
    }

    ~SmartPointer(){
        if(--p->count == 0){
            delete p;
        }
    }

};


struct A{
    int x;
    double y;
    A(int _x, double _y) : x(_x), y(_y){
    }
};


int main() {
    SmartPointer<A> p(new A(1, 2.0));
    auto p2(p);
    cout << (*p).x << endl;
    cout << p2->y << endl;
    SmartPointer<A> p3(new A(0, 0));
    p = p3;
    p2 = p3;
    return 0;
}
