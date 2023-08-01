#If only the hash of the signed message is required
#n forge signature (r_1,s_1)for d
from tools import *
def forge_signature(public_key):
    u = secrets.randbelow(N)
    v = secrets.randbelow(N)
    R_1 = point_add(point_multiply(u,G),point_multiply(v,public_key))
    # Choose (r_1 = x_1 mode n)
    r_1 = R_1[0]
    e_1 = r_1*u*mod_inverse(v,N)%N
    s_1 = r_1 *mod_inverse(v,N)%N
    return e_1,(r_1,s_1)

def verify(public_key, e, signature):#e = hash(m)
    r = signature[0]
    s = signature[1]

    w=mod_inverse(s,N)
    wG=point_multiply(w,G)
    wP=point_multiply(w,public_key)
    r_1,s_1=point_add(point_multiply(e,wG),point_multiply(r,wP))

    return r_1 == r

if __name__ == "__main__":
    sk,pk = generate_key()
    print(f"Private Key：{sk}\nPublic Key:{pk}")
    print()
    e_1,Sig_1 = forge_signature(pk)
    print(f"e_1:{e_1}\nr_1:{Sig_1[0]}\ns_1:{Sig_1[1]}")
    if  verify(pk, e_1, Sig_1):
        print("Forge_Signature Verification passed")
    else:
        print("Forge_Signature Verification failed")