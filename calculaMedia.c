double calculaMedia(double *valores, int quantidade){
    double media = 0;
    for(int i = 0; i < quantidade; i++){
        media += valores[i];
    }

    media = media / quantidade;
    return media;
}

