//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_REALLOG_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_REALLOG_HPP_INCLUDED

#include <nt2/toolbox/exponential/functions/reallog.hpp>
#include <nt2/toolbox/exponential/functions/log.hpp>
#include <nt2/include/functions/is_nltz.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>

// namespace nt2 { namespace ext
// {
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::reallog_, tag::cpu_
//                               , (A0)(X)
//                               , ((simd_< arithmetic_<A0>,X >))
//                               )
//   {

//     typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

//     NT2_FUNCTOR_CALL(1)
//     {
//       BOOST_ASSERT_MCG(nt2::all(nt2::is_nltz(a0)), "reallog cannot produce complex result.");
//       return nt2::log(tofloat(a0));
//     }
//   };
// } }

#endif
