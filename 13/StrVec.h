class StrVec {
public:
    StrVec(): // the allocator member is default initialized
      elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec&);             // copy construct
    StrVec& operator=(const StrVec&);  // copy assignment
    ~StrVec();                         // destructor
    void push_back(const std::string&);  // copy the element
    size_t size() const { return first_free - element; }
    size_t capacity() const { return cap - element; }
    std::string *begin() const { return element; }
    std::string *end() const { return first_free; }

private:
    std::allocator<std::string> alloc;  // allocates the elements
    
    // used by functions that add elements to StrVec
    void chk_n_alloc() { 
      if(size() == capacity()) reallocate();
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