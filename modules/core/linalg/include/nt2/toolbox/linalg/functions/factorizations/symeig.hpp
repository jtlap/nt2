//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_FACTORIZATIONS_SYMEIG_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_FACTORIZATIONS_SYMEIG_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/symeig.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/toolbox/linalg/functions/details/symeig.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::symeig_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_<A0>)
                                (scalar_< type8_<A1> >)
                                (scalar_< type8_<A2> >)
                              )
  {
    typedef typename meta::strip<A0>::type                            base_t;
    typedef typename base_t::value_type                              value_t;
    typedef typename base_t::settings_type                        settings_t;
    typedef details::symeig_result< table<value_t,settings_t> >      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const & jobz,
                                             A2 const & uplo) const
    {
      BOOST_ASSERT_MSG(issquare(a0), "Error using symeig. Matrix must be square.");
      result_type that(a0, jobz, uplo);
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::symeig_, tag::cpu_
                            , (A0)(A1)(A2)(IP)
                            , (ast_<A0>)
                              (scalar_< type8_<A1> >)
                              (scalar_< type8_<A2> >)
                              (unspecified_< IP >)
                            )
  {
    typedef details::symeig_result<A0&>       result_type;

    BOOST_FORCEINLINE result_type
      operator()(A0& a0,
                 A1 const & jobz,
                 A2 const & uplo,
                 IP const&)
    {
      BOOST_ASSERT_MSG(issquare(a0), "Error using symeig. Matrix must be square.");
      result_type that(a0, jobz, uplo);
      return that;
    }
  };
} }

#endif
