//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// #ifndef BOOST_SIMD_SDK_SIMD_SDK_SIMD_EXTENSIONS_LRB_LOGICAL_HPP_INCLUDED
// #define BOOST_SIMD_SDK_SIMD_SDK_SIMD_EXTENSIONS_LRB_LOGICAL_HPP_INCLUDED
//#ifdef BOOST_SIMD_HAS_LRB_SUPPORT

// #include <boost/simd/sdk/simd/native.hpp>
// #include <boost/simd/sdk/simd/meta/as_simd.hpp>
// #include <boost/simd/sdk/simd/exte nsions/lrb/lrb_prototype_primitives.hpp>

// namespace boost { namespace simd
// {
//   template<class Scalar> 
//   struct BOOST_SIMD_MAY_ALIAS native<logical<Scalar>, boost::simd::tag::lrb_>
//   {
//     typedef boost::simd::tag::lrb_                         extension_type;
//     typedef __mmask                                           native_type;
//     typedef native<Scalar,extension_type>                            type; 
    
//     typedef logical<Scalar>                                    value_type;
//     typedef logical<Scalar>                                     reference;
//     typedef logical<Scalar>                               const_reference;
//     typedef std::size_t                                         size_type;

//     template<class U> struct rebind
//     {
//       typedef native<U, extension_type> type;
//     };

//     enum { static_size = meta::cardinal_of<type>::value };

//     BOOST_DISPATCH_FORCE_INLINE native& operator=(native const& s)
//     {
//       data_ = s.data_;
//       return *this;
//     }
    
//     BOOST_DISPATCH_FORCE_INLINE native& operator=(native_type const& s)
//     {     
//       data_ = s;
//       return *this;
//     }

//     BOOST_DISPATCH_FORCE_INLINE
//     operator native_type const& ()   const { return data_; }
    
//     BOOST_DISPATCH_FORCE_INLINE
//     native_type const& operator()()  const { return data_; }

//     BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(native)

//     static BOOST_DISPATCH_FORCE_INLINE
//     std::size_t size() { return static_size; }

//     static BOOST_DISPATCH_FORCE_INLINE
//     bool empty() { return false; }

//     value_type operator[](std::size_t i) const
//     {
//       bool b  = (_mm512_mask2int(data_) >> i)&1
//       return value_type(b);
//     }    
    
//     native_type data_;
//   };
// } }

// //#endif
// //#endif
