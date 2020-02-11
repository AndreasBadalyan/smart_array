/**
\file 
\brief File contains definition of template Vector class.
*/

#ifndef _SMART_ARRAY_HPP_
#define _SMART_ARRAY_HPP_

#include <stdexcept>
#include <limits>
#include <cstdlib>
#include <cstddef>
#include <bits/cpp_type_traits.h>

#include "r_a_iterator.hpp"

namespace tasks {
    const unsigned cap_modifier = 3;

    /**
    \brief Template Vector class. 
    */
    template <typename T>
    class Vector
    {
    public:
        typedef size_t size_type;

        class Reverse_iterator;

        /**
        \brief Iterator class.
        */
        class Iterator : public R_a_iterator<T> 
        {
        public:
            Iterator(const T *w_ptr); 
        };

        /**
        \brief Reverse iterator class.
        */
        class Reverse_iterator : public Reverse_r_a_iterator<T>
        {
        public:
            Reverse_iterator(const T *w_ptr);
            operator Iterator() const;
        };

        typedef Iterator iterator;
        typedef const Iterator const_iterator;
        typedef Reverse_iterator reverse_iterator;
        typedef const Reverse_iterator const_reverse_iterator;

        ///Default constructor. 
        Vector() : v_size(0), v_capacity(0), v_front_ptr(0) {}
        Vector(const size_type, const T & = T());
        Vector(const Vector<T> &vec);
        template <typename In>
        Vector(In, In);
        ~Vector(void);
        
        const Vector<T> &operator=(const Vector<T> &);
        bool operator==(const Vector<T> &) const;
        bool operator!=(const Vector<T> & vec) const;
        T &operator[](const size_type i);
        const T &operator[](const size_type i) const;
        T &at(size_type);
        const T &at(size_type) const;
        void assign(const size_type , const T& = T());
        void push_back(const T &);
        void pop_back();
        iterator insert(iterator, const T &);
        iterator erase(iterator);
        T &front();
        T &back();
        const T &front() const;
        const T &back() const;
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;
        bool empty() const;
        size_type capacity() const;
        size_type size() const;
        void reserve(const size_type);
        void resize(const size_type, const T & = T()); 
        void swap(Vector<T> &);
        void clear();
        size_type max_size() const;

    private:
        ///Number of elements in vector.
        size_type v_size;
        ///Number of elements the vector can contain before reallocating.
        size_type v_capacity;
        ///Pointer to the start of an object array.
        T *v_front_ptr;

        T *service_dynamic(const size_type new_cap);
        size_type re_capacity();
        template <typename Int>
        void initialize_dispatcher(Int, Int, std::__true_type);
        template <typename In>
        void initialize_dispatcher(In, In, std::__false_type);
        template <typename In>
        void range_constructor_helper(In, In, std::input_iterator_tag);
        void constructor_helper(const size_type, const T&);
    };

    /**
    \brief Copies right array into left.
    \param left_ptr, right_ptr Pointers to the start of left and right arrays. 
    \param end_ptr Pointer to the end of the left array.
    */
    template <typename T>
    void copy(T *left_ptr, T *right_ptr, T *end_ptr)
    {
        for (; left_ptr !=  end_ptr; ++left_ptr, ++right_ptr) {
            *left_ptr = *right_ptr;
        }
    }

    /**
    \brief Default constructor.
    \param w_ptr Pointer to an object. 
    */
    template <typename T>
    Vector<T>::iterator::Iterator(const T *w_ptr) : R_a_iterator<T>(w_ptr)
    {
        
    }

    /**
    \brief Default constructor.
    \param w_ptr Pointer to an object. 
    */
    template <typename T>
    Vector<T>::reverse_iterator::Reverse_iterator(const T *w_ptr) : Reverse_r_a_iterator<T>(w_ptr)
    {
        
    }

    /**
    \brief Conversion to a specified type.
    */
    template <typename T>
    Vector<T>::reverse_iterator::operator Vector<T>::iterator() const
    {
       return Vector<T>::iterator(this->m_referee_ptr + 1);
    }

    /**
    \brief Constructor.
    \param size Count of elements.
    \param value Optional reference to an object to initialize all elements. 
    */
    template <typename T>
    Vector<T>::Vector(const size_type size, const T &value)
    {
        constructor_helper(size, value);
    }

    /**
    \brief Service function called by the first initialize_dispatcher 
     below and by the vector(n, value) constructor.
    \param size Count of elements.
    \param value Optional reference to an object to initialize all elements. 
    */
    template <typename T>
    void Vector<T>::constructor_helper(const size_type size, const T &value)
    {
        v_size = size; 
        v_front_ptr = service_dynamic(re_capacity()); 

        for (size_type i = 0; i < v_size; ++i) {
       	    v_front_ptr[i] = value; 
        }
    }

