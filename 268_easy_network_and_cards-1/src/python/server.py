import socket


if __name__ == "__main__":
    HOST, PORT = "localhost", 9999
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen(1)
        conn, addr = s.accept()
        with conn:
            data = conn.recv(1024)
            conn.sendall(data.upper())
