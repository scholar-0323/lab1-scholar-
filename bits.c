/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  return ~(~x & ~y) & ~(x & y); 
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x) {
  int sign = x >> 31;
  return sign & (~x + 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int src_shift = src << 3;
  int dst_shift = dst << 3;
  int byte = (x >> src_shift) & 0xFF;
  return (x & ~(0xFF << dst_shift)) | (byte << dst_shift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  return (x >> n) & ~(((1 << 31) >> n) << 1);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask1 = 0x0F | (0x0F << 8) | (0x0F << 16) | (0x0F << 24);
  int mask2 = mask1 << 4;
  return ((x & mask1) << 4) | (((x & mask2) >> 4) & mask1);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */

int secondLowestZeroBit(int x) {
  int y = x | (x + 1);
  return ~y & (y + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return ~x & 1; 
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int shift = (32 + ~n + 1) & 31;
  return ((x >> n) & ~(((1 << 31) >> n) << 1)) | (x << shift);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int bias = (1 << (n + ~0)) + ~0 + ((x >> n) & 1);
  return (x + bias) >> n << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int x_neg = x >> 31;
  int y_neg = y >> 31;
  int xy = x ^ y;
  
  /* 安全的基础平均值（向下取整） */
  int base = (x & y) + (xy >> 1);
  
  /* 安全判断 x > y（防止 INT_MIN 和 INT_MAX 相减溢出） */
  int x_gt_y = (~x_neg & y_neg) | (~(x_neg ^ y_neg) & ~((x + ~y + 1) >> 31) & 1);
  
  /* 修正项：仅当 x+y 为奇数，且 x > y 时，向上取整 (+1) 以靠近 x */
  int correction = (xy & 1) & x_gt_y;
  
  return base + correction;
}

// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sa = a >> 31, sb = b >> 31;
  int sx = x >> 31;

  // 1. 安全判断 a < b
  int lt_ab = (sa & ~sb) | (~(sa ^ sb) & ((a + ~b + 1) >> 31));

  // 2. 计算 min 和 max（lt_ab 为 -1 则 a<b，为 0 则 a>=b）
  int common = (a ^ b) & lt_ab;
  int min = b ^ common;
  int max = a ^ common;

  // 3. 安全判断 x < min
  int smin = min >> 31;
  int lt_x_min = (sx & ~smin) | (~(sx ^ smin) & ((x + ~min + 1) >> 31));

  // 4. 安全判断 max < x
  int smax = max >> 31;
  int lt_max_x = (smax & ~sx) | (~(smax ^ sx) & ((max + ~x + 1) >> 31));

  // 5. 最终结果：x >= min 且 x <= max。等价于 !(x < min) 且 !(max < x)
  return (~lt_x_min & ~lt_max_x) & 1;
}
// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */

/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 *   INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 */
int mul5Sat(int x) {
    int two  = x + x;              /* 2x */
    int four = two + two;          /* 4x */
    int prod = four + x;           /* 5x (mod 2^32) */

    int sx = x    >> 31;
    int s2 = two  >> 31;
    int s4 = four >> 31;
    int sp = prod >> 31;

    int ov2 = s2 ^ sx;                    /* 2x 溢出 */
    int ov4 = s4 ^ s2;                    /* 4x 溢出 */
    int ov5 = (~(s4 ^ sx)) & (s4 ^ sp);   /* 4x + x 溢出 */
    int mask = ov2 | ov4 | ov5;           /* 溢出为 -1，否则 0 */

    int INT_MAX = ~(1 << 31);
    int sat = INT_MAX ^ sx;               /* x>0 -> 0x7fffffff, x<0 -> 0x80000000 */

    return prod ^ (mask & (prod ^ sat));  /* 溢出取 sat，否则取 prod */
}
// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int xy = x + y;
  int s_xy = xy >> 31;
  int sum = xy + z;
  int s_sum = sum >> 31;
  int sx = x >> 31, sy = y >> 31, sz = z >> 31;
  
  /* 检查 x+y 是否溢出 */
  int xy_of = ~(sx ^ sy) & (sx ^ s_xy);
  int no_xy_of = ~xy_of;
  
  /* 检查总和 (x+y)+z 是否溢出（在 x+y 没溢出的前提下） */
  int sum_of = ~(s_xy ^ sz) & (s_xy ^ s_sum);
  
  /* 正溢出：xy没溢出但总和溢出了(且xy为正) | xy正溢出了(z为正 或 结果仍为负) */
  int pos_of = (no_xy_of & sum_of & ~s_xy) | (xy_of & ~sx & (~sz | s_sum));
  
  /* 负溢出：xy没溢出但总和溢出了(且xy为负) | xy负溢出了(z为负 或 结果仍为正) */
  int neg_of = (no_xy_of & sum_of & s_xy) | (xy_of & sx & (sz | ~s_sum));
  
  /* 注意：正溢出必须强制返回 1，负溢出返回 -1 */
  return (pos_of & 1) | neg_of;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    // NaN / Inf / Zero 直接返回
    if (exp == 0xFF) return uf;
    if (exp == 0 && frac == 0) return uf;
    if (exp == 0) {
        // 关键修复：先 *3 再 /2，保留精确余数
        unsigned tripled = frac + (frac << 1);
        unsigned res = tripled >> 1;
        unsigned rem = tripled & 1;

        // RNE: 余数为1 且 结果为奇数 → 进位到偶数
        if (rem && (res & 1))
            res++;

        // 检查是否进位到规格化数
        if (res >= 0x800000) {
            exp = 1;
            frac = res & 0x7FFFFF;
        } else {
            frac = res;
        }
        return sign | (exp << 23) | frac;
    }

    unsigned mant = frac | 0x800000;
    unsigned tripled = mant + (mant << 1);
    unsigned res = tripled >> 1;
    unsigned rem = tripled & 1;

    if (res & 0x1000000) {
        // 产生第25位，需右移并增加指数
        unsigned shifted = res >> 1;
        unsigned round_bit = res & 1;
        // sticky 包含原始余数
        if (round_bit && ((shifted & 1) || rem))
            shifted++;
        res = shifted;
        exp++;
    } else {
        // 未溢出，直接 RNE
        if (rem && (res & 1))
            res++;
    }

    // 溢出到无穷大
    if (exp >= 0xFF)
        return sign | 0x7F800000;

    return sign | (exp << 23) | (res & 0x7FFFFF);
}


// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  int exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;

  if (exp == 0xFF) return uf;

  int E = exp - 127;
  
  if (E < -1) return sign;
  if (E == -1) {
    if (frac > 0) return sign | 0x3F800000;
    return sign;
  }
  
  if (E >= 23) return uf;

  int shift = 23 - E;
  unsigned mask = (1 << shift) - 1;
  unsigned dropped = frac & mask;
  unsigned half = 1 << (shift - 1);

  unsigned res = (1 << E) + (frac >> shift);

  if (dropped > half || (dropped == half && (res & 1))) {
    res++;
  }

  int k = 0;
  unsigned temp = res;
  while (temp >>= 1) { k++; }

  if (k >= 23) {
    return sign | ((127 + k) << 23);
  }

  unsigned new_frac = (res << (23 - k)) & 0x7FFFFF;
  return sign | ((127 + k) << 23) | new_frac;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  if (x == 0) return 0;
  
  unsigned ux = x;
  unsigned sign = 0;
  if (x < 0) {
    sign = 0x80000000;
    ux = -x;
  }
  
  int E = 0;
  unsigned temp = ux;
  while (temp >>= 1) {
    E++;
  }
  
  unsigned res;
  if (E <= 23) {
    res = ux << (23 - E);
  } else {
    int shift = E - 23;
    unsigned mask = (1 << shift) - 1;
    unsigned dropped = ux & mask;
    unsigned half = 1 << (shift - 1);
    
    res = ux >> shift;
    
    if (dropped > half || (dropped == half && (res & 1))) {
      res++;
      /* 修正：必须是检查第 24 位 (1 << 24)，而不是第 23 位 */
      if (res & 0x1000000) {
        res >>= 1;
        E++;
      }
    }
  }
  
  return sign | ((E + 127) << 23) | (res & 0x7FFFFF);
}


// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int mask1 = 0x55 | (0x55 << 8);
  mask1 = mask1 | (mask1 << 16);
  int mask2 = 0x33 | (0x33 << 8);
  mask2 = mask2 | (mask2 << 16);
  int mask4 = 0x0F | (0x0F << 8);
  mask4 = mask4 | (mask4 << 16);
  int mask8 = 0xFF | (0xFF << 16);
  int mask16 = 0xFF | (0xFF << 8);
  
  int count = (x & mask1) + ((x >> 1) & mask1);
  count = (count & mask2) + ((count >> 2) & mask2);
  count = (count & mask4) + ((count >> 4) & mask4);
  count = (count & mask8) + ((count >> 8) & mask8);
  count = (count & mask16) + ((count >> 16) & mask16);
  return count;
}


// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x) {
  int mask1 = 0x55 | (0x55 << 8); mask1 |= mask1 << 16;
  int mask2 = 0x33 | (0x33 << 8); mask2 |= mask2 << 16;
  int mask4 = 0x0F | (0x0F << 8); mask4 |= mask4 << 16;
  int mask8 = 0xFF | (0xFF << 16);
  
  x = ((x >> 1) & mask1) | ((x & mask1) << 1);
  x = ((x >> 2) & mask2) | ((x & mask2) << 2);
  x = ((x >> 4) & mask4) | ((x & mask4) << 4);
  x = ((x >> 8) & mask8) | ((x & mask8) << 8);
  x = (x << 16) | ((x >> 16) & 0xFF | (0xFF << 8));
  return x;
}