//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SOBOL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SOBOL_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/include/constants/nbmantissabits.hpp>

#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_sobol sobol
 *   sobol(n) is an integer matrix containing a sobol sequence
 *   allowing to define quasi random numbers  fitted to Monte-Carlo
 *   integration up to dimension n.
 *   Currently n must be less or equal to 100.
 *   the type of the table element used to store the result is important,
 *   uint32_t or uint64_t will different sequences suited for respectively
 *   float and double quasi-random number sequence generation.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sobol.hpp>
 * \endcode
 *
 *
**/
//==============================================================================
// sobol actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag sobol_ of functor sobol
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct sobol_ :  ext::unspecified_<sobol_>
    {
      typedef ext::unspecified_<sobol_> parent;
    };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::sobol_, sobol, 1)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::sobol_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      sizee[1] = boost::proto::value(boost::proto::child_c<0>(e));
      sizee[0] = 23;
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::sobol_, Domain,N,Expr>
  {
    typedef uint32_t                 type;
  };
} }
#endif
