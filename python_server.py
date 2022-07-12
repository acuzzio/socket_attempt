import socket
import _thread as thr
import time
import json
from argparse import ArgumentParser


def read_arguments():
    description_string = "This is the tcp server."
    parser = ArgumentParser(description=description_string)
    parser.add_argument("-i", "--ip", type=str,
                        default='127.0.0.1', help="ip host")
    parser.add_argument("-p", "--port", type=int, default=8080, help="port")
    return parser.parse_args()


def recv_end(the_socket):
    End = b'<<END>>'
    total_data = []
    data = ''
    while True:
        data = the_socket.recv(8192)
        if End in data:
            total_data.append(data[:data.find(End)])
            break
        total_data.append(data)
        if len(total_data) > 1:
            # check if end_of_data was split
            last_pair = total_data[-2]+total_data[-1]
            if End in last_pair:
                total_data[-2] = last_pair[:last_pair.find(End)]
                total_data.pop()
                break
    return ''.join(x.decode('utf-8') for x in total_data)


def client_handler(connection):
    data = recv_end(connection)
    json_obj = json.loads(data)
    date = time.strftime('%X %x %Z')
    print(f'\n{date}\n{json_obj}\n\n')
    connection.close()


def accept_connections(ServerSocket):
    Client, address = ServerSocket.accept()
    print('Connected to: ' + address[0] + ':' + str(address[1]))
    thr.start_new_thread(client_handler, (Client, ))


def start_server(host, port):
    ServerSocket = socket.socket()
    try:
        ServerSocket.bind((host, port))
    except socket.error as e:
        print(str(e))
    print(f'Server is listening on the port {port}...')
    ServerSocket.listen()

    while True:
        accept_connections(ServerSocket)


def main():
    args = read_arguments()
    start_server(args.ip, args.port)


if __name__ == "__main__":
    main()
