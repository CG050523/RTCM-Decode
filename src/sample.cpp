#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <bitset>
#include <iomanip>
#include <vector>

using namespace std;

// 分别对应基准站1005,1006,卫星类型GPS,GLONASS,GALILEO,QZSS,BDS
int Type[7] = {
    1005, 1006, 107, 108, 109, 111, 112};

vector<string> fileIn(string loc)
{
    vector<string> rtcm;
    stringstream tmp_line;
    string word;
    string line;
    ifstream fin(loc);
    if (fin.is_open())
    {
        while (getline(fin, line, '\n'))
        {
            tmp_line.str(line);
            while (tmp_line >> word)
                rtcm.push_back(word);
            tmp_line.clear();
        }
    }
    else
    {
        cerr << "no file\n";
    }
    return rtcm;
}

int table[] =
    {
        0x000000, 0x864CFB, 0x8AD50D, 0x0C99F6, 0x93E6E1, 0x15AA1A, 0x1933EC, 0x9F7F17,
        0xA18139, 0x27CDC2, 0x2B5434, 0xAD18CF, 0x3267D8, 0xB42B23, 0xB8B2D5, 0x3EFE2E, 0xC54E89, 0x430272,
        0x4F9B84, 0xC9D77F, 0x56A868, 0xD0E493, 0xDC7D65, 0x5A319E, 0x64CFB0, 0xE2834B, 0xEE1ABD, 0x685646,
        0xF72951, 0x7165AA, 0x7DFC5C, 0xFBB0A7, 0x0CD1E9, 0x8A9D12, 0x8604E4, 0x00481F, 0x9F3708, 0x197BF3,
        0x15E205, 0x93AEFE, 0xAD50D0, 0x2B1C2B, 0x2785DD, 0xA1C926, 0x3EB631, 0xB8FACA, 0xB4633C, 0x322FC7,
        0xC99F60, 0x4FD39B, 0x434A6D, 0xC50696, 0x5A7981, 0xDC357A, 0xD0AC8C, 0x56E077, 0x681E59, 0xEE52A2,
        0xE2CB54, 0x6487AF, 0xFBF8B8, 0x7DB443, 0x712DB5, 0xF7614E, 0x19A3D2, 0x9FEF29, 0x9376DF, 0x153A24,
        0x8A4533, 0x0C09C8, 0x00903E, 0x86DCC5, 0xB822EB, 0x3E6E10, 0x32F7E6, 0xB4BB1D, 0x2BC40A, 0xAD88F1,
        0xA11107, 0x275DFC, 0xDCED5B, 0x5AA1A0, 0x563856, 0xD074AD, 0x4F0BBA, 0xC94741, 0xC5DEB7, 0x43924C,
        0x7D6C62, 0xFB2099, 0xF7B96F, 0x71F594, 0xEE8A83, 0x68C678, 0x645F8E, 0xE21375, 0x15723B, 0x933EC0,
        0x9FA736, 0x19EBCD, 0x8694DA, 0x00D821, 0x0C41D7, 0x8A0D2C, 0xB4F302, 0x32BFF9, 0x3E260F, 0xB86AF4,
        0x2715E3, 0xA15918, 0xADC0EE, 0x2B8C15, 0xD03CB2, 0x567049, 0x5AE9BF, 0xDCA544, 0x43DA53, 0xC596A8,
        0xC90F5E, 0x4F43A5, 0x71BD8B, 0xF7F170, 0xFB6886, 0x7D247D, 0xE25B6A, 0x641791, 0x688E67, 0xEEC29C,
        0x3347A4, 0xB50B5F, 0xB992A9, 0x3FDE52, 0xA0A145, 0x26EDBE, 0x2A7448, 0xAC38B3, 0x92C69D, 0x148A66,
        0x181390, 0x9E5F6B, 0x01207C, 0x876C87, 0x8BF571, 0x0DB98A, 0xF6092D, 0x7045D6, 0x7CDC20, 0xFA90DB,
        0x65EFCC, 0xE3A337, 0xEF3AC1, 0x69763A, 0x578814, 0xD1C4EF, 0xDD5D19, 0x5B11E2, 0xC46EF5, 0x42220E,
        0x4EBBF8, 0xC8F703, 0x3F964D, 0xB9DAB6, 0xB54340, 0x330FBB, 0xAC70AC, 0x2A3C57, 0x26A5A1, 0xA0E95A,
        0x9E1774, 0x185B8F, 0x14C279, 0x928E82, 0x0DF195, 0x8BBD6E, 0x872498, 0x016863, 0xFAD8C4, 0x7C943F,
        0x700DC9, 0xF64132, 0x693E25, 0xEF72DE, 0xE3EB28, 0x65A7D3, 0x5B59FD, 0xDD1506, 0xD18CF0, 0x57C00B,
        0xC8BF1C, 0x4EF3E7, 0x426A11, 0xC426EA, 0x2AE476, 0xACA88D, 0xA0317B, 0x267D80, 0xB90297, 0x3F4E6C,
        0x33D79A, 0xB59B61, 0x8B654F, 0x0D29B4, 0x01B042, 0x87FCB9, 0x1883AE, 0x9ECF55, 0x9256A3, 0x141A58,
        0xEFAAFF, 0x69E604, 0x657FF2, 0xE33309, 0x7C4C1E, 0xFA00E5, 0xF69913, 0x70D5E8, 0x4E2BC6, 0xC8673D,
        0xC4FECB, 0x42B230, 0xDDCD27, 0x5B81DC, 0x57182A, 0xD154D1, 0x26359F, 0xA07964, 0xACE092, 0x2AAC69,
        0xB5D37E, 0x339F85, 0x3F0673, 0xB94A88, 0x87B4A6, 0x01F85D, 0x0D61AB, 0x8B2D50, 0x145247, 0x921EBC,
        0x9E874A, 0x18CBB1, 0xE37B16, 0x6537ED, 0x69AE1B, 0xEFE2E0, 0x709DF7, 0xF6D10C, 0xFA48FA, 0x7C0401,
        0x42FA2F, 0xC4B6D4, 0xC82F22, 0x4E63D9, 0xD11CCE, 0x575035, 0x5BC9C3, 0xDD8538};

