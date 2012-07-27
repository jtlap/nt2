//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_CAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_CAT_HPP_INCLUDED

#include <nt2/core/functions/cat.hpp>
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
                            , ((node_<A0, nt2::tag::cat_, N>))
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
      size_t along =  boost::proto::child_c<2>(a0);
      of_size_max ex0 = boost::proto::child_c<0>(a0).extent();
      of_size_max ex1 = boost::proto::child_c<1>(a0).extent();
      sub_t pos0 = ind2sub(a0.extent(),p);
      i_t p0 = nt2::enumerate<i_t>(pos0[0]);
      if (along == 0)
        { //this is vertcat
          sub_t pos1 = pos0;  pos1[0] -= ex0[0];
          i_t h0 = nt2::splat    <i_t>(ex0[0]);
          return if_else(le(p0, h0), // are we in the upper or lower part (a0 or a1)
                         nt2::run(boost::proto::child_c<0>(a0),sub2ind(ex0, pos0),t),
                         nt2::run(boost::proto::child_c<1>(a0),sub2ind(ex1, pos1),t)
                         );
        }
      else
        { //these are the other cases
          if(size_t(pos0[along]) <= ex0[along]) // this is in the a0 part
            {
              State pp = sub2ind(ex0, pos0);
              return nt2::run(boost::proto::child_c<0>(a0),pp,t);
            }
          else // this is in the a1 part
            {
              pos0[along] -= ex0[along];
              State pp = sub2ind(ex1, pos0);
              return nt2::run(boost::proto::child_c<1>(a0),pp,t);
            }
        }
    }
  };

} }

#endif
