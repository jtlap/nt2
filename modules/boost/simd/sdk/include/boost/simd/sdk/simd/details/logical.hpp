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

#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/toolbox/predicates/include/functions/is_nez.hpp>

//==============================================================================
// Do something only if in SIMD mode
//==============================================================================
#if defined(BOOST_SIMD_DETECTED)
#include <boost/simd/sdk/simd/native.hpp>

namespace boost { namespace simd
{
  template<class Scalar,class Extension> 
  struct BOOST_SIMD_MAY_ALIAS native<logical<Scalar>, Extension>
  {
    typedef Extension                                       extension_type;

    #if defined(BOOST_SIMD_LRB_FAMILY)
    typedef __mmask                                         native_type;
    #else
    typedef typename meta::as_simd<Scalar, Extension>::type native_type;
    #endif
    typedef native<Scalar, Extension>                               type; 
    
    typedef logical<Scalar>                                 value_type;
    typedef logical<Scalar>                                 reference;
    typedef logical<Scalar>                                 const_reference;
    typedef std::size_t                                     size_type;

    template<class U> struct rebind
    {
      typedef native<U, extension_type> type;
    };

    #if defined(BOOST_SIMD_LRB_FAMILY)
    // Cardinal is __mmask size
    enum { static_size = sizeof(__mmask) };
    #else
    // Beware to have same cardinal than native<Scalar,Ext>
    enum { static_size = sizeof(native_type)/sizeof(Scalar)
                       ? sizeof(native_type)/sizeof(Scalar) : 1};

    #endif

    BOOST_DISPATCH_FORCE_INLINE native& operator=(native const& s)
    {
      data_ = s.data_;
      return *this;
    }
    
    // When initialized from a Scalar native, is_nez it
    BOOST_DISPATCH_FORCE_INLINE 
    native& operator=(native<Scalar,Extension> const& s)
    {
      data_ = is_nez(s);
      return *this;
    }
    
    BOOST_DISPATCH_FORCE_INLINE native& operator=(native_type const& data)
    {
      native<Scalar,Extension> s = { data };
      data_ = is_nez(s);
      return *this;
    }

    BOOST_DISPATCH_FORCE_INLINE
    operator native_type const& ()   const { return data_; }
    
    BOOST_DISPATCH_FORCE_INLINE
    native_type const& operator()()  const { return data_; }

    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(native)

    static BOOST_DISPATCH_FORCE_INLINE
    std::size_t size() { return static_size; }

    static BOOST_DISPATCH_FORCE_INLINE
    bool empty() { return false; }

    #if defined(BOOST_SIMD_LRB_FAMILY)   
    value_type operator[](std::size_t i) const { return data_ & (1 << i); }
    #else
    value_type operator[](std::size_t i) const
    {
      return (reinterpret_cast<Scalar const*>(&data_)[i]) ? true:false;
    }    
    #endif
    
    native_type data_;
  };
} }

#endif

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class X, class Origin>
  struct hierarchy_of< simd::native< simd::logical<T>, X>, Origin>
  {
    typedef simd::ext::simd_< simd::ext::logical_<Origin>, X> type;
  };
} }  }

namespace boost { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  // Stream insertion for swar types
  //////////////////////////////////////////////////////////////////////////////
  template<class S,class E> inline std::ostream&
  operator<<( std::ostream& os, native<logical<S>,E> const & v )
  {
    os << "{" << std::boolalpha; 
    for(std::size_t i=0;i<v.size()-1;++i) os << bool(v[i]) << ",";
    os << bool(v[v.size()-1UL]) << "}" << std::noboolalpha;
    return os;
  }
} }

#endif
