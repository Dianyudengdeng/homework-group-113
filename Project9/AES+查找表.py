import numpy as np
import random,time

LUT_2x = [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182, 184, 186, 188, 190, 192, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 246, 248, 250, 252, 254, 27, 25, 31, 29, 19, 17, 23, 21, 11, 9, 15, 13, 3, 1, 7, 5, 59, 57, 63, 61, 51, 49, 55, 53, 43, 41, 47, 45, 35, 33, 39, 37, 91, 89, 95, 93, 83, 81, 87, 85, 75, 73, 79, 77, 67, 65, 71, 69, 123, 121, 127, 125, 115, 113, 119, 117, 107, 105, 111, 109, 99, 97, 103, 101, 155, 153, 159, 157, 147, 145, 151, 149, 139, 137, 143, 141, 131, 129, 135, 133, 187, 185, 191, 189, 179, 177, 183, 181, 171, 169, 175, 173, 163, 161, 167, 165, 219, 217, 223, 221, 211, 209, 215, 213, 203, 201, 207, 205, 195, 193, 199, 197, 251, 249, 255, 253, 243, 241, 247, 245, 235, 233, 239, 237, 227, 225, 231, 229]
LUT_2xxx3x = np.array([[0, 0, 0, 0], [2, 1, 1, 3], [4, 2, 2, 6], [6, 3, 3, 5], [8, 4, 4, 12], [10, 5, 5, 15], [12, 6, 6, 10], [14, 7, 7, 9], [16, 8, 8, 24], [18, 9, 9, 27], [20, 10, 10, 30], [22, 11, 11, 29], [24, 12, 12, 20], [26, 13, 13, 23], [28, 14, 14, 18], [30, 15, 15, 17], [32, 16, 16, 48], [34, 17, 17, 51], [36, 18, 18, 54], [38, 19, 19, 53], [40, 20, 20, 60], [42, 21, 21, 63], [44, 22, 22, 58], [46, 23, 23, 57], [48, 24, 24, 40], [50, 25, 25, 43], [52, 26, 26, 46], [54, 27, 27, 45], [56, 28, 28, 36], [58, 29, 29, 39], [60, 30, 30, 34], [62, 31, 31, 33], [64, 32, 32, 96], [66, 33, 33, 99], [68, 34, 34, 102], [70, 35, 35, 101], [72, 36, 36, 108], [74, 37, 37, 111], [76, 38, 38, 106], [78, 39, 39, 105], [80, 40, 40, 120], [82, 41, 41, 123], [84, 42, 42, 126], [86, 43, 43, 125], [88, 44, 44, 116], [90, 45, 45, 119], [92, 46, 46, 114], [94, 47, 47, 113], [96, 48, 48, 80], [98, 49, 49, 83], [100, 50, 50, 86], [102, 51, 51, 85], [104, 52, 52, 92], [106, 53, 53, 95], [108, 54, 54, 90], [110, 55, 55, 89], [112, 56, 56, 72], [114, 57, 57, 75], [116, 58, 58, 78], [118, 59, 59, 77], [120, 60, 60, 68], [122, 61, 61, 71], [124, 62, 62, 66], [126, 63, 63, 65], [128, 64, 64, 192], [130, 65, 65, 195], [132, 66, 66, 198], [134, 67, 67, 197], [136, 68, 68, 204], [138, 69, 69, 207], [140, 70, 70, 202], [142, 71, 71, 201], [144, 72, 72, 216], [146, 73, 73, 219], [148, 74, 74, 222], [150, 75, 75, 221], [152, 76, 76, 212], [154, 77, 77, 215], [156, 78, 78, 210], [158, 79, 79, 209], [160, 80, 80, 240], [162, 81, 81, 243], [164, 82, 82, 246], [166, 83, 83, 245], [168, 84, 84, 252], [170, 85, 85, 255], [172, 86, 86, 250], [174, 87, 87, 249], [176, 88, 88, 232], [178, 89, 89, 235], [180, 90, 90, 238], [182, 91, 91, 237], [184, 92, 92, 228], [186, 93, 93, 231], [188, 94, 94, 226], [190, 95, 95, 225], [192, 96, 96, 160], [194, 97, 97, 163], [196, 98, 98, 166], [198, 99, 99, 165], [200, 100, 100, 172], [202, 101, 101, 175], [204, 102, 102, 170], [206, 103, 103, 169], [208, 104, 104, 184], [210, 105, 105, 187], [212, 106, 106, 190], [214, 107, 107, 189], [216, 108, 108, 180], [218, 109, 109, 183], [220, 110, 110, 178], [222, 111, 111, 177], [224, 112, 112, 144], [226, 113, 113, 147], [228, 114, 114, 150], [230, 115, 115, 149], [232, 116, 116, 156], [234, 117, 117, 159], [236, 118, 118, 154], [238, 119, 119, 153], [240, 120, 120, 136], [242, 121, 121, 139], [244, 122, 122, 142], [246, 123, 123, 141], [248, 124, 124, 132], [250, 125, 125, 135], [252, 126, 126, 130], [254, 127, 127, 129], [27, 128, 128, 155], [25, 129, 129, 152], [31, 130, 130, 157], [29, 131, 131, 158], [19, 132, 132, 151], [17, 133, 133, 148], [23, 134, 134, 145], [21, 135, 135, 146], [11, 136, 136, 131], [9, 137, 137, 128], [15, 138, 138, 133], [13, 139, 139, 134], [3, 140, 140, 143], [1, 141, 141, 140], [7, 142, 142, 137], [5, 143, 143, 138], [59, 144, 144, 171], [57, 145, 145, 168], [63, 146, 146, 173], [61, 147, 147, 174], [51, 148, 148, 167], [49, 149, 149, 164], [55, 150, 150, 161], [53, 151, 151, 162], [43, 152, 152, 179], [41, 153, 153, 176], [47, 154, 154, 181], [45, 155, 155, 182], [35, 156, 156, 191], [33, 157, 157, 188], [39, 158, 158, 185], [37, 159, 159, 186], [91, 160, 160, 251], [89, 161, 161, 248], [95, 162, 162, 253], [93, 163, 163, 254], [83, 164, 164, 247], [81, 165, 165, 244], [87, 166, 166, 241], [85, 167, 167, 242], [75, 168, 168, 227], [73, 169, 169, 224], [79, 170, 170, 229], [77, 171, 171, 230], [67, 172, 172, 239], [65, 173, 173, 236], [71, 174, 174, 233], [69, 175, 175, 234], [123, 176, 176, 203], [121, 177, 177, 200], [127, 178, 178, 205], [125, 179, 179, 206], [115, 180, 180, 199], [113, 181, 181, 196], [119, 182, 182, 193], [117, 183, 183, 194], [107, 184, 184, 211], [105, 185, 185, 208], [111, 186, 186, 213], [109, 187, 187, 214], [99, 188, 188, 223], [97, 189, 189, 220], [103, 190, 190, 217], [101, 191, 191, 218], [155, 192, 192, 91], [153, 193, 193, 88], [159, 194, 194, 93], [157, 195, 195, 94], [147, 196, 196, 87], [145, 197, 197, 84], [151, 198, 198, 81], [149, 199, 199, 82], [139, 200, 200, 67], [137, 201, 201, 64], [143, 202, 202, 69], [141, 203, 203, 70], [131, 204, 204, 79], [129, 205, 205, 76], [135, 206, 206, 73], [133, 207, 207, 74], [187, 208, 208, 107], [185, 209, 209, 104], [191, 210, 210, 109], [189, 211, 211, 110], [179, 212, 212, 103], [177, 213, 213, 100], [183, 214, 214, 97], [181, 215, 215, 98], [171, 216, 216, 115], [169, 217, 217, 112], [175, 218, 218, 117], [173, 219, 219, 118], [163, 220, 220, 127], [161, 221, 221, 124], [167, 222, 222, 121], [165, 223, 223, 122], [219, 224, 224, 59], [217, 225, 225, 56], [223, 226, 226, 61], [221, 227, 227, 62], [211, 228, 228, 55], [209, 229, 229, 52], [215, 230, 230, 49], [213, 231, 231, 50], [203, 232, 232, 35], [201, 233, 233, 32], [207, 234, 234, 37], [205, 235, 235, 38], [195, 236, 236, 47], [193, 237, 237, 44], [199, 238, 238, 41], [197, 239, 239, 42], [251, 240, 240, 11], [249, 241, 241, 8], [255, 242, 242, 13], [253, 243, 243, 14], [243, 244, 244, 7], [241, 245, 245, 4], [247, 246, 246, 1], [245, 247, 247, 2], [235, 248, 248, 19], [233, 249, 249, 16], [239, 250, 250, 21], [237, 251, 251, 22], [227, 252, 252, 31], [225, 253, 253, 28], [231, 254, 254, 25], [229, 255, 255, 26]])


