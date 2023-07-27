import ECDSA.ECDSA_Signature as ECDSA
import SM2.SM2_Signature as SM2
import Schnorr.Schnorr_Signature as Schnorr
from tools import *
from gmssl import sm3, func

def ECDSA_SM2(Sig_E,Sig_S,message):
    r1,s1=Sig_E
    r2,s2=Sig_S

    e1 = sm3.sm3_hash(func.bytes_to_list(bytes(message, encoding='utf-8')))
    e1 = int(e1, 16)
    temp1 = (s1 * s2 - e1) % N
    temp2 = (r1 - s1 * s2 - s1 * r2) % N
    temp2 = mod_inverse(temp2, N)
    d = temp1 * temp2 % N
    print(f"SM2:same d and k with ECDSA->d:{d}")
    return d

def ECDSA_Schnorr(Sig_E,Sig_S,msg1,msg2):
    r, s1 = Sig_E
    R, s2 = Sig_S
    e1 = sm3.sm3_hash(func.bytes_to_list(bytes(msg1, encoding='utf-8')))
    e1 = int(e1, 16)
    e2 = sm3.sm3_hash(func.bytes_to_list(bytes(str(R) + msg2, encoding='utf-8')))
    e2 = int(e2, 16)
    temp1 = (s2 - mod_inverse(s1, N) * e1) % N
    temp2 = (mod_inverse(s1, N) * r + e2) % N
    d = temp1* mod_inverse(temp2, N) % N
    print(f"Schnorr:same d and k with ECDSA->d:{d}")
    return d

if __name__=="__main__":
    msg1="ECDSA"
    sk, pk = generate_key()
    k,signature_ECDSA = ECDSA.sign(sk, msg1)
    if ECDSA.verify(pk, msg1, signature_ECDSA):
        print("Verification passed")
    else:
        print("Verification failed")

    print()
    #SM2
    print("# SM2")
    ID = "202100460030"
    msg2="SM2"
    Z_A = SM2.precompute(ID, A, B, G_X, G_Y, pk[0], pk[1])
    signature_SM2 = SM2.sign_k(sk, msg2, k, Z_A)
    if SM2.verify(pk, ID, msg2, signature_SM2):
        print("Verification passed")
    else:
        print("Verification failed")

    print(f"\nsk:{sk}")
    ECDSA_SM2(signature_ECDSA, signature_SM2, msg1)

    print()
    #Schnorr
    msg3="Schnorr"
    signature_Schnorr = Schnorr.sign_k(sk, msg3,k)
    if Schnorr.verify(pk, msg3, signature_Schnorr):
        print("Verification passed")
    else:
        print("Verification failed")
    print(f"\nsk:{sk}")
    ECDSA_Schnorr(signature_ECDSA, signature_Schnorr, msg1, msg3)