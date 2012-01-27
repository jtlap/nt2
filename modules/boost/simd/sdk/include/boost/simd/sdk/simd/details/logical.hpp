//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_LOGICAL_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/simd/details/soa_proxy.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class T,std::size_t Card>
  struct vector_of<logical<T>,Card> 
   : as_logical<typename vector_of<T,Card>::type >
  {
  };

  template<class T, class X >
  struct  cardinal_of< simd::native<simd::logical<T>, X> >
        : cardinal_of< simd::native<T, X> >
  {};
} } }

namespace boost { namespace simd
{
  template<class Scalar,class Extension> 
  struct native<logical<Scalar>, Extension>
  {
    typedef Extension                                       extension_type;
    typedef typename meta::
            as_simd<logical<Scalar>, Extension>::type          native_type;
    typedef native<logical<Scalar>, Extension>                   this_type;
    typedef native<Scalar, Extension>                                 type;

    typedef logical<Scalar>                                     value_type;

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
    BOOST_FORCEINLINE native& operator=(native const& s)
    {
      data_ = s.data_;
      return *this;
    }
    
    BOOST_FORCEINLINE native& operator=(native_type const& s)
    {     
      data_ = s;
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Type casting operator for compatibility with intrinsic functions
    // Use operator() for explicit conversion.
    ////////////////////////////////////////////////////////////////////////////
    BOOST_FORCEINLINE operator native_type &           ()             { return data_; }
    BOOST_FORCEINLINE          native_type & operator()()             { return data_; }
    
    BOOST_FORCEINLINE operator native_type const&           ()  const { return data_; }
    BOOST_FORCEINLINE          native_type const& operator()()  const { return data_; }

    ////////////////////////////////////////////////////////////////////////////
    // new/delete operator to force alignment on heap of native values
    ////////////////////////////////////////////////////////////////////////////
    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(native)

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    typedef std::size_t                                          size_type;
    typedef details::soa_proxy<value_type, Extension>            reference;
    typedef value_type const                                     const_reference;
    typedef details::soa_iterator<value_type, Extension>         iterator;
    typedef details::soa_const_iterator<value_type, Extension>   const_iterator;
    
    BOOST_FORCEINLINE
    iterator       begin()       { return iterator(*this);               };
    
    BOOST_FORCEINLINE
    iterator       end()         { return iterator(*this, size());       };
    
    BOOST_FORCEINLINE
    const_iterator begin() const { return const_iterator(*this);         };
    
    BOOST_FORCEINLINE
    const_iterator end()   const { return const_iterator(*this, size()); };

    ////////////////////////////////////////////////////////////////////////////
    // Array like interface
    ////////////////////////////////////////////////////////////////////////////
    static BOOST_FORCEINLINE  std::size_t size() { return meta::cardinal_of< native<value_type, Extension> >::value; }
    static BOOST_FORCEINLINE        bool empty() { return false; }

    reference operator[](std::size_t i)
    {
      return reference(*this, i);
    }

    const_reference operator[](std::size_t i) const
    {
      return typename dispatch::make_functor<tag::extract_, value_type>::type()(*this, i);
    }
    
    native_type data_;
  };
} }

#endif
