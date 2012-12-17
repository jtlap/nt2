//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_INTEGRATION_OPTIONS_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_OPTIONS_HPP_INCLUDED

#include <cstddef>
#include <nt2/sdk/option/options.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/table.hpp>
namespace nt2
{
  /**
   * Named parameter for passing number of iterations to iterative algortihms
   **/
//  NT2_REGISTER_PARAMETERS(iterations_);
  /**
   * Named parameter for passing number of function evaluation to iterative algortihms
   **/
//  NT2_REGISTER_PARAMETERS(evaluations_);

  namespace tolerance
  {
    /**
     * Named parameter for passing absolute tolerance to iterative algorithms
     **/
    NT2_REGISTER_PARAMETERS(abstol_);

    /**
     * Named parameter for passing relative tolerance to iterative algorithms
     **/
    NT2_REGISTER_PARAMETERS(reltol_);
//   }

//   namespace limits
//   {
    /**
     * Named parameter for passing absolute tolerance to iterative algorithms
     **/
    NT2_REGISTER_PARAMETERS(maxintvcnt_);

    /**
     * Named parameter for passing relative tolerance to iterative algorithms
     **/
    NT2_REGISTER_PARAMETERS(maxfunccnt_);
  }

  template<typename T, typename TAG = void> struct integ_params
  {
    typedef T value_type;
    static value_type abstol() { return nt2::Sqrteps<value_type>(); }
    static value_type reltol() { return nt2::Sqrteps<value_type>(); }
    static std::size_t maxfunccnt() { return 10000; }
    static std::size_t maxintvcnt() { return   650; }
  };

  // integ params for complex < T >  are those of T.
  template<class T, template < class > class V, typename TAG>
  struct integ_params < V<T>, TAG> :
  integ_params<T, TAG>{};

}

namespace nt2 { namespace details
{
  // INTERNAL ONLY
  // integration_settings gather the classical set of settings required
  // for an integration process from either the list of values or from an
  // options pack expressions
  template<typename T, typename TAG = void> struct integration_settings
  {
    typedef typename meta::as_real<T>::type real_type;
    typedef T value_type;
    typedef nt2::integ_params<value_type, TAG>               ip;

    integration_settings ( std::size_t    mfc = ip::maxfunccnt()
                           ,  std::size_t mic = ip::maxintvcnt()
                           , value_type at    = ip::abstol()
                           , value_type rt    = ip::reltol()
      )
      : maxfunccnt(mfc)
      , maxintvcnt(mic)
      , abstol(at)
      , reltol(rt)
    {}

    template<class Expr>
    integration_settings ( nt2::details::option_expr<Expr> const& x)
      : maxfunccnt(x(nt2::tolerance::maxfunccnt_, ip::maxfunccnt() ))
      , maxintvcnt(x(nt2::tolerance::maxintvcnt_, ip::maxintvcnt() ))
      , abstol    (x(nt2::tolerance::abstol_,  ip::abstol()     ))
      , reltol    (x(nt2::tolerance::reltol_,  ip::reltol()     ))

    {
      std::cout << "icitte" << std::endl;
      std::cout << "ip::maxfunccnt() " << ip::maxfunccnt()<< std::endl;
      std::cout << "ip::maxintvcnt() " << ip::maxintvcnt()<< std::endl;
      std::cout << "ip::abstol()     " << ip::abstol()    << std::endl;
      std::cout << "ip::reltol()     " << ip::reltol()    << std::endl;
    }
    void display_options() const
    {
      std::cout << "maxfunccnt "<< maxfunccnt << std::endl;
      std::cout << "maxintvcnt "<< maxintvcnt << std::endl;
      std::cout << "    abstol "<<     abstol << std::endl;
      std::cout << "    reltol "<<     reltol << std::endl;
    }
    std::size_t      maxfunccnt;
    std::size_t      maxintvcnt;
    value_type           abstol;
    value_type           reltol;
  };
} }

#endif
