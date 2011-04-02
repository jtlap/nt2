[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '2',
         'rturn' : {
             'default' : 'rtype',
            },
         'simd_types' : ['real_'],
         'type_defs' : 
            ['typedef typename boost::result_of<nt2::meta::floating(T)>::type etype;',
             'typedef boost::fusion::tuple<etype,etype> rtype;'],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 21/02/2011',
             'included' : 
                ['extern "C" {long double cephes_ellikl(long double,long double);}',
                 '#include <nt2/toolbox/trigonometric/include/constants.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 21/02/2011',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(1)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::One<T>()' : {'result' : ['nt2::Inf<r_t0>()', 'nt2::Zero<r_t1>()'],'ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : ['nt2::Pio_2<r_t0>()', 'nt2::Pio_2<r_t1>()'],'ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
            },
        },
    },
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '2',
         'rturn' : {
             'default' : 'rtype',
            },
         'simd_types' : ['real_'],
         'type_defs' : 
            ['typedef typename boost::result_of<nt2::meta::floating(T)>::type etype;',
             'typedef boost::fusion::tuple<etype,etype> rtype;'],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 21/02/2011',
             'included' : 
                ['extern "C" {long double cephes_ellikl(long double,long double);}',
                 '#include <nt2/toolbox/trigonometric/include/constants.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 21/02/2011',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(1)'], ['T(0)', 'T(0.01)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>(),0' : {'result' : ['nt2::Inf<r_t0>()', 'nt2::Zero<r_t1>()'],'ulp_thresh' : '0',},
                 'nt2::Zero<T>(),0' : {'result' : ['nt2::Pio_2<r_t0>()', 'nt2::Pio_2<r_t1>()'],'ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
            },
        },
    },
]
