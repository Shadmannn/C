/*
 * Bitwise operators work on the individual bits inside an integer.
 * Normal operators treat a number as one value. Bitwise operators
 * treat a number as a row of bits and change each bit on its own.
 *
 * They only work on integer types: char, short, int, long, and their
 * signed and unsigned versions. They do not work on float or double.
 *
 * There are six bitwise operators.
 *
 *     &    AND       both bits must be 1
 *     |    OR        at least one bit is 1
 *     ^    XOR       the two bits must be different
 *     ~    NOT       flip every bit
 *     <<   left shift
 *     >>   right shift
 *
 * Do not confuse & with &&, or | with ||.
 *
 *     &    bit by bit
 *     &&   whole value is true or false
 *     |    bit by bit
 *     ||   whole value is true or false
 *
 *     1 & 2   = 0     (0001 & 0010, no common 1-bit)
 *     1 && 2  = 1     (both non-zero, so both true)
 *
 * This mistake is common. Remember it.
 *
 * The four logical bitwise operators.
 *
 *     x       1 1 0 0 1 1 0 0
 *     y       1 0 1 0 1 0 1 0
 *     x & y   1 0 0 0 1 0 0 0
 *     x | y   1 1 1 0 1 1 1 0
 *     x ^ y   0 1 1 0 0 1 1 0
 *     ~x      0 0 1 1 0 0 1 1
 *
 * AND is used to clear bits (called masking).
 * OR is used to set bits.
 * XOR is used to toggle bits.
 * NOT is used to build masks.
 *
 * Shifts.
 *
 * Left shift (<<) moves every bit left by n positions. The new bits on
 * the right are 0. The bits that fall off the left are lost.
 *
 *     x         0 0 0 0 1 1 0 1    (13)
 *     x << 2    0 0 1 1 0 1 0 0    (52)
 *
 * Left shift by n is the same as multiplying by 2^n, as long as no
 * 1-bit falls off the top.
 *
 * Right shift (>>) moves every bit right by n positions. What fills
 * the empty bits on the left depends on the type.
 *
 *     unsigned: always fills with 0.
 *     signed:   fills with the sign bit on almost every modern machine
 *               (x86, ARM). This is called an arithmetic shift.
 *
 * Right shift by n is the same as integer division by 2^n.
 *
 * If you shift bits on purpose, use unsigned types. Signed shifts can
 * behave differently on different compilers.
 *
 * Why bit masks are written in hex or octal.
 *
 *     0000 0000 0111 1111
 *     decimal: 127
 *     octal:   0177
 *     hex:     0x7F
 *
 * Each octal digit is 3 bits. Each hex digit is 4 bits. So octal and
 * hex let you see the bit pattern at a glance. Decimal does not. This
 * is why K&R writes 0177 and not 127.
 *
 * Portability trap: hardcoded widths.
 *
 *     x = x & 0177700;     -- works if int is 16 bits, wrong otherwise 
 *     x = x & ~077;        -- correct on 16, 32, 64 bit machines 
 *
 * 0177700 assumes a 16-bit int. On a 32-bit int it leaves the top 16
 * bits alone. On 64-bit it leaves 48 bits alone. ~077 uses the natural
 * width of int on whatever machine you compile on. The compiler
 * computes ~077 at compile time, so there is no runtime cost.
 *
 * Never hardcode integer widths. Express masks as ~(something small).
 *
 * getbits example.
 *
 *     getbits(x, p, n) returns the n bits of x starting at position p,
 *     right-aligned. Position 0 is the rightmost bit.
 *
 *     (x >> (p + 1 - n)) & ~(~0 << n)
 *
 * Example: x = 0b11011100 (220), p = 4, n = 3.
 *
 *     bit  7  6  5  4  3  2  1  0
 *     x    1  1  0  1  1  1  0  0
 *
 * Positions 4, 3, 2 are 1, 1, 1. Answer should be 111 = 7.
 *
 *     shift amount = 4 + 1 - 3 = 2
 *     x >> 2      = 0 0 1 1 0 1 1 1    (the target bits are at the bottom)
 *
 *     ~0          = 1 1 1 1 1 1 1 1
 *     ~0 << 3     = 1 1 1 1 1 0 0 0
 *     ~(~0 << 3)  = 0 0 0 0 0 1 1 1    (mask of n ones)
 *
 *     result = 00110111 & 00000111 = 00000111 = 7
 *
 * Read the expression from right to left:
 *
 *     ~(~0 << n)           make a mask of n ones
 *     x >> (p + 1 - n)     line up the target bits
 *     ... & ...            keep only those bits
 *
 * Why a kernel developer uses this.
 *
 * Hardware registers. A driver reads a 32-bit register, checks bits to
 * see if the device is ready, sets bits to start a transfer, clears
 * bits to acknowledge an interrupt.
 *
 *     if (readl(reg) & STATUS_READY)
 *         ...
 *
 *     writel(readl(reg) | START_BIT, reg);
 *
 *     writel(readl(reg) & ~ACK_BIT, reg);
 *
 * Permissions. Unix file mode is a bitmask.
 *
 *     if (mode & S_IWUSR)
 *     			owner can write 
 *
 * Page tables. Each entry has bits for present, writable, user, and
 * executable. Every page fault handler manipulates these bits.
 *
 * Hashes and random numbers. XOR, shifts, and rotations are the core
 * of many kernel hash functions.
 *
 * Why a security person cares.
 *
 * Confusing & with &&. A permission check written as `if (flags & 0x01)`
 * when the author meant `&&` becomes a no-op. All non-zero flags pass.
 *
 * Signed right shift. Right-shifting a negative signed value is
 * implementation-defined. Moving to a new compiler can change the
 * behavior of a security check.
 *
 * Wrong mask width. A mask written for 16-bit ints leaves the top
 * bits untouched on modern ints. Blocked becomes allowed.
 *
 * Shifting by n >= width. Undefined behavior. On x86 it often wraps
 * around and does nothing, which is a very sneaky bug.
 *
 * Weak XOR ciphers. XOR alone with a repeating key is trivially broken.
 * The problem is the design, not XOR itself.
 *
 * Compiling and inspecting.
 *
 * Linux:
 *
 *     gcc -g -O0 2.9_bitwise_operators.c -o 2.9_demo
 *     ./2.9_demo
 *
 *     gdb ./2.9_demo
 *     (gdb) break getbits
 *     (gdb) run
 *     (gdb) layout asm
 *     (gdb) info registers rdi rsi rdx
 *     (gdb) stepi
 *
 * Linux x86-64 passes the first six integer arguments in rdi, rsi, rdx,
 * rcx, r8, r9. Inside getbits, rdi = x, rsi = p, rdx = n.
 *
 * Windows (MSYS2 or MinGW):
 *
 *     gcc -g -O0 2.9_bitwise_operators.c -o 2.9_demo.exe
 *     2.9_demo.exe
 *
 * x64dbg shows the same thing on Windows. Windows x64 passes the first
 * four integer arguments in rcx, rdx, r8, r9. So x = rcx, p = rdx,
 * n = r8.
 *
 * Instructions to look for:
 *
 *     shr    shift right
 *     shl    shift left
 *     and    AND
 *     or     OR
 *     xor    XOR
 *     not    NOT
 *
 * At -O3 the compiler may replace getbits with a single instruction
 * like bextr (bit field extract) on CPUs with BMI1/BMI2.
 *
 * long is different between Linux and Windows.
 *
 *     Linux x86-64   LP64    sizeof(long) == 8
 *     Windows x64    LLP64   sizeof(long) == 4
 *
 * ~0UL is 64 bits of ones on Linux, 32 bits on Windows. If width
 * matters, use int or uint32_t / uint64_t from stdint.h.
 */

