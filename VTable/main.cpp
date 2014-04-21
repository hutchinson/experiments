#include <iostream>
#include <cstring>

typedef void (*func_ptr)();

class A
{
public:
  int a;
  int b;
  void func()
  {
    std::cout << "A::func() " << a << " " << b << std::endl;
  }
};

struct FakeVTable
{
  func_ptr func;
};

void multiplePersonality()
{
  std::cout << "multiplePersonaility!!" << std::endl;
}

class B
{
public:
  int a;
  int b;

  virtual void func()
  {
    std::cout << "B::func() " << a << " " << b << std::endl;
  }

};

int main(int argc, char **argv)
{
  std::cout << "main()" << std::endl;
  
  struct FakeVTable fakeVTable;
  fakeVTable.func = multiplePersonality;
  void *vtable_ptr = &fakeVTable;

  A *a = new A();
  B *b = new B();
  
  a->a = 1;
  a->b = 2;
  a->func();

  memset(a, 0, sizeof(A));
  a->func();

  b->a = 1;
  b->b = 2;
  b->func();

  memset(b, 0, sizeof(B));
  memcpy(b, &vtable_ptr, sizeof(void*));
  b->func();

  return 0;
}
