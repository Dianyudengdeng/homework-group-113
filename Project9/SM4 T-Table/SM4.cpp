#include "SM4.h"
unsigned char Sbox[256] = {
    0xd6,0x90,0xe9,0xfe,0xcc,0xe1,0x3d,0xb7,0x16,0xb6,0x14,0xc2,0x28,0xfb,0x2c,0x05,
    0x2b,0x67,0x9a,0x76,0x2a,0xbe,0x04,0xc3,0xaa,0x44,0x13,0x26,0x49,0x86,0x06,0x99,
    0x9c,0x42,0x50,0xf4,0x91,0xef,0x98,0x7a,0x33,0x54,0x0b,0x43,0xed,0xcf,0xac,0x62,
    0xe4,0xb3,0x1c,0xa9,0xc9,0x08,0xe8,0x95,0x80,0xdf,0x94,0xfa,0x75,0x8f,0x3f,0xa6,
    0x47,0x07,0xa7,0xfc,0xf3,0x73,0x17,0xba,0x83,0x59,0x3c,0x19,0xe6,0x85,0x4f,0xa8,
    0x68,0x6b,0x81,0xb2,0x71,0x64,0xda,0x8b,0xf8,0xeb,0x0f,0x4b,0x70,0x56,0x9d,0x35,
    0x1e,0x24,0x0e,0x5e,0x63,0x58,0xd1,0xa2,0x25,0x22,0x7c,0x3b,0x01,0x21,0x78,0x87,
    0xd4,0x00,0x46,0x57,0x9f,0xd3,0x27,0x52,0x4c,0x36,0x02,0xe7,0xa0,0xc4,0xc8,0x9e,
    0xea,0xbf,0x8a,0xd2,0x40,0xc7,0x38,0xb5,0xa3,0xf7,0xf2,0xce,0xf9,0x61,0x15,0xa1,
    0xe0,0xae,0x5d,0xa4,0x9b,0x34,0x1a,0x55,0xad,0x93,0x32,0x30,0xf5,0x8c,0xb1,0xe3,
    0x1d,0xf6,0xe2,0x2e,0x82,0x66,0xca,0x60,0xc0,0x29,0x23,0xab,0x0d,0x53,0x4e,0x6f,
    0xd5,0xdb,0x37,0x45,0xde,0xfd,0x8e,0x2f,0x03,0xff,0x6a,0x72,0x6d,0x6c,0x5b,0x51,
    0x8d,0x1b,0xaf,0x92,0xbb,0xdd,0xbc,0x7f,0x11,0xd9,0x5c,0x41,0x1f,0x10,0x5a,0xd8,
    0x0a,0xc1,0x31,0x88,0xa5,0xcd,0x7b,0xbd,0x2d,0x74,0xd0,0x12,0xb8,0xe5,0xb4,0xb0,
    0x89,0x69,0x97,0x4a,0x0c,0x96,0x77,0x7e,0x65,0xb9,0xf1,0x09,0xc5,0x6e,0xc6,0x84,
    0x18,0xf0,0x7d,0xec,0x3a,0xdc,0x4d,0x20,0x79,0xee,0x5f,0x3e,0xd7,0xcb,0x39,0x48
};

