[ ## this file was manually modified by jt
    {
     'functor' : {
         'description':['Complete elliptic integral of the first kind','\par Formula',
                       '\\\\f[K(a_0) = \int_0^{\pi/2} \sqrt{1-a_0^2\sin^2 t} dt\\\\f]'],
         'param1' :  ['between -1 and 1'], 
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 21/02/2011',
             'included' : ['#include <boost/math/special_functions.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 21/02/2011',
            },
         'ranges' : {
             'real_' : [['T(-1)', 'T(1)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::One<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Pio_2<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::ellint_1(a0)'],
                },
             'property_value' : {
                 'default' : ['boost::math::ellint_1(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['3.5'],
                },
            },
        },
    },
]
