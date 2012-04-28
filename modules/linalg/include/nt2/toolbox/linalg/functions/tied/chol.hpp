//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_CHOL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TIED_CHOL_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/chol.hpp>
#include <nt2/options.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/toolbox/linalg/functions/factorizations/chol.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of chol is called whenever a tie(a,p) = chol(...) is captured
  // before assign is resolved. AS a tieable function, chol retrieves fusion
  // Sequences and static nargin/nargout as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chol_, tag::cpu_
                            , (ARGIN)(ARGOUT)(NARGIN)(NARGOUT)
                            , (fusion_sequence_<ARGIN>)
                              (fusion_sequence_<ARGOUT>)
                              (mpl_integral_<scalar_<unspecified_<NARGIN> > > )
                              (mpl_integral_<scalar_<unspecified_<NARGOUT> > >)
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::fusion::result_of::at_c<ARGOUT,0>::type dest_t;
    typedef typename meta::
            call< nt2::tag::
                  factorization::chol_(dest_t,char,nt2::details::in_place_)
                >::type                                             fact_t;

    BOOST_FORCEINLINE result_type
    operator()( ARGIN const& argin    , ARGOUT const& argout
              , NARGIN const&  nargin , NARGOUT const& nargout
              ) const
    {
      // Retrieve the up/lo options
      char ul = uplo(argin, nargin);

      // Copy data in output first
      boost::fusion::at_c<0>(argout) = boost::fusion::at_c<0>(argin);

      // Factorize in place
      fact_t t = factorization::chol(boost::fusion::at_c<0>(argout),ul,in_place_);

      // Retrieve correct version with minimum amount of (re)allocation
      if(ul == 'U') boost::fusion::at_c<0>(argout) = t.upper_result();
      else          boost::fusion::at_c<0>(argout) = t.lower_result();

      // Retrieve status
      status(argout, nargout, t.status());
    }

    private:
    //==========================================================================
    // INTERNAL ONLY
    // Extract a 'U' or a 'L' from lower_/upper_ or mpl::void_
    //==========================================================================
    BOOST_FORCEINLINE char uplo(ARGIN const&, boost::mpl::long_<1> const&) const
    {
      return 'U';
    }

    BOOST_FORCEINLINE char uplo(ARGIN const& in, boost::mpl::long_<2> const&) const
    {
      return boost::proto::value(boost::fusion::at_c<1>(in));
    }

    //==========================================================================
    // INTERNAL ONLY
    // If nargout is 2, fill the status
    //==========================================================================
    template<class Status> BOOST_FORCEINLINE
    void status(ARGOUT&, boost::mpl::long_<1> const&, Status const& ) const {}

    template<class Status> BOOST_FORCEINLINE
    void status(ARGOUT& o, boost::mpl::long_<2> const&, Status const& t) const
    {
      boost::proto::value(boost::fusion::at_c<1>(o)) = t;
    }
  };
} }

#endif
