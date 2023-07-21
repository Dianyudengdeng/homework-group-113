import hashlib
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import padding,utils
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.backends import default_backend

def generate_signature(data, private_key_file):
    # 读取密钥文件
    with open(private_key_file, "rb") as key_file:
        private_key = serialization.load_pem_private_key(key_file.read(), password=None, backend=default_backend())

    # 将字符串编码为字节串
    data_bytes = data.encode('utf-8')

    # 使用SHA-256哈希算法生成摘要
    digest = hashes.Hash(hashes.SHA256())
    digest.update(data_bytes)
    hash_value = digest.finalize()

    # 使用私钥对摘要进行签名
    signature = private_key.sign(
        hash_value,
        padding.PSS(mgf=padding.MGF1(hashes.SHA256()), salt_length=padding.PSS.MAX_LENGTH),
        hashes.SHA256()
    )

    return signature

def verify_signature(cert_file, data, signature):
    # 读取公钥文件
    with open(cert_file, "rb") as cert:
        cert_data = cert.read()

    # 加载证书中的公钥
    public_key = serialization.load_pem_public_key(cert_data, backend=default_backend())

    # 将字符串编码为字节串
    data_bytes = data.encode('utf-8')

    # 使用SHA-256哈希算法生成摘要
    digest = hashes.Hash(hashes.SHA256())
    digest.update(data_bytes)
    hash_value = digest.finalize()

    try:
        # 使用公钥验证签名
        public_key.verify(
            signature,
            hash_value,
            padding.PSS(mgf=padding.MGF1(hashes.SHA256()), salt_length=padding.PSS.MAX_LENGTH),
            hashes.SHA256()
        )
        return True  # 签名验证成功
    except Exception as e:
        print("Signature verification failed:", e)
        return False  # 签名验证失败


def sha224_hash(data):
    sha224_obj = hashlib.sha224()
    sha224_obj.update(data.encode('utf-8'))  # 将字符串编码为字节串并更新哈希对象
    sha224_hash_value = sha224_obj.hexdigest()

    return sha224_hash_value

def sha256_hash(data):
    sha256_obj = hashlib.sha256()
    sha256_obj.update(data.encode('utf-8'))
    sha256_hash_value = sha256_obj.hexdigest()
    return sha256_hash_value