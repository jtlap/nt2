//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_BANDWIDTH_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_BANDWIDTH_HPP_INCLUDED
#include <nt2/linalg/functions/bandwidth.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/linalg/options.hpp>
#include <boost/assert.hpp>
#include <utility>
namespace nt2{ namespace ext
{

  //============================================================================
  //BANDWIDTH Scalar
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( bandwidth_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef std::size_t result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& ) const
    {
      return 0;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( bandwidth_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
     typedef std::size_t result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& , const A1&) const
    {
      return 0;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( bandwidth_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((unspecified_<A1>))
                            )
  {
    typedef std::size_t result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1 const &) const
    {
      BOOST_ASSERT_MSG(ismatrix(a0), "input is not a matrix");
      BOOST_AUTO_TPL(t,if_zero_else(is_eqz(a0),
                                    bsxfun(nt2::functor<tag::minus_>()
                                          , colvect(_(1, int(height(a0))))
                                          , _(1, int(width(a0))))
                                   )
                    );
      return eval(t, A1());
    }
  private :
    template < class T >
    BOOST_FORCEINLINE
    size_t eval(T & t,  nt2::policy<ext::lower_>) const
    {
      return globalmax(t);
    }
    template < class T >
    BOOST_FORCEINLINE
    size_t eval(T & t,  nt2::policy<ext::upper_>) const
    {
      return globalmax(-t);
    }

  };

  BOOST_DISPATCH_IMPLEMENT   ( bandwidth_, tag::cpu_
                             , (A0)
                             , ((ast_<A0, nt2::container::domain>))
                             )
  {
    typedef typename meta::as_integer<A0, signed>::type itype_t;
    typedef std::pair<itype_t, itype_t>             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      BOOST_ASSERT_MSG(ismatrix(a0), "input is not a matrix");
      BOOST_AUTO_TPL(t,if_zero_else(is_eqz(a0),
                                    bsxfun(nt2::functor<tag::minus_>()
                                          , colvect(_(1, int(height(a0))))
                                          , _(1, int(width(a0))))
                                   )
                    );
      return std::make_pair(globalmax(t),globalmax(-t));
    }
  };
} }


#endif
