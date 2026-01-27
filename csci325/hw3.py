# Alexandra Chase
# amchas26@g.holycross.edu
# 29 September 2025
# CSCI 325 Homework 3 Question 3
# OFB Mode Encryption/Decryption

import math           # for algebraic calculations

def xorBytes(p1,p2):
    return bytes(a ^ b for a, b in zip(p1, p2))

# attacker has access to p1, c1, c2
with open("p1.txt", "rb") as f:
    p1 = f.read()
    print(f"Attacker has access to the first plaintext (P1): {p1.decode()}")

with open("c1.bin", "rb") as f:
    c1 = f.read()
    print(f"Attacker has access to the first ciphertext (C1): {c1.decode(errors='ignore')}")

with open("c2.bin", "rb") as f:
    c2 = f.read()
    print(f"Attacker has access to the second ciphertext (C2): {c2.decode(errors='ignore')}")

# recover the keystream S = P1 XOR C1
print("Recovering the keystream...")
keystream = xorBytes(p1, c1)

# recover P2 = C2 XOR S
print("Recovering the second plaintext (P2)...")
recovered_p2 = xorBytes(c2, keystream)

# save the recovered plaintext to a file
with open('recovered_p2.txt', 'wb') as f:
    f.write(recovered_p2)

print("\nAttack was successful!")
print(f"The recovered plaintext is: {recovered_p2.decode()}")
print("It has been saved to 'recovered_p2.txt'.")