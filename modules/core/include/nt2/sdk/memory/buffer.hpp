//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_VECTOR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_VECTOR_HPP_INCLUDED

#include <cstddef>
#include <boost/swap.hpp>
#include <boost/detail/iterator.hpp>
#include <nt2/sdk/memory/adapted/buffer.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /**!
   * @brief buffer is a dynamically-sized sequence using dynamic storage.
   **/
  //===========================================================================
  template<class T, class Allocator> class buffer
  {
    public:
    //==========================================================================
    // Container types
    //==========================================================================
    typedef typename Allocator::template rebind<T>::other allocator_type;
    typedef typename allocator_type::value_type           value_type;
    typedef typename allocator_type::reference            reference;
    typedef typename allocator_type::const_reference      const_reference;
    typedef typename allocator_type::pointer              pointer;
    typedef typename allocator_type::const_pointer        const_pointer;
    typedef typename allocator_type::pointer              iterator;
    typedef typename allocator_type::const_pointer        const_iterator;
    typedef std::reverse_iterator<iterator>               reverse_iterator;
    typedef std::reverse_iterator<const_iterator>         const_reverse_iterator;
    typedef typename allocator_type::size_type            size_type;
    typedef typename allocator_type::difference_type      difference_type;

    //==========================================================================
    // Default constructor
    //==========================================================================
    buffer( allocator_type a = allocator_type())
          : begin_(0), end_(0), capacity_(0), alloc(a)
    {}

    //==========================================================================
    // Size constructor
    //==========================================================================
    buffer( size_type n, allocator_type a = allocator_type())
          : begin_(0), end_(0), capacity_(0), alloc(a)
    {
      begin_ = alloc.allocate(n);
      if(begin_) end_ = capacity_ = begin_ + n;
    }

    //==========================================================================
    // Copy constructor
    //==========================================================================
    buffer( buffer const& src)
          : begin_(0), end_(0), capacity_(0), alloc(src.alloc)
    {
      begin_ = alloc.allocate(src.size());
      if(begin_) end_ = capacity_ = begin_ + src.size();
      copy(src);
    }

    //==========================================================================
    // Destructor
    //==========================================================================
    ~buffer()
    {
      if(begin_) alloc.deallocate(begin_,size());
    }

    //==========================================================================
    // Assignment
    //==========================================================================
    buffer& operator=(buffer const& src)
    {
      resize(src.size());
      copy(src);
      return *this;
    }

    //==========================================================================
    // Resize
    //==========================================================================
    void resize( size_type sz )
    {
      if(sz > capacity() )
      {
        buffer that(sz,alloc);
        swap(that);
      }
      else
      {
        end_ = begin_ + sz;
      }
    }

    //==========================================================================
    // Swap
    //==========================================================================
    void swap( buffer& src )
    {
      boost::swap(begin_    , src.begin_    );
      boost::swap(end_      , src.end_      );
      boost::swap(capacity_ , src.capacity_ );
      boost::swap(alloc     , src.alloc     );
    }

    //==========================================================================
    // Iterators
    //==========================================================================
    iterator        begin()       { return begin_;  }
    const_iterator  begin() const { return begin_;  }
    iterator        end()         { return end_;    }
    const_iterator  end()   const { return end_;    }

    reverse_iterator rbegin()     { return reverse_iterator(end());   }
    reverse_iterator rend()       { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const
    {
      return const_reverse_iterator(end());
    }

    const_reverse_iterator rend() const
    {
      return const_reverse_iterator(begin());
    }

    //==========================================================================
    // Raw values
    //==========================================================================
    pointer        raw()       { return begin_;  }
    const_pointer  raw() const { return begin_;  }

    //==========================================================================
    // Size related members
    //==========================================================================
    inline size_type  size()      const { return end_ - begin_;       }
    inline size_type  capacity()  const { return capacity_ - begin_;  }
    inline bool       empty()     const { return size() == 0;         }

    //==========================================================================
    // Random access
    //==========================================================================
    inline reference       operator[](size_type i)       { return begin_[i]; }
    inline const_reference operator[](size_type i) const { return begin_[i]; }

    protected:

    void copy(buffer const& src)
    {
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400) && BOOST_WORKAROUND(BOOST_MSVC, < 1600)
      stdext::unchecked_copy(src.begin(),src.end(),begin());
#elif BOOST_WORKAROUND(BOOST_MSVC, > 1500)
      std::copy ( src.begin(),src.end()
                , stdext::make_unchecked_array_iterator(begin())
                );
#else
      std::copy(src.begin(),src.end(),begin());
#endif
    }

    private:
    pointer         begin_, end_, capacity_;
    allocator_type  alloc;
  };

  //============================================================================
  /**!
   * Swap the contents of two buffer of same type and allocator settings
   * \param x First \c pointer_buffer to swap
   * \param y Second \c pointer_buffer to swap
   **/
  //============================================================================
  template<class T, class A> inline
  void swap (buffer<T,A>& x, buffer<T,A>& y)  { x.swap(y); }
} }

#endif
