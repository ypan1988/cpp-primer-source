#ifndef BLOB_H_
#define BLOB_H_

#include <initializer_list>
#include <string>
#include <vector>

template <typename T> class Blob {
 public:
  typedef T value_type;
  typedef typename std::vector<T>::size_type size_type;

  // constructors
  Blob();
  Blob(std::initializer_list<T> il);

  // number of elements in the Blob
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }

  // add and remove elements
  void push_back(const T &t) { data->push_back(t); }
  void push_back(T &&t) { data->push_back(std::move(t)); }
  void pop_back();

  // element access
  T& back();
  T& operator[](size_type i);

 private:
  std::shared_ptr<std::vector<T>> data;

  // throws msg if data[i] isn't valid
  void check(size_type i, const std::string &msg) const;
};

template <typename T>
Blob<T>::Blob(): data(std::make_shared<std::vector<T>>()) { }

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il):
data(std::make_shared<std::vector<T>>(il)) { }

tenplate <typename T>
void Blob<T>::pop_back()
{
  check(0, "pop_back on empty Blob");
  data->pop_back();
}

template <typename T>
T& Blob<T>::back()
{
  check(0, "back on empty Blob");
  return data->back();
}

template <typename T>
T& Blob<T>::operator[](size_type i)
{
  // if i is too big, check will throw, preventing access to a nonexistent
  // element
  check(i, "subscript out of range");
  return (*data)[i];
}

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
  if (i >= data->size())
    throw std::out_of_range(msg);
}

// BlobPtr throws an exception an attempts to access a nonexistent element
template <typename T> class BlobPtr
{
 public:
 BlobPtr(): curr(0) { }
 BlobPtr(Blob<T> &a, size_t sz = 0): wptr(a.data), curr(sz) { }

  T& operator*() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];		// (*p) is the vector to which this object points
  }

  // increment and decrement
  BlobPtr& operator++();	// prefix operators
  BlobPtr& operator--();
  BlobPtr operator++(int);	// postfix operators
  BlobPtr operator--(int);

 private:
  // check returns a shared_ptr to the vector if the check succeeds
  std::shared_ptr<std::vecotr<T>>
    check(size::size_t, const std::string &msg) const;
  // store a weak_ptr, which means the underlying vector might be destroyed
  std::weak_ptr<std::vector<T>> wptr;
  std::size_t curr;		// current position within the array
};

// prefix: return a reference to the incremented/decremented object
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++()
{
  // if curr already points past the end of the container, can't increment it
  check(curr, "increment past end of BlobPtr");
  ++curr;			// advance the current state
  return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--()
{
  // if curr is zero, decrementing it will yield an invalid subscript
  --curr;			// move the current state back one element
  check(-1, "decrement past begin of BlobPtr");
  return *this;
}

// postfix: increment/decrement the object but return the unchanged value
template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
  // no check needed here; the call to prefix increment will do the check
  BlobPtr ret = *this;		// save the current value
  ++*this;			// advance one element; prefix ++ checks the increment
  return ret;			// return the saved state
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
  // no check needed here; the call to prefix decrement will do the check
  BlobPtr ret = *this;		// save the current value
  --*this;			// move backward one element; prefix -- checks the increment
  return ret;			// return the saved state
}

#endif // BLOB_H_
