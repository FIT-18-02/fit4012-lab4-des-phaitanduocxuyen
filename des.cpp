#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm> // Thêm thư viện để đảo ngược khóa

using namespace std;

// --- CÁC HÀM TRỢ GIÚP (GLOBAL FUNCTIONS) ---
string convert_decimal_to_binary(int decimal) {
    return bitset<4>(decimal).to_string();
}

int convert_binary_to_decimal(const string& binary) {
    return stoi(binary, nullptr, 2);
}

string Xor(const string& a, const string& b) {
    string result = "";
    for (size_t i = 0; i < b.size(); i++) {
        result += (a[i] != b[i]) ? '1' : '0';
    }
    return result;
}

// --- HOÁN VỊ KHỞI TẠO VÀ KẾT THÚC ---
string initial_permutation(const string& input) {
    const int ip_table[64] = {
        58,50,42,34,26,18,10,2, 60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6, 64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1, 59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5, 63,55,47,39,31,23,15,7
    };
    string permuted = "";
    for (int i = 0; i < 64; i++) permuted += input[ip_table[i] - 1];
    return permuted;
}

string inverse_initial_permutation(const string& input) {
    const int inv_ip_table[64] = {
        40,8,48,16,56,24,64,32, 39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30, 37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28, 35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26, 33,1,41,9,49,17,57,25
    };
    string permuted = "";
    for (int i = 0; i < 64; i++) permuted += input[inv_ip_table[i] - 1];
    return permuted;
}

// --- SINH KHÓA VÒNG (KEY GENERATOR) ---
class KeyGenerator {
private:
    string key;
    vector<string> roundKeys;
    const int pc1[56] = {57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
    const int pc2[48] = {14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};

public:
    KeyGenerator(const string& input_key) : key(input_key) {}
    void generateRoundKeys() {
        roundKeys.clear();
        string permKey = "";
        for (int i = 0; i < 56; i++) permKey += key[pc1[i] - 1];
        string L = permKey.substr(0, 28), R = permKey.substr(28, 28);
        for (int i = 0; i < 16; i++) {
            int shift = (i == 0 || i == 1 || i == 8 || i == 15) ? 1 : 2;
            L = L.substr(shift) + L.substr(0, shift);
            R = R.substr(shift) + R.substr(0, shift);
            string combined = L + R, rKey = "";
            for (int j = 0; j < 48; j++) rKey += combined[pc2[j] - 1];
            roundKeys.push_back(rKey);
        }
    }
    const vector<string>& getRoundKeys() const { return roundKeys; }
};

// --- THUẬT TOÁN DES (ENCRYPTION/DECRYPTION) ---
class DES {
private:
    const int exp_t[48] = {32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
    const int perm_p[32] = {16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
    const int s_box[8][4][16] = {
        {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
        {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
        {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
        {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
        {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
        {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
        {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
        {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
    };
    vector<string> rKeys;

public:
    DES(const vector<string>& keys) : rKeys(keys) {}

    string encrypt_block(const string& block) {
        string perm = initial_permutation(block);
        string L = perm.substr(0, 32), R = perm.substr(32, 32);
        for (int i = 0; i < 16; i++) {
            string R_exp = "";
            for (int j = 0; j < 48; j++) R_exp += R[exp_t[j] - 1];
            string xored = Xor(rKeys[i], R_exp);
            string s_out = "";
            for (int j = 0; j < 8; j++) {
                string b = xored.substr(j * 6, 6);
                int row = convert_binary_to_decimal(string(1, b[0]) + b[5]);
                int col = convert_binary_to_decimal(b.substr(1, 4));
                s_out += convert_decimal_to_binary(s_box[j][row][col]);
            }
            string p_out = "";
            for (int j = 0; j < 32; j++) p_out += s_out[perm_p[j] - 1];
            string temp = R;
            R = Xor(p_out, L); L = temp;
        }
        return inverse_initial_permutation(R + L);
    }
};

// --- Q3 & Q4: GIẢI MÃ VÀ TRIPLE DES ---[cite: 1]
string des_decrypt(string cipher, vector<string> keys) {
    reverse(keys.begin(), keys.end()); // Dùng khóa ngược[cite: 1]
    DES engine(keys);
    return engine.encrypt_block(cipher);
}

string triple_des(int mode, string input, string k1, string k2, string k3) {
    KeyGenerator kg1(k1), kg2(k2), kg3(k3);
    kg1.generateRoundKeys(); kg2.generateRoundKeys(); kg3.generateRoundKeys();
    DES e1(kg1.getRoundKeys()), e2(kg2.getRoundKeys()), e3(kg3.getRoundKeys());

    if (mode == 3) { // Encrypt: E(k3)-D(k2)-E(k1)[cite: 1]
        string s1 = e1.encrypt_block(input);
        string s2 = des_decrypt(s1, kg2.getRoundKeys());
        return e3.encrypt_block(s2);
    } else { // Decrypt: D(k1)-E(k2)-D(k3)[cite: 1]
        string s1 = des_decrypt(input, kg3.getRoundKeys());
        string s2 = e2.encrypt_block(s1);
        return des_decrypt(s2, kg1.getRoundKeys());
    }
}

// --- HÀM MAIN: TUÂN THỦ SUBMISSION CONTRACT ---[cite: 1]
int main() {
    int mode;
    if (!(cin >> mode)) return 0; // Đọc chế độ[cite: 1]

    string input, k1, k2, k3;
    if (mode == 1 || mode == 2) {
        cin >> input >> k1; // Đọc plaintext và key[cite: 1]
        KeyGenerator kg(k1); kg.generateRoundKeys();
        DES engine(kg.getRoundKeys());

        if (mode == 1) { // Q2: DES Encrypt + Padding[cite: 1]
            while (input.length() % 64 != 0) input += '0'; // Zero padding[cite: 1]
            string result = "";
            for (size_t i = 0; i < input.length(); i += 64)
                result += engine.encrypt_block(input.substr(i, 64));
            cout << result << endl;
        } else { // Q3: DES Decrypt[cite: 1]
            cout << des_decrypt(input, kg.getRoundKeys()) << endl;
        }
    }
    else if (mode == 3 || mode == 4) { // Q4: Triple DES[cite: 1]
        cin >> input >> k1 >> k2 >> k3;
        cout << triple_des(mode, input, k1, k2, k3) << endl;
    }

    return 0;
}