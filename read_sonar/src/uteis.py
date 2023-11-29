import json
import re
from time import sleep

import serial

ser = serial.Serial('COM3', 9600)  # Substitua 'COMx' pela porta serial correta



    
def serialRead(ser):
    while True:
        # Lê a linha da porta serial
        line = ser.readline()

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

                return (angulo, distancia)

print(serialRead(ser))