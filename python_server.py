import socket
from _thread import *
import time
import json

host = '127.0.0.1'
port = 8080
ThreadCount = 0

def client_handler(connection):
    data = connection.recv(2048)
    message = data.decode('utf-8')
    print(f"{type(message)}\n>{message}<")
    cleanstring = message.split('\x00',1)[0]    
    json_obj = json.loads(cleanstring)
    date = time.strftime('%X %x %Z')
    print(f'\n{date}\n{json_obj}\n\n')
    connection.sendall(str.encode(f'I have received your message {message}'))
    connection.close()

def accept_connections(ServerSocket):
    Client, address = ServerSocket.accept()
    print('Connected to: ' + address[0] + ':' + str(address[1]))
    start_new_thread(client_handler, (Client, ))

def start_server(host, port):
    ServerSocket = socket.socket()
    try:
        ServerSocket.bind((host, port))
    except socket.error as e:
        print(str(e))
    print(f'Server is listing on the port {port}...')
    ServerSocket.listen()

    while True:
        accept_connections(ServerSocket)

start_server(host, port)