    /**
    \brief Copy constructor.
    \param vec Reference to a Vector object. 
    */
    template <typename T>
    Vector<T>::Vector(const Vector<T> &vec)
    { 
        v_size = vec.v_size; 
        v_front_ptr = service_dynamic(re_capacity()); 
        copy(v_front_ptr, vec.v_front_ptr, v_front_ptr + v_size); 
    }

    /**
    \brief Constructor.
    \param it_begin, it_end Iterators to the start and end of the sequence to initialize. 
    */
    template <typename T> template <typename In>
    Vector<T>::Vector(In it_begin, In it_end)
    {
            typedef typename std::__is_integer<In>::__type Integral;
            initialize_dispatcher(it_begin, it_end, Integral());
    }

    /**
    \brief Overloaded function that is called by range constructor.
    \param size Count of elements.
    \param value Optional reference to an object to initialize all elements.
    \param std::__true_type is a struct that is used to decide 
     which overloaded function will be called
    */
    template <typename T> template <typename Int>
    void Vector<T>::initialize_dispatcher(Int size, Int value, std::__true_type)
    {
        constructor_helper(static_cast<size_type>(size), value);
    }

    /**
    \brief Overloaded function that is called by range constructor.
    \param it_begin, it_end Iterators to the start and end of the sequence to initialize. 
    \param std::__false_type is a struct that is used to decide 
     which overloaded function will be called
    */
    template <typename T> template <typename In>
    void Vector<T>::initialize_dispatcher(In begin, In end, std::__false_type)
    {
       typedef typename std::iterator_traits<In>::iterator_category category;
       range_constructor_helper(begin, end, category());
    }
    
    /**
    \brief Called by dispatcher above.
    \param it_begin, it_end Iterators to the start and end of the sequence to initialize. 
    \param std::input_iterator_tag.
    */
    template <typename T> template <typename In>
    void Vector<T>::range_constructor_helper(In begin, In end, std::input_iterator_tag)
    {
        size_type size = std::distance(begin, end);

        if (size > 0) {
            v_size = size;
            v_front_ptr = service_dynamic(re_capacity());

            for (int i = 0; begin != end; ++begin, ++i) {
                v_front_ptr[i] = *begin;
            }
        } else {
            v_size = 0;
            v_capacity = 0;
            v_front_ptr = 0;
        }
    }

    ///Destructor.
    template <typename T>
    Vector<T>::~Vector(void)
    {
	    delete[] v_front_ptr; 
    }

    /**
    \brief Assigns given vector to the Vector object.
    \param right Given vector.
    \return Changed Vector object.
    */
    template <typename T>
    const Vector<T> &Vector<T>::operator=(const Vector<T> &right)
    {
        if(this != &right){ 
            v_size = right.v_size; 
            v_front_ptr = service_dynamic(re_capacity()); 
            copy(v_front_ptr, right.v_front_ptr, v_front_ptr + v_size); 
        } 
        return *this; 
    }

    /**
    \brief Compare equality of two vectors.
    \param right Vector to compare with.
    \return true if equal, false if not.
    */
    template <typename T>
    bool Vector<T>::operator==(const Vector<T> &right) const
    {
        if (v_size != right.v_size) {
       	    return false; 
        } else {

        	for (size_type i = 0; i <= v_size; ++i) {

        		if (v_front_ptr[i] != right.v_front_ptr[i]) {
        			return false; 
                }
            }
        }
        return true; 
    }

    /**
    \brief Compare non equality of two Vector objects.
    \param iter Vector object to compare with.
    \return true if non equal, false if equal;
    */
    template <typename T>
    bool Vector<T>::operator!=(const Vector<T> & vec) const
    {
        return !(*this == vec);
    }

    /**
    \brief Vector indexing.
    \param i Index. 
    \return Reference to an object at given index.
    */
    template <typename T>
    T &Vector<T>::operator[](const size_type i)
    {
        return *(v_front_ptr + i);
    }

    /**
    \brief Vector indexing.
    \param i Index. 
    \return Const reference to an object at given index.
    */
    template <typename T>
    const T &Vector<T>::operator[](const size_type i) const
    {
        return *(v_front_ptr + i);
    }

    /**
    \brief Accessing the vector element. Throws exception if index is out of range. 
    \param i Index.
    \return Reference to the element.
    */
    template <typename T>
    T &Vector<T>::at(size_type i)
    {
        if (i >= 0 && i < v_size) {
       	    return *(v_front_ptr + i); 
        } else { 
            throw std::out_of_range("Index is out of range.");
            return *v_front_ptr; 
        } 
    }

