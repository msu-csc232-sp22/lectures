# Lecture: C++ Details (Part 1)

C++ Details, part 1, in which we discuss pointers, lvalues, rvalues, and references.

_Note: The contents of this README is taken directly (with slight modifications) from Data Structures and Algorithm Analysis in C++, Fourth Edition by Mark Allen Weiss, Section 1.5, C++ Classes, pp 21-25, (c) 2014 Pearson Education, Inc. ISBN-13: 978-0-13-284737-7._

## Pointers and Parameter Passing

### Pointers

A **pointer variable** is a variable that stores the address where another object resides. It is the fundamental mechanism used in many data structures. For instance, to store a list of items, we could use a contiguous array, but insertion in the middle of a contiguous array requires relocation of many items. Rather than store the collection in an array, it is common to store each item in a separate, noncontiguous place of memory, which is allocated as the program runs. Along with each object is a link to the next object. This link is a pointer variable, because it stores the memory location of another object. This is the classic linked list discussed later in the semester.

To illustrate the operations that apply to pointers, we reuse our `IntCell` by dynamically allocating memory for one in [IntCellPtr.cpp](src/IntCellPtr.cpp). It must be emphasized that for a simple `IntCell` class, there is no good reason to write the C++ code this way. We do it only to illustrate dynamic memory allocation in a simple context. Later in the semester, we'll see more complicated classes, where this technique is useful and necessary.

#### Declaration

Note the declaration of the pointer variable:

```c++
IntCell *m;
```

The `*` indicates that `m` is a pointer variable; it is allowed to point to an `IntCell` object. The **value** of `m` is the address of the object to which it points. `m` is uninitialized at this point. In C++, no such check is performed to verify that `m` is assigned a value prior to being used (however, several vendors make products that do additional checks, including this one). The use of uninitialized pointers typically crashes programs because they result in access of memory locations that do not exist. In general, it is a good idea to provide an initial value, either by combining declaration and initialization into one line, or by initializing `m` to the `nullptr`:

```c++
IntCell *m = new IntCell{ };
```

or

```c++
IntCell *m = nullptr;
```

#### Dynamic Object Creation

In C++, the `new` operator returns a pointer to the newly created object. In C++ there are several ways to create an object using its zero-parameter constructor. The following would be legal:

```c++
m = new IntCell( ); // OK
m = new IntCell{ }; // C++11 and above
m = new IntCell;    // less explicit, but still valid
```

#### Garbage Collection and `delete`

In some languages, when an object is no longer referenced, it is subject to automatic garbage collection; the programmer does not have to worry about it. C++ does not have garbage collection for these so called "raw pointers." When an object that is _allocated_ by `new` is no longer referenced, the `delete` operation must be applied to the object (through a pointer). Otherwise, the memory that it consumes is lost (until the program terminates). This is known as a **memory leak**. Memory leaks are, unfortunately, common occurrences in many C++ programs. Fortunately, many sources of memory leaks can be automatically removed with care. One important rule is to not use `new` when an **automatic variable** can be used instead. In the previous lecture, the `IntCell` is not allocated by `new` but instead is allocated as a local variable. In that case, the memory for the `IntCell` is automatically reclaimed when the function in which it is declared returns. The `delete` operator is shown in use here:

```c++
delete m;
```

#### Assignment and Comparison of Pointers

Assignment and comparison of pointer variables in C++ is based on the value of the pointer, meaning the memory address that is stores. Thus two pointer variables are equal if they point at the same object. If they point at different objects, the pointer variables are not equal, even if the objects being pointed at are themselves equal. If `lhs` and `rhs` are pointer variables (of compatible types), then `lhs = rhs` makes `lhs` point at the same object to which `rhs` points.

#### Accessing Members of an Object through a Pointer

If a pointer variable points at a class type, then a (visible, i.e., `public`) member of the object being pointed at can be accessed via the `->` operator. This is illustrated thusly:

```c++
m->write( 5 );
std::cout << "Cell contents: " << m->read( ) << std::endl;
```

#### Address-of Operator (`&`)

One important operator is the **address-of operator** `&`. This operator returns the memory location where an object resides and is useful for implementing an alias test that is discussed later.

### Lvalues, Rvalues, and References

In addition to pointer types, C++ defines reference types. One of the major changes in C++11 is the creation of a new reference type, known as an rvalue reference. In order to discuss the rvalue references, and the more usual lvalue reference, we need to discuss the concept of lvalues and rvalues. Note that the precise rules are complex, and we provide a general description rather than focusing on the corner cases that are important in a language specification and for compiler writers.

An **lvalue** is an expression that identifies a non-temporary object. An **rvalue** is an expression that identifies a temporary object or is a value (such as a literal constant) not associated with any object.

As examples, consider the following:

```c++
vector<string> arr( 3 );
const int x = 2;
int y;
// ...
int z = x + y;
string str = "foo";
vector<string> *ptr = &arr;
```

