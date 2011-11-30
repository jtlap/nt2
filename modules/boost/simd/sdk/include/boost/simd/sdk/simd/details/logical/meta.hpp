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
//ok
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/details/bitwise_cast.hpp>

namespace boost { namespace simd { namespace ext
{
  template<class T, class X >
  struct  cardinal_of< simd::native<simd::logical<T>, X> >
        : cardinal_of< simd::native<T, X> >
  {};

  template<class T,class Extension>
  struct as_simd<logical<T>, Extension> : as_simd<T,Extension>
  {};
} } }

namespace boost { namespace simd
{
  template<class Scalar,class Extension> 
  struct BOOST_SIMD_MAY_ALIAS native<logical<Scalar>, Extension>
  {
    typedef Extension                                       extension_type;
    typedef typename meta::as_simd<Scalar, Extension>::type native_type;
    typedef native<Scalar, Extension>                       type; 
    
    typedef logical<Scalar>                                 value_type;
    typedef logical<Scalar>                                 reference;
    typedef logical<Scalar>                                 const_reference;
    typedef std::size_t                                     size_type;

    template<class U> struct rebind
    {
      typedef native<U, extension_type> type;
    };

    enum { static_size = meta::cardinal_of<native>::value };

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

    BOOST_DISPATCH_FORCE_INLINE
    operator native_type const& ()   const { return data_; }
    
    BOOST_DISPATCH_FORCE_INLINE
    native_type const& operator()()  const { return data_; }

    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(native)

    static BOOST_DISPATCH_FORCE_INLINE
    std::size_t size() { return static_size; }

    static BOOST_DISPATCH_FORCE_INLINE
    bool empty() { return false; }

    value_type operator[](std::size_t i) const
    {
      typedef typename logical<Scalar>::bits bits;
      bits b  = bitwise_cast<bits>(reinterpret_cast<native<Scalar, Extension> const&>(data_)[i]) 
              & 1;
      return value_type(b);
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
    os << "{" << std::boolalpha; 
    for(std::size_t i=0;i<v.size()-1;++i) os << bool(v[i]) << ",";
    os << bool(v[v.size()-1UL]) << "}" << std::noboolalpha;
    return os;
  }
} }

#ifdef __LRB__
namespace boost { namespace simd
{
  template<class Scalar> 
  struct BOOST_SIMD_MAY_ALIAS native<logical<Scalar>, boost::simd::tag::lrb_>
  {
    typedef boost::simd::tag::lrb_                         extension_type;
    typedef __mmask                                           native_type;
    typedef native<Scalar,extension_type>                            type; 
    
    typedef logical<Scalar>                                    value_type;
    typedef logical<Scalar>                                     reference;
    typedef logical<Scalar>                               const_reference;
    typedef std::size_t                                         size_type;
    static const uint8_t Masknbbits = meta::cardinal_of<type >::value;
    static const int Lmask = (Masknbbits == 8) ? 0xFF :  0xFFFF;
    // no doubt that in real life &Lmask will be removed...!?
    value_type all() const {
      return value_type((_mm512_mask2int(data_)&Lmask) == Lmask);
    }
    value_type any() const {
      return value_type((_mm512_mask2int(data_)&Lmask) != 0);
    }
    value_type none() const {
      return value_type((_mm512_mask2int(data_)&Lmask) == 0);
    }
    template<class U> struct rebind
    {
      typedef native<U, extension_type> type;
    };

    enum { static_size = meta::cardinal_of<type>::value };

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

    BOOST_DISPATCH_FORCE_INLINE
    operator native_type const& ()   const { return data_; }
    
    BOOST_DISPATCH_FORCE_INLINE
    native_type const& operator()()  const { return data_; }

    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(native)

    static BOOST_DISPATCH_FORCE_INLINE
    std::size_t size() { return static_size; }

    static BOOST_DISPATCH_FORCE_INLINE
    bool empty() { return false; }

    value_type operator[](std::size_t i) const
    {
      bool b  = (_mm512_mask2int(data_) >> i)&1; 
      return value_type(b);
    }    
    
    native_type data_;
  };
} }
#endif
#endif
