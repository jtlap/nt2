[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '3',
         'call_types' : ['T', 'T', 'iT'],
         'ret_arity' : '3',
         'rturn' : {
             'default' : 'boost::fusion::tuple<T,T,bool>',
            },
         'scalar_ints': 'True',   
         'simd_types' : ['real_'],
         'special' : ['swar'],  
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 24/02/2011',
             'simd_included' : ['#include <nt2/include/functions/all.hpp>',
                           '#include <nt2/include/functions/max.hpp>',
                           '#include <nt2/include/functions/min.hpp>',],
             'cover_included' : ['#include <nt2/include/functions/all.hpp>',
                           '#include <nt2/include/functions/max.hpp>',
                           '#include <nt2/include/functions/min.hpp>',
                           '#include <nt2/include/functions/is_equal.hpp>',],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 24/02/2011',
            },
         'ranges' : {
             'default' : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()'],['nt2::Valmin<T>()', 'nt2::Valmax<T>()'],['iT(0)', 'iT(1)']],
             'real_' : [['T(-100)', 'T(100)'],['T(-100)', 'T(100)'],['iT(0)', 'iT(1)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>()' : {'result' : ['nt2::One<r_t0>()', 'nt2::One<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : ['nt2::Zero<r_t0>()', 'nt2::Zero<r_t0>()', '0'],'ulp_thresh' : '0',},
                },
             'real_' : {
                 'nt2::Inf<T>()' : {'result' : ['nt2::Inf<r_t0>()', 'nt2::Inf<r_t1>()', '0'],'ulp_thresh' : '0',},
                 'nt2::Minf<T>()' : {'result' : ['nt2::Minf<r_t0>()', 'nt2::Minf<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'nt2::Mone<T>()' : {'result' : ['nt2::Mone<r_t0>()', 'nt2::Mone<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'nt2::Nan<T>()' : {'result' : ['nt2::Nan<r_t0>()', 'nt2::Nan<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : ['nt2::One<r_t0>()', 'nt2::One<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : ['nt2::Zero<r_t0>()', 'nt2::Zero<r_t0>()', '0'],'ulp_thresh' : '0',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : {'result' : ['nt2::Mone<r_t0>()', 'nt2::Mone<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : ['nt2::One<r_t0>()', 'nt2::One<r_t0>()', '0'],'ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : ['nt2::Zero<r_t0>()', 'nt2::Zero<r_t0>()', '0'],'ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::comparator(a0,a1,a2)'],
                },
             'property_value' : {
                 'default' : [['nt2::max(a0,a1)', 'nt2::min(a0,a1)', 'a0<=a1']],
                },
             'ulp_thresh' : {
                 'default' : ['0.5'],
                },
             'scalar_simul' :{
                    'default' : [
                        "        vT ma = nt2::max(a0,a1);",
                        "        vT mi = nt2::min(a0,a1);",
                        "        NT2_TEST(nt2::all(nt2::eq(boost::fusion::get<0>(v),(a2)?ma:mi)));",
                        "        NT2_TEST(nt2::all(nt2::eq(boost::fusion::get<1>(v),(a2)?mi:ma)));",
                            ]
               },
            },
        },
    },
]
