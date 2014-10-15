//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_TRANS33_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_TRANS33_HPP_INCLUDED

#include <nt2/linalg/functions/trans33.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/swap.hpp>
#include <nt2/include/functions/trans33.hpp>
#include <nt2/core/container/dsl.hpp>
#include <boost/mpl/assert.hpp>


namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trans33_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                              )
  {
    typedef typename A0::value_type value_type;
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 & a0) const
    {
      BOOST_ASSERT_MSG(nt2::width(a0) == 3 && nt2::height(a0) == 3, "input is not a 3x3 matrix");
      nt2::swap(a0(1, 2), a0(2, 1));
      nt2::swap(a0(1, 3), a0(3, 1));
      nt2::swap(a0(2, 3), a0(3, 2));
    }
  };

} }

#endif
