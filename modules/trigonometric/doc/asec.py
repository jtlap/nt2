[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type',
            },
         'simd_types' : ['real_convert_'],
         'special' : ['trigonometric'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 11/02/2011',
             'included' : 
                ['#include <nt2/toolbox/trigonometric/include/constants.hpp>',
                 'extern "C" {extern long double cephes_acosl(long double);}'],
             'notes' : ['acos(1/a0)'],
             'stamp' : 'modified by jt the 11/02/2011',
            },
         'ranges' : {
             'default' : [['nt2::One<T>()', 'nt2::Ten<T>()']],
             'real_' : [['T(1.01)', 'T(10)'], ['T(-10)', 'T(-1.01)']],
             'signed_int_' : [['T(1)', 'T(10)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Two<T>()' : {'result' : 'nt2::Pi<r_t>()/3','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 '-nt2::Two<T>()' : {'result' : '2*nt2::Pi<r_t>()/3','ulp_thresh' : '0.5',},
                 'nt2::Inf<T>()' : {'result' : 'nt2::Pio_2<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Pio_2<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Mone<T>()' : {'result' : 'nt2::Pi<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Two<T>()' : {'result' : 'nt2::Pi<r_t>()/3','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 '-nt2::Two<T>()' : {'result' : '2*nt2::Pi<r_t>()/3','ulp_thresh' : '0.5',},
                 'nt2::Mone<T>()' : {'result' : 'nt2::Pi<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Two<T>()' : {'result' : 'nt2::Pi<r_t>()/3','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::asec(a0)'],
                },
             'property_value' : {
                 'real_' : ['::cephes_acosl(1.0l/(a0))'],
                },
             'ulp_thresh' : {
                 'real_' : ['5.0'],
                },
            },
        },
    },
]
