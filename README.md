### SSAD
**The C++ language + Design patterns**

#### lectures 7, 8 - Introduction to C++ Templates
* recommended books:
  * C++ Templates The Complete Guide david Vandevoorde, Nicolai M. Josuttis first, second editions
  * **into to C++ templates**
    * like generics in other languages
    * Set <= abstraction <= List => specialization => Ordered list
    * 
    ```
    int Max (int a, int b) {
      return a > b ? : a : b;
    }


    // funcion template

    temlate < typename T >                //Template header
    T Max (T a, T b) {                    // T - Template type parameter
      return a > b ? a : b;               // Template body
    }

    double x, y, res;
    ...
    res = Max(x-1, y+2.5);
    ```
    * template instantiation, invocation
    * compiler generates function with a "mangled" name and compiler-generated function call is produced. All behin the scene
    * compiler uses the same function instantion for the same typenames
    * for 2 different typenames (e.g double, int). compiler generates Max_double, Max_int
    ```
    class C {
      int m;
      public:
        C() : m(0) { }

        bool operator>(C& c) {          // Now Max() works properly
          return m > c.m;
        }
    };

    C c1, c2;
    Max(c1, c2);
    ```
    * **Concepts**
    ```
    template < typename T >             // Concepts decalrtion states that objects of some type T can
    concept GreaterThan =               // be compares using '>' and the result is bool
      requires(T x, T y) { { x > y } -> bool; }


    temlate < typename T > requires GreaterThan<T>
    T Max (T a, T b) {
      return a > b ? a : b;
    }
    ```
    * Stack generic
    ```
    template < typename T >
    class Stack {
      int top;
      T S[100];                           // size is restricted

      public:
        Stack() : top(-1) { }

        void push (T V) { S[++top] = v; } // invoking copy constructor of
                                          // V and assignment operators might be costly
                                          // T should suppport copy constructor and = operation
                                        
        void push (T& V) { S[++top] = v; } // copy constructor of T is not invoked
                                          // in industry pass by ref is used
        
        T pop (void) { return S[--top]; }

        T& pop (void) { return S[--top]; } // no copy constructor is invoked
    }


    template < typename T, int N >        // Non-type parameter
    class Stack {
      int top;
      T S[N];

      public:
        Stack() : top(-1) { }
                                        
        void push (T& V) { S[++top] = v; }

        T& pop (void) { return S[--top]; }
    }

    Stack<int, 10> s10int;
    ```
    * class templates is not a type, but a __family of types__
    * function templates is not a function, but a __family of (overloaded) functions
  * **Function & Class Templates**
  * **Template Type & Non-**
  * **Metaprogramming Exmaple**
    * Range types
    ```
    int currentDay, currentMonth;

    currentDay = 70;                      // Non logical, should be range
    currentDay = currentMonth+1;          // semantically incorrect
    ```
    ```
    class RANGE {
      int leftBOrder;
      int rightBorder;
      int vlue;

      RANGE(int v, int l, int r) {
        leftBorder = l;
        rightBorder = r;
        value = v;
      }

      RANGE::RANGE( RANGE &r) {           // copy constructor
        leftBorder = l;
        rightleftBorder = r;
        value = v;
      };
    }
    ```
  * Incomplete Instantiation
    ```
    template < unsigned N, typename T >
    T Power (T v ) {
      T res = v;
      for (int i = 1; i < N; i++) {
        res *= N;
      }

      return res;
    }

    int d1 = Power<5, int>(1.2);          // explicit instantiation - correct
    double d2 = Power<5>(1.2);            // implicit instantiation - correct
    ```
  * FUnction templatesinstantiation kinds
    ```
    template <typename T1, >
    ```
  * Explicit Specializations
    ```
    template <typename T>
    class C {
      public: bool less (T& v1, T& v2) {
        return v1 < v2;
      }
    }

    template <>                           // explicit specialization
    class C<const char*> {
      public: bool less (const char* v1, const char* v2) {
        return strcmp(v1 < v2)<0;
      }
    }

    C<int> c1;
    bool l1 = c1.less(1,2);

    C<double> c2;
    bool l2 = c2.less(1.2, 3.4);

    C<const char*> c3;
    bool 14 = c3.less("abc", "abcx");     // compares 2 strs
    ```
    
    ```
    template <unsigned N >                // calls itself infinite times
    unsigned long Fact (void) {
      if ( N < 2) return 1;
      return N*Fact<N-1>;
    }

    unsigned long f5 = Fact<3>();


    template <unsigned N >                // solves the above problem
    unsigned long Fact (void) {
        if ( N < 2) return 1;
        return N*Fact<N-1>();
    }

    template<>
    unsigned long Fact<1> (void) {
        return 1;
    }

    template<>
    unsigned long Fact<0> (void) {
        return 1;
    }
    ```
  * Partial Specialization
    ```
    template<typename T>                  // for all pointers except const char*
    class C<T*> {
      public: bool less (T* v1, T* v2) { return *v1 < *v2; }
    }
    ```
  * why we need template paprametrize by template
