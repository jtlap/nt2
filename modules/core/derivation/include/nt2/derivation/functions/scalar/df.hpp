//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DERIVATION_FUNCTIONS_SCALAR_DF_HPP_INCLUDED
#define NT2_DERIVATION_FUNCTIONS_SCALAR_DF_HPP_INCLUDED

#include <nt2/derivation/functions/df.hpp>
#include <nt2/include/functions/backward.hpp>
#include <nt2/include/functions/centered.hpp>
#include <nt2/include/functions/forward.hpp>
#include <nt2/include/functions/vand.hpp>
#include <nt2/derivation/options.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( df_, tag::cpu_
                            , (F)(X)(M)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (unspecified_<M>)
                            )
  {
    typedef X result_type;

    BOOST_FORCEINLINE
    result_type operator()(const F &f, const X& x, const M& ) const
    {
      return functor<M>()(f, x);
    }
  };
  BOOST_DISPATCH_IMPLEMENT  ( df_, tag::cpu_
                            , (F)(X)(M)(P)
                            , (unspecified_<F>)
                              (scalar_<floating_<X> >)
                              (unspecified_<M>)
                              (unspecified_<P>)
                            )
  {
    typedef X result_type;

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
