import socket
import time
import threading

client_sockets = []
MAX_CLIENTS = 10


def listen():
    HOST, PORT = "localhost", 9999
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen(MAX_CLIENTS)
        print('Listening on {}:{}'.format(HOST, PORT))
        while True:
            conn, addr = s.accept()
            print('Got connection from {}'.format(addr))
            client_sockets.append(conn)


def heartbeat():
    # TODO: Because 'listen' is in a thread, I can see a critical section
    # occuring here resulting in the 'for' look freaking out over changes
    # in the length of client_sockets
    print('Beginning heartbeats')
    while True:
        for sock in client_sockets:
            sock.sendall(b'HELLO')
        time.sleep(1)

if __name__ == "__main__":
    listener = threading.Thread(target=listen)
    listener.start()
    heartbeat()