#### lecture 4
* **move constructor**
  * A move constructor enables the resources owned by an rvalue object to be moved into an lvalue without copying
* **move semantics**
  * we dont always want to copy objects - expensive. Instead, we can move them using move semantics.
  ```
  class String {
    public:
      String(const char* string) {

      }
  }
  ```
#### **Value categories in C++**
* expression: `7` of type `int`, `5+2`, `x` if `x` of type int.
* each expression has its value category, which describes how value was formed and how it behaves
* Traditional lvalue, rvalue:
  * historically, there were only 2 categories of types: lvale, rvale. **lvalue** are the expressions that refer to actual values stored in the memory or in a machine registers, such are the expression `x`, where `x` is the name of the variable. **lvalues** are modifiable. `x=7;` value of `x` is updated.
  * **lvalue**: can occur in left-hand side of assignment
    ```
    int const x = 5;        // x is non-modifible lvalue
    x = 7;                  // Error, x must be modifiable lvalue
    ```
      * `*p`, `p->data`, call to functions that return value of "traditional" lvalue reference type declared with `&`
      ```
      int& get(int& i) {
          cout << "i: " << i << endl;
          return i;
      }

      char& g(char& i) {
          cout << "char: " << i << endl;
          return i;
      }

      int i = 10;
      get(i) = 1;
      cout << "i: " << i << endl;

      char ch = 'a';
      g(ch) = 'b';
      cout << "ch: " << ch << endl;

      vector<int> v;
      v.front();                      // lvalue, bc return type is an lvalue reference

      // Output:
      // i: 10
      // i: 1
      // char: a
      // ch: b
      ```
  * **rvalue**: can occur in right-hand side of assignment
  * Later, C++ made possible for **rvalues** to stand on the left-hand side of assignment.
    * those assignments are actually function calls to the appropriate assingment operator of the class rather than "simple" assignments for scalar types. So, they follow (seperate) rules of memeber function calls.
  * due to the changes, lvalue sometimes stands for "localizable value"
  * **lvalue-to-Rvalue** conversions
    * while it is error `Rvalue = Rvalue, 7 = 8`, it is possible that `Lvalue = Lvalue`.
      * because of the implicit lvalue-to-rvalue conversion => by reading from the storage or register associated with the _lvalue_
        * _lvalue_ can be used wherever _rvalue_ expected
        * identifies where in the program the compiler (prior to optimization) may emit a "load" instruction to read a value from memory.
  * any literals (except string) are **rvalues**
  * C++11 + L/Rvalue were not enough to describe the language's behavior. <img title="a title" alt="Alt text" src="./lib/value_categories.png">
  * new 
  * `function(const T& arg) {}` can't change the value of `arg`, but can pass rvalue
  * `fucntion(T& a) {}` can't be called with _Rvalue_
  * Значение **glvalue** — это выражение, вычисление которого определяет идентификатор объекта, битового поля или функции.
  * **Prvalue** — это выражение, вычисление которого инициализирует объект или битовое поле или вычисляет значение операнда оператора в соответствии с контекстом, в котором оно отображается.
    1. any literal which is not string, user defined literal
       1. A literal is some data that's presented directly in the code, rather than indirectly through a variable or function call.
    2. & operator (taking the adress of an expression)
    3. applications of built-in arithmetic operators
    4. a call to a function with a return type that is not a reference type
    5. lambda expressions
  * **Xvalue** — это значение glvalue, обозначающее объект или битовое поле, ресурсы которого можно использовать повторно (обычно потому, что это приближается к концу своего времени существования). Пример. Некоторые типы выражений, включающие ссылки rvalue (8.3.2), дают значения xvalue, такие как вызов функции, возвращаемый типом которой является ссылка rvalue или приведение к типу ссылки rvalue.
    1. a call to a function with a return type that is an rvalue reference to an object type (e.g `std::move()`)
    2. a cast to an rvalue reference to an object type
  * **Lvalue** — это значение glvalue, которое не является xvalue
    * correspond to objects you can refer to, either by name or by following a pointer or lvalue reference
    * A useful heuristic to determine whether an expression is an lvalue is to ask if you can take its address. If you can, it typically is. If you can’t, it’s usually an rvalue.
    1. Выражения, обозначающие переменные или функции
    2. * operator ("pointer indirection == dereferencing")
    3. expression that is just a string literal
    4. a call to a function, which returns _lvalue_
     * Note that rvalue references to function types produce lvalues
  * **Rvalue** — это prvalue или xvalue.
    ```
    class Widget {
    public:
      Widget(Widget&& rhs);    // rhs is an lvalue, though it has
      …                        // an rvalue reference type
    };
    ```
  ```
  class N {
  public:
    N();
    N(N const&) = delete;       // this class is neither copyable …
    N(N&&) = delete;            // … nor movable
  };

  N make_N() {
    return N{};      // Always creates a conceptual temporary prior to C++17.
  }                  // In C++17, no temporary is created at this point.
  auto n = make_N(); // ERROR prior to C++17 because the prvalue needs a
                    // conceptual copy. OK since C++17, because n is
                    // initialized directly from the prvalue.
  ```
  ```
  int&  lvalue();
  int&& xvalue();
  int   prvalue();
  ```
  ```
  int x = 3;  // x here is a variable, not an lvalue. 3 is a prvalue initializing
            // the variable x.
  int y = x;  // x here is an lvalue. The evaluation of that lvalue expression does not
              // produce the value 3, but a designation of an object containing the value 3.
              // That lvalue is then then converted to a prvalue, which is what initializes y.
  ```
  * The distinction between arguments and parameters is important, because parameters are lvalues, but the arguments with which they are initialized may be rvalues or lvalues.

