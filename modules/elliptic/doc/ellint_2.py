[ ## this file was manually modified by jt
    {
     'functor' : {
         'description':['Complete elliptic integral of the second kind','\par Formula',
                       '\\\\f[E(a_0) = \int_0^{\pi/2} (1-a_0^2\sin^2 t)^{\\\\frac12} dt\\\\f]'],
         'param1' :  ['between -1 and 1'], 
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 21/02/2011',
             'included' : ['#include <boost/math/special_functions.hpp>',
                           '#include <nt2/toolbox/trigonometric/constants.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 21/02/2011',
            },
         'ranges' : {
             'real_' : [['T(-1)', 'T(1)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::One<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Pi<r_t>()/2','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::ellint_2(a0)'],
                },
             'property_value' : {
                 'default' : ['boost::math::ellint_2(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0.5'],
                },
            },
        },
    },
]
