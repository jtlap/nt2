/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_NATIVE_CAST_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_NATIVE_CAST_HPP_INCLUDED
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/simd/sdk/simd/meta/is_simd_specific.hpp>
#include <boost/simd/sdk/meta/is_logical.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/assert.hpp>
// namespace boost { namespace simd
// {
//   template < class T, class U,
// 	     class ISLT = typename meta::is_logical<T>::type,
// 	     class ISLU = typename meta::is_logical<U>::type > struct convert; 

//   template < class T, class U > struct convert < T, U, 
// 	     boost::mpl::true_,
// 	     boost::mpl::true_>
//   {
//     static inline T const & do_convert(const U& u)
//     {
//       return bitwise_cast<T const &>(u);
//     }
//   };
//   template < class T, class U > struct convert < T, U, 
// 	     boost::mpl::false_,
// 	     boost::mpl::false_>
//   {
//     static inline T do_convert(const U& u)
//     {
//        return bitwise_cast<T>(u);
//     }
//   };
//   template < class T, class U > struct convert < T, U, 
// 	     boost::mpl::true_,
// 	     boost::mpl::false_>
//   {
//     static inline T  do_convert(const U& u)
//     {
//        typedef typename meta::as_logical<U>::type lU;
//        const lU tmp = is_nez(u); 
//       return bitwise_cast<T>(tmp);
//     }
//   };
//   template < class T, class U > struct convert < T, U, 
// 	     boost::mpl::false_,
// 	     boost::mpl::true_>
//   {
//     static inline T do_convert(const U& u)
//     {
//        typedef typename U::type nU;
//        const nU tmp = genmask(u); 
//        return bitwise_cast<T>(tmp);
//     }
//   };

  
//   using boost::simd::meta::is_logical; 
//   template<class T, class U>
//   BOOST_DISPATCH_FORCE_INLINE
//   T  native_cast( U const& u )
//   {
//     BOOST_MPL_ASSERT_MSG( meta::is_native<T>::value, BOOST_SIMD_NATIVE_CAST_TARGET_NOT_NATIVE, (T) );
//     BOOST_MPL_ASSERT_MSG( sizeof(T) == sizeof(U), BOOST_SIMD_NATIVE_CAST_TARGET_NOT_SAME_SIZE_AS_SOURCE, (T, U) );
//     return convert<T, U>::do_convert(u);
//   }
// } }

namespace boost { namespace simd
{
  template<class T, class U>
  BOOST_DISPATCH_FORCE_INLINE
  typename boost::enable_if< meta::is_simd_specific<U, typename T::extension_type>, T const&>::type
  native_cast( U const& u )
  {
    BOOST_MPL_ASSERT_MSG( meta::is_native<T>::value, BOOST_SIMD_NATIVE_CAST_TARGET_NOT_NATIVE, (T) );
     BOOST_MPL_ASSERT_MSG( sizeof(T) == sizeof(U), BOOST_SIMD_NATIVE_CAST_TARGET_NOT_SAME_SIZE_AS_SOURCE, (T, U) );
    
    return reinterpret_cast<T const&>(u);
  }
  
  template<class T, class U>
  BOOST_DISPATCH_FORCE_INLINE
  typename boost::disable_if< meta::is_simd_specific<U, typename T::extension_type>, T const&>::type
  native_cast( U const& u )
  {
   
//     typedef typename meta::scalar_of<T>::type sT;
//     typedef typename meta::scalar_of<U>::type sU;
//     BOOST_MPL_ASSERT_MSG(   (meta::is_logical<sT>::value && meta::is_logical<sU>::value)
//                          || (!meta::is_logical<sT>::value && !meta::is_logical<sU>::value)
//                         , BOOST_SIMD_NATIVE_CAST_LOGICAL_MISMATCH
//                         , (sT, sU)
//                         );

        BOOST_MPL_ASSERT_MSG( sizeof(T) == sizeof(U), BOOST_SIMD_NATIVE_CAST_TARGET_NOT_SAME_SIZE_AS_SOURCE, (T, U) );
    
    return reinterpret_cast<T const&>(u);
  }

} }

#endif