#### tut 3
* namespace and class with static members
    namespace a ways of organizing a code by grouping related identifiers, and avoiding name collisions
    while classes encapsulates the data

* headers
  * what is heder and why used
      * contains declarations of functions (prototypes), variable, classes, constructs
      * to seperate declarations from implementations for maintaining and easier reuse
      * prevent mmultiple function definitions  
        ```
        #ifndef HEADER_NAME
        #define HEADER_NAME
        
        // content of header file

        #endif
        ```
          
  * function overloading, same name, different params. if for the same function name and args but different return vals => compilers error

#### lesson 3 OOP
* **declare**
  * `T v = expresssion;` `T v {expression};`
  * Static semantics of declaration
  * ...
  * Dynamic semantics of devlaration
    * allocate mem for the new obj from stack
    * calculare the expression
    * perform type conversion to **T** if needed
    * store value of expression in **v**
* **create**
  * static and dunamic ways of creating objs
    * `int x = 7;`
  * dynamic way of creting objs
    * `int* p = new int(7);`
    * `new` returns pointer to created obj, obj is in **heap**
    * `new T(expr)`
    * no name for the obj created by **new**
    * lives untill explicit deletion operator or untill the whole program terminates
* **remove**
  * `delete p;` deletes obj p from **heap**
  * `delete` unary operator
* **copy /constructor**
  ```
  class-name ( const class-name & )               // Typical declaration of a copy constructor	
  class-name ( const class-name & ) = default;    // Forcing a copy constructor to be generated by the compiler
  class-name ( const class-name & ) = delete;     // Avoiding implicit generation of the copy constructor
  ```
  * Copy constructor is called whenever an object is initialized from another object of the same type, which includes:
    1. initialization: `T a = b;` or `T a(b);`, where `b` is of type `T`.
    2. function argument passing: `f(a);`, where `a` is of type `T` and `f` is `void f(T t);`
    3. function return: `return a;` inside a function such as `T f()`, where `a` is of type `T`, which has no move constructor.
  ```
  {
    float x1 = 7.7, x2 = 8.8;
    float y = x1; // initialization
    y = x2; // assignment
  }
  ```
  * _declaration vs. assignment_ 
    * declaration adds a new obj, while assignment works with already existing objs
    * consequence 
* **assign**
* **move**
* **convert**
  * `(T) expression;`
* **work with objects of a given type**
  * access:
    * via name for static objs
    * via pointer for dynamically created objs
