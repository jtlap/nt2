//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_FACTORIZATIONS_SCHUR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_FACTORIZATIONS_SCHUR_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/schur.hpp>
#include <nt2/options.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/toolbox/linalg/functions/details/schur.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::schur_, tag::cpu_
                              , (A0)(A1)(A2)(A3)
                              , (ast_<A0>)
                              (scalar_< type8_<A1> >)
                              (scalar_< type8_<A2> >)
                              (scalar_< type8_<A3> >)
                             )
  {
    typedef typename meta::strip<A0>::type                               base_t;
    typedef typename base_t::value_type                                 value_t;
    typedef typename base_t::settings_type                           settings_t;
    typedef details::schur_result< table<value_t,settings_t> >      result_type;

    BOOST_FORCEINLINE result_type
      operator()(A0 const& a0,
                 A1 const & jobvs,
                 A2 const & sort,
                 A3 const & sense) const
    {
      BOOST_ASSERT_MSG(is_square(a0), "Error using schur. Matrix must be square.");
      result_type that(a0, jobvs, sort, sense);
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::schur_, tag::cpu_
                              , (A0)(A1)(A2)(A3)(IP)
                            , (ast_<A0>)
                              (scalar_< type8_<A1> >)
                              (scalar_< type8_<A2> >)
                              (scalar_< type8_<A3> >)
                              (unspecified_< IP >)
                            )
  {
    typedef details::schur_result<A0&>       result_type;

    BOOST_FORCEINLINE result_type
      operator()(A0& a0,
                 A1 const & jobvs,
                 A2 const & sort,
                 A3 const & sense,
                 IP const&)
    {
      BOOST_ASSERT_MSG(is_square(a0), "Error using schur. Matrix must be square.");
      result_type that(a0, jobvs, sort, sense);
      return that;
    }
  };
} }

#endif
