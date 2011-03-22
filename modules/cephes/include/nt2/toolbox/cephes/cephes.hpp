//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CEPHES_CEPHES_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_CEPHES_HPP_INCLUDED

//<include> please don't modify between these tags
#include <nt2/toolbox/cephes/include/chdtri.hpp>
#include <nt2/toolbox/cephes/include/chdtrc.hpp>
#include <nt2/toolbox/cephes/include/hyperg.hpp>
#include <nt2/toolbox/cephes/include/atan2.hpp>
#include <nt2/toolbox/cephes/include/kn.hpp>
#include <nt2/toolbox/cephes/include/yn.hpp>
#include <nt2/toolbox/cephes/include/spence.hpp>
#include <nt2/toolbox/cephes/include/beta.hpp>
#include <nt2/toolbox/cephes/include/bdtrc.hpp>
#include <nt2/toolbox/cephes/include/i0.hpp>
#include <nt2/toolbox/cephes/include/i1.hpp>
#include <nt2/toolbox/cephes/include/atan.hpp>
#include <nt2/toolbox/cephes/include/exp.hpp>
#include <nt2/toolbox/cephes/include/expx2.hpp>
#include <nt2/toolbox/cephes/include/bdtri.hpp>
#include <nt2/toolbox/cephes/include/sin.hpp>
#include <nt2/toolbox/cephes/include/i1e.hpp>
#include <nt2/toolbox/cephes/include/k0.hpp>
#include <nt2/toolbox/cephes/include/k1.hpp>
#include <nt2/toolbox/cephes/include/lgam.hpp>
#include <nt2/toolbox/cephes/include/sqrt.hpp>
#include <nt2/toolbox/cephes/include/atanh.hpp>
#include <nt2/toolbox/cephes/include/floor.hpp>
#include <nt2/toolbox/cephes/include/gdtr.hpp>
#include <nt2/toolbox/cephes/include/tan.hpp>
#include <nt2/toolbox/cephes/include/nbdtr.hpp>
#include <nt2/toolbox/cephes/include/fdtr.hpp>
#include <nt2/toolbox/cephes/include/iv.hpp>
#include <nt2/toolbox/cephes/include/igami.hpp>
#include <nt2/toolbox/cephes/include/lbeta.hpp>
#include <nt2/toolbox/cephes/include/k1e.hpp>
#include <nt2/toolbox/cephes/include/expn.hpp>
#include <nt2/toolbox/cephes/include/rgamma.hpp>
#include <nt2/toolbox/cephes/include/erf.hpp>
#include <nt2/toolbox/cephes/include/igamc.hpp>
#include <nt2/toolbox/cephes/include/powi.hpp>
#include <nt2/toolbox/cephes/include/tanh.hpp>
#include <nt2/toolbox/cephes/include/stdtr.hpp>
#include <nt2/toolbox/cephes/include/nbdtri.hpp>
#include <nt2/toolbox/cephes/include/nbdtrc.hpp>
#include <nt2/toolbox/cephes/include/asinh.hpp>
#include <nt2/toolbox/cephes/include/cotdg.hpp>
#include <nt2/toolbox/cephes/include/exp10.hpp>
#include <nt2/toolbox/cephes/include/ellpe.hpp>
#include <nt2/toolbox/cephes/include/log10.hpp>
#include <nt2/toolbox/cephes/include/cosdg.hpp>
#include <nt2/toolbox/cephes/include/k0e.hpp>
#include <nt2/toolbox/cephes/include/ellpk.hpp>
#include <nt2/toolbox/cephes/include/exp2.hpp>
#include <nt2/toolbox/cephes/include/log.hpp>
#include <nt2/toolbox/cephes/include/zeta.hpp>
#include <nt2/toolbox/cephes/include/pow.hpp>
#include <nt2/toolbox/cephes/include/fdtrc.hpp>
#include <nt2/toolbox/cephes/include/hyp2f1.hpp>
#include <nt2/toolbox/cephes/include/gamma.hpp>
#include <nt2/toolbox/cephes/include/acos.hpp>
#include <nt2/toolbox/cephes/include/erfc.hpp>
#include <nt2/toolbox/cephes/include/cot.hpp>
#include <nt2/toolbox/cephes/include/cos.hpp>
#include <nt2/toolbox/cephes/include/bdtr.hpp>
#include <nt2/toolbox/cephes/include/fdtri.hpp>
#include <nt2/toolbox/cephes/include/sinh.hpp>
#include <nt2/toolbox/cephes/include/pdtr.hpp>
#include <nt2/toolbox/cephes/include/gdtrc.hpp>
#include <nt2/toolbox/cephes/include/jn.hpp>
#include <nt2/toolbox/cephes/include/incbi.hpp>
#include <nt2/toolbox/cephes/include/jv.hpp>
#include <nt2/toolbox/cephes/include/log2.hpp>
#include <nt2/toolbox/cephes/include/ellik.hpp>
#include <nt2/toolbox/cephes/include/struve.hpp>
#include <nt2/toolbox/cephes/include/ndtri.hpp>
#include <nt2/toolbox/cephes/include/pdtrc.hpp>
#include <nt2/toolbox/cephes/include/ellie.hpp>
#include <nt2/toolbox/cephes/include/asin.hpp>
#include <nt2/toolbox/cephes/include/cosh.hpp>
#include <nt2/toolbox/cephes/include/j1.hpp>
#include <nt2/toolbox/cephes/include/j0.hpp>
#include <nt2/toolbox/cephes/include/incbps.hpp>
#include <nt2/toolbox/cephes/include/sindg.hpp>
#include <nt2/toolbox/cephes/include/chdtr.hpp>
#include <nt2/toolbox/cephes/include/tandg.hpp>
#include <nt2/toolbox/cephes/include/zetac.hpp>
#include <nt2/toolbox/cephes/include/incbet.hpp>
#include <nt2/toolbox/cephes/include/yv.hpp>
#include <nt2/toolbox/cephes/include/ceil.hpp>
#include <nt2/toolbox/cephes/include/i0e.hpp>
#include <nt2/toolbox/cephes/include/psi.hpp>
#include <nt2/toolbox/cephes/include/cbrt.hpp>
#include <nt2/toolbox/cephes/include/igam.hpp>
#include <nt2/toolbox/cephes/include/pdtri.hpp>
#include <nt2/toolbox/cephes/include/dawsn.hpp>
#include <nt2/toolbox/cephes/include/y0.hpp>
#include <nt2/toolbox/cephes/include/y1.hpp>
#include <nt2/toolbox/cephes/include/acosh.hpp>
#include <nt2/toolbox/cephes/include/ndtr.hpp>
//<\include>

#endif
