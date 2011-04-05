[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['T', 'iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['integer_'],
         'type_defs' : [],
         'types' : ['integer_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : ['#include <nt2/include/functions/twopower.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2'], ['T(0)', 'sizeof(T)*8-1']],
            },
         'specific_values' : {
             'integer_' : {
                 'nt2::Mone<T>(),1' : {'result' : 'r_t(-2)','ulp_thresh' : '0.5',},
                 'nt2::Mone<T>(),2' : {'result' : 'r_t(-4)','ulp_thresh' : '0.5',},
                 'nt2::One<T>(),1' : {'result' : 'nt2::Two<r_t>()','ulp_thresh' : '0.5',},
                 'T(2),2' : {'result' : 'nt2::Eight<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>(),1' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['nt2::shli(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['r_t(a0*nt2::twopower(a1))'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
    },
]