unsigned int T_Table_1[256] = { 2396347227, 3499246146, 1307223975, 117308411, 4241437491, 1709344647, 3376280820, 1807081182, 1310087256, 1857346266, 1142181968, 3401648907, 2284363936, 402190319, 2620174512, 285545492, 2267786412, 4217806237, 4070074986, 2927090137, 2183833768, 1186790138, 335810576, 3485470479, 44608170, 1413812497, 1595100236, 3190200472, 1833444645, 2659457562, 503715864, 4254819942, 3969806962, 1245907209, 273760577, 620221395, 3583198790, 1408024511, 4170867298, 2457594345, 4281584844, 72700241, 655043628, 1329728781, 1508816823, 4090249023, 481211058, 3932391817, 1961333651, 2142359246, 1813803120, 229353126, 3989448487, 671621152, 1223402403, 3247920726, 2156003842, 2749136767, 3298185810, 318368747, 2708788693, 3012378174, 3275750652, 1050974874, 1531321629, 453450780, 1000709790, 218100723, 1072746447, 3211972045, 1259822172, 1387850474, 2407599630, 1029203301, 3426545904, 2098816100, 2128976795, 2441549334, 1934507325, 145400482, 3362365857, 3345657261, 2239956486, 2058406602, 3044066757, 4100297105, 3000593259, 2810785326, 419161059, 1206431663, 856636476, 1732914477, 2960245185, 240605529, 3919541878, 3778401492, 1713272952, 3022295184, 906901560, 643791225, 4016213389, 945381729, 2513585991, 715164298, 2972030100, 2854389896, 2357064177, 3611028716, 83952644, 2770437252, 2558124513, 2609192478, 2228704083, 0, 1581717785, 190209373, 3818749566, 2681229135, 3139935388, 441665865, 2085433649, 3996571864, 167905288, 2078580639, 547521154, 3569816339, 3905626915, 3869014650, 1122610091, 1136525054, 2726832682, 2597407563, 1078001921, 3687063327, 3627606240, 1639438038, 799116942, 737468383, 988924875, 4140645179, 502982631, 3848308101, 1091916884, 631473798, 1625523075, 380418746, 693925237, 883331730, 4154027630, 3828666576, 1914333288, 22304085, 430945974, 3750841934, 4197632200, 4029726912, 569825239, 3163435570, 1974716102, 1876987791, 1763538036, 787864539, 1793166219, 2519644344, 2323646986, 4268202393, 3804834603, 3764486529, 3234005763, 2368316580, 2938342540, 128560814, 957166644, 525487437, 1984903481, 3547250109, 2178307927, 3084414831, 3946306780, 1363416341, 2799532923, 167704567, 3062643258, 2469379260, 251857932, 66912255, 3261835689, 3128150473, 3647780277, 3698176433, 928673133, 357582149, 3113170486, 1998285932, 330153662, 3666889290, 1471803118, 2849929079, 1287582450, 2206137853, 1427194948, 3185207143, 744321393, 1161823493, 1663007868, 1343242304, 844851561, 3101385571, 571090984, 3317827335, 4113679556, 2827624994, 833066646, 4191041335, 2541415917, 1237317366, 2569909428, 2759184849, 2429764419, 1511147592, 1488642786, 1910937495, 1689703122, 1890763458, 2911577638, 3446187429, 3415563870, 1649092905, 1007431728, 3465828954, 2876693981, 2256534009, 4049900949, 1572595430, 905103303, 755573796, 3519420183, 3597646265, 3737459483, 2491814418, 2014863456, 821281731, 2306668021, 1559212979, 3527076072, 2900325235, 2035037493, 2686484608, 2641946085, 1458420667, 593395069, 3326015736, 2345951071, 3888656175, 3711558884, 1749623073 };
unsigned int T_Table_2[256] = { 1536087387, 1120965186, 2806901415, 4211539451, 872206131, 2271601287, 4106829300, 3731600862, 1481512536, 3664688346, 1346638928, 197837067, 2693277856, 4011325679, 2963025072, 336659732, 2894539692, 2650498717, 1794283626, 3652089817, 2827102888, 4198939898, 269747216, 265273359, 2852300970, 290735377, 1281299276, 2562598552, 627918885, 446596122, 404620824, 1727896422, 1928109682, 155861769, 1091588417, 3542415315, 1188401990, 3209948351, 1660459618, 3918691305, 3439277004, 1359238481, 740756268, 223298061, 3076124343, 1072942143, 2988224178, 2313839497, 2473912211, 3464475086, 1886133360, 2785913766, 669895207, 539494432, 2739465123, 1455527766, 41976322, 2141445247, 1388615250, 3943889387, 3584128213, 1051954494, 4240654332, 2587796634, 492520989, 471533340, 2654709150, 4077715443, 3477074127, 3451876045, 1548425052, 3931289834, 244285710, 1698519141, 4039916784, 1685920100, 2608784795, 378636054, 1030966845, 2718476962, 2714266017, 2915527341, 109413126, 3397038282, 3317002437, 2448713105, 1806883179, 782731566, 3810065379, 2940725423, 1009979196, 761743917, 3249566145, 1494112089, 1995022198, 3571529172, 2019958392, 2427724944, 943066680, 2032557945, 2381275789, 1631082849, 1201001031, 2318049418, 2494637460, 2292851336, 4052516337, 3973528556, 67436804, 2225414532, 3784866273, 513508638, 1401214803, 0, 425608985, 1561024093, 2128846206, 1335873615, 2629511068, 1226462025, 830229809, 3639490264, 134873608, 2675696799, 2183176834, 332711699, 602458915, 2061933690, 2873289131, 4265852414, 715294762, 1268437323, 20988161, 534496287, 3772266720, 3596728278, 2385486222, 3744199903, 3409637835, 1006030139, 3877501671, 2246402181, 1413551444, 2250613638, 2204164995, 3122048186, 1965644917, 2452924050, 1861720430, 3504616656, 1752308328, 1426150485, 3055136694, 1323274574, 3371840200, 3236966592, 3609327319, 851217970, 3329602502, 2406473871, 1953045876, 3677287899, 2339037579, 3096850104, 176848906, 2583586713, 736282923, 2178965889, 62964483, 2760714660, 2360288140, 2919737774, 876154164, 1293898317, 964054841, 3184750269, 1468126807, 1874319471, 3706402780, 357647381, 2074533243, 4144627447, 985041978, 3163762620, 202310412, 4278451455, 2848091049, 3384439753, 3050925237, 2984013233, 1832344173, 1159024709, 918130486, 1819745132, 3188960702, 1255837770, 3998726638, 2007621239, 4065115890, 4253253373, 1146425668, 1740495463, 1898732913, 88424453, 2086870908, 1078988864, 1764907881, 1673059171, 673319464, 130400775, 3304403396, 581470754, 2519836566, 939118135, 3986127597, 4132028406, 3029937588, 3517216209, 1133564739, 1213862472, 3797465826, 2540824215, 3529815762, 3262165698, 648907558, 2781702309, 1590400350, 694307625, 809241648, 1523487834, 3719001821, 4186341369, 2515625109, 3864902630, 3342201543, 606931236, 399623703, 3117838265, 467584283, 311723538, 1618483296, 3274765251, 4119428341, 3009212339, 3906091752, 1940709235, 897141813, 2157977728, 3852302565, 3143036347, 2099469949, 4173741816, 1602999391, 803719215, 3839703524, 560482593 };
unsigned int T_Table_3[256] = { 1532726997, 1111675026, 2812759530, 4227532541, 859045071, 2273797602, 4109683005, 3739118517, 1482182166, 3671748276, 1347437588, 185322177, 2694875176, 4025423864, 2964364332, 336859397, 2896987947, 2644376422, 1785393816, 3654921847, 2829615658, 4210706108, 269489156, 252694464, 2863268520, 286348357, 1280073491, 2560146982, 623209800, 437952132, 404233734, 1718025627, 1920134302, 151603779, 1094783057, 3553830135, 1179047315, 3216987116, 1650653338, 3924398715, 3435986739, 1364264021, 741091083, 218976066, 3082246638, 1061155788, 2998017198, 2307517027, 2475914471, 3469639601, 1886415900, 2795900331, 656928202, 538978312, 2745387243, 1448526231, 33718402, 2139071452, 1381155990, 3958051577, 3587547508, 1044296589, 4244423487, 2593799844, 488463174, 471603975, 2661170085, 4092792063, 3486466032, 3452813170, 1549552407, 3941225144, 235835265, 1701133656, 4042312764, 1684307225, 2610659045, 370577799, 1027437390, 2728528042, 2711734377, 2913847146, 101090691, 3402267312, 3318068592, 2442261605, 1802220249, 774809481, 3823311099, 2947500008, 1010578191, 757950282, 3250696305, 1499008599, 1987504543, 3570721077, 2021156382, 2425402404, 943207950, 2037982815, 2374889314, 1633761369, 1195873746, 2324310688, 2492772645, 2290657826, 4059139197, 3974944571, 67372289, 2223285537, 3789658233, 505322373, 1397982423, 0, 421092935, 1566378838, 2122245021, 1330618320, 2627517223, 1229527635, 825326669, 3638095414, 134744578, 2678029284, 2189566114, 320066759, 589555915, 2054874780, 2880127721, 4278076349, 707437192, 1263246033, 16859201, 522181572, 3772831800, 3604373943, 2391682977, 3755944948, 3419093745, 993785549, 3890683386, 2240144736, 1414807829, 2256938403, 2206425315, 3132757676, 1970612572, 2459055270, 1852766105, 3503350836, 1751675418, 1431634260, 3065387439, 1313791889, 3368614450, 3233869872, 3621200374, 842185870, 3334895027, 2408542176, 1953786141, 3688574709, 2341169889, 3099104814, 168462976, 2577006183, 724296393, 2172772449, 50577603, 2762247465, 2358030115, 2930640809, 875837709, 1296899922, 960067151, 3183334254, 1465352662, 1869592536, 3705465655, 353718596, 2071701213, 4160162302, 976926348, 3166475055, 202116867, 4294902780, 2846474859, 3385440883, 3048593772, 2981223533, 1835874138, 1162155344, 909556111, 1819047707, 3200127917, 1246419600, 4008597433, 2004330974, 4075965630, 4261249918, 1145328913, 1734852058, 1903242333, 84231488, 2088526623, 1077956624, 1768501851, 1667479771, 673718794, 117949890, 3301242161, 572696714, 2526425511, 926415310, 3991771002, 4143335871, 3031734573, 3520177269, 1128501459, 1212701202, 3806484666, 2543284710, 3537003702, 3267522738, 640069003, 2779106664, 1583270805, 690577995, 808467468, 1515900564, 3722292086, 4193879679, 2509631844, 3873856955, 3351721458, 606350601, 387436998, 3115964015, 454811333, 303207558, 1616934936, 3284349171, 4126509436, 3014876399, 3907572282, 1936960735, 892696908, 2155913248, 3857030520, 3149616877, 2105353054, 4177053246, 1600097236, 791668680, 3840204089, 555837513 };
unsigned int T_Table_4[256] = { 3579534222, 2453816016, 3936855885, 4261149446, 3476239356, 3800532837, 1039463625, 3051282027, 374888526, 3034241646, 340807748, 3238726602, 681615496, 4176473879, 749777052, 85201937, 732736647, 1721605627, 2557111026, 2010765742, 715696258, 3170564678, 68161556, 3222212559, 2829756930, 1158746452, 323767391, 647534782, 1210393965, 2216303262, 102242334, 2607179517, 2658300652, 1124665674, 1363230992, 4157854500, 2470856405, 3971989331, 2590139128, 2078927250, 869059839, 1431392516, 187444263, 1108151631, 4005017433, 3426697203, 2930946588, 1669958122, 3885208436, 2983120511, 477130860, 2879825421, 3391563757, 136323112, 3953369928, 2539017921, 2181169792, 3699343267, 2521977540, 4192987922, 1960170913, 2369666739, 1073544387, 2761595454, 1176313179, 119282715, 2778635835, 4294177548, 4040150847, 1926090175, 391928907, 3102403154, 2165182095, 1483040061, 1022423244, 426009725, 3852180350, 2266371729, 1312636275, 2862785032, 1772200392, 1789767111, 2198210181, 2966080122, 1892009397, 1704038900, 3647695794, 2301505191, 4226016024, 3903827783, 255605811, 1244474727, 1908523440, 1465473294, 2675341033, 903140577, 511211622, 613454004, 238565430, 1601796390, 1653444079, 1499554104, 3527886741, 2693433898, 630494385, 579373226, 2113008012, 1005382871, 17040389, 562332837, 2044846488, 2233343643, 3612562308, 0, 1192827230, 1448959243, 2642312931, 3494858655, 664575163, 1397311770, 1295069564, 920180974, 34080778, 3835666299, 2726461984, 3339916244, 3408077800, 2625272550, 3920341826, 3187605059, 2284464802, 3511372698, 1090584896, 3290374107, 954261720, 3084310113, 2710474287, 4108312363, 4056664890, 3443211254, 4209501981, 1619363301, 357848129, 2743502373, 3817046880, 2897918486, 1551201577, 2794623540, 2574151415, 886100196, 443050098, 1414878465, 2947986969, 2437828319, 852019450, 817938672, 4141340449, 2385654460, 3016148597, 3767504751, 494171241, 4124826414, 3784018794, 783857814, 2148141706, 1738119678, 3375049698, 1635877344, 3271754688, 698655885, 596413615, 2846797319, 221525049, 1380797727, 1329150326, 1857928659, 3596048257, 3631181751, 937221355, 1142232401, 3715857318, 4277663497, 2352626358, 800898195, 51121167, 4244635395, 1806281154, 1942604218, 1823847897, 1840361948, 1517120823, 1346716949, 2402694841, 460090487, 2914958867, 2420787930, 3119443543, 3732371369, 3203592780, 2130574723, 289686613, 3664209853, 1567715628, 1074070853, 528252003, 272646224, 1533634866, 3680723896, 170403874, 3255240645, 834979061, 2317492904, 2811663921, 3459725305, 2062413207, 3220633161, 766817433, 1976684964, 3544400784, 306727002, 3135431256, 3868694385, 3067269732, 2999108208, 2334533293, 1755686349, 2505989835, 1260988770, 204484668, 2488949454, 1994251691, 2147088774, 1687524849, 3152471645, 4073178933, 153363501, 3323402193, 1874442710, 3306888158, 2249331348, 408969336, 4089692976, 2096493961, 4021531484, 988342482, 3748885420, 1278555513, 545292448, 2028332445, 3988503382, 1585282339, 1056504006, 3563020171, 3358535655, 971302109, 1226908008 };