bool operator==(const string s1, const string s2)
{
    if (s1.compare(s2) == 0)
        return true;
    else
        return false;
}

bool crcCheck(vector<string> &rtcm, int *buf)
{
    if (stoi(rtcm[rtcm.size() - 3], nullptr, 16) == buf[0])
    {
        if (stoi(rtcm[rtcm.size() - 2], nullptr, 16) == buf[1])
        {
            if (stoi(rtcm[rtcm.size() - 1], nullptr, 16) == buf[2])
            {
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

long int int2hex(string &it)
{
    return stol(it, nullptr, 16);
}

string hex_to_bin(const string &hex)
{
    std::string bin;
    for (size_t i = 0; i < hex.length(); ++i)
    {
        char hex_char = hex[i];
        int hex_value = 0;
        if (hex_char >= '0' && hex_char <= '9')
        {
            hex_value = hex_char - '0';
        }
        else if (hex_char >= 'a' && hex_char <= 'f')
        {
            hex_value = hex_char - 'a' + 10;
        }
        else if (hex_char >= 'A' && hex_char <= 'F')
        {
            hex_value = hex_char - 'A' + 10;
        }
        std::bitset<4> bin_value(hex_value);
        bin += bin_value.to_string();
    }
    return bin;
}

string bin_to_hex(const string &binary)
{
    std::string hex;
    int len = binary.length();
    for (int i = 0; i < len; i += 4)
    {
        int val = 0;
        for (int j = 0; j < 4; j++)
        {
            if (binary[i + j] == '1')
                val |= 1 << (3 - j);
        }
        hex += (val < 10) ? ('0' + val) : ('A' + val - 10);
    }
    return hex;
}

string binToComplement(const string &binaryString, int bitWidth)
{
    string paddedString = binaryString;

    if (paddedString[0] == '0')
    {
        return paddedString;
    }

    string invertedString = paddedString;
    replace(invertedString.begin() + 1, invertedString.end(), '0', 't');
    replace(invertedString.begin() + 1, invertedString.end(), '1', '0');
    replace(invertedString.begin() + 1, invertedString.end(), 't', '1');

    bool carry = true;
    for (int i = bitWidth - 1; i > 0 && carry; --i)
    {
        if (invertedString[i] == '1')
        {
            invertedString[i] = '0';
        }
        else
        {
            invertedString[i] = '1';
            carry = false;
        }
    }

    return invertedString;
}

long int bin2int(string &bin, int width)
{
    auto bin_com = binToComplement(bin, width);
    auto tmp = bin_com.substr(1, bin_com.length() - 1);
    while (tmp.length() < 40)
    {
        tmp = '0' + tmp;
    }
    auto size = tmp.length();
    auto hex = bin_to_hex(tmp);
    if (bin_com[0] == '0')
        return stol(hex, nullptr, 16);
    else
        return -stol(hex, nullptr, 16);
}

void Decode_XYZ(vector<string>::iterator check, long int *Location)
{
    string tmp;
    for (auto i = 0; i < 3; ++i)
    {
        auto str = *(check + 1) + *(check + 2) + *(check + 3) + *(check + 4);
        tmp = hex_to_bin(str);
        tmp = hex_to_bin(*(check)).substr(2, 6) + tmp;
        Location[i] = bin2int(tmp, 38);
        if (i <= 1)
            check += 5;
    }
}

int main(void)
{
    int stableID = 0; // 基准站ID
    long int Location[3] = {0, 0, 0};
    string header[2] = {
        "D3", "00"};
    int crc = 0, i;
    int infoLenth = 0;
    int buf[3];
    auto rtcm = fileIn("./input.txt");
    // Header Check
    auto D3check = find(rtcm.begin(), rtcm.end(), header[0]);
    if (D3check != rtcm.end())
    {
        auto check = find(D3check, D3check + 1, header[1]);
        if (check != rtcm.end())
        {
            // Get Length of Info
            infoLenth = stoi(*(++check), nullptr, 16);
            if (rtcm.size() - 3 >= infoLenth + 3)
            {
                // CRC Check
                for (i = 0; i < infoLenth + 3; i++)
                {
                    crc = ((crc << 8) & 0xFFFFFF) ^ table[(crc >> 16) ^ (stoi(rtcm[i], nullptr, 16) & 0xFF)];
                }
                buf[0] = ((crc & 0xFF0000) >> 16);
                buf[1] = ((crc & 0xFF00) >> 8);
                buf[2] = (crc & 0xFF);
                if (crcCheck(rtcm, buf))
                {
                    auto DataType = stoi(*(check + 1) + (*(check + 2))[0], nullptr, 16);
                    check += 2;
                    for (auto i = 0; i < 7; ++i)
                    {
                        // Check DataType
                        if (DataType == Type[i])
                        {
                            if (i == 0 || i == 1)
                            {
                                // Decode XYZ Data
                                stableID = stoi((*check)[1] + (*(check + 1)), nullptr, 16);
                                check += 3;
                                Decode_XYZ(check, Location);
                            }
                        }
                    }
                }
            }
        }
    }
    for (auto &it : Location)
    {
        cout << it << '\n';
    }
    return 0;
}
