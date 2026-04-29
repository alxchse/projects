# Alexandra Chase
# amchas26@g.holycross.edu
# CSCI 356, Project 1
# 09 September 2024

#!/usr/bin/python3
# Author: K. Walsh <kwalsh@cs.holycross.edu>
# Date: 20 August 2020
#
# A simple POP3 client from scratch in Python. Run it like this:
#   ./pop3-client.py whitehouse.kwalsh.org 110
# It will connect to whitehouse.kwalsh.org on port 110, the standard POP3 port,
# then allow the user to send and receive data.
# - To send data, type "send" followed by something, then hit enter. A standard
#   POP3 line ending "\r\n" will be sent automatically as well.
# - To receive data, type "recv" then hit enter.
#
# Note: This code is not "pythonic" at all; there are more concise ways to write
# this code by using python features like dicts and string interpolation. We
# also avoid use of any modules except for a few basic ones.

import socket    # for socket stuff
import sys       # for sys.argv
import traceback # for printing exceptions

# Global configuration variables, with default values
server_host = None
server_port = None

class SocketError:
    def __init__(self, msg):
        self.msg = msg
    def __repr__(self):
        return "Socket Error: " + msg

ERR_SOCKET_WAS_CLOSED = SocketError("Connection Closed")
ERR_SOCKET_HAD_TIMEOUT = SocketError("Read Timeout")
ERR_SOCKET_HAD_ERROR = SocketError("Read Failure")

# recv_one_line attempts to read() data from socket connection, repeatedly,
# until a "\r\n" pair is detected. It returns all the data received as a python
# string, not including the terminating "\r\n" pair. If something went wrong,
# then a special value is returned instead:
# - ERR_SOCKET_WAS_CLOSED is returned if the connection was closed unexpectedly
# - ERR_SOCKET_HAD_TIMEOUT is returned if no data was received for 3 seconds
# - ERR_SOCKET_HAD_ERROR is returned if som other error occurred
def read_one_line(connection):
    # Set 3 second timeout, so we don't wait for data forever
    connection.settimeout(3.0)
    try:
        data = ""
        # Keep reading from socket until we get a "\r\n" pair.
        while not data.endswith("\r\n"):
            # Read one more byte from socket, append it to our data.
            more_data = connection.recv(1)
            if not more_data:
                return ERR_SOCKET_WAS_CLOSED
            data += more_data.decode() # decode byte as an ascii character
        # Return the accumulated data, without the terminating "\r\n" sequence.
        return data[:-2]
    except socket.timeout as err:
        return ERR_SOCKET_HAD_TIMEOUT
    except:
        print("Error reading from socket: " + traceback.format_exc())
        return ERR_SOCKET_HAD_ERROR
    finally:
        # Remove the timeout, so future operations are not affected by this.
        connection.settimeout(None)

# Get command-line parameters, if present
server_host = "whitehouse.kwalsh.org"
server_port = 110

# Print a welcome message
print("Welcome to the A.C. email client!")
print("Using server %s on port %d" % (server_host, server_port))

# Create a client socket, and connect it to the server
server_addr = (server_host, server_port)
connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
connection.connect(server_addr)

print("Connecting...")
print()
resp = read_one_line(connection)   
if resp.startswith("+"):                                  
    print("Successful connection established!")
else:
    print("Failed to connect to server. Program will now quit.")
    print("Server error states: " + resp)
    sys.exit()

# First, ask what the user's username is. Do not ask for password.
print("What is your username?")
ans = input()
connection.sendall(("user " + ans + "\r\n").encode())
print("Logging in as " + ans + " with the default password.")
resp = read_one_line(connection)
if resp.startswith("+"):                                  
    print("User " + ans + " verified.")
else:
    print("Failed to validate user. Program will now quit.")
    print("Server error states: " + resp)
    sys.exit()                                    

# All users have same password, so automatically send. 
connection.sendall(("pass hunter2" + "\r\n").encode())
print("Welcome " + ans + " to the brand-new A.C. email client!")
resp = read_one_line(connection)
if resp.startswith("+"):                                  
    print("Password accepted.")
else:
    print("Failed to validate password. Program will now quit.")
    print("Server error states: " + resp)
    sys.exit()