#include <stdio.h>

static void print_binary8(unsigned char val)
{
	int i;

	for (i = 7; i >= 0; i--)
		printf("%d", (val >> i) & 1);
}

static unsigned int getbits(unsigned int x, int p, int n)
{
	return (x >> (p + 1 - n)) & ~(~0 << n);
}

int main(void)
{
	unsigned int x = 0b11011100;
	int p = 4;
	int n = 3;
	unsigned int extracted;
	unsigned char val = 0b10111101;
	unsigned char low7;

	printf("x           : ");
	print_binary8((unsigned char)x);
	printf("  (%u)\n", x);

	extracted = getbits(x, p, n);
	printf("getbits(4,3): ");
	print_binary8((unsigned char)extracted);
	printf("  (%u)\n\n", extracted);

	printf("val         : ");
	print_binary8(val);
	printf("\n");

	low7 = val & 0177;
	printf("val & 0177  : ");
	print_binary8(low7);
	printf("\n\n");

	printf("1 & 2       = %d\n", 1 & 2);
	printf("1 && 2      = %d\n", 1 && 2);
	printf("\n");
	printf("0xAB ^ 0x5A             = 0x%02X\n", 0xAB ^ 0x5A);
	printf("(0xAB ^ 0x5A) ^ 0x5A    = 0x%02X\n", (0xAB ^ 0x5A) ^ 0x5A);

	return 0;
}