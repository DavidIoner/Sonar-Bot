import json
import re
from time import sleep

import serial

# Configuração da porta serial
for i in range(10):
    try:
        ser = serial.Serial('COM3', 9600)  # Substitua 'COMx' pela porta serial correta
        if ser:
            pass
    except:
        sleep(1)
        print(f"Conectando a porta COM. Tentativa: {i+1}")

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

            print(angulo, distancia)