    /**
    \brief Accessing the vector element. Throws exception if index is out of range. 
    \param i Index.
    \return Const reference to the element.
    */
    template <typename T>
    const T &Vector<T>::at(size_type i) const
    {
        if (i >= 0 && i < v_size) {
       	    return *(v_front_ptr + i); 
        } else { 
            throw std::out_of_range("Index is out of range.");
            return *v_front_ptr; 
        } 
    }

    /**
    \brief Adding element to the end of the vector. Reallocating if neccessary.
    \param value Element to be added.
    */
    template <typename T>
    void Vector<T>::push_back(const T &value)
    {
        if (v_size < v_capacity) { 
       	    v_front_ptr[v_size] = value; 
            ++v_size; 
        } else { 

       	    if (empty()) { 
                 v_size = 1;
        	     v_front_ptr = service_dynamic(re_capacity()); 
        	     v_front_ptr[v_size - 1] = value; 
            } else { 
                T *temp_ptr = v_front_ptr; 
                v_front_ptr = service_dynamic(re_capacity()); 
                copy(v_front_ptr, temp_ptr, v_front_ptr + v_size); 
                v_front_ptr[v_size] = value; 
                ++v_size; 
                delete[] temp_ptr; 
        	} 
        } 
    }

    ///Popping the last element of Vector.
    template <typename T>
    void Vector<T>::pop_back()
    {
        if (v_size) --v_size;
    }
        
    /**
    \brief Inserts element to given position. Does nothing if position is out of range.
    \param pos Position.
    \param value Value to be inserted.
    \return Iterator to the inserted element if inserted, to the end otherwise.
    */
    template <typename T>
    typename Vector<T>::iterator Vector<T>::insert(iterator pos, const T &value)
    {
        if (pos == end()) {
            push_back(value);
            return Vector<T>::iterator(v_front_ptr + v_size - 1);
        }
        if (end() < pos || pos < begin()) {
            return end();
        }
        if (v_size < v_capacity) {
            size_type index = pos - begin();
            T *temp_ptr = service_dynamic(v_capacity - index);
            copy(temp_ptr, v_front_ptr + index, temp_ptr + v_size - index);
            v_front_ptr[index] = value;
            ++v_size;
            copy(v_front_ptr + index + 1, temp_ptr, v_front_ptr + v_size);
            delete[] temp_ptr;
            return Vector<T>::iterator(v_front_ptr + index);
        }
        size_type index = pos - begin();
        T *temp_ptr = v_front_ptr;
        ++v_size;
        v_front_ptr = service_dynamic(re_capacity());
        copy(v_front_ptr, temp_ptr, v_front_ptr + index);
        v_front_ptr[index] = value;
        copy(v_front_ptr + index + 1, temp_ptr + index, v_front_ptr + v_size);
        delete[] temp_ptr;
        return Vector<T>::iterator(v_front_ptr + index);
    }

    /**
    \brief Remove element of given position. Does nothing if position is out of range.
    \param pos Position.
    \return Iterator to the next element of removed element, to the end if not removed.
    */
    template <typename T>
    typename Vector<T>::iterator Vector<T>::erase(iterator pos)
    {
        
        if (end() < pos || pos == end() || pos < begin()) {
            return end();
        }
        if (end() == pos + 1) {
            --v_size;
            return end();
        }
        for (Vector<T>::iterator it = pos; it != end(); ++it) {
            *it = *(it + 1);
        }
        --v_size;
        return pos;
    }

    ///Returns reference of the first element.
    template <typename T>
    T &Vector<T>::front()
    {
        return *v_front_ptr;
    }

    ///Returns reference of the last element.
    template <typename T>
    T &Vector<T>::back()
    {
        return *(v_front_ptr + v_size - 1);
    }

    ///Returns const reference of the first element.
    template <typename T>
    const T &Vector<T>::front() const
    {
        return *v_front_ptr;
    }

    ///Returns const reference of the last element.
    template <typename T>
    const T &Vector<T>::back() const
    {
        return *(v_front_ptr + v_size - 1);
    }

    ///Returns iterator to the first element.
    template <typename T>
    typename Vector<T>::iterator Vector<T>::begin()
    {
        return iterator(v_front_ptr);
    }

    ///Returns iterator to end of Vector.
    template <typename T>
    typename Vector<T>::iterator Vector<T>::end()
    {
        return iterator(v_front_ptr + v_size);
    }

    ///Returns const iterator to the first element.
    template <typename T>
    typename Vector<T>::const_iterator Vector<T>::begin() const
    {
        return const_iterator(v_front_ptr);
    }

