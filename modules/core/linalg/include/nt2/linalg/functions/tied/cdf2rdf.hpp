//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TIED_CDF2RDF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TIED_CDF2RDF_HPP_INCLUDED

#include <nt2/linalg/functions/cdf2rdf.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/globalany.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/is_not_equal.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/colon/colon.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( cdf2rdf_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& ) const
    {
      return a0;
    }
  };

  //============================================================================
  //Eig computations
  //============================================================================
  BOOST_DISPATCH_IMPLEMENT  ( cdf2rdf_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::cdf2rdf_
                                    , N0, nt2::container::domain
                                      >
                              ))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type    child0;
    typedef typename child0::value_type                                     type_t;
    typedef typename nt2::meta::as_real<type_t>::type                      rtype_t;
    typedef typename nt2::meta::as_complex<rtype_t>::type                  ctype_t;
    typedef nt2::memory::container<tag::table_, rtype_t, nt2::_2D> desired_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - [v, w] = cdf2rdf(cv, cw)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      NT2_AS_TERMINAL_OUT  (desired_semantic,  v, boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT  (desired_semantic,  w, boost::proto::child_c<1>(a1));
      auto i = find(imag(diag_of(cw)));
      auto index = i(_(1u, 2u, length(i)));
      if isempty(index)
      {
        boost::proto::child_c<0>(a0) = real(cv);
        boost::proto::child_c<1>(a0) = real(cw);
        return;
      }
      BOOST_ASSERT_MSG((globalmax(index)==size(cw,1)) || globalany(neq(conj(cw(index,index), cw(index+1,index+1)))));
      table<ctype_t> ct = eye(length(d), meta::as_<ctype_t>());
      table<ctype_t> twobytwo =  cons<ctype_t>(One<ctype_t>, I<ctype_t>(), One<ctype_t>(), -I<ctype_t>());
      auto i2 = _(0u, 1u);
      for(i : index)
      {
        ct(i2+i, i2+i) = twobytwo;
      }
      boost::proto::child_c<0>(a0) = real(linsolve(cv, ct));
      boost::proto::child_c<1>(a0) = real(linsolve(cw, ct));
    }



  };
} }

#endif


