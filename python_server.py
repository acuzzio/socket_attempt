from pathlib import Path
import socket
import _thread as thr
import time

import json
from argparse import ArgumentParser


def read_arguments():
    description_string = "This is the tcp server."
    parser = ArgumentParser(description=description_string)
    parser.add_argument(
        "-i", "--ip", type=str, default="127.0.0.1", help="ip host"
    )
    parser.add_argument("-p", "--port", type=int, default=9998, help="port")
    return parser.parse_args()


def recv_end(the_socket):
    End = b"<<END>>"
    total_data = []
    data = ""
    while True:
        data = the_socket.recv(8192)
        if End in data:
            total_data.append(data[: data.find(End)])
            break
        total_data.append(data)
        if len(total_data) > 1:
            # check if end_of_data was split
            last_pair = total_data[-2] + total_data[-1]
            if End in last_pair:
                total_data[-2] = last_pair[: last_pair.find(End)]
                total_data.pop()
                break
    # return "".join(x.decode("utf-8") for x in total_data)
    return b"".join(total_data)


def get_filename(root_path: Path, date: time.struct_time) -> Path:
    folder = (
        root_path / f"{date.tm_year}" / f"{date.tm_mon}" / f"{date.tm_mday}"
    )
    file = f"{date.tm_hour}_{date.tm_min}_{date.tm_sec}.json"
    folder.mkdir(parents=True, exist_ok=True)
    fn = folder / file
    return fn


def client_handler(connection):
    data = recv_end(connection)
    date = time.localtime()
    fn = get_filename(Path("."), date)
    with open(fn, "bw") as f:
        f.write(data)
    print(f"\nFile {fn} written.\n")
    # print(f'\n{date=}\n{data=}\n\n')
    connection.close()


def accept_connections(ServerSocket):
    Client, address = ServerSocket.accept()
    print("Connected to: " + address[0] + ":" + str(address[1]))
    thr.start_new_thread(client_handler, (Client,))


def start_server(host, port):
    ServerSocket = socket.socket()
    try:
        ServerSocket.bind((host, port))
    except socket.error as e:
        print(str(e))
    print(f"Server is listening on the port {port}...")
    ServerSocket.listen()

    while True:
        accept_connections(ServerSocket)


def main():
    args = read_arguments()
    start_server(args.ip, args.port)


if __name__ == "__main__":
    main()
