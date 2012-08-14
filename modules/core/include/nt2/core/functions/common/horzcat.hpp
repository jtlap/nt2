/*//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_HORZCAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_HORZCAT_HPP_INCLUDED

#include <nt2/core/functions/horzcat.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/enumerate.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::horzcat_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename boost::dispatch::meta::
            call<nt2::tag::run_ ( typename  boost::proto::result_of::
                                            child_c<A0&, 0>::type
                                , State&, Data&
                                )
                >::type                                        base_type;

    typedef typename meta::strip<base_type>::type               result_type;
    typedef typename meta::as_integer<result_type>::type                i_t;
    typedef typename meta::call<nt2::tag::ind2sub_(of_size_max,State)>::type  sub_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      of_size_max ex0 = boost::proto::child_c<0>(a0).extent();
      sub_t pos = ind2sub(a0.extent(),p);
      if(size_t(pos[1]) <= ex0[1]) // this is in the a0 part
        {
          State pp = sub2ind(ex0, pos);
          return nt2::run(boost::proto::child_c<0>(a0),pp,t);
        }
      else // this is in the a1 part
        {
          of_size_max ex1 = boost::proto::child_c<1>(a0).extent();
          pos[1] -= ex0[1];
          State pp = sub2ind(ex1, pos);
          return nt2::run(boost::proto::child_c<1>(a0),pp,t);
        }
    }
  };

} }

#endif
*/
