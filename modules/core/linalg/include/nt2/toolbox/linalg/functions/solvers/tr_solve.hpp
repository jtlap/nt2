//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_SOLVERS_TR_SOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_SOLVERS_TR_SOLVE_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/tr_solve.hpp>
#include <nt2/options.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/istril.hpp>
#include <nt2/include/functions/istriu.hpp>
#include <nt2/include/functions/ofsameheight.hpp>
#include <nt2/toolbox/linalg/functions/details/tr_solve.hpp>
#include <nt2/sdk/error/warning.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::solvers::tr_solve_, tag::cpu_
                              , (A0)(A1)(A2)(A3)(A4)
                              , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_<type8_< A2> >)
                              (scalar_<type8_< A3> >)
                              (scalar_<type8_< A4> >)
                            )
  {
    typedef typename meta::strip<A0>::type                              base_t;
    typedef typename base_t::value_type                                value_t;
    typedef typename base_t::settings_type                          settings_t;
    typedef details::tr_solve_result< table<value_t,settings_t> >  result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a,
                                             A1 const& b,
                                             A2 const & uplo, 
                                             A3 const & trans, 
                                             A4 const & diag) const
    {
      NT2_DISPLAY(a);
      NT2_DISPLAY(b);
      
      BOOST_ASSERT_MSG((ofsameheight(a, b)&&(trans == 'N'))||((size(a, 2) == size(b, 1))&&(trans != 'N')),
                       "a and b have different heights");
      result_type that(a, b, uplo, trans, diag);
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::solvers::tr_solve_, tag::cpu_
                              , (A0)(A1)(A2)(A3)(A4)(IP)
                              , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_<type8_< A2> >)
                              (scalar_<type8_< A3> >)
                              (scalar_<type8_< A4> >)
                              (unspecified_< IP >)
                              )
  {
    typedef details::tr_solve_result<A0&, A1&> result_type;
    BOOST_FORCEINLINE result_type operator()  (A0& a,
                                               A1& b,
                                               A2 const & uplo,
                                               A3 const & trans, 
                                               A4 const & diag,  
                                               IP const &) const
    {
      NT2_DISPLAY(a);
      NT2_DISPLAY(b);
      BOOST_ASSERT_MSG((ofsameheight(a, b)&&(trans == 'N'))||((size(a, 2) == size(b, 1))&&(trans != 'N')),
                       "a and b have different heights");
//       NT2_WARNING(istril(a)&&(uplo == 'L'),
//                   "a is not lower triangular, but only the lower part of the matrix will be used");
//       NT2_WARNING(istriu(a)&&(uplo == 'U'),
//                   "a is not upper triangular, but only the upper part of the matrix will be used");
      result_type that(a, b, uplo, trans, diag);
      return that;
    }
  };
} }

#endif
