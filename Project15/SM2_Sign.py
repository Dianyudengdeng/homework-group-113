from gmssl import sm3, func
from tools import *
from Generate_K import *

def precompute(ID, a, b, G_X, G_Y, x_A, y_A):
    ENTL = str(get_bit_num(ID))
    joint = ENTL+ID+str(a)+str(b)+str(G_X)+str(G_Y)+str(x_A)+str(y_A)
    joint_b = bytes(joint, encoding='utf-8')
    digest = sm3.sm3_hash(func.bytes_to_list(joint_b))
    return int(digest, 16)

def sign(private_key, message, Z_A):
    M_1 = str(Z_A) + message
    M_b = bytes(M_1, encoding='utf-8')
    e = sm3.sm3_hash(func.bytes_to_list(M_b))
    e = int(e, 16)

    k = generate_k(message, private_key, N, get_bit_num(N), hash_function=hashlib.sha256)
    kG = point_multiply(k, G)

    r = (e + kG[0]) % N
    s = (mod_inverse(1 + private_key, N) * (k - r * private_key)) % N
    print(f"{message} 生成签名对:")
    print(f"r:{r}\ns:{s}")
    return (r, s)


def verify(public_key, ID, message, signature):
    r = signature[0]
    s = signature[1]

    Z_A  = precompute(ID, A, B, G_X, G_Y, public_key[0], public_key[1])
    M_1 = str(Z_A) + message
    M_b = bytes(M_1, encoding='utf-8')
    e = sm3.sm3_hash(func.bytes_to_list(M_b))  # str
    e = int(e, 16)
    t = (r + s) % N

    result = point_add(point_multiply(s, G), point_multiply(t, public_key))

    x1 = result[0]
    R = (e + x1) % N

    return R == r

if __name__=="__main__":
    ID = "202100460030"
    message="我是待签名的消息"
    sk, pk = generate_key()
    Z_A=precompute(ID, A, B, G_X, G_Y, pk[0], pk[1])
    signature = sign(sk, message, Z_A)
    if verify(pk, ID, message, signature):
        print("Verification passed")
    else:
        print("Verification failed")