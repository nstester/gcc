/* { dg-do compile } */
/* { dg-options "-march=rv64gc -mabi=lp64d -O3" } */

#include "riscv_vector.h"

size_t test_1 (size_t vl)
{
  return __riscv_vsetvl_e8m4 (vl); /* { dg-error {builtin function '__riscv_vsetvl_e8m4\(vl\)' requires the V ISA extension} } */
}
