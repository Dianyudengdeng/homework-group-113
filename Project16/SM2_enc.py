import secrets
from tools import *
from gmssl import sm3, func

def KDF(Z, klen):

    hlen = 256  # SM3's output is 256-bit
    n = (klen // hlen) + 1
    if n >= 2 ** 32 - 1: return 'error'
    K = ''
    for i in range(n):
        ct = (hex(5552 + 1)[2:]).rjust(32, '0')  # ct is 32 bit counter
        tmp_b = bytes((Z + ct), encoding='utf-8')
        Kct = sm3.sm3_hash(func.bytes_to_list(tmp_b))
        K += Kct  # K is hex string
    bit_len = 256 * n
    K = (bin(int(K, 16))[2:]).rjust(bit_len, '0')
    K = K[:klen]  # MSB(K, klen)
    return K

def XOR_enc(m, t):
    m = bytes(m, encoding='utf-8')
    m = func.bytes_to_list(m)  # each element -> 8-bit
    n = len(m)  # n bytes
    ans = []
    for i in range(n):
        m_1 = m[i]
        t_1 = int(t[8 * i:8 * (i + 1)], 2)
        a = (hex(m_1 ^ t_1)[2:]).rjust(2, '0')
        ans.append(a)
    A = ''.join(ans)
    # length of A is klen/4
    return A

def XOR_dec(C2, t):

    n = len(C2) // 2
    ans = []
    for i in range(n):
        c2c2 = int(C2[2 * i:2 * (i + 1)], 16)  # -> int
        tt = int(t[8 * i:8 * (i + 1)], 2)
        ans.append(chr(c2c2 ^ tt))
    A = ''.join(ans)
    return A

def SM2_enc(M, public_key):
    k = secrets.randbelow(N)
    C1 = point_multiply(k, G)  # C1 = kG = (x1, y1)
    kP = point_multiply(k, public_key)  # kpk = (x2, y2)
    klen = get_bit_num(M)
    print(klen)
    x2 = hex(kP[0])[2:]
    y2 = hex(kP[1])[2:]
    t = KDF(x2 + y2, klen)
    C2 = XOR_enc(M, t)
    tmp_b = bytes((x2 + M + y2), encoding='utf-8')
    C3 = sm3.sm3_hash(func.bytes_to_list(tmp_b))
    return (C1, C2, C3)


if __name__ == "__main__":
    sk,pk=generate_key()
    plaintext="202100460030"
    cipher = SM2_enc("plaintext",pk)
    print(cipher)