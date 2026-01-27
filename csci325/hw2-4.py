# Alexandra Chase
# amchas26@g.holycross.edu
# 14 September 2025
# CSCI 325 Homework 2

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
    
    # find keyword using index of coincidence
    print("Finding keyword length using Index of Coincidence...")
    ciphertext = open("cipherNoKey.txt", "r").read() # read in the ciphertext from the file
    keylength = findKeyLength(ciphertext) # find the most likely key length
    
    # find the keyword using frequency analysis
    print("Running frequency analysis to find keyword with length ", keylength, "...")
    keyword = findKeyword(ciphertext, keylength, alphabet_values)
    
    # run the decryption with found key
    print("Running Vigenere Cipher Decryption of given file with key " + keyword + "...")
    decrypted_message = vigenere_decrypt(ciphertext, keyword, alphabet_values)
    print("Decrypted message (first 200 chars): ", decrypted_message[:200])
    
    # output doesn't make sense with found keyword, try chi-squared analysis
    print("That is still nonsense. Trying Chi-Squared analysis to find a better keyword...")
    keyword = findKeywordChiSq(ciphertext, keylength, alphabet_values)
    
    # run the decryption with found key
    print("Running Vigenere Cipher Decryption of given file with key " + keyword + "...")
    decrypted_message = vigenere_decrypt(ciphertext, keyword, alphabet_values)
    print("Decrypted message (first 200 chars): ", decrypted_message[:200])
    with open("plaintext.txt", "w") as f: # write the decrypted message to a file
        f.write(decrypted_message)

def assign_alphabet_values():
    # for each letter in the alphabet, assign it a value from 0-25 in a dictionary
    alphabet_values = {}
    for i, letter in enumerate(string.ascii_uppercase):
        alphabet_values[letter] = i
    return alphabet_values

def index_of_coincidence(ciphertext):
    # Calculate the Index of Coincidence for a given text
    frequency = collections.Counter(ciphertext) # count frequency of each letter
    n = len(ciphertext) # total number of letters in given ciphertext
    if n <= 1:
        return 0
    ioc = sum(f * (f - 1) for f in frequency.values()) / (n * (n - 1)) # IOC formula: sum of frequencies of each letter 
    return ioc

def findKeyLength(ciphertext):
    # Function to find the most likely key length using Index of Coincidence
    avgiocs = {} # dictionary to store average IoC for each key length and the difference from 0.067    
    bestLength = 0  # best key length found
    bestioc = 100 # start with a high IoC to find the best
    
    for keyLength in range(1, 21): # test key lengths from 1 to 20
        substrings = ['' for _ in range(keyLength)] # create substrings for each position in the key
        for i, curr in enumerate(ciphertext): # iterate through the ciphertext
            substrings[i % keyLength] += curr # distribute letters into substrings based on key length
        avg_ioc = sum(index_of_coincidence(sub) for sub in substrings) / keyLength # calculate avg IoC for the substrings
        print("For key length ", keyLength, ", IoC = ", avg_ioc) # print the IoC of the substring for this key length
        iocdiff = abs(0.067 - avg_ioc) # difference from expected IoC for English text
        avgiocs[keyLength] = (avg_ioc, iocdiff) # store avg IoC and its difference val
        if iocdiff < bestioc: # if this IoC is closer to 0.067 than previous best, update best
            bestLength = keyLength
            bestioc = iocdiff
    print("Best key length found: ", bestLength, " with IoC difference of ", bestioc)
    return bestLength
        
def findKeyword(ciphertext, keylength, alphabet_values):
    # Function to find the keyword using frequency analysis
    substrings = ['' for _ in range(keylength)] # create substrings for each position in the key
    for i, curr in enumerate(ciphertext): # distribute letters into substrings based on key length
        substrings[i % keylength] += curr 
    keywordChars = [] # list to store the found keyword characters
    
    for sub in substrings: # for each substring, perform frequency analysis
        freq = collections.Counter(sub) # count frequency of each letter in the substring
        most_common_letter, _ = freq.most_common(1)[0] # get the most common letter in the substring
        shift = (alphabet_values[most_common_letter] - alphabet_values['E']) % 26 # assume 'E' is the most common letter in English
        keyword_curr = chr((shift + ord('A'))) # calculate the corresponding character in the keyword
        keywordChars.append(keyword_curr) # append to keyword list
    
    keyword = ''.join(keywordChars) # join list into a string
    print("Found keyword: ", keyword)
    return keyword

def findKeywordChiSq(ciphertext, keylength, alphabet_values):
    # English letter frequencies (A-Z, normalized)
    english_freq = [
        0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094,
        0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929,
        0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
        0.01974, 0.00074
    ]
    substrings = ['' for _ in range(keylength)] # create substrings for each position in the key
    for i, curr in enumerate(ciphertext): # distribute letters into substrings based on key length
        substrings[i % keylength] += curr
    keywordChars = [] # list to store the found keyword characters
    
    for sub in substrings: # for each substring, perform chi-squared analysis
        if len(sub) == 0:  # handle empty substring case
            keywordChars.append('A')
            continue
        min_chi_sq = float('inf') # initialize min chi-squared value
        best_shift = 0 # initialize best shift
        for shift in range(26): # try all possible shifts (0-25)
            shifted = [chr((alphabet_values[c] - shift) % 26 + ord('A')) for c in sub] # shift the subs
            freq = collections.Counter(shifted) # count frequency of each letter in the shifted substring
            chi_sq = 0.0 # initialize chi-squared value
            for i in range(26): # calculate chi-squared stats
                observed = freq.get(chr(ord('A') + i), 0) # observed frequency of letter
                expected = english_freq[i] * len(sub) # expected frequency based on standard Eng letter frequencies
                chi_sq += ((observed - expected) ** 2) / expected if expected > 0 else 0 # chi-squared formula
            if chi_sq < min_chi_sq: # if this chi-squared is the lowest found, update best
                min_chi_sq = chi_sq
                best_shift = shift
        keyword_curr = chr(ord('A') + best_shift) # calculate the corresponding character in the keyword
        keywordChars.append(keyword_curr) # append to keyword list
    keyword = ''.join(keywordChars) 
    print("Found keyword: ", keyword) 
    return keyword


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