import socket

HOST, PORT = "localhost", 9999

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    sock.connect((HOST, PORT))
    while True:
        received = str(sock.recv(1024), "utf-8")
        print(received)
finally:
    sock.close()
