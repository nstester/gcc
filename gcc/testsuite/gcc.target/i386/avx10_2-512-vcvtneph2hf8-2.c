/* { dg-do run } */
/* { dg-options "-O2 -mavx10.2-512" } */
/* { dg-require-effective-target avx10_2_512 } */

#ifndef AVX10_2
#define AVX10_2
#define AVX10_2_512
#define AVX10_512BIT
#endif

#include "avx10-helper.h"
#include "fp8-helper.h"

#define SIZE_SRC (AVX512F_LEN / 16)
#define SIZE (AVX512F_LEN_HALF / 8)
#include "avx512f-mask-type.h"

void
CALC (unsigned char *r, _Float16 *s)
{
  int i, hf8_bf8, saturate;

  hf8_bf8 = 0;
  saturate = 0;
  
  for (i = 0; i < SIZE; i++)
    {
      r[i] = 0;
      if (i < SIZE_SRC)
        {
          Float16Union usrc = {.f16 = s[i]};
          r[i] = convert_fp16_to_fp8(usrc.f16, 0, hf8_bf8, saturate);
        }
    }
}

void
TEST (void)
{
  int i,sign;
  UNION_TYPE (AVX512F_LEN_HALF, i_b) res1, res2, res3; 
  UNION_TYPE (AVX512F_LEN, h) src;
  MASK_TYPE mask = MASK_VALUE;
  unsigned char res_ref[SIZE];

  sign = 1;
  for (i = 0; i < SIZE_SRC; i++)
    {
      src.a[i] = (_Float16)(sign * (2.5 * (1 << (i % 3))));
      sign = -sign;
    }

  for (i = 0; i < SIZE; i++)
    res2.a[i] = DEFAULT_VALUE;

  CALC(res_ref, src.a);

  res1.x = INTRINSIC (_cvtneph_phf8) (src.x);
  if (UNION_CHECK (AVX512F_LEN_HALF, i_b) (res, res_ref))
    abort ();

  res2.x = INTRINSIC (_mask_cvtneph_phf8) (res2.x, mask, src.x);
  MASK_MERGE (h) (res_ref, mask, SIZE);
  if (UNION_CHECK (AVX512F_LEN_HALF, i_b) (res, res_ref))
    abort ();

  res3.x = INTRINSIC (_maskz_cvtneph_phf8) (mask, src.x);
  MASK_ZERO (h) (res_ref, mask, SIZE);
  if (UNION_CHECK (AVX512F_LEN_HALF, i_b) (res, res_ref))
    abort ();
}
