#include <iostream>
using namespace std;

class Stack {
  public:
    Stack(int size = 1000) : msize(size), mtop(0) {
        cout << "Stack(int)" << endl;
        mpstack = new int[size];
    }

    ~Stack() {
        cout << "~Stack()" << endl;
        delete[] mpstack;
        mpstack = nullptr;
    }

    Stack(const Stack &src) : msize(src.msize), mtop(src.mtop) {
        cout << "Stack(const Stack&)" << endl;
        mpstack = new int[src.msize];
        for (int i = 0; i < mtop; ++i) {
            mpstack[i] = src.mpstack[i];
        }
    }

    Stack(Stack &&src) : msize(src.msize), mtop(src.mtop) {
        cout << "Stack(Stack&&)" << endl;

        mpstack = src.mpstack;
        src.mpstack = nullptr;
    }

    Stack &operator=(const Stack &src) {
        cout << "operator=" << endl;
        if (this == &src)
            return *this;

        delete[] mpstack;

        msize = src.msize;
        mtop = src.mtop;
        mpstack = new int[src.msize];
        for (int i = 0; i < mtop; ++i) {
            mpstack[i] = src.mpstack[i];
        }
        return *this;
    }

    Stack &operator=(Stack &&src) {
        cout << "operator=(Stack&&)" << endl;

        if (this == &src)
            return *this;

        delete[] mpstack;

        msize = src.msize;
        mtop = src.mtop;

        mpstack = src.mpstack;
        src.mpstack = nullptr;

        return *this;
    }

    int getSize() { return msize; }

  private:
    int *mpstack;
    int mtop;
    int msize;
};

Stack GetStack(Stack &stack) {
    Stack tmp(stack.getSize());
    return tmp;
}

int main() {
    Stack s;
    s = GetStack(s);
    return 0;
}
