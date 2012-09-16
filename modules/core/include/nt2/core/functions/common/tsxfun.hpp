//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_TSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_TSXFUN_HPP_INCLUDED

#include <nt2/core/functions/tsxfun.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/min.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::tsxfun_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename boost::proto::result_of::
                     child_c<A0&,0>::value_type                        child0_t;
    typedef typename boost::simd::ext::adapt_data<child0_t,Data>::type    ad0_t;

    typedef typename boost::proto::result_of::
                     child_c<A0&,1>::value_type                        child1_t;
    typedef typename boost::simd::ext::adapt_data<child1_t,Data>::type    ad1_t;

    typedef typename boost::proto::result_of::
                     child_c<A0&,2>::value_type                        child2_t;
    typedef typename boost::simd::ext::adapt_data<child1_t,Data>::type    ad2_t;

    typedef typename A0::extent_type                                      ext_t;
    typedef typename Data::type                                     result_type;

    typedef typename meta::as_index<result_type>::type                      i_t;
    typedef typename result_of::as_subscript<ext_t,i_t>::type               s_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Grab position and size for each children
      s_t pos0  = as_subscript(a0.extent(),enumerate<i_t>(p));
      ext_t sz0 = boost::proto::child_c<0>(a0).extent();
      ext_t sz1 = boost::proto::child_c<1>(a0).extent();
      ext_t sz2 = boost::proto::child_c<2>(a0).extent();
      s_t pos1  = pos0;
      s_t pos2  = pos0;

      // If you're a singleton, you're always the smallest
      for(std::size_t i = 0; i != ext_t::size(); ++i)
      {
        pos0[i] = nt2::min(splat<i_t>(sz0[i]-1u),pos0[i]);
        pos1[i] = nt2::min(splat<i_t>(sz1[i]-1u),pos1[i]);
        pos2[i] = nt2::min(splat<i_t>(sz2[i]-1u),pos2[i]);
      }

      // Call f on each value potential repeated
      return  boost::proto::value(boost::proto::child_c<3>(a0))
              ( run(boost::proto::child_c<0>(a0), as_index(sz0, pos0), ad0_t())
              , run(boost::proto::child_c<1>(a0), as_index(sz1, pos1), ad1_t())
              , run(boost::proto::child_c<2>(a0), as_index(sz2, pos2), ad2_t())
              );
    }
  };
} }

#endif
