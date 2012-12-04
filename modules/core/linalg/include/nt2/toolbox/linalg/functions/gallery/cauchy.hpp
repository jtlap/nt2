/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_CAUCHY_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_CAUCHY_HPP_INCLUDED
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/toolbox/linalg/functions/cauchy.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauchy_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename meta::call<tag::rowvect_(A1)>::type                     T0;
    typedef typename meta::call<tag::colvect_(A0)>::type                     T1;
    typedef typename meta::call<tag::bsxfun_( nt2::functor<tag::plus_>
                                            , T0, T1) >::type                T2;
    typedef typename meta::call<tag::rec_(T2)>::type                result_type;
    NT2_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG( numel(a0) == numel(a1)
                      , "a0 and a1 doesn' have the same number of elements"
                      );

      return rec(bsxfun(nt2::functor<tag::plus_>(), rowvect(a1), colvect(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauchy_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename meta::call<tag::cauchy_(A0, A0)>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return cauchy(a0, a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauchy_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<integer_<A0> >)((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename A1::value_type value_type;
    typedef typename meta::call<tag::colon_(value_type, value_type)>::type T0;
    typedef typename meta::call<tag::cauchy_(T0, A1)>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return cauchy(colon(value_type(1), value_type(a0)), a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauchy_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::call<tag::colon_(value_type, value_type)>::type T1;
    typedef typename meta::call<tag::cauchy_(A0, T1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return cauchy(a0, colon(value_type(1), value_type(a1)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauchy_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_<scalar_<floating_<A2> > > )
                            )
  {
    typedef typename A2::type value_type;
    typedef typename meta::call<tag::colon_(value_type, value_type)>::type T1;
    typedef typename meta::call<tag::cauchy_(T1, T1)>::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 const& a1, A2 const& ) const
    {
      return cauchy ( colon(value_type(1), value_type(a0))
                    , colon(value_type(1), value_type(a1))
                    );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauchy_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<integer_<A0> >)
                              (target_<scalar_<floating_<A1> > > )
                            )
  {
    typedef A1 value_type;
    typedef typename meta::call<tag::colon_(value_type, value_type)>::type T1;
    typedef typename meta::call<tag::cauchy_(T1, T1)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return cauchy ( colon(value_type(1), value_type(a0))
                    , colon(value_type(1), value_type(a0))
                    );
    }
  };
} }

#endif
