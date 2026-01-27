# alexandra chase
# amchas26@g.holycross.edu
# 21 october 2025
# practice sending packets in python

import socket

IP = "127.0.0.1"  # localhost
PORT = 65432  # arbitrary port
data = b"Hello, World!"  # data to send

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # create a UDP socket
sock.sendto(data, (IP, PORT))  # send data to the server
print(f"Sent: {data.decode()}")  # print the sent data
sock.close()  # close the socket