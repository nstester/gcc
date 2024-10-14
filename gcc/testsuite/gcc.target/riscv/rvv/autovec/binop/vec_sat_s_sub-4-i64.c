/* { dg-do compile } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -ftree-vectorize -fdump-rtl-expand-details" } */

#include "../vec_sat_arith.h"

DEF_VEC_SAT_S_SUB_FMT_4(int64_t, uint64_t, INT64_MIN, INT64_MAX)

/* { dg-final { scan-rtl-dump-times ".SAT_SUB " 2 "expand" } } */
/* { dg-final { scan-assembler-times {vssub\.vv} 1 } } */
