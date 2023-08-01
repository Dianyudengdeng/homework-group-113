import hashlib
import hmac
import math
import gmpy2

def bits2octets(bits, mlen):
    full_bytes = bits // 8
    extra_bits = bits % 8
    if extra_bits > 0:
        full_bytes += 1
    padding_bytes = mlen - full_bytes
    # 使用 gmpy2 进行大整数转换
    bits_bigint = gmpy2.mpz(bits)
    return b'\x00' * padding_bytes + gmpy2.digits(bits_bigint, 256)

def bits2int(bits, qlen):
    q = 1 << qlen
    # 使用 gmpy2 进行大整数转换
    bits_bigint = gmpy2.mpz(bits)
    return gmpy2.f_mod(bits_bigint, q)


def generate_k(msg, private_key, q, q_bits=256, hash_function=hashlib.sha256):
    """
    Generate the deterministic random value k according to RFC 6979.

    Parameters:
        msg (bytes): The message to be signed (hashed).
        private_key (int): The private key used for signing.
        q_bits (int): The bit length of the elliptic curve order (q).
        hash_function (callable): The hash function to use for HMAC (default: SHA-256).

    Returns:
        int: The deterministic random value k.
    """
    hlen = hash_function().digest_size * 8
    qlen = math.ceil(q_bits / 8) * 8

    # Step a
    h1 = hash_function(msg.encode()).digest()

    # Step b
    V = b'\x01' * math.ceil(hlen / 8)

    # Step c
    K = b'\x00' * math.ceil(hlen / 8)

    # Step d
    K = hmac.new(K, V + b'\x00' + private_key.to_bytes(math.ceil(q_bits / 8), byteorder='big') + h1, hash_function).digest()
    # Step e
    V = hmac.new(K, V, hash_function).digest()

    # Step f
    K = hmac.new(K, V + b'\x01' + private_key.to_bytes(math.ceil(q_bits / 8), byteorder='big') + h1, hash_function).digest()

    # Step g
    V = hmac.new(K, V, hash_function).digest()

    # Step h
    T = b''
    tlen = 0

    while tlen < qlen:
        V = hmac.new(K, V, hash_function).digest()
        T = T + V

        tlen = len(T) * 8
        k = bits2int(int.from_bytes(T, byteorder='big'), qlen)

        if 1 <= k < q - 1:
            return k

        K = hmac.new(K, V + b'\x00', hash_function).digest()
        V = hmac.new(K, V, hash_function).digest()

    raise ValueError("Failed to generate a valid k value.")