# Grab stats for email. Show user how many emails they have. 
connection.sendall(("stat" + "\r\n").encode())
resp = read_one_line(connection)
words = resp.split()
numEmails = words[1]
if resp.startswith("+"):                                  
    print("You have " + words[1] + " emails in your inbox.")
    if (words[1] == 0):
        print("Can't perform actions with no emails! Program will now quit.")
        sys.exit()
else:
    print("Failed to validate inbox info. Program will now quit.")
    print("Server error states: " + resp)
    sys.exit()

deletedMsgs = set()
readMsgs = set()
curr = 1
i = 1

try: # Finally, the main user-interaction loop.
    while True:
        
        for i in range(curr, curr+3): # list the headers for the next 3 messages
            connection.sendall(("list " + str(i) + "\r\n").encode())
            resp = read_one_line(connection)
            if resp.startswith("-"):
                print("Could not list messages.")
                print("Server error states: " + resp)
            words = resp.split()
            msgNum = int(words[1])
            if i == curr:
                print(" * ", end='')
            else:
                print("   ", end='')
            if msgNum in deletedMsgs: 
                print("["+words[1]+"] DELETED")
            elif msgNum in readMsgs: 
                print("["+words[1]+"]"+" (old) "+words[2]+" bytes " +words[3]+" "+words[4])
            elif msgNum not in readMsgs: 
                print("["+words[1]+"]"+" (new) "+words[2]+" bytes "+words[3]+" "+words[4])
        try:
            print("[V]iew msg, [S]kip msg, [D]elete msg, [J]ump to other msg, or [Q]uit?")
            cmd = input()
        except:
            break

        if cmd == "V" or cmd == "v": # if the user decides to view the curr message
            connection.sendall(("retr " + str(curr) + "\r\n").encode())
            resp = read_one_line(connection)
            if resp.startswith("-"):
                print("Could not display full message.")
                print("Server error states: " + resp)
                break
            line = read_one_line(connection)
            while line != ".":
                print(line)
                line = read_one_line(connection)
            readMsgs.add(curr)

        elif cmd == "S" or cmd == "s": # if the user decides to skip the curr message
            curr = curr + 1
        
        elif cmd == "D" or cmd == "d": # if the user decides to delete the curr message
            if curr in deletedMsgs:
                print("Message is already selected for deletion!")
            else: 
                deletedMsgs.add(curr)
                curr = curr + 1
        
        elif cmd == "U" or cmd == "u": # if the user decides to undelete the curr message
            if curr not in deletedMsgs:
                print("Message is not currently selected for deletion.")
            else:
                deletedMsgs.remove(curr)

        elif cmd == "J" or cmd == "j": # if the user decides to jump to a new message
            print("What message number would you like to jump to?")
            ans = input()
            curr = int(ans)

        elif cmd == "Q" or cmd == "q": # if the user decides to quit the program
            print("Are you sure you want to quit and permanently delete the indicated messages? [Y]/[N]")
            ans = input()
            if ans == "Y" or ans == "y":
                for deletedMsg in deletedMsgs: # go through and actually delete all messages
                    print("Deleting message number: " + str(deletedMsg))
                    connection.sendall(("dele " + str(deletedMsg) + "\r\n").encode())
                    resp = read_one_line(connection)
                    if resp.startswith("-"):                                  
                        print("Deletion of message " + deletedMsg + " could not be completed.")
                        print("Server error states: " + resp)
                deletedMsgs.clear()
                connection.sendall(("quit\r\n").encode()) # quit program
                resp = read_one_line(connection)
                if resp.startswith("-"):
                    print("Quit function failed. " + resp)                         
                    sys.exit()
                print("Okay! Everything is deleted.")
            else:                
                connection.sendall(("rset\r\n").encode())
                resp = read_one_line(connection)
                continue
        elif cmd == "fail": # this is only for stress-testing the pop-server
            connection.sendall(b"\r\n")
            print("recv: " + read_one_line(connection))
            connection.sendall(b" \r\n")
            print("recv: " + read_one_line(connection))
            connection.sendall(b" \n  \r\n")
            print("recv: " + read_one_line(connection))
            connection.sendall(b"xyz")
            break
        else:
            print("Command not valid. Choose from one of the options below:")
finally:
    print("Closing socket connection to server.")
    connection.close()
    print("Done.")
    sys.exit()