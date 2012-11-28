#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
##############################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################


"""generation of an exhaustive test unit
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2011    $"
__copyright__ = "Lapreste Jean-thierry"
__license__   = "Boost Software License, Version 1.0"

class Exhaustive_data(object) :
    Tpl = {
        'scalar' : {
            },
        'simd' : {
            'global_header_txt' : '\n'.join([
                '////////////////////////////////////////////////////////////////////////',
                '// exhaustive test in simd mode for functor $prefix$::$name$',
                '////////////////////////////////////////////////////////////////////////',
                '#include <nt2/include/functions/$name$.hpp>',
                '',
                '#include <nt2/include/functions/iround.hpp>',
                '#include <nt2/include/functions/load.hpp>',
                '#include <nt2/include/functions/min.hpp>',
                '#include <nt2/include/functions/splat.hpp>',
                '#include <nt2/include/functions/successor.hpp>',
                '#include <nt2/include/functions/ulpdist.hpp>',
                '',
                '#include <nt2/include/constants/real.hpp>',
                '',
                '#include <nt2/sdk/meta/cardinal_of.hpp>',
                '#include <nt2/sdk/meta/as_integer.hpp>',
                '',
                '#include <iostream>',
                '',
                'typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;',
            ]),
            'typ_repfunc_txt' : '\n'.join([
                'static inline ',
                'typename nt2::meta::call<nt2::tag::$name$_($typ$)>::type',
                'repfunc(const $typ$ & a0)',
                '{',
                '  return $repfunc$;',
                '}',
                ]),
            'test_func_forwarding_txt' : '\n'.join([
                'template <class T>',
                'void exhaust_test_$name$(const T& mini,const T& maxi);'
                ]),
            'test_func_call_txt' : '\n'.join([
                '    exhaust_test_$name$($mini$,$maxi$);'
                ]),
            'main_beg_txt' : '\n'.join([
                'int main(){',
                '{',
                ]),
            'main_end_txt' : '\n'.join([
                '  return 0;',
                '}',
                '',
                ]),
            'test_func_typ_txt' : '\n'.join([
                'template <>',
                'void exhaust_test_$name$<$typ$>(const $typ$& mini,const $typ$& maxi)',
                '  {',
                '    typedef boost::simd::native<$typ$,ext_t>  n_t;',
                '    typedef typename nt2::meta::as_integer<n_t>::type   in_t;',
                '    typedef typename nt2::meta::call<nt2::tag::$name$_($typ$)>::type r_t;',
                '    typedef typename nt2::meta::call<nt2::tag::$name$_(n_t)>::type r_t;',
                '    $typ$ mini = $mini$;',
                '    $typ$ maxi = $maxi$;',
                '    const nt2::uint32_t N = nt2::meta::cardinal_of<n_t>::value;',
                '    const in_t vN = nt2::splat<in_t>(N);',
                '    const nt2::uint32_t M =  10;',
                '    nt2::uint32_t histo[M+1];',
                '    for(nt2::uint32_t i = 0; i < M; i++) histo[i] = 0;',
                '    float a[N];',
                '    a[0] = mini;',
                '    for(nt2::uint32_t i = 1; i < N; i++)',
                '      a[i] = nt2::successor(a[i-1], 1);',
                '    n_t a0 = nt2::load<n_t>(&a[0],0);',
                '    nt2::uint32_t k = 0,j = 0;',
                '    std::cout << "a line of points to wait for... be patient!" << std::endl;',
                '    for(; a0[N-1] < maxi; a0 = nt2::successor(a0, vN))',
                '      {',
                '        n_t z =  nt2::$name$(a0);',
                '        for(nt2::uint32_t i = 0; i < N; i++)',
                '          {',
                '             float v = repfunc(a0[i]);',
                '             float sz = z[i];',
                '             ++histo[nt2::min(M, nt2::iround(2*nt2::ulpdist(v, sz)))];',
                '             ++k;',
                '             if (k%100000000 == 0){',
                '               std::cout << "." << std::flush; ++j;',
                '               if (j == 80){std::cout << std::endl; j = 0;}',
                '             }',
                '          }',
                '        }',
                '      std::cout << "exhaustive test for " << std::endl;',
                '      std::cout << " nt2::$name$ versus $repfunc$ " << std::endl;',
                '      std::cout << " in $mode$ mode and $typ$ type" << std::endl;',
                '      for(nt2::uint32_t i = 0; i < M; i++)',
                '        std::cout << i/2.0 << " -> " << histo[i] << std::endl;',
                '      std::cout << k << " values computed" << std::endl;',
                '      std::cout << std::endl;',
                '      std::cout << std::endl;',
                '      for(nt2::uint32_t i = 0; i < M; i++)',
                '        std::cout << i/2.0 << " -> "',
                '                  << (histo[i]*100.0/k) << "%" << std::endl;',
                '  }',
                '',
                ]),
            }
        }
    def __init__(self) :
        self.tpl = Exhaustive_data.Tpl

if __name__ == "__main__" :
    print __doc__
    from pprint   import PrettyPrinter
    PrettyPrinter().pprint(Exhaustive_data.Tpl)
    PrettyPrinter().pprint(Exhaustive_data().tpl)
