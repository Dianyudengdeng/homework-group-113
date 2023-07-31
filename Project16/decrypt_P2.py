import ast
import socket
import secrets
from tools import *

if __name__ == "__main__":
    print("---------------生成d2---------------")
    d2 = secrets.randbelow(N)
    print(f"d2:{d2}\n")
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # 绑定服务器地址和端口
    server_address = ('localhost', 12345)
    server_socket.bind(server_address)

    # 监听连接
    server_socket.listen(1)

    print("等待连接...")

    # 等待客户端连接
    client_socket, client_address = server_socket.accept()
    message = str(d2)
    client_socket.sendall(message.encode('utf-8'))
    print("---------------计算T2--------------")
    recv_T1 = client_socket.recv(1024).decode()
    T1=ast.literal_eval(recv_T1)
    T2=point_multiply(mod_inverse(d2,N),T1)
    print(f"T2:{T2}")
    message = str(T2)
    client_socket.sendall(message.encode('utf-8'))



    client_socket.close()
    server_socket.close()