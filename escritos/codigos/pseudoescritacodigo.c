arquivoPal = AbreArquivo(pal.bin);
contador = 0;
enquanto ( contador < vetorPaleta.tamanho )
{
  cor = vetorPaleta[contador];
  
  bitAlto = 1;
  bitAlto = shiftLeft(bitAlto,5);
  bitAlto = bitAlto + shiftRight(cor.azul,3);
  bitAlto = shiftLeft(bitAlto,2);
  bitAlto = bitAlto + shiftRight(cor.verde,6);
  
  bitBaixo = shiftRight(seisBitsMaisBaixos(cor.verde),3);
  bitBaixo = shiftLeft(bitBaixo,5);
  bitBaixo = bitBaixo + shiftRight(cor.vermelho,3);
  
  escreveChar(arquivoPal, bitBaixo);
  escreveChar(arquivoPal, bitAlto);
}
enquanto ( contador < 256 )
{
  escreveChar(arquivoPal, 0);
  escreveChar(arquivoPal, 0);
}
FechaArquivo(arquivoPal);

arquivoTiles = AbreArquivo(tiles.bin);
paraCada tile em vetorTiles
{
  paraCada pixel em tile
  {
    indicePaleta = devolveIndicePelaCor(pixel, vetorPaleta);
    escreveChar(arquivoTiles, indicePaleta);
  }
}
contador = 0;
enquanto contador < 64
{
  escreveChar(arquivoTiles, 0);
}
fechaArquivo(arquivoTiles);

arquivoMap = AbreArquivo(map.bin);
paraCada indice em matrizMap
{
  escreveChar(arquivoMap,indice);
}
fechaArquivo(arquivoMap);
