/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include "buffer_test.hpp"
#include <nt2/sdk/memory/container.hpp>

#define NT2_CONTAINER_EXP(T,N)                                        \
NT2_RUN_EXPERIMENT_TPL( buffer_test                                   \
                      , ((nt2::memory::container<T,nt2::settings()>)) \
                      , (1 << N)                                      \
                      )                                               \
/**/

NT2_CONTAINER_EXP(double , 2);
NT2_CONTAINER_EXP(double , 4);
NT2_CONTAINER_EXP(double , 8);
NT2_CONTAINER_EXP(double , 16);

NT2_CONTAINER_EXP(float , 2);
NT2_CONTAINER_EXP(float , 4);
NT2_CONTAINER_EXP(float , 8);
NT2_CONTAINER_EXP(float , 16);

NT2_CONTAINER_EXP(char , 2);
NT2_CONTAINER_EXP(char , 4);
NT2_CONTAINER_EXP(char , 8);
NT2_CONTAINER_EXP(char , 16);
