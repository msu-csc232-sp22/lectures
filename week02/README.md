# Lecture: C++ Classes

A repository that covers a review of C++ classes.

*Note: The contents of this README is taken directly (with slight modifications) from Data Structures and Algorithm Analysis in C++, Fourth Edition by Mark Allen Weiss, Section 1.4, C++ Classes, pp 12-21, (c) 2014 Pearson Education, Inc. ISBN-13: 978-0-13-284737-7.*

## C++ Classes

In this course, we will write many data structures. All of the data structures will be objects that store data (usually a collection of identically typed items) and will provide functions that manipulate the collection. In C++ (and other languages), this is accomplished by using a *class*. This lecture describes the C++ class.

### Basic `class` Syntax

A class in C++ consists of its **members**. These members can be either data or functions. The functions are called **member functions**. Each instance of a class is an *object*. Each object contains the data components specified in the class (unless the data components are `static`, a detail that can be safely ignored for now). A member function is used to act on an object. Often member functions are called **methods**.

As an example, a complete declaration of `IntCell` class is found in a file named [int_cell_inline.cpp](./src/int_cell_inline.cpp) in this repository. In the `IntCell` class, each instance of the `IntCell` -- an `IntCell` object -- contains a single data member named `storedValue`. Everything else in this particular class is a method. In our example, there are four methods. Two of these methods are `read` and `write`. The other two are special methods known as constructors. Let us describe some key features.

First, notice the two labels `public` and `private`. These labels determine visibility of class members. In this example, everything except the `storedValue` data member is `public`. The data member `storedValue` is `private`. A member that is `public` may be accessed by any method in any class. A member that is `private` may only be accessed by method in its class. Typically, data members are declared `private`, thus restricting access to internal details of the class, while methods intended for general use are made `public`. This is known as `information hiding`. By using `private` data members, we can change the internal representation of the object without having an effect on other parts of the program that use the object. This is because the object is accessed through the `public` member functions whose viewable behavior remains unchanged. The users of the class do not need to know internal details of how the class is implemented. In many cases, having this access leads to trouble. For instance, in a class that stores dates using month, day, and year, by making the month, day and year `private`, we prohibit an outsider from setting these data members to illegal dates, such as Feb 29, 2019. However, some methods may be for internal use and can be `private`. In a class, all members are `private` by default, so the initial `public` is not optional.

Second, we see two **constructors**. A constructor is a method that describes how an instance of the class is constructed. If no constructor is explicitly defined, one that initializes the data members using language defaults is automatically generated. The `IntCell` class defines two constructors. The first is called if no parameter is specified. The second is called if an `int` parameter is provided, and uses that `int` to initialize the `storedValue` member.

#### Extra Constructor Syntax and Accessors

Although the class works as written, there is some extra syntax that makes for better code. Four changes are shown in a file named [int_cell_inline_improved.cpp](./src/int_cell_inline_improved.cpp) found in this repository.

The differences are as follows:

#### Default Parameters

The `IntCell` constructor illustrates the `default parameter`. As a result, there are still two `IntCell` constructors defined. One accepts an `initialValue`. The other is the zero-parameter constructor, which is implied because the one-parameter constructor says that `initialValue` is optional. Default parameters can be used in any function, but they are more commonly used in constructors.

#### Initialization List

The `IntCell` constructor uses an **initialization list** prior to the body of the constructor. The initialization list is used to initialize the data members directly. While not much different that the original definition, using the initialization list instead of an assignment statement in the body saves time in the case where the data members are class types that have complex initializations. In some cases it is required. For instance, if a data member is `const` (meaning that it is not changeable after the object has been constructed), then the data member's value can only be initialized in the initialization list. Also, if a data member is itself a class type that does not have a zero-parameter constructor, then it must be initialized in the initialization list.

Let's take a closer look at the initialization list and the syntax employed. We see the use of curly braces

```c++
    : storedValue{ initialValue }
```

instead of the traditional use of parentheses

```c++
    : storedValue( initialValue )
```

The use of braces instead of parentheses is new in C++ 11 and is part of a larger effort to provide a uniform syntax for initialization everywhere. Generally speaking, anywhere you can initialize, you can do so by enclosing initializations in curly braces (though there is one important exception discussed later related to vectors).

#### `explicit` Constructor

The `IntCell` constructor is `explicit`. You should make all one-parameter constructors `explicit` to avoid behind-the-scenes type conversions. Otherwise, there are somewhat lenient rules that will allow type conversions without explicit casting operations. Usually, this is unwanted behavior that destroys strong typing and can lead to hard-to-find bugs. As an example, consider the following:

```c++
IntCell obj; // obj is an IntCell
obj = 37;    // should not compile: type mismatch
```