    ///Returns const iterator to end of Vector.
    template <typename T>
    typename Vector<T>::const_iterator Vector<T>::end() const
    {
        return const_iterator(v_front_ptr + v_size);
    }

    ///Returns reverse iterator to the first element.
    template <typename T>
    typename Vector<T>::reverse_iterator Vector<T>::rbegin()
    {
        return reverse_iterator(v_front_ptr + v_size);
    }

    ///Returns reverse iterator to end of Vector.
    template <typename T>
    typename Vector<T>::reverse_iterator Vector<T>::rend()
    {
        return reverse_iterator(v_front_ptr);
    }

    ///Returns const reverse iterator to the first element.
    template <typename T>
    typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const
    {
        return const_reverse_iterator(v_front_ptr + v_size);
    }

    ///Returns const reverse iterator to end of Vector.
    template <typename T>
    typename Vector<T>::const_reverse_iterator Vector<T>::rend() const
    {
        return const_reverse_iterator(v_front_ptr);
    }

    ///Checks if Vector object has no elements.
    template <typename T>
    bool Vector<T>::empty() const
    {
        return 0 == v_size;
    }

    ///Returns the capacity of Vector object.
    template <typename T>
    typename Vector<T>::size_type Vector<T>::capacity() const
    {
        return v_capacity;
    }

    ///Returns the size of Vector object.
    template <typename T>
    typename Vector<T>::size_type Vector<T>::size() const
    {
        return v_size;
    }

    /**
    \brief Increasing the capacity if given value is greater than capacity.
           Throws length_error if value is greater than maximum size.
    \param new_cap Capacity.
    */
    template <typename T>
    void Vector<T>::reserve(size_type new_cap)
    {
        if (new_cap > max_size()) {
            throw std::length_error("Capacity cannot be greater than maximum size.");
        }
        if (new_cap > v_capacity) { 
            v_capacity = new_cap; 
            T *temp_ptr = v_front_ptr; 
       	    v_front_ptr = service_dynamic(v_capacity); 
            copy(v_front_ptr, temp_ptr, v_front_ptr + v_size); 
           	delete [] temp_ptr; 
        } 
    }

    /**
    \brief Changes the number of stored elements. Works like std::vector::resize().
    \param new_size Number of elements.
    \param value Value of appended elements if new_size is greater than the size.
    */
    template <typename T>
    void Vector<T>::resize(const size_type new_size, const T &value)
    {
	size_type old_size = v_size;
	v_size = new_size;	

        if (v_size <= old_size) {
            return;
        } else {

            if (v_size > v_capacity) {
                T *temp_ptr = v_front_ptr;
                v_front_ptr = service_dynamic(re_capacity()); 
                copy(v_front_ptr, temp_ptr, v_front_ptr + old_size); 
           	    delete [] temp_ptr; 
            } 
            for (size_type i = old_size; i < v_size; ++i) {
       	        v_front_ptr[i] = value; 
            }
        }
    }

    /**
    \brief Swaps the contents of two vectors.
    \param other Vector to make swap with.
    */
    template <typename T>
    void Vector<T>::swap(Vector<T> &other)
    {
        T *temp_ptr = v_front_ptr;
	size_type temp_size = v_size;
        v_front_ptr = other.v_front_ptr;
	v_size = other.v_size;
        other.v_front_ptr = temp_ptr;
	other.v_size = temp_size;
    }

    ///Removed all elements.
    template <typename T>
    void Vector<T>::clear()
    {
        v_size = 0;
    }

    ///Returns the maximum allowed size of Vector.
    template <typename T>
    typename Vector<T>::size_type Vector<T>::max_size() const
    {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    /**
    \brief Replaces the contents with count copies of given value.
    \param count Number of elements to be replaced.
    \param value Values to be copied.
    */
    template <typename T>
    void Vector<T>::assign(const size_type count, const T &value)
    {
        v_size = count; 
        v_front_ptr = service_dynamic(re_capacity()); 

        for (size_type i = 0; i < v_size; ++i) {
       	    v_front_ptr[i] = value; 
        }
    }

    /**
    \brief Allocates memory.
    \param new_cap Number of elements to allocate. 
    \return Pointer to allocated memory.
    */
    template <typename T>
    T *Vector<T>::service_dynamic(const size_type new_cap)
    {
        return new T[new_cap]; 
    }

    ///Recalculating and changing the capacity value to be up to date.
    template <typename T>
    typename Vector<T>::size_type Vector<T>::re_capacity()
    {
        return v_capacity = v_size + v_size / 2 + cap_modifier;
    }
}

#endif
