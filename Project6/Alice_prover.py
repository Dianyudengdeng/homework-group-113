import socket
import ssl
import datetime
from Cryptography import *

while 1:
    choice=input("请输入你想要执行的操作：1：获得s与Sigc 2：向Verifier提供证明\n")
    # 与Trusted Issuer交互获得s和Sigc
    if choice=="1":
        try:
            context = ssl.create_default_context(ssl.Purpose.SERVER_AUTH)
            context.load_verify_locations('E:\创新创业Project\Project6 Range Proof With Hash Function\Trusted_Issuer\certificate.pem')

            client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client_socket.connect(('localhost', 12345))

            ssl_conn_Alice = context.wrap_socket(client_socket, server_hostname='Trusted_Issuer')
            print("Connected to Trusted_Issuer")

            message = "Prover"
            ssl_conn_Alice.send(message.encode('utf-8'))  # 将字符串转换为字节串并发送消息

            received_data = ssl_conn_Alice.recv(1024)  # 接收最多1024字节的数据
            print("Received from server:", received_data.decode('utf-8'))  # 将接收到的字节串转换为字符串并打印

            birth_year = int(input("请输入出生年份："))
            validity_period=int(input("请输入有效期限："))
            message = f"{birth_year}-{validity_period}"
            ssl_conn_Alice.send(message.encode('utf-8'))  # 将字符串转换为字节串并发送消息
            received_data = ssl_conn_Alice.recv(1024)  # 接收最多1024字节的数据
            s,sig = (received_data.decode('utf-8').split('||'))
            print(f"Prover从Trusted Issuer接收到的\ns:{s}\nsig:{sig}")

            ssl_conn_Alice.close()
        except Exception as e:
            print("Error handling client:", e)


    elif choice=="2":
    # 向Verifier：Bob提供证明
        try:
            context = ssl.create_default_context(ssl.Purpose.SERVER_AUTH)
            context.load_verify_locations('E:\创新创业Project\Project6 Range Proof With Hash Function\Bob\Bob.crt')

            client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client_socket.connect(('localhost', 20000))

            ssl_conn_Alice = context.wrap_socket(client_socket, server_hostname='Bob')
            print("Connected to Trusted_Issuer")

            message = "Prover"
            ssl_conn_Alice.send(message.encode('utf-8'))  # 将字符串转换为字节串并发送消息

            received_data = ssl_conn_Alice.recv(1024)  # 接收最多1024字节的数据
            print("Received from server:", received_data.decode('utf-8'))  # 将接收到的字节串转换为字符串并打印

            limit = 18
            #获取当前年份以计算
            current_datetime = datetime.datetime.now()
            current_year = current_datetime.year
            d0 = current_year-limit-birth_year
            p = s
            for i in range(d0):
                p = sha256_hash(p)
            message=f"{validity_period}||{p}||{sig}"
            ssl_conn_Alice.send(message.encode('utf-8'))  # 将字符串转换为字节串并发送消息
            received_data = ssl_conn_Alice.recv(1024)  # 接收最多1024字节的数据
            print(received_data.decode())
            ssl_conn_Alice.close()
        except Exception as e:
             print("Error handling client:", e)
