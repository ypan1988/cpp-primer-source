#ifndef STRVEC_H_
#define STRVEC_H_

#include <string>
#include <utility>
#include <memory>

class StrVec {
public:
    StrVec() : // the allocator member is default initialized
        elements(nullptr), first_free(nullptr), cap(nullptr) {}

    StrVec(const StrVec&);                // copy construct
    StrVec& operator=(const StrVec&);     // copy assignment

    StrVec(StrVec&&) noexcept;            // move construct
    StrVec& operator=(StrVec&&) noexcept; // move assignment

    ~StrVec();                            // destructor

    void push_back(const std::string&);   // copy the element
    void push_back(std::string&&);        // move the element

    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }

private:
    std::allocator<std::string> alloc;  // allocates the elements

    // used by functions that add elements to StrVec
    void chk_n_alloc() {
        if (size() == capacity()) reallocate();
    }

    // utilities used by the copy construct, assignment operator and destructor
    std::pair<std::string*, std::string*> alloc_n_copy
    (const std::string*, const std::string*);

    void free();              // destroy the elements and free the space
    void reallocate();        // get more space and copy the existing elements

    std::string *elements;    // pointer to the first element in the array
    std::string *first_free;  // pointer to the first free element in the array
    std::string *cap;         // pointer to one past the end of the array
};

inline
StrVec::StrVec(const StrVec &s)
{
    // call alloc_n_copy to allocate exactly as many elements as in s
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

inline
StrVec& StrVec::operator=(const StrVec &rhs)
{
    // call alloc_n_copy to allocate exactly as many elements as in rhs
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = data.second;
    return *this;
}

inline
StrVec::StrVec(StrVec &&s) noexcept  // move won't throw any exceptions
// member initializer take over the resource in s
    : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    // leave s in a state in which it is safe to run the destructor
    s.elements = s.first_free = s.cap = nullptr;
}

inline
StrVec& StrVec::operator=(StrVec &&rhs) noexcept
{
    // direct test for self-assignment
    if (this != &rhs) {
        free();
        elements = rhs.elements;      // free existing element
        first_free = rhs.first_free;  // take over resources from rhs
        cap = rhs.cap;
        // leave rhs in a destructible state
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

inline
StrVec::~StrVec() { free(); }

inline
void StrVec::push_back(const std::string &s)
{
    chk_n_alloc();  // ensure that there is room for another element
    // construct a copy of s in the element to which first_free point
    alloc.construct(first_free++, s);
}

inline
void StrVec::push_back(std::string &&s)
{
    chk_n_alloc();  // reallocates the StrVec if necessary
    alloc.construct(first_free++, std::move(s));
}

inline
std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
    // allocate space to hold as many elements as are in the range
    auto data = alloc.allocate(e - b);
    // initialize and return a pair constructed from data and
    // the value returned by unintialized_copy
    return { data, uninitialized_copy(b, e, data) };
}

inline
void StrVec::free()
{
    // may not pass deallocate a 0 pointer; if elements is 0, there's no work to do
    if (elements) {
        // destroy the old elements in reverse order
        for (auto p = first_free; p != elements; /* empty */)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

inline
void StrVec::reallocate()
{
    // we'll allocate space for twice as many elements as the current size
    auto newcapacity = size() ? 2 * size() : 1;
    // allocate new memory
    auto newdata = alloc.allocate(newcapacity);
    // move the data from the old memory to the new
    auto dest = newdata;  // points to the next free position in the new array
    auto elem = elements; // points to the next element in the old array
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();  // free the old space once we've moved the elements
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

#endif