* **classes**
  * class is the user defined compound type
  ```
  class Pointer {
    double x;
    double y;
  }
  Pointer p1, p2;
  ```
  * in C++ classes can be made very similar to predefined types
  * special member functions
    * constructor**s**
      ```
        class Pointer {
          private:
            double x, y;
          public:
            void Move(double dx, double dy) {
              ...
            }
            Pointer() { // default ctor
              ...
            }
            Pointer(double x, double y) {
              ...
            }
          ...
        }
        Pointer p1; // static
        Pointer p2(1.5); // static
        Pointer* p3 = new Pointer(); // ddynamic

        p1 = p2; //copying objs

        p1.Move(0.5, 0.6);
        p3->Move(0.0, -1.3);
        ```
        * by default everything is **private**
        ````
        class Some {
          int a;
          Some() { a = 0; }                  // default ctor
          Some(int i) {a = i; }              // conversion ctor
          Some(Some& arg) { a = arg.a; }        // copy ctor, create a new obj taking element of old obj
          Some(int i, int j) { a = i + j; }
        }

        Some obj(1); // converison of 1 to type c;

        // Move ctor

        Some c1;            // default ctor
        Some c1 = Some();   // default ctor, new obj created and copied to c1
        Some c1();          // dunction declarartion
        Some c1(1);         // conversion ctor
        Some c1 = 1;        // 1 converts to Some, the new Some obj is copied to c1
        Some c1 = Some(1);  // conv ctor + copy ctor
        Some c1(2);         // converison ctor

        Some c1; c1 = 2;    //
        ````
    * destructor
    * operator function**s**
      ```
      class Point {
        ...

        void moveDia(double v) {
          ...
        }

        // new way, introduce exitsitng += operator to type Point
        void operator+=(double v) {
          x += v; y += v;
        }

        Point&  operator+(Point& p1) {
          return Point(member+p1.memeber)
        }

        int operator()(int p) {             // call operator
          return memeber+p;
        }

        int operator[](int p) {             // indexing operator
          return memeber-p;
        }
      }

      Point p1;
      Point p2(1.4, 4.5);
      Point* p = new Point();

      p1 += 0.5;

      Point sum = p1 + p2;

      int int = sum(1);                     // = sum.operator()(1);
      int dec = sum[3];                     // = sum.operator[](3);
      ```
        * Just use fixed, existing operators (`+, -, *, /, new, delete`), but don't introduce new operators, like `+++`
      ```
      T operator OpSign ( Params ) {
        Actions
      }
      ```
      * redefine any operator from set of all available opertors can be added as a operator function to a user defined type
    * conversion function**s**
      * used to extend number of conversion. Allow of my type to be comverter to other types;
      ```
      class Some {
        int memeber;
        ...
        public :
          C(int p) { 
            member = p;
          }

          operator bool() {                 // conversion function
            return member != 0;
          }
      }
      void f() {
        Some c1;

        if (c1) {                           // if (c1.operator bool())
          do something ...
        }
      }
      ``` 
      * `operator TargetType() { Actions; }`
  
* **structured binding**
  ```
  struct S {...}
  S f();
  const auto [x, y] = f();
  ```


#### lesson 2
* **Object declarations**
  * `int x` declaration
  * **`S T name initializer;`**
    * `S` - storage class specifier `static`
    * `float** c` type of c is pointer to pointer to float
    * `int* f1();` function without params returning pointer to interger
    * `double* a1[10];` array of pointers to doubles
    * **clockwise/spiral rule**
    * `int (*f3) (int);` - pointer to function that accepts one int param and returns integer
    * `double (*a)[10];`
  * `typedef int (*PtrFun) (int); PtrFun a4[10];` alternative is `using PrtFun = int (*) (int); PrtFun a4[10];`
  * `int f (double d, int, float*);` forward declaration, function prototype
  * **auto** - int the past it was part of storage class specifiers like static, extern, register
    * `auto int v2;` same as `int v2;`
    * Now is has a new purpose
    * Now it is a **type specifier**;
      * `auto x = 7;`
      * compiler determines the type of the object being declared = **type deducing** or **type inference**
      * `auto var = some-expression;`
    * `vector<double*>* v = new vector<double*>(77);` rewriting using `auto`
      * `auto v = new vector<double*>(77);`
      * `auto f(auto, auto) { auto; }` :laughing: :laughing: :laughing:
      <img title="a title" alt="Alt text" src="./lib/meme">
* **type conversions**
  * `float v = 777;` no data loss
  * `int i = 5.6;` data loss :x:
  * 1. _implicit conversion_
  * 2. _explicit conversion_
  * 1. _standard conversion_ : `int a[10]` here a is a pointer, _arr => pointer_. `if (z) { ... }` _int => bool_
  * 2. _user defined conversion_
  ```
  void foo (double x) {
    ...
  }
  foo(3.14); //OK
  foo(true); //OK
  foo(3); //OK
  ```
  * **how to restrict?**
  ```
  void foo (double x) { ... }
  void foo (int x) = delete;
  void foo (bool x) = delete;

  foo(3.14); // OK
  foo(true); // Error
  foo(3);    // Error
  ```
  * but above doesn't cover all other possile conversions
  * for any kind of conversion, except one
  ```
  templete<typename T>
  void foo(T) = delete;

  void foo (double x) { ... }

  foo(3.14); // OK
  foo(true); // Error
  foo(3);    // Error
  ```

