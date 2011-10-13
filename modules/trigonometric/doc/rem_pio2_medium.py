[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['compute the remainder modulo \\\\f$\pi/2\\\\f$ with cephes algorthm.','\par',
                         'This function is mainly for internal reduction purposes',
                         'This is a medium version version accurate if the input is in:',
                         '\\\\arg \\\\f$[-2^6\pi,2^6\pi\\\\f$ for float,',
                         '\\\\arg \\\\f$[-2^18\pi,2^18\pi\\\\f$ for double.',
                         '\par',
                         'The reduction of the argument modulo \\\\f$pi/2\\\\f$ is generally',
                         'the most difficult part of trigonometric evaluations.',
                         'The accurate algorithm is over costly and implies the knowledge',
                         'of a few hundred \\\\f$pi\\\\f$ decimals',
                         'some simpler algorithms as this one',
                         'can be used, but the precision is only insured on small intervals.'
                         ],
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '3',
         'rturn' : {
             'default' : 'typename nt2::meta::call<rem_pio2_medium_(T)>::type',
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
                 '#include <nt2/toolbox/trigonometric/include/functions/rem_pio2.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 11/02/2011',
            },
         'ranges' : {
             'real_' : [['nt2::Zero<T>()', '64*nt2::Pi<T>()']],
            },
         'specific_values' : {
             'real_' : {
                'nt2::Zero<T>()' : {'result' : ['nt2::Zero<r_t0>()','nt2::Zero<r_t1>()','nt2::Zero<r_t2>()'],'ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
           'property_call' : {
                 'real_' : ['nt2::rem_pio2_medium(a0)'],
                },
             'property_value' : {
                 'real_' : ['boost::fusion::get<0>(nt2::rem_pio2(a0))','no test available','boost::fusion::get<2>(nt2::rem_pio2(a0))'],
                },
             'ulp_thresh' : {
                 'real_' : ['0.5','0','0'],
                },
            },
        },
    },
]
