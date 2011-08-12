[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : [],
         'special' : ['fdlibm'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 03/03/2011',
             'included' : [ '#include <nt2/include/functions/remainder.hpp>',
                            '#include <nt2/include/functions/abs.hpp>',
                            '#include <nt2/include/functions/idivround.hpp>'
                          ],
              'cover_included': [ '#include <nt2/include/functions/rem.hpp>',
                                  '#include <nt2/toolbox/fdlibm/include/functions/fmod.hpp>'
                                ],
             'notes' : [],
             'stamp' : 'modified by jt the 03/03/2011',
            },
         'ranges' : {
             'default' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'special_call' : [
                    '        T v1 = nt2::abs(nt2::fdlibm::fmod(a0,a1)+a1*(nt2::idivround(a0, a1))-a0);',
                    '        T v2 = nt2::abs(nt2::rem(a0,a1)+a1*(nt2::idivround(a0, a1))-a0);',
                    '        NT2_TEST_LESSER_EQUAL(v2, v1); ',
                    ],
             'property_call' : {
                 'default' : ['nt2::fdlibm::__ieee754_remainder(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['nt2::remainder(a0,a1)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['1'],
                },
            },
        },
    },
]