With these declarations, `arr`, `str`, `arr[x]`, `&x` `y`, `z`, `ptr`, `*ptr`, `(*ptr)[x]` are all lvalues. Additionally, `x` is also an lvalue, although it is not a modifiable lvalue. As a general rule, if you have a name for a variable, it is an lvalue, regardless of whether it is modifiable.

For the above declarations, `2`, `"foo"`, `x + y`, `str.substr(0, 1)` are all rvalues. `2` and `"foo"` are rvalues because they are literals. Intuitively, `x + y` is an rvalue because its value is temporary; it is certainly not `x` or `y`, but it is stored somewhere prior to being assigned to `z`. Similar logic applies for `str.substr(0,1)`.

Notice the consequences that there are some cases in which the result of a function call or operator call can be an lvalue (since `*ptr` and `arr[x]` generate lvalues) as does `cin >> x >> y` and others where it can be an rvalue; hence, the language syntax allows a function all or operator overload to specify this in the return type, and this aspect is discussed later on. Intuitively, if the function call computes an expression whose value does not exist prior to the call and does not exist once the call is finished unless it is copied somewhere, it is likely to be an rvalue.

A reference type allows us to define a new name for an existing value. In classic C++, a reference can generally only be a name for an lvalue, since having a reference to a temporary would lead to the ability to access an object that has theoretically been declared as no longer needed, and thus may have had its resources reclaimed for another object. However, in C++11, we can have two types of references: lvalue references and rvalue references.

In C++11, an **lvalue reference** is declared by placing an `&` after some type. An lvalue reference then becomes a synonym (i.e., another name) for the object it references. For instance,

```c++
string str = "hell";
string & rst = str;              // rstr is another name for str
rst += 'o';                      // changes str to "hello"
bool cond = (&str == &rstr);     // true; str and rstr are the same object
string & bad1 = "hello";         // illegal: "hello" is not a modifiable value
string & bad2 = str + "";        // illegal: str+"" is not an lvalue
string & sub = str.substr(0, 4); // illegal: str.substr(0, 4) is not an lvalue
```

In C++11, an **rvalue reference** is declared by placing an `&&` after some type. An rvalue reference has the same characteristics as an lvalue reference except that, unlike an lvalue reference, an rvalue reference can also reference an rvalue (i.e., a temporary). For instance,

```c++
string str = "hell";
string && bad1 = "hello";         // Legal
string && bad2 = str + "";        // Legal
string && sub = str.substr(0, 4); // Legal
```

Whereas lvalue references have several clear uses in C++, the utility of rvalue references is not obvious. Several uses of lvalue refrences will be discussed now; rvalue references are deferred until our discussion on parameter passing.

#### lvalue reference use #1: aliasing complicated names

The simplest use, which we will see later in the semester, is to use a local reference variable solely for the purpose of renaming an object that is known by a complicated expression. The code we will see is similar to the following:

```c++
auto & whichList = theLists[ myhash(x, theLists.size() ) ];
if (find( begin( whichList ), end( whichList), x ) != end( whichList) )
    return false;
whichList.push_back( x );
```

A reference variable is used so that the considerably more complex expression `theLists[myHash(x, theLists.size())] does not have to be written (and then evaluated) four times. Simply writing

```c++
auto whichList = theLists[ myHash(x, theLists.size( ) ) ];
```

would not work; it would create a copy, and the the `push_back` operation on the last line would be applied to the copy, not the original.

#### lvalue references use #2: range `for` loops

 A second use is in the range `for` statement. Suppose we would like to increment by 1 all values in a `vector`. This is easy with a `for` loop:

 ```c++
 for( int i = 0; i < arr.size( ); ++i )
    ++arr[ i ];
````

But of course, a range `for` loop would be more elegant. Unfortunately, the natural code does not work, because `x` assumes a copy of each value in the `vector`.

```c++
for( auto x : arr ) // broken
    ++x;
```

What we really want is for `x` to be another name for each value in the `vector`, which is easy to do if `x` is a reference:

```c++
for(auto & x : arr ) // works
    ++x;
```

#### lvalue references use #3: avoiding a copy

Suppose we have a function `findMax` that returns the largest value in a `vector` or other large collection. Then given a `vector arr`, if we invoke `findMax`, we would naturally write

```c++
auto x = findMax( arr );
```

However, notice that if the `vector` stores large objects, then the result is that `x` will be copy of the largest value in `arr`. If we ned a copy for some reason, that is fine; however, in many instances, we only need the value and will not make any changes to `x`. In such a case, it would be more efficient to declare that `x` is another name for the largest value in `arr`, and hence we would declare `x` to be a reference (`auto` will deduce constness; if `auto` is not used, then typically a non-modifiable reference is explicitly state with `const`):

```c++
auto & x = findMax( arr );
```

Normally, this means that `findMax` would also specify a return type that indicates a reference variable.

This code illustrates two important concpets:

1. Reference variables are often used to avoid copying objects across function-call boundaries (either in the function call or the function return).
1. Syntax is needed in function declarations and returns to enable the passing and returning using references instead of copies.
