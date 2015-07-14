//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_GENERIC_SINHCOSH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_GENERIC_SINHCOSH_HPP_INCLUDED
#include <nt2/hyp_derivatives/include/functions/sinhcosh.hpp>
#include <nt2/include/functor.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/functions/simd/sinhcosh.hpp>
#include <nt2/include/functions/swap.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( sinhcosh_, tag::cpu_
                            , (order)(A0)(A1)(A2)
                            , (unspecified_<order>)
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A1> >))
                              ((generic_< floating_<A2> >))
                            )
  {
    typedef void result_type;
    typedef typename boost::mpl::long_<order::value % 2>     ordermod2;
    BOOST_FORCEINLINE result_type operator()(const order,
                                             A0 const& a0, A1 & a1, A1 & a2) const
    {
      sinhcosh(a0, a1, a2);
      compute(ordermod2(), a1, a2);
    }
    private:
      BOOST_FORCEINLINE void compute(const boost::mpl::long_<0>
                                           , A1&
                                           , A2& ) const
      { }
      BOOST_FORCEINLINE void compute(const boost::mpl::long_<1>
                                           ,A1& u
                                           ,A2& v) const
      {
        nt2::swap(u, v);
      }
  };

  BOOST_DISPATCH_IMPLEMENT  ( sinhcosh_
                            , tag::cpu_
                            , (order)(A0)(A2)
                            , (unspecified_<order>)
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A2> >))
                            )
  {
    typedef A0 result_type;
    typedef typename boost::mpl::long_<order::value % 2>     ordermod2;
    BOOST_FORCEINLINE result_type operator()(const order&
                                            ,A0 const& a0,A2 & a2) const
    {
      A0 a1;
      a1 = sinhcosh(a0, a2);
      compute(ordermod2(), a1, a2);
      return a1;
    }
  private:
    BOOST_FORCEINLINE void compute(const boost::mpl::long_<0>
                                  , A0&
                                  , A2& ) const
    { }
    BOOST_FORCEINLINE void compute(const boost::mpl::long_<1>
                                  ,A0& u
                                  ,A2& v) const
    {
      nt2::swap(u, v);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( sinhcosh_, tag::cpu_
                            , (order)(A0)
                            , (unspecified_<order>)
                              (generic_< floating_<A0> >)
                            )
  {
    typedef std::pair<A0, A0>                      result_type;
    typedef typename boost::mpl::long_<order::value % 2>     ordermod2;
    BOOST_FORCEINLINE result_type operator()(const order&
                                            , A0 const& a0) const
    {
      A0 a1, a2;
      sinhcosh(a0, a1, a2);
      compute(ordermod2(), a1, a2);
      return result_type(a1, a2);
    }
  private:
    BOOST_FORCEINLINE void compute(const boost::mpl::long_<0>
                                  , A0&
                                  , A0& ) const
    { }
    BOOST_FORCEINLINE void compute(const boost::mpl::long_<1>
                                  ,A0& u
                                  ,A0& v) const
    {
      nt2::swap(u, v);
    }
  };


} }


#endif
