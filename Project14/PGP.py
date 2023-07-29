from utils import *
from gmssl import sm2, func
from gmssl.sm4 import CryptSM4, SM4_ENCRYPT, SM4_DECRYPT


def PGP_sender(data,s_sk,s_pk,r_pk):
    print("生成SM4临时会话密钥......")
    sm4Key_str = func.random_hex(16)
    sm4Key = bytes(sm4Key_str, encoding='utf-8')  # 字符串转bytes
    sm4_crypt = CryptSM4()  # 初始化CryptSM4
    sm4_crypt.set_key(sm4Key, mode=SM4_ENCRYPT)  # 初始化key到CryptSM4 这里传的是SM_DECRYPT
    print("Session key：", sm4Key)

    print("对称加密明文.....")
    data = data.encode("utf-8")  # 列表转字符串转bytes
    encryptData = sm4_crypt.crypt_ecb(data)  # 对数据(bytes)加密
    encryptData = base64.b64encode(encryptData)  # bytes 转base64
    encryptData = encryptData.decode("utf-8")  # 由于转为base64,还是bytes,json不支持,故转为str
    print("EncryptData:", encryptData)

    print("使用r_pk加密会话密钥......")
    sm2_crypt = sm2.CryptSM2(private_key=None, public_key=r_pk)  # 附公钥
    encryptKey = sm2_crypt.encrypt(sm4Key)  # 对sm4Key(bytes) 进行加密,返回bytes
    encryptKey = base64.b64encode(encryptKey)  # bytes 转base64
    print("EncryptKey", encryptKey)

    print("使用s_sk进行签名......")
    sm2_crypt_s = sm2.CryptSM2(private_key=s_sk, public_key=s_pk)  # 私钥签名, 公钥验证
    random_hex_str = func.random_hex(sm2_crypt.para_len)  # para_len为64, 生成64位随机字符串
    sign = sm2_crypt_s.sign(data, random_hex_str)  # 签名需要用私钥 , sign为字符串格式
    sign = base64.b64encode(bytes(sign, encoding='utf-8'))  # 字符串转base64
    sign = sign.decode("utf-8")  # bytes转字符串
    print("sign:", sign)

    print("\nsender send msg(encryptKey||encryptData||sign) to receiver......")
    cipher = {"encryptKey":encryptKey,"encryptData":encryptData,"sign":sign}
    print(cipher)
    return cipher


def PGP_receiver(cipher,r_sk,r_pk,s_pk):
    encryptKey = base64.b64decode(cipher["encryptKey"])
    encryptData = base64.b64decode(cipher["encryptData"])
    sign = base64.b64decode(cipher['sign'])

    print("使用r_sk获取会话密钥......")
    sm2_crypt_r = sm2.CryptSM2(private_key=r_sk, public_key=r_pk)
    sm4Key_r = sm2_crypt_r.decrypt(encryptKey)  # 解密, 返回bytes
    print("Session Key that receiver obtain:", sm4Key_r)

    # sm4解密得到data
    print("对称解密密文")
    sm4_crypt_r = CryptSM4()
    sm4_crypt_r.set_key(sm4Key_r, mode=SM4_DECRYPT)
    data_r = sm4_crypt_r.crypt_ecb(encryptData)
    data_r = data_r.decode('utf-8')
    print("data that receiver obtain:", data_r)

    # 公钥签名验证
    print("使用s_pk进行签验签......")
    sm2_crypt_sr = sm2.CryptSM2(private_key=None, public_key=s_pk)
    if sm2_crypt_sr.verify(sign, data_r.encode()):
        print("Vertification pass")
    else:
        print("Vertification failed")



if __name__ == "__main__":
    sender_private_key,sender_public_key = create_key_pair()
    receiver_private_key,receiver_public_key = create_key_pair()
    print("------------------------生成密钥对--------------------------")
    print("Generate sm2Key......")
    print("s_sk:",sender_private_key,"\ns_pk:",sender_public_key)
    print("r_sk:",receiver_private_key,"\nr_pk:",receiver_public_key)

    print("------------------------Sender加密--------------------------")
    cipher = PGP_sender("message",sender_private_key,sender_public_key,receiver_public_key)

    print("------------------------Receiver 解密--------------------------")
    PGP_receiver(cipher,receiver_private_key,receiver_public_key,sender_public_key)



