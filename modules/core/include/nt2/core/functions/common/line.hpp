//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_LINE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_LINE_HPP_INCLUDED

#include <nt2/core/functions/line.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/arith.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::line_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename boost::dispatch::meta::
      call<nt2::tag::run_ ( typename  boost::proto::result_of::
                            child_c<A0&, 0>::type
                            , State&, Data&
                            )
      >::type                                                     result_type;
    typedef typename A0::extent_type                                   extt_t;
    typedef typename meta::strip<extt_t>::type                          ext_t;
    //   typedef typename meta::call<nt2::tag::ind2sub_(ext_t,State)>::type  sub_t;
    typedef typename meta::strip<result_type>::type                 base_type;
    typedef typename meta::as_integer<base_type,unsigned>::type          id_t;
  BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      ext_t ex0 = boost::proto::child_c<0>(a0).extent();
      size_t dist  =  boost::proto::child_c<4>(a0);
      size_t start =  boost::proto::child_c<3>(a0);
      size_t ind =  boost::proto::child_c<2>(a0);
      size_t dim =  boost::proto::child_c<1>(a0);
 //      ext_t ex1 = ex0;
//       ex1[dim] = 1;
//       sub_t pos = ind2sub(ex1, ind);
//       State start = sub2ind(ex0, pos); 
      
      
//      size_t dist = nextalong(ex0, dim);  

      return nt2::run(boost::proto::child_c<0>(a0), nt2::arith<id_t>(start+p*dist, dist), t);
    }
  
//   static size_t nextalong(const ext_t& ex,  const size_t& along)
//     {
//       size_t r = 1u; 
//       if (along == 0) return r;
//       for(size_t i=1; i <= along; ++i) r*= ex[i-1];
//       return r; 
//     }
  };

} }

#endif
