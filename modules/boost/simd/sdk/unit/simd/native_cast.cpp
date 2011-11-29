/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::native_cast"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/include/functions/genmask.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

// namespace boost { namespace simd
// {
//   template < class T, class U,
// 	     class ISLT = typename meta::is_logical<T>::type,
// 	     class ISLU = typename meta::is_logical<U>::type > struct convert; 

//   template < class T, class U > struct convert < T, U, 
// 	     boost::mpl::true_,
// 	     boost::mpl::true_>
//   {
//     static inline const T& do_convert(const U& u)
//     {
//       return reinterpret_cast<T const&>(u);
//     }
//   };
//   template < class T, class U > struct convert < T, U, 
// 	     boost::mpl::false_,
// 	     boost::mpl::false_>
//   {
//     static inline const T& do_convert(const U& u)
//     {
//       return reinterpret_cast<T const&>(u);
//     }
//   };
//   template < class T, class U > struct convert < T, U, 
// 	     boost::mpl::true_,
// 	     boost::mpl::false_>
//   {
//     static inline const T& do_convert(const U& u)
//     {
//       typedef typename meta::as_logical<U>::type lU; 
//       return convert<T,lU>::do_convert(is_nez(u));
//     }
//   };
//   template < class T, class U > struct convert < T, U, 
// 	     boost::mpl::false_,
// 	     boost::mpl::true_>
//   {
//     static inline const T& do_convert(const U& u)
//     {
//       typedef typename U::type nU; 
//       return convert<T,nU>::do_convert(genmask(u));
//     }
//   };

  
//   using boost::simd::meta::is_logical; 
//   template<class T, class U>
//   BOOST_DISPATCH_FORCE_INLINE
//   T const&  nat_cast( U const& u )
//   {
//     BOOST_MPL_ASSERT_MSG( meta::is_native<T>::value, BOOST_SIMD_NATIVE_CAST_TARGET_NOT_NATIVE, (T) );
//     BOOST_MPL_ASSERT_MSG( sizeof(T) == sizeof(U), BOOST_SIMD_NATIVE_CAST_TARGET_NOT_SAME_SIZE_AS_SOURCE, (T, U) );
    
//     return convert<T, U>::do_convert(u);
//   }
// } }
////////////////////////////////////////////////////////////////////////////////
// Test native_cast
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(native_cast, BOOST_SIMD_SIMD_TYPES )
{
  using boost::simd::native;
  using boost::simd::native_cast;
  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>   vT;
  typedef typename boost::simd::meta::as_logical<T>::type  slT;
  typedef typename boost::simd::meta::as_logical<vT>::type  lvT;
  //  typedef boost::simd::int32_t T1;
  typedef T T1; 
  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>   vT1;
  typedef typename boost::simd::meta::as_logical<T1>::type  slT1;
  typedef typename boost::simd::meta::as_logical<vT1>::type  lvT1; 
  {
    vT  x = boost::simd::One<vT>();
    vT1 y;
    y = native_cast<vT1 >(x);
    std::cout << x << " -> " << y << std::endl; 
  }
  {
    vT  x = boost::simd::One<vT>();
    lvT1 y;
    y = native_cast<lvT1>(x);
    std::cout << x << " -> " << y << std::endl; 
  }
   {
    lvT  x= boost::simd::True<vT>();
    lvT1 y;
    y = native_cast<lvT1>(x);
    std::cout << x << " -> " << y << std::endl; 
  }
  {
    lvT  x= boost::simd::True<vT>();
    vT1 y;
    y = native_cast<vT1>(x);
    std::cout << x << " -> " << y << std::endl; 
  }
}