unsigned int MK[4];
unsigned int FK[4] = { 0xA3B1BAC6, 0x56AA3350, 0x677D9197, 0xB27022DC };
unsigned int CK[32] = {
    0x00070e15, 0x1c232a31, 0x383f464d, 0x545b6269, 0x70777e85, 0x8c939aa1, 0xa8afb6bd, 0xc4cbd2d9,
    0xe0e7eef5, 0xfc030a11, 0x181f262d, 0x343b4249, 0x50575e65, 0x6c737a81, 0x888f969d, 0xa4abb2b9,
    0xc0c7ced5, 0xdce3eaf1, 0xf8ff060d, 0x141b2229, 0x30373e45, 0x4c535a61, 0x686f767d, 0x848b9299,
    0xa0a7aeb5, 0xbcc3cad1, 0xd8dfe6ed, 0xf4fb0209, 0x10171e25, 0x2c333a41, 0x484f565d, 0x646b7279 };
unsigned int RK[32];

#define rotl32(value, shift) ((value << shift) | value >> (32 - shift))
unsigned int L(unsigned int x)
{
    return x ^ rotl32(x, 2) ^ rotl32(x, 10) ^ rotl32(x, 18) ^ rotl32(x, 24);
}

unsigned int L_1(unsigned int x)
{
    return x ^ rotl32(x, 13) ^ rotl32(x, 23);
}

