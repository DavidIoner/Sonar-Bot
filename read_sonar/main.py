import bluetooth

# Endereço MAC do ESP32 (substitua pelo endereço do seu dispositivo)
esp32_address = "94:E6:86:3B:86:8A"

def receive_data():
    server_sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    server_sock.bind(("",  bluetooth.PORT_ANY))
    server_sock.listen(1)


    try:
        print("Aguardando conexão Bluetooth...")
        client_sock, address = server_sock.accept()
        print(f"Conectado a {address}")
        while True:
            data = client_sock.recv(1024)
            if not data:
                break
            print(f"Valor recebido: {data.decode('utf-8')}")

    except KeyboardInterrupt:
        pass

    print("Conexão encerrada.")
    client_sock.close()
    server_sock.close()

if __name__ == "__main__":
    receive_data()