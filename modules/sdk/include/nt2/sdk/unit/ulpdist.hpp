/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
// #ifndef NT2_SDK_UNIT_DETAILS_ULPDIST_HPP_INCLUDED
// #define NT2_SDK_UNIT_DETAILS_ULPDIST_HPP_INCLUDED
// #include <nt2/sdk/constant/eps_related.hpp>

// namespace nt2
// {
//   namespace details {
    
//     struct other_ {};
//     struct double_{};
//     struct float_ {}; 
//     template < class T > T nt2_ulpdist(T a0, T a1,  double_ )
//     {
//       typedef int32_t itype;
//       typedef T   type; 
//       if (a0 == a1)              return Zero<type>();
//       if ((a0!=a0) && (a1!= a1)) return Zero<type>();
//       itype e1 = 0, e2 = 0;
//       double m1, m2;
//       ::frexp(a0, &e1);
//       ::frexp(a1, &e2);
//       itype expo = -(e1 > e2)?e1:e2;
//       type e = (e1 == e2) ?
// 	std::abs(m1-m2) :
// 	std::abs(::ldexp(a0, expo) - ::ldexp(a1, expo));
//       return e/nt2::Eps<type>();
//     }
    
//     template < class T > T nt2_ulpdist(T a0, T a1,  float_)
//     {
//       typedef int32_t itype;
//       typedef T   type; 
//       if (a0 == a1)              return Zero<type>();
//       if ((a0!=a0) && (a1!= a1)) return Zero<type>();
//       itype e1 = 0, e2 = 0;
//       double m1, m2;
//       ::frexpf(a0, &e1);
//       ::frexpf(a1, &e2);
//       itype expo = -(e1 > e2)?e1:e2;
//       type e = (e1 == e2) ?
// 	std::abs(m1-m2) :
// 	std::abs(::ldexpf(a0, expo) - ::ldexpf(a1, expo));
//       return e/Eps<type>();
//     }
    
//     template < class T > T nt2_ulpdist(T a0, T a1,  other_)
//     {
//       return a0 > a1 ? a0-a1 : a1-a0; 
//     }
    
//     template <class T> struct classif  { typedef   other_ type; };
//     template <> struct classif<double> { typedef  double_ type; };
//     template <> struct classif<float>  { typedef   float_ type; };
//   }    

//   template < class T > T  nt2_ulpdist(T a0, T a1)
//   {
//     typedef typename meta::strip<T>::type type; 
//     return nt2_ulpdist(type(a0), type(a1), typename details::classif<T>::type()); 
//   }

// }
// #endif

// /////////////////////////////////////////////////////////////////////////////
// End of ulpdist.hpp
// /////////////////////////////////////////////////////////////////////////////
