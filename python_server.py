from pathlib import Path
import socket
import _thread as thr
import time

from argparse import ArgumentParser


def read_arguments():
    description_string = "This is the tcp server."
    parser = ArgumentParser(description=description_string)
    parser.add_argument(
        "-i", "--ip", type=str, default="127.0.0.1", help="ip host"
    )
    parser.add_argument("-p", "--port", type=int, default=9998, help="port")
    return parser.parse_args()


def cleanstring(bytestring):
    return bytestring.split(b"\x00", 1)[0]


def get_filename(
    root_path: Path, date: time.struct_time, name: str = ""
) -> Path:
    folder = (
        root_path / f"{date.tm_year}" / f"{date.tm_mon}" / f"{date.tm_mday}"
    )
    if not name:
        name = f"{date.tm_hour}_{date.tm_min}_{date.tm_sec}.json"
    folder.mkdir(parents=True, exist_ok=True)
    fn = folder / name
    return fn


def recv_end(the_socket):
    size_of_name_msg = the_socket.recv(128)
    size_of_name = int(cleanstring(size_of_name_msg))
    name = the_socket.recv(size_of_name)
    size_of_data_msg = the_socket.recv(128)
    size_of_data = int(cleanstring(size_of_data_msg))
    data = the_socket.recv(size_of_data)
    print(f"""
{size_of_name_msg=}
{size_of_name=}
{name=}
{size_of_data_msg=}
{size_of_data=}
""")
    return size_of_name, name.decode("utf-8"), size_of_data, data


def client_handler(connection):
    _, name, _, data = recv_end(connection)
    date = time.localtime()
    fn = get_filename(Path("."), date, name)
    with open(fn, "bw") as f:
        f.write(data)
    print(f"\nFile {fn} written.\n")
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
