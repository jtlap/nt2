[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '3',
         'rturn' : {
             'default' : 'typename nt2::meta::call<rem_pio2_(T)>::type',
            },
         'simd_types' : ['real_'],
         'special' : ['trigonometric'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 11/02/2011',
             'included' : ['#include <nt2/toolbox/trigonometric/constants.hpp>',
                 'extern "C" {extern long double cephes_cosl(long double);}'],
             'notes' : [],
             'stamp' : 'modified by jt the 11/02/2011',
            },
         'ranges' : {
             'real_' : [['0', '200000*nt2::Pi<T>()']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::Zero<T>()' : {'result' : ['nt2::Zero<r_t0>()','nt2::Zero<r_t1>()','nt2::Zero<r_t2>()'],'ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {

            },
        },
    },
]
