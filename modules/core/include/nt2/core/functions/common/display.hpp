//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_DISPLAY_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_DISPLAY_HPP_INCLUDED

#include <iostream>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::display_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef void result_type;

    result_type operator()(A0 const& a0) const
    {
      std::cout << "ans = \n" << a0 << std::endl;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::display_, tag::cpu_
                            , (A0)(A1)
                            , (unspecified_<A0>)
                              (unspecified_<A1>)
                            )
  {
    typedef void result_type;

    result_type operator()(A0 const& a0, A1 const& a1) const
    {
      std::cout << a0 << " = \n" << a1 << std::endl;
    }
  };
} }

#endif
