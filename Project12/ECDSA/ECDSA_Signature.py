from tools import *
from Generate_K import *
from gmssl import sm3, func

def sign(private_key, message):
    k = generate_k(message, private_key, N, get_bit_num(N), hash_function=hashlib.sha256)
    R = point_multiply(k, G)
    r = R[0]%N

    e = sm3.sm3_hash(func.bytes_to_list(bytes(message, encoding='utf-8')))
    e = int(e, 16)
    s = (mod_inverse(k, N)*(e + private_key*r))%N
    print(f"{message} 生成签名对:")
    print(f"r:{r}\ns:{s}")
    return k,(r, s)

def sign_k(private_key, message, k):
    R = point_multiply(k, G)
    r = R[0] % N

    e = sm3.sm3_hash(func.bytes_to_list(bytes(message, encoding='utf-8')))
    e = int(e, 16)
    s = (mod_inverse(k, N) * (e + private_key * r)) % N
    print(f"{message} 生成签名对:")
    print(f"r:{r}\ns:{s}")
    return  (r, s)

def verify(public_key, message, signature):
    r = signature[0]
    s = signature[1]
    e = sm3.sm3_hash(func.bytes_to_list(bytes(message, encoding='utf-8')))
    e = int(e, 16)

    w=mod_inverse(s,N)
    wG=point_multiply(w,G)
    wP=point_multiply(w,public_key)
    r_1,s_1=point_add(point_multiply(e,wG),point_multiply(r,wP))

    return r_1 == r

if __name__=="__main__":
    message="我是待签名的消息"
    sk, pk = generate_key()
    k,signature = sign(sk, message)
    if verify(pk, message, signature):
        print("Verification passed")
    else:
        print("Verification failed")