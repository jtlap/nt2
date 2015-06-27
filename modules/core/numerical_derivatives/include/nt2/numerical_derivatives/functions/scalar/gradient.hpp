//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_NUMERICAL_DERIVATIVES_FUNCTIONS_SCALAR_GRADIENT_HPP_INCLUDED
#define NT2_NUMERICAL_DERIVATIVES_FUNCTIONS_SCALAR_GRADIENT_HPP_INCLUDED

#include <nt2/numerical_derivatives/functions/gradient.hpp>
#include <nt2/include/functions/backward.hpp>
#include <nt2/include/functions/centered.hpp>
#include <nt2/include/functions/forward.hpp>
#include <nt2/include/functions/vand.hpp>
#include <nt2/numerical_derivatives/options.hpp>
#include <utility>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/if.hpp>
#include <nt2/sdk/meta/as_real.hpp>


namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( gradient_, tag::cpu_
                            , (F)(X)(M)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (unspecified_<M>)
                            )
  {
    typedef decltype(std::declval<F>()(std::declval<X>())) v_type;
    typedef typename meta::as_real<v_type>::type           r_type;
    typedef typename boost::mpl::if_<boost::is_same<M, tag::vand_>
                                     , r_type
                                     , v_type>::type result_type;
    BOOST_FORCEINLINE
    result_type operator()(const F &f, const X& x, const M& ) const
    {
      return functor<M>()(f, x);
    }
  };
  BOOST_DISPATCH_IMPLEMENT  ( gradient_, tag::cpu_
                            , (F)(X)(M)(P)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (unspecified_<M>)
                              (unspecified_<P>)
                            )
  {
    typedef decltype(std::declval<F>()(std::declval<X>())) v_type;
    typedef typename meta::as_real<v_type>::type           r_type;
    typedef typename boost::mpl::if_<boost::is_same<M, tag::vand_>
                                     , r_type
                                     , v_type>::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(const F &f, const X& x, const M& , const P& ) const
    {
      return compute(f, x, M(), P());
    }
  private :
    static BOOST_FORCEINLINE result_type compute(const F &f, const X & x
                                                , const M&, const P&)
    {
      return functor<M>()(f, x, P());
    }
    static BOOST_FORCEINLINE result_type compute(const F &f, const X & x
                                                , const tag::vand_&, const P&)
    {
      return functor<M>()(f, x);
    }
  };

} }

#endif
