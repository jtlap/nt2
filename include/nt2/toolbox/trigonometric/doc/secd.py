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
                 '#include <nt2/toolbox/cephes/include/cos.hpp>',
                 '#include <nt2/include/functions/rec.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 11/02/2011',
            },
         'ranges' : {
             'real_' : [['T(-80)', 'T(80)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::Zero<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::_45<T>()' : {'result' : 'nt2::Sqrt_2<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 '-nt2::_180<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 '-nt2::_45<T>()' : {'result' : 'nt2::Sqrt_2<r_t>()','ulp_thresh' : '0.5',},
                 '-nt2::_90<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Inf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::_180<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::_45<T>()' : {'result' : 'nt2::Sqrt_2<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::_90<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 '-nt2::_45<T>()' : {'result' : 'nt2::Sqrt_2<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::_45<T>()' : {'result' : 'nt2::Sqrt_2<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::secd(a0)'],
                },
             'property_value' : {
                 'real_' : ['nt2::rec(::cos(a0*nt2::Deginrad<T>()))'],
                },
             'ulp_thresh' : {
                 'real_' : ['3.5'],
                },
            },
        },
    },
]