#include <iostream>
#include <string>

std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int letterposition(char letter)
{
    for (int i = 0; i < alphabet.length(); i++)
    {
        if (alphabet[i] == letter)
        {
            return i;
        }
    }
    return -1;  
}

std::string encryptShift(const std::string &message, unsigned key)
{
    std::string encryptedstring = message;
    for (int i = 0; i < message.length(); i++)
    {
        if (message[i] >= 'A' && message[i] <= 'Z')
        {
            int pos = letterposition(message[i]);
            encryptedstring[i] = alphabet[(pos + key) % 26];
        }
    }
    return encryptedstring;
}

std::string decryptShift(const std::string &message, unsigned key)
{
    std::string decryptedstring = message;
    for (int i = 0; i < message.length(); i++)
    {
        if (message[i] >= 'A' && message[i] <= 'Z')
        {
            int pos = letterposition(message[i]);
            decryptedstring[i] = alphabet[(pos - key + 26) % 26];
        }
    }
    return decryptedstring;
}

bool decryptSubstitution(const std::string& ciphertext, const std::string& crib, std::string& substitutionMap) {
    
    auto ord = [](char c) -> int {
        return c - 'A';
    };

    if (ciphertext.length() != crib.length()) {
        return false;
    }

    for (int i = 0; i < crib.length(); i++) {
        char crib_letter = crib[i];
        char ciphertext_letter = ciphertext[i];
        if (crib_letter != ' ') {
            if (substitutionMap[ord(ciphertext_letter)] != '-' && substitutionMap[ord(ciphertext_letter)] != crib_letter) {
                return false;
            }
            substitutionMap[ord(ciphertext_letter)] = crib_letter;
        }
    }

    return true;
}

std::string encryptAffine(const std::string &message, unsigned affineAlpha, unsigned affineBeta) {
    std::string encryptedstring = message;
    for (int i = 0; i < message.length(); i++) {
        if (message[i] >= 'A' && message[i] <= 'Z')
        {
            int pos = letterposition(message[i]);
            encryptedstring[i] = alphabet[(affineAlpha * pos + affineBeta) % 26];
        }
    }
    return encryptedstring;
}

std::string decryptAffine(const std::string &message, unsigned affineAlpha, unsigned affineBeta) {
    std::string decryptedstring = message;

    unsigned inverseAlpha = 1;
    for (int x = 1; x < 26; x++)
        if ((affineAlpha * x) % 26 == 1)
            inverseAlpha = x;

    for (int i = 0; i < message.length(); i++) {
        if (message[i] >= 'A' && message[i] <= 'Z')
        {
            int pos = letterposition(message[i]);
            decryptedstring[i] = alphabet[(inverseAlpha * (pos - affineBeta + 26)) % 26];
        }
    }
    return decryptedstring;
}



int main()
{
    // Encryption & Decryption using Shift Cipher
    std::string message;
    unsigned key;
    std::cout << "-----SHIFT CIPHER-----" << std::endl;
    std::cout << "Enter your string to encrypt (in uppercase): ";
    std::getline(std::cin, message);
    std::cout << "Enter the encryption key (between 1 and 25): ";
    std::cin >> key;

    std::string encryptedMessageShift = encryptShift(message, key);
    std::cout << "Encrypted Message (Shift): " << encryptedMessageShift << std::endl;

    std::string decryptedMessageShift = decryptShift(encryptedMessageShift, key);
    std::cout << "Decrypted Message (Shift): " << decryptedMessageShift << std::endl;

    std::cin.ignore();





    // Decryption using Simple Substitution Cipher
    std::cout << "\n-----SUBSTITUTION CIPHER-----" << std::endl;
    std::string ciphertext;
    std::string crib;

    std::cout << "Enter the encrypted message: ";
    std::getline(std::cin, ciphertext);

    std::cout << "Enter the crib: ";
    std::getline(std::cin, crib);

    // Initialize the substitution map.
    std::string substitutionMap(26, '-');

    // Decrypt the ciphertext using the known plaintext attack.
    bool success = decryptSubstitution(ciphertext, crib, substitutionMap);

    // Check if the crib was found in the ciphertext.
    if (success) {
        std::cout << "Substitution Map: " << substitutionMap << std::endl;
    } else {
        std::cout << "The crib could not be mapped to the ciphertext." << std::endl;
    }






    // Encryption & Decryption using Affine Cipher
    unsigned affineAlpha, affineBeta;
    std::cout << "\n-----AFFINE CIPHER-----" << std::endl;
    std::cout << "Enter your string to encrypt (in uppercase): ";
    std::getline(std::cin, message);
    std::cout << "Enter the alpha value for affine encryption (odd value, not 13, between 1 and 25): ";
    std::cin >> affineAlpha;
    std::cout << "Enter the beta value for affine encryption (between 0 and 25): ";
    std::cin >> affineBeta;

    std::string encryptedMessageAffine = encryptAffine(message, affineAlpha, affineBeta);
    std::cout << "Encrypted Message (Affine): " << encryptedMessageAffine << std::endl;

    std::string decryptedMessageAffine = decryptAffine(encryptedMessageAffine, affineAlpha, affineBeta);
    std::cout << "Decrypted Message (Affine): " << decryptedMessageAffine << std::endl;

    return 0;
}
