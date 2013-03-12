//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_INVHILB_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_INVHILB_HPP_INCLUDED
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/round.hpp>

namespace nt2{ namespace ext
{
 //
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::invhilb_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_< scalar_< unspecified_<T> > >)
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::invhilb_
      , container::domain
      , size_t
      , T
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             T  const&) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::invhilb_, container::domain>
        ( size_t(a0)
          , T()
          , boxify(sizee)
          );
    }
  };

  //2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::invhilb_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::invhilb_
      , container::domain
      , size_t
      , meta::as_<double>
      , box<_2D>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::invhilb_, container::domain>
        ( size_t(a0)
          , meta::as_<double>()
          , boxify(sizee)
          );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::invhilb_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,1>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  boost::dispatch::meta::semantic_of<tmp1_type>::type tmp2_type;
    typedef typename  tmp2_type::type                                    value_type;
    result_type operator()(A0& out, const A1& in) const
    {
      size_t n = boost::proto::child_c<0>(in);
      out.resize(nt2::of_size(n, n));
      value_type p = n;
      value_type r = nt2::sqr(p);
      out(1, 1) = r;
      for(size_t j = 2; j <= n; ++j)
      {
        r =  -((n-j+1)*r*(n+j-1))/nt2::sqr(j-1);
        out(1,j) = r/j;
        out(j,1) = out(1, j);
      }
      for(size_t i = 2; i <= n; ++i)
      {
        p = ((n-i+1)*p*(n+i-1))/nt2::sqr(i-1);
        r = nt2::sqr(p);
        out(i,i) = r/(2*i-1);
        for(size_t j = i+1; j <= n; ++j)
        {
          r = -((n-j+1)*r*(n+j-1))/nt2::sqr(j-1);
          out(i,j) = r/(i+j-1);
          out(j,i) = out(i, j);
        }
      }
      return out = nt2::round(out);
    }
  };
} }


#endif
