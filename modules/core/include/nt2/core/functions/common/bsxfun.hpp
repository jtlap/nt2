//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_BSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_BSXFUN_HPP_INCLUDED

#include <nt2/core/functions/bsxfun.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/min.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::bsxfun_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename boost::dispatch::meta::
      call<nt2::tag::run_ ( typename  boost::proto::result_of::
                            child_c<A0&, 0>::type
                            , State&, Data&
                            )
      >::type                                        base_type1;
    typedef typename boost::dispatch::meta::
      call<nt2::tag::run_ ( typename  boost::proto::result_of::
                            child_c<A0&, 1>::type
                            , State&, Data&
                            )
      >::type                                        base_type2;
    typedef typename boost::proto::result_of::
            value< typename boost::proto::result_of::
                   child_c<A0&, 2>::type
                 >::value_type                           func_t;
   
    typedef typename boost::dispatch::meta::
      result_of < func_t( base_type1, base_type2)
      >::type                                        base_type;
    typedef typename meta::strip<base_type>::type               result_type;
    
    typedef typename meta::as_integer<result_type>::type                i_t;
    typedef typename boost::proto::result_of::child_c<A0&, 0>::value_type::extent_type     ext1t_t;
    typedef typename boost::proto::result_of::child_c<A0&, 1>::value_type::extent_type     ext2t_t;
    typedef typename meta::strip<ext1t_t>::type  ext1_t;
    typedef typename meta::strip<ext2t_t>::type  ext2_t; 
    typedef typename  make_size<(ext1_t::static_size > ext2_t::static_size)
                 ? ext1_t::static_size
                 : ext2_t::static_size>::type                                                ext_t;
  
    typedef typename meta::call<nt2::tag::ind2sub_(ext_t,State)>::type  sub_t;
  BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      func_t f =   boost::proto::value(boost::proto::child_c<2>(a0));
      ext1_t ex0 = boost::proto::child_c<0>(a0).extent();
      ext2_t ex1 = boost::proto::child_c<1>(a0).extent();
      sub_t pos0 = ind2sub(a0.extent(),p);
      sub_t pos1 = pos0; 
      for(int i = 0; i != ext_t::size(); ++i)
        {
          pos0[i] = nt2::min(ex0[i], size_t(pos0[i]));
          pos1[i] = nt2::min(ex1[i], size_t(pos1[i]));
        }
      State p0 = sub2ind(ex0, pos0);
      State p1 = sub2ind(ex1, pos1);
      return f(nt2::run(boost::proto::child_c<0>(a0), p0, t), 
               nt2::run(boost::proto::child_c<1>(a0), p1, t)
               ); 
    }
  };

} }

#endif
