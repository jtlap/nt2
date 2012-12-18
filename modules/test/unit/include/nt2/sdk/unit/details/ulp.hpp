//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_ULP_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_ULP_HPP_INCLUDED

#include <nt2/sdk/unit/config.hpp>
#include <nt2/include/functions/value.hpp>
#include <nt2/sdk/unit/details/is_sequence.hpp>
#include <nt2/sdk/unit/details/smallest_type.hpp>

#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <algorithm>

namespace nt2 { namespace details
{
  /// Default implementation of max_ulps forward to generic ulpdist
  template<class A,class B>
  BOOST_FORCEINLINE double max_ulps(A const& a, B const& b )
  {
    return (a<b) ? b-a : a-b;
  }

  /// Precompiled implementation max_ulps on double
  NT2_TEST_UNIT_DECL double max_ulps(double a, double b);

  /// Precompiled implementation max_ulps on float
  NT2_TEST_UNIT_DECL double max_ulps(float  a, float  b);

  /// Perform a test of equality on A and B with a given ulp tolerance
  /// Detects if A and/or B is actually a sequence and apply max_ulps on
  /// every elements of said sequences
  template< class A, class B
          , bool IsASeq=nt2::details::is_sequence<A>::value
          , bool IsBSeq=nt2::details::is_sequence<B>::value
          >
  struct max_ulp_
  {
    typedef double result_type;

    /// Main operator() checks of A and B are Fusion Sequence then
    /// jump into the proper eval() member functions depending on this
    /// status.
    BOOST_FORCEINLINE result_type operator()(A const& a, B const& b) const
    {
      return eval ( a , b
                  , boost::mpl::
                    bool_ < boost::fusion::traits::is_sequence<A>::value
                        &&  boost::fusion::traits::is_sequence<B>::value
                          >()
                  );
    }

    /// A and B are not Fusion Sequence, just call max_ulps
    BOOST_FORCEINLINE
    result_type eval(A const& a, B const& b,boost::mpl::false_ const&) const
    {
      return max_ulps ( nt2::details::smallest_a(nt2::value(a),nt2::value(b))
                      , nt2::details::smallest_b(nt2::value(a),nt2::value(b))
                      );
    }

    /// A and B are Fusion Sequence, call max_ulps on every elements and
    /// compute the maximum
    BOOST_FORCEINLINE
    result_type eval(A const& a, B const& b,boost::mpl::true_ const&) const
    {
      return eval ( a , b, 0
                  , typename boost::fusion::result_of::size<A>::type()
                  );
    }

    BOOST_FORCEINLINE bool
    eval(A const& a, B const& b, double z, boost::mpl::int_<1> const&) const
    {
      return std::max ( z
                      , max_ulps ( nt2::details
                                   ::smallest_a ( boost::fusion::at_c<0>(a)
                                                , boost::fusion::at_c<0>(b)
                                                )
                                  , nt2::details
                                    ::smallest_b( boost::fusion::at_c<0>(a)
                                                , boost::fusion::at_c<0>(b)
                                                )
                                  )
                      );
    }

    template<class N>
    BOOST_FORCEINLINE bool
    eval(A const& a, B const& b, double z,N const&) const
    {
      return eval ( a , b
                  , std::max( z
                            , max_ulps ( nt2::details::
                                         smallest_a ( boost::fusion::at_c<0>(a)
                                                    , boost::fusion::at_c<0>(b)
                                                    )
                                        , nt2::details::
                                          smallest_b( boost::fusion::at_c<0>(a)
                                                    , boost::fusion::at_c<0>(b)
                                                    )
                                        )
                            )
                  ,typename boost::mpl::prior<N>::type()
                  );
    }
  };

  /// Both A and B are sequence, so we iterate over elements using the single
  /// value version of max_ulp_
  template<class A, class B>
  struct max_ulp_< A, B, true,true>
  {
    typedef double result_type;

    BOOST_FORCEINLINE result_type operator()(A const& a, B const& b) const
    {
      result_type res = 0;

      typename A::const_iterator ab = a.begin();
      typename A::const_iterator ae = a.end();
      typename B::const_iterator bb = b.begin();

      while(ab != ae)
      {
        res = std::max( res
                      , max_ulp_< typename A::value_type
                                , typename B::value_type
                                >()(*ab,*bb)
                      );
        ab++;
        bb++;
      }

      return res;
    }
  };

  /// A is a sequence while B is not, this means B has exactly one element
  template<class A, class B>
  struct max_ulp_< A, B, true, false>
  {
    typedef double result_type;

    BOOST_FORCEINLINE result_type operator()(A const& a, B const& b) const
    {
      return  max_ulp_<typename A::value_type,B>()(*a.begin(),b)
          &&  (std::distance(a.begin(),a.end()) == 1);
    }
  };

/// B is a sequence while A is not, this means B has exactly one element
  template<class A, class B>
  struct max_ulp_< A, B, false, true>
  {
    typedef double result_type;

    BOOST_FORCEINLINE result_type operator()(A const& a, B const& b) const
    {
      return  max_ulp_<A, typename B::value_type>()(a,*b.begin())
          &&  (std::distance(b.begin(),b.end()) == 1);
    }
  };
} }

namespace nt2 { namespace unit
{
  /// INTERNAL ONLY Main test for equality over any types A and B within a
  /// given ulp tolerance
  template<class A, class B>
  BOOST_FORCEINLINE double max_ulp(A const& a, B const& b)
  {
    return details::max_ulp_<A,B>()(a,b);
  }
} }

#endif