unsigned int tao(unsigned int x)
{
    return Sbox[x & 0xFF] | (Sbox[(x >> 8) & 0xFF] << 8) | (Sbox[(x >> 16) & 0xFF] << 16) | (Sbox[(x >> 24) & 0xFF] << 24);
}

unsigned int T(unsigned int x)
{
    return T_Table_4[x & 0xFF] ^ T_Table_3[(x >> 8) & 0xFF] ^ T_Table_2[(x >> 16) & 0xFF] ^ T_Table_1[(x >> 24) & 0xFF];
}

unsigned int T_p(unsigned int x)
{
    return L_1(tao(x));
}



void Key_Extension()
{
    unsigned int K[36];
    int i = 0;
    for (i = 0; i < 4; i++)
        K[i] = MK[i] ^ FK[i];
    for (i = 0; i < 32; i++)
    {
        K[i + 4] = K[i] ^ (T_p(K[i + 1] ^ K[i + 2] ^ K[i + 3] ^ CK[i]));
        RK[i] = K[i + 4];
    }
}

void setKey(unsigned char* key)
{
    for (int j = 0; j < 4; j++)
        MK[j] = key[j * 4] << 24 | key[j * 4 + 1] << 16 | key[j * 4 + 2] << 8 | key[j * 4 + 3];
    Key_Extension();
}

