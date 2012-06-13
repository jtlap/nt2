/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_PINV_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_PINV_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/pinv.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/svd.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pinv_, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef typename A0::value_type       value_type;
    typedef typename A0::index_type       index_type;
    typedef table<value_type, index_type> result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return  nt2::details::svd_result<A0>(a0, 'A', 'A').pinv();
    }
  };
} }

#endif
