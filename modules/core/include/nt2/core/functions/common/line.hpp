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
    typedef typename meta::call<nt2::tag::ind2sub_(ext_t,State)>::type  sub_t;
    typedef typename meta::strip<result_type>::type                 base_type;
    typedef typename meta::as_integer<base_type,unsigned>::type          id_t;
  BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      ext_t ex0 = boost::proto::child_c<0>(a0).extent();
      size_t ind =  boost::proto::child_c<2>(a0);
      size_t dim =  boost::proto::child_c<1>(a0);
//       size_t fact = (dim == 0)? ex0[0] : 1u; 
//       for(int i=2; i < dim; ++i) fact*= ex0[i];
      size_t fact = factoralong(ex0, dim); 
      size_t dist = nextalong(ex0, dim);  
//       std::cout << "dim " << dim <<  std::endl;
//       std::cout << "dist "<< dist <<  std::endl; 
//       std::cout << "fact "<< fact <<  std::endl;   
//       std::cout << "p   " << p   <<  std::endl;
//       std::cout << "ind " << ind <<  std::endl;  
//       sub_t pos0;
//       for(int i=0; i < sub_t::size(); ++i) pos0[i] = 1; //TO DO Have a memcopy do it
//       pos0[dim] = ind*fact+p-1; 
//       State p1 = sub2ind(ex0, pos0);
      State p1 = (ind-1)*fact+p*dist; 
      return nt2::run(boost::proto::child_c<0>(a0), nt2::arith<id_t>(p1, dist), t);
    }
  
  static size_t nextalong(const ext_t& ex,  const size_t& along)
    {
      size_t r = 1u; 
      if (along == 0) return r;
      for(int i=1; i <= along; ++i) r*= ex[i-1];
      return r; 
    }
  static size_t factoralong(const ext_t& ex,  const size_t& along)
    {
      size_t r =  (along == 0)? ex[0] : 1u;  
      if (along <= 1) return r; 
      for(int i=2; i < along; ++i) r*= ex[i];
      return r; 
    }

  
  };

} }

#endif
