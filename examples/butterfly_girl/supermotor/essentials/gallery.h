// Removing elements not planned for a while
// (will be implemented in the future,
//  but it's just not an immediate priority for me rn... e.e)




// #include <cstdint.h>     // Includes uintN_t datatypes (I THINK dafsfhdsjg)
#include <stdint.h>     // Includes uintN_t datatypes (I THINK dafsfhdsjg)




// Specifies the Gallery interface.


template <class T>
class Gallery {

    public:
        Gallery(uint32_t size = 100);
        T& getPrev(T&);
        T& getNext(T&); 
        uint32_t getSize(); 

    private:
        uint32_t size;
        T previous;
        T next; 
};






// Implements the Gallery interface.
// You would usually have this in a .cpp file,
// but I'd rather do a "header-only game engine",
// so there goes that design choice of mine...

// Q: What is an interface?
// A: An interface is a "class of classes", kind of.
//    Think of polymorphism or operator overloading, for example
//    (actually, a C++ template is kind of an operator overloading generator [Aguilar, 2006]).

// Q: What is a Gallery?
// A: A Gallery is an ADT (a fancy word that means: I made it up :3)
//    It will be like a "circle":
//    Imagine you have for example a gallery of 3 items:
//       Item 1:
//         prev: Item 3
//         next: Item 2
//       Item 2:
//         prev: Item 1
//         next: Item 3
//       Item 3:
//         prev: Item 2
//         next: Item 1
//
//
//      This should allow us (and you!)
//      to implement grids, image galleries, etc. :3
//      (think of Pureya's menus, for example).


// Constructor.
// .
// You can have uint64_t instead if
// (for whatever absolutely MACABRE reason...)
// you need a bigger Gallery.
template <class T>
Gallery <T> :: Gallery (uint32_t this_size)     // Java who? :p
{
    size = this_size;
}


template <class T>
T& Gallery <T> :: getPrev(T& currentElement)
{
    return &getPrev();      // "Prev" stands for "previous" (duh...)
}


template <class T>
T& Gallery <T> :: getNext(T& currentElement)
{
    return &getNext();
}
