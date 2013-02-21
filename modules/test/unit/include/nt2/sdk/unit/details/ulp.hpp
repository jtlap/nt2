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
#include <boost/foreach.hpp>
#include <algorithm>
#include <vector>

namespace nt2 { namespace details
{
  /// Hold which value was faulty and by how much
  template<class A, class B> struct failed_value
  {
    A           value;
    B           desired_value;
    double      ulp_error;
    std::size_t index;
  };

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
  /// Detects if A and/or B is actually a Fusion sequence or not
  template< class A, class B
          , bool IsAFusionSeq=boost::fusion::traits::is_sequence<A>::value
          , bool IsBFusionSeq=boost::fusion::traits::is_sequence<A>::value
          >
  struct max_ulp_value_;

  /// A and B are not Fusion Sequence, call max_ulps on the value
  template< class A, class B>
  struct max_ulp_value_<A,B,false,false>
  {
    typedef failed_value<A,B> failure_type;

    template<class VF>
    BOOST_FORCEINLINE double
    operator()( A const& a, B const& b
              , double max_ulpd, VF& fails, std::size_t i
              ) const
    {
      double d = max_ulps ( nt2::details::smallest_a( nt2::value(a)
                                                    , nt2::value(b)
                                                    )
                          , nt2::details::smallest_b( nt2::value(a)
                                                    , nt2::value(b)
                                                    )
                          );

      if(d > max_ulpd )
      {
        failure_type f = { a, b, d, i };
        fails.push_back(f);
      }

      return d;
    }
  };

  /// A and B are Fusion Sequence, call max_ulps on every elements and
  /// compute the maximum
  template< class A, class B>
  struct max_ulp_value_<A,B,true,true>
  {
    template<int I, int N> struct max_ulp_seq_
    {
      template<class X, class Y>
      BOOST_FORCEINLINE double
      operator()( X const& a, Y const& b, double z ) const
      {
        return max_ulp_seq_<I+1,N>()
              ( a , b
              , std::max( z
                        , max_ulps( nt2::details::
                                    smallest_a( boost::fusion::at_c<I>(a)
                                              , boost::fusion::at_c<I>(b)
                                              )
                                  , nt2::details::
                                    smallest_b( boost::fusion::at_c<I>(a)
                                              , boost::fusion::at_c<I>(b)
                                              )
                                  )
                        )
              );
      }
    };

    template<int N> struct max_ulp_seq_<N,N>
    {
      template<class X, class Y>
      BOOST_FORCEINLINE double
      operator()( X const&, Y const&, double z ) const
      {
        return z;
      }
    };

    typedef failed_value<A,B> failure_type;

    template<class VF>
    BOOST_FORCEINLINE double
    operator()( A const& a, B const& b
              , double max_ulpd, VF& fails, std::size_t i
              ) const
    {
      double d =  max_ulp_seq_<0,boost::fusion::result_of
                                              ::size<A>::value>()(a,b,0.);

      if(d > max_ulpd)
      {
        failure_type f = {a, b, d, i};
        fails.push_back(f);
      }

      return d;
    }
  };

  /// Perform a test of equality on A and B with a given ulp tolerance
  /// Detects if A and/or B is actually a sequence and apply max_ulps on
  /// every elements of said sequences
  template< class A, class B
          , bool IsASeq=nt2::details::is_sequence<A>::value
          , bool IsBSeq=nt2::details::is_sequence<B>::value
          >
  struct max_ulp_
  {
    typedef typename max_ulp_value_<A,B>::failure_type failure_type;

    /// Main operator() checks of A and B are Fusion Sequence then
    /// jump into the proper eval() member functions depending on this
    /// status.
    template<class VF>
    BOOST_FORCEINLINE double
    operator()( A const& a, B const& b
              , double max_ulpd, VF& fails, std::size_t i
              ) const
    {
      return max_ulp_value_<A,B>()(a, b, max_ulpd, fails, i);
    }
  };

  /// Both A and B are sequence, so we iterate over elements using the single
  /// value version of max_ulp_
  template<class A, class B>
  struct max_ulp_< A, B, true,true>
  {
    typedef failed_value< typename A::value_type
                        , typename B::value_type
                        >                         failure_type;

    template<class VF>
    BOOST_FORCEINLINE double
    operator()( A const& a, B const& b
              , double max_ulpd, VF& fails, std::size_t i
              ) const
    {
      double res = 0;

      typename A::const_iterator ab = a.begin();
      typename A::const_iterator ae = a.end();
      typename B::const_iterator bb = b.begin();

      while(ab != ae)
      {
        res = std::max( res
                      , max_ulp_< typename A::value_type
                                , typename B::value_type
                                >()(*ab,*bb,max_ulpd,fails,i++)
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
    typedef failed_value<typename A::value_type, B> failure_type;

    template<class VF>
    BOOST_FORCEINLINE double
    operator()( A const& a, B const& b
              , double max_ulpd, VF& fails, std::size_t i
              ) const
    {
      BOOST_ASSERT_MSG( (std::distance(a.begin(),a.end()) == 1)
                      , "Sequence is not of size 1"
                      );
      return max_ulp_<typename A::value_type,B>() ( *a.begin(),b
                                                  , max_ulpd,fails,i
                                                  );
    }
  };

  /// B is a sequence while A is not, this means B has exactly one element
  template<class A, class B>
  struct max_ulp_< A, B, false, true>
  {
    typedef failed_value<A, typename B::value_type> failure_type;

    template<class VF>
    BOOST_FORCEINLINE double
    operator()( A const& a, B const& b
              , double max_ulpd, VF& fails , std::size_t i
              ) const
    {
      BOOST_ASSERT_MSG( (std::distance(b.begin(),b.end()) == 1)
                      , "Sequence is not of size 1"
                      );
      return  max_ulp_<A, typename B::value_type>() ( a,*b.begin()
                                                    , max_ulpd,fails,i
                                                    );
    }
  };
} }

namespace nt2 { namespace unit
{
  /// INTERNAL ONLY Main test for equality over any types A and B within a
  /// given ulp tolerance
  template<class A, class B, class VF>
  BOOST_FORCEINLINE
  double max_ulp( A const& a, B const& b, double max_ulpd, VF& fails )
  {
    return details::max_ulp_<A,B>()(a,b,max_ulpd,fails,0);
  }
} }

#endif