The code fragment above constructs an `IntCell` object `obj1` and then performs an assignment statement. But the assignment statement *should* not work, because the right-hand side of the assignment operator is not another `IntCell`. `obj`'s `write` method should have been used instead. However, C++ has lenient rules. Normally, a one-parameter constructor defines an **implicit type conversion**, in which a temporary object is created that makes an assignment (or parameter to a function) compatible. In this case, the compiler would attempt to convert

```c++
obj = 37;    // should not compile: type mismatch
```

into

```c++
IntCell temporary = 37;
obj = temporary;
```

Notice that the construction of the temporary can be performed by using the one-parameter constructor. The use of `explicit` means that a one-parameter constructor cannot be used to generate an implicit temporary. Thus, since `IntCell`'s constructor is declared `explicit`, the compiler will correctly complain that there is a type mismatch.

#### Constant Member Function

A member function that examines but does not change the state of its object is an **accessor**. A member function that changes the state is a **mutator** (because it mutates the state of the object). In the typical collection class, for instance, `isEmpty` is an accessor, while `makeEmpty` is a mutator.

In C++, we can mark each member function as being an accessor or a mutator. Doing so is an important part of the design process and should not be viewed as simply a comment. Indeed, there are important semantic consequences. For instance, mutators cannot be applied to constant objects. By default, all member functions are mutators. To make a member function an accessor, we must add the keyword `const` after the closing parentheses that ends the parameter type list. The const-ness is part of the signature. `const` can be used with many different meanings. The function declaration can have `const` in three different contexts. Only the `const` after a closing parenthesis signifies an accessor. Other uses will be described in a future lecture.

In the `IntCell` class, `read` is clearly an accessor; it does not change the state of the `IntCell`. Thus, it is made a constant member function. If a member function is marked as an accessor but has an implementation that changes the value of any data member, a compiler error is generated. (Note: Data members *can* be mared `mutable` to indicate that the const-ness should not apply to them.)

### Separation of Interface and Implementation

The class in [int_cell_inline_improved.cpp](./src/int_cell_inline_improved.cpp) contains all the correct syntatic constructs. However, in C++ it is more common to separate the class interface from its implementation. The interface lists the class and its members (data and functions). The implementation provides implementations of the functions.

The file [int_cell.h](./src/int_cell.h) shows the class interface for `IntCell` and the file [int_cell.cpp](./src/int_cell.cpp) shows the implementation and the file [test_int_cell.cpp](./src/test_int_cell.cpp) shows a `main` routine that uses the `IntCell`. Some important points follow.

#### Preprocessor Commands

The interface is typically placed in a file that ends in `.h`. Source code that requires knowledge of the interface must `#include` the interface file. In our case, this is both the implementation file and the file that contains `main`. Occassionally, a complicated project will have files including other files, and there is the danger that an interface might be read twice in the course of compiling a file. This can be illegal. To guard against this, each header file uses the preprocessor to define a symbol when the class interface is read. This is shown on the first two lines of [int_cell.h](./src/int_cell.h). The symbol name, `CSC232_INTCELL_H`, should not appear in any other file; usually we construct it from the file name. The first line of the interface file tests whether the symbol is undefined. If so, we can process the file. Otherwise, we do not process the file (by skipping to the `#endif`), because we know that we have already read the file.

#### Scope Resolution Operator

In the implemenation file, which typically ends in `.cpp`, `.cc`, or `.C`, each member function must identify the class that it is a part of. Otherwise, it would be assumed that the function is in global scope (and zillions or errors would result). The syntax is `ClassName::member`. The `::` is called the **scope resolution operator**.

#### Signatures Must Match Exactly

The signature of an implemented member function must match exactly the signature listed in the class interface. Recall that whether a member function is an accessor (via the `const` at the end) or a mutator is part of the signature. Thus, an error would result if, for example, the `const` was omitted from exactly on of the `read` signatures in [int_cell.h](./src/int_cell.h) and [int_cell.cpp](./src/int_cell.cpp). Note that default parameters are specified in the interface only. They are omitted in the implemenation.

#### Objects Are Declared Like Primitive Types

In classic C++, an object is declared just like a primitive type. Thus the following are legal declarations of an `IntCell` object:

```c++
IntCell obj1;       // Zero parameter constructor
IntCell obj2( 12 ); // One parameter constructor
```

On the other hand, the following are incorrect:

```c++
IntCell obj3 = 37; // Constructor is explicit
IntCell obj4();    // Function declaration
```

The declaration of `obj3` is illegal beause the one-parameter constructor is `explicit`. It would be legal otherwise. (In other words, in classic C++ a declaration that uses the one-parameter constructor must use the parentheses to signify the initial value.) The declaration for `obj4` states that it is a function (defined elsewhere) that takes no parameters and returns an `IntCell`.

