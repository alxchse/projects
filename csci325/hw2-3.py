# Alexandra Chase
# amchas26@g.holycross.edu
# 14 September 2025
# CSCI 325 Homework 2 Question 3

import math           # for algebraic calculations
import collections    
import os             # for file and directory stuff, like os.path.isfile()
import socket         # for socket stuff
import sys            # for sys.argv and sys.exit()
import random         # for random numbers
import re             # for regex functions
import string         # for various string operations

def main():
    # main function, start with assigning alphabet values
    alphabet_values = assign_alphabet_values() # get the alphabet values
    
    # run the encryption
    plaintext = "MAYTHEFOURTHBEWITHYOU"
    keyword = "LUKE"
    print("Running Vigenere Cipher Encryption of " + plaintext + " using keyword " + keyword + "...")
    encrypted_message = vigenere_encrypt(plaintext, keyword, alphabet_values)
    print("Encrypted message: ", encrypted_message)
    
    # run the decryption with known key
    print("Now running Vigenere Cipher Decryption of given file with Known Key...")
    keyword = "TAGORE"
    ciphertext = open("cipherKnownKey.txt", "r").read() # read in the ciphertext from the file
    decrypted_message = vigenere_decrypt(ciphertext, keyword, alphabet_values)
    print("Decrypted message: ", decrypted_message)

def assign_alphabet_values():
    # for each letter in the alphabet, assign it a value from 0-25 in a dictionary
    alphabet_values = {}
    for i, letter in enumerate(string.ascii_uppercase):
        alphabet_values[letter] = i
    return alphabet_values

def vigenere_encrypt(plaintext, keyword, alphabet_values):
    # Vigenere cipher encryption function
    keyidx = 0 # index for the keyword
    encrypted_text = [] # encrypted text is in a list to make appending easier
    for i in range(len(plaintext)): # for each letter in the plaintext
        curr = plaintext[i]
        if curr in string.ascii_uppercase: # only encrypt letters, skip spaces and punctuation  
            shift = alphabet_values[keyword[keyidx % len(keyword)]] # tells us how much to shift by
            encrypted_char = chr((alphabet_values[curr] + shift) % 26 + ord('A')) # encrypts the character algebraically
            encrypted_text.append(encrypted_char) # append encrypted character to list
            keyidx += 1 # increment key 
        else:
            encrypted_text.append(curr) # if not a letter, just append the character as is    
    return ''.join(encrypted_text) # join the list into a string and return it  

def vigenere_decrypt(ciphertext, keyword, alphabet_values):
    # Vigenere cipher decryption function
    keyidx = 0 # index for the keyword
    decrypted_text = [] # decrypted text is in a list to make appending easier
    for i in range(len(ciphertext)): # for each letter in the ciphertext
        curr = ciphertext[i]
        if curr in string.ascii_uppercase: # only decrypt letters, skip spaces and punctuation
            shift = alphabet_values[keyword[keyidx % len(keyword)]] # tells us how much to shift by
            decrypted_char = chr((alphabet_values[curr] - shift) % 26 + ord('A')) # decrypts the character algebraically
            decrypted_text.append(decrypted_char) # append decrypted character to list
            keyidx += 1 # increment key 
        else:
            decrypted_text.append(curr) # if not a letter, just append the character as is
    print("Using key: " + keyword)
    return ''.join(decrypted_text) # join the list into a string and return it          
      
if __name__ == "__main__":
    main()    
   


