# arrayref
## A C++ class that wraps an array

### Motivation

In C, if you want to pass an array by reference to a function, this is generally done by passing a pointer to the beginning of the array along with a size:

```C
double average(const double* ptr, size_t count);
```

In the C++ Standard Library, the equivalent idiom is to pass a begin iterator and an end iterator:

```C++
template<class Iter>
double average(Iter begin, Iter end);
```

The problem emerges: since there is no single iterator, this has to be a template. This is how the functions in the `<algorithm>` standard include header operate. (For these, it makes sense, since they want to be templates anyway.)

So we could go for this instead:

```C++
double average(const double* begin, const* double end);
```

This will certainly do the job, and in this case would be appropriate. But what if your function looks like this:

```C++
void cross_product(
    const double* vec1_begin, const double* vec1_end,
    const double* vec2_begin, const double* vec2_end,
    double* result_begin, double* result_end);
```

Clearly, having to have two parameters for each array reference every time can become tedious. This is where `class ArrayRef<T>` comes in:

```C++
void cross_product(ArrayRef<const double>& vec1, ArrayRef<const double>& vec2, ArrayRef<double>& result);
```

Calling this function is as easy as:

```C++
const double a[] = { 12., 23., 34. },
             b[] = { .1, .2, .3 };
std::vector<double> xprod;
xprod.resize(3);
cross_product(a, b, xprod);
```

### Const-ness

One thing to watch out for is `ArrayRef`'s behaviour with respect to `const`-ness. If you want a reference to a `const` array, you need to construct an `ArrayRef<const T>`, where `T` is your type; do not be tempted to think that `const ArrayRef<T>` is enough. In fact, whether or not the `ArrayRef<T>` object itself is `const` or not is of no real importance. Think of it this way:

* `ArrayRef<const T>` *is like* `const T*` (sometimes written `T const *`)
* `const ArrayRef<T>` *is like* `T *const`

Accordingly, all member functions of `ArrayRef<T>` are declared `const`.

### Full documentation

Since this class is really quite trivial, a look at the source code should be sufficient. In summary, it exposes an interface somewhat like a `std::vector`.
