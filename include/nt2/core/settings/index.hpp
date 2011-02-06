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

#include <cstddef>
#include <boost/mpl/vector_c.hpp>
#include <nt2/extension/parameters.hpp>
#include <nt2/core/settings/meta/option.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

////////////////////////////////////////////////////////////////////////////////
// Defines index options
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace options
{
  struct index_ { typedef void nt2_is_option_type; };
} }

////////////////////////////////////////////////////////////////////////////////
// Helper macros
////////////////////////////////////////////////////////////////////////////////
#define M0(z,n,t) ptrdiff_t BOOST_PP_CAT(I,BOOST_PP_INC(n)) = BOOST_PP_CAT(I,n)

////////////////////////////////////////////////////////////////////////////////
// index<I0,..,In> represents the base index over the Nth dimensions. By default
// index<I0,I1> is equivalent to index<I0,I1,I1,...,I1>.
// Indexes data are stored in a mpl::vector_c of proper size.
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
  template< std::ptrdiff_t I0 = 1
          , BOOST_PP_ENUM(BOOST_PP_DEC(NT2_MAX_DIMENSIONS),M0,~)
          >
  struct  index
        : BOOST_PP_CAT(BOOST_PP_CAT(boost::mpl::vector,NT2_MAX_DIMENSIONS),_c)
          <std::ptrdiff_t, BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,I)>
  {};
}

////////////////////////////////////////////////////////////////////////////////
// Register index_ has a valid options::index_ type
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,std::ptrdiff_t I)
          , class Default
          >
  struct option < index<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,I)>
                , options::index_
                , Default
                , void
                >
  {
    typedef index<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,I)> type;
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Defines some usual short-cut for C and Matlab base indexing
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
  typedef index<0> C_index_;
  typedef index<1> matlab_index_;
}

////////////////////////////////////////////////////////////////////////////////
// Macros clean-up
////////////////////////////////////////////////////////////////////////////////
#undef M0

#endif