void encrypt(unsigned char plain[16], unsigned char cipher[16])
{
    unsigned int X[4];
    int j = 0;
    unsigned int temp_x;

    X[0] = plain[0] << 24 | plain[1] << 16 | plain[2] << 8 | plain[3];
    X[1] = plain[4] << 24 | plain[5] << 16 | plain[6] << 8 | plain[7];
    X[2] = plain[8] << 24 | plain[9] << 16 | plain[10] << 8 | plain[11];
    X[3] = plain[12] << 24 | plain[13] << 16 | plain[14] << 8 | plain[15];

    for (j = 0; j < 32; j++) {
        temp_x = X[0] ^ T(X[1] ^ X[2] ^ X[3] ^ RK[j]);
        X[0] = X[1];
        X[1] = X[2];
        X[2] = X[3];
        X[3] = temp_x;
    }
    for (int i = 0; i < 4; i++) {
        cipher[4 * i] = (X[3 - i] >> 24) & 0xff;
        cipher[4 * i + 1] = (X[3 - i] >> 16) & 0xff;
        cipher[4 * i + 2] = (X[3 - i] >> 8) & 0xff;
        cipher[4 * i + 3] = (X[3 - i]) & 0xff;
    }
}



void encrypt(unsigned int plain[4], unsigned int cipher[4])
{
    unsigned int X[4];
    int j = 0;
    unsigned int temp_x;

    for (j = 0; j < 4; j++) {
        X[j] = plain[j];
    }

    for (j = 0; j < 32; j++) {
        temp_x = X[0] ^ T(X[1] ^ X[2] ^ X[3] ^ RK[j]);
        X[0] = X[1];
        X[1] = X[2];
        X[2] = X[3];
        X[3] = temp_x;
    }
    cipher[0] = X[3];
    cipher[1] = X[2];
    cipher[2] = X[1];
    cipher[3] = X[0];

}