The confusion of `obj4` is one reason for the uniform initialization syntax using braces. It was ugly that initializing with zero parameter in a constructor initialization list would require paretheses with no parameter, but the same syntax would be illegal elsewhere (for `obj4`). In C++ 11, we can instead write:

```c++
IntCell obj1;       // Zero-parameter constructor, same as before
IntCell obj2{ 12 }; // One-parameter constructor, same as before
IntCell obj4{ };    // Zero-parameter constructor
```

The declaration of `obj4` is nicer because initialization with a zero-parameter constructor is no longer a special syntax case; the initialization style is uniform.

### `vector` and `string`

The C++ standard defines two classes: the `vector` and `string` is intended to replace the built-in C++ array which causes no end of trouble. The problem with the built-in C++ array is that it does not behave like a first-class object. For instance, built-in arrays cannot be copied with `=`, a built-in array does not remember how many items it can store, and its indexing operator does not check that the index is valid. The built-in string is simply an array of characters, and thus has the liabilities of arrays plus a few more.  For instance, `==` does not correctly compare two built-in strings.

The `vector` and `string` classes in the STL treat arrays and strings as first-class objects. A `vector` knows how large it is. Two `string` objects can be compared with `==`, `<`, and so on. Both `vector` and `string` can be copied with `=`. If possible, you should avoid using the built-in C++ array and string.

`vector` and `string` are easy to use. The code in [vector_example.cpp](./src/vector_example.cpp) creates a `vector` that stores one hundred perfect squares and outputs them. Notice that `size` is a method that returns the size of the `vector`. A nice feature of the `vector` is that it is easy to change its size. In many cases, the initial size is 0 and the `vector` grows as needed.

C++ has long allowed initialization of built-in C++ arrays::

```c++
int daysInMonth[ ] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
```

It was annoying that this syntax was not legal for `vector`s. In older C++, `vector`s were either initialized with size 0 or possibly by a specified size. So, for instance, we would write:

```c++
vector<int> daysInMonth( 12 ); // No {} before C++11
daysInMonth[ 0 ] = 31; daysInMonth[ 1 ] = 28; daysInMonth[ 2 ] = 31;
daysInMonth[ 3 ] = 30; daysInMonth[ 4 ] = 31; daysInMonth[ 5 ] = 30;
daysInMonth[ 6 ] = 31; daysInMonth[ 7 ] = 31; daysInMonth[ 8 ] = 30;
daysInMonth[ 9 ] = 31; daysInMonth[ 10 ] = 30; daysInMonth[ 11 ] = 31;
```

Certainly this leaves something to be desired. C++11 fixes this problem and allows:

```c++
vector<int> daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
```

Requiring the `=` in the initialization violates the spirit of uniform initialization, since now we would have to remember when it would be appropriate to use `=`. Consequently, C++11 also allows (and some prefer):

```c++
vector<int> daysInMonth { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
```

With syntax, however, comes ambiguity, as one sees with the declaration

```c++
vector<int> daysInMonth { 12 };
```

Is this a `vector` of size 12, or is it a `vector` of size 1 with a single element 12 in position 0? C++11 gives precedence to the initializer list, so in fact this is a `vector` of size 1 with a single element 12 in position 0, and if the intention is to initialize a `vector` of size 12, the old C++ syntax using parentheses must be used:

```c++
vector<int> daysInMonth( 12 ); // Must use () to call constructor that takes size
```

`string` is also easy to use and has all the relational and equality operators to compare the states of two strings. Thus `str1 == str2` is `true` if the values of the strings are the same. It also has a `length` method that returns the string length.

Looking again at [vector_example.cpp](./src/vector_example.cpp), the basic operation on arrays is indexing with `[]`. Thus, the sum of the squares can be computed as:

```c++
int sum { 0 };
for( int i = 0; i < squares.size( ); ++i )
{
    sum += squares[ i ];
}
```

The pattern of accessing every element sequently in a collection such as an array or a `vector` is fundamental, and using array indexing for this purpose does not clearly express the idiom. C++11 adds a **range** `for` syntax for this purpose. The above fragment can be written instead as:

```c++
int sum { 0 };
for( int x : squares ) 
{
    sum += x;
}
```

In many cases, the declaration of the type in the range `for` statement is unneeded; if `squares` is a `vector<int>`, it is obvious that `x` is intended to be an `int`. Thus C++11 also allows the use of the reserved word `auto` to signify that the compiler will automatically infer the appropriate type:

```c++
int sum { 0 };
for( auto x : squares ) 
{
    sum += x;
}
```
