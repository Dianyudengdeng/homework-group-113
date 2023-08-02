import secrets

from Schnorr_Signature import *

def Batch_verify(public_key, message, signature,num):
    s = 0
    R = 0
    ep = 0
    for i in range(num):
        R = point_add(R,signature[i][0])
        s = (s+signature[i][1])%N
        e = sm3.sm3_hash(func.bytes_to_list(bytes(str(signature[i][0])+message[i], encoding='utf-8')))
        e = int(e, 16)
        ep = point_add(ep,point_multiply(e,public_key[i]))

    sG = point_multiply(s,G)
    R_ep = point_add(R,ep)
    return sG == R_ep

def Batch_verify_pro(public_key, message, signature,num):
    s = signature[0][1]
    R = signature[0][0]
    e = int(sm3.sm3_hash(func.bytes_to_list(bytes(str(signature[0][0]) + message[0], encoding='utf-8'))),16)
    ep = point_multiply(e, public_key[0])
    for i in range(1,num):
        a = secrets.randbelow(100)
        R = point_add(R,point_multiply(a,signature[i][0]))
        s = (s+a*signature[i][1])%N
        e = int(sm3.sm3_hash(func.bytes_to_list(bytes(str(signature[i][0])+message[i], encoding='utf-8'))),16)
        ep = point_add(ep,point_multiply(a*e,public_key[i]))

    sG = point_multiply(s,G)
    R_ep = point_add(R,ep)
    return sG == R_ep


def forge_signature(sk1,pk2,msg1,msg2):
    r2=secrets.randbelow(N)
    s2=secrets.randbelow(N)
    R2= point_multiply(r2,G)
    e2 = int(sm3.sm3_hash(func.bytes_to_list(bytes(str(R2)+ msg2, encoding='utf-8'))),16)
    R1 = point_inverse(point_multiply(e2,pk2))
    e1 = int(sm3.sm3_hash(func.bytes_to_list(bytes(str(R1)+ msg1, encoding='utf-8'))),16)
    s1 = (r2 + e1*sk1 - s2)%N
    print(f"生成的伪造签名对\nR1：{R1}\ns1:{s1}\nR2:{R2}\ns2:{s2}")
    return (R1,s1),(R2,s2)

if __name__=="__main__":

    num = 5
    sk = []
    pk = []
    Msg = []
    Sig = []
    for i in range(num):
        messagei =f"{i}"
        ski, pki = generate_key()
        k, signaturei = sign(ski, messagei)
        sk.append(ski)
        pk.append(pki)
        Msg.append(messagei)
        Sig.append(signaturei)

    if Batch_verify(pk, Msg, Sig,num):
        print("Batch Verification passed")
    else:
        print("Batch Verification failed")

    print("---------------Froge Signature---------------")
    sk1,pk1 = generate_key()
    sk2,pk2 = generate_key()
    msg1 = "111"
    msg2 = "222"
    Sig1,Sig2 = forge_signature(sk1,pk2,msg1,msg2)
    pk_1 = [pk1,pk2]
    Sig_1 =[Sig1,Sig2]
    Msg_1 = [msg1,msg2]
    if Batch_verify(pk_1, Msg_1, Sig_1,2):
        print("Batch Verification passed")
    else:
        print("Batch Verification failed")

    print("---------------Batch_verify_pro---------------")
    print("正常的签名对：")
    if Batch_verify_pro(pk, Msg, Sig,5):
        print("Batch Pro Verification passed")
    else:
        print("Batch Pro Verification failed")
    print("伪造的签名对：")
    if Batch_verify_pro(pk_1, Msg_1, Sig_1,2):
        print("Batch Pro Verification passed")
    else:
        print("Batch Pro Verification failed")