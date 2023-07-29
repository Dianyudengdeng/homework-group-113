import ast
import random
import socket
from tools import *
from gmssl import sm3, func
from SM2_Sign import *
import gmpy2

def Gen_Key_p1():
    d1 = secrets.randbelow(N)
    d1_inv = mod_inverse(d1, N)
    P1 = point_multiply(d1_inv, G)
    return d1, P1

def Compute_Q1(msg,private_key,Z):
    M_1 = str(Z) +msg
    M_b = bytes(M_1, encoding='utf-8')
    e = int(sm3.sm3_hash(func.bytes_to_list(M_b)),16)

    k1 = random.randint(0, N - 1)
    Q1 = point_multiply(k1, G)
    return Q1,e,k1

def Gen_Sig(d1, k1, s2,s3,r):
    d1=gmpy2.mpz(d1)
    k1 = gmpy2.mpz(k1)
    s2 = gmpy2.mpz(s2)
    s3 = gmpy2.mpz(s3)
    r = gmpy2.mpz(r)
    s = (d1*k1*s2+d1*s3-r)%N
    r=int(r)
    s=int(s)
    if s!=0 or s!=N-r:
        return (r,s)
    else:
        return None

if __name__ == "__main__":
    ID = "202100460030"
    print("---------------生成d1，P1---------------")
    d1,p1=Gen_Key_p1()
    print(f"d1:{d1}\nP1:{p1}")

    # 创建 TCP/IP 套接字
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # 连接服务器
    server_address = ('localhost', 12345)
    client_socket.connect(server_address)

    print("---------------发送P1---------------")
    message = str(p1)
    client_socket.sendall(message.encode('utf-8'))
    print("成功发送！")

    print("---------------接收P---------------")
    P = client_socket.recv(1024).decode()
    P = ast.literal_eval(P)
    print(f"P:{P}")
    print("---------------预计算获得Z---------------")
    Z = precompute(ID, A, B, G_X, G_Y, P[0], P[1])
    print(f"Z:{Z}")
    print("---------------计算Q1,e---------------")
    plaintext="two-party sign"
    Q1,e,k1 = Compute_Q1(plaintext, d1, Z)
    print(f"Q1:{Q1}\ne:{e}")
    print("---------------发送Q1,e---------------")
    message = f"{Q1}||{e}"
    client_socket.sendall(message.encode('utf-8'))
    print("---------------接收r，s2，s3---------------")
    recv = client_socket.recv(1024).decode()
    r,s2,s3 = recv.split("||")
    print("---------------生成签名(r,s)---------------")
    Sig = Gen_Sig(d1, k1, s2, s3, r)
    if Sig:
        print(f"(r,s):{Sig}")
    else:
        print("生成签名失败")

    print("---------------验证签名(r,s)---------------")
    if verify(P, ID, plaintext, Sig):
        print("Verification passed")
    else:
        print("Verification failed")
    client_socket.close()
