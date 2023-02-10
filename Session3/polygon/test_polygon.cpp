#include "polygon.hpp"
#include <iostream>
#include <vector>

/**
 * Code to test the understanding of special member functions and references.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

polygon polygon_factory(size_t count){ return polygon(count); }

void draw_value(polygon) { std::cout << "passed-by-value\n"; }
void draw(const polygon&) { std::cout << "passed-by-const-reference\n"; }
void draw(polygon&) { std::cout << "passed-by-lvalue-reference\n"; }
void draw(polygon&&) { std::cout << "passed-by-rvalue-reference\n"; }

int main()
{
    std::string ruler(40, '-');
    // Replace "???" with your predictions: what gets printed after each line?
    //       Note that some statements may print more than one line.
    // After all "???" are gone, step through the program in debugger and check your answers against output.
    // Answer the additional questions below.
    {   // for example:
        std::cout << ruler << std::endl;
        polygon poly;
        // default-constructor
        // destructor
    }
    {
        std::cout << ruler << std::endl;
        polygon poly(1);
        // custom-constructor(1)
        // destructor
    }
    {
        std::cout << ruler << std::endl;
        // polygon poly = 1; // no longer possible after marking the custom constructor as explicit
        // custom-constructor(1)
        // destructor
    }
    {
        std::cout << ruler << std::endl;
        const polygon poly0;
        // default-constructor

        std::cout << ruler << std::endl;
        polygon poly1 = poly0;
        // copy-constructor

        std::cout << ruler << std::endl;
        polygon poly2 = polygon(2);
        // custom-constructor(2)

        std::cout << ruler << std::endl;
        polygon poly3{{1,2},{3,4},{5,6},{7,8}};
        // custom-constructor{point{1,2},point{3,4},point{5,6},point{7,8}}

        std::cout << ruler << std::endl;
        poly2 = poly1;
        // copy-assignment

        std::cout << ruler << std::endl;
        poly2 = polygon_factory(3);
        // custom-constructor(3)
        // move-assignment
        // destructor

        std::cout << ruler << std::endl;
        draw_value(poly0);
        // copy-constructor
        // passed-by-value
        // destructor

        std::cout << ruler << std::endl;
        draw(poly0);
        // passed by const reference

        std::cout << ruler << std::endl;
        draw(poly1);
        // passed by lvalue reference

        std::cout << ruler << std::endl;
        draw(polygon_factory(4));
        // custom-constructor(4)
        // passed-by-rvalue-reference
        // destructor

        std::cout << ruler << std::endl;
        std::vector<polygon> polies(4, poly3);
        // copy-constructor
        // copy-constructor
        // copy-constructor
        // copy-constructor

        std::cout << polies.capacity() << std::endl;
        std::cout << ruler << std::endl;
        polies.push_back(poly3);
        // Why are so many operations here?
        // This happens because the initial capacity of the vector is 4, and all 4 slots are used.
        // So when we push a new polygon into the vector, it needs to reallocate memory. Basically, it increases its
        // capacity to 8 by allocating a new buffer and moving all the existing items into this new buffer.

        std::cout << ruler << std::endl;
        polies.push_back(poly3);
        // Why is the number of operations fewer here than for the above one?
        // Because the capacity is now 8 instead of 4, it does not need to reallocate any memory, so it simply copies
        // the polygon into the vector.

        std::cout << ruler << std::endl;

        for (polygon p : polies)
            std::cout << p << " at " << &p << '\n';
        // copy-constructor
        // point x at address
        // destructor
        // Can we make the loop above more efficient?
        // This is an incredibly common mistake, make sure to fix it, or ask.

        // The above loop is super in-efficient because it calls the copy-constructor and destructor in each iteration.
        // Using const auto &p reference instead fixes this:
        std::cout << ruler << std::endl;
        for (const auto &p: polies)
            std::cout << p << " at " << &p << '\n';
    }
    {
        std::cout << ruler << std::endl;
        // draw(1);
        // custom constructor(1)
        // passed-by-rvalue-reference
        // destructor
        
        // What is going on here? Why "1" is treated as polygon? This is unlikely to be intentional.
        // Can we forbid the last statement without breaking the previous code?
        // Fix it in polygon.hpp so that this line does not compile.
        
        // I fixed it by adding the "explicit" keyword in front of the custom constructor.
        // This makes it so implicit conversions do not occur.
        // Now it no longer compiles.
    }
    {
        std::cout << ruler << std::endl;
        polygon poly = polygon(2);
        std::cout << poly << " at " << &poly << std::endl;
        draw_value(std::move(poly));
        // passed-by-value        
        
        std::cout << poly << " at " << &poly << std::endl;
        // What was inside poly before draw_value call?
        // Before the draw_value call, we had a polygon with 2 points: (0, 0) and (0, 0).
        
        // What is inside poly after draw_value call? Why?
        // We created a new polygon by calling the move-constructor (using std::move), which also causes the original 
        // to become empty (since it swaps values and its default values are 0 and nullptr).
        // Finally, this new polygon is passed by value into draw_value, and is then destroyed with the destructor
        // since it goes out of scope immediately.
        // Now we're left with an empty polygon, which goes out of scope and its destructor is also called.
    }
    {
        std::cout << ruler << std::endl;
        polygon poly = polygon(2);
        std::cout << poly << " at " << &poly << std::endl;
        draw(std::move(poly));
        // passed-by-rvalue-reference
        
        std::cout << poly << " at " << &poly << std::endl;
        // What was inside poly before draw call?
        // Before the draw call, we had a polygon with 2 points: (0, 0) and (0, 0).
        
        // What is inside poly after draw call? Why?
        // std::move casts poly to an rvalue reference, which causes it to call the draw(polygon&&) method.
        // After the call, we can't really say for sure what is inside poly (since it was moved to another scope!),
        // and trying to use it afterwards is bad practice. But since draw() doesn't change any of the values in poly,
        // nothing changes after the draw call.
    }
    std::cout << ruler << ruler << std::endl;
}