S_Box = [
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
]


S_invBox = [
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
]
Rconj = [[0x00, 0x00, 0x00, 0x00],[0x01, 0x00, 0x00, 0x00], [0x02, 0x00, 0x00, 0x00], [0x04, 0x00, 0x00, 0x00],[0x08, 0x00, 0x00, 0x00], [0x10, 0x00, 0x00, 0x00],
     [0x20, 0x00, 0x00, 0x00], [0x40, 0x00, 0x00, 0x00], [0x80, 0x00, 0x00, 0x00],[0x1B, 0x00, 0x00, 0x00], [0x36, 0x00, 0x00, 0x00]]


def PMatrix(plaintext):#文本转文本矩阵
    PlainText_Matrix = np.zeros((4, 4), dtype=int)#初始化文本矩阵（ECB模式，所以矩阵各元素初始化为0）

    for x in range(len(plaintext)):#遍历将文本元素转换为ASCILL码并赋值给矩阵
        PlainText_Matrix[x%4][x//4] = ord(plaintext[x])
    return PlainText_Matrix

def RePMatrix(PlainText_Matrix):#文本矩阵转文本
    text = ''
    for j in range(4):
        for i in range(4):
            text += (chr(PlainText_Matrix[i][j]))
    return text

def KMatrix(keytext):#密钥转密钥矩阵
    Key_Matrix = np.zeros((4, 44),dtype=int)#初始化密钥矩阵

    for x in range(len(keytext)):#遍历将密钥元素转换为ASCILL码并赋值给矩阵
            Key_Matrix[x % 4][x // 4] = ord(keytext[x])
    return Key_Matrix

#字节代换
def SubBytes(value,box):
     return box[value]

#字节代换处理矩阵
def SubBytes_all(Matrix,box):
    for i in range(4):
        for j in range(4):
            Matrix[i][j] = SubBytes(Matrix[i][j],box)

#轮密钥加
def AddRoundKey(k,Matrix_text,Matrix_key):
    Medium_Matrix = np.zeros((4, 4), dtype=int)
    for i in range(4):
        for j in range(4):
            Medium_Matrix[i][j] = Matrix_text[i][j]^Matrix_key[i][4*k+j]
    return Medium_Matrix

#行移位
def ShiftRows(Matrix):
    MediumMatrix = np.zeros((4, 4), dtype=int)
    for i in range(4):
        for j in range(4):
            MediumMatrix[i][j]=Matrix[i][(i+j)%4]
    return  MediumMatrix

def ShiftReRows(Matrix):
    MediumMatrix = np.zeros((4, 4), dtype=int)
    for i in range(4):
        for j in range(4):
            MediumMatrix[i][j]=Matrix[i][(j-i+4)%4]
    return MediumMatrix

#有限域乘法
def GaloisMultiply(numL,numR):
    result =0
    while(numL):
        if numL&0x01:
            result^=numR
        numL = numL>>1
        if numR&0x80:
            numR = numR<<1
            numR ^=0x1B
        else:
            numR=numR<<1
    return result%256

#列混淆
def MixColumn(Matrix):
    MixArray=np.array([[0x02, 0x03, 0x01, 0x01],[0x01, 0x02, 0x03, 0x01],[0x01, 0x01, 0x02, 0x03],[0x03, 0x01, 0x01, 0x02]])
    MediumMatrix = np.zeros((4, 4), dtype=int)
    for i in range(4):
        for j in range(4):
            MediumMatrix[i][j] = GaloisMultiply(MixArray[i][0] , Matrix[0][j])^GaloisMultiply(MixArray[i][1] , Matrix[1][j]) ^ GaloisMultiply(MixArray[i][2] , Matrix[2][j]) ^ GaloisMultiply(MixArray[i][3] , Matrix[3][j])
    return MediumMatrix

def MixColumn_LUT_1(Matrix):
    MediumMatrix = np.zeros((4, 4), dtype=int)
    for i in range(4):#列
        MediumMatrix[0][i] = SubBytes(Matrix[0][i]^Matrix[1][i],LUT_2x)^Matrix[1][i]^Matrix[2][i]^Matrix[3][i]
        MediumMatrix[1][i] = SubBytes(Matrix[1][i]^Matrix[2][i],LUT_2x)^Matrix[0][i]^Matrix[2][i]^Matrix[3][i]
        MediumMatrix[2][i] = SubBytes(Matrix[2][i]^Matrix[3][i],LUT_2x)^Matrix[0][i]^Matrix[1][i]^Matrix[3][i]
        MediumMatrix[3][i] = SubBytes(Matrix[0][i]^Matrix[3][i],LUT_2x)^Matrix[0][i]^Matrix[1][i]^Matrix[2][i]
    return MediumMatrix

def MixColumn_LUT_2(Matrix):
    MediumMatrix = np.zeros((4, 4), dtype=int)
    for i in range(4):#列
        item0 = LUT_2xxx3x[Matrix[0,i]]
        item1 = LUT_2xxx3x[Matrix[1,i]]
        item2 = LUT_2xxx3x[Matrix[2,i]]
        item3 = LUT_2xxx3x[Matrix[3,i]]
        MediumMatrix[0][i] = item0[0]^item1[3]^item2[2]^item3[1]
        MediumMatrix[1][i] = item0[1]^item1[0]^item2[3]^item3[2]
        MediumMatrix[2][i] = item0[2]^item1[1]^item2[0]^item3[3]
        MediumMatrix[3][i] = item0[3]^item1[2]^item2[1]^item3[0]
    return MediumMatrix

def MixColumn_LUT_3(Matrix):
    MediumMatrix = np.zeros((4, 4), dtype=int)
    temp1 = np.zeros(4)
    temp2 = np.zeros(4)
    for i in range(4):#列
        item0 = LUT_2xxx3x[(Matrix[0][i])]
        item1 = LUT_2xxx3x[(Matrix[1][i])]
        item1 = np.concatenate((item1[3:],item1[:3]),axis=0)
        item2 = LUT_2xxx3x[(Matrix[2][i])]
        item2 = np.concatenate((item2[2:],item2[:2]),axis=0)
        item3 = LUT_2xxx3x[(Matrix[3][i])]
        item3 = np.concatenate((item3[1:],item3[:1]),axis=0)
        temp1 = item0 ^ item1
        temp2 = item2 ^ item3
        temp1 = temp1^temp2
        for j in range(4):
            MediumMatrix[j][i]=temp1[j]
    return MediumMatrix


#逆列混淆
def MixReColumn(Matrix):
    MixArray=np.array([[0x0E, 0x0B, 0x0D, 0x09],[0x09, 0x0E, 0x0B, 0x0D],[0x0D, 0x09, 0x0E, 0x0B],[0x0B, 0x0D, 0x09, 0x0E]])
    MediumMatrix = np.zeros((4, 4), dtype=int)
    for i in range(4):
        for j in range(4):
            MediumMatrix[i][j] = GaloisMultiply(MixArray[i][0] , Matrix[0][j])^GaloisMultiply(MixArray[i][1] , Matrix[1][j]) ^ GaloisMultiply(MixArray[i][2] , Matrix[2][j]) ^ GaloisMultiply(MixArray[i][3] , Matrix[3][j])
    return MediumMatrix

#密钥扩展

def T_Function(Matrix,i):
    vector = [0,0,0,0]
    vector[0],vector[1],vector[2],vector[3] = Matrix[1, i - 1],Matrix[2, i - 1],Matrix[3, i - 1],Matrix[0, i - 1]
    for j in range(4):
        vector[j] = SubBytes(vector[j],S_Box)
        vector[j] = vector[j] ^ Rconj[int(i/4)][j]
    return vector

def Key_Extension(key_Matrix):
    for i in range(4,44):
        if i % 4:
            key_Matrix[:,i] = key_Matrix[:,i-4]^key_Matrix[:,i-1]
        else:
            key_Matrix[:,i] = key_Matrix[:,i-4]^T_Function(key_Matrix,i)


#循环测试
def Circulate(k):
    PlainText_Matrix = np.zeros((4, 4), dtype=int)  # 初始化文本矩阵（ECB模式，所以矩阵各元素初始化为0）
    for c in range(k):
        for i in range(4):
            for j in range(4):
                PlainText_Matrix[i][j] = random.randint(0,255)
        for i in range(255):
            PlainText_Matrix[3][3] = i
            Cryptor_test(PlainText_Matrix,"202100460030")

#加密机测试版本
def Cryptor_test(PlainText_Matrix,keytext):
    Cipher_Matrix = PlainText_Matrix
    #print(PlainText_Matrix)
    Key_Matrix = KMatrix(keytext)#自动填充
    Key_Extension(Key_Matrix)#密钥扩展
    #加密
    Cipher_Matrix = AddRoundKey(0,Cipher_Matrix,Key_Matrix)
    for i in range(1,10):
        SubBytes_all(Cipher_Matrix,S_Box)
        Cipher_Matrix = ShiftRows(Cipher_Matrix)
        Cipher_Matrix = MixColumn_LUT_3(Cipher_Matrix)
        Cipher_Matrix = AddRoundKey(i, Cipher_Matrix, Key_Matrix)
    SubBytes_all(Cipher_Matrix, S_Box)
    Cipher_Matrix = ShiftRows(Cipher_Matrix)
    Cipher_Matrix = AddRoundKey(10, Cipher_Matrix, Key_Matrix)
    return Cipher_Matrix

#加密机
def Cryptor(plaintext,keytext):
    PlainText_Matrix = PMatrix(keytext)#自动填充
    Cipher_Matrix = PlainText_Matrix
    print(PlainText_Matrix)
    Key_Matrix = KMatrix(keytext)#自动填充
    Key_Extension(Key_Matrix)#密钥扩展
    print(Key_Matrix)
    #加密
    Cipher_Matrix = AddRoundKey(0,Cipher_Matrix,Key_Matrix)
    for i in range(1,10):
        SubBytes_all(Cipher_Matrix,S_Box)
        Cipher_Matrix = ShiftRows(Cipher_Matrix)
        Cipher_Matrix = MixColumn_LUT_3(Cipher_Matrix)
        Cipher_Matrix = AddRoundKey(i, Cipher_Matrix, Key_Matrix)
    SubBytes_all(Cipher_Matrix, S_Box)
    Cipher_Matrix = ShiftRows(Cipher_Matrix)
    Cipher_Matrix = AddRoundKey(10, Cipher_Matrix, Key_Matrix)
    print(Cipher_Matrix)
    return Cipher_Matrix


#解密机
def Decryptor(Cipher_Matrix,keytext):
    PlainText_Matrix = Cipher_Matrix
    Key_Matrix = KMatrix(keytext)  # 自动填充
    Key_Extension(Key_Matrix)  # 密钥扩展
    # 加密
    PlainText_Matrix = AddRoundKey(10, PlainText_Matrix, Key_Matrix)
    PlainText_Matrix = ShiftReRows(PlainText_Matrix)
    SubBytes_all(PlainText_Matrix, S_invBox)
    for i in range(1, 10):
        PlainText_Matrix = AddRoundKey(10 - i, PlainText_Matrix, Key_Matrix)
        PlainText_Matrix = MixReColumn(PlainText_Matrix)
        PlainText_Matrix = ShiftReRows(PlainText_Matrix)
        SubBytes_all(PlainText_Matrix, S_invBox)
    PlainText_Matrix = AddRoundKey(0, PlainText_Matrix, Key_Matrix)
    print(PlainText_Matrix)
    PlainText =RePMatrix(PlainText_Matrix)
    return PlainText

def Initialize_LUT_1():#2x的查找表
    LUT = []
    for x in range(256):
        LUT.append(GaloisMultiply(2,x))
    print(LUT)

def Initialize_LUT_2():#(2x, x, x, 3x)的查找表
    LUT = []
    item = []
    for x in range(256):
        item = [GaloisMultiply(2,x),x,x,GaloisMultiply(3,x)]
        LUT.append(item)
    print(LUT)

if __name__ == "__main__":
    ''' plaintext = "202100460030"
    keytext = "202100460030"
    PlainText_Matrix=PMatrix(plaintext)
    print(PlainText_Matrix)
    Key_Matrix = KMatrix(keytext)
    Key_Extension(Key_Matrix)
    print(Key_Matrix)
    Cipher_Matrix = Cryptor(plaintext,keytext)
    print(Decryptor(Cipher_Matrix,keytext))
    '''
    start = time.time()
    Circulate(100)
    end = time.time()
    print(f"CPU 占用的总时间:{end - start}s")
    print("程序退出...")


