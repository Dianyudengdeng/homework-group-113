import socket
import ssl
import threading
import re
import secrets
from Cryptography import *


def handle_client(conn, ssl_conn):
    try:
        # 处理客户端连接的逻辑，这里假设收到的消息不超过1024字节
        received_data = ssl_conn.recv(1024)
        message_from_client = received_data.decode('utf-8')
        print("Received from client:", message_from_client)
        # 在这里处理接收到的数据，例如回复消息等
        if(message_from_client =="Prover"):
            message_to_client = "Hello, Prover! 请输入出身年份以及证明有效期限"
            ssl_conn.send(message_to_client.encode('utf-8'))  # 将字符串转换为字节串并发送消息
            while True:
                received_data = ssl_conn.recv(1024)
                message_from_client = received_data.decode('utf-8')
                match = re.match(r'(\d{4})-(\d{4})', message_from_client)
                if match:
                    birth_year = match.group(1)
                    validity_period = match.group(2)
                    print("Year of birth:", birth_year)
                    print("Validity period:", validity_period)
                    seed=secrets.token_hex(16)
                    k = int(validity_period) - int(birth_year)
                    c = s = sha224_hash((seed))
                    for i in range(k):
                        c = sha256_hash(c)
                    Sig_message = str(validity_period)+c
                    print(Sig_message)
                    sig=generate_signature(Sig_message,'E:\创新创业Project\Project6 Range Proof With Hash Function\Trusted_Issuer\Trusted_private_key.pem')
                    print(str(sig))
                    message_to_client =  f"{s}||{sig}"
                    ssl_conn.send(message_to_client.encode('utf-8'))  # 将字符串转换为字节串并发送消息

        if (message_from_client == "Verifier"):
                message_to_client = "Hello, Verifier! This is a message from the server."
                ssl_conn.send(message_to_client.encode('utf-8'))  # 将字符串转换为字节串并发送消息

    except Exception as e:
        print("Error handling client:", e)

    finally:
        # 关闭连接
        ssl_conn.close()
        conn.close()

context = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
context.load_cert_chain(certfile='certificate.pem', keyfile='Trusted_private_key.pem')

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('localhost', 12345))
server_socket.listen(5)  # 设置监听队列的长度

print("Waiting for connections...")

while True:
    conn, addr = server_socket.accept()
    ssl_conn = context.wrap_socket(conn, server_side=True)

    print("Connected to:", addr)

    # 创建线程来处理客户端连接
    client_thread = threading.Thread(target=handle_client, args=(conn, ssl_conn))
    client_thread.start()
