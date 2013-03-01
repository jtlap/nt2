//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_CTRANS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_CTRANS_HPP_INCLUDED

#include <nt2/core/functions/ctrans.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/conj.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ctrans_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>)) )
  {
     BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
                            (nt2::trans(nt2::conj(a0)))
                           )
       };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ctrans_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >) )
  {
     BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
                            (nt2::conj(a0))
                           )
       };
} }

#endif
