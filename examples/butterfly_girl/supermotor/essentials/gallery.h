// Adding/removing elements not planned for a while
// (will be implemented in the future,
//  but it's just not an immediate priority for me rn... e.e)




// #include <cstdint.h>     // Includes uintN_t datatypes (I THINK dafsfhdsjg)
#include <stdint.h>     // Includes uintN_t datatypes (I THINK dafsfhdsjg)




//////////  Specifies the Gallery interface.

// Makes gallery items as a "class inside a class"
/*
class GalleryItem {

    public:
        // GalleryItem();
        T& getPrev(T&);
        T& getNext(T&); 

    private:
        T prev;
        T next; 
};
*/


template <class T>
class Gallery {

    public:
        Gallery(uint32_t size = 100);
        uint32_t getSize(); 
        T GalleryItem;     // Makes gallery items as a "class inside a class"   (Credits to https://stackoverflow.com/a/10250087/30458314)

    private:
        uint32_t size;
};






//////////  Implements the Gallery interface.

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


//    Q: How is this "Gallery" thing implemented here?
//    A: Gallery is a template, and
//       GalleryItem is a class.
//      
//             GalleryItem is kind of a "class inside a class" thing here :3



// Constructor.
// .
// You can have uint64_t instead if
// (for whatever absolutely MACABRE reason...)
// you need a bigger Gallery.
template <class T>
Gallery <T> :: Gallery (uint32_t this_size)     // Java who? :p
{
    size = this_size;
    class GalleryItem
    {
    public:
        T&   getPrev()   { return &getPrev(); }
        T&   getNext()   { return &getNext(); }
    private:
        T    prev;     // "Prev" stands for "previous" (duh...)
        T    next;
    };
}




