import json
import re

import serial

ser = serial.Serial('COM3', 9600)  # Substitua 'COMx' pela porta serial correta
if ser:
    print('conectado')
else:
    print('falha ao conectar')

while True:
    line = ser.readline().decode("utf-8")
    print(line)
        # Verifica se a linha não está vazia
    if line:
        match = re.search(r'\{.*\}', str(line))

        if match:
                # Obtém a parte correspondente à expressão regular
            json_recebido = match.group()

                # Carrega a string JSON em um objeto Python
            dados_json = json.loads(json_recebido)

                # Agora você pode acessar os itens do JSON
            angulo = dados_json['angulo']
            distancia = dados_json['distancia']
            print(distancia, angulo)