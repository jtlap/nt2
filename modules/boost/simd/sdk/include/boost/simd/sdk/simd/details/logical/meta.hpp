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
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/details/bitwise_cast.hpp>

namespace boost { namespace simd { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // vector_of<T,Card> computes the proper type for pack of N elements of types T
  // Either <T,Card> maps onto a SIMD types, either to array<T,Card>
  //////////////////////////////////////////////////////////////////////////////
  template<class T,std::size_t Card>
  struct vector_of<logical<T>,Card> 
  {
    typedef typename meta::as_logical<vector_of<T,Card> >::type type;
  };

} } }

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
    typedef typename meta::as_simd<Scalar, Extension>::type    native_type;
    typedef native<Scalar, Extension>                                 type; 
    
    typedef logical<Scalar>                                     value_type;
    typedef logical<Scalar>                                      reference;
    typedef logical<Scalar>                                const_reference;
    typedef std::size_t                                          size_type;
    typedef Scalar*                                               iterator;
    typedef Scalar const*                                   const_iterator;

    template<class U> struct rebind
    {
      typedef native<U, extension_type> type;
    };

    ////////////////////////////////////////////////////////////////////////////
    // vector size
    ////////////////////////////////////////////////////////////////////////////
    enum { static_size = sizeof(native_type)/sizeof(value_type)
                       ? sizeof(native_type)/sizeof(value_type) : 1};
    //    enum { static_size = meta::cardinal_of<native>::value };

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
    iterator       begin()       { return data(); };
    
    BOOST_DISPATCH_FORCE_INLINE
    iterator       end()         { return data() + static_size; };
    
    BOOST_DISPATCH_FORCE_INLINE
    const_iterator begin() const { return data(); };
    
    BOOST_DISPATCH_FORCE_INLINE
    const_iterator end()   const { return data() + static_size; };

    ////////////////////////////////////////////////////////////////////////////
    // Array like interface
    ////////////////////////////////////////////////////////////////////////////
    static BOOST_DISPATCH_FORCE_INLINE  std::size_t size() { return static_size; }
    static BOOST_DISPATCH_FORCE_INLINE        bool empty() { return false; }

    value_type operator[](std::size_t i) const
    {
      typedef typename logical<Scalar>::bits bits;
      bits b  = bitwise_cast<bits>(reinterpret_cast<native<Scalar, Extension> const&>(data_)[i]) & 1;
      return value_type(b);
    }    
    
    native_type data_;
    BOOST_DISPATCH_FORCE_INLINE
    value_type* data()
    {
      return reinterpret_cast<value_type*>(&data_);
    }

    BOOST_DISPATCH_FORCE_INLINE
    const value_type* data() const
    {
      return const_cast<native&>(*this).data();
    }
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
zut
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
    typedef Scalar*                                              iterator;
    typedef Scalar const*                                  const_iterator;

    ////////////////////////////////////////////////////////////////////////////
    //These are helpers to work with logical in lrb mode
    // in the current emulation...
    // no doubt that at least in real life &Lmask will be removed...!?
    ////////////////////////////////////////////////////////////////////////////
    static const uint8_t Masknbbits = meta::cardinal_of<type >::value;
    static const int Lmask = (Masknbbits == 8) ? 0xFF :  0xFFFF;
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

    ////////////////////////////////////////////////////////////////////////////
    // vector size
    ////////////////////////////////////////////////////////////////////////////
    enum { static_size = meta::cardinal_of<type>::value };

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
    iterator       begin()       { return data(); };
    
    BOOST_DISPATCH_FORCE_INLINE
    iterator       end()         { return data() + static_size; };
    
    BOOST_DISPATCH_FORCE_INLINE
    const_iterator begin() const { return data(); };
    
    BOOST_DISPATCH_FORCE_INLINE
    const_iterator end()   const { return data() + static_size; };

    ////////////////////////////////////////////////////////////////////////////
    // Array like interface
    ////////////////////////////////////////////////////////////////////////////
    static BOOST_DISPATCH_FORCE_INLINE  std::size_t size() { return static_size; }
    static BOOST_DISPATCH_FORCE_INLINE        bool empty() { return false; }

    value_type operator[](std::size_t i) const
    {
      bool b  = (_mm512_mask2int(data_) >> i)&1; 
      return value_type(b);
    }    
    
    native_type data_;
    native_type data_;
    BOOST_DISPATCH_FORCE_INLINE
    value_type* data()
    {
      return reinterpret_cast<value_type*>(&data_);
    }

    BOOST_DISPATCH_FORCE_INLINE
    const value_type* data() const
    {
      return const_cast<native&>(*this).data();
    }
  };
} }
#endif
#endif
