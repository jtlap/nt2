//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_DCSUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_DCSUM_HPP_INCLUDED

#include <nt2/core/functions/dcsum.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/functions/csort.hpp>
#include <nt2/include/functions/ifloor.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/tocomplex.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( dcsum_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>)) )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 a0)
                          , nt2::dcsum(a0,firstnonsingleton(a0))
                          );
  };


  BOOST_DISPATCH_IMPLEMENT  ( dcsum_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename A0::value_type                                  type_t;
    typedef container::table<type_t>                            result_type;
    typedef typename meta::as_real<type_t>::type                    rtype_t;
    typedef container::table<rtype_t>                                rtab_t;
    typedef typename meta::is_complex<type_t>::type              is_cmplx_t;
    BOOST_FORCEINLINE result_type operator()(A0& a0, const A1& n) const
    {
      if (size(a0, n) <= 1) return a0;
      return do_sum(a0, n, is_cmplx_t());
    }
  private:
    template < class A >
    BOOST_FORCEINLINE rtab_t do_sum(A const& a, const A1& n, const boost::mpl::false_ &) const
    {
      auto cmp = [](rtype_t aa, rtype_t bb){return nt2::abs(bb) < nt2::abs(aa); }; //sort by decreasing order
      container::table<rtype_t> x =  csort(a,cmp,n);
      container::table<rtype_t> s =  along(x,1,n);
      container::table<rtype_t> c =  zeros(s.extent(), meta::as_<rtype_t>());
      container::table<rtype_t> y(s.extent());
      container::table<rtype_t> t(s.extent());
      container::table<rtype_t> v(s.extent());
      container::table<rtype_t> z(s.extent());
      container::table<rtype_t> u(s.extent());

      for(std::size_t k = 2; k <=  size(x, n); ++k)
      {
        y = c+along(x,k,n);
        u = along(x,k,n)-(y-c);
        t = y+s;
        v = y-(t-s);
        z = u+v;
        s = t+z;
        c = z-(s-t);
      }
      return s;
    }

    template < class A >
    BOOST_FORCEINLINE result_type do_sum(A const& a, const A1& n, const boost::mpl::true_ &) const
    {
      return nt2::tocomplex( do_sum(real(a), n, boost::mpl::false_())
                           , do_sum(imag(a), n, boost::mpl::false_()));
    }
  };

} }

#endif
