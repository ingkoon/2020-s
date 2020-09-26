import socket

server_socket =  socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_socket.bind(('localhost',2222))
server_socket.listen(0)

client_socket, addr = server_socket.accept()
data = client_socket.recv(62235)

print(data.decode())
