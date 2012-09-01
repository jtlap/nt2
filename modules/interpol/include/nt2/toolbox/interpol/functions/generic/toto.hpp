/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTERPOL_FUNCTIONS_GENERIC_TOTO_HPP_INCLUDED
#define NT2_TOOLBOX_INTERPOL_FUNCTIONS_GENERIC_TOTO_HPP_INCLUDED
/////////////////////////////////////////////////////////////////////
/// by          : J. Falcou and J.T. Lapresté                                                                                            
/// description :
///  Perform a binary search of an array of values.
///  The parameters index_lo and index_hi provide an initial bracket,                                                    
///  and it is assumed that index_lo < index_hi. The resulting index                                                     
///  is guaranteed to be strictly less than index_hi and greater than                                                    
///  or equal to index_lo, so that the implicit bracket [index, index+1]                                         
///  always corresponds to a region within the implicit value range of                                           
///  the value array.                                                                                                                                       
///  Note that this means the relationship of 'x' to xx(index)                                                           
///  and xx(index+1) depends on the result region, i.e. the                                                                      
///  behaviour at the boundaries may not correspond to what you                                                                          
///  expect. We have the following complete specification of the                                                                         
///  behaviour.
///  Suppose the input is xx = { x0, x1, ..., xN }                                                                                                       
///     if ( x == x0 )           then  index == 0
///     if ( x > x0 && x <= x1 ) then  index == 0, and sim. for other interior pts 
///     if ( x == xN )           then  index == N-1
///     if ( x > xN )            then  index == N-1
///     if ( x < x0 )            then  index == 0
/////////////////////////////////////////////////////////////////////
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/is_nge.hpp>
#include <nt2/include/functions/is_nle.hpp>
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

namespace nt2 { namespace ext
{
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)
                              , (ast_<A0>)
                              ((node_<A1,nt2::tag::toto_,boost::mpl::long_<2> >))
                              )
  {
    typedef A0& result_type;
    
    result_type operator()(A0& xout, A1& inputs) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,0>::type        child0;
      typedef typename boost::proto::result_of::child_c<A1&,1>::type        child1;
      xout.resize(inputs.extent()); 
      const child0 & p  =  boost::proto::child_c<0>(inputs);
      const child1 & xin  =  boost::proto::child_c<1>(inputs);
      xout =  xin+p; 
      return xout;
    }
  }; 
} }

#endif
