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
#include <nt2/toolbox/cephes/include/functions/chdtri.hpp>
#include <nt2/toolbox/cephes/include/functions/chdtrc.hpp>
#include <nt2/toolbox/cephes/include/functions/hyperg.hpp>
#include <nt2/toolbox/cephes/include/functions/atan2.hpp>
#include <nt2/toolbox/cephes/include/functions/kn.hpp>
#include <nt2/toolbox/cephes/include/functions/yn.hpp>
#include <nt2/toolbox/cephes/include/functions/spence.hpp>
#include <nt2/toolbox/cephes/include/functions/beta.hpp>
#include <nt2/toolbox/cephes/include/functions/bdtrc.hpp>
#include <nt2/toolbox/cephes/include/functions/i0.hpp>
#include <nt2/toolbox/cephes/include/functions/i1.hpp>
#include <nt2/toolbox/cephes/include/functions/atan.hpp>
#include <nt2/toolbox/cephes/include/functions/exp.hpp>
#include <nt2/toolbox/cephes/include/functions/expx2.hpp>
#include <nt2/toolbox/cephes/include/functions/bdtri.hpp>
#include <nt2/toolbox/cephes/include/functions/sin.hpp>
#include <nt2/toolbox/cephes/include/functions/i1e.hpp>
#include <nt2/toolbox/cephes/include/functions/k0.hpp>
#include <nt2/toolbox/cephes/include/functions/k1.hpp>
#include <nt2/toolbox/cephes/include/functions/lgam.hpp>
#include <nt2/toolbox/cephes/include/functions/sqrt.hpp>
#include <nt2/toolbox/cephes/include/functions/atanh.hpp>
#include <nt2/toolbox/cephes/include/functions/floor.hpp>
#include <nt2/toolbox/cephes/include/functions/gdtr.hpp>
#include <nt2/toolbox/cephes/include/functions/tan.hpp>
#include <nt2/toolbox/cephes/include/functions/nbdtr.hpp>
#include <nt2/toolbox/cephes/include/functions/fdtr.hpp>
#include <nt2/toolbox/cephes/include/functions/iv.hpp>
#include <nt2/toolbox/cephes/include/functions/igami.hpp>
#include <nt2/toolbox/cephes/include/functions/lbeta.hpp>
#include <nt2/toolbox/cephes/include/functions/k1e.hpp>
#include <nt2/toolbox/cephes/include/functions/expn.hpp>
#include <nt2/toolbox/cephes/include/functions/rgamma.hpp>
#include <nt2/toolbox/cephes/include/functions/erf.hpp>
#include <nt2/toolbox/cephes/include/functions/igamc.hpp>
#include <nt2/toolbox/cephes/include/functions/powi.hpp>
#include <nt2/toolbox/cephes/include/functions/tanh.hpp>
#include <nt2/toolbox/cephes/include/functions/stdtr.hpp>
#include <nt2/toolbox/cephes/include/functions/nbdtri.hpp>
#include <nt2/toolbox/cephes/include/functions/nbdtrc.hpp>
#include <nt2/toolbox/cephes/include/functions/asinh.hpp>
#include <nt2/toolbox/cephes/include/functions/cotdg.hpp>
#include <nt2/toolbox/cephes/include/functions/exp10.hpp>
#include <nt2/toolbox/cephes/include/functions/ellpe.hpp>
#include <nt2/toolbox/cephes/include/functions/log10.hpp>
#include <nt2/toolbox/cephes/include/functions/cosdg.hpp>
#include <nt2/toolbox/cephes/include/functions/k0e.hpp>
#include <nt2/toolbox/cephes/include/functions/ellpk.hpp>
#include <nt2/toolbox/cephes/include/functions/exp2.hpp>
#include <nt2/toolbox/cephes/include/functions/log.hpp>
#include <nt2/toolbox/cephes/include/functions/zeta.hpp>
#include <nt2/toolbox/cephes/include/functions/pow.hpp>
#include <nt2/toolbox/cephes/include/functions/fdtrc.hpp>
#include <nt2/toolbox/cephes/include/functions/hyp2f1.hpp>
#include <nt2/toolbox/cephes/include/functions/gamma.hpp>
#include <nt2/toolbox/cephes/include/functions/acos.hpp>
#include <nt2/toolbox/cephes/include/functions/erfc.hpp>
#include <nt2/toolbox/cephes/include/functions/cot.hpp>
#include <nt2/toolbox/cephes/include/functions/cos.hpp>
#include <nt2/toolbox/cephes/include/functions/bdtr.hpp>
#include <nt2/toolbox/cephes/include/functions/fdtri.hpp>
#include <nt2/toolbox/cephes/include/functions/sinh.hpp>
#include <nt2/toolbox/cephes/include/functions/pdtr.hpp>
#include <nt2/toolbox/cephes/include/functions/gdtrc.hpp>
#include <nt2/toolbox/cephes/include/functions/jn.hpp>
#include <nt2/toolbox/cephes/include/functions/incbi.hpp>
#include <nt2/toolbox/cephes/include/functions/jv.hpp>
#include <nt2/toolbox/cephes/include/functions/log2.hpp>
#include <nt2/toolbox/cephes/include/functions/ellik.hpp>
#include <nt2/toolbox/cephes/include/functions/struve.hpp>
#include <nt2/toolbox/cephes/include/functions/ndtri.hpp>
#include <nt2/toolbox/cephes/include/functions/pdtrc.hpp>
#include <nt2/toolbox/cephes/include/functions/ellie.hpp>
#include <nt2/toolbox/cephes/include/functions/asin.hpp>
#include <nt2/toolbox/cephes/include/functions/cosh.hpp>
#include <nt2/toolbox/cephes/include/functions/j1.hpp>
#include <nt2/toolbox/cephes/include/functions/j0.hpp>
#include <nt2/toolbox/cephes/include/functions/incbps.hpp>
#include <nt2/toolbox/cephes/include/functions/sindg.hpp>
#include <nt2/toolbox/cephes/include/functions/chdtr.hpp>
#include <nt2/toolbox/cephes/include/functions/tandg.hpp>
#include <nt2/toolbox/cephes/include/functions/zetac.hpp>
#include <nt2/toolbox/cephes/include/functions/incbet.hpp>
#include <nt2/toolbox/cephes/include/functions/yv.hpp>
#include <nt2/toolbox/cephes/include/functions/ceil.hpp>
#include <nt2/toolbox/cephes/include/functions/i0e.hpp>
#include <nt2/toolbox/cephes/include/functions/psi.hpp>
#include <nt2/toolbox/cephes/include/functions/cbrt.hpp>
#include <nt2/toolbox/cephes/include/functions/igam.hpp>
#include <nt2/toolbox/cephes/include/functions/pdtri.hpp>
#include <nt2/toolbox/cephes/include/functions/dawsn.hpp>
#include <nt2/toolbox/cephes/include/functions/y0.hpp>
#include <nt2/toolbox/cephes/include/functions/y1.hpp>
#include <nt2/toolbox/cephes/include/functions/acosh.hpp>
#include <nt2/toolbox/cephes/include/functions/ndtr.hpp>
//<\include>

#endif
