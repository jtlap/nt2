//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_RANK_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_RANK_HPP_INCLUDED
#include <nt2/linalg/functions/rank.hpp>
#include <nt2/include/functions/scalar/rank.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/inbtrue.hpp>
#include <nt2/include/functions/gt.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/gesvd.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2{ namespace ext
{
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rank_, tag::cpu_,
                                (A0)
                                ,((ast_<A0, nt2::container::domain>))
                                )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
    typedef size_t result_type;
    typedef nt2::container::table<type_t>  entry_type;
    typedef nt2::container::table<type_t,shape>  matrix_type;
    typedef nt2::container::table<rtype_t>  base_type;

    NT2_FUNCTOR_CALL(1)
    {
      entry_type u,v;
      base_type s;
      matrix_type work(a0);

      nt2_la_int  m  = nt2::height(work);
      nt2_la_int  n  = nt2::width(work);

      s.resize(nt2::of_size(std::min(m,n), 1));

      nt2::gesvd( boost::proto::value(work), boost::proto::value(s)
                , boost::proto::value(u), boost::proto::value(v),'N','N');

      type_t epsi = nt2::max(n, m)*nt2::eps(s(1));

      return size_t(inbtrue(gt(s, epsi)));
    }
  };
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rank_, tag::cpu_,
                                (A0)(A1)
                                ,((ast_<A0, nt2::container::domain>))
                                (scalar_<floating_<A1 > >)
                                )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename meta::option<typename A0::settings_type,nt2::tag::shape_>::type shape;
    typedef size_t result_type;
    typedef nt2::container::table<type_t>  entry_type;
    typedef nt2::container::table<type_t,shape>  matrix_type;
    typedef nt2::container::table<rtype_t>  base_type;

    NT2_FUNCTOR_CALL(2)
    {
      entry_type u,v;
      base_type s;
      matrix_type work(a0);
      type_t epsi = a1;

      nt2_la_int  m  = nt2::height(work);
      nt2_la_int  n  = nt2::width(work);

      s.resize(nt2::of_size(std::min(m,n), 1));

      nt2::gesvd( boost::proto::value(work), boost::proto::value(s)
                , boost::proto::value(u), boost::proto::value(v),'N','N');

      epsi =  (epsi < 0) ?  nt2::max(n, m)*nt2::eps(s(1)): epsi;

      return size_t(sum(if_one_else_zero(gt(s, epsi))(_)));;
    }
  };

} }


#endif
