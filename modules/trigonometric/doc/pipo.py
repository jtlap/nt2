[ ## this file was manually modified
    {
     'unit' : {
         'ranges' : {
             'default' : [['T(-60)', 'T(60)']]
             'signed_int_' : [['T(-40)', 'T(40)']]
             'unsigned_int_' : [['T(0)', 'T(40)']]
             'real_' : [['-20*nt2::Pi<T>()', '20*nt2::Pi<T>()']]
            },
         'global_header' : {
             'stamp' : 'modified by jt the 10/02/2011'
             'included' : ['#include <nt2/toolbox/trigonometric/include/constants.hpp>', '#include <nt2/toolbox/crlibm/include/cos.hpp>']
             'notes' : []
             'first_stamp' : 'created  by jt the 10/02/2011'
            },
         'specific_values' : {
             'default' : {
                 'nt2::Zero<T>()' : {'ulp_thresh' : '0.5', 'result' : 'nt2::One<r_t>()', },
                },
             'signed_int_   ' : {
                 'nt2::Zero<T>()' : {'ulp_thresh' : '0.5', 'result' : 'nt2::One<r_t>()', },
                },
             'real_' : {
                 '-nt2::Pi<T>()' : {'ulp_thresh' : '0.5', 'result' : 'nt2::Mone<r_t>()', },
                 'nt2::Pi<T>()/2' : {'ulp_thresh' : '0.5', 'result' : 'nt2::Zero<r_t>()', },
                 '-nt2::Pi<T>()/4' : {'ulp_thresh' : '0.5', 'result' : 'nt2::Sqrt_2o_2<r_t>()', },
                 'nt2::Minf<T>()' : {'ulp_thresh' : '0.5', 'result' : 'nt2::Nan<r_t>()', },
                 'nt2::Inf<T>()' : {'ulp_thresh' : '0.5', 'result' : 'nt2::Nan<r_t>()', },
                 'nt2::Pi<T>()/4' : {'ulp_thresh' : '0.5', 'result' : 'nt2::Sqrt_2o_2<r_t>()', },
                 'nt2::Zero<T>()' : {'ulp_thresh' : '0.5', 'result' : 'nt2::One<r_t>()', },
                 'nt2::Nan<T>()' : {'ulp_thresh' : '0.5', 'result' : 'nt2::Nan<r_t>()', },
                 'nt2::Pi<T>()' : {'ulp_thresh' : '0.5', 'result' : 'nt2::Mone<r_t>()', },
                 '-nt2::Pi<T>()/2' : {'ulp_thresh' : '0.5', 'result' : 'nt2::Zero<r_t>()', },
                },
            },
         'verif_test' : {
             'property_value' : {
                 'real_' : ['nt2::crlibm::cos<nt2::rn>(a0)']
                },
             'ulp_thresh' : {
                 'real_' : ['0.5']
                },
             'property_call' : {
                 'real_' : ['nt2::cos(a0)']
                },
            },
        },
     'functor' : {
         'type_defs' : []
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type'
            },
         'arity' : '1'
         'ret_arity' : '0'
         'simd_types' : ['real_convert_']
         'call_types' : []
         'types' : ['real_', 'unsigned_int_', 'signed_int_']
        },
    },
]