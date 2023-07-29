import secrets
from tools import *
import socket
import random
import ast

def Gen_Key_p2(P1):
    d2 = secrets.randbelow(N)
    temp = point_multiply(mod_inverse(d2, N), P1)
    P = point_sub(temp, G)
    return d2, P

def Gen_Partial_Sig(d2, Q1, e):
    k2 = random.randint(0, N - 1)
    Q2 = point_multiply(k2, G)
    k3 = random.randint(0, N - 1)
    temp = point_multiply(k3, Q1)
    (x1, y1) = point_add(temp,Q2)
    r = (x1+e) % N
    s2 = (d2*k3) %N
    s3 = (d2*(r+k2))%N
    return r,s2,s3

if __name__ == "__main__":
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # 绑定服务器地址和端口
    server_address = ('localhost', 12345)
    server_socket.bind(server_address)

    # 监听连接
    server_socket.listen(1)

    print("等待连接...")

    # 等待客户端连接
    client_socket, client_address = server_socket.accept()


    P1 = client_socket.recv(1024).decode()
    P1 = ast.literal_eval(P1)
    print(f"收到P1：{P1}")
    print("---------------计算公钥P---------------")
    d2,P=Gen_Key_p2(P1)
    print(f"d2:{d2}\nP:{P}")
    print("---------------公布P---------------")
    message = str(P)
    client_socket.sendall(message.encode('utf-8'))
    print("---------------接收Q1,e---------------")
    recv = client_socket.recv(1024).decode()
    Q1,e = recv.split("||")
    Q1=ast.literal_eval(Q1)
    print(f"Q1:{Q1}\ne:{e}")

    print("---------------计算r，s2，s3---------------")
    r,s2,s3 = Gen_Partial_Sig(d2, Q1, int(e))
    print(f"r:{r}\ns2:{s2}\ns3:{s3}")
    print("---------------发送r，s2，s3---------------")
    message = f"{r}||{s2}||{s3}"
    client_socket.sendall(message.encode('utf-8'))

    client_socket.close()
    server_socket.close()