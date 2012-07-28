/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTERPOL_FUNCTIONS_GENERIC_LINEAR_HPP_INCLUDED
#define NT2_TOOLBOX_INTERPOL_FUNCTIONS_GENERIC_LINEAR_HPP_INCLUDED
#include <nt2/core/container/table/table.hpp>

#include <nt2/include/functions/is_nge.hpp>
#include <nt2/include/functions/is_nle.hpp>
#include <nt2/include/functions/bsearch.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/sdk/meta/type_id.hpp>

namespace nt2 { namespace ext
{
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N1)
                              , (ast_<A0>)
                              ((node_<A1,nt2::tag::linear_,N1>))
                              )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type        child0;
    typedef typename boost::proto::result_of::child_c<A1&,1>::type        child1;
    typedef typename boost::proto::result_of::child_c<A1&,2>::type        child2;
    typedef typename meta::scalar_of<child0>::type               cref_value_type;
    typedef typename meta::strip<cref_value_type>::type               value_type; 
    typedef typename meta::as_integer<value_type>::type               index_type;      
    typedef typename A0::value_type                                    sale_type; 
    typedef A0&                                                      result_type;
    
    result_type operator()(A0& yi, A1& inputs) const
    {
//        std::cout << "zut et zut " << nt2::type_id<sale_type>() << std::endl; 
//        std::cout << nt2::type_id(yi) << std::endl; 
       const child0 & x   =  boost::proto::child_c<0>(inputs);
       const child1 & y   =  boost::proto::child_c<1>(inputs);
       const child2 & xi  =  boost::proto::child_c<2>(inputs);
       bool extrap = false;
       value_type extrapval = Nan<value_type>();
       choices(inputs, extrap, extrapval, N1());
       table<index_type>   index = bsearch (x, xi);
//        NT2_DISPLAY(x); 
//        NT2_DISPLAY(xi); 
//        NT2_DISPLAY(index);
//        NT2_DISPLAY(x(index));
//        std::cout << nt2::type_id<value_type>() << std::endl; 
       table<value_type>  dx    =  xi-x(index); 
//        NT2_DISPLAY(dx);
       yi =  fma(oneminus(dx), y(index), dx*y(oneplus(index)));
//        NT2_DISPLAY(yi);
       if (!extrap) yi = nt2::if_else(logical_or(boost::simd::is_nge(xi, x(begin_)), boost::simd::is_nle(xi, x(end_))), extrapval, yi);
       return yi;
    } 
  private :
    static void choices(const A1&, bool &,  value_type&, boost::mpl::long_<3> const &)
      { }
    static void choices(const A1& inputs, bool & extrap,  value_type& extrapval, boost::mpl::long_<4> const &)
      {
        typedef typename boost::proto::result_of::child_c<A1&,3>::type             child3;
        typedef typename meta::scalar_of<child3>::type                    cref_param_type;
        typedef typename meta::strip<cref_param_type>::type                    param_type; 
        get(inputs, extrap, extrapval, param_type());         
      }
    static void get(const A1& inputs, bool & extrap,  value_type&,  const bool &)
      {
        extrap =  boost::proto::child_c<3>(inputs);
      }
    static void get(const A1& inputs, bool &,  value_type& extrapval,  const value_type &)
      {
        extrapval =  boost::proto::child_c<3>(inputs);
      }
  }; 
} }


#endif