void encfile(unsigned int* data_in, unsigned int* data_out)
{
    int i = 0;
    for (i = 0; i < 175812; i += 4) {
        encrypt(data_in + i, data_out + i);
    }
}

void decrypt(unsigned char cipher[16], unsigned char plain[16])
{
    unsigned int X[4];
    int j = 0;
    unsigned int temp_x;

    X[0] = cipher[0] << 24 | cipher[1] << 16 | cipher[2] << 8 | cipher[3];
    X[1] = cipher[4] << 24 | cipher[5] << 16 | cipher[6] << 8 | cipher[7];
    X[2] = cipher[8] << 24 | cipher[9] << 16 | cipher[10] << 8 | cipher[11];
    X[3] = cipher[12] << 24 | cipher[13] << 16 | cipher[14] << 8 | cipher[15];

    for (j = 0; j < 32; j++) {
        temp_x = X[0] ^ T(X[1] ^ X[2] ^ X[3] ^ RK[(31 - j)]);
        X[0] = X[1];
        X[1] = X[2];
        X[2] = X[3];
        X[3] = temp_x;
    }
    for (int i = 0; i < 4; i++) {
        plain[4 * i] = (X[3 - i] >> 24) & 0xff;
        plain[4 * i + 1] = (X[3 - i] >> 16) & 0xff;
        plain[4 * i + 2] = (X[3 - i] >> 8) & 0xff;
        plain[4 * i + 3] = (X[3 - i]) & 0xff;
    }
}


void decrypt(unsigned int cipher[4], unsigned int plain[4])
{
    unsigned int X[4];
    int j = 0;
    unsigned int temp_x;

    for (j = 0; j < 4; j++) {
        X[j] = cipher[j];
    }

    for (j = 0; j < 32; j++) {
        temp_x = X[0] ^ T(X[1] ^ X[2] ^ X[3] ^ RK[(31 - j)]);
        X[0] = X[1];
        X[1] = X[2];
        X[2] = X[3];
        X[3] = temp_x;
    }
    plain[0] = X[3];
    plain[1] = X[2];
    plain[2] = X[1];
    plain[3] = X[0];
}
