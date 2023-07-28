from sympy import GF
from sympy import Rational
from tools import *
import hashlib

DST = b'QUUX-V01-CS02-with-secp256k1_XMD:SHA-256_SSWU_RO_'


def expand_message_xmd(msg, DST, len_in_bytes):
    # Step 1: Calculate ell
    b_in_bytes = 32  # 假设 b = 256，即 SHA-256 输出大小为 32 字节
    ell = (len_in_bytes + b_in_bytes - 1) // b_in_bytes

    # Step 2: Check conditions
    if ell > 255 or len_in_bytes > 65535 or len(DST) > 255:
        raise ValueError("Invalid parameters: ell > 255 or len_in_bytes > 65535 or len(DST) > 255")

    # Step 3: Calculate DST_prime
    I2OSP_DST = len(DST).to_bytes(1, 'big')
    DST_prime = DST + I2OSP_DST

    # Step 4: Calculate Z_pad
    s_in_bytes = 64  # 假设使用 SHA-256，输入块大小为 64 字节
    Z_pad = b'\x00' * s_in_bytes

    # Step 5: Calculate l_i_b_str
    l_i_b_str = len_in_bytes.to_bytes(2, 'big')

    # Step 6: Construct msg_prime
    msg_prime = Z_pad + msg + l_i_b_str + b'\x00' + DST_prime

    # Step 7: Calculate b_0
    b_0 = hashlib.sha256(msg_prime).digest()

    # Step 8: Calculate b_1
    b_1 = hashlib.sha256(b_0 + b'\x01' + DST_prime).digest()

    # Steps 9-10: Calculate b_i for i in (2, ..., ell)
    uniform_bytes = b_1
    for i in range(2, ell + 1):
        b_i = hashlib.sha256(bytes([a ^ b for a, b in zip(b_0, uniform_bytes)]) + bytes([i]) + DST_prime).digest()
        uniform_bytes += b_i

    # Step 12: Return the first len_in_bytes bytes of uniform_bytes
    return uniform_bytes[:len_in_bytes]

def CMOV(a, b, c, F):
    mask = -c  # If c is True, mask = -1; otherwise, mask = 0
    return (a * mask) + (b * (1 + mask))

def sgn0(x):
    if x is None:
        return 0
    return int(x < 0)


def inv0(x, F):
    # Compute x^(q - 2) as the multiplicative inverse
    q_2=F.characteristic() - 2
    result = F(1)
    base = x
    while q_2 > 0:
        if q_2 % 2 == 1:
            result *= base
        base *= base
        q_2 //= 2

    # Check if the result is 0 or 1 in the field F
    return result

def is_square(x, F):
    q_minus_1_div_2 = (F.characteristic() - 1) // 2

    # Exponentiation by Squaring
    result = F(1)
    base = x
    while q_minus_1_div_2 > 0:
        if q_minus_1_div_2 % 2 == 1:
            result *= base
        base *= base
        q_minus_1_div_2 //= 2

    # Check if the result is 0 or 1 in the field F
    return result == 0 or result == 1


def sqrt(x, F):
    q = F.characteristic()
    if x == 0:
        return F(0), F(0)
    power = (q - 1) // 2
    result = x ** power
    # Check if the result is 0 or 1 in the field F
    if result == 0:
        return F(0), F(0)
    elif result == 1:
        return result, -result
    else:
        return None, None


def map_to_curve_svdw(u, F, A, B, Z):
    # Constants
    c1 = F(Z)
    c2 = -Z / 2
    c3_positive, c3_negative = sqrt(-c1 * (3 * Z ** 2 + 4 * A), F)
    if c3_positive is not None and sgn0(c3_positive) == 0:
        c3 = c3_positive
    elif c3_negative is not None and sgn0(c3_negative) == 0:
        c3 = c3_negative
    else:
        raise ValueError("No valid c3 found.")
    c4 = -4 * c1 / (3 * Z**2 + 4 * A)
    c2 = Rational(c2)
    c4 = Rational(c4)
    tv1 = u**2
    tv1 = tv1 * c1
    tv2 = 1 + tv1
    tv1 = 1 - tv1
    tv3 = tv1 * tv2
    tv3 = inv0(tv3,F)
    tv4 = u * tv1
    tv4 = tv4 * tv3
    tv4 = tv4 * c3
    x1 = c2 - tv4
    # Step 11
    gx1 = x1**2
    gx1 = gx1 + A
    gx1 = gx1 * x1
    gx1 = gx1 + B
    e1 = is_square(gx1,F)
    x2 = c2 + tv4
    gx2 = x2**2
    gx2 = gx2 + A

    gx2 = gx2 * x2
    gx2 = gx2 + B
    e2 = is_square(gx2,F) and not e1
    x3 = tv2**2
    x3 = x3 * tv3
    x3 = x3**2
    x3 = x3 * c4
    x3 = x3 + Z
    x = CMOV(x3, x1, e1, F)
    x = CMOV(x, x2, e2, F)
    gx = x**2
    gx = gx + A
    gx = gx * x
    gx = gx + B
    y = sqrt(gx,F)
    e3 = sgn0(u) == sgn0(y)
    y = CMOV(-y, y, e3, F)
    return (x, y)


if __name__ == "__main__":
    # Example usage:
    msg =b"202100460030"  # Your message


    output = expand_message_xmd(msg, DST,96)
    print(output.hex())
    u0=output.hex()[:96]
    u1=output.hex()[96:]
    F = GF(P)
    Z = 1
    Q0=map_to_curve_svdw(int(u0,16), F, A, B, Z)
    print(Q0)
    Q1=map_to_curve_svdw(int(u1,16), F, A, B, Z)
    R = point_add(Q0,Q1)
    print(R)

