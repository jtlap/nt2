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
             'included' : ['#include <nt2/toolbox/trigonometric/include/constants.hpp>',
                           'extern "C" {extern long double cephes_acosl(long double);}'],
             'notes' : [],
             'stamp' : 'modified by jt the 11/02/2011',
            },
         'ranges' : {
             'default' : [['nt2::Zero<T>()', 'nt2::One<T>()']],
             'real_' : [['nt2::Mone<T>()', 'nt2::One<T>()']],
             'signed_int_' : [['T(-1)', 'T(1)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Pi<r_t>()/2','ulp_thresh' : '0',},
                },
             'real_' : {
                 'nt2::Half<T>()' : {'result' : 'nt2::Pi<r_t>()/3','ulp_thresh' : '0',},
                 'nt2::Inf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0',},
                 'nt2::Mhalf<T>()' : {'result' : '2*nt2::Pi<r_t>()/3','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0',},
                 'nt2::Mone<T>()' : {'result' : 'nt2::Pi<r_t>()','ulp_thresh' : '0',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Pi<r_t>()/2','ulp_thresh' : '0',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : {'result' : 'nt2::Pi<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Pi<r_t>()/2','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::acos(a0)'],
                },
             'property_value' : {
                 'real_' : ['::cephes_acosl(a0)'],
                },
             'ulp_thresh' : {
                 'real_' : ['0.5'],
                },
            },
        },
    },
]
