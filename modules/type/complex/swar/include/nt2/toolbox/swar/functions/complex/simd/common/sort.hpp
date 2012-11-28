//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMPLEX_COMMON_SORT_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMPLEX_COMMON_SORT_HPP_INCLUDED
//TO DO
#include <nt2/toolbox/swar/functions/sort.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/store.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>

#include <algorithm>

// namespace nt2 { namespace ext
// {
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sort_, tag::cpu_
//                             , (A0)(X)
//                             , ((simd_<arithmetic_<A0>,X>))
//                             )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL(1)
//     {
//       //  When X is complex, the elements are sorted by ABS(X).  Complex
//       //  matches are further sorted by ANGLE(X).TO DO
//        typedef typename meta::scalar_of<A0>::type stype;
//       static const size_t size = nt2::meta::cardinal_of<A0>::value;
//       NT2_ALIGNED_TYPE(stype) tmp[size];
//       store(a0, &tmp[0], 0);
//       std::sort(tmp, tmp + size);
//       return load<A0>(&tmp[0], 0);
//     }
//   };
//  } }


#endif
