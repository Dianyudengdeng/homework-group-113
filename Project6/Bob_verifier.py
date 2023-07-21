import socket
import ssl
import threading
import datetime
from Cryptography import *
import ast

def handle_client(conn, ssl_conn):
    try:
        # 处理客户端连接的逻辑，这里假设收到的消息不超过1024字节
        received_data = ssl_conn.recv(1024)
        message_from_client = received_data.decode('utf-8')
        print("Received from client:", message_from_client)
        # 在这里处理接收到的数据，例如回复消息等
        if(message_from_client =="Prover"):
            message_to_client = "Hello, Prover! 请提供你年龄大于18岁的证明"
            ssl_conn.send(message_to_client.encode('utf-8'))  # 将字符串转换为字节串并发送消息
            received_data = ssl_conn.recv(1024)
            validity_period,p,sig = received_data.decode('utf-8').split('||')

            current_datetime = datetime.datetime.now()
            current_year = current_datetime.year
            limit = current_year-18
            d1=int(validity_period)-limit
            c_1=p
            for i in range(d1):
                c_1=sha256_hash(c_1)
            Sig_message = validity_period+c_1
            print(Sig_message)
            bytes_sig = ast.literal_eval(sig)
            verify_result = verify_signature('E:\创新创业Project\Project6 Range Proof With Hash Function\Trusted_Issuer\Trusted_public_key.pem', Sig_message ,  bytes_sig)
            if verify_result:
                message_to_client = "Signature Verification Passed!"
                ssl_conn.send(message_to_client.encode('utf-8'))  # 将字符串转换为字节串并发送消息
            else:
                message_to_client = "Signature Verification Failed!"
                ssl_conn.send(message_to_client.encode('utf-8'))  # 将字符串转换为字节串并发送消息


    except Exception as e:
        print("Error handling client:", e)

    finally:
        # 关闭连接
        ssl_conn.close()
        conn.close()

context = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
context.load_cert_chain(certfile='Bob.crt', keyfile='Bob.key')

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('localhost', 20000))
server_socket.listen(5)  # 设置监听队列的长度

print("Waiting for connections...")

while True:
    conn, addr = server_socket.accept()
    ssl_conn = context.wrap_socket(conn, server_side=True)

    print("Connected to:", addr)

    # 创建线程来处理客户端连接
    client_thread = threading.Thread(target=handle_client, args=(conn, ssl_conn))
    client_thread.start()
