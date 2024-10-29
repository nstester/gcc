/* { dg-do compile } */
/* { dg-options "-march=rv64gcv_zvfh -mabi=lp64d -O3 -fno-vect-cost-model -fdump-rtl-expand-details" } */

#include "strided_ld_st.h"

DEF_STRIDED_LD_ST_FORM_1(_Float16)

/* { dg-final { scan-rtl-dump-times ".MASK_LEN_STRIDED_LOAD " 4 "expand" } } */
/* { dg-final { scan-rtl-dump-times ".MASK_LEN_STRIDED_STORE " 4 "expand" } } */
/* { dg-final { scan-assembler-times {vlse16.v} 1 } } */
/* { dg-final { scan-assembler-times {vsse16.v} 1 } } */
