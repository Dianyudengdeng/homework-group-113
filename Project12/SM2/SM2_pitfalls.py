from SM2_Signature import *
from tools import *

#1.Leaking k leads to leaking of d
def leaking_k(k,Sig):
    d = (mod_inverse(Sig[0]+Sig[1],N)*(k-Sig[1]))%N
    print(f"Leaking k->d:{d}")
    return d

#2.Reusing k leads to leaking of d
def reusing_k(Sig1,Sig2):
    r1,s1 = Sig1[0],Sig1[1]
    r2,s2 = Sig2[0],Sig2[1]
    d=((s2-s1)*mod_inverse((s1-s2+r1-r2),N))%N
    print(f"Reusing k->d:{d}")
    return d

#3.Reusing k by different users leads to leaking of d
def Reusing_k_different_users(k,Sig):
    d = ((k-Sig[1])*mod_inverse((Sig[0]+Sig[1]),N))%N
    print(f"Reusing k by different users->d:{d}")
    return d

if __name__=="__main__":
    ID = "202100460030"
    message="我是待签名的消息111"
    sk, pk = generate_key()
    print(f"私钥：{sk}")
    print(f"公钥：{pk}")
    Z_A=precompute(ID, A, B, G_X, G_Y, pk[0], pk[1])
    k,signature = sign(sk, message, Z_A)
    if verify(pk, ID, message, signature):
        print("Verification passed")
    else:
        print("Verification failed")
    print(f"使用的随机数k：{k}\n")

    # 1.Leaking k leads to leaking of d
    print('# 1.Leaking k leads to leaking of d')
    leaking_k(k,signature)

    print()
    # 2.Reusing k leads to leaking of d: ECDSA、Schnorr、SM2-sig
    # 使用k再生成一个签名
    print('# 2.Reusing k leads to leaking of d')
    message_1 = "我是待签名的消息222"
    signature_1 = sign_k(sk, message_1, k, Z_A)
    reusing_k(signature,signature_1)

    print()
    # 3.Reusing k by different users leads to leaking of d
    print('# 3.Reusing k by different users leads to leaking of d')
    print('另一个用户Bob进行签名')
    ID_Bob = "202100460031"
    message_Bob = "我是待签名的消息Bob"
    sk_Bob, pk_Bob = generate_key()
    print(f"私钥_Bob：{sk_Bob}")
    print(f"公钥_Bob：{pk_Bob}")
    Z_A_Bob = precompute(ID_Bob, A, B, G_X, G_Y, pk_Bob[0], pk_Bob[1])
    signature_Bob = sign_k(sk_Bob, message_Bob, k, Z_A_Bob)
    print("Alice deduce Bob secreet key")
    Reusing_k_different_users(k, signature_Bob)
    print("Bob deduce Alice secreet key")
    Reusing_k_different_users(k, signature)
