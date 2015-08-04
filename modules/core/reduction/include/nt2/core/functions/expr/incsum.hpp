//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_INCSUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_INCSUM_HPP_INCLUDED

#include <nt2/core/functions/incsum.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/functions/csort.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/tocomplex.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/options.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( incsum_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 a0)
                          , nt2::incsum(a0,firstnonsingleton(a0))
                          );
  };

  BOOST_DISPATCH_IMPLEMENT  ( incsum_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1>>)
                            )

  {
    typedef typename A0::value_type                                  type_t;
    typedef container::table<type_t>                            result_type;
    typedef typename meta::as_real<type_t>::type                    rtype_t;
    typedef container::table<rtype_t>                                rtab_t;
    typedef typename meta::is_complex<type_t>::type              is_cmplx_t;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0
                                            , const A1& n) const
    {
      return do_sum(a0, n, is_cmplx_t());
    }
  private:
    template < class A >
    BOOST_FORCEINLINE result_type do_sum(A const& a, const A1& n
                                        , const boost::mpl::false_ &) const
    {
      //sort by decreasing order
      auto cmp = [](rtype_t aa, rtype_t bb){return aa < bb; };
      container::table<rtype_t> x = csort(a,cmp,n);
      return sum(x, n);
    }

    template < class A >
    BOOST_FORCEINLINE result_type do_sum(A const& a, const A1 n
                                        , const boost::mpl::true_ &) const
    {
      return nt2::tocomplex( do_sum(real(a), n, boost::mpl::false_())
                           , do_sum(imag(a), n, boost::mpl::false_()));
    }

  };
} }

#endif
