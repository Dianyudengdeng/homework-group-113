import ast
import socket
from SM2_enc import *


if __name__ == "__main__":
    plaintext="202100460030"
    print("---------------生成d1---------------")
    d1 = secrets.randbelow(N)
    print(f"d1:{d1}\n")
    # 创建 TCP/IP 套接字
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # 连接服务器
    server_address = ('localhost', 12345)
    client_socket.connect(server_address)
    print("---------------额外步骤，计算公钥--------------")
    recv_d2 = client_socket.recv(1024).decode()
    P =point_multiply(mod_inverse(d1*int(recv_d2),N)-1,G)
    print("---------------生成待合作解密的密文--------------")
    cipher = SM2_enc(plaintext,P)
    print(f"cipher:{cipher}\n")
    C1,C2,C3=cipher
    print("---------------计算T1--------------")
    if cipher[0]:
        T1 = point_multiply(mod_inverse(d1,N),C1)
    print(f"T1:{T1}")
    message = str(T1)
    client_socket.sendall(message.encode('utf-8'))
    print("---------------解密--------------")
    recv_T2 = client_socket.recv(1024).decode()
    T2 = ast.literal_eval(recv_T2)
    point = point_sub(T2,C1)
    klen = len(C2) * 4
    x2 = hex(point[0])[2:]
    y2 = hex(point[1])[2:]
    t = KDF(x2 + y2, klen)
    M_1=XOR_dec(C2,t)
    tmp_b = bytes((x2 + M_1 + y2), encoding='utf-8')
    u = sm3.sm3_hash(func.bytes_to_list(tmp_b))
    if u==C3:
        print(f"decipher:{M_1}")
    client_socket.close()
