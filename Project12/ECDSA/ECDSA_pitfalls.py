from ECDSA_Signature import *
from tools import *

#1.Leaking k leads to leaking of d
def leaking_k(k,Sig,message):
    e = sm3.sm3_hash(func.bytes_to_list(bytes(message, encoding='utf-8')))  # e = hash(m)
    e = int(e, 16)
    d = (Sig[1] * k - e) % N * mod_inverse(Sig[0], N) % N
    print(f"Leaking k->d:{d}")
    return d

#2.Reusing k leads to leaking of d
def reusing_k(Sig1,Sig2,msg1,msg2):
    r1,s1 = Sig1[0],Sig1[1]
    r2,s2 = Sig2[0],Sig2[1]
    e1 = sm3.sm3_hash(func.bytes_to_list(bytes(msg1, encoding='utf-8')))  # e = hash(m)
    e1 = int(e1, 16)
    e2 = sm3.sm3_hash(func.bytes_to_list(bytes(msg2, encoding='utf-8')))  # e = hash(m)
    e2 = int(e2, 16)
    d = (((e1 - e2) * s2) % N * mod_inverse((s1 - s2) % N, N) - e2) * mod_inverse(r1, N) % N
    print(f"Reusing k->d:{d}")
    return d



#3.Reusing k by different users leads to leaking of d
def Reusing_k_different_users(k,Sig,message):
    e = sm3.sm3_hash(func.bytes_to_list(bytes(message, encoding='utf-8')))  # e = hash(m)
    e = int(e, 16)
    d = (Sig[1] * k - e) % N * mod_inverse(Sig[0], N) % N
    print(f"Reusing k by different users->d:{d}")
    return d

if __name__=="__main__":
    message="我是待签名的消息111"
    sk, pk = generate_key()
    print(f"私钥：{sk}")
    print(f"公钥：{pk}")
    k,signature = sign(sk, message)
    if verify(pk, message, signature):
        print("Verification passed")
    else:
        print("Verification failed")
    print(f"使用的随机数k：{k}\n")

    print()
    # 1.Leaking k leads to leaking of d
    print('# 1.Leaking k leads to leaking of d')
    leaking_k(k,signature,message)

    print()
    # 2.Reusing k leads to leaking of d: ECDSA、Schnorr、SM2-sig
    # 使用k再生成一个签名
    print('# 2.Reusing k leads to leaking of d')
    message_1 = "我是待签名的消息222"
    signature_1 = sign_k(sk, message_1, k)
    reusing_k(signature,signature_1,message,message_1)

    print()
    # 3.Reusing k by different users leads to leaking of d
    print('# 3.Reusing k by different users leads to leaking of d')
    print('另一个用户Bob进行签名')
    ID_Bob = "202100460031"
    message_Bob = "我是待签名的消息Bob"
    sk_Bob, pk_Bob = generate_key()
    print(f"私钥_Bob：{sk_Bob}")
    print(f"公钥_Bob：{pk_Bob}")
    signature_Bob = sign_k(sk_Bob, message_Bob, k)
    print("Alice deduce Bob secreet key")
    Reusing_k_different_users(k, signature_Bob,message_Bob)
    print("Bob deduce Alice secreet key")
    Reusing_k_different_users(k, signature,message)

    print()
    # 4.(r,s) and (r,-s)are both valid signatures
    print('# 4.(r,s) and (r,-s)are both valid signatures')
    if verify(pk, message, signature):
        print("(r,s) Verification passed")
    else:
        print("(r,s) Verification failed")
    signature_1=(signature[0],(-signature[1])%N)
    if verify(pk, message, signature_1):
        print("(r,-s) Verification passed")
    else:
        print("(r,-s) Verification failed")