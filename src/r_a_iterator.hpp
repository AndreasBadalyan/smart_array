/**
\file 
\brief File contains definitions of template iterator class hierarchy.
*/

#ifndef R_A_ITERATOR_HPP
#define R_A_ITERATOR_HPP

#include <cstddef>
#include <iterator>

namespace tasks {

    template <typename T>
    class Vector;

    /**
    \brief Base template class representing base iterator. 
    */
    template <typename T>
    class Base_r_a_iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
        friend class Vector<T>;
    protected:
        ///Pointer to an object on which iterator points.
        T* m_referee_ptr;
        T* get_ptr() const { return m_referee_ptr; }
        //typename std::iterator<std::random_access_iterator_tag, T>::pointer m_referee_ptr;
    public:
        /**
        \brief Default constructor.
        \param w_ptr Pointer to an object. 
        */
        Base_r_a_iterator(const T *w_ptr = 0) : m_referee_ptr(const_cast<T *>(w_ptr)) { }
        T &operator*();
        const T &operator*() const;
        T *operator->();
        const T *operator->() const;
        bool operator==(Base_r_a_iterator<T> iter) const; 
        bool operator!=(Base_r_a_iterator<T> iter) const;
        bool operator<(Base_r_a_iterator<T> iter) const;
    };

    ///returns reference  to an object.
    template <typename T>
    T &Base_r_a_iterator<T>::operator*()
    {
        return *m_referee_ptr;
    }

    ///returns const reference  to an object.
    template <typename T>
    const T &Base_r_a_iterator<T>::operator*() const
    {
        return *m_referee_ptr;
    }

    ///returns pointer to an object. 
    template <typename T>
    T *Base_r_a_iterator<T>::operator->()
    {
        return m_referee_ptr;
    }

    ///returns const pointer to an object. 
    template <typename T>
    const T *Base_r_a_iterator<T>::operator->() const
    {
        return m_referee_ptr; 
    }

    /**
    \brief Compare equality of two iterators.
    \param iter Iterator to compare with.
    \return true if equal, false if not.
    */
    template <typename T>
    bool Base_r_a_iterator<T>::operator==(Base_r_a_iterator<T> iter) const 
    { 
        return m_referee_ptr == iter.m_referee_ptr;
    }

    /**
    \brief Compare non equality of two iterators.
    \param iter Iterator to compare with.
    \return true if non equal, false if equal;
    */
    template <typename T>
    bool Base_r_a_iterator<T>::operator!=(Base_r_a_iterator<T> iter) const
    {
        return !(*this == iter);
    }
    
    /**
    \brief Compare if iterator is less than given iterator.
    \param iter Iterator to compare with.
    \return true if less than given, false if not.
    */
    template <typename T>
    bool Base_r_a_iterator<T>::operator<(Base_r_a_iterator<T> iter) const 
    { 
        return m_referee_ptr < iter.m_referee_ptr;
    }

    /**
    \brief Template iterator class.
    */
    template <typename T>
    class R_a_iterator : public Base_r_a_iterator<T>
    {
    public:
        /**
        \brief Default constructor.
        \param w_ptr Pointer to an object. 
        */
        R_a_iterator(const T *w_ptr = 0) : Base_r_a_iterator<T>(w_ptr) { }
        R_a_iterator<T> &operator++();
        R_a_iterator<T> operator++(int);
        R_a_iterator<T> &operator--();
        R_a_iterator<T> operator--(int);
        R_a_iterator<T> operator+(const unsigned value) const;
        R_a_iterator<T> operator-(const unsigned value) const;
        ptrdiff_t operator-(const R_a_iterator<T> iter) const;
        R_a_iterator<T> &operator+=(const unsigned value);
        R_a_iterator<T> &operator-=(const unsigned value);
    };

    /**
    \brief Calculates the distance of two iterators.
    \param iter Iterator to get distance from.
    \return Distance of two iterators.
    */
    template <typename T>
    ptrdiff_t R_a_iterator<T>::operator-(const R_a_iterator<T> iter) const
    {
         return this->m_referee_ptr - iter.m_referee_ptr;
    }

    /**
    \brief Preincrements iterator.
    \return Preincremented iterator.
    */
    template <typename T>
    R_a_iterator<T> &R_a_iterator<T>::operator++()
    {
        ++this->m_referee_ptr;
        return *this;
    }

    /**
    \brief Postincrements iterator.
    \return Iterator before incrementing.
    */
    template <typename T>
    R_a_iterator<T> R_a_iterator<T>::operator++(int)
    {
        R_a_iterator<T> temp = *this;
        ++this->m_referee_ptr;
        return temp;
    }

    /**
    \brief Predecrements iterator.
    \return Predecremented iterator.
    */
    template <typename T>
    R_a_iterator<T> &R_a_iterator<T>::operator--()
    {
        --this->m_referee_ptr;
        return *this;
    }

    /**
    \brief Postdecrements iterator.
    \return Iterator before decrementing. 
    */
    template <typename T>
    R_a_iterator<T> R_a_iterator<T>::operator--(int)
    {
        R_a_iterator<T> temp = *this;
        --this->m_referee_ptr;
        return temp;
    }

    /**
    \brief Performs addition assignment to iterator with given value.
    \param offset Value for adding to an iterator.
    \return Iterator after addition assignment.
    */
    template <typename T>
    R_a_iterator<T> &R_a_iterator<T>::operator+=(const unsigned offset)
    {
        this->m_referee_ptr += offset;
        return *this;
    }

    /**
    \brief Performs addition to iterator with given value.
    \param offset Value for adding to an iterator.
    \return Temperary iterator as an addition result.
    */
    template <typename T>
    R_a_iterator<T> R_a_iterator<T>::operator+(const unsigned offset) const
    {
        R_a_iterator<T> temp(this->m_referee_ptr + offset);
        return temp;
    }

    /**
    \brief Performs subtraction assignment to iterator with given value.
    \param offset Value for subtracting from an iterator.
    \return Iterator after subtraction assignment.
    */
    template <typename T>
    R_a_iterator<T> &R_a_iterator<T>::operator-=(const unsigned offset)
    {
        this->m_referee_ptr -= offset;
        return *this;
    }

    /**
    \brief Performs subtraction from iterator with given value.
    \param offset Value for subtracting from an iterator.
    \return Temperary iterator as a subtraction result.
    */
    template <typename T>
    R_a_iterator<T> R_a_iterator<T>::operator-(const unsigned offset) const
    {
        R_a_iterator<T> temp(this->m_referee_ptr - offset);
        return temp;
    }

    /**
    \brief Template reverse iterator.
    */
    template <typename T>
    class Reverse_r_a_iterator : public Base_r_a_iterator<T>
    {
    public:
        /**
        \brief Default constructor.
        \param w_ptr Pointer to an object. 
        */
        Reverse_r_a_iterator(const T *w_ptr = 0) : Base_r_a_iterator<T>(w_ptr - 1) { }
        Reverse_r_a_iterator<T> &operator++();
        Reverse_r_a_iterator<T> operator++(int);
        Reverse_r_a_iterator<T> &operator--();
        Reverse_r_a_iterator<T> operator--(int);
        Reverse_r_a_iterator<T> operator+(const unsigned value) const;
        Reverse_r_a_iterator<T> operator-(const unsigned value) const;
        operator R_a_iterator<T>() const;
        ptrdiff_t operator-(const Reverse_r_a_iterator<T> iter) const;
        Reverse_r_a_iterator<T> &operator+=(const unsigned value);
        Reverse_r_a_iterator<T> &operator-=(const unsigned value);
    };

    /**
    \brief Calculates the distance of two iterators.
    \param iter Iterator to get distance from.
    \return Distance of two iterators.
    */
    template <typename T>
    ptrdiff_t Reverse_r_a_iterator<T>::operator-(const Reverse_r_a_iterator<T> iter) const
    {
         return iter.m_referee_ptr - this->m_referee_ptr;
    }

    /**
    \brief Preincrements iterator.
    \return Preincremented iterator.
    */
    template <typename T>
    Reverse_r_a_iterator<T> &Reverse_r_a_iterator<T>::operator++()
    {
        --this->m_referee_ptr;
        return *this;
    }

    /**
    \brief Postincrements iterator.
    \return Iterator before incrementing.
    */
    template <typename T>
    Reverse_r_a_iterator<T> Reverse_r_a_iterator<T>::operator++(int)
    {
        Reverse_r_a_iterator<T> temp = *this;
        --this->m_referee_ptr;
        return temp;
    }

    /**
    \brief Predecrements iterator.
    \return Predecremented iterator.
    */
    template <typename T>
    Reverse_r_a_iterator<T> &Reverse_r_a_iterator<T>::operator--()
    {
        ++this->m_referee_ptr;
        return *this;
    }

    /**
    \brief Postincrements iterator.
    \return Iterator before incrementing.
    */
    template <typename T>
    Reverse_r_a_iterator<T> Reverse_r_a_iterator<T>::operator--(int)
    {
        Reverse_r_a_iterator<T> temp = *this;
        ++this->m_referee_ptr;
        return temp;
    }

    /**
    \brief Performs addition assignment to iterator with given value.
    \param offset Value for adding to an iterator.
    \return Iterator after addition assignment.
    */
    template <typename T>
    Reverse_r_a_iterator<T> &Reverse_r_a_iterator<T>::operator+=(const unsigned offset)
    {
        this->m_referee_ptr -= offset;
        return *this;
    }

    /**
    \brief Performs addition to iterator with given value.
    \param offset Value for adding to an iterator.
    \return Temperary iterator as an addition result.
    */
    template <typename T>
    Reverse_r_a_iterator<T> Reverse_r_a_iterator<T>::operator+(const unsigned offset) const
    {
        Reverse_r_a_iterator<T> temp(this->m_referee_ptr + offset);
        return temp;
    }

    /**
    \brief Performs subtraction assignment to iterator with given value.
    \param offset Value for subtracting from an iterator.
    \return Iterator after subtraction assignment.
    */
    template <typename T>
    Reverse_r_a_iterator<T> &Reverse_r_a_iterator<T>::operator-=(const unsigned offset)
    {
        this->m_referee_ptr += offset;
        return *this;
    }

    /**
    \brief Performs subtraction from iterator with given value.
    \param offset Value for subtracting from an iterator.
    \return Temperary iterator as a subtraction result.
    */
    template <typename T>
    Reverse_r_a_iterator<T> Reverse_r_a_iterator<T>::operator-(const unsigned offset) const
    {
        Reverse_r_a_iterator<T> temp(this->m_referee_ptr + offset);
        return temp;
    }

    /**
    \brief Conversion to a specified type.
    */
    template <typename T>
    Reverse_r_a_iterator<T>::operator R_a_iterator<T>() const
    {
       return R_a_iterator<T>(this->m_referee_ptr + 1);
    }
}

#endif
