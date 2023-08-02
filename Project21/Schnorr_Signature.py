from tools import *
from Generate_K import *
from gmssl import sm3, func

def sign(private_key, message):
    k = generate_k(message, private_key, N, get_bit_num(N), hash_function=hashlib.sha256)
    R = point_multiply(k, G)
    R_M = str(R)+message

    e = sm3.sm3_hash(func.bytes_to_list(bytes(R_M, encoding='utf-8')))
    e = int(e, 16)
    s = (k+e*private_key)%N
    print(f"{message} 生成签名对:")
    print(f"r:{R}\ns:{s}")
    return k,(R, s)


def sign_k(private_key, message, k):
    R = point_multiply(k, G)
    R_M = str(R) + message

    e = sm3.sm3_hash(func.bytes_to_list(bytes(R_M, encoding='utf-8')))
    e = int(e, 16)
    s = (k + e * private_key) % N
    print(f"{message} 生成签名对:")
    print(f"R:{R}\ns:{s}")
    return (R, s)


def verify(public_key, message, signature):
    R = signature[0]
    s = signature[1]
    e = sm3.sm3_hash(func.bytes_to_list(bytes(str(R)+message, encoding='utf-8')))
    e = int(e, 16)

    sG=point_multiply(s,G)
    R_ep = point_add(R,point_multiply(e,public_key))
    return sG == R_ep

if __name__=="__main__":
    message="我是待签名的消息"
    sk, pk = generate_key()
    k,signature = sign(sk, message)
    if verify(pk, message, signature):
        print("Verification passed")
    else:
        print("Verification failed")