#### lesson 1
* **Reference type, sysnonym**
  *  `T& r = m;` r becomes synonym to m
  *  `r = 7;` the same as `x = 7;`
  *  `x = 777;` the same as `r = 777;`
  *  `int v = r;` v is 777
  ```
  int v[20];
  void f (double& a) { a += 3.14; }
  int& f (int i) { return v[i]; }
  double d = 7.0;
  
  f(d);  // d has the val of 10.14

  f(3) = 7;  // now the 4th element of the arr v has the falue of 7
  ```
  :x: :x: :x: **call of overloaded ‘f(double&)’ is ambiguous**
  ```
  void f (double& a) {
    cout << "double&" << endl;
    a += 3.14;
    }

    void f (double a) {
        cout << "double" << endl;
        a += 3.14;
    }

    int main() {
        double a = 7.0;
        f(a);
    }
  ```
  * references:
    * no pointers to references
    * no arrs of references
    * no refs to refs
    * no nocstant refs
  * `int* p; int*& rp = p;`
  * `const int rx = 7; int& = x;` both rx, x have val of 7
  * `void f(Class& c);` pass by reference
  * `void f(c);` pass by value
  * no specifig operators on references, bc refs are not objs
* **pointers vs. references**
  * both explicitly declared
  * pointers are objs, occupy mem | refs aren't objs
  * pointer's vals are addresses of objs | refs themselves do not have val
  * pointers can be non-initialized (null pointers) | refs should be initialized; always refer to an obj (no null ref)
  * explicit &, * | no special opers on refs
* **Constant types**
  * in C there are constants, but not constant types
  * `Type`, `const Type` different types, but represent **the same set of values**
  * `const int c = 7;` **value of `c` can't be changed**
  * `int x = const int;`
  * :x: `const int c = int;`
  ```
  int a;
  const int b = 777; // compile-time expression
  a = 5; 
  b = 5; // Error

  const int x = a + b; // run-time expression
  x = 5; // Error
  ```
  ```
  const int x = Expression;
  x = 5;
  float A[x]; // shouldn't be initialized this kind of array, compiler should know arrays size
  ```
* **Constans & Pointers**
  * `T* ptr1;` pointer to an objs of type T
  * `const T* ptr2;` pointer to a constant obj of type T; cannot use ptr2 to modify object pointed to by it
  * `T*const prt3 = &v;` constant pointer to an object of type T, can't modify val of ptr3 (it must be initialized)
  * `const T*const prt4 = &pc;` Constant pointer to a constant object of type T; cannot modify the value of ptr4 (it must be initialized) and cannot use it to modify object pointed to by it
* **Namespaces**
  * way to group a set of related declarations into the single higher-level construct.
  ```
  namespace Subsystem1 {
    class Cl {...}
    int a, b;
    void f() {...}
  }
  ```
  * _namespace-name::name_ => `std::cin`
  * can be extended to several files
  * namespaces can be nested
    ```
    namespace A {
        namespace B {
            ...
        }
    }
    ```
    `A::B::f()` access nested namespace
  * the whole prog. is considered as an **unnamed namespace**
    ```
    int a;
    namespace Subsys {
        int a;
    }
    ...
    int x = Subsys::a;  // access to a from Subsys
    int y = a;  // global a
    int z = ::a;  // global a
    ```
  * all entities of **stdlib** is inside namespace `std`
  * `using namespace namespace-name;`
* **`vector<T> name;`** 
  * access by indexing
  * dynamically changed
  * `vector<int> v4 = {1, 2, 3, 4};`
  * `v4.push_back(5);`
  * `v4.size()`
  * `for (int elem : v4) { sum += elem; }`
  * `for (int elem : v4) { elem *= 10; }` array doesn't change, bc elem is a local vars within loop
  * `for (int& elem : v4) { elem *= 10; }` array will change
  * `for (auto& elem : v4) { elem *= 10; }` no need to specify `elem` type => **type deducing/inference**
  * `v.assign`
  * `v.at`
  * `v.back`
  * `v.begin`
  * `v.capacity`
  * `v.clear`
  * `v.end`
  * `v.erase`
* **`list<int>`**
* **`queue<int>`**
* **`stack<int>`**
* **`list<int>`**