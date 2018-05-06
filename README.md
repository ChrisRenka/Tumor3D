# Tumor3D

Códigos em C: realizam a simulação. Os resultados são salvos em pastas numeradas com o valor da simulação (a primeira simulação será salva na pasta 1, a segunda na pasta 2, e assim a diante).
Em cada pasta, o arquivo "dados.txt" guarda os parâmetros da simulação. Os outros arquivos da pasta são na forma "necroX.txt", "proliX.txt", "quieX.txt" e "vasosX.txt". Estes arquivos guardam, respectivamente, as posições das células necróticas, proliferativas, quiescentes e vasos sanguíneos no frame X da simulação.

Códigos em Python3: realizam o plot tridimensional do tumor. Ao executar um destes códigos, será perguntado primeiro o número da simulação que se quer plotar, e em seguida o número do frame.
Cada código plota uma parte diferente do tumor, sendo:
 - plot_necro.py: plota as células necróticas;
 - plot_proli.py: plota as células proliferativas;
 - plot_quie.py: plota as células quiescentes;
 - plot_tudo.py: plota todas as células simultaneamente;
 - plot_tumor.py: plota todo o tumor, sem vasos sanguíneos;
 - plot_vasos.py: plota os vasos sanguíneos;
 
Os parâmetros da simulação são definidos no arquivo tumor3D.h, e eles são:

- TAM: tamanho da rede
- PASSOS: total de passos da simulação
- PASSOS_INIC: número de passos antes da rede ser semeada
- VASOS: quantidade de vasos sanguíneos
- ISIM: quantidade de passos entre cada frame salvo

- OP: nível de oxigênio mínimo para células proliferativas
- OQ: nível de oxigênio mínimo para células quiescentes
- GT: nível de glicose mínimo para células proliferativas e quiescentes
- TD: tempo médio de divisão de uma célula proliferativa
- TN: tempo médio para remoção de uma célula necrótica

- DO: coeficiente de difusão do oxigênio
- OKV: produção de oxigênio nos vasos sanguíneos
- OPC: consumo de oxigênio por células proliferativas
- OQC: consumo de oxigênio por células quiescentes
- OO: concentração inicial de oxigênio
- DG: coeficiente de difusão da glicose
- GKV: produção de glicose nos vasos sanguíneos
- GPC: consumo de glicose por células proliferativas
- GQC: consumo de glicose por células quiescentes
- GO: concentração inicial de glicose

- AO: concentração inicial de fatores angiogênicos
- DA: coeficiente de difusão dos fatores angiogênicos
- AKV: consumo de fatores angiogênicos por vasos sanguíneos
- APC: consumo de fatores angiogênicos por células proliferativas
- AQC: consumo de fatores angiogênicos por células quiescentes
- AN: produção de fatores angiogênicos quando uma célula se torna necrótica
- AP: nível mínimo de fatores angiogênicos para a angiogênese
- AT: tempo médio de reprodução de um vaso sanguíneo
- MAX_VIZS: número máximo de células sanguíneas que um vaso sangúineo pode ter como vizinho



