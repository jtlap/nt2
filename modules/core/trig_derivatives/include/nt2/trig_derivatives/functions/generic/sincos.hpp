//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_SINCOS_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_GENERIC_SINCOS_HPP_INCLUDED
#include <nt2/include/functions/simd/sincos.hpp>
#include <nt2/include/functor.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/functions/simd/sincos.hpp>
#include <nt2/include/functions/swap.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( sincos_, tag::cpu_
                            , (order)(A0)
                            , (unspecified_<order>)
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                            )
  {
    typedef void result_type;
    typedef typename boost::mpl::long_<order::value % 4>     ordermod4;
    BOOST_FORCEINLINE result_type operator()(const order&,
                                             A0 const& a0, A0 & a1, A0 & a2) const
    {
      sincos(a0, a1, a2);
      compute(order(), a1, a2);
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
        v = -v;
      }
      BOOST_FORCEINLINE void compute(const boost::mpl::long_<2>
                                           ,  A0& u
                                           ,  A0& v) const
      {
        u = -u;
        v = -v;
      }
      BOOST_FORCEINLINE void compute(const boost::mpl::long_<3>
                                           , A0& u
                                           , A0& v) const
      {
        nt2::swap(u, v);
        u = -u;
      }
  };

  BOOST_DISPATCH_IMPLEMENT  ( sincos_
                            , tag::cpu_
                            , (order)(A0)
                            , (unspecified_<order>)
                              ((generic_< floating_<A0> >))
                              ((generic_< floating_<A0> >))
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const order&
                                            ,A0 const& a0,A0 & a2) const
    {
      A0 a1;
      sincos(order(), a0, a1, a2);
      return a1;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( sincos_, tag::cpu_
                            , (order)(A0)
                            , (unspecified_<order>)
                              (unspecified_<order>)
                              (generic_< floating_<A0> >)
                            )
  {
    typedef std::pair<A0, A0>                      result_type;
    BOOST_FORCEINLINE result_type operator()(const order&
                                            , A0 const& a0) const
    {
      A0 a1, a2;
      sincos(order(), a0, a1, a2);
      return result_type(a1, a2);
    }
  };


} }


#endif
