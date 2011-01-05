LeImagem();
CorTransparente = Magenta;
TamanhoDoSprite = 8x8;
InsereNaPaleta(CorTransparente);
ParaCadaUm pixelsNaHorizontal faca
  ParaCadaUm pixelsNaVertical faca
    Comeca
      Cor = Faz3BitsMenosSignificativosDeCadaCorZero(CorDoPixel);
      Se Cor naoExiste em paleta
        InsereNaPaleta(Cor);
      InserePixelNoSprite(Cor,Sprite);
      Se Sprite temTamanho tamanhoDoSprite
      Comeca
        Se Sprite naoExiste em VetorDeSprites
          Comeca
            InsereNoVetorDeSprites(Sprite);
            IndiceSprite = VetorDeSprites.Ultimo;
          Termina;
        Senao
          IndiceSprite = IndiceNoVetorDeSprites(Sprite);
        
        PintaNaTela(Sprite);
        PintaNaTela(QuadradoGrid, PosicaoSprite);
        MatrizMapa[PosicaoSprite] = IndiceSprite;
        
        ZeraSprite(Sprite);
      Termina;
    Termina;

ParaCadaUm VetorSprites faca
  PintaNoGridDeSprites(Sprite)