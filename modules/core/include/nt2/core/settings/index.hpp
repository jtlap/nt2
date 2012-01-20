/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_SETTINGS_INDEX_HPP_INCLUDED
#define NT2_CORE_SETTINGS_INDEX_HPP_INCLUDED

#include <nt2/core/settings/forward/index.hpp>
#include <nt2/core/settings/option.hpp>

namespace nt2 
{ 
  namespace meta
  {
    //==========================================================================
    // Make options extracting the ID from id_
    //==========================================================================
    template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,std::ptrdiff_t I)
            , class Default
            >
    struct option < index_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,I)>
                  , tag::index_, Default
                  >
    {    
      typedef index_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,I)>  type;
    };
  }   
}

#endif
