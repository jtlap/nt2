//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_SCHUR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_SCHUR_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/schur.hpp>
#include <nt2/toolbox/linalg/functions/factorizations/schur.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of schur is called whenever a tie(a,p) = schur(...) is captured
  // before assign is resolved. As a tieable function, schur retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::schur_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::schur_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type          in0;
    typedef typename meta::strip<in0>::type                           strip_in0;
    typedef typename strip_in0::value_type                           value_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename meta::
            call< nt2::tag::
                  factorization::schur_(child0,char,char,char,nt2::details::in_place_)
                >::type                                             fact_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      typedef typename nt2::meta::is_complex<value_type>::type choice_t;
      // Retrieve the lapack schur relevant options options
      char sort = 'N';
      char jobvs = (N1::value == 1) ? 'N' : 'V';
      char sense =  'N';
      // Copy data in output first
      child0 & out = boost::proto::child_c<0>(a1);
      prepare(a0, a1, out, N0(), choice_t());
      // Factorize in place
      fact_t f = factorization::schur(boost::proto::child_c<0>(a1),jobvs,sort,sense,in_place_);
      decomp(f, a1, N1());

    }

  private:
    //==========================================================================
    // INTERNAL ONLY
    // prepare the output
    //==========================================================================
    BOOST_FORCEINLINE
    void prepare(A0 & a0, A1 & a1,
                 child0 & out, boost::mpl::long_<1> const&, boost::mpl::true_ const &) const
    {
      in0 & in     = boost::proto::child_c<0>(a0);
      out.resize(extent(in));
      for(size_t i=1; i <= numel(in); ++i)
      {
        out(i) = value_type(in(i)); //TODO a cast
      }
    }
    BOOST_FORCEINLINE
    void prepare(A0 & a0, A1 & a1,
                 child0 & out, boost::mpl::long_<1> const&, boost::mpl::false_ const &) const
    {
      out = boost::proto::child_c<0>(a0);
    }

    template < class S >
    BOOST_FORCEINLINE
    void prepare(A0 & a0, A1 & a1,
                 child0 & out, boost::mpl::long_<2> const&, S const &) const
    {
      typedef typename boost::proto::result_of::child_c<A0&,1>::type         in1_t;
      typedef typename meta::strip<in1_t>::type                             sin1_t;
      typedef typename sin1_t::value_type                                   v_type;
      prepare(a0, a1, out, boost::mpl::long_<1>(), boost::mpl::true_());
    }

    //==========================================================================
    // INTERNAL ONLY
    // If nargout is 2, fill the status
    //==========================================================================
    BOOST_FORCEINLINE
    void decomp(fact_t & f, A1 & a1, boost::mpl::long_<1> const&) const
    {
       boost::proto::child_c<0>(a1) = f.t();
    }

    BOOST_FORCEINLINE
    void decomp(fact_t & f, A1 & a1, boost::mpl::long_<2> const&) const
    {
      boost::proto::child_c<0>(a1) = f.z();
      boost::proto::child_c<1>(a1) = f.t();
    }
  };
} }

#endif
