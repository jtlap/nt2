//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ISINSIDE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ISINSIDE_HPP_INCLUDED

#include <nt2/core/functions/isinside.hpp>
#include <nt2/core/container/category.hpp>
#include <boost/fusion/adapted/mpl.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isinside_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (ast_<A1>)
                            )
  {
    typedef typename meta::strip<A1>::type                          base_t;
    typedef typename base_t::extent_type                            ext_t;
    typedef typename base_t::indexes_type                           idx_t;
    typedef typename  meta::call
                      < nt2::tag::isinside_(A0&,ext_t,idx_t)>::type result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0,const A1& a1) const
    {
      return isinside(a0,a1.extent(),a1.indexes());
    }
  };
} }

#endif
