//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_LOGICAL_META_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_LOGICAL_META_HPP_INCLUDED

#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/io/ios_state.hpp>

namespace boost { namespace simd { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // vector_of<T,Card> computes the proper type for pack of N elements of types T
  // Either <T,Card> maps onto a SIMD types, either to array<T,Card>
  //////////////////////////////////////////////////////////////////////////////
  template<class T,std::size_t Card>
  struct vector_of<logical<T>,Card> 
   : as_logical<typename vector_of<T,Card>::type >
  {
  };
  
  template<class T, class X>
  struct is_vectorizable<logical<T>, X>
    : is_vectorizable<T, X>
  {
  };

  template<class T, class X >
  struct  cardinal_of< simd::native<simd::logical<T>, X> >
        : cardinal_of< simd::native<T, X> >
  {};
} } }

namespace boost { namespace simd { namespace tag
{
  struct insert_;
  struct extract_;
} } }

namespace boost { namespace simd
{
  template<class Scalar,class Extension> 
  struct BOOST_SIMD_MAY_ALIAS native<logical<Scalar>, Extension>
  {
    typedef Extension                                       extension_type;
    typedef typename meta::
            as_simd<logical<Scalar>, Extension>::type          native_type;
    typedef native<logical<Scalar>, Extension>                   this_type;
    typedef native<Scalar, Extension>                                 type;
    
    typedef logical<Scalar>                                     value_type;
    typedef std::size_t                                          size_type;
    
    struct proxy
    {
      proxy(this_type& data_, std::size_t index_) : data(data_), index(index_)
      {
      }

      proxy const& operator=(value_type const& other) const
      {
        typename dispatch::make_functor<tag::insert_, Scalar>::type()(other, data, index);
        return *this;
      }

      operator bool() const
      {
        return typename dispatch::make_functor<tag::extract_, Scalar>::type()(data, index);
      }

      this_type& data;
      std::size_t index;
    };
    
    typedef proxy                                                reference;
    typedef logical<Scalar> const                          const_reference;
    
    template<class T>
    struct iterator_base
    {
      iterator_base(T& data_, std::size_t index_ = 0) : data(data_), index(index_) {}
      
    protected:
      friend class iterator_core_access;
      
      void increment()
      {
        ++index;
      }
      
      void advance(std::size_t n)
      {
        index += n;
      }
      
      void decrement()
      {
        --index;
      }
      
      std::ptrdiff_t distance_to(iterator_base const& other) const
      {
        return other.index - index;
      }
      
      bool equal(iterator_base const& other) const
      {
        return index == other.index;
      }
      
      T& data;
      std::size_t index;
    };
    
    struct iterator
      : iterator_base<this_type>, iterator_facade<iterator, value_type, std::random_access_iterator_tag, proxy>
    {
      iterator(this_type& data_, std::size_t index_ = 0) : iterator_base<this_type>(data_, index_) {}
      
    private:
      friend class iterator_core_access;
      
      proxy dereference() const
      {
        return proxy(this->data, this->index);
      }
    };
    
    struct const_iterator
      : iterator_base<this_type const>, iterator_facade<const_iterator, value_type,
                                                        std::random_access_iterator_tag, value_type const>
    {
      const_iterator(this_type const& data_, std::size_t index_ = 0) :
        iterator_base<this_type const>(data_, index_) {}
      
    private:
      friend class iterator_core_access;
      
      value_type const dereference() const
      {
        return typename dispatch::make_functor<tag::extract_, Scalar>::type()(this->data, this->index);
      }
    };

    template<class U>
    struct rebind
    {
      typedef native<U, extension_type> type;
    };

    ////////////////////////////////////////////////////////////////////////////
    // vector size
    ////////////////////////////////////////////////////////////////////////////
    enum { static_size = meta::cardinal_of<native>::value };

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator from native vector type
    ////////////////////////////////////////////////////////////////////////////
    BOOST_DISPATCH_FORCE_INLINE native& operator=(native const& s)
    {
      data_ = s.data_;
      return *this;
    }
    
    BOOST_DISPATCH_FORCE_INLINE native& operator=(native_type const& s)
    {     
      data_ = s;
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Type casting operator for compatibility with intrinsic functions
    // Use operator() for explicit conversion.
    ////////////////////////////////////////////////////////////////////////////
    BOOST_DISPATCH_FORCE_INLINE
    operator native_type const& ()   const { return data_; }
    
    BOOST_DISPATCH_FORCE_INLINE
    native_type const& operator()()  const { return data_; }

    ////////////////////////////////////////////////////////////////////////////
    // new/delete operator to force alignment on heap of native values
    ////////////////////////////////////////////////////////////////////////////
    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(native)

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    BOOST_DISPATCH_FORCE_INLINE
    iterator       begin()       { return iterator(*this); };
    
    BOOST_DISPATCH_FORCE_INLINE
    iterator       end()         { return iterator(*this, static_size); };
    
    BOOST_DISPATCH_FORCE_INLINE
    const_iterator begin() const { return const_iterator(*this); };
    
    BOOST_DISPATCH_FORCE_INLINE
    const_iterator end()   const { return const_iterator(*this, static_size); };

    ////////////////////////////////////////////////////////////////////////////
    // Array like interface
    ////////////////////////////////////////////////////////////////////////////
    static BOOST_DISPATCH_FORCE_INLINE  std::size_t size() { return static_size; }
    static BOOST_DISPATCH_FORCE_INLINE        bool empty() { return false; }

    proxy operator[](std::size_t i)
    {
      return proxy(*this, i);
    }

    const_reference operator[](std::size_t i) const
    {
      return typename dispatch::make_functor<tag::extract_, Scalar>::type()(*this, i);
    }
    
    native_type data_;
  };
} }

namespace boost { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  // Stream insertion for swar types
  //////////////////////////////////////////////////////////////////////////////
  template<class S,class E> inline std::ostream&
  operator<<( std::ostream& os, native<logical<S>,E> const & v )
  {
    boost::io::ios_flags_saver saver(os);
    os << "{" << std::boolalpha; 
    for(std::size_t i=0;i<v.size()-1;++i) os << bool(v[i]) << ",";
    os << bool(v[v.size()-1UL]) << "}";
    return os;
  }
} }

#endif
