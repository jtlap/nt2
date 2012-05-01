/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_INV_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_INV_HPP_INCLUDED
#include <nt2/include/functions/inv.hpp>
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/table.hpp>

namespace nt2{ namespace ext 
{
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inv_, tag::cpu_,
                                       (A0)
                                       ,((ast_<A0>))
                                   )
  {
    typedef typename A0::value_type value_type;
    typedef typename A0::index_type index_type; 
    typedef table<value_type, index_type> result_type; 
    NT2_FUNCTOR_CALL(1)
      {
        BOOST_ASSERT_MSG(issquare(a0), "inverse of non square matrix requested"); 
        return  nt2::details::lu_result<A0>(a0).inv(false);        
      }
  };

} }


#endif
