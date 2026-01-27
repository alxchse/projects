# alexandra chase
# amchas26@g.holycross.edu
# 21 october 2025
# practice sending packets in python

import socket

IP = "0.0.0.0"  # listen on all interfaces
PORT = 65432  # arbitrary port

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # create a UDP socket
sock.bind((IP, PORT))  # bind the socket to the address and port
print(f"Server listening on {IP}:{PORT}")

while True:
    data, (ip, port) = sock.recvfrom(1024)  # receive data from a client
    print(f"Received from {ip}:{port}: {data.decode()}")  # print the received data